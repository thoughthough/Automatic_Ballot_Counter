/**
 * @file electionCPL.cc
 * @brief ElectionCPL class handles Closed Party List (CPL) election
 *
 * Responsible for reading in election data from a file in the same directory as src,
 * reads election data from file, processes ballots, determines winners,
 * and outputs results. Extends Election class.
 *
 * @author Zaid Nolley
 */
#include "include/electionCPL.h"

#include <sstream>
#include <iomanip>

using namespace std;

ElectionCPL::ElectionCPL(vector<string> files) {
    this->files = files;
    this->totalBallots = 0;
    this->seatsAvailable = 0;
}

int ElectionCPL::getTotalBallots() {
    return this->totalBallots;
}

int ElectionCPL::getTotalSeats() {
    return this->seatsAvailable;
}

void ElectionCPL::readHeader() {
    ifstream file;
    std::string fileLine;
    file.open(this->files[0]);

    std::getline(file, fileLine);
    if(fileLine != "CPL"){
        //currently C code, probably will need to be changed to work with c++
        std::cerr << "Error reading file" << endl;
        return;
    }
    std::getline(file, fileLine);
    this->seatsAvailable = stoi(fileLine);
    std::getline(file, fileLine);
    std::getline(file, fileLine);
    int totalParties = stoi(fileLine);

    //reads in the party name, followed by the candidates belonging to that party on each line
    //the order that the candidates are read in indicate their party's ranking of them (i.e decreasing)
    std::vector<std::string> tokens;
    std::string word;
    for(int i = 0; i < totalParties; i++) {
        std::getline(file, fileLine, ',');
        this->partymap.addParty(fileLine);
        std::getline(file, fileLine);
        istringstream my_stream(fileLine);
        //gets each candidate name
        while(std::getline(my_stream, word, ',')){
            this->partymap.addCandidate(word, i);
        }
    }
    file.close();
}

void ElectionCPL::readBallots() {
    if(this->partymap.getPartyCount() < 1){
        std::cerr << "Invalid number of parties in PartyMap" << endl;
        return;
    }
    ifstream file;
    std::string fileLine;
    int curBallots = 0;
    for (int i_line = 0; i_line < this->files.size(); i_line++) {
        file.open(this->files[i_line]);
        //skip over header lines of file

        // Skip  two lines
        getline(file, fileLine);
        getline(file, fileLine);

        // Get ballot count
        getline(file, fileLine);
        curBallots = stoi(fileLine);
        this->totalBallots += curBallots;

        // Skip parties plus 1 lines
        int HeaderLines = 1 + this->partymap.getPartyCount();
        while(HeaderLines--){
            std::getline(file, fileLine);
        }

        int ballotsLeft = curBallots;
        while(ballotsLeft--){
            std::string voteIdx;
            std::getline(file, fileLine);
            istringstream my_stream(fileLine);
            std::getline(my_stream, voteIdx, '1');
            this->partymap.addPartyVote(voteIdx.size());
        }
        this->winnerInfo.resize(this->partymap.getPartyCount());
        for (int i = 0; i < this->partymap.getPartyCount(); i++) {
            this->winnerInfo[i].resize(7);
        }
        file.close();
    }
    
}   

void ElectionCPL::determineWinners() {
    
    // Determine seat counts
    this->partymap.calculateSeats(this->getTotalBallots(), this->getTotalSeats(), this->winnerInfo);
    


    // Extract winners
    tuple<string, string, int> winnerTemp;
    for (int i = 0; i < this->partymap.getPartyCount(); i++) {
        for (int j = 0; j < this->partymap.getPartySeats(i); j++) {
            // Extract a winner
            winnerTemp = this->partymap.extractHighestRank(i);
            this->winnerCandidates.push_back(winnerTemp);
        }
    }

}

void ElectionCPL::outputScreen() {
    vector<Party> parties = this->partymap.getParties();
    vector<vector<Candidate>> candidates = this->partymap.getCandidates();
    cout << "========RESULTS========\n";
    cout << "Election type: Closed Party\n";
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
        << " Name: " << get<1>(winnerCandidates[i]) << "\n";
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

void ElectionCPL::outputFile() {
    string filename = "audit_files/audit.txt";
    ofstream outputFile(filename);

    vector<Party> parties = this->partymap.getParties();
    vector<vector<Candidate>> candidates = this->partymap.getCandidates();
    outputFile << "========RESULTS========\n";
    outputFile << "Election type: Closed Party\n";
    outputFile << "Number of Parties: " << this->partymap.getPartyCount() << "\n";
    outputFile << "Number of Ballots: " << this->getTotalBallots() << "\n";
    outputFile << "Number of Seats: " << this->getTotalSeats() << "\n";
    outputFile << "Parties and Candidates:\n";
    for (int i = 0; i < this->partymap.getPartyCount(); i++) {
        outputFile << "  " << parties[i].getName() << ":\n";
        for (int j = 0; j < candidates[i].size(); j++) {
            outputFile << "    " << candidates[i][j].getName() << "\n";
        }
    }
    outputFile << "Winners:\n";
    for (int i = 0 ; i < this->winnerCandidates.size(); i++) {
        outputFile << "  Party: " << get<0>(winnerCandidates[i])
        << " Name: " << get<1>(winnerCandidates[i]) << "\n";
    }

    const char seperator = ' ';
    outputFile << "Seat Allocation:\n";
    outputFile << "  Parties     Votes   First Allocation   Remaining Votes   Second Allocation  Final Seat Total  % of Vote to % of Seats\n";
    for (int i = 0; i < this->winnerInfo.size(); i++) {
        for (int j = 0; j < this->winnerInfo[i].size(); j++) {
            outputFile << left << setw(17) << setfill(seperator) << this->winnerInfo[i][j];
        }
        outputFile << "\n";
    }

    outputFile.close();

    string command = "chmod 444 " + filename;
    system(command.c_str());
}


