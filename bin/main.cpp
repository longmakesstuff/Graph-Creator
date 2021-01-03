#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <Graph.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Graph Creator", sf::Style::Default);
    window.setFramerateLimit(30);

    tgui::GuiSFML gui{window};

    sf::Font arial;
    arial.loadFromFile("arial.ttf");

    Config config{
        .centerX = 100.0f,
        .centerY = 100.0f,
        .xTick = 100.0f,
        .yTick = 100.0f,
        .gridSize = 10.0f,
        .sample = 100,
        .radius = 5
    };

    Graph graph(&arial, &window, &gui, &config);
    while (window.isOpen()) {
        graph.update();
    }
}