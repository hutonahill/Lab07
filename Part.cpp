#include "Part.h"

Part::Part() {};

Part::Part(string nameInput, Angle angleInput, Position locationInput, 
	Velocity velocityInput, int numFragmentsInput, 
	function<void(const Position&, double)> drawInput, int radiusInput) {
	name = nameInput;
	angle = angleInput;
	location = locationInput;
	objectVelocity = velocityInput;
	numFragments = numFragmentsInput;
	draw = drawInput;
	radius = radiusInput;
}

Part::Part(string nameInput, int numFragmentsInput,
	function<void(const Position&, double)> drawInput, int radiusInput) {
	name = nameInput;
	angle = Angle();
	location = Position();
	objectVelocity = Velocity();
	numFragments = numFragmentsInput;
	draw = drawInput;
	radius = radiusInput;
}

Part::Part(Part* oldPart) {
	name = oldPart->name;
	angle = oldPart->angle;
	location = oldPart->location;
	objectVelocity = oldPart->objectVelocity;
	numFragments = oldPart->numFragments;
	parts = oldPart->parts;
	draw = oldPart->draw;
	radius = oldPart->radius;
}

bool Part::animate(double time) {
	translate(time);
	draw(location, angle.getRadians());
	return true;
}