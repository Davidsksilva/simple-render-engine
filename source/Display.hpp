#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "includes.hpp"



class Display{

    public:

    static std::unique_ptr<sf::RenderWindow> _window;
    
    static void create();
     
    static void update();

    static void close();

    static void clear( GLfloat r = 0, GLfloat g = 0, GLfloat b = 0 );

    static bool isOpen();

    static void checkForClose();

    static GLfloat getHeight();

    constexpr static GLuint WIDTH  = 1280;
    constexpr static GLuint HEIGHT = 720;

};

#endif // DISPLAY_HPP


