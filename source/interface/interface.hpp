#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "../includes/includes.hpp"
#include "../engine_core/master_renderer.hpp"
#include "../engine_core/display.hpp"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../engine_core/display.hpp"
#include <experimental/filesystem>
#include "../engine_core/loader.hpp"
namespace fs = std::experimental::filesystem;

class UserInterface{

    private:

    MasterRenderer& m_master_renderer;
    bool m_show_dock;
    bool m_show_demo_window;
    GLfloat m_color[3];
    GLfloat m_light_color[3];

    public:
    
    UserInterface( MasterRenderer& t_master_renderer);

    void startInterface( std::vector<Entity*>& t_entities );
    void loadStyle();

};


#endif // INTERFACE_HPP