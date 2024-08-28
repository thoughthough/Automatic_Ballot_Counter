#include "../src/include/electionMV.h"
#include "gtest/gtest.h"

using namespace std;
#include <sstream>

class MVTest : public ::testing::Test {
 public:
 //code that executes before test runs
  void SetUp() {
    MV_vector.push_back("../../testing/MultiMV1.csv");
    MV_vector.push_back("../../testing/MultiMV1.csv");
    elections.push_back(new ElectionMV(MV_vector));
    mv_0 = dynamic_cast<ElectionMV*>(elections.at(0));
    MV_vector.clear();
    MV_vector.push_back("../../testing/MultiMV1.csv");
    elections.push_back(new ElectionMV(MV_vector));
    mv_1 = dynamic_cast<ElectionMV*>(elections.at(1));
    MV_vector.clear();
    MV_vector.push_back("../../testing/MultiMV3.csv");
    MV_vector.push_back("../../testing/MultiMV4.csv");
    elections.push_back(new ElectionMV(MV_vector));
    mv_2 = dynamic_cast<ElectionMV*>(elections.at(2));
  }
 protected:
    vector<Election*> elections;
    vector<std::string> MV_vector;
    ElectionMV* mv_0;
    ElectionMV* mv_1;
    ElectionMV* mv_2;
};

TEST_F(MVTest, GetterTests) {
  //tests getters after initialization
  EXPECT_EQ(mv_0->getTotalBallots(),0)
    <<"getTotalballots not returning 0"; 
  EXPECT_EQ(mv_0->getTotalCandidates(),0)
    <<"getTotalCandidates not returning 0"; 
  EXPECT_EQ(mv_0->getTotalSeats(),0)
    <<"getTotalSeats not returning 0"; 
}

TEST_F(MVTest, ReadHeaderTests) {
  mv_0->readHeader();
  EXPECT_EQ(mv_0->getTotalBallots(),0)
    <<"getTotalballots not returning 0"; 
  EXPECT_EQ(mv_0->getTotalCandidates(),4)
    <<"getTotalCandidates not returning 4"; 
  EXPECT_EQ(mv_0->getTotalSeats(),3)
    <<"getTotalSeats not returning 3"; 
}

TEST_F(MVTest, ReadBallotTests) {
  mv_0->readHeader();
  mv_0->readBallots();
  EXPECT_EQ(mv_0->getTotalBallots(),12)
    <<"getTotalballots not returning 12"; 
  EXPECT_EQ(mv_0->getTotalCandidates(),4)
    <<"getTotalCandidates not returning 4"; 
  EXPECT_EQ(mv_0->getTotalSeats(),3)
    <<"getTotalSeats not returning 3"; 
}
TEST_F(MVTest, DifferentBallotTests) {
  mv_2->readHeader();
  mv_2->readBallots();
  mv_2->determineWinners();
  EXPECT_EQ(mv_2->getTotalBallots(),100001 + 100000)
    <<"getTotalballots not returning correctly"; 
  EXPECT_EQ(mv_2->getTotalCandidates(),4)
    <<"getTotalCandidates not returning 4"; 
  EXPECT_EQ(mv_2->getTotalSeats(),3)
    <<"getTotalSeats not returning 3";
  //informally checks the syntax of output
  //mv_2->outputScreen();

}
TEST_F(MVTest, ScreenOutputTests) {
  mv_0->readHeader();
  mv_0->readBallots();
  mv_0->determineWinners();
  testing::internal::CaptureStdout();
  mv_0->outputScreen();
  std::string output1 = testing::internal::GetCapturedStdout();

  mv_1->readHeader();
  mv_1->readBallots();
  mv_1->determineWinners();
  testing::internal::CaptureStdout();
  mv_1->outputScreen();
  std::string output2 = testing::internal::GetCapturedStdout();
  EXPECT_NE(output1, output2)
    <<"Output strings should be different";

}