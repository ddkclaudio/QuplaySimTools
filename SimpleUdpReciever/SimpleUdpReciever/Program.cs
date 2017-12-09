using System;
using System.Collections.Generic;
using System.Text;
using System.Net.Sockets;
using System.Net;

namespace SimpleUdpReciever
{
    /// <summary>
    /// Simple implementation of the Udp Reciever 
    /// Autor: Claudio Silva - DDK
    /// Blog: https://clclaudio.wordpress.com
    /// </summary>
    class Program
    {
        static void Main(string[] args)
        {
            string ip = "127.0.0.1";
            int port = 4123;
            string name_space = typeof(Program).Namespace;

            try {
                IPEndPoint remoteSender = new IPEndPoint(IPAddress.Parse(ip), port);

                // Create UDP client
                UdpClient client = new UdpClient(port);
                UdpState state = new UdpState(client, remoteSender);

                // Start async receiving
                client.BeginReceive(new AsyncCallback(DataReceived), state);

                // Wait for any key to terminate application

                Console.Write(name_space + ": Waiting for packages\n");
                Console.ReadKey();
                client.Close();
                Console.Write(name_space + ": Finalized\n");
            }
            catch (Exception e) {
                Console.Write(name_space + ": ERROR : " + e);
            }
        }

        private static void DataReceived(IAsyncResult ar)
        {
            UdpClient c = (UdpClient)((UdpState)ar.AsyncState).c;
            IPEndPoint wantedIpEndPoint = (IPEndPoint)((UdpState)(ar.AsyncState)).e;
            IPEndPoint receivedIpEndPoint = new IPEndPoint(IPAddress.Any, 0);
            Byte[] receiveBytes = c.EndReceive(ar, ref receivedIpEndPoint);

            // Convert data to ASCII and print in console
            string receivedText = ASCIIEncoding.ASCII.GetString(receiveBytes);
            Console.Write(receivedText + "\n");

            // Restart listening for udp data packages
            c.BeginReceive(new AsyncCallback(DataReceived), ar.AsyncState);
        }
    }
}
