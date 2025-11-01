class Program
{
    static async Task Main(){
        await RunAwait();
        await RunContinue();
    }
    // static void Main(){
    //     ParallelFor();
    //     // Task t = RunContinue();
    //     // t.Wait();
    // }

    private static void ParallelFor(){
        Parallel.For(0, 10, i => {
            Console.WriteLine($"item {i}, thread: {Thread.CurrentThread.ManagedThreadId}");
        });
    }

    private static Task RunContinue(){
        return Task.Run(() => Console.WriteLine("Hello async"))
            .ContinueWith(t => Console.WriteLine("Продовження після завершення"));
    }

    private static async Task RunAwait(){
        await Task.Run(() => Console.WriteLine("Hello async"));
        Console.WriteLine("Продовження після завершення");
    }
}