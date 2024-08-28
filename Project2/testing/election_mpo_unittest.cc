#include "../src/include/electionMPO.h"
#include "gtest/gtest.h"

using namespace std;
#include <sstream>

class MPOTest : public ::testing::Test {
 public:
 //code that executes before test runs
  void SetUp() {
    MPO_vector.push_back("../../testing/MultiMPO1.csv");
    MPO_vector.push_back("../../testing/MultiMPO1.csv");
    elections.push_back(new ElectionMPO(MPO_vector));
    mpo_0 = dynamic_cast<ElectionMPO*>(elections.at(0));
    MPO_vector.clear();
    MPO_vector.push_back("../../testing/MultiMPO1.csv");
    elections.push_back(new ElectionMPO(MPO_vector));
    mpo_1 = dynamic_cast<ElectionMPO*>(elections.at(1));
    MPO_vector.clear();

    MPO_vector.push_back("../../testing/MultiMPO2.csv");
    MPO_vector.push_back("../../testing/MultiMPO1.csv");
    elections.push_back(new ElectionMPO(MPO_vector));
    mpo_2 = dynamic_cast<ElectionMPO*>(elections.at(2));
    MPO_vector.clear();

    for(int i = 0; i < 25; i++){
      MPO_vector.push_back("../../testing/MultiMPO3.csv");
    }
    elections.push_back(new ElectionMPO(MPO_vector));
    mpo_3 = dynamic_cast<ElectionMPO*>(elections.at(3));

  }
 protected:
    vector<Election*> elections;
    vector<std::string> MPO_vector;
    ElectionMPO* mpo_0;
    ElectionMPO* mpo_1;
    ElectionMPO* mpo_2;
    ElectionMPO* mpo_3;
};


TEST_F(MPOTest, GetterTests) {
  //tests getters after initialization
  EXPECT_EQ(mpo_0->getTotalBallots(),0)
    <<"getTotalballots not returning 0"; 
  EXPECT_EQ(mpo_0->getTotalCandidates(),0)
    <<"getTotalCandidates not returning 0"; 
  EXPECT_EQ(mpo_0->getTotalSeats(),0)
    <<"getTotalSeats not returning 0"; 
  
  EXPECT_EQ(mpo_3->getTotalBallots(),0)
    <<"getTotalballots not returning 0"; 
  EXPECT_EQ(mpo_3->getTotalCandidates(),0)
    <<"getTotalCandidates not returning 0"; 
  EXPECT_EQ(mpo_3->getTotalSeats(),0)
    <<"getTotalSeats not returning 0"; 
}

TEST_F(MPOTest, ReadHeaderTests) {
  mpo_0->readHeader();
  EXPECT_EQ(mpo_0->getTotalBallots(),0)
    <<"getTotalballots not returning 0"; 
  EXPECT_EQ(mpo_0->getTotalCandidates(),4)
    <<"getTotalCandidates not returning 4"; 
  EXPECT_EQ(mpo_0->getTotalSeats(),3)
    <<"getTotalSeats not returning 3";

  mpo_3->readHeader();
  EXPECT_EQ(mpo_3->getTotalBallots(),0)
    <<"getTotalballots not returning 0"; 
  EXPECT_EQ(mpo_3->getTotalCandidates(),4)
    <<"getTotalCandidates not returning 3"; 
  EXPECT_EQ(mpo_3->getTotalSeats(),3)
    <<"getTotalSeats not returning 3"; 
}

TEST_F(MPOTest, ReadBallotTests) {
  mpo_0->readHeader();
  mpo_0->readBallots();
  EXPECT_EQ(mpo_0->getTotalBallots(),100001*2)
    <<"getTotalballots not returning 200002"; 
  EXPECT_EQ(mpo_0->getTotalCandidates(),4)
    <<"getTotalCandidates not returning 4"; 
  EXPECT_EQ(mpo_0->getTotalSeats(),3)
    <<"getTotalSeats not returning 3"; 

  //check on different files with same candidates
  mpo_2->readHeader();
  mpo_2->readBallots();
  EXPECT_EQ(mpo_2->getTotalBallots(),100001 + 16)
    <<"getTotalballots not returning 100017"; 
  EXPECT_EQ(mpo_2->getTotalCandidates(),4)
    <<"getTotalCandidates not returning 4"; 
  EXPECT_EQ(mpo_2->getTotalSeats(),3)
    <<"getTotalSeats not returning 3"; 

  //checks 25 files with total votes > 100000
  mpo_3->readHeader();
  mpo_3->readBallots();
  EXPECT_EQ(mpo_3->getTotalBallots(),5013 * 25)
    <<"getTotalballots not returning correctly"; 
  EXPECT_EQ(mpo_3->getTotalCandidates(),4)
    <<"getTotalCandidates not returning 4"; 
  EXPECT_EQ(mpo_3->getTotalSeats(),3)
    <<"getTotalSeats not returning 3"; 
}

TEST_F(MPOTest, ScreenOutputTests) {
  mpo_0->readHeader();
  mpo_0->readBallots();
  mpo_0->determineWinners();
  testing::internal::CaptureStdout();
  mpo_0->outputScreen();
  std::string output1 = testing::internal::GetCapturedStdout();

  mpo_1->readHeader();
  mpo_1->readBallots();
  mpo_1->determineWinners();
  testing::internal::CaptureStdout();
  mpo_1->outputScreen();
  std::string output2 = testing::internal::GetCapturedStdout();
  EXPECT_NE(output1, output2)
    <<"Output strings should be different";
}