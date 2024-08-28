CC = g++

CFLAGS = -g -std=c++11
DEP_DIR = ../dependencies
SOURCES = election_opl_unittest.cc ../src/main.cc ../src/candidate.cc ../src/electionCPL.cc ../src/electionOPL.cc ../src/party.cc ../src/partyMap.cc ../src/electionMPO.cc ../src/electionMV.cc
BUILD = build



EXECUTABLE = unittest

all: $(EXECUTABLE)

$(EXECUTABLE) : election_opl_unittest.cc election_cpl_unittest.cc election_mv_unittest.cc election_mpo_unittest.cc ../src/candidate.cc ../src/electionCPL.cc ../src/electionOPL.cc ../src/party.cc ../src/partyMap.cc ../src/electionMPO.cc ../src/electionMV.cc



$(EXECUTABLE):
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -I$(DEP_DIR)/include -Iinclude -L$(DEP_DIR)/lib $^ -lgtest_main -lgtest -lgmock -pthread -o $(BUILD)/$@

%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o /$@

.PHONY: clean

clean:
	rm -f $(EXECUTABLE) $(OBJECTS) core
