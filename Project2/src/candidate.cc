/**
 * @file Candidate.h
 * @brief Definition of the Candidate class.
 *
 * The Candidate class has the candidate name, vote count, and rank. 
 * It provides methods to manipulate and access these attributes.
 *
 * @author Christopher Atherton
 */
#include "include/candidate.h"

using namespace std;

Candidate::Candidate(string name, int rank) {
    this->name = name;
    this->rank = rank;
    this->voteCount = 0;
    this->won = false;
}

int Candidate::getVotes() {
    return this->voteCount;
}

int Candidate::getRank() {
    return this->rank;
}

void Candidate::setRank(int rank) {
    this->rank = rank;
}

string Candidate::getName() {
    return this->name;
}

int Candidate::addVote() {
    this->voteCount += 1;

    return this->voteCount;
}

void Candidate::setWinner() {
    this->won = true;
}

bool Candidate::getWon() {
    return this->won;
}
