AutomatedMakefile = am
CC = g++
CXXFLAGS = -Wno-deprecated-declarations -g -O0

PROJECT_PATH = $(PROJECT_DIR)
GUI_PATH = $(DRIVE_LETTER)/TDM-GCC-64/wxWidgets-3.1.0

INC_DIRS = -I$(PROJECT_PATH)/CSC2110
LIB_DIRS = -L$(PROJECT_PATH)/CSC2110 -L$(GUI_PATH)/lib/gcc510TDM_x64_dll
LDFLAGS = -Wl,-Bstatic
LIBS = $(LDFLAGS) -lCSC2110 

COMPILE = $(CC) $(CXXFLAGS) $(INC_DIRS) -c 
LINK = $(CC) $(CXXFLAGS) $(LIB_DIRS)

FILES =PQSortDriver.o
EXECUTABLE = PQSort.exe

all: Graph

Graph: $(FILES)
	 $(LINK) $(FILES) $(LIBS) -o $(EXECUTABLE)

PQSortDriver.o:	
	$(COMPILE) PQSortDriver.cpp
