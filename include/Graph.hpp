#pragma once

#include <SFML/Graphics.hpp>
#include "Common.hpp"

class Graph {
private:
    sf::Font *font;
    sf::RenderWindow *window;
    Config *config;
    sf::Vector2f center;
    sf::Event event;
    sf::Clock clock;
    fpt timeElapsed = 0;

    void drawAxes();

    void drawTicks();

    void drawGrids();

    void translateGraph();

    [[nodiscard]] sf::Vector2f currentMouse() const;
public:
    Graph(sf::Font *font, sf::RenderWindow *window, Config *config);

    void update();
};