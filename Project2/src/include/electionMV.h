/**
 * @file electionMV.h
 * @brief ElectionMV class handles municipal voting (MV) elections.
 *
 * Responsible for reading in election data from a file in the same directory as src,
 * reads election data from file, processes ballots, determines winners,
 * and outputs results. Extends Election class.
 *
 * @author Zachary Ross, Zaid Nolley
 */
#ifndef ELECTION_MV_H_
#define ELECTION_MV_H_

#include "election.h"
#include <tuple>


/**
 * @brief ElectionMV class handles Open Party List (MV) election.
 * 
 * Responsible for reading in election data from a file in the same directory as src.
 * Reads header data to determine whether it is an MV election. It reads the election 
 * data from file, processes ballots, determines winners, and outputs results to both 
 * terminal and a readonly audit file. Extends Election class.
 */
class ElectionMV : public Election {
    public:
        /**
         * @brief Constructs ElectionMV object with a user declared file name.
         * 
         * @param files The names (i.e. paths) of the files containing election data.
         */
        ElectionMV(vector<string> files);

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
         * @brief Gets the number of candidates in the election.
         * 
         * @return The number of candidates.
         */
        int getTotalCandidates();

        /**
         * @brief Reads the header information from the first election 
         * file that was passed in during initilization.
         * 
         * Includes the number of seats, number of ballots,
         * and number of candidates.
         *  It then organizes candidates by party.
         */
        void readHeader();

        /**
         * @brief Reads and processes all ballots.
         * 
         * This method goes through each ballot, counting votes party.
         * Also sets totalSeats and total Candidates.
         */
        void readBallots();

        /**
         * @brief Determines the winners.
         * 
         * This calculates the number of seats won by each party and
         * which candidates win.
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
         * Similar format as 'outputScreen', but directed into a file.
         */
        void outputFile();

    private:
        PartyMap partymap; ///< Manages party and candidate
        int seatsAvailable; ///< Number of seats available
        int totalBallots; ///< Number of ballots cast
        int totalCandidates; ///< Number of candidates
        vector<string> files; // Name of files with election data
        vector<vector<string>> winnerInfo; ///< Winners information by party
        vector<tuple<string, string, int>> winnerCandidates; ///< Winners
        vector<tuple<int, int>> partyRange; ///< Range of candidates for each party

};

#endif
