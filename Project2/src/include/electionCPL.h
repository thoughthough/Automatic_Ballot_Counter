/**
 * @file electionCPL.h
 * @brief ElectionCPL class handles Closed Party List (CPL) election
 *
 * Responsible for reading in election data from a file in the same directory as src,
 * reads election data from file, processes ballots, determines winners,
 * and outputs results. Extends Election class.
 *
 * @author Zaid Nolley
 */
#ifndef ELECTION_CPL_H_
#define ELECTION_CPL_H_

#include "election.h"

/**
 * @brief ElectionCPL class handles Closed Party List (CPL) election.
 * 
 * Responsible for reading in election data from a file in the same directory as src,
 * reads election data from file, processes ballots, determines winners,
 * and outputs results. Extends Election class.
 */
class ElectionCPL : public Election {
    public:
        /**
         * @brief Constructs ElectionCPL object with a user declared file name.
         * 
         * @param files The name of the files containing election data.
         */
        ElectionCPL(vector<string> files);

        /**
         * @brief Gets the total number of ballots.
         * 
         * @return Total number of ballots.
         */
        int getTotalBallots();

        /**
         * @brief Gets the number of seats available.
         * 
         * @return The number of seats.
         */
        int getTotalSeats();

        /**
         * @brief Reads the header information from the election file.
         * 
         * Includes the number of seats, number of ballots,
         * and number of candidates.
         *  It then organizes candidates
         */
        void readHeader();

        /**
         * @brief Reads and processes all ballots
         * 
         * This method goes through each ballot, counting votes for candidates
         */
        void readBallots();

        /**
         * @brief Determines the winners.
         * 
         * This calculates the number of seats won by candidate
         */
        void determineWinners();

        /**
         * @brief Outputs the results to the screen.
         * 
         * Displays election results, party names, candidate names,
         * and winners.
         */
        void outputScreen();

        /**
         * @brief Outputs the results to a file named 'audit.txt'.
         * 
         * Like 'outputScreen', but directs to a file.
         */
        void outputFile();


    private:
        PartyMap partymap; ///< Manages party and candidate
        int seatsAvailable; ///< Number of seats available
        int totalBallots; ///< Number of ballots cast
        vector<string> files; // Name of files with election data
        vector<vector<string>> winnerInfo; ///< Winners information
        vector<tuple<string, string, int>> winnerCandidates; ///< Winners
        vector<tuple<int, int>> partyRange; ///< Range of candidates for each party

};

#endif
