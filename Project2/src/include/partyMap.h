/**
 * @file PartyMap.h
 * @brief Definition of the PartyMap class for parties and candidates
 *
 * The PartyMap class is to manage the of parties and candidates.
 * It can add parties and candidates, track votes for parties and 
 * candidates, calculate seats won by parties, and determine the ranking of candidates.
 *
 * @author Christopher Atherton
 */
#ifndef PARTYMAP_H_
#define PARTYMAP_H_

#include <iostream>
#include <vector>

#include "party.h"
#include "candidate.h"

using namespace std;

class PartyMap {
    public:
        /**
         * @brief Constructs a new PartyMap object
         */
        PartyMap();

        /**
         * @brief Adds a party
         * 
         * @param name Name of the party to be added
         * @return The index of the added party in the list
         */
        int addParty(string name);

        /**
         * @brief Adds a new candidate to a party
         * 
         * @param cName Name of candidate to be added
         * @param partyIdx Index of the party which the candidate belongs
         * @return Index of newly added candidate in party's candidate list
         */
        int addCandidate(string cName, int partyIdx);

        /**
         * @brief Gets total number of parties
         *
         * @return Number of parties
         */
        int getPartyCount();

        /**
         * @brief Gets number of seats won by a party
         * 
         * @param partyIdx Index of the party
         * @return The number of seats won by party
         */
        int getPartySeats(int partyIdx);

        
        /**
         * @brief Gets a list of all parties
         * 
         * @return Vector of all parties
         */
        vector<Party> getParties();

        /**
         * @brief List of list of all candidates, by party
         * 
         * @return Vector of vectors, =inner vector is of candidates of a party
         */
        vector<vector<Candidate>> getCandidates();

        /**
         * @brief Adds a vote to a party
         * 
         * @param partyIdx Index of party to get a vote.
         * @return Vote count for a party after one vote is added
         */
        int addPartyVote(int partyIdx);

        /**
         * @brief Adds a vote to a candidate within a party
         * 
         * @param partyIdx Index of party
         * @param canIdx Index of candidate in a party
         * @return Vote count of candidate after a vote is added
         */
        int addCandidateVote(int partyIdx, int canIdx);

        /**
         * @brief Breaks the ties 
         * 
         * @param numTied Number of ties
         */
        int tieBreaker(int numTied);

        /**
         * @brief Calculates and assigns seats to parties based on votes
         * 
         * @param totalVotes Number of votes cast
         * @param totalSeats Number of seats
         * @param winnerInfo Reference to a vector storing information about winners
         */
        void calculateSeats(int totalVotes, int totalSeats, vector<vector<string>>& winnerInfo);
       
        /**
         * @brief Sets the rank of candidates in a party based on vote
         */
        void setRankByVoteCount();

        /**
         * @brief Extracts the candidate with highest rank from party
         * 
         * @param partyIdx Index of party
         * @return Tuple of the party name, candidate name, and vote count
         */
        tuple<string, string, int> extractHighestRank(int partyIdx);

        void extractPopularCandidate();

        /**
         * @brief Prints a list of parties and their candidates to the GUI
         */
        void printParties();

    private:
        vector<Party> parties; ///< Vector of Party objects of parties
        vector<vector<Candidate>> candidates;

};

#endif
