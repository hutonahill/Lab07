#include "TempObject.h"

bool TempObject::animate(double time) {
	if (timeToLive > 0) {
		translate(time);
		draw(location, angle.getRadians());
		timeToLive -= time;
		return true;
	}
	return false;
}

TempObject::TempObject(string nameInput, Angle angleInput, Position locationInput,
	Velocity velocityInput, function<void(const Position&, double)> drawInput, double timeToLiveInput,
	int radiusInput) {
	name = nameInput;
	angle = angleInput;
	location = locationInput;
	objectVelocity = velocityInput;
	numFragments = 0;
	draw = drawInput;
	timeToLive = timeToLiveInput;
	radius = radiusInput;
}

TempObject::TempObject(TempObject* OldObject) {
	name = OldObject->name;
	angle = OldObject->angle;
	location = OldObject->location;
	objectVelocity = OldObject->objectVelocity;
	numFragments = OldObject->numFragments;
	draw = OldObject->draw;
	timeToLive = OldObject->timeToLive;
	radius = OldObject->radius;


}

TempObject::TempObject() {}

void TempObject::setTimeToLive(int newTime) {
	timeToLive = newTime;
}