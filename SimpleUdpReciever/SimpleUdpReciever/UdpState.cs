using System;
using System.Collections.Generic;
using System.Text;
using System.Net.Sockets;
using System.Net;

namespace SimpleUdpReciever
{
    /// <summary>
    /// Simple implementation of the UdpState class mentioned on 
    /// http://msdn.microsoft.com/en-us/library/c8s04db1(v=VS.80).aspx
    /// </summary>
    internal class UdpState
    {
        internal UdpState(UdpClient c, IPEndPoint e)
        {
            this.c = c;
            this.e = e;
        }

        internal UdpClient c;
        internal IPEndPoint e;
    }
}
