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
            For each game its ID (a string) is kept together with 
            IDs and IP addreses of players playing it.
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
            if (String.IsNullOrEmpty(gameName))
                throw new Exception("Register: gameName cannot be empty!");

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
            if (String.IsNullOrEmpty(gameName))
                throw new Exception("GetOpponentsIpAddress: gameName cannot be empty!");

            /// Check if the ID is potentially correct
            if (sessionId < 1 || (sessionId % 2) == 1)
                throw new Exception("GetOpponentsIpAddress: sessionId has to be a positive even integer number.");

            if (!games.Keys.ToList().Contains(gameName))
                throw new Exception("GetOpponentsIpAddress: game called " + gameName + " has not been registered on the server");

            return games[gameName][sessionId - 1];
        }

        [WebMethod]
        public List<string> getGamePlayers(string gameName)
        {
            if (String.IsNullOrEmpty(gameName))
                throw new Exception("GetGamePlayers: gameName cannot be empty!");

            if (!games.Keys.ToList().Contains(gameName))
                return null;

            List<string> players = new List<string>();
            foreach(KeyValuePair<int, string> entry in games[gameName])
                players.Add("Session ID: " + entry.Key + ", IP: " + entry.Value);

            return players;
        }

    }

}