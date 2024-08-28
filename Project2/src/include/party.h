/**
 * @file Party.h
 * @brief Definition of the Party class
 *
 * The Party class represents a political party, includes
 * party's name, total vote count, and seats won.
 *
 * @author Christopher Atherton
 */
#ifndef PARTY_H_
#define PARTY_H_

#include <iostream>

using namespace std;

class Party {
    public:
        /**
         * @brief Constructs a new Party object with a string name
         * 
         * @param name Name of party
         */
        Party(string name);

        /**
         * @brief Gets number of votes the party has
         * 
         * @return Vote count for the party
         */
        int getVotes();

        /**
         * @brief Gets number of seats won by party
         * 
         * @return Number of seats party has won
         */
        int getSeats();

        /**
         * @brief Gets the name of party
         * 
         * @return Name of party as string
         */
        string getName();

        /**
         * @brief Sets the number of seats won by party
         * 
         * @param seats Number of seats to be assigned to party
         */
        void setSeats(int seats);

        /**
         * @brief Increments the party vote count by one
         * 
         * Is used to add a vote for party
         * 
         * @return Vote count after adding one vote
         */
        int addVote();
        
    private:
        string name; ///< Name of party
        int voteCount; ///< Number of votes party has
        int seats; ///< Number of seats won by party

};

#endif
