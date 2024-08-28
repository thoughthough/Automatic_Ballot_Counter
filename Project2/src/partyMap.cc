/**
 * @file PartyMap.cc
 * @brief Definition of the PartyMap class for parties and candidates
 *
 * The PartyMap class is to manage the of parties and candidates.
 * It can add parties and candidates, track votes for parties and 
 * candidates, calculate seats won by parties, and determine the ranking of candidates.
 *
 * @author Christopher Atherton
 */
#include "include/partyMap.h"
#include <tuple>

using namespace std;

PartyMap::PartyMap() {

}

int PartyMap::addParty(string name) {
    this->parties.push_back(Party(name));
    this->candidates.push_back(vector<Candidate>());
    return 0;
}

int PartyMap::addCandidate(string cName, int partyIdx) {
    this->candidates[partyIdx].push_back(Candidate(cName, this->candidates[partyIdx].size() + 1));
    return 0;
}

int PartyMap::getPartyCount() {
    return this->parties.size();
}

int PartyMap::getPartySeats(int partyIdx) {
    return this->parties[partyIdx].getSeats(); 
}

vector<Party> PartyMap::getParties() {
    return this->parties;
}

vector<vector<Candidate>> PartyMap::getCandidates() {
    return this->candidates;
}

int PartyMap::addPartyVote(int partyIdx) {
    this->parties[partyIdx].addVote();
    return 0;
}

int PartyMap::addCandidateVote(int partyIdx, int canIdx) {
    this->candidates[partyIdx][canIdx].addVote();
    this->parties[partyIdx].addVote();
    return 0;
}   

int PartyMap::tieBreaker(int numTied) {
    int finalNumber;
    for (int i = 0; i < 1000; i++) {
        finalNumber = rand() % numTied;
    }

    return finalNumber;
}

void PartyMap::calculateSeats(int totalVotes, int totalSeats, vector<vector<string>>& winnerInfo) {
    int quota = totalVotes / totalSeats;
    int originalTotal = totalSeats;
    // Get votes of each party
    vector<int> votes, seats;
    for (int i = 0; i < this->parties.size(); i++) {
        votes.push_back(this->parties[i].getVotes());
        // Set party name and vote count
        winnerInfo[i][0] = this->parties[i].getName();
        winnerInfo[i][1] = to_string(votes[i]);
    }
    seats.assign(votes.size(), 0);

    // First pass
    int curSeats = 0;
    for (int i = 0; i < votes.size(); i++) {
        if (quota != 0) {
            curSeats = votes[i] / quota;
            if (curSeats > this->candidates[i].size()) {
                curSeats = this->candidates[i].size();
            }
        }
        winnerInfo[i][2] = to_string(curSeats);
        seats[i] += curSeats;
        totalSeats -= curSeats;
        votes[i] -= quota * curSeats;
        winnerInfo[i][3] = to_string(votes[i]);
        winnerInfo[i][4] = to_string(0);
    }

    for (int i = 0; i < seats.size(); i++) {
        if (seats[i] == this->candidates[i].size()) {
            votes[i] = -1;
        }
    }

    // Second pass
    int curHighestVotes, curVotes, highestIndex, tiedWinner;
    vector<int> tiedParties;
    for (int i = 0; i < totalSeats; totalSeats--) {
        tiedParties.clear();
        curHighestVotes = -1;

        // Find highest vote count
        for (int j = 0; j < votes.size(); j++) {
            curVotes = votes[j];
            if (curVotes > curHighestVotes) {
                tiedParties.clear();
                curHighestVotes = curVotes;
                highestIndex = j;
                tiedWinner = highestIndex;
                tiedParties.push_back(highestIndex);
            }
        }

        // Check for ties
        for (int j = 0; j < votes.size(); j++) {
            curVotes = votes[j];
            if (curVotes == curHighestVotes && j != highestIndex) {
                tiedParties.push_back(j);
            }
        }
        if (tiedParties.size() > 1) {
            tiedWinner = tiedParties[this->tieBreaker(tiedParties.size())];
        }

        votes[tiedWinner] = -1;
        seats[tiedWinner] += 1;
        // totalSeats--;
        winnerInfo[tiedWinner][4] = to_string(1);
    }

    // Set seats of parties
    for (int i = 0; i < seats.size(); i++) {
        this->parties[i].setSeats(seats[i]);
        winnerInfo[i][5] = to_string(seats[i]);
    }

    // Set final winner info
    votes.clear();
    for (int i = 0; i < this->parties.size(); i++) {
        votes.push_back(this->parties[i].getVotes());
    }

    double percVote, percSeats;
    for (int i = 0; i < seats.size(); i++) {
        if (totalVotes == 0) {
            percVote = 0.0;
        } else {
            percVote = double(votes[i]) / double(totalVotes);
        }
        percSeats = double(seats[i]) / double(originalTotal);
        percVote *= 100;
        percSeats *= 100;
        winnerInfo[i][6] = to_string(int(percVote)) + "%/" + to_string(int(percSeats)) + "%";
    }

}

void PartyMap::setRankByVoteCount() {
    vector<int> votes, ranks;
    int curHighestVotes, curRank, curVotes, highestIndex;
    for (int i = 0; i < this->parties.size(); i++) {
        votes.clear();
        ranks.clear();

        // Get votes for current party
        for (int j = 0; j < this->candidates[i].size(); j++) {
            votes.push_back(this->candidates[i][j].getVotes());
        }
        ranks = votes;

        // Get ranks of party members
        curHighestVotes = -1;
        curRank = 1;
        for (int j = 0; j < votes.size(); j++) {
            curHighestVotes = -1;
            // Find highest vote count
            for (int k = 0; k < votes.size(); k++) {
                curVotes = votes[k];
                if (curVotes > curHighestVotes) {
                    curHighestVotes = curVotes;
                    highestIndex = k;
                }
            }
            ranks[highestIndex] = curRank;
            votes[highestIndex] = -1;
            // Check for ties
            for (int k = 0; k < votes.size(); k++) {
                curVotes = votes[k];
                if (curVotes == curHighestVotes && k != highestIndex) {
                    ranks[k] = curRank;
                    votes[k] = -1;
                    j++;
                }
            }
            curRank++;
        } 

        // Set ranks of current party
        for (int j = 0; j < this->candidates[i].size(); j++) {
            this->candidates[i][j].setRank(ranks[j]);
        }
    }
}

tuple<string, string, int> PartyMap::extractHighestRank(int partyIdx) { 
    vector<int> highestCandidates;
    int curHighestRank = 1000000;
    int curRank;

    // Get the highest ranked candidates
    for (int i = 0; i < this->candidates[partyIdx].size(); i++) {
        curRank = this->candidates[partyIdx][i].getRank();
        if (curRank <= curHighestRank) {
            if (curRank < curHighestRank) {
                highestCandidates.clear();
                highestCandidates.push_back(i);
                curHighestRank = curRank;
            } else {
                highestCandidates.push_back(i);
            }
        }
    }

    // Handle tie and get index of winner
    int winnerIdx;
    if (highestCandidates.size() > 1) {
        winnerIdx = highestCandidates[this->tieBreaker(highestCandidates.size())];
    } else {
        winnerIdx = highestCandidates[0];
    }

    // Get name, number of votes and remove from list
    string partyName = this->parties[partyIdx].getName();
    string winnerName = this->candidates[partyIdx][winnerIdx].getName();
    int winnerVotes = this->candidates[partyIdx][winnerIdx].getVotes();
    this->candidates[partyIdx][winnerIdx].setRank(1000000);

    return make_tuple(partyName, winnerName, winnerVotes); 
}

void PartyMap::extractPopularCandidate() {
    int curHighestVotes = -1;
    vector<tuple<int, int>> highestCandidates;

    // Find highest votes candidate
    int curVotes;
    for (int i = 0; i < this->parties.size(); i++) {
        for (int j = 0; j < this->candidates[i].size(); j++) {
            if (this->candidates[i][j].getWon() == false) {
                curVotes = this->candidates[i][j].getVotes();
            } else {
                curVotes = -1;
            }
            if (curVotes >= curHighestVotes) {
                if (curVotes > curHighestVotes) {
                    highestCandidates.clear();
                    highestCandidates.push_back(make_tuple(i, j));
                    curHighestVotes = curVotes;
                } else {
                    highestCandidates.push_back(make_tuple(i, j));
                }
            }
        }
    }

    // Handle tie and get index of winner
    tuple<int, int> winnerIdx;
    if (highestCandidates.size() > 1) {
        winnerIdx = highestCandidates[this->tieBreaker(highestCandidates.size())];
    } else {
        winnerIdx = highestCandidates[0];
    }

    // Set winner
    this->candidates[get<0>(winnerIdx)][get<1>(winnerIdx)].setWinner();

}

void PartyMap::printParties() {
    for (int i = 0; i < this->parties.size(); i++) {
        cout << "  " << this->parties[i].getName() << ":\n";
        for (int j = 0; j < this->candidates[i].size(); j++) {
            cout << "    Name:" << this->candidates[i][j].getName() 
            << " Votes:" << this->candidates[i][j].getVotes()
            << " Rank:" << this->candidates[i][j].getRank() << "\n";
        }
    }
}
