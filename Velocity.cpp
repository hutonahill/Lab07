#include "Velocity.h"

#include<vector>


using namespace std;

Velocity::Velocity(double xInput, double yInput) {
	xVelocity = xInput;
	yVelocity = yInput;
}

Velocity::Velocity() {
	xVelocity = 0;
	yVelocity = 0;
}

Velocity::Velocity(Velocity* oldVelocity) {
	xVelocity = oldVelocity->xVelocity;
	yVelocity = oldVelocity->yVelocity;
}

double Velocity::getTotal() {
	double x2 = xVelocity * xVelocity;
	double y2 = yVelocity * yVelocity;

	double output = sqrt(x2 + y2);

	return output;
}
