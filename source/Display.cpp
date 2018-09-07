#include "Display.hpp"

std::unique_ptr<sf::RenderWindow> Display::_window;

void Display::create(){

    _window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WIDTH,HEIGHT),"OpenGL",sf::Style::Default);
    _window->setFramerateLimit(120);

    glewInit();
    glViewport(0,0,WIDTH,HEIGHT);

}

void Display::update(){

    _window->display();

}

void Display::close(){

    _window->close();
}

void Display::clear(float r, float g,float b){

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(r,g,b,1);
}

bool Display::isOpen(){

    return _window->isOpen();
}

void Display::checkForClose(){
    
    sf::Event evnt;

    while(_window->pollEvent(evnt)){
        if(evnt.type == sf::Event::Closed){
            _window->close();
        }
    }
}




