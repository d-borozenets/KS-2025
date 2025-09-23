using System.Diagnostics;

class Program
{
    static void HeavyCalculations(int index)
    {

        double x = 6464.3232;

        const int count = 10000;

        for (int i = 0; i < count; i++)
        {
            for (int j = 0; j < count; j++)
            {
                x = Math.Pow(x, 2);
                x += 0.00000000001;
                x = Math.Sqrt(x);
            }
        }
        Console.WriteLine($"Complete[{index}] x = {x}");
    }

    static void Main()
    {
        Console.WriteLine($"Hello World");
    }
}
