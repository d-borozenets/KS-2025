using System.Collections.Concurrent;
using System.Diagnostics;

static class Program{
    const int N = 300_000_000;
    const int M = (int)(0.0002 * N);


    static void Main(string[] args){
        double[] a, b;
        
        if (args.Length == 0) {
            a = InitializeArray(N);
            // RunSequential(a);
            // RunParallelFor(a);
            // RunParallelForWithOption(a, 2);
            // RunParallelForWithOption(a, 4);
            // RunParallelForWithOption(a, 8);
            // RunParallelForWithOption(a, -1);

            // b = InitializeArray(M);
            // RunParallelForWithOptionWithLoad(b, -1, true);
            // RunParallelForWithOptionWithLoad(b, -1, false);
            return;
        } 
        string mode = args[0];

        switch (mode)
        {
            case "test=seq":
                a = InitializeArray(N);
                RunSequential(a);
                break;
            case "test=par":
                a = InitializeArray(N);
                RunParallelFor(a);
                break;
            case "test=par2":
                a = InitializeArray(N);
                RunParallelForWithOption(a, 2);
                break;
            case "test=par4":
                a = InitializeArray(N);
                RunParallelForWithOption(a, 4);
                break;
            case "test=par8":
                a = InitializeArray(N);
                RunParallelForWithOption(a, 8);
                break;
            case "test=par-1":
                a = InitializeArray(N);
                RunParallelForWithOption(a, -1);
                break;
            case "test=loadTrue":
                b = InitializeArray(M);
                RunParallelForWithOptionWithLoad(b, -1, true);
                break;
            case "test=loadFalse":
                b = InitializeArray(M);
                RunParallelForWithOptionWithLoad(b, -1, false);
                break;
            default:
                Console.WriteLine($"Unknown test argument: {mode}");
                break;
        }
    }


    static void RunSequential(double[] a){
    }

    static void RunParallelFor(double[] a){
    }

    static void RunParallelForWithOption(double[] a, int maxDegree){
    }


    static void RunParallelForWithOptionWithLoad(double[] a, int maxDegree, bool averageLoad){
    }

    private static double[] InitializeArray(int count){
        double[] result = new double[count];
        double rnd = (new Random()).NextDouble();

        for (int i = 0; i < count; i++) {
            result[i] = rnd;
        }

        return result;
    }

    private static double CalcResultItem(double[] a, int i){
        return Math.Sqrt(a[i]) + Math.Sin(a[i]);
    }
}