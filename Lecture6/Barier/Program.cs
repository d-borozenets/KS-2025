using System;
using System.Threading;

class Program{
    static readonly Barrier barrier = new(3, b => { Console.WriteLine("=== Усі потоки завершили етап ==="); });

    static void DoWork(int id){
        Console.WriteLine($"Потік {id} виконує етап 1");
        Thread.Sleep(1000 + id * 200);
        barrier.SignalAndWait(); // чекає, поки всі дійдуть сюди

        Console.WriteLine($"Потік {id} виконує етап 2");
        Thread.Sleep(800 + id * 150);
        barrier.SignalAndWait(); // чекає знову
    }
    

    static void Main(){
        for (int i = 1; i <= 3; i++) {
            int localId = i;
            new Thread(() => DoWork(localId)).Start();
        }
    }
}