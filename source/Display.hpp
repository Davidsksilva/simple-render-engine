#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "includes.hpp"

#define WIDTH 1280
#define HEIGHT 720

class Display{

    public:

    static std::unique_ptr<sf::RenderWindow> _window;
    
    static void create();
     
    static void update();

    static void close();

    static void clear( GLfloat r = 0, GLfloat g = 0, GLfloat b = 0 );

    static bool isOpen();

    static void checkForClose();

};

#endif // DISPLAY_HPP


