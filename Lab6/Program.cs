using System.Diagnostics;

static class Program{
    const int N = 10_000_000;


    static void Main(string[] args){
        double[] a;

        if (args.Length == 0) {
            a = InitializeArray(N);
            // CalculateSumSeq(a);
            // CalculateSumWith3Tasks(a);
            CalculateSumWithThreadPool(a);
            // HelloFrom3Tasks();
            return;
        }

        string mode = args[0];

        switch (mode) {
            case "test=hello":
                break;
            case "test=seq":
                a = InitializeArray(N);
                CalculateSumSeq(a);
                break;
            case "test=tasks":
                a = InitializeArray(N);
                CalculateSumWith3Tasks(a);
                break;
            case "test=pool":
                a = InitializeArray(N);
                CalculateSumWithThreadPool(a);
                break;
            default:
                Console.WriteLine($"Unknown test argument: {mode}");
                break;
        }
    }

    private static void CalculateSumSeq(double[] doubles){
    }


    private static void CalculateSumWith3Tasks(double[] a){
    }

    private static void CalculateSumWithThreadPool(double[] a){
    }

    private static void HelloFrom3Tasks(){
    }

    private static double[] InitializeArray(int count){
        return null;
    }

    private static double SumOfRange(double[] a, int start, int end){
        return 0;
    }
}