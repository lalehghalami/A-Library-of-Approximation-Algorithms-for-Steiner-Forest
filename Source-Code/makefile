CXX=g++

EXEC    = SF-main

main:
	$(CXX) -o SFout $(EXEC).cpp PD-SF.cpp PG-SF.cpp GL-SF.cpp TM-SF.cpp SF-Solution.cpp SF-Functions.cpp TM-Functions.cpp -std=c++0x

clean:
	/bin/rm -f $(EXEC) $(EXEC)*.o $(EXEC)*.s