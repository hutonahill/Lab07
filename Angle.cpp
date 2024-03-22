#include "Angle.h"

const double Angle::pi = 3.141592653589793;

Angle::Angle(double radians) {
	angleRadians = normalize(radians);
}

Angle::Angle(double degrees, bool usingDegrees) {
	double radians = convertToRadians(degrees);

	angleRadians = normalize(radians);
}

Angle::Angle() {
	angleRadians = 0;
}

Angle::Angle(Angle* oldAngle) {
	angleRadians = oldAngle->angleRadians;
}

double Angle::convertToRadians(double degrees) {
	double radians = (degrees * pi / 180) / 0.01745l;

	double normalRadians = normalize(radians);

	return normalRadians;
}

double Angle::convertToDegrees(double radians) {
	double normalRadians = normalize(radians);

	double degrees = normalRadians * (180 / pi);

	return degrees;
}

double Angle::normalize(double radians) {
	double maxValue = 2 * pi;

	// if over max value, subtract maxValue until its within range.
	while (radians >= maxValue) {
		radians -= maxValue;
	}

	// if under maxValue, add maxValue until its within range.
	while (radians < 0) {
		radians += maxValue;
	}

	return radians;
}

double Angle::getDegrees() {
	double degrees = convertToDegrees(angleRadians);

	return degrees;
}

double Angle::getRadians() {
	return angleRadians;
}

void Angle::setDegrees(double degrees) {
	double radians = convertToRadians(degrees);

	angleRadians = radians;
}

void Angle::setRadians(double radians) {
	double normalRadians = normalize(radians);

	angleRadians = normalRadians;
}