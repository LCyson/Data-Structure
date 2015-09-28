BIN_DIR = tests
CXX = g++
CPPFLAGS = -Wall -g

all: $(BIN_DIR)/Pro5 $(BIN_DIR)/Pro7 $(BIN_DIR)/Pro3 $(BIN_DIR)/Pro4

$(BIN_DIR)/Pro5: $(BIN_DIR)/stackdbl.o $(BIN_DIR)/llistdbl.o $(BIN_DIR)/test_pro5.cpp 
	$(CXX) $(CPPFLAGS) $(BIN_DIR)/test_pro5.cpp $(BIN_DIR)/stackdbl.o $(BIN_DIR)/llistdbl.o -o $(BIN_DIR)/Pro5

$(BIN_DIR)/Pro7: $(BIN_DIR)/stackdbl.o $(BIN_DIR)/llistdbl.o postfix.cpp
	$(CXX) $(CPPFLAGS) postfix.cpp $(BIN_DIR)/llistdbl.o $(BIN_DIR)/stackdbl.o -o $(BIN_DIR)/Pro7

$(BIN_DIR)/Pro3: $(BIN_DIR)/llistdbl.o $(BIN_DIR)/test_pro3.cpp
	$(CXX) $(CPPFLAGS) $(BIN_DIR)/test_pro3.cpp $(BIN_DIR)/llistdbl.o -o $(BIN_DIR)/Pro3

$(BIN_DIR)/Pro4: $(BIN_DIR)/alistint.o $(BIN_DIR)/test_pro4.cpp
	$(CXX) $(CPPFLAGS) $(BIN_DIR)/test_pro4.cpp $(BIN_DIR)/alistint.o -o $(BIN_DIR)/Pro4

$(BIN_DIR)/stackdbl.o: stackdbl.h stackdbl.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c stackdbl.cpp -o $(BIN_DIR)/stackdbl.o

$(BIN_DIR)/llistdbl.o: llistdbl.h llistdbl.cpp  $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c llistdbl.cpp -o $(BIN_DIR)/llistdbl.o

$(BIN_DIR)/alistint.o: alistint.h alistint.cpp  $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c alistint.cpp -o $(BIN_DIR)/alistint.o

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

PHONY: clean
clean:
	rm -rf $(BIN_DIR)