CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -Werror -MMD -Werror=vla
EXEC = a4q5
OBJECTS = main.o textdisplay.o grid.o cell.o window.o graphicsdisplay.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
