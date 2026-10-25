import numpy as np
from scipy import stats

np.random.seed(42)  # фиксируем seed для воспроизводимости

# ПАРАМЕТРЫ
n = 1000            # объём выборки
alpha = 0.05        # уровень значимости

# 1. БИНОМИАЛЬНОЕ РАСПРЕДЕЛЕНИЕ Bi(m=5, p=0.6)
print("=" * 60)
print("БИНОМИАЛЬНОЕ РАСПРЕДЕЛЕНИЕ Bi(m=5, p=0.6)")
print("=" * 60)

m_binom, p_binom = 5, 0.6
true_mean_binom = m_binom * p_binom            # = 3.0
true_var_binom  = m_binom * p_binom * (1 - p_binom)  # = 1.2

sample_binom = np.random.binomial(m_binom, p_binom, n)

# несмещённые оценки
mean_binom = sample_binom.mean()
var_binom  = sample_binom.var(ddof=1)   # ddof=1 для несмещённой оценки

print(f"Истинное матожидание:      {true_mean_binom:.4f}")
print(f"Оценка матожидания:        {mean_binom:.4f}")
print(f"Отклонение:                {abs(mean_binom - true_mean_binom):.4f}")
print()
print(f"Истинная дисперсия:        {true_var_binom:.4f}")
print(f"Оценка дисперсии:          {var_binom:.4f}")
print(f"Отклонение:                {abs(var_binom - true_var_binom):.4f}")
print()

# --- χ²-Пирсон ---
# Возможные значения: 0, 1, 2, 3, 4, 5
k_values = np.arange(0, m_binom + 1)
observed = np.array([np.sum(sample_binom == k) for k in k_values])
expected_prob = stats.binom.pmf(k_values, m_binom, p_binom)
expected = expected_prob * n

# объединяем хвосты, если ожидаемая частота < 5
# (в нашем случае все expected >= 5)
print("Наблюдаемые частоты:", observed)
print("Ожидаемые частоты:  ", np.round(expected, 2))
print()

chi2_binom = np.sum((observed - expected) ** 2 / expected)
df_binom = len(k_values) - 1
chi2_crit_binom = stats.chi2.ppf(1 - alpha, df_binom)

print(f"χ²-статистика:     {chi2_binom:.4f}")
print(f"Число степеней свободы: {df_binom}")
print(f"Критическое значение (α=0.05): {chi2_crit_binom:.4f}")
print(f"Результат: {'ОК (не отвергаем H0)' if chi2_binom < chi2_crit_binom else 'НЕ ОК (отвергаем H0)'}")
print()

# --- Проверка ошибки I рода ---
# Многократно повторяем тест на "истинно биномиальных" выборках
n_reps = 1000
rejections = 0
for _ in range(n_reps):
    s = np.random.binomial(m_binom, p_binom, n)
    obs = np.array([np.sum(s == k) for k in k_values])
    # пересчитываем ожидаемые
    chi2 = np.sum((obs - expected) ** 2 / expected)
    if chi2 >= chi2_crit_binom:
        rejections += 1
print(f"Проверка ошибки I рода ({n_reps} повторов):")
print(f"  Доля отвержений H0: {rejections / n_reps:.4f}  (должно быть ≈ {alpha})")
print()

# 2. РАСПРЕДЕЛЕНИЕ ПУАССОНА П(λ=2)
print("=" * 60)
print("РАСПРЕДЕЛЕНИЕ ПУАССОНА П(λ=2)")
print("=" * 60)

lam = 2.0
true_mean_pois = lam
true_var_pois  = lam

sample_pois = np.random.poisson(lam, n)

mean_pois = sample_pois.mean()
var_pois  = sample_pois.var(ddof=1)

print(f"Истинное матожидание:      {true_mean_pois:.4f}")
print(f"Оценка матожидания:        {mean_pois:.4f}")
print(f"Отклонение:                {abs(mean_pois - true_mean_pois):.4f}")
print()
print(f"Истинная дисперсия:        {true_var_pois:.4f}")
print(f"Оценка дисперсии:          {var_pois:.4f}")
print(f"Отклонение:                {abs(var_pois - true_var_pois):.4f}")
print()

# --- χ²-Пирсон ---
# Определяем диапазон значений, пока хвост не станет маленьким
max_k = 15
k_values_p = np.arange(0, max_k + 1)
observed_p = np.array([np.sum(sample_pois == k) for k in k_values_p])
# последняя категория = ">= max_k" (объединяем хвост)
observed_p[-1] = np.sum(sample_pois >= max_k)
expected_p = stats.poisson.pmf(k_values_p, lam) * n
expected_p[-1] = stats.poisson.sf(max_k - 1, lam) * n  # хвост >= max_k

print("Наблюдаемые частоты:", observed_p)
print("Ожидаемые частоты:  ", np.round(expected_p, 2))
print()

# объединяем корзины с expected < 5
mask = expected_p >= 5
if not mask.all():
    # склеиваем все "мелкие" с предыдущей/последней
    # (в нашем случае при λ=2 почти всё >= 5)
    pass

chi2_pois = np.sum((observed_p - expected_p) ** 2 / expected_p)
df_pois = len(k_values_p) - 1
chi2_crit_pois = stats.chi2.ppf(1 - alpha, df_pois)

print(f"χ²-статистика:     {chi2_pois:.4f}")
print(f"Число степеней свободы: {df_pois}")
print(f"Критическое значение (α=0.05): {chi2_crit_pois:.4f}")
print(f"Результат: {'ОК (не отвергаем H0)' if chi2_pois < chi2_crit_pois else 'НЕ ОК (отвергаем H0)'}")
print()

# --- Проверка ошибки I рода ---
rejections_p = 0
for _ in range(n_reps):
    s = np.random.poisson(lam, n)
    obs = np.array([np.sum(s == k) for k in k_values_p])
    obs[-1] = np.sum(s >= max_k)
    chi2 = np.sum((obs - expected_p) ** 2 / expected_p)
    if chi2 >= chi2_crit_pois:
        rejections_p += 1
print(f"Проверка ошибки I рода ({n_reps} повторов):")
print(f"  Доля отвержений H0: {rejections_p / n_reps:.4f}  (должно быть ≈ {alpha})")
print()

# 3. СВОДНЫЙ ИТОГ
print("=" * 60)
print("СВОДКА")
print("=" * 60)
print(f"{'Распределение':<20}{'χ²':>10}{'χ²_крит':>12}{'Гипотеза':>15}")
print("-" * 60)
print(f"{'Bi(5, 0.6)':<20}{chi2_binom:>10.4f}{chi2_crit_binom:>12.4f}"
      f"{'принимаем' if chi2_binom < chi2_crit_binom else 'отвергаем':>15}")
print(f"{'П(2)':<20}{chi2_pois:>10.4f}{chi2_crit_pois:>12.4f}"
      f"{'принимаем' if chi2_pois < chi2_crit_pois else 'отвергаем':>15}")