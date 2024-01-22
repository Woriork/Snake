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
    //Enemies spawn
    enSpawnTimerMax = 100.f;
    enSpawnTimer = enSpawnTimerMax;
    enMaxEnemies = 5;

    mouseHeld = false;
}

void Game::initWindow()
{
    videoMode.height = 920;
    videoMode.width = 1600;
    window = new sf::RenderWindow(sf::VideoMode(videoMode.width, videoMode.height), "Jakaœ fajna gierka", sf::Style::Resize | sf::Style::Close | sf::Style::Titlebar);
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

void Game::spawnEnemies()
{
    //Timer
    if (enSpawnTimer < enSpawnTimerMax) {
        enSpawnTimer += 1.f;
    }
    else {
        if (enemiesList.size() < enMaxEnemies) {
            enemiesList.push_back(Enemies());
            enSpawnTimer = 0.f;
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
    //for (int i = 0; i < objects.size(); i++) {

    //    objects[i].move(sf::Vector2f(1.f, 1.f));
    //}

}

void Game::updateEnemies()
{
    for (auto& enemy : enemiesList) {
        enemy.update(window);
    }
}

void Game::updateCollision()
{
    player.checkCollisionWithObjects(objects);
    enemies.checkCollisionWithObjects(objects);
    for (auto& enemy : enemiesList) {
        enemy.checkCollisionWithObjects(objects);
    }
    collissionPlayerEnemy();
}

bool Game::collissionPlayerEnemy()
{
    player.checkCollisionWithObjects(objects);

    // Kolizja miêdzy segmentem gracza a ogonem wê¿a przeciwnika
    for (size_t i = 0; i < enemiesList.size(); ++i) {
        auto& enemySegments = enemiesList[i].getSegments();
        sf::FloatRect playerHeadBounds = player.getSegments().front().getGlobalBounds();

        // SprawdŸ kolizjê miêdzy g³ow¹ gracza a ogonem wê¿a przeciwnika
        for (size_t j = 1; j < enemySegments.size(); ++j)
        {
            if (playerHeadBounds.intersects(enemySegments[j].getGlobalBounds()))
            {
                // Skróæ wê¿a gracza o 3 segmenty
                for (int k = 0; k < 3 && !player.getSegments().empty(); ++k) {
                    player.getSegments().pop_back();
                }

                // Usuñ wê¿a przeciwnika
                enemiesList.erase(enemiesList.begin() + i);
                --i; // Zmniejsz indeks, poniewa¿ usuniêto element z listy
                break; // Przerwij pêtlê, bo segment gracza ju¿ zosta³ usuniêty
            }
        }
    }

    // Kolizja miêdzy segmentem wê¿a przeciwnika a ogonem gracza
    for (size_t i = 0; i < enemiesList.size(); ++i) {
        auto& enemySegments = enemiesList[i].getSegments();
        sf::FloatRect playerTailBounds = player.getSegments().back().getGlobalBounds();

        // SprawdŸ kolizjê miêdzy ogonem gracza a segmentem wê¿a przeciwnika
        for (size_t j = 1; j < enemySegments.size(); ++j)
        {
            if (playerTailBounds.intersects(enemySegments[j].getGlobalBounds()))
            {
                // Usuñ danego wê¿a przeciwnika
                enemiesList.erase(enemiesList.begin() + i);
                --i; // Zmniejsz indeks, poniewa¿ usuniêto element z listy
                break; // Przerwij pêtlê, bo w¹¿ przeciwnika ju¿ zosta³ usuniêty
            }
        }
    }

    return false;
}

//functions
void Game::update() {
    this->pollEvents();

    spawnObjects();
    spawnEnemies();
    player.update(window);
    enemies.update(window);
    updateCollision();
    updateEnemies();

    if (endgame == false) {
        updateMousePositions();
        updateObjects();
    }
    //endgame condition
    if (player.getSegments().size() <= 0) {
        endgame = true;
    }

}

void Game::render() {
    window->clear();

    //draw game objects
    for (auto i : objects) {
        i.render(*this->window);
    }
    enemies.render(window);
    player.render(window);
    // Rysuj przeciwników
    for (auto& enemy : enemiesList) {
        enemy.render(window);
    }

    window->display();
}
