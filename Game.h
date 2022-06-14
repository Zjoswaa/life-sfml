#ifndef GAME_H
#define GAME_H

#include <iostream>
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
    std::vector<std::vector<bool>> board;

    bool paused;
    int speed;

    sf::Texture sideBarTexture;
    sf::Sprite sideBarSprite;

    sf::Texture progressBarTextures[8];
    sf::Sprite progressBar;

    void pollEvents();
    void initWindow();
    void initVariables();
    bool initTextures();
    void initSprites();
    void drawSprites();
    void updateProgressBarTexture();
};

#endif