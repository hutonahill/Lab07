#include "DreamChaser.h"



DreamChaser::DreamChaser(Position locationInput, Angle angleInput, 
	Velocity velocityInput, vector<Object*>* ObjectListInput, 
	function<void(const Position&, double, bool)> drawInput, int radiusInput) {
	location = locationInput;
	angle = angleInput;
	objectVelocity = velocityInput;
	ObjectList = ObjectListInput;
	isThrusting = false;
	draw = drawInput;
	radius = radiusInput;

	
}

DreamChaser::DreamChaser() {}

DreamChaser::DreamChaser(DreamChaser* oldChaser) {
	location = oldChaser->location;
	angle = oldChaser->angle;
	objectVelocity = oldChaser->objectVelocity;
	ObjectList = oldChaser->ObjectList;
	isThrusting = oldChaser->isThrusting;
	draw = oldChaser->draw;
	thrustAcceleration = oldChaser->thrustAcceleration;
	radius = oldChaser->radius;
}

void DreamChaser::handleUserInput(vector<Object*>* ObjectList, const Interface* pUI, ogstream* ui){
	handleUserInput(ObjectList, ui, pUI->isUp(), pUI->isDown(), pUI->isLeft(), pUI->isRight());
}

void DreamChaser::handleUserInput(vector<Object*>* ObjectList, ogstream* ui, 
	bool up, bool down, bool left, bool right) {
	if (down) {
		isThrusting = true;
		xAcceleration += horazantalComponant(thrustAcceleration, angle);
		yAcceleration += verticalComponant(thrustAcceleration, angle);
	}
	else {
		isThrusting = false;
	}

	if (right && left) {}
	else if (right) {
		angle.setRadians(angle.getRadians() + 0.1);
	}
	else if (left) {
		angle.setRadians(angle.getRadians() - 0.1);
	}

	if (up) {
		(*ObjectList).push_back(generateBullet(ui));
	}
}

TempObject* DreamChaser::generateBullet(ogstream* ui) {

	Position ptShipFrount = rotate(location, 0, 19, angle.getRadians());; //visual studio realy wanted me to include this ;;. no idea why.

	auto boundDrawProjectile = bind(&ogstream::drawProjectile, ui, placeholders::_1, placeholders::_2);

	TempObject tempObject = TempObject("Bullet", angle, ptShipFrount, objectVelocity, boundDrawProjectile, 2880, 1);
	return &tempObject;
}

bool DreamChaser::animate(double time) {
	translate(time);
	draw(location, angle.getRadians(), isThrusting);
	return true;
}


// no idea how to acces this method without copy/paste
/************************************************************************
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *    INPUT  origin   The center point we will rotate around
 *           x,y      Offset from center that we will be rotating, in pixels
 *           rotation Rotation in degrees
 *    OUTPUT point    The new position
 *************************************************************************/
Position DreamChaser::rotate(const Position& origin, double x, double y, double rotation)
{
	// because sine and cosine are expensive, we want to call them only once
	double cosA = cos(rotation);
	double sinA = sin(rotation);

	// start with our original point
	Position ptReturn(origin);

	// find the new values
	ptReturn.addPixelsX(x * cosA + y * sinA);
	ptReturn.addPixelsY(y * cosA - x * sinA);

	return ptReturn;
}