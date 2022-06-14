#include "Game.h"

Game::Game() {
    this->initVariables();
    this->initWindow();
    if (this->initTextures()) {
        this->initSprites();
    }
}

Game::~Game() {
    delete this->window;
}

void Game::update() {
    this->pollEvents();
    this->updateProgressBarTexture();
    //std::cout << "Speed: " << this->speed << std::endl;
    std::cout << this->board.at(0).size() << " " << this->board.size() << std::endl;
}

void Game::render() {
    this->window->clear(sf::Color::Blue);
    this->drawSprites();
    this->window->display();
}

bool Game::running() {
    return this->window->isOpen();
}

void Game::pollEvents() {
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
            case sf::Event::Closed:
                this->window->close();
                break;

            case sf::Event::MouseButtonPressed:
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    std::cout << "Left click" << std::endl;
                } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    std::cout << "Right click" << std::endl;
                }
                break;

            case sf::Event::KeyPressed:
                switch (this->ev.key.code) {
                    case sf::Keyboard::Escape:
                        this->window->close();
                        break;

                    case sf::Keyboard::P:
                        // Pause game
                        this->paused = !(this->paused);
                        break;

                    case sf::Keyboard::N:
                        // Next generation
                        if (paused) {

                        }
                        break;

                    case sf::Keyboard::F:
                        // Increase Speed
                        this->speed = std::min(maxSpeed, this->speed + 1);
                        break;

                    case sf::Keyboard::S:
                        // Decrease Speed
                        this->speed = std::max(minSpeed, this->speed - 1);
                        break;

                    case sf::Keyboard::D:
                        // Default Speed
                        this->speed = minSpeed;
                        break;

                    default:
                        break;
                }
            default:
                break;
        }
    }
}
void Game::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Game of Life", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(fps);
}


void Game::initVariables() {
    this->window = nullptr;
    this->paused = true;
    this->speed = minSpeed;

    std::vector<bool> v;
    for (int i = 0; i < (boardHeight / squareSize); i++) {
        v.clear();
        for (int j = 0; j < (boardWidth / squareSize); j++) {
            v.push_back(false);
        }
        this->board.push_back(v);
    }
}

bool Game::initTextures() {
    if (!this->sideBarTexture.loadFromFile("../textures/life-sidebar.png")) {
        return false;
    } if (!this->progressBarTextures[0].loadFromFile("../textures/progress-bar/life-progress-bar-1.png")) {
        return false;
    } if (!this->progressBarTextures[1].loadFromFile("../textures/progress-bar/life-progress-bar-2.png")) {
        return false;
    } if (!this->progressBarTextures[2].loadFromFile("../textures/progress-bar/life-progress-bar-3.png")) {
        return false;
    } if (!this->progressBarTextures[3].loadFromFile("../textures/progress-bar/life-progress-bar-4.png")) {
        return false;
    } if (!this->progressBarTextures[4].loadFromFile("../textures/progress-bar/life-progress-bar-5.png")) {
        return false;
    } if (!this->progressBarTextures[5].loadFromFile("../textures/progress-bar/life-progress-bar-6.png")) {
        return false;
    } if (!this->progressBarTextures[6].loadFromFile("../textures/progress-bar/life-progress-bar-7.png")) {
        return false;
    } if (!this->progressBarTextures[7].loadFromFile("../textures/progress-bar/life-progress-bar-8.png")) {
        return false;
    }

    return true;
}

void Game::initSprites() {
    this->sideBarSprite.setTexture(this->sideBarTexture);
    this->sideBarSprite.setPosition(windowWidth - sidebarWidth, 0);

    this->progressBar.setTexture(progressBarTextures[0]);
    this->progressBar.setPosition(windowWidth - sidebarWidth + 236, 508);
}

void Game::drawSprites() {
    this->window->draw(sideBarSprite);
    this->window->draw(progressBar);
}

void Game::updateProgressBarTexture() {
    this->progressBar.setTexture(this->progressBarTextures[speed - 1]);
}