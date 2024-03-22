#pragma once
#include<string>

using namespace std;

class Angle {
public:

	Angle(double radians);

	Angle(double degrees, bool usingDegrees);

	Angle();

	Angle(Angle* oldAngle);

	/*Takes no parameters and return the angle in degrees.*/
	double getDegrees();

	/* Takes no parameters and return the angle in radians.*/
	double getRadians();

	/*Takes a degrees as a parameter and updates the attribute
	with the passed parameter. If the parameter is above 360 or
	below zero, then it will "unwrap" so the radians is between 0 and 2pi.*/
	void setDegrees(double degrees);

	/* Takes a radian as a parameter and updates the
	attribute with the passed parameter.
	If the parameter is above 2pi or below zero,
	then it will "unwrap."*/
	void setRadians(double radians);

	/*Takes a ostream & out as a parameter display the value,
	in degrees, to 1 decimal place of accuracy.
	This out parameter can be treated exactly the same as cout.
	You can use it with a.display(cout) if a is the name of your object.*/
	string display();

private:
	/*  Takes a radian as a parameter and reduce it to between 0 and 2pi.
	For example, 3pi will become pi, 362 degrees will become 2 degrees,
	 -5 degrees will become 355 degrees, and -7pi will become pi.
	 */
	double normalize(double radians);

	/* Takes a radians as a parameter and returns degrees.
	Does not utilize the class's attribute.
	Note that the results must be normalized. */
	double convertToDegrees(double radians);

	/*Takes a degrees as a parameter and returns radians.
	Does not utilize the class's attribute.
	Note that the results must be normalized. */
	double convertToRadians(double degrees);


	const static double pi;

	double angleRadians;
};



