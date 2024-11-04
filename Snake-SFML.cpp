#include <SFML/Graphics.hpp>

void main(int argc, char** argv[]) {
	sf::RenderWindow window(sf::VideoMode(1080, 720), "Snake");
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				// Close window button clicked.
				window.close();
			}
		}
		window.clear(sf::Color::Black);
		// Draw here.
		window.display();
	}
}
