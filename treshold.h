
//includes files
#include "effect.h"


class Treshold : public Effect {
//child class

//attributes:
	int canal_;
	int treshold_;

public:

	Treshold(int canal, int treshold) : canal_(canal), treshold_(treshold) {};
	//constructor

	int* getCanal() { return &canal_; };
	//return attribute
	int* getTreshold() { return &treshold_; };
	//return attribute

	void makeEffect(Picture& e_image_) override {
		//modifies image - adds treshold on choosen canal
		sf::Color color;

		for (int x = 0; x < e_image_.getImage()->getSize().x; x++) {

			for (int y = 0; y < e_image_.getImage()->getSize().y; y++) {


				color = e_image_.getImage()->getPixel(x, y);
				if (e_image_.getImage()->getPixel(x, y).r < treshold_ && canal_ == 114) {
					color.r = treshold_;
				}
				if (e_image_.getImage()->getPixel(x, y).g < treshold_ && canal_ == 103) {
					color.g = treshold_;
				}
				if (e_image_.getImage()->getPixel(x, y).b < treshold_ && canal_ == 98) {
					color.b = treshold_;
				}
				e_image_.getImage()->setPixel(x, y, color);

			}
		}
		
	}
	//destructor
	~Treshold(){};
};