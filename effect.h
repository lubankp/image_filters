//includes files
#pragma once
#include "image.h"

class Effect {
//parent class

public:
	//method
	virtual void makeEffect(Picture&) = 0;
	//destructor
	virtual ~Effect() {};
};

