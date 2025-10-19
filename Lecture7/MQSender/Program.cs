using System;
using System.IO;
using System.IO.Pipes;
using System.Text;

class Server
{
    static void Main()
    {
        Console.OutputEncoding = Encoding.UTF8;
        Console.WriteLine("Server started.");

        using (var pipeServer = new NamedPipeServerStream("TestPipe", PipeDirection.Out))
        {
            Console.WriteLine("Waiting for client...");
            pipeServer.WaitForConnection();
            Console.WriteLine("Client connected.");

            using (var writer = new StreamWriter(pipeServer, Encoding.UTF8))
            {
                writer.AutoFlush = true;

                for (int i = 1; i <= 3; i++)
                {
                    string message = $"Message {i} from server";
                    writer.WriteLine(message);
                    Console.WriteLine($"Sent: {message}");
                }
            }
        }

        Console.WriteLine("Server finished.");
    }
}