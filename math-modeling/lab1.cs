using System;
using System.Linq;

class Lab1
{
    const ulong M = 2147783648;
    const ulong beta = 50653;
    const int N = 1000;
    const int K = 64;

    static double[] GenerateMKV(ulong seed, ulong beta, int count)
    {
        var result = new double[count];
        ulong x = seed;
        for (int i = 0; i < count; i++)
        {
            x = (beta * x) % M;
            result[i] = (double)x / M;
        }
        return result;
    }

    // beta: последовательность-источник (длина >= N + K)
    // c:    последовательность-указатель (длина >= N)
    static double[] GenerateMMM(double[] beta, double[] c, int n, int k)
    {
        var V = new double[k];
        Array.Copy(beta, V, k);

        var result = new double[n];
        for (int i = 0; i < n; i++)
        {
            int s = (int)(c[i] * k);
            if (s >= k) s = k - 1;
            result[i] = V[s];
            V[s] = beta[k + i];
        }
        return result;
    }

    static double Kolmogorov(double[] a)
    {
        var sorted = (double[])a.Clone();
        Array.Sort(sorted);

        int n = sorted.Length;
        double D = 0;
        for (int i = 0; i < n; i++)
        {
            double deviation = Math.Abs((i + 1.0) / n - sorted[i]);
            if (deviation > D) D = deviation;
        }

        double stat = Math.Sqrt(n) * D;
        Console.WriteLine($"Колмогоров: sqrt(n)*D = {stat:F3}, порог 1.358 -> " +
                          (stat < 1.358 ? "ОК" : "НЕ ОК"));
        return stat;
    }

    static double Pirson(double[] a, int m)
    {
        int n = a.Length;
        var counts = new int[m];

        foreach (double x in a)
        {
            int bucket = (int)(x * m);
            if (bucket >= m) bucket = m - 1;
            counts[bucket]++;
        }

        double expected = (double)n / m;
        double xi2 = 0;
        for (int j = 0; j < m; j++)
        {
            double diff = counts[j] - expected;
            xi2 += diff * diff / expected;
        }

        Console.WriteLine($"Пирсон: xi^2 = {xi2:F3}, порог 16.92 -> " +
                          (xi2 < 16.92 ? "ОК" : "НЕ ОК"));
        return xi2;
    }

    static void Main()
    {
        Console.OutputEncoding = System.Text.Encoding.UTF8;

        Console.WriteLine("=== Мультипликативный конгруэнтный метод ===");
        double[] b = GenerateMKV(beta, beta, N);
        Kolmogorov(b);
        Pirson(b, 10);
        Console.WriteLine();

        //     beta' = 3*beta + 1, длина N + K = 1100
        Console.WriteLine("=== Метод Маклорена-Марсальи ===");
        ulong beta2 = 3 * beta + 1;
        double[] betaSeq = GenerateMKV(beta2, beta2, N + K); // источник
        double[] cSeq = GenerateMKV(beta, beta, N);   // указатели

        double[] a = GenerateMMM(betaSeq, cSeq, N, K);
        Kolmogorov(a);
        Pirson(a, 10);
    }
}