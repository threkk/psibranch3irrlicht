using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MasterGameServer
{
    public class PlayRequestResult
    {

        // Session ID generated
        public int sessionId { get; set; }
        // Opponent's IP (if joining)
        public string opponentsIP { get; set; }
        // Hosting/joining
        public bool hosting { get; set; }
        // Player's login
        public string login { get; set; }
        // Error code (0 if no error)
        public int errorCode { get; set; }
        // Check in interval required by the game/server
        public int checkInInterval { get; set; }

    }
}