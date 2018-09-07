#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

#define WIDTH 1280
#define HEIGHT 720

class Display{

    public:

    static std::unique_ptr<sf::RenderWindow> _window;
    
    static void create();
     
    static void update();

    static void close();

    static void clear(float r = 0, float g = 0,float b = 0);

    static bool isOpen();

    static void checkForClose();

};

#endif // DISPLAY_HPP


