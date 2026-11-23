# Лабораторная работа №4. Метод Монте-Карло.
# Вариант 6.
#   I1 = ∫_{-∞}^{+∞} e^{-x^4} sqrt(1 + x^2) dx
#   I2 = ∬_{1 ≤ x²+y² < 7} (x³ + e^y) / (x² + 2y²) dx dy

import math
import numpy as np
import matplotlib.pyplot as plt
from scipy import integrate, optimize

N_MAX = 100000
N_TABLE = [100, 1000, 10000, 100000]
Z95 = 1.96


# ---------- Генератор БСВ (линейный конгруэнтный) ----------
class LCG:
    def __init__(self, seed=12345):
        self.state = seed
        self.a = 1664525
        self.c = 1013904223
        self.m = 2 ** 32

    def random(self):
        self.state = (self.a * self.state + self.c) % self.m
        return (self.state + 0.5) / self.m


lcg = LCG()


# ---------- Эталоны ----------
# I1: аналитически не берётся -> scipy.quad
def f1(x):
    return math.exp(-x ** 4) * math.sqrt(1 + x ** 2)

L = 6.0   # обрезание: |x| > 6 -> f1(x) < 1e-500
I1_EXACT = integrate.quad(f1, -L, L, epsabs=1e-12, epsrel=1e-12)[0]
I1_TAIL  = integrate.quad(f1, L, np.inf, epsabs=1e-12)[0] \
         + integrate.quad(f1, -np.inf, -L, epsabs=1e-12)[0]
I1_EXACT += I1_TAIL

# I2: аналитически не берётся -> scipy.dblquad в полярных координатах
def f2_polar(r, theta):
    x, y = r * math.cos(theta), r * math.sin(theta)
    return (x ** 3 + math.exp(y)) / (x ** 2 + 2 * y ** 2) * r 

I2_EXACT = integrate.dblquad(
    f2_polar, 0, 2 * math.pi,
    lambda _: 1.0,
    lambda _: math.sqrt(7.0),
    epsabs=1e-10, epsrel=1e-10)[0]


# ---------- Подынтегральная функция для I2 (hit-or-miss) ----------
# Слагаемое x^3/(x^2+2y^2) обнуляется по симметрии области,
# остаётся только e^y/(x^2+2y^2) >= 0
def g2_pos(x, y):
    return math.exp(y) / (x ** 2 + 2 * y ** 2)


# ---------- Поиск g_max на кольце ----------
# параметризация в полярных: r ∈ [1, √7], theta ∈ [0, 2π)
def neg_g2_polar(r, theta):
    if r < 1.0 or r >= math.sqrt(7.0):
        return 1e10
    x, y = r * math.cos(theta), r * math.sin(theta)
    return -g2_pos(x, y)

# грубый перебор по сетке
best = (-np.inf, None, None)
for r0 in np.linspace(1.001, math.sqrt(7.0) - 0.001, 50):
    for t0 in np.linspace(0, 2 * math.pi, 90, endpoint=False):
        val = g2_pos(r0 * math.cos(t0), r0 * math.sin(t0))
        if val > best[0]:
            best = (val, r0, t0)

# уточнение через Nelder-Mead
res = optimize.minimize(
    lambda p: neg_g2_polar(p[0], p[1]),
    x0=[best[1], best[2]],
    method="Nelder-Mead",
    options={"xatol": 1e-9, "fatol": 1e-13, "maxiter": 10000})

G_MAX = -res.fun * 1.01
R_BOX = math.sqrt(7.0)
V_BOX = (2 * R_BOX) ** 2 * G_MAX


# ---------- Метод Монте-Карло ----------
# I1: обрезаем на [-L, L], x_i ~ U[-L, L]
def mc_I1(n):
    vals = np.empty(n)
    for i in range(n):
        x = 2 * L * lcg.random() - L       # U[-L, L]
        vals[i] = 2 * L * f1(x)            # 2L * f(x) = f(x) / p(x)
    return vals


# I2: hit-or-miss в коробке [-R, R] × [-R, R] × [0, g_max]
def mc_I2(n):
    vals = np.empty(n)
    for i in range(n):
        x = 2 * R_BOX * lcg.random() - R_BOX
        y = 2 * R_BOX * lcg.random() - R_BOX
        z = G_MAX * lcg.random()

        r2 = x * x + y * y
        if 1.0 <= r2 < 7.0 and z <= g2_pos(x, y):
            vals[i] = V_BOX                # попадание
        else:
            vals[i] = 0.0
    return vals


# ---------- Накопленные оценки ----------
def running_estimates(vals):
    n = np.arange(1, len(vals) + 1)
    mean = np.cumsum(vals) / n
    mean_sq = np.cumsum(vals ** 2) / n
    var = np.maximum(mean_sq - mean ** 2, 0) * n / np.maximum(n - 1, 1)
    se = np.sqrt(var / n)
    return mean, se


# ---------- Моделирование ----------
print("1. ЭТАЛОННЫЕ ЗНАЧЕНИЯ\n")
print(f"I1: scipy.quad    = {I1_EXACT:.10f}   (хвост = {I1_TAIL:.2e})")
print(f"I2: scipy.dblquad = {I2_EXACT:.10f}")
print(f"g_max = {G_MAX:.6f},  V_box = {V_BOX:.6f}\n")

vals1 = mc_I1(N_MAX)
vals2 = mc_I2(N_MAX)
est1, se1 = running_estimates(vals1)
est2, se2 = running_estimates(vals2)

# ---------- Таблица ----------
print("2. РЕЗУЛЬТАТЫ МОНТЕ-КАРЛО\n")
for name, est, se, exact in (("I1", est1, se1, I1_EXACT),
                             ("I2", est2, se2, I2_EXACT)):
    print(f"{name} (эталон = {exact:.6f})")
    print(f"{'n':>8s} | {'оценка':>12s} | {'abs. ошибка':>12s} | "
          f"{'ст. ошибка':>12s} | 95% дов. интервал")
    for n in N_TABLE:
        e, s = est[n - 1], se[n - 1]
        print(f"{n:8d} | {e:12.6f} | {abs(e - exact):12.2e} | "
              f"{s:12.2e} | [{e - Z95*s:.6f}, {e + Z95*s:.6f}]")
    print()


# ---------- Графики ----------
fig, axes = plt.subplots(2, 2, figsize=(14, 9))
ns = np.arange(1, N_MAX + 1)

for col, (name, est, se, exact) in enumerate((
        ("I1", est1, se1, I1_EXACT),
        ("I2", est2, se2, I2_EXACT))):

    ax = axes[0, col]
    ax.plot(ns, est, label="Оценка Монте-Карло", linewidth=1)
    ax.fill_between(ns, est - Z95*se, est + Z95*se, alpha=0.25,
                    label="95% доверительный интервал")
    ax.axhline(exact, color="r", linestyle="--", label="Эталон")
    ax.set_xscale("log")
    ax.set_xlabel("n")
    ax.set_ylabel("Значение интеграла")
    ax.set_title(f"Сходимость оценки {name}")
    ax.legend()
    ax.grid(True, alpha=0.3)

    ax = axes[1, col]
    err = np.abs(est - exact)
    ax.loglog(ns, np.maximum(err, 1e-14), linewidth=0.8, label="|ошибка|")
    ax.loglog(ns, Z95*se, "g-", linewidth=1.5, label="1.96·s/√n")
    ref = Z95 * se[-1] * math.sqrt(N_MAX) / np.sqrt(ns)
    ax.loglog(ns, ref, "r--", label="~ 1/√n")
    ax.set_xlabel("n")
    ax.set_ylabel("Погрешность")
    ax.set_title(f"Точность {name} vs n")
    ax.legend()
    ax.grid(True, which="both", alpha=0.3)

plt.tight_layout()
plt.savefig("lab4_plots.png", dpi=120)
plt.show()
print("Графики сохранены в lab4_plots.png")