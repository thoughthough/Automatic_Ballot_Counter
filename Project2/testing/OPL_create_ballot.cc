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

    int seats, totalBallots = 0, candidates;
    std::cout << "Enter number of seats: ";
    std::cin >> seats;
    std::cout << "Enter number of candidates: ";
    std::cin >> candidates;

    // Placeholder for candidate names and votes count
    std::vector<std::string> candidateNames(candidates);
    std::vector<int> ballotsPerCandidate(candidates, 0);

    std::cin.ignore(); // Flush the newline character out of the buffer

    // Input for candidate names
    for (int i = 0; i < candidates; ++i) {
        std::cout << "Enter candidate " << i + 1 << " name and party: ";
        std::getline(std::cin, candidateNames[i]);
    }

    // Input for ballots per candidate
    for (int i = 0; i < candidates; ++i) {
        std::cout << "Enter how many ballots for candidate " << i + 1 << " you want generated: ";
        std::cin >> ballotsPerCandidate[i];
        totalBallots += ballotsPerCandidate[i]; // Sum up total ballots
    }

    // Write the header to the file
    outFile << "OPL" << std::endl;
    outFile << seats << std::endl;
    outFile << totalBallots << std::endl; // Total ballots calculated from user input
    outFile << candidates << std::endl;

    // Write candidate names to the file
    for (const auto& candidateLine : candidateNames) {
        outFile << candidateLine << std::endl;
    }

    // Generate ballots based on user input for each candidate
    for (int i = 0; i < candidates; ++i) {
        for (int j = 0; j < ballotsPerCandidate[i]; ++j) {
            for (int k = 0; k < candidates; ++k) {
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
