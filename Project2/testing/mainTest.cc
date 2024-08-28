#include "electionOPL.h"
#include "electionCPL.h"
#include "partyMap.h"
#include "party.h"
#include <iostream>

void testAddPartyAndCandidate() {
    PartyMap partyMap;

    // Test adding a party
    partyMap.addParty("Test Party");
    std::cout << "Added 'Test Party'. Party count: " << partyMap.getPartyCount() << std::endl;

    // Test adding a candidate to the party
    partyMap.addCandidate("Test Candidate", 0); // Assuming the first party has index 0
    auto candidates = partyMap.getCandidates();
    std::cout << "Added 'Test Candidate' to 'Test Party'.\n";
    std::cout << "Candidate count in 'Test Party': " << candidates[0].size() << std::endl;

    // Verify if candidate is added correctly
    if (candidates[0].size() > 0 && candidates[0][0].getName() == "Test Candidate") {
        std::cout << "Candidate verification passed.\n";
    } else {
        std::cout << "Candidate verification failed.\n";
    }
}

void testVoteCountAndSeats() {
    PartyMap partyMap;
    partyMap.addParty("Voting Party");
    partyMap.addCandidate("Voting Candidate", 0);

    // Adding votes
    partyMap.addPartyVote(0);
    partyMap.addCandidateVote(0, 0);

    // Assigning seats
    partyMap.getParties()[0].setSeats(1);

    std::cout << "Votes for 'Voting Party': " << partyMap.getParties()[0].getVotes() << std::endl;
    std::cout << "Seats for 'Voting Party': " << partyMap.getParties()[0].getSeats() << std::endl;

    // Verifications
    if (partyMap.getParties()[0].getVotes() == 1 && partyMap.getParties()[0].getSeats() == 1) {
        std::cout << "Vote and seat assignment test passed.\n";
    } 
}

void testCandidate() {
    std::cout << "\nTesting Candidate class\n";

    Candidate candidate("Test Candidate", 1);

    // Test getName()
    std::cout << "Candidate name: " << candidate.getName() << std::endl;

    // Test addVote() and getVotes()
    candidate.addVote();
    std::cout << "Votes after adding 1 vote: " << candidate.getVotes() << std::endl;

    // Test setRank() and getRank()
    candidate.setRank(2);
    std::cout << "Rank after setting to 2: " << candidate.getRank() << std::endl;

    // Verification
    bool passed = true;
    if (candidate.getName() != "Test Candidate") {
        std::cout << "Name test failed.\n";
        passed = false;
    }
    if (candidate.getVotes() != 1) {
        std::cout << "Vote count test failed.\n";
        passed = false;
    }
    if (candidate.getRank() != 2) {
        std::cout << "Rank test failed.\n";
        passed = false;
    }

    if (passed) {
        std::cout << "All Candidate tests passed.\n";
    }
}

int main() {
    // Create a party instance
    Party party("Test Party");

    std::cout << "Testing Party class\n";

    // Test getName()
    std::cout << "Party name: " << party.getName() << std::endl;
    if (party.getName() == "Test Party") {
        std::cout << "getName() test passed\n";
    } else {
        std::cout << "getName() test failed\n";
    }

    // Test addVote() and getVotes()
    party.addVote();
    party.addVote(); 
    std::cout << "Votes after adding 2 votes: " << party.getVotes() << std::endl;
    if (party.getVotes() == 2) {
        std::cout << "Vote manipulation test passed\n";
    } else {
        std::cout << "Vote manipulation test failed\n";
    }

    // Test setSeats() and getSeats()
    party.setSeats(5); // Assign 5 seats
    std::cout << "Seats after setting to 5: " << party.getSeats() << std::endl;
    if (party.getSeats() == 5) {
        std::cout << "Seat manipulation test passed\n";
    } else {
        std::cout << "Seat manipulation test failed\n";
    }

    std::cout << "Testing PartyMap and related classes\n";
    
    testAddPartyAndCandidate();
    testVoteCountAndSeats();
    
    testCandidate();

    return 0;
}
