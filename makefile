CXXFLAGS = -g -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic

SOURCEDIR = source
BUILDIR = build

LIBS = -lGLEW -lsfml-graphics -lsfml-window -lsfml-system -lGL -std=c++11 -std=c++17 -lstdc++fs -L/usr/local/lib -lglfw -lrt -lXrandr -lGL -lm -ldl -lXrender -ldrm -lXdamage -lX11-xcb -lxcb-glx -lxcb-dri2 -lxcb-dri3 -lxcb-present -lxcb-sync -lxshmfence -lXxf86vm -lXfixes -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp

EXECUTABLE= run

SOURCES = $(wildcard $(SOURCEDIR)/*.cpp) \
		  $(wildcard $(SOURCEDIR)/shaders/*.cpp) \
		  $(wildcard $(SOURCEDIR)/models/*.cpp)\
		  $(wildcard $(SOURCEDIR)/includes/*.cpp)\
		  $(wildcard $(SOURCEDIR)/entities/*.cpp)\
		  $(wildcard $(SOURCEDIR)/engine_core/*.cpp)\
		  $(wildcard $(SOURCEDIR)/imgui/*.cpp)\
		  $(wildcard $(SOURCEDIR)/interface/*.cpp)
DEPENDENCIES = $(wildcard $(SOURCEDIR)/*.hpp) \
		       $(wildcard $(SOURCEDIR)/shaders/*.hpp) \
		       $(wildcard $(SOURCEDIR)/models/*.hpp) \
		  	   $(wildcard $(SOURCEDIR)/includes/*.hpp)\
		       $(wildcard $(SOURCEDIR)/entities/*.hpp)\
		  	   $(wildcard $(SOURCEDIR)/engine_core/*.hpp)\
		       $(wildcard $(SOURCEDIR)/imgui/*.h)\
		       $(wildcard $(SOURCEDIR)/interface/*.hpp)


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
