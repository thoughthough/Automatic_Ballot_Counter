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

#include "include/electionMPO.h"

using namespace std;

ElectionMPO::ElectionMPO(vector<string> files) {
    this->files = files;
    this->totalBallots = 0;
    this->totalCandidates = 0;
    this->seatsAvailable = 0;
}

int ElectionMPO::getTotalBallots() {
    return this->totalBallots;
}

int ElectionMPO::getTotalSeats() {
    return this->seatsAvailable;
}

int ElectionMPO::getTotalCandidates() {
    return this->totalCandidates;
}

void ElectionMPO::readHeader() {
    ifstream file;
    string line;

    file.open(this->files[0]);

    // Skip first line
    getline(file, line);
    
    // Get number of seats
    getline(file, line);
    this->seatsAvailable = stoi(line);

    // Get number of candidate
    getline(file, line);
    this->totalCandidates = stoi(line);

    // Get candidates
    getline(file, line);
    string currentCandidate = "";
    string currentParty = "";
    int currentPartySize = -1;
    
    vector<string> tokens;
    string word;
    tuple<int, int> range = make_tuple(0, 0);


    // Tokenize line
    istringstream s(line);
    while(getline(s, word, ',')) {
        word.erase(0, word.find_first_not_of("[ "));
        word.erase(word.find_last_not_of(" ]") + 1);
        tokens.push_back(word);
    }
    
    for (int i = 0; i < tokens.size(); i+= 2) {
        // Change partyRange
        if (tokens[i + 1].compare(currentParty) != 0) {
            if (i != 0) {
                get<1>(range) = (i / 2) - 1;
                this->partyRange.push_back(range);
            }
            get<0>(range) = i / 2;
            currentParty = tokens[i + 1];
            this->partymap.addParty(currentParty);
            currentPartySize++;
        }
        this->partymap.addCandidate(tokens[i], currentPartySize);
    }
    get<1>(range) = this->getTotalCandidates() - 1;
    this->partyRange.push_back(range);

    file.close();

}

void ElectionMPO::readBallots() {
    ifstream file;
    string line;
    int curBallots = 0;
    for (int i_line = 0; i_line < this->files.size(); i_line++) {
        file.open(this->files[i_line]);

        // Skip four lines
        getline(file, line);
        getline(file, line);
        getline(file, line);
        getline(file, line);

        // Get ballot count
        getline(file, line);
        curBallots = stoi(line);
        this->totalBallots += curBallots;
        
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

void ElectionMPO::determineWinners() {
    // Extract winners
    tuple<string, string, int> winnerTemp;
    for (int i = 0; i < this->getTotalSeats(); i++) {
        this->partymap.extractPopularCandidate();
    }

}

void ElectionMPO::outputScreen() {
    vector<Party> parties = this->partymap.getParties();
    vector<vector<Candidate>> candidates = this->partymap.getCandidates();
    cout << "========RESULTS========\n";
    cout << "Election type: Multiple Popularity Only\n";
    cout << "Number of Parties: " << this->partymap.getPartyCount() << "\n";
    cout << "Number of Ballots: " << this->getTotalBallots() << "\n";
    cout << "Number of Seats: " << this->getTotalSeats() << "\n";
    cout << "Winners:\n";
    double percVote;
    for (int i = 0 ; i < parties.size(); i++) {
        for (int j = 0; j < candidates[i].size(); j++) {
            if (candidates[i][j].getWon() == true) {
                percVote = double(candidates[i][j].getVotes()) / double(this->getTotalBallots());
                percVote *= 100;
                cout << "  Party: " << parties[i].getName()
                << " Name: " << candidates[i][j].getName()
                << " Vote Percentage: " << to_string(int(percVote)) + "%\n";
            }
        }
    }
    cout << "Losers:\n";
    for (int i = 0 ; i < parties.size(); i++) {
        for (int j = 0; j < candidates[i].size(); j++) {
            if (candidates[i][j].getWon() == false) {
                percVote = double(candidates[i][j].getVotes()) / double(this->getTotalBallots());
                percVote *= 100;
                cout << "  Party: " << parties[i].getName()
                << " Name: " << candidates[i][j].getName()
                << " Vote Percentage: " << to_string(int(percVote)) + "%\n";
            }
        }
    }
}

void ElectionMPO::outputFile() {
    string filename = "audit_files/audit.txt";  // Define the output file path
    ofstream outputFile(filename);  // Create ofstream object for file output

    if (!outputFile) {
        cerr << "Error opening the output file." << endl;
        return;
    }

    // Get parties and candidates from the party map
    vector<Party> parties = this->partymap.getParties();
    vector<vector<Candidate>> candidates = this->partymap.getCandidates();

    // Write header and election details to file
    outputFile << "========RESULTS========\n";
    outputFile << "Election type: Multiple Popularity Only (MPO)\n";  // Adjusted to correct election type
    outputFile << "Number of Parties: " << this->partymap.getPartyCount() << "\n";
    outputFile << "Number of Ballots: " << this->getTotalBallots() << "\n";
    outputFile << "Number of Seats: " << this->getTotalSeats() << "\n";

    // Writing winners to the file
    outputFile << "Winners:\n";
    double percVote;
    for (int i = 0; i < parties.size(); i++) {
        for (int j = 0; j < candidates[i].size(); j++) {
            if (candidates[i][j].getWon()) {
                percVote = 100.0 * candidates[i][j].getVotes() / this->getTotalBallots();
                outputFile << "  Party: " << parties[i].getName()
                           << " Name: " << candidates[i][j].getName()
                           << " Vote Percentage: " << fixed << setprecision(2) << percVote << "%\n";
            }
        }
    }

    // Writing losers to the file
    outputFile << "Losers:\n";
    for (int i = 0; i < parties.size(); i++) {
        for (int j = 0; j < candidates[i].size(); j++) {
            if (!candidates[i][j].getWon()) {
                percVote = 100.0 * candidates[i][j].getVotes() / this->getTotalBallots();
                outputFile << "  Party: " << parties[i].getName()
                           << " Name: " << candidates[i][j].getName()
                           << " Vote Percentage: " << fixed << setprecision(2) << percVote << "%\n";
            }
        }
    }

    outputFile.close();  // Close the file stream

    string command = "chmod 444 " + filename;
    system(command.c_str());
}
