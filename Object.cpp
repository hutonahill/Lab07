#include "Object.h"

double earthRadiusKm = 6378;
double gravity = 9.80665;

Object::Object() {}

Object::Object(string nameInput, Angle angleInput, Position locationInput, 
	Velocity velocityInput, int numFragmentsInput, vector<Part*> partsInput,
	int radiusInput) {
	name = nameInput;
	angle = angleInput;
	location = locationInput;
	objectVelocity = velocityInput;
	numFragments = numFragmentsInput;
	parts = partsInput;
	radius = radiusInput;
}

Object::Object(Object* oldObject) {
	name = oldObject->name;
	angle = oldObject->angle;
	location = oldObject->location;
	objectVelocity = oldObject->objectVelocity;
	numFragments = oldObject->numFragments;
	parts = oldObject->parts;
	radius = oldObject->radius;
}

void Object::translate(double time) {
	
	double gravityAcceleration = getGravityAccelerationMagnatude(location);

	Angle gravAngle = getGravityAngle(location);

	// claculate the x and y componants of gravity
	double gravityX = horazantalComponant(gravityAcceleration, gravAngle);
	double gravityY = verticalComponant(gravityAcceleration, gravAngle);

	// calculate acceleration due to the forces on the object
	double xAccelerationTotal = xAcceleration + gravityX;
	double yAccelerationTotal = yAcceleration + gravityY;

	// calclulate the new position
	double newXPos = newPosition(location.getMetersX(), objectVelocity.xVelocity, time, xAcceleration);
	double newYPos = newPosition(location.getMetersY(), objectVelocity.yVelocity, time, yAcceleration);

	// claclulate the new velocity
	double newXVelocity = newVelocity(objectVelocity.xVelocity, xAcceleration, time);
	double newYVelocity = newVelocity(objectVelocity.yVelocity, yAcceleration, time);

	// apply the new values
	objectVelocity.xVelocity = newXVelocity;
	objectVelocity.yVelocity = newYVelocity;

	location.setMetersX(newXPos);
	location.setMetersY(newYPos);
}

double getGravityAccelerationMagnatude(Position location) {
	double distanceToCenter = computeDistance(location, Position(0, 0));

	double altitude = distanceToCenter - earthRadiusKm*1000;

	double expression1 = (earthRadiusKm * 1000 / distanceToCenter);

	double results = gravity * expression1 * expression1;

	return results;

}

Angle getGravityAngle(Position location) {
	double resultRadians = atan2(-location.getMetersY(), -location.getMetersX());

	Angle output = Angle(resultRadians);
	return output;
}

double Object::horazantalComponant(double total, Angle angle) {
	return total * sin(angle.getRadians());
}

double Object::verticalComponant(double total, Angle angle) {
	return total * cos(angle.getRadians());

}

double newPosition(double initalPosition, double velocity, double time, double acceleration){
	double statment2 = velocity * time;
	double statment3 = 0.5 * acceleration * time * time;

	return initalPosition + statment2 + statment3;
}

double newVelocity(double initalVeloctiy, double acceleration, double time) {
	double addtionalVelocity = acceleration * time;

	return initalVeloctiy + addtionalVelocity;
}

double getAcceleration(double force, double mass) {
	return force / mass;
}


void Object::setLocation(Position newLocation) {
	location = newLocation;
}

void Object::setVelocity(Velocity newVelocity) {
	objectVelocity = newVelocity;
}

vector<Part*> Object::getParts() {
	return parts;
}

int Object::getNumFragments() {
	return numFragments;
}

Position Object::getLocation() {
	return location;
}

Velocity Object::getVelocity() {
	return objectVelocity;
}

int Object::getRadius() {
	return radius;
}