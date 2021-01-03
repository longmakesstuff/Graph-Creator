#include "Graph.hpp"

Graph::Graph(sf::Font *font, sf::RenderWindow *window, Config *config) : font(font), window(window), config(config) {
    this->center = sf::Vector2f{config->centerX, config->centerY};
}

void Graph::translateGraph() {
    sf::Vector2f translationVector{0, 0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        translationVector.x += this->timeElapsed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        translationVector.x -= this->timeElapsed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        translationVector.y += this->timeElapsed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        translationVector.y -= this->timeElapsed;
    }
    this->center += translationVector;
    for(auto & point : this->dataPoints){
        point += translationVector;
    }
}

void Graph::update() {
    this->timeElapsed = this->clock.restart().asMilliseconds();

    while (window->pollEvent(this->event));

    // Adding new points to graph
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        this->dataPoints.push_back(this->currentMouse());
    }

    this->translateGraph();

    window->clear(sf::Color::White);
    this->drawAxes();
    this->drawTicks();
    this->drawGrids();
    this->drawDataPoints();
    window->display();
}

void Graph::drawGrids() {
    sf::Color gridColor{150, 150, 150, 150};

    // Draw x grid from 0 to infinity
    for (int32_t x = this->center.x; x < WINDOW_WIDTH; x += this->config->gridSize) {
        sf::RectangleShape xGrid(sf::Vector2f(1, WINDOW_HEIGHT));
        xGrid.setFillColor(gridColor);
        xGrid.setPosition(x, 0);
        this->window->draw(xGrid);
    }

    // Draw x grid from 0 to -infinity
    for (int32_t x = this->center.x; x >= 0; x -= this->config->gridSize) {
        sf::RectangleShape xGrid(sf::Vector2f(1, WINDOW_HEIGHT));
        xGrid.setFillColor(gridColor);
        xGrid.setPosition(x, 0);
        this->window->draw(xGrid);
    }

    // Draw y grid from 0 to -infinity
    for (int32_t y = this->center.y; y < WINDOW_HEIGHT; y += this->config->gridSize) {
        sf::RectangleShape yTick(sf::Vector2f(WINDOW_WIDTH, 1));
        yTick.setFillColor(gridColor);
        yTick.setPosition(0, y);
        this->window->draw(yTick);
    }

    // Draw y grid from 0 to infinity
    for (int32_t y = this->center.y; y >= 0; y -= this->config->gridSize) {
        sf::RectangleShape yTick(sf::Vector2f(WINDOW_WIDTH, 1));
        yTick.setFillColor(gridColor);
        yTick.setPosition(0, y);
        this->window->draw(yTick);
    }
}

void Graph::drawAxes() {
    sf::RectangleShape xAxis(sf::Vector2f(WINDOW_WIDTH, 2));
    xAxis.setFillColor(sf::Color::Black);
    xAxis.setPosition(0, this->center.y);

    sf::RectangleShape yAxis(sf::Vector2f(2, WINDOW_HEIGHT));
    yAxis.setFillColor(sf::Color::Black);
    yAxis.setPosition(this->center.x, 0);

    sf::Text xAxisLabel("X", *this->font, 20);
    xAxisLabel.setPosition(WINDOW_WIDTH - 25, this->center.y - 25);
    xAxisLabel.setFillColor(sf::Color::Black);

    sf::Text yAxisLabel("Y", *this->font, 20);
    yAxisLabel.setPosition(this->center.x + 15, WINDOW_HEIGHT - 25);
    yAxisLabel.setFillColor(sf::Color::Black);

    this->window->draw(xAxis);
    this->window->draw(xAxisLabel);
    this->window->draw(yAxis);
    this->window->draw(yAxisLabel);
}

void Graph::drawTicks() {
    // Draw x ticks from 0 to -infinity
    for (int32_t x = this->center.x; x >= 0; x -= this->config->xTick) {
        sf::RectangleShape xTick(sf::Vector2f(2, 20));
        xTick.setFillColor(sf::Color::Black);
        xTick.setPosition(x, this->center.y - 10);
        this->window->draw(xTick);
    }

    // Draw x ticks from 0 to infinity
    for (int32_t x = this->center.x; x < WINDOW_WIDTH; x += this->config->xTick) {
        sf::RectangleShape xTick(sf::Vector2f(2, 20));
        xTick.setFillColor(sf::Color::Black);
        xTick.setPosition(x, this->center.y - 10);
        this->window->draw(xTick);
    }

    // Draw y ticks from 0 to -infinity
    for (int32_t y = this->center.y; y < WINDOW_HEIGHT; y += this->config->yTick) {
        sf::RectangleShape yTick(sf::Vector2f(20, 2));
        yTick.setFillColor(sf::Color::Black);
        yTick.setPosition(this->center.x - 10, y);
        this->window->draw(yTick);
    }

    // Draw y ticks from 0 to infinity
    for (int32_t y = this->center.y; y >= 0; y -= this->config->yTick) {
        sf::RectangleShape yTick(sf::Vector2f(20, 2));
        yTick.setFillColor(sf::Color::Black);
        yTick.setPosition(this->center.x - 10, y);
        this->window->draw(yTick);
    }
}

sf::Vector2f Graph::currentMouse() const {
    sf::Vector2i pos = sf::Mouse::getPosition(*this->window);
    return sf::Vector2f{(float) pos.x, (float) pos.y};
}

void Graph::drawDataPoints() {
    for(const auto& point : this->dataPoints) {
        sf::CircleShape circle(5);
        circle.setFillColor(sf::Color::Red);
        circle.setPosition(point);
        window->draw(circle);
    }
}
