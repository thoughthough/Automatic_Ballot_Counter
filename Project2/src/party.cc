/**
 * @file Party.cc
 * @brief Definition of the Party class
 *
 * The Party class represents a political party, includes
 * party's name, total vote count, and seats won.
 *
 * @author Christopher Atherton
 */
#include "include/party.h"

using namespace std;

Party::Party(string name) {
    this->name = name;
    this->seats = 0;
    this->voteCount = 0;
}

int Party::getVotes() {
    return this->voteCount;
}

int Party::getSeats() {
    return this->seats;
}

string Party::getName() {
    return this->name;
}

void Party::setSeats(int seats) {
    this->seats = seats;
}

int Party::addVote() {
    this->voteCount += 1;

    return this->voteCount;
}
