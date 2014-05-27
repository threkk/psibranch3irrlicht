using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MasterGameServer
{
    public class Player
    {

        public int sessionId { get; set; }
        public bool waiting { get; set; }
        public string ipAddress { get; set; }
        public string login { get; set; }

    }
}