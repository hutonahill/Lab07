#pragma once
#include "Object.h"

class Satalite : public Object
{
private:
	function<void(const Position&, double)> draw = function<void(const Position&, double)>();
	
public:
	Satalite();
	Satalite(string nameInput, Angle angleInput, Position locationInput,
		Velocity velocityInput, int numFragmentsInput,
		vector<Part*> partsInput, function<void(const Position&, double)> drawInput, int radiusInput);
	Satalite(Satalite* oldSatalite);

	bool animate(double time) override;

};

