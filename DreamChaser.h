#pragma once
#include "TempObject.h"
#include "uiInteract.h" // for INTERFACE

class Object;

class DreamChaser : public Object
{
public:
	DreamChaser(Position locationInput, Angle angleInput, 
		Velocity velocityInput, vector<Object*>* ObjectListInput, 
		function<void(const Position&, double, bool)> drawInput, int radiusInput);
	DreamChaser();
	DreamChaser(DreamChaser* oldChaser);
	void handleUserInput(vector<Object*>* ObjectList, const Interface* pUI, ogstream* ui);
	void handleUserInput(vector<Object*>* ObjectList, ogstream* ui,
		bool up, bool down, bool left, bool right);

	bool animate(double time) override;
private:
	bool isThrusting;
	function<void(const Position&, double, bool)> draw = function<void(const Position&, double, bool)>();
	double thrustAcceleration;
	vector<Object*>* ObjectList;
	TempObject* generateBullet(ogstream* ui);
	Position rotate(const Position& origin, double x, double y, double rotation);

	
};

