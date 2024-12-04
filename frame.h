
#include "effect.h"

class Frame : public Effect {

	int horizontal_;
	int vertical_;

public:

	Frame(int horizontal, int vertical) : horizontal_(horizontal), vertical_(vertical) {};
	
	int* getHorizontal() { return &horizontal_; };
	int* getVertical() { return &vertical_; };

	void makeEffect(Picture& e_image_) override {

		sf::Color white = sf::Color::White;
		int horizontal_s = (e_image_.getImage()->getSize().x - horizontal_) / 2;
		int horizontal_f = e_image_.getImage()->getSize().x - horizontal_s;
		int vertical_s = (e_image_.getImage()->getSize().y - vertical_) / 2;
		int vertical_f = e_image_.getImage()->getSize().y - vertical_s;


		for (int x = 0; x < e_image_.getImage()->getSize().x; x++) {

			for (int y = 0; y < e_image_.getImage()->getSize().y; y++) {

				if ((x < horizontal_s || x > horizontal_f) || (y < vertical_s || y > vertical_f)) {

					e_image_.getImage()->setPixel(x, y, white);
				}
			}
		}

	}
	~Frame(){};
};