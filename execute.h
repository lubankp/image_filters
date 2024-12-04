//includes files
#include "image.h"
#include "effect.h"

class Execute {


public:

	void execute(std::vector<std::shared_ptr<Effect>>& finish_vect, Picture& picture) {
		//execute operations in taken vector

		for (auto element : finish_vect) {
			element->makeEffect(picture);
		}
	}
};