/**
 * @file Candidate.h
 * @brief Definition of the Candidate class.
 *
 * The Candidate class has the candidate name, vote count, and rank. 
 * It provides methods to manipulate and access these attributes.
 *
 * @author Christopher Atherton
 */
#ifndef CANDIDATE_H_
#define CANDIDATE_H_

#include <iostream>

using namespace std;

class Candidate {
    public:
        /**
         * @brief Constructs a new Candidate object
         * 
         * @param name Name of candidate
         * @param rank Initial rank of candidate
         */
        Candidate(string name, int rank);

        /**
         * @brief Gets number of votes for candidate
         * 
         * @return Vote count
         */
        int getVotes();
      
        /**
         * @brief Gets rank of candidate
         * 
         * @return Rank
         */
        int getRank();

        /**
         * @brief Sets rank of candidate
         * 
         * @param rank New rank to be set for the candidate
         */
        void setRank(int rank);

        /**
         * @brief Gets name of candidate
         * 
         * @return Name as string
         */
        string getName();

        /**
         * @brief Increments the vote count of candidate one
         * 
         * This method is used to count a vote for a candidate
         * 
         * @return Total vote count after adding one
         */
        int addVote();

        void setWinner();

        bool getWon();

    private:
        string name; ///< Name of candidate
        int voteCount; ///< Number of votes candidate has
        int rank; ///< Rank of candidate, used in the election results
        bool won;
};

#endif
