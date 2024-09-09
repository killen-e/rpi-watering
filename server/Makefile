CC := g++
SOURCES := $(shell find . -name "*.cpp")
NAME := server
BOOST_LOC := ../../boost_1_86_0/
ARGS := -pthread -fcoroutines

compile:
	${CC} -I ${BOOST_LOC} ${SOURCES} -o bin/${NAME} ${ARGS}
clean: 
	$(shell rm -rf bin/*.*)