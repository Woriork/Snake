#include "Game.h"
//private funcions
void Game::initVariables()
{
	this->window = nullptr;
}
void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Moja fajna gierka", sf::Style::Resize | sf::Style::Close | sf::Style::Titlebar);
}
//konstruktor
Game::Game() {
	this->initVariables();
	this->initWindow();
}
//dekonstruktor
Game::~Game() {
	delete this->window;
}
const bool Game::running() const
{
	return this->window->isOpen();
}
//Accessors


void Game::pollEvents()
{
    // Event polling
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        default:
            break;
        }
    }
}

//functions
void Game::update() {
    this->pollEvents();
}
void Game::render() {
    /*
    *   return void
    *   clear old frame
    *   render objects
    *   display frame in window
        Renders the game objects.
    */
    this->window->clear(sf::Color(255,0,0,255));
    //draw game
    this->window->display();
}