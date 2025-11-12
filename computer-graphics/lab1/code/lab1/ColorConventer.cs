using System;

public class ColorConverter
{
    private const double Xref = 95.047;
    private const double Yref = 100.000;
    private const double Zref = 108.883;

    public static void RgbToHsv(int r, int g, int b, out double h, out double s, out double v)
    {
        double red = r / 255.0;
        double green = g / 255.0;
        double blue = b / 255.0;

        double max = Math.Max(red, Math.Max(green, blue));
        double min = Math.Min(red, Math.Min(green, blue));
        double delta = max - min;

        // Hue
        if (delta == 0)
            h = 0;
        else if (max == red)
            h = 60 * (((green - blue) / delta) % 6);
        else if (max == green)
            h = 60 * (((blue - red) / delta) + 2);
        else
            h = 60 * (((red - green) / delta) + 4);

        if (h < 0) h += 360;

        // Округляем и ограничиваем Hue
        h = Math.Round(h, 2);
        if (h >= 360) h = 0;

        // Sat
        s = (max == 0) ? 0 : (delta / max);
        s = Math.Round(s, 4);
        s = Math.Max(0, Math.Min(1, s));

        // Value
        v = max;
        v = Math.Round(v, 4);
        v = Math.Max(0, Math.Min(1, v));
    }

    public static void HsvToRgb(double h, double s, double v, out int r, out int g, out int b)
    {
        h = h % 360;
        if (h < 0) h += 360;
        s = Math.Max(0, Math.Min(1, s));
        v = Math.Max(0, Math.Min(1, v));

        double c = v * s;
        double x = c * (1 - Math.Abs((h / 60) % 2 - 1));
        double m = v - c;

        double red = 0, green = 0, blue = 0;

        if (h >= 0 && h < 60)
        {
            red = c; green = x; blue = 0;
        }
        else if (h >= 60 && h < 120)
        {
            red = x; green = c; blue = 0;
        }
        else if (h >= 120 && h < 180)
        {
            red = 0; green = c; blue = x;
        }
        else if (h >= 180 && h < 240)
        {
            red = 0; green = x; blue = c;
        }
        else if (h >= 240 && h < 300)
        {
            red = x; green = 0; blue = c;
        }
        else if (h >= 300 && h < 360)
        {
            red = c; green = 0; blue = x;
        }

        r = (int)Math.Round((red + m) * 255);
        g = (int)Math.Round((green + m) * 255);
        b = (int)Math.Round((blue + m) * 255);

        r = Math.Max(0, Math.Min(255, r));
        g = Math.Max(0, Math.Min(255, g));
        b = Math.Max(0, Math.Min(255, b));
    }

    public static void RgbToLab(int r, int g, int b, out double l, out double a, out double b_out)
    {
        double red = r / 255.0;
        double green = g / 255.0;
        double blue = b / 255.0;

        red = (red > 0.04045) ? Math.Pow((red + 0.055) / 1.055, 2.4) : red / 12.92;
        green = (green > 0.04045) ? Math.Pow((green + 0.055) / 1.055, 2.4) : green / 12.92;
        blue = (blue > 0.04045) ? Math.Pow((blue + 0.055) / 1.055, 2.4) : blue / 12.92;

        double x = red * 0.4124564 + green * 0.3575761 + blue * 0.1804375;
        double y = red * 0.2126729 + green * 0.7151522 + blue * 0.0721750;
        double z = red * 0.0193339 + green * 0.1191920 + blue * 0.9503041;

        x *= 100;
        y *= 100;
        z *= 100;

        x /= Xref;
        y /= Yref;
        z /= Zref;

        x = (x > 0.008856) ? Math.Pow(x, 1.0 / 3.0) : (7.787 * x) + (16.0 / 116.0);
        y = (y > 0.008856) ? Math.Pow(y, 1.0 / 3.0) : (7.787 * y) + (16.0 / 116.0);
        z = (z > 0.008856) ? Math.Pow(z, 1.0 / 3.0) : (7.787 * z) + (16.0 / 116.0);

        l = Math.Round((116.0 * y) - 16, 2);
        a = Math.Round(500 * (x - y), 2);
        b_out = Math.Round(200 * (y - z), 2);
    }

    public static void LabToRgb(double l, double a, double b_val, out int r, out int g, out int b)
    {
        try
        {
            double y3 = (l + 16) / 116.0;
            double x3 = a / 500.0 + y3;
            double z3 = y3 - b_val / 200.0;

            x3 = double.IsNaN(x3) ? 0 : x3;
            y3 = double.IsNaN(y3) ? 0 : y3;
            z3 = double.IsNaN(z3) ? 0 : z3;

            x3 = (Math.Pow(x3, 3) > 0.008856) ? Math.Pow(x3, 3) : (x3 - 16.0 / 116.0) / 7.787;
            y3 = (Math.Pow(y3, 3) > 0.008856) ? Math.Pow(y3, 3) : (y3 - 16.0 / 116.0) / 7.787;
            z3 = (Math.Pow(z3, 3) > 0.008856) ? Math.Pow(z3, 3) : (z3 - 16.0 / 116.0) / 7.787;

            double x = x3 * Xref;
            double y = y3 * Yref;
            double z = z3 * Zref;

            x /= 100;
            y /= 100;
            z /= 100;

            double red = x * 3.2404542 + y * -1.5371385 + z * -0.4985314;
            double green = x * -0.9692660 + y * 1.8760108 + z * 0.0415560;
            double blue = x * 0.0556434 + y * -0.2040259 + z * 1.0572252;

            red = (red > 0.0031308) ? 1.055 * Math.Pow(red, 1 / 2.4) - 0.055 : 12.92 * red;
            green = (green > 0.0031308) ? 1.055 * Math.Pow(green, 1 / 2.4) - 0.055 : 12.92 * green;
            blue = (blue > 0.0031308) ? 1.055 * Math.Pow(blue, 1 / 2.4) - 0.055 : 12.92 * blue;

            r = (int)Math.Round(red * 255);
            g = (int)Math.Round(green * 255);
            b = (int)Math.Round(blue * 255);

            r = Math.Max(0, Math.Min(255, r));
            g = Math.Max(0, Math.Min(255, g));
            b = Math.Max(0, Math.Min(255, b));
        }
        catch
        {
            r = g = b = 0;
        }
    }
}