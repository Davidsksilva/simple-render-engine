#include "display.hpp"

// Creating static pointer to the window
std::unique_ptr<sf::RenderWindow> Display::m_window;

void Display::create(){

    sf::ContextSettings settings;

    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    // Creating the window
    m_window = std::make_unique<sf::RenderWindow>( sf::VideoMode(kWIDTH,kHEIGHT), "OpenGL", sf::Style::Default, settings );
    // Setting framerate limit
    m_window->setFramerateLimit( 60 );
    m_window->setVerticalSyncEnabled( true );

    // Initialize glew
    glewInit();

    // Set Viewport
    glViewport( 0, 0, kWIDTH, kHEIGHT );

    glEnable    ( GL_DEPTH_TEST );
    glEnable    ( GL_CULL_FACE  );
    glCullFace  ( GL_BACK );
}

void Display::update(){

    // Updating the window
    m_window->display();

}

void Display::close(){

    // Close the window
    m_window->close();
}

void Display::clear( const GLfloat t_r, const GLfloat t_g, const GLfloat t_b ){

    // Clear Color Buffers
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    // Set background color
    glClearColor( t_r, t_g, t_b, 1 );
}

bool Display::isOpen(){

    // Return if the  window is open
    return m_window->isOpen();
}
bool Display::pollEvent( sf::Event t_event ){

    return m_window->pollEvent( t_event );
}
void Display::checkForClose(){
    
    sf::Event evnt;

    // Checking window events
    while( m_window->pollEvent( evnt ) ){
        ImGui::SFML::ProcessEvent(evnt);
        //Check if event is closing
        if( evnt.type == sf::Event::Closed ){
            m_window->close();
        }
    }


}



