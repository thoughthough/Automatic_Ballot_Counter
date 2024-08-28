#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {
    std::string filename;
    std::cout << "Enter output filename (with .csv extension): ";
    std::getline(std::cin, filename);

    // Open a file in write mode.
    std::ofstream outFile(filename);

    // Check if file is open
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    int seats, totalBallots = 0, parties;
    std::cout << "Enter number of seats: ";
    std::cin >> seats;
    std::cout << "Enter number of parties: ";
    std::cin >> parties;

    // Placeholder for party names and votes count
    std::vector<std::string> partyNames(parties);
    std::vector<int> ballotsPerParty(parties, 0);

    std::cin.ignore(); // Flush the newline character out of the buffer

    // Input for party names
    for (int i = 0; i < parties; ++i) {
        std::cout << "Enter party " << i + 1 << " and candidate names: ";
        std::getline(std::cin, partyNames[i]);
    }

    // Input for ballots per party
    for (int i = 0; i < parties; ++i) {
        std::cout << "Enter how many ballots for party " << i + 1 << " you want generated: ";
        std::cin >> ballotsPerParty[i];
        totalBallots += ballotsPerParty[i]; // Sum up total ballots
    }

    // Write the header to the file
    outFile << "CPL" << std::endl;
    outFile << seats << std::endl;
    outFile << totalBallots << std::endl; // Total ballots calculated from user input
    outFile << parties << std::endl;

    // Write party and candidate names to the file
    for (const auto& partyLine : partyNames) {
        outFile << partyLine << std::endl;
    }

    // Generate ballots based on user input for each party
    for (int i = 0; i < parties; ++i) {
        for (int j = 0; j < ballotsPerParty[i]; ++j) {
            for (int k = 0; k < parties; ++k) {
                if (k == i) {
                    outFile << "1";
                } else {
                    outFile << ",";
                }
            }
            outFile << std::endl;
        }
    }

    // Close the file
    outFile.close();

    std::cout << "Ballots have been successfully generated in '" << filename << "'." << std::endl;

    return 0;
}
