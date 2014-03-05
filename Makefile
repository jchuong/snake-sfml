CXX = g++
CXXFLAGS = -Wall -MMD -g -std=c++11
EXEC = snake
OBJECTS = game.o board.o snake.o
DEPENDS = ${OBJECTS:.o=.d}

all: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -lsfml-graphics -lsfml-window -lsfml-system -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
