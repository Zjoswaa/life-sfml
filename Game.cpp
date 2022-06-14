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
    //std::cout << this->board.at(0).size() << " " << this->board.size() << std::endl;
    //std::cout << currentSquareSize << std::endl;
}

void Game::render() {
    this->window->clear(sf::Color::White);
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
                    this->setSquareAtMouse(true);
                } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    this->setSquareAtMouse(false);
                }
                break;

            case sf::Event::MouseWheelMoved:
                if (this->ev.mouseWheel.delta < 0) {
                    // Decrease Speed
                    this->speed = std::max(minSpeed, this->speed - 1);
                } else {
                    // Increase Speed
                    this->speed = std::min(maxSpeed, this->speed + 1);
                }

            case sf::Event::KeyPressed:
                switch (this->ev.key.code) {
                    case sf::Keyboard::Escape:
                        this->window->close();
                        break;

                    case sf::Keyboard::P:
                        // Pause game
                        if (this->paused) {
                            this->paused = false;
                            this->pauseStatus.setTexture(this->pauseIconTexture);
                        } else {
                            this->paused = true;
                            this->pauseStatus.setTexture(this->playIconTexture);
                        }
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

                    case sf::Keyboard::C:
                        // Clear board
                        this->clearBoard();
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

    std::vector<sf::RectangleShape> v;
    for (int i = 0; i < (boardHeight / squareSize); i++) {
        v.clear();
        for (int j = 0; j < (boardWidth / squareSize); j++) {
            sf::RectangleShape square((sf::Vector2f((float)squareSize, (float)squareSize)));
            square.setFillColor(deadColor);
            square.setPosition((float)(j * squareSize), (float)(i * squareSize));
            v.push_back(square);
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
    } if (!this->pauseIconTexture.loadFromFile("../textures/life-pause-icon.png")) {
        return false;
    } if (!this->playIconTexture.loadFromFile("../textures/life-play-icon.png")) {
        return false;
    }

    return true;
}

void Game::initSprites() {
    this->sideBarSprite.setTexture(this->sideBarTexture);
    this->sideBarSprite.setPosition(windowWidth - sidebarWidth, 0);

    this->progressBar.setTexture(progressBarTextures[0]);
    this->progressBar.setPosition(windowWidth - sidebarWidth + 236, 508);

    this->pauseStatus.setTexture(playIconTexture);
    this->pauseStatus.setPosition(windowWidth - sidebarWidth + 16, 452);
}

void Game::drawSprites() {
    this->window->draw(sideBarSprite);
    this->window->draw(progressBar);
    this->window->draw(pauseStatus);

    for (int i = 0; i < (boardHeight / squareSize); i++) {
        for (int j = 0; j < (boardWidth / squareSize); j++) {
            this->window->draw(this->board[i][j]);
        }
    }
}

void Game::updateProgressBarTexture() {
    this->progressBar.setTexture(this->progressBarTextures[speed - 1]);
}

void Game::clearBoard() {
    for (int i = 0; i < (boardHeight / squareSize); i++) {
        for (int j = 0; j < (boardWidth / squareSize); j++) {
            this->board[i][j].setFillColor(deadColor);
        }
    }
}

void Game::setSquareAtMouse(bool alive) {
    if (floor((sf::Mouse::getPosition(*this->window).x) / squareSize) >= 0
    && floor((sf::Mouse::getPosition(*this->window).x) / squareSize) < (float)board[0].size()
    && floor((sf::Mouse::getPosition(*this->window).y) / squareSize) >= 0
    && floor((sf::Mouse::getPosition(*this->window).y) / squareSize) < (float)board.size()) {
        if (alive) {
            board[floor((sf::Mouse::getPosition(*this->window).y) / squareSize)]
            [floor((sf::Mouse::getPosition(*this->window).x) / squareSize)].setFillColor(aliveColor);
        } else {
            board[floor((sf::Mouse::getPosition(*this->window).y) / squareSize)]
            [floor((sf::Mouse::getPosition(*this->window).x) / squareSize)].setFillColor(deadColor);
        }
    }
}