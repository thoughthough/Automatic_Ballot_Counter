/**
 * @file Election.h
 * @brief Abstract base class calculating elections.
 *
 * The Election class serves as an abstract base for different types of elections.
 * Includes interface definitions for reading election headers and ballots from file,
 * abstract methods for determining election winners, and
 * methods for outputting election results to the GUI and to audit file.
 *
 * Derived classes to provide concrete implementations of these
 * methods.
 *
 * @author Christopher Atherton
 */
#ifndef ELECTION_H_
#define ELECTION_H_

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "partyMap.h"

using namespace std;
/**
 * @brief Election class is the interface for derived subtypes of elections
 * 
 */
class Election {
    public:
        Election() {}

        // Pure virtual functions
        virtual int getTotalBallots() = 0;

        virtual int getTotalSeats() = 0;

        virtual void readHeader() = 0;

        virtual void readBallots() = 0;

        virtual void determineWinners() = 0;

        virtual void outputScreen() = 0;

        virtual void outputFile() = 0;


    protected:
        PartyMap partymap; // party and candidate management
        int seatsAvailable; // Seats in election
        int totalBallots; // Ballots cast
        vector<string> files; // Name of files with election data
        vector<vector<string>> winnerInfo; // Information of winners

};

#endif
