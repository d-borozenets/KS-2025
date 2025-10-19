using System;
using System.IO;
using System.IO.Pipes;
using System.Text;

class PipeServer
{
    static void Main()
    {
        Console.WriteLine("Server: створюю іменований канал...");
        using (var pipeServer = new NamedPipeServerStream("DemoPipe", PipeDirection.Out))
        {
            Console.WriteLine("Очікую підключення клієнта...");
            pipeServer.WaitForConnection();

            Console.WriteLine("Клієнт підключився!");
            using (var writer = new StreamWriter(pipeServer, Encoding.UTF8))
            {
                writer.AutoFlush = true;
                writer.WriteLine("Hello from server 👋");
            }
            Console.WriteLine("Повідомлення відправлено. Завершення роботи сервера.");
        }
    }
}