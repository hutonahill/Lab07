#include "Satalite.h"



bool Satalite::animate(double time){
	translate(time);
	draw(location, angle.getRadians());
	return true;
}

Satalite::Satalite(string nameInput, Angle angleInput, Position locationInput,
	Velocity velocityInput, int numFragmentsInput,
	vector<Part*> partsInput, function<void(const Position&, double)> drawInput, int radiusInput) {
	name = nameInput;
	angle = angleInput;
	location = locationInput;
	objectVelocity = velocityInput;
	numFragments = numFragmentsInput;
	draw = drawInput;
	parts = partsInput;
	radius = radiusInput;
}

Satalite::Satalite(Satalite* oldSatalite) {
	name = oldSatalite->name;
	angle = oldSatalite->angle;
	location = oldSatalite->location;
	objectVelocity = oldSatalite->objectVelocity;
	numFragments = oldSatalite->numFragments;
	draw = oldSatalite->draw;
	parts = oldSatalite->parts;
	radius = oldSatalite->radius;
}

Satalite::Satalite() {}
