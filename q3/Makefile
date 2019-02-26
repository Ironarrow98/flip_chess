CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror -MMD -Werror=vla
EXEC = a4q3
OBJECTS = main.o basic.o image.o decorator.o flip.o rotate.o sepia.o exception.o ppm.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
