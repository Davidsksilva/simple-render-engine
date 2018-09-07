CXXFLAGS = -g -Wall -pedantic

SOURCEDIR = source
BUILDIR = build

LIBS = -lGLEW -lsfml-graphics -lsfml-window -lsfml-system -lGL

EXECUTABLE= run

SOURCES = $(wildcard $(SOURCEDIR)/*.cpp)
DEPENDENCIES = $(wildcard $(SOURCEDIR)/*.hpp)

_OBJECTS = $(SOURCES:.cpp=.o)
OBJECTS = $(patsubst $(SOURCEDIR)/%,$(BUILDIR)/%,$(_OBJECTS))

$(BUILDIR)/%.o : $(SOURCEDIR)/%.cpp $(DEPENDENCIES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXECUTABLE) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

.PHONY : cleanobj clean

cleanobj:
	rm $(OBJECTS)
clean:
	rm $(EXECUTABLE)