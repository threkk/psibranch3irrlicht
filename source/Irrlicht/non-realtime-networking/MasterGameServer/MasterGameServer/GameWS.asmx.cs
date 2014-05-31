using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;
using System.Runtime.CompilerServices;

namespace MasterGameServer
{

    /// <summary>
    /// This Web Service acts as a master server for possibly many games.
    /// It keeps track of all games played and all registered players.
    /// </summary>
    
    [WebService(Namespace = "http://non-real-time-networking-web-service.psi")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    public class GameWS : System.Web.Services.WebService
    {
        
        // CONSTANTS:

        // Maximum number of high scores stored for each game
        const int MAX_SCORES_PER_GAME = 15;

        // ERROR CODES:
        const int SCORE_TOO_SMALL = -5;
        const int NO_SUCH_PLAYER = -4;
        const int GAME_NAME_EMPTY = -3;
        const int LOGIN_TAKEN = -2;
        const int NO_SUCH_GAME = -1;

        /// <summary>
        /// List of games registered on the server.
        /// </summary>
        static List<Game> games = new List<Game>();

        /// <summary>
        /// List of players registered on the server.
        /// </summary>
        static List<Player> players = new List<Player>();

        /// <summary>
        /// Session counter. It is used to assign
        /// session IDs for newly registered players.
        /// </summary>
        static int sessionCounter = 1;

        /// <summary>
        /// Object used for locking the critical section
        /// </summary>   
        static readonly object syncLock = new object();

        // Public methods:

        /// <summary>
        /// Registers player on the server for a given game.
        /// If a game was not registered on the server before,
        /// its instance is created. For every player his object
        /// is created and relevant data is stored. This function
        /// is also responsible for putting players into pairs.
        /// </summary>
        /// <param name="gameName">
        /// name of the game to be played by a player
        /// </param>
        /// <param name="login">
        /// player's desired login (optional)
        /// </param>
        /// <returns>
        /// Structure containing the following information:
        ///     sessionId - session ID assigned by the server
        ///     opponentsIP - IP address of the opponent (if hosting == false)
        ///     hosting - determines whether the player will be hosting or joining a game
        ///     login - player's login
        ///     errorCode - error code, 0 if everything went fine
        /// </returns>
        [WebMethod]
        public PlayRequestResult register(string gameName, string login)
        {
            
            // Check parameters
            if (String.IsNullOrEmpty(gameName))
                return new PlayRequestResult
                {
                    errorCode = GAME_NAME_EMPTY
                };

            PlayRequestResult playRequestResult = null;

            /*
                Lock the critical section to prevent inconsistency
                and unexpected behaviour of the server.
            */
            lock (syncLock) // beginning of critical section
            {               
            
            Game game = games.FirstOrDefault(g => g.name == gameName);

                if (!loginAvailible(game, login))
                    return new PlayRequestResult
                    {
                        errorCode = LOGIN_TAKEN
                    };
                            
                // If a game was not registered on the server:
                if (game == null)
                {
                    game = new Game { // Create new game
                        name = gameName,
                        highScores = new List<Score>()
                    };
                }

                int sesId = sessionCounter++;

                // Save player:
                Player player = new Player()
                {
                    sessionId = sesId,
                    login = (String.IsNullOrEmpty(login) ? "Player" + sesId.ToString() : login),
                    ipAddress = Context.Request.ServerVariables["REMOTE_ADDR"]
                };

                player.game = game;

                playRequestResult = getPlayRequestResult(player);                

                DateTime now = DateTime.Now;
                player.joined = player.lastCheckedIn = now;

                // This still needs to be locked as it's not thread safe
                players.Add(player);
                games.Add(player.game); // Initialize game's list

            } // end of critical section

            return playRequestResult;

        }

        /// <summary>
        /// Function decides whether the returning player will host or
        /// join a game.
        /// </summary>
        /// <param name="sessionId">session ID of an already registered player</param>
        /// <returns>
        /// Structure containing the following information:
        ///     opponentsIP - IP address of the opponent (if hosting == false)
        ///     hosting - determines whether the player will be hosting or joining a game
        ///     errorCode - error code, 0 if everything went fine
        /// </returns>
        [WebMethod]
        public PlayRequestResult play(int sessionId)
        {
            Player player = players.FirstOrDefault(p => p.sessionId == sessionId);

            if (player == null)
                return new PlayRequestResult
                {
                    errorCode = NO_SUCH_PLAYER
                };

            player.ipAddress = Context.Request.ServerVariables["REMOTE_ADDR"];
            player.lastCheckedIn = DateTime.Now;

            PlayRequestResult playRequestResult = getPlayRequestResult(player);

            return playRequestResult;

        }

        /// <summary>
        /// Returns a list of players registered on the server.
        /// </summary>
        [WebMethod]
        public List<Player> getPlayers()
        {
            return players;
        }

        /// <summary>
        /// Returns a list of games registered on the server.
        /// </summary>
        [WebMethod]
        public List<Game> getGamesPlayed()
        {
            return games;
        }

        /// <summary>
        /// Removes a player from the server. His high scores (if any)
        /// are kept, though.
        /// </summary>
        /// <param name="sessionId">session ID of a player to be removed</param>
        /// <returns>0 on success, error code otherwise</returns>
        [WebMethod]
        public int removePlayer(int sessionId)
        {

            Player playerToRemove = players.FirstOrDefault(p => p.sessionId == sessionId);
            if (playerToRemove != null)
            {
                players.Remove(playerToRemove);
                return 0;
            }
            else
                return NO_SUCH_PLAYER;

        }

        /// <summary>
        /// Used to update player's lastCheckedIn attribute,
        /// which is later used to determine whether he/she
        /// is still active.
        /// </summary>
        /// <param name="sessionId">session ID of a player</param>
        /// <returns>0 on success, error code otherwise</returns>
        [WebMethod]
        public int checkIn(int sessionId)
        {

            Player player = players.FirstOrDefault(p => p.sessionId == sessionId);
            if (player == null)
                return NO_SUCH_PLAYER;

            player.lastCheckedIn = DateTime.Now;

            return 0;

        }

        /// <summary>
        /// Saves player's score on the server.
        /// </summary>
        /// <param name="sessionId">session ID of a calling player</param>
        /// <param name="score">Score to be saved</param>
        /// <returns>0 on success, error code otherwise</returns>
        [WebMethod]
        public int addScore(int sessionId, float score)
        {

            Player player = players.FirstOrDefault(p => p.sessionId == sessionId);
            if (player == null)
                return NO_SUCH_PLAYER;

            Game game = player.game;
            Score newScore = new Score
            {
                score = score,
                playerLogin = player.login
            };

            if (game.highScores.Count == MAX_SCORES_PER_GAME)
            {
                Score minScore = game.highScores.OrderBy(s => s.score).FirstOrDefault();
                if (minScore.score < newScore.score)
                    game.replaceScore(minScore, newScore);
                else
                    return SCORE_TOO_SMALL;
            }
            else
            {
                game.highScores.Add(newScore);
            }

            return 0;
            
        }

        /// <summary>
        /// Returns a list of high scores for a given game.
        /// </summary>
        /// <param name="gameName">Name of the game for which to retrieve scores.</param>
        /// <param name="limit">Optional list size limit</param>
        [WebMethod]
        public List<Score> getScoreList(string gameName, int limit)
        {

            Game game = games.FirstOrDefault(g => g.name == gameName);
            if (game == null)
                return null;

            return game.highScores.OrderByDescending(s => s.score).Take(limit).ToList();

        }

        /*
         * The method is synchronized as only one thread (one player)
         * can access it at a time.
        */
        [MethodImpl(MethodImplOptions.Synchronized)]
        private PlayRequestResult getPlayRequestResult(Player player)
        {

            // Create new object
            PlayRequestResult playRequestResult = new PlayRequestResult();

            // Find the opponent:
            Player opponent = players.FirstOrDefault(p => p.waiting == true && p.game == player.game);

            if (opponent == null) // Nobody's waiting for an opponent
            {
                playRequestResult.hosting = true; // Calling player will host a game
                player.waiting = true; // Calling player will wait for somebody to join him
            }
            else // Opponent found
            {
                if (opponent.isActive(player.game.checkInInterval)) // Opponent active
                {
                    playRequestResult.opponentsIP = opponent.ipAddress; // Assign opponent's IP address
                    opponent.waiting = false; // Opponent is not waiting anymore
                    player.waiting = false; // Player is not waiting
                }
                else // Player will host
                {
                    playRequestResult.hosting = true; // Calling player will host a game
                    opponent.waiting = false; // Opponent is not waiting
                    player.waiting = true; // Calling player will wait for somebody to join him
                }

            }

            playRequestResult.sessionId = player.sessionId; // Assign player's generated session ID
            playRequestResult.login = player.login; // Assign player's login

            return playRequestResult; // Return resulting structure

        }

        /*
         * Function checks whether somebody with the same login
         * is not already playing given game.
        */
        private bool loginAvailible(Game game, string login)
        {
            if (game == null) // Such game does not exist, exit
                return true;
            return players.FirstOrDefault(p => p.login == login && p.game == game) == null; // return boolean value
        }

    }

}