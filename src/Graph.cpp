#include "Graph.hpp"

Graph::Graph(sf::Font *font, sf::RenderWindow *window, tgui::GuiSFML *gui, Config *config) : font(font), window(window), gui(gui), config(config),
                                                                         polynomial(6) {
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
    for (auto &point : this->dataPoints) {
        point += translationVector;
    }
}

void Graph::adjust() {
    Eigen::VectorXd xData(this->dataPoints.size());
    Eigen::VectorXd yData(this->dataPoints.size());
    for (int32_t i = 0; i < dataPoints.size(); i++) {
        xData(i) = dataPoints[i].x;
        yData(i) = dataPoints[i].y;
    }
    this->polynomial.fit(xData, yData);
}

void Graph::update() {
    this->timeElapsed = this->clock.restart().asMilliseconds();

    while (window->pollEvent(this->event)) {
        gui->handleEvent(event);
        if (event.type == sf::Event::Closed) {
            window->close();
        }
    }


    // Adding new points to graph
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        this->dataPoints.push_back(this->currentMouse());
        this->adjust();
    }

    this->translateGraph();

    window->clear(sf::Color::White);
    this->drawAxes();
    this->drawTicks();
    this->drawGrids();
    this->drawDataPoints();
    this->drawCurve();
    gui->draw();
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
    for (const auto &point : this->dataPoints) {
        sf::CircleShape circle(this->config->radius);
        circle.setFillColor(sf::Color::Red);
        circle.setPosition(point.x - this->config->radius, point.y - this->config->radius);
        window->draw(circle);
    }
}

void Graph::drawCurve() {
    Eigen::VectorXd xData(this->config->sample);
    for (int32_t i = 0; i < this->config->sample; i++) {
        xData(i) = WINDOW_WIDTH / this->config->sample * i;
    }

    Eigen::VectorXd yData = this->polynomial.calculate(xData);
    for (int32_t i = 0; i < xData.rows() - 1; i++) {
        sf::Vertex line[2];
        line[0].position = sf::Vector2f(xData(i), yData(i));
        line[0].color = sf::Color::Red;
        line[1].position = sf::Vector2f(xData(i + 1), yData(i + 1));
        line[1].color = sf::Color::Red;
        window->draw(line, 2, sf::PrimitiveType::Lines);
    }

    if (!this->dataPoints.empty()) {
        xData = Eigen::VectorXd(this->dataPoints.size());

        for (int32_t i = 0; i < this->dataPoints.size(); i++) {
            xData(i) = this->dataPoints[i].x;
        }

        yData = this->polynomial.calculate(xData);

        for (int32_t i = 0; i < xData.rows() - 1; i++) {
            sf::Vertex line[2];

            line[0].position = dataPoints[i];
            line[0].color = sf::Color::Blue;

            line[1].position = sf::Vector2f(xData(i), yData(i));
            line[1].color = sf::Color::Blue;

            window->draw(line, 2, sf::PrimitiveType::Lines);

        }


        if (this->dataPoints.size() > 1) {
            fpt mae = this->mae(yData);

            std::stringstream ss;
            ss << "MAE: " << mae;

            sf::Text meanAbsoluteError(ss.str(), *this->font, 15);
            meanAbsoluteError.setPosition(5, 5);
            meanAbsoluteError.setFillColor(sf::Color::Black);
            window->draw(meanAbsoluteError);
        }
    }
}


fpt Graph::mae(const Eigen::VectorXd &yHat) {
    fpt mae = 0;
    for (int32_t i = 0; i < yHat.size(); i++) {
        mae += std::abs(dataPoints[i].y - yHat[i]);
    }
    mae /= yHat.size();
    return mae;
}