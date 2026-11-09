import math
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

# ---------- Параметры ----------
N = 1000
EPS = 0.05
REPS = 2000
SEED = 2024
M_N, S2_N = 5.0, 9.0
S_N = math.sqrt(S2_N)

np.random.seed(SEED)

# 1. ТРИ МЕТОДА ГЕНЕРАЦИИ

def gen_inverse(n, m, s):
    """Метод обратной функции: u -> ppf(u)."""
    u = np.random.uniform(0, 1, n)
    return stats.norm.ppf(u, loc=m, scale=s)


def gen_box_muller(n, m, s):
    """
    Бокс — Мюллер:
        Z1 = sqrt(-2 ln U1) * cos(2 pi U2)
        Z2 = sqrt(-2 ln U1) * sin(2 pi U2)
    """
    result = np.empty(n)
    half = (n + 1) // 2
    for i in range(half):
        u1 = np.random.uniform(0, 1)
        u2 = np.random.uniform(0, 1)
        while u1 < 1e-15:
            u1 = np.random.uniform(0, 1)
        r = math.sqrt(-2 * math.log(u1))
        z1 = r * math.cos(2 * math.pi * u2)
        z2 = r * math.sin(2 * math.pi * u2)
        result[2 * i] = z1
        if 2 * i + 1 < n:
            result[2 * i + 1] = z2
    return m + s * result


def gen_clt(n, m, s, k=12):
    """
    ЦПТ: Z = (sum_{i=1}^k U_i - k/2) / sqrt(k/12)  ~ N(0, 1).
    При k=12: Z = sum(U_i) - 6.
    """
    u = np.random.uniform(0, 1, (n, k)).sum(axis=1)
    z = (u - k / 2.0) / math.sqrt(k / 12.0)
    return m + s * z

# 2. ТЕОРЕТИЧЕСКИЕ CDF/PDF/PPF

normal_cdf = lambda x: stats.norm.cdf(x, loc=M_N, scale=S_N)
normal_ppf = lambda p: stats.norm.ppf(p, loc=M_N, scale=S_N)
normal_pdf = lambda x: stats.norm.pdf(x, loc=M_N, scale=S_N)

# 3. ОЦЕНКИ

def sample_mean_var(data):
    return float(np.mean(data)), float(np.var(data, ddof=1))


# 4. КРИТЕРИЙ КОЛМОГОРОВА

def kolmogorov_test(sample, cdf_func, alpha=EPS):
    n = len(sample)
    sorted_data = np.sort(sample)
    ecdf = np.arange(1, n + 1) / n
    tcdf = cdf_func(sorted_data)
    D_plus = np.max(ecdf - tcdf)
    D_minus = np.max(tcdf - np.concatenate([[0.0], ecdf[:-1]]))
    D = max(D_plus, D_minus)
    stat = math.sqrt(n) * D
    threshold = 1.358 if alpha == 0.05 else 1.628
    return D, stat, threshold, stat > threshold

# 5. КРИТЕРИЙ ПИРСОНА

def pearson_test(sample, ppf_func, n_bins=20, alpha=EPS):
    n = len(sample)
    probs = np.linspace(0, 1, n_bins + 1)[1:-1]
    edges = ppf_func(probs)
    edges = np.concatenate([[-np.inf], edges, [np.inf]])

    observed, _ = np.histogram(sample, bins=edges)
    expected = np.full(n_bins, n / n_bins)

    obs_m, exp_m, o_buf, e_buf = [], [], 0, 0.0
    for o, e in zip(observed, expected):
        o_buf += o; e_buf += e
        if e_buf >= 5.0:
            obs_m.append(o_buf); exp_m.append(e_buf)
            o_buf, e_buf = 0, 0.0
    if e_buf > 1e-9:
        obs_m[-1] += o_buf; exp_m[-1] += e_buf

    chi2 = sum((o - e) ** 2 / e for o, e in zip(obs_m, exp_m))
    df = len(exp_m) - 1
    p = 1 - stats.chi2.cdf(chi2, df)
    return chi2, df, p, p < alpha


# 6. ОСНОВНОЙ СЦЕНАРИЙ

def separator(title=""):
    print("\n" + "=" * 66)
    if title:
        print(title)
        print("=" * 66)


separator("1. ГЕНЕРАЦИЯ ВЫБОРОК ТРЕМЯ МЕТОДАМИ")

samples = {
    "Обратная функция": gen_inverse(N, M_N, S_N),
    "Бокс — Мюллер":    gen_box_muller(N, M_N, S_N),
    "ЦПТ (k=12)":       gen_clt(N, M_N, S_N, k=12),
}

separator("2. ОЦЕНКИ МАТОЖИДАНИЯ И ДИСПЕРСИИ")

for name, data in samples.items():
    m_emp, v_emp = sample_mean_var(data)
    print(f"\n{name}:")
    print(f"  Мат.ожидание: теория = {M_N:.4f},  оценка = {m_emp:.4f},  "
          f"|Δ| = {abs(M_N - m_emp):.4f}")
    print(f"  Дисперсия:    теория = {S2_N:.4f},  оценка = {v_emp:.4f},  "
          f"|Δ| = {abs(S2_N - v_emp):.4f}")


separator("3. КРИТЕРИЙ КОЛМОГОРОВА")

for name, data in samples.items():
    D, stat, thr, rej = kolmogorov_test(data, normal_cdf)
    print(f"{name:<22}  D_n = {D:.4f},  sqrt(n)D = {stat:.4f}  "
          f"(порог {thr})  ->  {'ОТВЕРГАЕМ' if rej else 'принимаем'}")


separator("4. КРИТЕРИЙ ПИРСОНА")

for name, data in samples.items():
    chi2, df, p, rej = pearson_test(data, normal_ppf)
    print(f"{name:<22}  chi2 = {chi2:.4f},  df = {df},  p = {p:.4f}  ->  "
          f"{'ОТВЕРГАЕМ' if rej else 'принимаем'}")


separator(f"5. ОШИБКА I РОДА ({REPS} повторов)")

def type1_error(generator, cdf_func, ppf_func, n_reps=REPS):
    rej_ks, rej_chi = 0, 0
    for _ in range(n_reps):
        s = generator(N, M_N, S_N)
        if kolmogorov_test(s, cdf_func)[3]:
            rej_ks += 1
        if pearson_test(s, ppf_func)[3]:
            rej_chi += 1
    return rej_ks / n_reps, rej_chi / n_reps

methods = {
    "Обратная функция": gen_inverse,
    "Бокс — Мюллер":    gen_box_muller,
    "ЦПТ (k=12)":       lambda n, m, s: gen_clt(n, m, s, k=12),
}

print(f"\n{'Метод':<22}{'KS ошибка':>14}{'χ² ошибка':>14}")
print("-" * 52)
for name, gen in methods.items():
    ks_err, chi_err = type1_error(gen, normal_cdf, normal_ppf)
    print(f"{name:<22}{ks_err:>14.4f}{chi_err:>14.4f}")
print("(номинал ε = 0.05)")

# 7. ГРАФИКИ

fig, axes = plt.subplots(len(samples), 2, figsize=(14, 10))

for i, (name, data) in enumerate(samples.items()):
    lo, hi = normal_ppf(0.001), normal_ppf(0.999)

    # гистограмма + плотность
    ax = axes[i, 0]
    ax.hist(data[(data >= lo) & (data <= hi)], bins=40, density=True,
            alpha=0.6, color="steelblue", label="Гистограмма")
    xs = np.linspace(lo, hi, 400)
    ax.plot(xs, normal_pdf(xs), "r-", lw=2, label="Теоретическая плотность")
    ax.set_title(f"{name}: гистограмма vs плотность")
    ax.set_xlabel("x"); ax.set_ylabel("плотность")
    ax.legend(); ax.grid(alpha=0.3)

    # CDF
    ax = axes[i, 1]
    sorted_data = np.sort(data)
    ecdf = np.arange(1, len(sorted_data) + 1) / len(sorted_data)
    ax.step(sorted_data, ecdf, where="post", color="steelblue", label="Эмпирическая CDF")
    ax.plot(xs, normal_cdf(xs), "r-", lw=2, label="Теоретическая CDF")
    ax.set_title(f"{name}: эмпирическая vs теоретическая CDF")
    ax.set_xlabel("x"); ax.set_ylabel("F(x)")
    ax.legend(); ax.grid(alpha=0.3)

plt.tight_layout()
plt.savefig("lab3_normal.png", dpi=120)
plt.show()
print("\nГрафики сохранены в lab3_normal.png")