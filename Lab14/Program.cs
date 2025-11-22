// See https://aka.ms/new-console-template for more information

using System.Diagnostics;
using System.Runtime.Intrinsics;
using System.Runtime.Intrinsics.Arm;
using System.Runtime.Intrinsics.X86;

class Program{
    const int N = 4;
    private const int COLUMNS = 4096;
    private const int ROWS = 4096;

    private static readonly Random RANDOM = new();
    private static float[] image = null!;
    private static float[] filter = null!;
    private static float[] result = null!;

    static void Main(){
        image = Generate();
        filter = Generate();
        result = new float[image.Length];

        // ApplyFilterScalar();
        // ApplyFilterParallel();
        // ApplyFilterSimd();
    }

    private static void ApplyFilterSimd(){
    }

    private static unsafe void ApplySimdSse(){
        Stopwatch sw = Stopwatch.StartNew();
        fixed (float* imageAddr = image, filterAddr = filter, resultAddr = result) {
            
            
        }
        sw.Stop();
        Console.WriteLine($"Sse Time: {sw.ElapsedMilliseconds} ms");
    }

    private static unsafe void ApplySimdNeon(){
        Stopwatch sw = Stopwatch.StartNew();
        fixed (float* imageAddr = image, filterAddr = filter, resultAddr = result) {
            
            
        }
        sw.Stop();
        Console.WriteLine($"AdvSimd  Time: {sw.ElapsedMilliseconds} ms");
    }

    private static void ApplyFilterParallel(){
        Stopwatch sw = Stopwatch.StartNew();
        sw.Stop();
        Console.WriteLine($"Parallel.For Time: {sw.ElapsedMilliseconds} ms");
    }

    private static void ApplyFilterScalar(){
        Stopwatch sw = Stopwatch.StartNew();
        sw.Stop();
        Console.WriteLine($"Scalar Time: {sw.ElapsedMilliseconds} ms");
    }

    private static float[] Generate(){
        float[] floats = new float[ROWS * COLUMNS * N];
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLUMNS; j++) {
                for (int k = 0; k < N; k++) {
                    int pos = (i * COLUMNS + j) * N + k;
                    floats[pos] = RANDOM.NextSingle();
                }
            }
        }

        return floats;
    }
}