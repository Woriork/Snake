#include "Game.h"

//private funcions
void Game::initVariables()
{
    window = nullptr;
    //Game logic
    endgame = false;
    points = 0;
    //Objects spawn
    spawnTimerMax = 100.f;
    spawnTimer = spawnTimerMax;
    maxObjects = 10;

    mouseHeld = false;
}

void Game::initWindow()
{
    videoMode.height = 920;
    videoMode.width = 1600;
    window = new sf::RenderWindow(sf::VideoMode(videoMode.width, videoMode.height), "Moja fajna gierka", sf::Style::Resize | sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(100);
}

//constructors /destructors
Game::Game() {
    initVariables();
    initWindow();
}

Game::~Game() {
    delete window;
}

//Accessors
const bool Game::running() const
{
    return window->isOpen();
}

const bool Game::getEndGame() const
{
    return endgame;
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
    mousePosWindow = sf::Mouse::getPosition(*this->window);
    mousePosView = window->mapPixelToCoords(mousePosWindow);
}

void Game::updateObjects()
{
    //Updates the objexts spawn timer and spawn enemies
    //when the total amount of enemies is smaller than max
    for (size_t i = 0; i < objects.size(); i++)
    {
        objects[i].update(*window);
        objects[i].checkCollision(*window);

        if (objects[i].getBounds().top > window->getSize().y)
        {
            objects.erase(objects.begin() + i);
        }
    }
    //Move the objects and updating
    for (int i = 0; i < objects.size(); i++) {

        objects[i].move(sf::Vector2f(1.f, 1.f));
    }
}

void Game::updateCollision()
{
    // Check collision Player - Objects
    auto it = objects.begin();
    while (it != objects.end()) {
        bool collisionDetected = false;

        for (size_t j = 0; j < player.getSegments().size(); j++) {
            if (player.getSegments()[j].getGlobalBounds().intersects(it->getBounds())) {
                player.grow(); 
                collisionDetected = true;
                break;
            }
        }

        if (collisionDetected) {
            it = objects.erase(it);  // Usuñ element i zwróæ iterator wskazuj¹cy na kolejny element
        } else {
            ++it;  // PrzejdŸ do kolejnego elementu
        }
    }
}

//functions
void Game::update() {
    this->pollEvents();

    spawnObjects();
    player.update(window);
    updateCollision();

    if (endgame == false) {
        updateMousePositions();
        updateObjects();
    }
    //endgame condition
    if (player.hp <= 0) {
        endgame = true;
    }
}

void Game::render() {
    window->clear();

    //draw game objects
    for (auto i : objects) {
        i.render(*this->window);
    }
    player.render(window);

    window->display();
}
