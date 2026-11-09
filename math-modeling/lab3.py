import math
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

# ---------- Параметры эксперимента ----------
N = 1000             # объём выборки
EPS = 0.05           # уровень значимости
REPS = 2000          # число повторов для ошибки I рода
SEED = 2024          # seed

np.random.seed(SEED)

# 1. ГЕНЕРАЦИЯ ВЫБОРОК (метод обратной функции)

def inv_normal(u, m, s):
    """Обратная функция нормального распределения (через scipy)."""
    return stats.norm.ppf(u, loc=m, scale=s)


def inv_cauchy(u, a, b):
    """Обратная функция распределения Коши: x = a + b*tg(pi*(u-0.5))."""
    return a + b * math.tan(math.pi * (u - 0.5))


def inv_laplace(u, a):
    """Обратная функция распределения Лапласа (сдвиг 0, масштаб a)."""
    # F(x) = 0.5*exp(x/a) при x<0; 1-0.5*exp(-x/a) при x>=0
    if u < 0.5:
        return a * math.log(2 * u)
    else:
        return -a * math.log(2 * (1 - u))


def simulate_inverse(n, inv_cdf):
    """Универсальная генерация: n значений через обратную функцию и БСВ."""
    u = np.random.uniform(0, 1, n)
    return np.array([inv_cdf(x) for x in u])

# 2. ТЕОРЕТИЧЕСКИЕ ХАРАКТЕРИСТИКИ

# N(5, 9): E = 5, Var = 9
TRUE_NORMAL = {"mean": 5.0, "var": 9.0}

# Коши C(-1, 3): моменты не существуют
TRUE_CAUCHY = {"mean": None, "var": None,
               "median": -1.0, "iqr": 2 * 3.0}   # IQR = 2b

# Лапласа L(2): E = 0, Var = 2a^2 = 8 (a — масштаб)
TRUE_LAPLACE = {"mean": 0.0, "var": 2 * 2.0 ** 2}

# 3. ОЦЕНКИ

def sample_mean_var(data):
    """Несмещённые оценки: mean и var (ddof=1)."""
    return float(np.mean(data)), float(np.var(data, ddof=1))


def sample_median_iqr(data):
    """Медиана и межквартильный размах — робастные оценки для Коши."""
    med = float(np.median(data))
    q1, q3 = np.percentile(data, [25, 75])
    return med, float(q3 - q1)

# 4. КРИТЕРИЙ КОЛМОГОРОВА
def kolmogorov_test(sample, cdf_func, alpha=EPS):
    n = len(sample)
    sorted_data = np.sort(sample)

    ecdf = np.arange(1, n + 1) / n          # F_n(x_i)
    tcdf = cdf_func(sorted_data)             # F(x_i)

    # D+ = max_i (i/n - F(x_i))
    # D- = max_i (F(x_i) - (i-1)/n)
    D_plus  = np.max(ecdf - tcdf)
    D_minus = np.max(tcdf - np.concatenate([[0.0], ecdf[:-1]]))
    D = max(D_plus, D_minus)

    stat = math.sqrt(n) * D
    threshold = 1.358 if alpha == 0.05 else 1.628
    reject = stat > threshold
    return D, stat, threshold, reject

# 5. КРИТЕРИЙ ПИРСОНА

def pearson_test(sample, cdf_func, ppf_func, n_bins=20, alpha=EPS):
    """
    sample  : выборка
    cdf_func: теоретическая CDF (для расчёта ожидаемых вероятностей)
    ppf_func: обратная CDF (для равновероятного разбиения)
    n_bins  : желаемое число корзин (до объединения)
    """
    n = len(sample)

    # Равновероятное разбиение: границы через квантили
    probs = np.linspace(0, 1, n_bins + 1)[1:-1]
    edges = ppf_func(probs)
    edges = np.concatenate([[-np.inf], edges, [np.inf]])

    observed, _ = np.histogram(sample, bins=edges)
    expected = np.full(n_bins, n / n_bins)

    # объединяем корзины с e < 5
    obs_merged, exp_merged = [], []
    o_buf, e_buf = 0, 0.0
    for o, e in zip(observed, expected):
        o_buf += o
        e_buf += e
        if e_buf >= 5.0:
            obs_merged.append(o_buf)
            exp_merged.append(e_buf)
            o_buf, e_buf = 0, 0.0
    if e_buf > 1e-9:
        obs_merged[-1] += o_buf
        exp_merged[-1] += e_buf

    chi2 = sum((o - e) ** 2 / e for o, e in zip(obs_merged, exp_merged))
    df = len(exp_merged) - 1
    p_value = 1 - stats.chi2.cdf(chi2, df)
    return chi2, df, p_value, p_value < alpha

# 6. СБОРКА РАСПРЕДЕЛЕНИЙ

# N(5, 9)
m_n, s2_n = 5.0, 9.0
s_n = math.sqrt(s2_n)
normal_sample = simulate_inverse(N, lambda u: inv_normal(u, m_n, s_n))
normal_cdf = lambda x: stats.norm.cdf(x, loc=m_n, scale=s_n)
normal_ppf = lambda p: stats.norm.ppf(p, loc=m_n, scale=s_n)

# Коши C(-1, 3)
a_c, b_c = -1.0, 3.0
cauchy_sample = simulate_inverse(N, lambda u: inv_cauchy(u, a_c, b_c))
cauchy_cdf = lambda x: stats.cauchy.cdf(x, loc=a_c, scale=b_c)
cauchy_ppf = lambda p: stats.cauchy.ppf(p, loc=a_c, scale=b_c)

# Лапласа L(2)
a_l = 2.0
laplace_sample = simulate_inverse(N, lambda u: inv_laplace(u, a_l))
laplace_cdf = lambda x: stats.laplace.cdf(x, loc=0.0, scale=a_l)
laplace_ppf = lambda p: stats.laplace.ppf(p, loc=0.0, scale=a_l)


# 7. MAIN

def separator(title=""):
    print("\n" + "=" * 66)
    if title:
        print(title)
        print("=" * 66)


separator("1. МОДЕЛИРОВАНИЕ И ОЦЕНКИ ПАРАМЕТРОВ")

# --- Нормальное ---
mean_n, var_n = sample_mean_var(normal_sample)
print(f"\nНормальное N({m_n}, {s2_n})")
print(f"  Мат.ожидание: теория = {TRUE_NORMAL['mean']:8.4f}   "
      f"оценка = {mean_n:8.4f}   |Δ| = {abs(TRUE_NORMAL['mean'] - mean_n):.4f}")
print(f"  Дисперсия:    теория = {TRUE_NORMAL['var']:8.4f}   "
      f"оценка = {var_n:8.4f}   |Δ| = {abs(TRUE_NORMAL['var'] - var_n):.4f}")

# --- Коши ---
med_c, iqr_c = sample_median_iqr(cauchy_sample)
print(f"\nКоши C({a_c}, {b_c})  [матожидание и дисперсия НЕ существуют]")
print(f"  Медиана:  теория = {TRUE_CAUCHY['median']:8.4f}   "
      f"оценка = {med_c:8.4f}   |Δ| = {abs(TRUE_CAUCHY['median'] - med_c):.4f}")
print(f"  IQR:      теория = {TRUE_CAUCHY['iqr']:8.4f}   "
      f"оценка = {iqr_c:8.4f}   |Δ| = {abs(TRUE_CAUCHY['iqr'] - iqr_c):.4f}")
print(f"  (выборочное среднее = {np.mean(cauchy_sample):.4f} — "
      f"нестабильно, для Коши не используется)")

# --- Лапласа ---
mean_l, var_l = sample_mean_var(laplace_sample)
print(f"\nЛапласа L({a_l})")
print(f"  Мат.ожидание: теория = {TRUE_LAPLACE['mean']:8.4f}   "
      f"оценка = {mean_l:8.4f}   |Δ| = {abs(TRUE_LAPLACE['mean'] - mean_l):.4f}")
print(f"  Дисперсия:    теория = {TRUE_LAPLACE['var']:8.4f}   "
      f"оценка = {var_l:8.4f}   |Δ| = {abs(TRUE_LAPLACE['var'] - var_l):.4f}")


separator("2. КРИТЕРИЙ КОЛМОГОРОВА")

D_n, stat_n, thr_n, rej_n = kolmogorov_test(normal_sample, normal_cdf)
print(f"\nN({m_n}, {s2_n}):  D_n = {D_n:.4f},  sqrt(n)*D_n = {stat_n:.4f},  "
      f"порог = {thr_n}  ->  {'ОТВЕРГАЕМ' if rej_n else 'принимаем'} H0")

D_c, stat_c, thr_c, rej_c = kolmogorov_test(cauchy_sample, cauchy_cdf)
print(f"C({a_c}, {b_c}):  D_n = {D_c:.4f},  sqrt(n)*D_n = {stat_c:.4f},  "
      f"порог = {thr_c}  ->  {'ОТВЕРГАЕМ' if rej_c else 'принимаем'} H0")

D_l, stat_l, thr_l, rej_l = kolmogorov_test(laplace_sample, laplace_cdf)
print(f"L({a_l}):     D_n = {D_l:.4f},  sqrt(n)*D_n = {stat_l:.4f},  "
      f"порог = {thr_l}  ->  {'ОТВЕРГАЕМ' if rej_l else 'принимаем'} H0")


separator("3. КРИТЕРИЙ ПИРСОНА")

chi2_n, df_n, p_n, rej_n2 = pearson_test(normal_sample, normal_cdf, normal_ppf)
print(f"\nN({m_n}, {s2_n}):  chi2 = {chi2_n:.4f},  df = {df_n},  "
      f"p-value = {p_n:.4f}  ->  {'ОТВЕРГАЕМ' if rej_n2 else 'принимаем'} H0")

chi2_c, df_c, p_c, rej_c2 = pearson_test(cauchy_sample, cauchy_cdf, cauchy_ppf)
print(f"C({a_c}, {b_c}):  chi2 = {chi2_c:.4f},  df = {df_c},  "
      f"p-value = {p_c:.4f}  ->  {'ОТВЕРГАЕМ' if rej_c2 else 'принимаем'} H0")

chi2_l, df_l, p_l, rej_l2 = pearson_test(laplace_sample, laplace_cdf, laplace_ppf)
print(f"L({a_l}):     chi2 = {chi2_l:.4f},  df = {df_l},  "
      f"p-value = {p_l:.4f}  ->  {'ОТВЕРГАЕМ' if rej_l2 else 'принимаем'} H0")


separator(f"4. ОЦЕНКА ОШИБКИ I РОДА ({REPS} повторов, ε = {EPS})")

def estimate_type1_error(inv_cdf, cdf_func, ppf_func, n_reps=REPS):
    """Генерирует n_reps выборок из правильного распределения, считает долю отвержений."""
    rej_ks, rej_chi = 0, 0
    for _ in range(n_reps):
        s = simulate_inverse(N, inv_cdf)
        if kolmogorov_test(s, cdf_func)[3]:
            rej_ks += 1
        if pearson_test(s, cdf_func, ppf_func)[3]:
            rej_chi += 1
    return rej_ks / n_reps, rej_chi / n_reps

ks_err_n, chi_err_n = estimate_type1_error(
    lambda u: inv_normal(u, m_n, s_n), normal_cdf, normal_ppf)
ks_err_c, chi_err_c = estimate_type1_error(
    lambda u: inv_cauchy(u, a_c, b_c), cauchy_cdf, cauchy_ppf)
ks_err_l, chi_err_l = estimate_type1_error(
    lambda u: inv_laplace(u, a_l), laplace_cdf, laplace_ppf)

print(f"\n{'Распределение':<22}{'KS ошибка':>14}{'χ² ошибка':>14}")
print("-" * 50)
print(f"{'N(5, 9)':<22}{ks_err_n:>14.4f}{chi_err_n:>14.4f}")
print(f"{'C(-1, 3)':<22}{ks_err_c:>14.4f}{chi_err_c:>14.4f}")
print(f"{'L(2)':<22}{ks_err_l:>14.4f}{chi_err_l:>14.4f}")
print(f"{'(номинал ε = 0.05)':<22}")


separator("5. ПЕРЕКРЁСТНАЯ ПРОВЕРКА (каждая выборка каждым критерием)")

distributions = [
    ("N(5, 9)", normal_sample, normal_cdf, normal_ppf),
    ("C(-1, 3)", cauchy_sample, cauchy_cdf, cauchy_ppf),
    ("L(2)", laplace_sample, laplace_cdf, laplace_ppf),
]

for s_name, s_data, _, _ in distributions:
    print(f"\n--- Выборка из {s_name} ---")
    for d_name, _, d_cdf, d_ppf in distributions:
        _, stat, thr, rej = kolmogorov_test(s_data, d_cdf)
        chi2, df, p, rej2 = pearson_test(s_data, d_cdf, d_ppf)
        print(f"  H0: {d_name:<12}  KS: sqrt(n)D={stat:7.3f} (порог {thr}) "
              f"{'ОТВЕРГ' if rej else 'принимаем':>10}  |  "
              f"χ²: {chi2:8.3f} (df={df}, p={p:.3f}) "
              f"{'ОТВЕРГ' if rej2 else 'принимаем':>10}")


# 6. ГРАФИКИ

fig, axes = plt.subplots(3, 2, figsize=(14, 12))

dist_data = [
    ("N(5, 9)", normal_sample, normal_cdf, normal_ppf),
    ("C(-1, 3)", cauchy_sample, cauchy_cdf, cauchy_ppf),
    ("L(2)", laplace_sample, laplace_cdf, laplace_ppf),
]

for i, (name, data, cdf, ppf) in enumerate(dist_data):
    # ---- левый столбец: гистограмма + теоретическая плотность ----
    ax = axes[i, 0]
    # обрезаем по квантилям 0.1% и 99.9%, чтобы не растягивать график хвостами Коши
    lo, hi = ppf(0.001), ppf(0.999)
    clipped = data[(data >= lo) & (data <= hi)]
    lo, hi = ppf(0.01), ppf(0.99)
    ax.hist(clipped, bins=40, density=True, alpha=0.6, color="steelblue",
            label="Гистограмма выборки")
    xs = np.linspace(lo, hi, 400)
    if name.startswith("N"):
        pdf = stats.norm.pdf(xs, loc=m_n, scale=s_n)
    elif name.startswith("C"):
        pdf = stats.cauchy.pdf(xs, loc=a_c, scale=b_c)
    else:
        pdf = stats.laplace.pdf(xs, loc=0.0, scale=a_l)
    ax.plot(xs, pdf, "r-", lw=2, label="Теоретическая плотность")
    ax.set_title(f"{name}: гистограмма vs плотность")
    ax.set_xlabel("x")
    ax.set_ylabel("плотность")
    ax.legend()
    ax.grid(alpha=0.3)

    # ---- правый столбец: эмпирическая CDF vs теоретическая ----
    ax = axes[i, 1]
    sorted_data = np.sort(data)
    ecdf = np.arange(1, len(sorted_data) + 1) / len(sorted_data)
    ax.step(sorted_data, ecdf, where="post", label="Эмпирическая CDF", color="steelblue")
    xs2 = np.linspace(lo, hi, 400)
    ax.plot(xs2, cdf(xs2), "r-", lw=2, label="Теоретическая CDF")
    ax.set_title(f"{name}: эмпирическая vs теоретическая CDF")
    ax.set_xlabel("x")
    ax.set_ylabel("F(x)")
    ax.legend()
    ax.grid(alpha=0.3)

plt.tight_layout()
plt.savefig("lab3_plots.png", dpi=120)
plt.show()
print("\nГрафики сохранены в lab3_plots.png")