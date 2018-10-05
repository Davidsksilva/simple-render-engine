#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "../includes/includes.hpp"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include <stdio.h>

#include <GL/glew.h>    // Initialize with glewInit()

#include <GLFW/glfw3.h> // Include glfw3.h after our OpenGL definitions


class Display{

    public:

    //static std::unique_ptr<sf::RenderWindow> m_window;
    static GLFWwindow* window;
    static int create(GLuint t_w, GLuint t_h, const char * t_title);
    static void update();

    //static bool pollEvent( sf::Event t_event );

    static void close();

    static void clear( const GLfloat t_r = 0, const GLfloat t_g = 0, const GLfloat t_b = 0 );

    static bool isOpen();

    //static void checkForClose();

    static GLfloat getHeight();

    constexpr static GLuint kWIDTH  = 1280;
    constexpr static GLuint kHEIGHT = 720;

};

#endif // DISPLAY_HPP


