/**
 * @file electionMV.cc
 * @brief ElectionMV class handles Open Party List (MV) election.
 *
 * Responsible for reading in election data from a file in the same directory as src,
 * reads election data from file, processes ballots, determines winners,
 * and outputs results. Extends Election class.
 *
 * @author Zach Ross
 */
#include <sstream>
#include <iomanip>

#include "include/electionMV.h"

using namespace std;

ElectionMV::ElectionMV(vector<string> files) {
    this->files = files;
    this->totalBallots = 0;
    this->totalCandidates = 0;
    this->seatsAvailable = 0;
}

int ElectionMV::getTotalBallots() {
    return this->totalBallots;
}

int ElectionMV::getTotalSeats() {
    return this->seatsAvailable;
}

int ElectionMV::getTotalCandidates() {
    return this->totalCandidates;
}

void ElectionMV::readHeader() {
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

void ElectionMV::readBallots() {
    ifstream file;
    string line;
    int curBallots = 0;

    for (const auto& filename : this->files) {
        file.open(filename);

        // Skip four lines (MV, number of seats, number of candidates, candidate details)
        for (int i = 0; i < 4; ++i) {
            getline(file, line);
        }

        // Read number of ballots
        getline(file, line);
        curBallots = stoi(line);
        this->totalBallots += curBallots;

        // Read ballots
        while (getline(file, line)) {
            istringstream iss(line);
            string vote;
            int candidateIndex = 0;

            // Process each position in the ballot
            while (getline(iss, vote, ',')) {
                if (vote == "1") {
                    // Determine which party and candidate index it corresponds to
                    for (int j = 0; j < this->partyRange.size(); j++) {
                        tuple<int, int> currentRange = this->partyRange[j];
                        if (candidateIndex >= get<0>(currentRange) && candidateIndex <= get<1>(currentRange)) {
                            int partyIndex = j;
                            this->partymap.addCandidateVote(partyIndex, candidateIndex - get<0>(currentRange));
                            break; // Break once the correct range is found
                        }
                    }
                }
                candidateIndex++;
            }
        }

        file.close();
    }
}

void ElectionMV::determineWinners() {
    // Extract winners
    tuple<string, string, int> winnerTemp;
    for (int i = 0; i < this->getTotalSeats(); i++) {
        this->partymap.extractPopularCandidate();
    }

}

void ElectionMV::outputScreen() {
    vector<Party> parties = this->partymap.getParties();
    vector<vector<Candidate>> candidates = this->partymap.getCandidates();
    cout << "========RESULTS========\n";
    cout << "Election type: Multiple Vote\n";
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

void ElectionMV::outputFile() {
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
    outputFile << "Election type: Municipal Voting (MV)\n";  // Adjusted to correct election type
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
