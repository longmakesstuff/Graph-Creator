#include <SFML/Graphics.hpp>
#include <Graph.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Graph Creator", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Font arial;
    arial.loadFromFile("arial.ttf");

    Config config{
        .centerX = 100.0f,
        .centerY = 100.0f,
        .xTick = 100.0f,
        .yTick = 100.0f
    };

    Graph graph(&arial, &window, &config);
    while (window.isOpen()) {
        graph.update();
    }
}