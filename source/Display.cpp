#include "Display.hpp"

// Creating static pointer to the window
std::unique_ptr<sf::RenderWindow> Display::_window;

void Display::create(){
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    // Creating the window
    _window = std::make_unique<sf::RenderWindow>( sf::VideoMode(WIDTH,HEIGHT), "OpenGL", sf::Style::Default, settings );
    // Setting framerate limit
    _window->setFramerateLimit( 60 );

    // Initialize glew
    glewInit();

    // Set Viewport
    glViewport( 0, 0, WIDTH, HEIGHT );

    glEnable    ( GL_DEPTH_TEST );
}

void Display::update(){

    // Updating the window
    _window->display();

}

void Display::close(){

    // Close the window
    _window->close();
}

void Display::clear(GLfloat r, GLfloat g,GLfloat b){

    // Clear Color Buffers
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    // Set background color
    glClearColor( r, g, b, 1 );
}

bool Display::isOpen(){

    // Return if the  window is open
    return _window->isOpen();
}

void Display::checkForClose(){
    
    sf::Event evnt;

    // Checking window events
    while( _window->pollEvent( evnt ) ){

        //Check if event is closing
        if( evnt.type == sf::Event::Closed ){
            _window->close();
        }
    }
}



