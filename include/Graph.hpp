#pragma once

#include <SFML/Graphics.hpp>
#include "Common.hpp"

class Graph {
private:
    sf::Font *font;
    sf::RenderWindow *window;
    Config *config;
    sf::Vector2f center;
    sf::Vector2f middleMouseClickedPosition;
    sf::Event event;
    bool middleMousePressed;

    void drawAxes();

    void drawTicks();

    void translateGraph();

    [[nodiscard]] sf::Vector2f currentMouse() const;
public:
    Graph(sf::Font *font, sf::RenderWindow *window, Config *config);

    void update();
};