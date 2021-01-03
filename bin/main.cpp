#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main() {
    RenderWindow window;
    window.setFramerateLimit(30);

    Font arial;
    arial.loadFromFile("arial.ttf");
    Event event;

    while (window.isOpen()) {
        while (window.pollEvent(event)) {}

    }

}