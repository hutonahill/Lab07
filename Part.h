#pragma once
#include "Object.h"

class Object;

class Part : public Object
{
private:
	function<void(const Position&, double)> draw;
public:
	Part();
	Part(string nameInput, Angle angleInput, Position locationInput, 
		Velocity velocityInput, int numFragmentsInput, 
		function<void(const Position&, double)> drawInput, int radiusInput);
	Part(string nameInput, int numFragmentsInput,
		function<void(const Position&, double)> drawInput, int radiusInput);
	Part(Part* oldPart);
	bool animate(double time) override;
};

