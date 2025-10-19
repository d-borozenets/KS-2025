using System;
using System.IO;
using System.IO.Pipes;
using System.Text;

class PipeClient
{
    static void Main()
    {
        Console.WriteLine("Client: підключаюся до DemoPipe...");
        using (var pipeClient = new NamedPipeClientStream(".", "DemoPipe", PipeDirection.In))
        {
            pipeClient.Connect();
            Console.WriteLine("Підключено до сервера!");

            using (var reader = new StreamReader(pipeClient, Encoding.UTF8))
            {
                string message = reader.ReadLine();
                Console.WriteLine($"Отримано повідомлення: {message}");
            }
        }
        Console.WriteLine("👋 Клієнт завершує роботу.");
    }
}