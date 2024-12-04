#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>


class Picture {

	sf::Image image_;

public:
	
	bool openPicture(std::string fileName) {

		return	image_.loadFromFile(fileName);
	}

	void createPicture(unsigned int width, unsigned int high, sf::Color color) {

		image_.create(width, high, color);
	}

	void writePicture(std::string fileName) {

		image_.saveToFile(fileName);
	}

	
	void show() {

		sf::RenderWindow window(sf::VideoMode(image_.getSize().x, image_.getSize().y), "Picture");
		sf::Texture texture;
		sf::IntRect r1(0, 0, image_.getSize().x, image_.getSize().y);
		texture.loadFromImage(image_, r1);


		while (window.isOpen())
		{
			// handle events
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			sf::Sprite sprite(texture);
			window.draw(sprite);
			window.display();
		}

	}

	sf::Image* getImage() { return &image_; };
	



};