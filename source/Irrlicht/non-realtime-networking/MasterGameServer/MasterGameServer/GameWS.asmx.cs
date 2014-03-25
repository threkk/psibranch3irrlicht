using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;

namespace MasterGameServer
{

    /**
        This Web Service acts as a master server for possibly many games.
        It has a dictionary that keeps track of all games played and also 
        records of all players (their Ids and IP addresses).
    */

    [WebService(Namespace = "http://non-real-time-networking-web-service.psi")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    public class GameWS : System.Web.Services.WebService
    {
        /**
            Dictionary is an equivalent of Map that we see in C++ and Java.
            For each game it's ID (a string) is kept together with 
            ID's and IP addreses of players playing it.
        */
        static Dictionary<string, Dictionary<int, string>> games = new Dictionary<string,Dictionary<int,string>>();

        /// sessionCounter counts players that play a certain game and is used to generate player's IDs.
        static Dictionary<string, int> sessionCounters = new Dictionary<string,int>();

        /// Object used for locking the critical section
        readonly object syncLock = new object();

        /// Returns a list of strings representing games played
        [WebMethod]
        public List<string> getGamesPlayed()
        {
            return games.Keys.ToList();
        }

        /**
            Registers player on the WS for a given game.
            There is a lock on the critical section to prevent
            two players from accessing and modifying the same
            attributes at the same time - that may lead to severe
            inconsistency on the server.
        */
        [WebMethod]
        public int register(string gameName)
        {
            lock (syncLock) // beginning of critical section
            {
                if (!games.Keys.ToList().Contains(gameName))
                {
                    games.Add(gameName, new Dictionary<int, string>()); // Initialize game's dictionary
                    sessionCounters.Add(gameName, 1); // Initialize session counter for that game
                }

                /// Put player's ID and his IP address into the dictionary
                // sessions.Add(sessionCounter++, HttpContext.Current.Request.UserHostAddress);
                games[gameName].Add(sessionCounters[gameName]++, Context.Request.ServerVariables["REMOTE_ADDR"]);
            } // end of critical section
            
            // Return player's ID
            return sessionCounters[gameName] - 1;
        }

        /// Returns IP address of the opponent for a specific game
        [WebMethod]
        public string getOpponentsIpAddress(string gameName, int sessionId)
        {
            /// Check if the ID is potentially correct
            if (sessionId < 1)
                throw new Exception("sessionId has to be a positive integer number.");

            /// Check if a player with such ID was registered for that game with his IP address
            if (!(games[gameName][sessionId] == Context.Request.ServerVariables["REMOTE_ADDR"]))
                throw new Exception("You have to register for that game first if you want to play it.");

            return games[gameName][sessionId];
        }

    }

}