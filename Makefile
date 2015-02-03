AutomatedMakefile = am
CC = g++

FILES = 
EXECUTABLE = 

PROJECT_PATH = $(PROJECT_DIR)

INC_DIRS = 
LIB_DIRS = 
LIBS = 

COMPILE = $(CC) $(INC_DIRS) -c
LINK = $(CC) $(LIB_DIRS) -o

all: Project

Project: 		$(FILES)
			$(LINK) $(EXECUTABLE) $(FILES) $(LIBS)



