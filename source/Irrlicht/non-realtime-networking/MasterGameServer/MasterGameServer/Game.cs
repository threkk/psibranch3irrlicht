using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace MasterGameServer
{
    public class Game
    {

        // Game's name
        public string name { get; set; }
        // List of best scores
        public List<Score> highScores { get; set; }

        // Check in interval
        private int _checkInInterval = 3000;

        public int checkInInterval
        {
            get { return _checkInInterval; }
            set
            {
                if (value < 3)
                    _checkInInterval = 3;
                else
                    _checkInInterval = value;
            }
        }

        public void replaceScore(Score oldScore, Score newScore)
        {
            highScores.Remove(oldScore);
            highScores.Add(newScore);
        }

    }
}