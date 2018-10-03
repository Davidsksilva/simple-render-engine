#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "../includes/includes.hpp"
#include "../imgui/imgui-SFML.h"



class Display{

    public:

    static std::unique_ptr<sf::RenderWindow> m_window;
    
    static void create();
     
    static void update();

    static bool pollEvent( sf::Event t_event );

    static void close();

    static void clear( const GLfloat t_r = 0, const GLfloat t_g = 0, const GLfloat t_b = 0 );

    static bool isOpen();

    static void checkForClose();

    static GLfloat getHeight();

    constexpr static GLuint kWIDTH  = 1280;
    constexpr static GLuint kHEIGHT = 720;

};

#endif // DISPLAY_HPP


