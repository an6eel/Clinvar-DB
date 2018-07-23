.PHONY: clean mrproper all

AR= ar
CXX= g++

#Carpetas

INC= include
SRC= src
OBJ= obj
BIN= bin

CXXFLAGS=  -std=c++11  -g -I./include

all : $(BIN)/clinvarDB

clean :
	echo "Limpiando..."
	-rm $(OBJ)/*.o

mrproper : clean
	-rm -rf $(BIN)/* ./doc/html/ ./doc/latex/

documentacion:
	doxygen doc/doxys/Doxyfile
	
#Archivos Objeto

$(OBJ)/mutacion.o : $(INC)/enfermedad.h $(INC)/mutacion.h $(SRC)/mutacion.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/mutacion.cpp

$(OBJ)/enfermedad.o : $(INC)/enfermedad.h $(SRC)/enfermedad.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/enfermedad.cpp
	
$(OBJ)/clinvar.o : $(INC)/clinvar.h $(INC)/mutacion.h $(INC)/enfermedad.h $(SRC)/clinvar.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/clinvar.cpp
	
$(OBJ)/clinvarDB.o : $(INC)/clinvar.h $(INC)/mutacion.h $(INC)/enfermedad.h $(SRC)/main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $(SRC)/main.cpp

# Mains

$(BIN)/clinvarDB : $(OBJ)/clinvarDB.o $(OBJ)/mutacion.o $(OBJ)/enfermedad.o $(OBJ)/clinvar.o
	$(CXX) $(CXXFLAGS)  -o  $@ $^


