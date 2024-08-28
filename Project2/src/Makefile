CXX = g++ -g

CXXFLAGS = -g -Wall -Wextra -std=c++11

SOURCES = main.cc candidate.cc electionCPL.cc electionOPL.cc party.cc partyMap.cc electionMPO.cc electionMV.cc

OBJECTS = $(SOURCES:.cpp=.0)

EXECUTABLE = election

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(EXECUTABLE)