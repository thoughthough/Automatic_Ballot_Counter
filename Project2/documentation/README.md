# repo-Team19
(Chris Atherton, Zaid Nolley, and Zach Ross)

Took the two day grace period for SDD document due on 3/1/2024.

SRS has been updated to fix/add use cases.

To use the program it needs to be compiled from the Project1/src directory using make. 
To run the program election officals then should input './election'
Then follow the prompts to input a file.
Input file needs to be in the same directory as src/
Or properly pathed example testing/Test.csv again from src/
Input files must be .csv example testing/inputFile.csv
Input files most be valid. See VALID FILES below.

Alternatively Testers can excute the program and input a test file from the command line.
after compiling the file using make 
Enter ./election testing/exampleTestFile.csv
This will expedite testing.
Input files most be valid. See VALID FILES below.

VALID FILES
Valid files need to have more candidites then seats.
Valid files must strictly adhear to the style guide.
First line declares election type. Either: OPL or CPL nothing else may appear on this line including spaces or tabs.
The Second line must only declare the number of Seats using a numberal. 
Example: 1. Spelling out the number is invalid, example: one. As is any spaces or tabs.
The Third line must only declare the number of Ballots using a numberal. 
Example: 1. Spelling out the number is invalid, example: one. As is any spaces or tabs.
The Fourth line must only declare the number of Parties using a numberal. 
Example: 1. Spelling out the number is invalid, example: one. As is any spaces or tabs.
If the election is of type CPL the next lines should declare the Parties and their respective candidites.
Each line is to contain one party and its candidites. 
The example that follows must be strictly followed.
Example on next line shows 6 parties declared:

Democratic, Joe, Sally, Ahmed
Republican, Allen, Nikki, Taihui
New Wave, Sarah
Reform, Xinyue, Nikita
Green, Bethany
Independent, Mike

After every party has been represented on its own line,
the next lines should show each individual ballot.
Example below for 9 ballots:
1,,,,,
1,,,,,
,1,,,,
,,,,1,
,,,,,1
,,,1,,
,,,1,,
1,,,,,
,1,,,,

The first ballot line shows a vote for the first party input
on the lines devoted to party input.
The third ballot shows a vote for the second party input.

Below is an example of a corretly formated file.csv:
CPL
3
9
6
Democratic, Joe, Sally, Ahmed
Republican, Allen, Nikki, Taihui
New Wave, Sarah
Reform, Xinyue, Nikita
Green, Bethany
Independent, Mike
1,,,,,
1,,,,,
,1,,,,
,,,,1,
,,,,,1
,,,1,,
,,,1,,
1,,,,,
,1,,,,

For OPL file format all of the above must be followed.
But the format should be as follows:
OPL
2
9
6
Democrat, Pike
Democrat, Lucy
Democrat, Beiye
Republican, Etta
Republican, Alawa
Independent1, Sasha
1,,,,,
1,,,,,
,1,,,,
,,,,1,
,,,,,1
,,,1,,
,,,1,,
,,,,1,
,,,,,1

Line one should be OPL.
And each candidate gets its own line.

All files should checked to ensure there are enough candites for seats.
The number of candidites declared on line 4 in OPL must match the number of candidates input on the proceding lines.
The number of parties declared on line 4 in CPL must match the number of parties input on the proceding lines.
The number of ballot declared in OPL or CPL on line 3 must match the number of ballots appearing on the file.


Running google tests:

Compiling: Type 'make' or 'make -j' inside of testing directory to compile GoogleTests for files election_opl_unittest.cc,
election_cpl_unittest.cc, election_mv_unittest.cc, and election_mpo_unittest.cc. This will create a single executable in 
the subdirectory '../build'.

Running: The tests are executed by entering './unittest' from inside this directory. The results of the
tests will be outputed as a list to the terminal with indications of the tests run, their source, and whether passed or failed.
A failed test may have an additional message printed indicating what should have been returned. The final lines of the output 
displays the number of tests run.

