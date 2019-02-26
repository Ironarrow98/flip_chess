CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror -MMD -Werror=vla
EXEC = a4q4
OBJECTS = main.o textdisplay.o grid.o cell.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
