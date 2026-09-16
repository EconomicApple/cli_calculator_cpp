CPP_COMPILER=g++
CPP_FLAGS=

EXECUTABLE=bin/main

OBJECT_DIR=obj
LOCAL_LIB_DIR=src/lib
MAIN_DIR=src/main

MAIN_FILE=main.cpp

MAIN_OBJ=main.opp

ARGS=

STDIN=tests/testcases/test.txt
STDOUT=tests/testoutput/out.txt

LOCAL_LIB_SOURCE_FILES=lexerlib.cpp parserlib.cpp

OBJECT_FILES=${LOCAL_LIB_SOURCE_FILES:%.cpp=${OBJECT_DIR}/%.opp} ${OBJECT_DIR}/${MAIN_OBJ}

all: build

# Compiles relevant c source file found in lib into the obj file.
${OBJECT_DIR}/%.opp: ${LOCAL_LIB_DIR}/%.cpp
	${CPP_COMPILER} -c $^ -o $@


${OBJECT_DIR}/${MAIN_OBJ}: ${MAIN_DIR}/${MAIN_FILE}
	${CPP_COMPILER} -c $^ -o $@

# build
${EXECUTABLE}: ${OBJECT_FILES}
	${CPP_COMPILER} ${CPP_FLAGS} -o $@ $^ 


build: ${EXECUTABLE}

run: ${EXECUTABLE}
	${EXECUTABLE} ${ARGS} < ${STDIN} > ${STDOUT}

clean:
	rm ${EXECUTABLE} ${OBJECT_DIR}/*.opp