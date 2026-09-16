CPP_COMPILER=g++
CPP_FLAGS=-fsanitize=address

OBJECT_DIR=obj
LOCAL_LIB_DIR=src/lib

MAIN_DIR=src/main

MAIN_FILE_NAME=clicalc

EXECUTABLE=bin/${MAIN_FILE_NAME}
MAIN_FILE=${MAIN_FILE_NAME}.cpp

ARGS=

STDIN=tests/testcases/test.txt
STDOUT=tests/testoutput/out.txt

LOCAL_LIB_SOURCE_FILES=lexerlib.cpp parserlib.cpp calculatorlib.cpp

OBJECT_FILES=${LOCAL_LIB_SOURCE_FILES:%.cpp=${OBJECT_DIR}/%.opp} ${MAIN_FILE:%.cpp=${OBJECT_DIR}/%.opp}

all: build

# Compiles relevant c source file found in lib into the obj file.
${OBJECT_DIR}/%.opp: ${LOCAL_LIB_DIR}/%.cpp
	${CPP_COMPILER} -c $^ -o $@


${OBJECT_DIR}/%.opp: ${MAIN_DIR}/%.cpp
	${CPP_COMPILER} -c $^ -o $@

# build
${EXECUTABLE}: ${OBJECT_FILES}
	${CPP_COMPILER} ${CPP_FLAGS} -o $@ $^ 


build: ${EXECUTABLE}

run: ${EXECUTABLE}
	${EXECUTABLE} ${ARGS} < ${STDIN} > ${STDOUT}

clean:
	rm ${EXECUTABLE} ${OBJECT_DIR}/*.opp