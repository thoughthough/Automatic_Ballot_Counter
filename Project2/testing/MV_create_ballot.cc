#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::string filename;
    std::cout << "Enter output filename (with .csv extension): ";
    std::getline(std::cin, filename);

    if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".csv") {
        std::cerr << "Error: Filename must end with '.csv'" << std::endl;
        return 1;
    }

    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    int seats, candidates;
    std::cout << "Enter number of seats: ";
    if (!(std::cin >> seats) || seats < 1) {
        std::cerr << "Invalid number of seats." << std::endl;
        return 1;
    }

    std::cout << "Enter number of candidates: ";
    if (!(std::cin >> candidates) || candidates < 1) {
        std::cerr << "Invalid number of candidates." << std::endl;
        return 1;
    }

    std::vector<std::string> candidateNames(candidates);
    std::cin.ignore(); // Flush the newline character out of the buffer

    for (int i = 0; i < candidates; ++i) {
        std::cout << "Enter candidate " << i + 1 << " name and party: ";
        std::getline(std::cin, candidateNames[i]);
    }

    outFile << "MV" << std::endl;
    outFile << seats << std::endl;
    outFile << candidates << std::endl;
    for (int i = 0; i < candidates; ++i) {
        outFile << "[" << candidateNames[i] << "]";
        if (i < candidates - 1) outFile << ", ";
    }
    outFile << std::endl;

    int totalBallots;
    std::cout << "Enter number of ballots: ";
    std::cin >> totalBallots;
    outFile << totalBallots << std::endl;

    std::vector<int> votes(candidates, 0);
    for (int i = 0; i < candidates; ++i) {
        std::cout << "Enter number of votes for candidate " << i + 1 << ": ";
        std::cin >> votes[i];
        if (votes[i] > totalBallots) {
            std::cerr << "Error: Votes for a candidate cannot exceed the total number of ballots." << std::endl;
            return 1;
        }
    }

    // Generate ballots ensuring that each ballot has up to 'seats' votes
    std::vector<std::vector<int>> ballots(totalBallots, std::vector<int>(candidates, 0));
    for (int i = 0; i < candidates; ++i) {
        for (int j = 0, k = 0; j < votes[i]; ++j, ++k) {
            // Find the next ballot that has room for another vote
            while (std::count(ballots[k % totalBallots].begin(), ballots[k % totalBallots].end(), 1) >= seats) {
                k++;
            }
            ballots[k % totalBallots][i] = 1;
        }
    }

    for (const auto &ballot : ballots) {
        for (size_t i = 0; i < ballot.size(); ++i) {
            if (i > 0) outFile << ",";
            outFile << (ballot[i] ? "1" : "");
        }
        outFile << std::endl;
    }

    outFile.close();
    std::cout << "Ballots have been successfully generated in '" << filename << "'." << std::endl;

    return 0;
}
