using System;
using System.IO;
using System.IO.Pipes;
using System.Text;

class Client
{
    static void Main()
    {
        Console.OutputEncoding = Encoding.UTF8;
        Console.WriteLine("Client started.");

        using (var pipeClient = new NamedPipeClientStream(".", "TestPipe", PipeDirection.In))
        {
            Console.WriteLine("Connecting to server...");
            pipeClient.Connect();
            Console.WriteLine("Connected.");

            using (var reader = new StreamReader(pipeClient, Encoding.UTF8))
            {
                string? line;
                while ((line = reader.ReadLine()) != null)
                {
                    Console.WriteLine($"Received: {line}");
                }
            }
        }

        Console.WriteLine("Client finished.");
    }
}