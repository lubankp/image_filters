#pragma once
#include "image.h"

class Effect {

public:
	
	virtual void makeEffect(Picture&) = 0;
	virtual ~Effect() {};
};

