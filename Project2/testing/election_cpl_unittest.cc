#include "../src/include/electionCPL.h"
#include "gtest/gtest.h"

using namespace std;
#include <sstream>



class CPLTest : public ::testing::Test {
 public:
 //code that executes before test runs
  void SetUp() {
    CPL_vector.push_back("../../testing/CPL_2.csv");
    CPL_vector.push_back("../../testing/CPL_2.csv");
    elections.push_back(new ElectionCPL(CPL_vector));
    //downcasts first object in elections so that we can access its methods
    cpl_0 = dynamic_cast<ElectionCPL*>(elections.at(0));
    
    CPL_vector.clear();
    CPL_vector.push_back("../../testing/TestCPLTieFourMinute.csv");
    CPL_vector.push_back("../../testing/TestCPLTieFourMinute.csv");
    CPL_vector.push_back("../../testing/TestCPLTieFourMinute.csv");

    elections.push_back(new ElectionCPL(CPL_vector));
    cpl_1 = dynamic_cast<ElectionCPL*>(elections.at(1));
    
    CPL_vector.clear();
    CPL_vector.push_back("../../testing/TestCPLComplexLarge.csv");
    CPL_vector.push_back("../../testing/TestCPLComplexLarge.csv");
    elections.push_back(new ElectionCPL(CPL_vector));
    cpl_2 = dynamic_cast<ElectionCPL*>(elections.at(2));

    CPL_vector.clear();
    CPL_vector.push_back("../../testing/TestCPLComplexLarge.csv");
    elections.push_back(new ElectionCPL(CPL_vector));
    cpl_3 = dynamic_cast<ElectionCPL*>(elections.at(3));

  }

  protected:
    vector<Election*> elections;
    vector<std::string> CPL_vector;
    ElectionCPL* cpl_0;
    ElectionCPL* cpl_1;
    ElectionCPL* cpl_2;
    ElectionCPL* cpl_3;



};

TEST_F(CPLTest, GetterTests) {
  //tests getters after initialization
  EXPECT_EQ(cpl_0->getTotalBallots(),0)
    <<"getTotalballots not returning 0"; 
  EXPECT_EQ(cpl_0->getTotalSeats(),0)
    <<"getTotalSeats not returning 0"; 

}

TEST_F(CPLTest, ReadHeaderTests) {
    cpl_0->readHeader();
    //tests getters after readHeader()
    EXPECT_EQ(cpl_0->getTotalBallots(),0)
    <<"getTotalballots not returning 0"; 
    EXPECT_EQ(cpl_0->getTotalSeats(),1)
    <<"getTotalSeats not returning 1"; 

}

TEST_F(CPLTest, ReadBallotsTests) {
  cpl_0->readHeader();
  cpl_0->readBallots();
  EXPECT_EQ(cpl_0->getTotalBallots(), 230)
    <<"getTotalballots not returning accurate count";
  EXPECT_EQ(cpl_0->getTotalSeats(),1)
    <<"getTotalSeats not returning 1"; 

}

TEST_F(CPLTest, LargeFileTests) {
  //get time in seconds from start to end of calculation
  std::time_t start = std::time(0);
  cpl_1->readHeader();
  cpl_1->readBallots();
  EXPECT_EQ(cpl_1->getTotalBallots(), 300000)
    <<"getTotalballots not returning accurate count";
  EXPECT_EQ(cpl_1->getTotalSeats(),1)
    <<"getTotalSeats not returning 1";
  cpl_1->determineWinners();
  std::time_t end = std::time(0);
  //run time < 4 minutes
  EXPECT_LE(end - start, 240)
    <<"calculation should be under 4 minutes";

}

TEST_F(CPLTest, LargeFileComplexTests) {
  cpl_2->readHeader();
  cpl_2->readBallots();
  EXPECT_EQ(cpl_2->getTotalBallots(), 171390 * 2)
    <<"getTotalballots not returning accurate count";
  EXPECT_EQ(cpl_2->getTotalSeats(),25)
    <<"getTotalSeats not returning 25";
  cpl_2->determineWinners();
}


TEST_F(CPLTest, ScreenOutputTests){
  cpl_2->readHeader();
  cpl_2->readBallots();

  cpl_2->determineWinners();
  testing::internal::CaptureStdout();
  cpl_2->outputScreen();
  std::string output1 = testing::internal::GetCapturedStdout();
  cpl_3->readHeader();
  cpl_3->readBallots();
  cpl_3->determineWinners();

  testing::internal::CaptureStdout();
  cpl_3->outputScreen();
  std::string output2 = testing::internal::GetCapturedStdout();
  EXPECT_NE(output1, output2)
    <<"Output strings should be different";
}
