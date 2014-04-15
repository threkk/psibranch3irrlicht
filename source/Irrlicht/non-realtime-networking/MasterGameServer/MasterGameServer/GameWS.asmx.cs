﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;

namespace MasterGameServer
{

    /// <summary>
    /// This Web Service acts as a master server for possibly many games.
    /// It has a dictionary that keeps track of all games played and also 
    /// records of all players (their IDs and IP addresses).
    /// </summary>
    
    [WebService(Namespace = "http://non-real-time-networking-web-service.psi")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    public class GameWS : System.Web.Services.WebService
    {
        /// <summary>
        /// Dictionary is an equivalent of Map that we see in C++ and Java.
        /// For each game its ID (a string) is kept together with 
        /// IDs and IP addreses of players playing it.
        /// </summary>
        static Dictionary<string, Dictionary<int, string>> games = new Dictionary<string, Dictionary<int,string>>();

        /// <summary>
        /// For each game a session counter is kept. It is used
        /// to generate session IDs for new players.
        /// </summary>
        static Dictionary<string, int> sessionCounters = new Dictionary<string, int>();

        /// <summary>
        /// Object used for locking the critical section
        /// </summary>   
        readonly object syncLock = new object();

        /// <summary>
        /// Returns a list of strings representing games registered on the server.
        /// </summary>
        [WebMethod]
        public List<string> getGamesPlayed()
        {
            return games.Keys.ToList();
        }

        /// <summary>
        /// Registers player on the server for a given game.
        /// If a game was not registered on the server before,
        /// a new dictionary is created to hold data of people
        /// playing it. The server saves player's IP address
        /// and generates a session ID for him.
        /// </summary>
        /// <param name="gameName">
        /// name of the game to be played by a player
        /// </param>
        [WebMethod]
        public int register(string gameName)
        {
            // Check if the parameter was provided
            if (String.IsNullOrEmpty(gameName))
                throw new Exception("Register: gameName cannot be empty!");

            /*
                Lock the critical section to prevent inconsistency
                and unexpected behaviour of the server.
            */
            lock (syncLock) // beginning of critical section
            {
                // If a game was not registered on the server:
                if (!games.Keys.ToList().Contains(gameName))
                {
                    games.Add(gameName, new Dictionary<int, string>()); // Initialize game's dictionary
                    sessionCounters.Add(gameName, 1); // Initialize the session counter for that game
                }

                // Put player's session ID and his IP address into the dictionary
                // sessions.Add(sessionCounter++, HttpContext.Current.Request.UserHostAddress);
                games[gameName].Add(sessionCounters[gameName]++, Context.Request.ServerVariables["REMOTE_ADDR"]);
            } // end of critical section
            
            // Return player's session ID
            return sessionCounters[gameName] - 1;
        }

        /// <summary>
        /// Returns the IP address of the opponent for a specific game.
        /// </summary>        
        [WebMethod]
        public string getOpponentsIpAddress(string gameName, int sessionId)
        {
            // Check if the parameter was provided
            if (String.IsNullOrEmpty(gameName))
                throw new Exception("GetOpponentsIpAddress: gameName cannot be empty!");

            // Check if provided session ID is even and is not equal to 0
            if (sessionId < 1 || (sessionId % 2) == 1)
                throw new Exception("GetOpponentsIpAddress: sessionId has to be a positive even integer number.");
            // Check if given game was registered on the server
            if (!games.Keys.ToList().Contains(gameName))
                throw new Exception("GetOpponentsIpAddress: game called " + gameName + " has not been registered on the server");

            // return the IP address of the opponent
            return games[gameName][sessionId - 1];
        }

        /// <summary>
        /// Returns a list of people playing given game (their IDs and IP addresses).
        /// This function is not used by the library itself,
        /// it's just used for debugging to see whether players
        /// register correctly for a given game.
        /// </summary>
        /// <param name="gameName">name of the game to retrieve players for</param>
        [WebMethod]
        public List<string> getGamePlayers(string gameName)
        {
            // Check if the parameter was provided
            if (String.IsNullOrEmpty(gameName))
                throw new Exception("GetGamePlayers: gameName cannot be empty!");

            // if such game was not registered on the server, return null
            if (!games.Keys.ToList().Contains(gameName))
                return null;

            // create a list of players for a given game
            List<string> players = new List<string>();
            // add player data one by one
            foreach(KeyValuePair<int, string> entry in games[gameName])
                players.Add("Session ID: " + entry.Key + ", IP: " + entry.Value);

            // return the list of players
            return players;
        }

    }

}