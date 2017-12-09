using UnityEngine;
using System.Collections;
using System;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.IO;

public class UDPSend : MonoBehaviour
{
    public string IP = "127.0.0.1";
    public int port = 4123;

    IPEndPoint remoteEndPoint;
    UdpClient client;


    void Start()
    {
        remoteEndPoint = new IPEndPoint(IPAddress.Parse(IP), port);
        client = new UdpClient();
        StartCoroutine("Fade");
    }

    IEnumerator Fade()
    {
        string debug_file = Path.Combine(System.Environment.GetFolderPath(System.Environment.SpecialFolder.MyDocuments), "debug_file.txt");
        print(debug_file);

        while (true)
        {
            string info = UnityEngine.Random.Range(-180.0f, 180.0f) + ":PosX";
            byte[] data = Encoding.Default.GetBytes(info);
            client.Send(data, data.Length, remoteEndPoint);
            File.AppendAllText(debug_file,
                   info + Environment.NewLine);
            yield return null;
        }
    }






}