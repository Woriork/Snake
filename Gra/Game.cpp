#include "Game.h"
//private funcions
void Game::initVariables()
{
    this->window = nullptr;
    //Game logic
    this->endgame = false;
    this->points = 0;
    this->health = 10;
    this->enemySpawnTimer = 0.f;
    this->enemySpawnTimerMax = 1000.f;
    this->maxEnemies = 10;
    this->mouseHeld = false;
}
void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Moja fajna gierka", sf::Style::Resize | sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(144);
}
void Game::initEnemies()
{   
    this->enemy.setPosition(0.f,0.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setFillColor(sf::Color::Cyan);
 //   this->enemy.setOutlineColor(sf::Color::Green);
 //   this->enemy.setOutlineThickness(1.f);
}
//konstruktor
Game::Game() {
	this->initVariables();
	this->initWindow();
    this->initEnemies();
}
//dekonstruktor
Game::~Game() {
	delete this->window;
}
const bool Game::running() const
{
	return this->window->isOpen();
}
const bool Game::getEndGame() const
{
    return this->endgame;
}
//Accessors


void Game::spawnEnemies()
{
    /*
    @return void
    spawns enemies and sets their colors and position
    -set random position
    -sets a random color
    -adds enemy to the vector
    */
    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().y - this->enemy.getSize().y))
        );
    this->enemy.setFillColor(sf::Color::Green);
    this->enemies.push_back(this->enemy);
}

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

void Game::updateMousePositions()
{
    /*
    @return void
    update the mouse positions:
       - Mouse position relative to window(Vector2i)
    */

    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    //map to view
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{
    /*
     @return void
     Updates the enemy spawn timer and spawn enemies
     when the total amount of enemies is smaller than max
     Moves the enemies downwards:
     Removes the enemies at the edge of the screen /only in y now
    */

    if (this->enemies.size() < this->maxEnemies) {

        if (this->enemySpawnTimer >= enemySpawnTimerMax) {
            //spawn the enemy and reset the timer
            this->spawnEnemies();
            this->enemySpawnTimer = 0.f;
        }
        else {
            this->enemySpawnTimer += 1.f;
        }
    }
    //Move the enemies and updating
    for (int i = 0; i < this->enemies.size(); i++) {
        bool delated = false;

        this->enemies[i].move(0.f, 1.f);

        //if enemy is past the bottom of the screen
        if (this->enemies[i].getPosition().y > window->getSize().y) {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
        }

    }
    //check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        if (this->mouseHeld == false) {

            this->mouseHeld = true;
            bool delated = false;
            for (size_t i = 0; i < this->enemies.size() && delated == false; i++) {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {

                    //Delate the enemy
                    delated = true;
                    this->enemies.erase(this->enemies.begin() + i);

                    //Gain points
                    this->points += 1.f;
                }
            }
        }
        
    }
    else {
        this->mouseHeld = false;
    }
}
//functions
void Game::update() {
    this->pollEvents();
    //update mouse position
    //relative to the screen - useeeeeelessssss
    //std::cout << "Mouse pos:" << sf::Mouse::getPosition().x << sf::Mouse::getPosition().y << '\n';
    //relative to the window
    //std::cout << "Mouse pos:" 
    //   << sf::Mouse::getPosition(*this->window).x 
    //    << sf::Mouse::getPosition(*this->window).y << '\n';
    if (this->endgame == false) {
        this->updateMousePositions();
        this->updateEnemies();
    }
    //endgame condition
    if (this->health <= 0) {
        this->endgame = true;
    }
}
void Game::renderEnemies()
{   
    //rendering the enemies
    for (auto& e : this->enemies) {
        this->window->draw(e);
    }
}
void Game::render() {
    /*
    *   return void
    *   clear old frame
    *   render objects
    *   display frame in window
        Renders the game objects.
    */
    this->window->clear();
    //draw game objects
    this->renderEnemies();

    this->window->display();
}
