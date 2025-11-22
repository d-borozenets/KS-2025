using System.Net;
using System.Net.Sockets;
using System.Text;

class Server{
    static void Main(){
        StartServer();
    }

    private static void StartServer(){
        const int port = 5000;
    }

    private static void HandleClient(int id, TcpClient client){


        while (true) {
            try {
                
            }
            catch (IOException) {
                // Клієнт розірвав з’єднання — нормально, просто виходимо
                break;
            }
            catch (SocketException) {
                // Також нормальна ситуація — клієнт завершив роботу
                break;
            }
            catch (ObjectDisposedException) {
                // Потік вже закритий
                break;
            }
        }

        client.Close();
        Console.WriteLine($"Client [{id}] disconnected.");
    }
}