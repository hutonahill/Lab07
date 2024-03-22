#pragma once
#include<string>
#include<vector>
#include <functional>

#include "Angle.h"
#include "position.h"
#include "Velocity.h"
#include "uiDraw.h"

using namespace std;

class Part;

class Object{

protected:
	string name;
	Angle angle;
	Position location;
	Velocity objectVelocity;
	int numFragments;
	vector<Part*> parts;

	int radius;

	void translate(double time);

	double horazantalComponant(double total, Angle angle);
	double verticalComponant(double total, Angle angle);
	double getGravityAccelerationMagnatude(Position location);
	Angle getGravityAngle(Position location);
	double newPosition(double initalPosition, double velocity, double time, double acceleration);
	double newVelocity(double initalVeloctiy, double acceleration, double time);
	double getAcceleration(double force, double mass);
public:
	virtual bool animate(double time) = 0;

	double xAcceleration = 0;
	double yAcceleration = 0;

	Object();
	Object(string nameInput, Angle angleInput, Position locationInput, 
		Velocity velocityInput, int numFragments, vector<Part*> partsInput,
		int radiusInput);

	Object(Object* oldObject);

	void setLocation(Position newLocation);
	void setVelocity(Velocity newVelocity);

	vector<Part*> getParts();

	int getNumFragments();

	Position getLocation();
	Velocity getVelocity();
	int getRadius();
};

