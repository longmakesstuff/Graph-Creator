#pragma once

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "Polynomial.hpp"
#include "Common.hpp"

class Graph {
private:
    sf::Font *font;
    sf::RenderWindow *window;
    tgui::GuiSFML *gui;
    Config *config;
    sf::Vector2f center;
    sf::Event event{};
    sf::Clock clock;
    fpt timeElapsed = 0;
    std::vector<sf::Vector2f> dataPoints;
    Polynomial polynomial;

    void drawAxes();

    void drawTicks();

    void drawGrids();

    void drawDataPoints();

    void drawCurve();

    void translateGraph();

    void adjust();

    [[nodiscard]] sf::Vector2f currentMouse() const;

    fpt mae(const Eigen::VectorXd &yHat);

public:
    Graph(sf::Font *font, sf::RenderWindow *window, tgui::GuiSFML *gui, Config *config);

    void update();
};