using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MasterGameServer
{
    public class Player
    {

        // Player's session ID:
        public int sessionId { get; set; }

        // Player's login:
        public string login { get; set; }

        // Player's IP address:
        public string ipAddress { get; set; }

        // When the player joined 
        public DateTime joined { get; set; }
        
        // Last time the player checked in
        public DateTime lastCheckedIn { get; set; }

        // Waiting for somebody to join
        public bool waiting { get; set; }

        // The game player is playing
        public Game game { get; set; }

        public bool isActive(int checkInterval) {
            if (lastCheckedIn.Add(new TimeSpan(0, 0, checkInterval + 1)) < DateTime.Now)
                return false;
            else
                return true;
        }

    }
}