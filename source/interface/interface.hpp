#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "../includes/includes.hpp"
#include "../imgui/imgui.h"
#include "../imgui/imgui-SFML.h"
#include "../engine_core/master_renderer.hpp"
#include <SFML/System/Clock.hpp>

class UserInterface{

    private:

    MasterRenderer& m_master_renderer;
    sf::Clock m_delta_clock;
    bool m_show_dock;
    GLfloat m_color[3];

    public:
    
    UserInterface( MasterRenderer& t_master_renderer, sf::Clock& t_delta_clock );

    void startInterface();

};


#endif // INTERFACE_HPP