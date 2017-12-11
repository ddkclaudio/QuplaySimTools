using UnityEngine;
using System.Collections;
using System;
using System.Text;
using System.Net;
using System.Net.Sockets;

class Simtools
{
    public float Roll;
    public float Pitch;
    public float Yaw;
    public float Heave;
    public float Sway;
    public float Surge;
    public float Extra1;
    public float Extra2;
    public float Extra3;
    public Simtools() { }
    public Simtools(float Roll, float Pitch, float Yaw, float Heave, float Sway, float Surge, float Extra1, float Extra2, float Extra3)
    {
        this.Roll = Roll;
        this.Pitch = Pitch;
        this.Yaw = Yaw;
        this.Heave = Heave;
        this.Sway = Sway;
        this.Surge = Surge;
        this.Extra1 = Extra1;
        this.Extra2 = Extra2;
        this.Extra3 = Extra3;
    }
}

public class QuPlaySimtools : MonoBehaviour
{
    public string IP = "127.0.0.1";
    public int port = 4123;

    IPEndPoint remoteEndPoint;
    static UdpClient client;
    static Simtools simtools;

    void Start()
    {
        remoteEndPoint = new IPEndPoint(IPAddress.Parse(IP), port);
        client = new UdpClient();
        simtools = new Simtools();
        StartCoroutine("QuSimtools_Start");
    }

    public static void QuSimtools_SendTelemetry(float Roll, float Pitch, float Yaw, float Heave, float Sway, float Surge, float Extra1, float Extra2, float Extra3)
    {
        simtools = new Simtools(Roll, Pitch, Yaw, Heave, Sway, Surge, Extra1, Extra2, Extra3);
    }

    IEnumerator QuSimtools_Start()
    {
        while (true)
        {
            string info = String.Format("{0},{1},{2},{3},{4},{5},{6},{7},{8}", simtools.Roll, simtools.Pitch, simtools.Yaw, simtools.Heave, simtools.Sway, simtools.Surge, simtools.Extra1, simtools.Extra2, simtools.Extra3);
            byte[] data = Encoding.Default.GetBytes(info);
            client.Send(data, data.Length, remoteEndPoint);
            yield return null;
        }
    }
}