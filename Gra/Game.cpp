#include "Game.h"
//private funcions
void Game::initVariables()
{
    window = nullptr;
    //Game logic
    endgame = false;
    points = 0;
    health = 10;
    //
    enemySpawnTimer = 0.f;
    enemySpawnTimerMax = 1000.f;
    maxEnemies = 10;
    //
    spawnTimerMax = 10.f;
    spawnTimer = spawnTimerMax;
    maxObjects = 10;

    mouseHeld = false;
}
void Game::initWindow()
{
	videoMode.height = 600;
	videoMode.width = 800;
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Moja fajna gierka", sf::Style::Resize | sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(144);
}
//
void Game::initEnemies()
{   
    enemy.setPosition(0.f,0.f);
    enemy.setSize(sf::Vector2f(100.f, 100.f));
    enemy.setFillColor(sf::Color::Cyan);

}
//

//konstruktor
Game::Game() {
	initVariables();
	initWindow();
    //
    initEnemies();
    //
}
//dekonstruktor
Game::~Game() {
	delete window;
}
const bool Game::running() const
{
	return window->isOpen();
}
const bool Game::getEndGame() const
{
    return endgame;
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
    enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - enemy.getSize().x)),
        static_cast<float>(rand() % static_cast<int>(window->getSize().y - enemy.getSize().y))
        );
    enemy.setFillColor(sf::Color::Green);
    enemies.push_back(enemy);
}

void Game::spawnObjects()
{
    //Timer
    if (spawnTimer < spawnTimerMax) {
        spawnTimer += 1.f;
    }
    else {
        if (objects.size() < maxObjects) {
            objects.push_back(Object(*this->window));
            spawnTimer = 0.f;
        } 
    }
}

void Game::pollEvents()
{
    // Event polling
    while (window->pollEvent(ev)) {
        switch (ev.type) {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            if (ev.key.code == sf::Keyboard::Escape)
                window->close();
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

    mousePosWindow = sf::Mouse::getPosition(*this->window);
    //map to view
    mousePosView = window->mapPixelToCoords(mousePosWindow);
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

    if (enemies.size() < maxEnemies) {

        if (enemySpawnTimer >= enemySpawnTimerMax) {
            //spawn the enemy and reset the timer
            spawnEnemies();
            enemySpawnTimer = 0.f;
        }
        else {
            enemySpawnTimer += 1.f;
        }
    }
    //Move the enemies and updating
    for (int i = 0; i < enemies.size(); i++) {
        bool delated = false;
        
        float moveX = static_cast<float>(std::rand() % 3 - 1); // -1, 0, or 1 for horizontal movement
        float moveY = static_cast<float>(std::rand() % 3 - 1); // -1, 0, or 1 for vertical movement

        enemies[i].move(moveX, moveY);

        //if enemy is past the bottom of the screen
        if (enemies[i].getPosition().y > window->getSize().y) {
            enemies.erase(enemies.begin() + i);
            health -= 1;
        }
        //if player touch the enemy

    }
    //check if clicked upon
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        if (mouseHeld == false) {

            mouseHeld = true;
            bool delated = false;
            for (size_t i = 0; i < this->enemies.size() && delated == false; i++) {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {

                    //Delate the enemy
                    delated = true;
                    enemies.erase(this->enemies.begin() + i);

                    //Gain points
                    points += 1.f;
                }
            }
        }
        
    }
    else {
        mouseHeld = false;
    }
}
//functions
void Game::update() {
    this->pollEvents();
    spawnObjects();
    player.update(window);
    //update mouse position
    //relative to the screen - useeeeeelessssss
    //std::cout << "Mouse pos:" << sf::Mouse::getPosition().x << sf::Mouse::getPosition().y << '\n';
    //relative to the window
    //std::cout << "Mouse pos:" 
    //   << sf::Mouse::getPosition(*this->window).x 
    //    << sf::Mouse::getPosition(*this->window).y << '\n';
    if (endgame == false) {
        updateMousePositions();
        updateEnemies();
    }
    //endgame condition
    if (health <= 0) {
        endgame = true;
    }
}
void Game::renderEnemies()
{   
    //rendering the enemies
    for (auto& e : this->enemies) {
        window->draw(e);
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
    window->clear();

    //draw game objects

    for (auto i : objects) {
        i.render(*this->window);
    }

    player.render(window);
    renderEnemies();

    window->display();
}
