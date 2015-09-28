BIN_DIR = bin
CC = g++
CPPFLAGS = -Wall -g
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all: $(BIN_DIR)/LListIntTest $(BIN_DIR)/SetTest $(BIN_DIR)/pgindex
	-@echo "--- All Built!---"

$(BIN_DIR)/llistint.o: llistint.h llistint.cpp $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c llistint.cpp -o $@

$(BIN_DIR)/LListIntTest: LListIntTest.cpp $(BIN_DIR)/llistint.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/test_pro3: test_pro3.cpp $(BIN_DIR)/llistint.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@	

$(BIN_DIR)/pgindex: pgindex.cpp $(BIN_DIR)/llistint.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@		

$(BIN_DIR)/SetTest: SetTest.cpp $(BIN_DIR)/setint.o $(BIN_DIR)/llistint.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@		

$(BIN_DIR)/setint.o: setint.h setint.cpp $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c setint.cpp -o $@	

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

PHONY: clean copytest

copytest: $(BIN_DIR)/LListIntTest
	-@$(BIN_DIR)/LListIntTest
	-@echo "--- All Tested!---"

test_pro3: $(BIN_DIR)/test_pro3
	-@$(BIN_DIR)/test_pro3
	-@echo "--- All Tested!---"	

settest: $(BIN_DIR)/SetTest
	-@$(BIN_DIR)/SetTest
	-@echo "--- Set Built!---"


pgindex: $(BIN_DIR)/pgindex
	-@$(BIN_DIR)/pgindex
	-@echo "--- Map Built!---"
 
clean:
	rm -rf $(BIN_DIR)
	-@echo "--- All Clean!---"