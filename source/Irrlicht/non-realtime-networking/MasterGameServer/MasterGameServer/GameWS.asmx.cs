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
        /*
            Dictionary is an equivalent of Map that we see in C++ and Java.
            For each game it's ID (a string) is kept together with 
            ID's and IP addreses of players playing it.
        */
        static Dictionary<string, Dictionary<int, string>> games = new Dictionary<string,Dictionary<int,string>>();

        /// sessionCounter counts players that play a certain game and is used to generate player's IDs.
        static Dictionary<string, int> sessionCounters = new Dictionary<string,int>();

        [WebMethod]
        public List<string> getGamesPlayed()
        {
            return games.Keys.ToList();
        }

        [WebMethod]
        /// Register player on the WS
        public int register(string gameName)
        {
            if (!games.Keys.ToList().Contains(gameName))
            {
                games.Add(gameName, new Dictionary<int, string>());
                sessionCounters.Add(gameName, 1);
            }

            /// Put player's ID and his IP address into the dictionary
            // sessions.Add(sessionCounter++, HttpContext.Current.Request.UserHostAddress);
            games[gameName].Add(sessionCounters[gameName]++, Context.Request.ServerVariables["REMOTE_ADDR"]);            
            
            // Return player's ID
            return sessionCounters[gameName] - 1;
        }

        // Returns IP address of the opponent
        [WebMethod]
        public string getOpponentsIpAddress(string gameName, int sessionId)
        {
            if (sessionId < 1)
                throw new Exception("sessionId has to be a positive integer number.");
            return games[gameName][sessionId];
        }

    }

}