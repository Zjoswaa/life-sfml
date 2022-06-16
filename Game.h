#ifndef GAME_H
#define GAME_H

#include <cmath>
#include <iostream>
#include <random>
#include <windows.h>
#include <SFML/Graphics.hpp>
#include "constants.h"

class Game {
public:
    Game();
    ~Game();

    void update();
    void render();
    bool running();

private:
    sf::RenderWindow* window;
    sf::Event ev;
    //std::vector<std::vector<bool>> board;
    std::vector<std::vector<sf::RectangleShape>> board;
    std::vector<std::vector<bool>> nextBoard;

    bool paused;
    int speed;
    int frameCounter;

    sf::Texture sideBarTexture;
    sf::Sprite sideBarSprite;

    sf::Texture progressBarTextures[8];
    sf::Sprite progressBar;

    sf::Texture pauseIconTexture;
    sf::Texture playIconTexture;
    sf::Sprite pauseStatus;

    void pollEvents();
    void initWindow();
    void initVariables();
    bool initTextures();
    void initSprites();
    void drawSprites();
    void updateProgressBarTexture();
    void clearBoard();
    // Sets the square that the mouse is currently on alive or dead
    void setSquareAtMouse(bool alive);
    // Gets the amount of alive neighbours of the square at (x, y)
    int getAliveNeighbours(int x, int y);
    // Updates the board to the next generation
    void updateBoard();
    void addRandomSquares();
};

#endif