/**
 * @file main.cc
 * @brief main calls functions
 *
 * Responsible for organizing the program
 *
 * @author Christopher Atherton
 */



#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

#include "include/electionOPL.h"
#include "include/electionCPL.h"
#include "include/electionMPO.h"
#include "include/electionMV.h"
#include "include/partyMap.h"

using namespace std;

int main(int argc, char* argv[]) {
    vector<string> files;
    string file_name;
    string line;
    ifstream file;
    // Open ballot file
    if (argc >= 2) {
        for (int i = 0; i < argc - 1; i ++) {
            file.open(argv[i + 1]);
            files.push_back(argv[i + 1]);
            if (!file.is_open()) {
                cout << "Could not open file\n";
                return 0;
            }
            file.close();
        }
    } else {
        bool finished = false;
        bool firstLoop = true;
        cout << "Type 'q' if you wish to exit the program without calculating results"<< endl;
        while ((!file.is_open() || !finished) && firstLoop) {
            cout << "Please enter the file name of your ballot file: ";
            cin >> file_name;
            if(file_name == "q"){
                return 0;
            }
            file.open(file_name);
            if (!file.is_open()) {
                cout << "File not found\n";
            } else {
                files.push_back(file_name);
                file.close();
                firstLoop = false;
            }
        }
        while(!firstLoop){
            cout << "Type 'c' to enter another file, type 'q' to quit, or type any other key to calculate results: ";
            cin >> file_name;
            if(file_name == "q"){
                return 0;
            }
            if (file_name != "c") {
                break;
            }
            cout << "Please enter the file name of your ballot file: ";
            cin >> file_name;
            file.open(file_name);
            if (!file.is_open()) {
                cout << "File not found\n";
            } else {
                files.push_back(file_name);
                file.close();
            }
        }
    }


    file_name = files[0];
    // Get first line of file and check if OPL, CPL, MPO. or MV
    file.open(file_name);
    getline(file, line);
    
    vector<Election*> elections;
    elections.push_back(new ElectionOPL(files));
    elections.push_back(new ElectionCPL(files));
    elections.push_back(new ElectionMPO(files));
    elections.push_back(new ElectionMV(files));
    int election_type;

    // Check for election type
    if (line.compare("OPL") == 0) {
        election_type = 0;
    } else if (line.compare("CPL") == 0) {
        election_type = 1;
    } else if (line.compare("MPO") == 0) {
        election_type = 2;
    } else if (line.compare("MV") == 0) {
        election_type = 3;
    } else {
        cout << "Invalid election type\n";
        return 0;
    }

    srand((unsigned) time(NULL));

    file.close();

    // Run election
    elections[election_type]->readHeader();
    elections[election_type]->readBallots();
    elections[election_type]->determineWinners();
    elections[election_type]->outputScreen();
    elections[election_type]->outputFile();
    return 0;
}
