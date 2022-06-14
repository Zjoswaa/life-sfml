#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>

const int windowWidth = 960;
const int windowHeight = 540;

const int boardWidth = 640;
const int boardHeight = 540;

const int sidebarWidth = 320;
const int sidebarHeight = 540;

const int fps = 60;
const int squareSize = 10;
const int maxSpeed = 8;
const int minSpeed = 1;

const sf::Color deadColor = sf::Color(255, 255, 255, 255);
const sf::Color aliveColor = sf::Color(0, 0, 0, 150);

#endif