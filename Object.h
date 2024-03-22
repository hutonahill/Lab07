#pragma once
#include<string>
#include<vector>
#include <functional>

#include "Angle.h"
#include "position.h"
#include "Part.h"
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
public:
	virtual bool animate(double time);

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

