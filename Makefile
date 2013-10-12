BIN=./bin
DOC=./doc
INCLUDE=./include
LIB=./lib
OBJ=./obj
SRC=./src

all: $(OBJ)/cifras.o $(OBJ)/main.o
	g++ -o $(BIN)/RetoII $^
$(OBJ)/cifras.o: $(SRC)/cifras.cpp 
	g++ -o $(OBJ)/cifras.o -c $< -I$(INCLUDE)
$(OBJ)/main.o: $(SRC)/main.cpp 
	g++ -o $(OBJ)/main.o -c $< -I$(INCLUDE)
clean:
	rm $(OBJ)/*.o
doc:
	doxygen $(DOC)/doxys/Doxyfile
