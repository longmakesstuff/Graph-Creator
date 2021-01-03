#include "Graph.hpp"

Graph::Graph(sf::Font *font, sf::RenderWindow *window, Config *config) : font(font), window(window), config(config) {
    this->center = sf::Vector2f{config->centerX, config->centerY};
    this->middleMousePressed = false;
}

void Graph::translateGraph() {
    sf::Vector2f currentMouse = this->currentMouse();
    sf::Vector2f delta = currentMouse - middleMouseClickedPosition;
    this->center += delta * 0.1;
}

void Graph::update() {
    while (window->pollEvent(this->event)) {}

    if (this->event.type == sf::Event::EventType::MouseButtonPressed) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && !this->middleMousePressed) {
            this->middleMousePressed = true;
            this->middleMouseClickedPosition = this->currentMouse();
        }
    }
    if (this->event.type == sf::Event::EventType::MouseButtonReleased) {
        if (this->middleMousePressed) {
            this->middleMousePressed = false;
        }
    }
    if (this->event.type == sf::Event::EventType::MouseMoved) {
        if (this->middleMousePressed) {
            this->translateGraph();
        }
    }

    window->clear(sf::Color::White);
    this->drawAxes();
    this->drawTicks();
    window->display();
}

void Graph::drawAxes() {
    sf::RectangleShape xAxis(sf::Vector2f(WINDOW_WIDTH, 2));
    xAxis.setFillColor(sf::Color::Black);
    xAxis.setPosition(0, this->center.y);

    sf::RectangleShape yAxis(sf::Vector2f(2, WINDOW_HEIGHT));
    yAxis.setFillColor(sf::Color::Black);
    yAxis.setPosition(this->center.x, 0);

    sf::Text xAxisLabel("X-Axis", *this->font, 20);
    xAxisLabel.setPosition(WINDOW_WIDTH - 75, this->center.y - 25);
    xAxisLabel.setFillColor(sf::Color::Black);


    sf::Text yAxisLabel("Y-Axis", *this->font, 20);
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
        sf::RectangleShape xTick(sf::Vector2f(1, 20));
        xTick.setFillColor(sf::Color::Black);
        xTick.setPosition(x, this->center.y - 10);
        this->window->draw(xTick);
    }

    // Draw x ticks from 0 to infinity
    for (int32_t x = this->center.x; x < WINDOW_WIDTH; x += this->config->xTick) {
        sf::RectangleShape xTick(sf::Vector2f(1, 20));
        xTick.setFillColor(sf::Color::Black);
        xTick.setPosition(x, this->center.y - 10);
        this->window->draw(xTick);
    }

    // Draw y ticks from 0 to -infinity
    for (int32_t y = this->center.y; y < WINDOW_HEIGHT; y += this->config->yTick) {
        sf::RectangleShape yTick(sf::Vector2f(20, 1));
        yTick.setFillColor(sf::Color::Black);
        yTick.setPosition(this->center.x - 10, y);
        this->window->draw(yTick);
    }

    // Draw y ticks from 0 to infinity
    for (int32_t y = this->center.y; y >= 0; y -= this->config->yTick) {
        sf::RectangleShape yTick(sf::Vector2f(20, 1));
        yTick.setFillColor(sf::Color::Black);
        yTick.setPosition(this->center.x - 10, y);
        this->window->draw(yTick);
    }
}

sf::Vector2f Graph::currentMouse() const {
    sf::Vector2i pos = sf::Mouse::getPosition(*this->window);
    return sf::Vector2f{(float) pos.x, (float) pos.y};
}
