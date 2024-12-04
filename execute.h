#include "image.h"
#include "effect.h"

class Execute {


public:

	void execute(std::vector<std::shared_ptr<Effect>>& finish_vect, Picture& picture) {
	
		for (auto element : finish_vect) {
			element->makeEffect(picture);
		}
	}
};