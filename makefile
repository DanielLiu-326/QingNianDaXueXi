CXX=g++
CXXFLAGS= -std=c++11 -Wall -pedantic
OBJ_DIR = ./obj/
INCLUDE_DIR = ./include/
DEPS = -lcurl
BUILD_DIR = ./build/
SRC_DIR = ./src/
$(BUILD_DIR)QNDXX_Program:$(SRC_DIR)main.cpp $(OBJ_DIR)Network.o $(OBJ_DIR)Program.o $(INCLUDE_DIR)Program.hpp init
	$(CXX) $(CXXFLAGS) $(DEPS) $< -o $@ $(filter %.o,$^) -I $(INCLUDE_DIR)

 $(OBJ_DIR)Network.o:$(SRC_DIR)Network.cpp $(INCLUDE_DIR)Network.hpp init
	$(CXX) $(CXXFLAGS) $(DEPS) -c $< -o $@ -I $(INCLUDE_DIR)

 $(OBJ_DIR)Program.o:$(SRC_DIR)Program.cpp $(INCLUDE_DIR)Program.hpp $(INCLUDE_DIR)Network.hpp init
	$(CXX) $(CXXFLAGS) $(DEPS) -c $< -o $@  -I $(INCLUDE_DIR)
init:
	sh ./init.sh
clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)
