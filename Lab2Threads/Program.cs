using System.Diagnostics;

class Program{
    static void HeavyCalculations(object? labelObj){
        string label = (string)(labelObj ?? "?");
        double x = 6464.3232;

        const int count = 1_000_000;//починаємо з невеликого значення

        for (int i = 0; i < count; i++) {
            x = Math.Pow(x, 2);
            x += 0.00000000001;
            x = Math.Sqrt(x);
        }

        Console.Write($"{label} -> ");
    }

    static void Main(){
        int cores = 0;
        Console.WriteLine($"CPU cores: {cores}");

        // N+1 блоків
        for (int i = 1; i <= cores + 1; i++) {
            // RunSequential(i);
        }
        // Console.ReadKey();
    }
}