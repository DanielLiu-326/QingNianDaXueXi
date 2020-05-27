CXX=g++
CXXFLAGS= -std=c++11 -Wall -pedantic
OBJ_DIR = ../obj/
INCLUDE_DIR = ../include/
DEPS = -lcurl
BUILD_DIR = ../build/

$(BUILD_DIR)QNDXX_Program:./main.cpp $(OBJ_DIR)Network.o $(OBJ_DIR)Program.o $(INCLUDE_DIR)Program.hpp
	$(CXX) $(CXXFLAGS) $(DEPS) $< -o $@ $(filter %.o,$^) -I $(INCLUDE_DIR)

 $(OBJ_DIR)Network.o:./Network.cpp $(INCLUDE_DIR)Network.hpp
	$(CXX) $(CXXFLAGS) $(DEPS) -c $< -o $@ -I $(INCLUDE_DIR)

 $(OBJ_DIR)Program.o:./Program.cpp $(INCLUDE_DIR)Program.hpp $(INCLUDE_DIR)Network.hpp
	$(CXX) $(CXXFLAGS) $(DEPS) -c $< -o $@  -I $(INCLUDE_DIR)

clean:
	rm -rf ../obj/*.o ../build/*