BIN=./bin
DOC=./doc
INCLUDE=./include
LIB=./lib
OBJ=./obj
SRC=./src

all: FLAGS= -Wall -g -std=c++11
grupos: FLAGS= -Wall -g -std=c++11 -DGRUPOS

all: $(OBJ)/cifras.o $(OBJ)/main.o
	g++ -o $(BIN)/RetoII $^ $(FLAGS)
grupos: $(OBJ)/cifras.o $(OBJ)/main.o
	g++ -o $(BIN)/Grupos $^ $(FLAGS)
$(OBJ)/cifras.o: $(SRC)/cifras.cpp
	g++ -o $(OBJ)/cifras.o -c $< -I$(INCLUDE) $(FLAGS)
$(OBJ)/main.o: $(SRC)/main.cpp
	g++ -o $(OBJ)/main.o -c $< -I$(INCLUDE) $(FLAGS)
clean:
	rm $(OBJ)/*.o
doc:
	doxygen $(DOC)/doxys/Doxyfile
