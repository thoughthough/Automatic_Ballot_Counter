#include "../src/include/electionOPL.h"
#include "gtest/gtest.h"

using namespace std;
#include <sstream>



class OPLTest : public ::testing::Test {
 public:
 //code that executes before test runs
  void SetUp() {
    OPL_vector.push_back("../../testing/OPL_1.csv");
    OPL_vector.push_back("../../testing/OPL_1.csv");
    elections.push_back(new ElectionOPL(OPL_vector));
    //downcasts first object in elections so that we can access its methods
    opl_0 = dynamic_cast<ElectionOPL*>(elections.at(0));

    OPL_vector.clear();
    OPL_vector.push_back("../../testing/TestOPLTieFourMinute.csv");
    OPL_vector.push_back("../../testing/TestOPLTieFourMinute.csv");
    OPL_vector.push_back("../../testing/TestOPLTieFourMinute.csv");
    elections.push_back(new ElectionOPL(OPL_vector));
    opl_1 = dynamic_cast<ElectionOPL*>(elections.at(1));

    OPL_vector.clear();
    OPL_vector.push_back("../../testing/TestOPLTieFourMinute.csv");
    elections.push_back(new ElectionOPL(OPL_vector));
    opl_2 = dynamic_cast<ElectionOPL*>(elections.at(2));
    
  }

  protected:
    vector<Election*> elections;
    vector<std::string> OPL_vector;
    ElectionOPL* opl_0;
    ElectionOPL* opl_1;
    //only 1 file added for comparison purposes
    ElectionOPL* opl_2;

};

TEST_F(OPLTest, GetterTests) {
  //tests getters after initialization
  EXPECT_EQ(opl_0->getTotalBallots(),0)
    <<"getTotalballots not returning 0"; 
  EXPECT_EQ(opl_0->getTotalCandidates(),0)
    <<"getTotalCandidates not returning 0"; 
  EXPECT_EQ(opl_0->getTotalSeats(),0)
    <<"getTotalSeats not returning 0"; 

}

TEST_F(OPLTest, ReadHeaderTests) {
  opl_0->readHeader();
  EXPECT_EQ(opl_0->getTotalCandidates(),6)
    <<"getTotalCandidates not returning 12"; 
  EXPECT_EQ(opl_0->getTotalSeats(),2)
    <<"getTotalSeats not returning 2"; 
  opl_0->determineWinners();
}


TEST_F(OPLTest, LargeFileTests) {
  opl_1->readHeader();
  opl_1->readBallots();
  std::time_t start = std::time(0);
  EXPECT_EQ(opl_1->getTotalCandidates(),10)
    <<"getTotalCandidates not returning 10"; 
  EXPECT_EQ(opl_1->getTotalSeats(),1)
    <<"getTotalSeats not returning 1"; 
  EXPECT_EQ(opl_1->getTotalBallots(), 300000)
    <<"getTotalballots not returning accurate count";
  opl_1->determineWinners();
    std::time_t end = std::time(0);
  //run time < 4 minutes
  EXPECT_LE(end - start, 240)
    <<"calculation should be under 4 minutes";

}

TEST_F(OPLTest, ScreenOutputTests){
  opl_1->readHeader();
  opl_1->readBallots();
  opl_1->determineWinners();
  testing::internal::CaptureStdout();
  opl_1->outputScreen();
  std::string output1 = testing::internal::GetCapturedStdout();

  opl_2->readHeader();
  opl_2->readBallots();
  opl_2->determineWinners();

  testing::internal::CaptureStdout();
  opl_2->outputScreen();
  std::string output2 = testing::internal::GetCapturedStdout();
  EXPECT_NE(output1, output2)
    <<"Output strings should be different";
}
