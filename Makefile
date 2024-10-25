# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall

# Linker flags
LDFLAGS = -lpthread

# Target executable
PlatformAPI: PlatformAPI.o User.o Item.o Computer.o Book.o Note.o GenericAPI.o
	$(CXX) $(LDFLAGS) PlatformAPI.o User.o Item.o Computer.o Book.o Note.o GenericAPI.o -o PlatformAPI

# Object file rules
PlatformAPI.o: PlatformAPI.cpp User.h Item.h Computer.h Book.h Note.h GenericAPI.h persistence.h
	$(CXX) $(CXXFLAGS) -c PlatformAPI.cpp

User.o: User.cpp User.h
	$(CXX) $(CXXFLAGS) -c User.cpp

Item.o: Item.cpp Item.h
	$(CXX) $(CXXFLAGS) -c Item.cpp

Computer.o: Computer.cpp Computer.h
	$(CXX) $(CXXFLAGS) -c Computer.cpp

Book.o: Book.cpp Book.h
	$(CXX) $(CXXFLAGS) -c Book.cpp

Note.o: Note.cpp Note.h
	$(CXX) $(CXXFLAGS) -c Note.cpp

GenericAPI.o: GenericAPI.cpp GenericAPI.h User.h Item.h Note.h Computer.h Book.h
	$(CXX) $(CXXFLAGS) -c GenericAPI.cpp

GenericAPITest: GenericAPITest.cpp User.o Item.o Computer.o Book.o Note.o GenericAPI.o
	g++ -lpthread GenericAPITest.cpp User.o Item.o Computer.o Book.o Note.o GenericAPI.o -o GenericAPITest

PersistenceTest: persistenceTest.cpp persistence.h Item.o
	g++ -lpthread persistenceTest.cpp Item.o -o PersistenceTest

ComputerTest: ComputerTest.cpp Computer.cpp Computer.h Computer.o Item.h Item.o
	g++ -lpthread ComputerTest.cpp Computer.o Item.o -o ComputerTest 

run-unit-tests: GenericAPITest PersistenceTest ComputerTest
	./GenericAPITest    ;\
	./PersistenceTest	;\
	./ComputerTest

static-analysis:
	cppcheck *.cpp

# Clean ups
clean:
	rm -f *.o PlatformAPI
