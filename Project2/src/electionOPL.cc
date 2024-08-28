/**
 * @file electionOPL.cc
 * @brief ElectionOPL class handles Open Party List (OPL) election.
 *
 * Responsible for reading in election data from a file in the same directory as src,
 * reads election data from file, processes ballots, determines winners,
 * and outputs results. Extends Election class.
 *
 * @author Christopher Atherton
 */
#include <sstream>
#include <iomanip>

#include "include/electionOPL.h"

using namespace std;

ElectionOPL::ElectionOPL(vector<string> files) {
    this->files = files;
    this->totalBallots = 0;
}

int ElectionOPL::getTotalBallots() {
    return this->totalBallots;
}

int ElectionOPL::getTotalSeats() {
    return this->seatsAvailable;
}

int ElectionOPL::getTotalCandidates() {
    return this->totalCandidates;
}

void ElectionOPL::readHeader() {
    ifstream file;
    string line;

    file.open(this->files[0]);

    // Skip first line
    getline(file, line);
    
    // Get number of seats
    getline(file, line);
    this->seatsAvailable = stoi(line);

    // Skip number of ballots
    getline(file, line);

    // Get number of candidate
    getline(file, line);
    this->totalCandidates = stoi(line);

    // Get candidates
    string currentParty = "";
    int currentPartySize = -1;
    
    vector<string> tokens;
    string word;
    tuple<int, int> range = make_tuple(0, 0);
    for (int i = 0; i < this->getTotalCandidates(); i++) {
        tokens.clear();
        getline(file, line);

        // Tokenize line
        istringstream s(line);
        while(getline(s, word, ',')) {
            word.erase(0, word.find_first_not_of(" "));
            word.erase(word.find_last_not_of(" ") + 1);
            tokens.push_back(word);
        }
        
        // Change partyRange
        if (tokens[0].compare(currentParty) != 0) {
            if (i != 0) {
                get<1>(range) = i - 1;
                this->partyRange.push_back(range);
            }
            get<0>(range) = i;
            currentParty = tokens[0];
            this->partymap.addParty(currentParty);
            currentPartySize++;
        }

        this->partymap.addCandidate(tokens[1], currentPartySize);
        
    }

    get<1>(range) = this->getTotalCandidates() - 1;
    this->partyRange.push_back(range);
    
    // Resize info vector according to number of parties
    this->winnerInfo.resize(this->partymap.getPartyCount());
    for (int i = 0; i < this->partymap.getPartyCount(); i++) {
        this->winnerInfo[i].resize(7);
    }

    file.close();

}

void ElectionOPL::readBallots() {
    ifstream file;
    string line;
    int curBallots = 0;
    for (int i_line = 0; i_line < this->files.size(); i_line++) {
        file.open(this->files[i_line]);

        // Skip  two lines
        getline(file, line);
        getline(file, line);

        // Get ballot count
        getline(file, line);
        curBallots = stoi(line);
        this->totalBallots += curBallots;

        // Skip candidates plus 1 lines
        for (int i = 0; i < this->getTotalCandidates() + 1; i++) {
            getline(file, line);
        }
        
        // Read ballots
        int voteIndex, partyIndex, candidateIndex;
        tuple<int, int> currentRange;
        for (int i = 0; i < curBallots; i++) {
            getline(file, line);
            voteIndex = line.find('1');

            // Check which range it falls in
            for (int j = 0; j < this->partyRange.size(); j++) {
                currentRange = this->partyRange[j];
                if (voteIndex >= get<0>(currentRange) && voteIndex <= get<1>(currentRange)) {
                    partyIndex = j;
                    candidateIndex = voteIndex - get<0>(currentRange);
                    this->partymap.addCandidateVote(partyIndex, candidateIndex);
                }
            }
        }

        file.close();
    }
}   

void ElectionOPL::determineWinners() {

    // Determine seat counts
    this->partymap.calculateSeats(this->getTotalBallots(), this->getTotalSeats(), this->winnerInfo);

    // Rank candidates by vote
    this->partymap.setRankByVoteCount();

    // Extract winners
    tuple<string, string, int> winnerTemp;
    for (int i = 0; i < this->partymap.getPartyCount(); i++) {
        for (int j = 0; j < this->partymap.getPartySeats(i); j++) {
            // Extract a winner j number of times
            winnerTemp = this->partymap.extractHighestRank(i);
            this->winnerCandidates.push_back(winnerTemp);
        }
    }

}

void ElectionOPL::outputScreen() {
    vector<Party> parties = this->partymap.getParties();
    vector<vector<Candidate>> candidates = this->partymap.getCandidates();
    cout << "========RESULTS========\n";
    cout << "Election type: Open Party Listing\n";
    cout << "Number of Parties: " << this->partymap.getPartyCount() << "\n";
    cout << "Number of Ballots: " << this->getTotalBallots() << "\n";
    cout << "Number of Seats: " << this->getTotalSeats() << "\n";
    cout << "Parties and Candidates:\n";
    for (int i = 0; i < this->partymap.getPartyCount(); i++) {
        cout << "  " << parties[i].getName() << ":\n";
        for (int j = 0; j < candidates[i].size(); j++) {
            cout << "    " << candidates[i][j].getName() << "\n";
        }
    }
    cout << "Winners:\n";
    for (int i = 0 ; i < this->winnerCandidates.size(); i++) {
        cout << "  Party: " << get<0>(winnerCandidates[i])
        << " Name: " << get<1>(winnerCandidates[i])
        << " Votes: " << get<2>(winnerCandidates[i]) << "\n";
    }

    cout << "Seat Allocation:\n";
    cout << "  Parties     Votes   First Allocation   Remaining Votes   Second Allocation  Final Seat Total  % of Vote to % of Seats\n";
    for (int i = 0; i < this->winnerInfo.size(); i++) {
        for (int j = 0; j < this->winnerInfo[i].size(); j++) {
            cout << left << setw(17) << setfill(' ') << this->winnerInfo[i][j];
        }
        cout << "\n";
    }
}

void ElectionOPL::outputFile() {
    string filename = "audit_files/audit.txt";
    ofstream outputFile(filename);

    vector<Party> parties = this->partymap.getParties();
    vector<vector<Candidate>> candidates = this->partymap.getCandidates();
    outputFile << "========RESULTS========\n";
    outputFile << "Election type: Open Party Listing\n";
    outputFile << "Number of Parties: " << this->partymap.getPartyCount() << "\n";
    outputFile << "Number of Ballots: " << this->getTotalBallots() << "\n";
    outputFile << "Number of Seats: " << this->getTotalSeats() << "\n";
    outputFile << "Parties and Candidates:\n";
    for (int i = 0; i < this->partymap.getPartyCount(); i++) {
        outputFile << "  " << parties[i].getName() << ":\n";
        for (int j = 0; j < candidates[i].size(); j++) {
            double votePercentage = (static_cast<double>(candidates[i][j].getVotes()) / this->getTotalBallots()) * 100;
            outputFile << "    " << candidates[i][j].getName()
                       << " - Votes: " << candidates[i][j].getVotes()
                       << " (" << fixed << setprecision(2) << votePercentage << "%)\n";
        }
    }
    outputFile << "Winners:\n";
    for (int i = 0; i < this->winnerCandidates.size(); i++) {
        outputFile << "  Party: " << get<0>(winnerCandidates[i])
                   << " Name: " << get<1>(winnerCandidates[i])
                   << " Votes: " << get<2>(winnerCandidates[i]) << "\n";
    }

    outputFile << "Seat Allocation:\n";
    outputFile << "  Parties     Votes   First Allocation   Remaining Votes   Second Allocation  Final Seat Total  % of Vote to % of Seats\n";
    for (int i = 0; i < this->winnerInfo.size(); i++) {
        for (int j = 0; j < this->winnerInfo[i].size(); j++) {
            outputFile << left << setw(17) << setfill(' ') << this->winnerInfo[i][j];
        }
        outputFile << "\n";
    }

    outputFile.close();

    string command = "chmod 444 " + filename;
    system(command.c_str());
}
