#pragma once
class Velocity
{
private:
	

public:
	Velocity(double xInput, double yInput);

	Velocity();
	Velocity(Velocity* oldVelocity);

	double xVelocity;
	double yVelocity;

	double getTotal();
};

