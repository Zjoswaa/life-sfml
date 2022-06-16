#include "Game.h"

std::random_device generator;
std::uniform_int_distribution<int> randomWidth(0, (boardWidth / squareSize) - 1);
std::uniform_int_distribution<int> randomHeight(0, (boardHeight / squareSize) - 1);

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

    if (!paused) {
        this->frameCounter++;
        if (this->frameCounter >= fps / this->speed) {
            this->frameCounter = 0;
            updateBoard();
        }
    }
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
                            updateBoard();
                        } else {
                            this->paused = true;
                            this->pauseStatus.setTexture(this->playIconTexture);
                            this->frameCounter = 0;
                        }
                        break;

                    case sf::Keyboard::N:
                        // Next generation
                        if (paused) {
                            this->updateBoard();
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
                        if (paused) {
                            this->clearBoard();
                        }
                        break;

                    case sf::Keyboard::R:
                        // Add random squares
                        this->addRandomSquares();
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
    this->frameCounter = 0;

    std::vector<sf::RectangleShape> r;
    std::vector<bool> b;
    for (int i = 0; i < (boardHeight / squareSize); i++) {
        r.clear();
        b.clear();
        for (int j = 0; j < (boardWidth / squareSize); j++) {
            sf::RectangleShape square((sf::Vector2f((float)squareSize, (float)squareSize)));
            square.setFillColor(deadColor);
            square.setPosition((float)(j * squareSize), (float)(i * squareSize));
            r.push_back(square);
            b.push_back(false);
        }
        this->board.push_back(r);
        this->nextBoard.push_back(b);
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

int Game::getAliveNeighbours(int x, int y) {
    int count = 0;

    // Top left corner
    if (x == 0 && y == 0) {
        if (board[y][x + 1].getFillColor() == aliveColor) {
            count ++;
        } if (board[y + 1][x + 1].getFillColor() == aliveColor) {
            count++;
        } if (board[y + 1][x].getFillColor() == aliveColor) {
            count++;
        }
    }
    // Top right corner
    else if (x == (boardWidth / squareSize) - 1 && y == 0) {
        if (board[y][x - 1].getFillColor() == aliveColor) {
            count++;
        } if (board[y + 1][x - 1].getFillColor() == aliveColor) {
            count++;
        } if (board[y + 1][x].getFillColor() == aliveColor) {
            count++;
        }
    }
    // Bottom right corner
    else if (x == (boardWidth / squareSize) - 1 && y == (boardHeight / squareSize) - 1) {
        if (board[y - 1][x].getFillColor() == aliveColor) {
            count++;
        } if (board[y - 1][x - 1].getFillColor() == aliveColor) {
            count++;
        } if (board[y][x - 1].getFillColor() == aliveColor) {
            count++;
        }
    }
    // Bottom left corner
    else if (x == 0 && y == (boardHeight / squareSize) - 1) {
        if (board[y - 1][x].getFillColor() == aliveColor) {
            count++;
        } if (board[y - 1][x + 1].getFillColor() == aliveColor) {
            count++;
        } if (board[y][x + 1].getFillColor() == aliveColor) {
            count++;
        }
    }
    // Top row non-corners
    else if (y == 0) {
        if (board[y + 1][x - 1].getFillColor() == aliveColor) {
            count++;
        } if (board[y + 1][x].getFillColor() == aliveColor) {
            count++;
        } if (board[y + 1][x + 1].getFillColor() == aliveColor) {
            count++;
        } if (board[y][x - 1].getFillColor() == aliveColor) {
            count++;
        } if (board[y][x + 1].getFillColor() == aliveColor) {
            count++;
        }
    }
    // Right column non-corners
    else if (x == (boardWidth / squareSize) - 1) {
        if (board[y - 1][x - 1].getFillColor() == aliveColor) {
            count++;
        } if (board[y][x - 1].getFillColor() == aliveColor) {
            count++;
        } if (board[y + 1][x - 1].getFillColor() == aliveColor) {
            count++;
        } if (board[y - 1][x].getFillColor() == aliveColor) {
            count++;
        } if (board[y + 1][x].getFillColor() == aliveColor) {
            count++;
        }
    }
    // Bottom row non-corners
    else if (y == (boardHeight / squareSize) - 1) {
        if (board[y - 1][x - 1].getFillColor() == aliveColor) {
            count++;
        } if (board[y - 1][x].getFillColor() == aliveColor) {
            count++;
        } if (board[y - 1][x + 1].getFillColor() == aliveColor) {
            count++;
        } if (board[y][x - 1].getFillColor() == aliveColor) {
            count++;
        } if (board[y][x + 1].getFillColor() == aliveColor) {
            count++;
        }
    }
    // Left column non-corners
    else if (x == 0) {
        if (board[y - 1][x + 1].getFillColor() == aliveColor) {
            count++;
        } if (board[y][x + 1].getFillColor() == aliveColor) {
            count++;
        } if (board[y + 1][x + 1].getFillColor() == aliveColor) {
            count++;
        } if (board[y - 1][x].getFillColor() == aliveColor) {
            count++;
        } if (board[y + 1][x].getFillColor() == aliveColor) {
            count++;
        }
    }
    // Rest of the squares
    else {
        if (board[y - 1][x].getFillColor() == aliveColor) {
            count++;
        } if (board[y - 1][x + 1].getFillColor() == aliveColor) {
            count++;
        } if (board[y][x + 1].getFillColor() == aliveColor) {
            count++;
        } if (board[y + 1][x + 1].getFillColor() == aliveColor) {
            count++;
        } if (board[y + 1][x].getFillColor() == aliveColor) {
            count++;
        } if (board[y + 1][x - 1].getFillColor() == aliveColor) {
            count++;
        } if (board[y][x - 1].getFillColor() == aliveColor) {
            count++;
        } if (board[y - 1][x - 1].getFillColor() == aliveColor) {
            count++;
        }
    }
    return count;
}

void Game::updateBoard() {
    int aliveNeighbours;
    // Apply life rules
    for (int i = 0; i < board[0].size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            aliveNeighbours = getAliveNeighbours(i, j);
            // If square is alive
            if (board[j][i].getFillColor() == aliveColor) {
                if (aliveNeighbours < 2 || aliveNeighbours > 3) {
                    nextBoard[j][i] = false;
                } else {
                    nextBoard[j][i] = true;
                }
            }

            // If square is dead
            else {
                if (aliveNeighbours == 3) {
                    nextBoard[j][i] = true;
                } else {
                    nextBoard[j][i] = false;
                }
            }
        }
    }

    // Copy nextBoard to board
    for (int i = 0; i < board[0].size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            if (nextBoard[j][i]) {
                board[j][i].setFillColor(aliveColor);
            } else {
                board[j][i].setFillColor(deadColor);
            }
        }
    }
}

void Game::addRandomSquares() {
    for (int i = 0; i < randomSquaresCount; i++) {
        board[randomHeight(generator)][randomWidth(generator)].setFillColor(aliveColor);
    }
}