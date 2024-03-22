#pragma once
#include "Object.h"

class TempObject : public Object
{
private:
	double timeToLive = 0;
	function<void(const Position&, double)> draw;
public:
	bool animate(double time) override;

	TempObject(string nameInput, Angle angleInput, Position locationInput,
		Velocity velocityInput, function<void(const Position&, double)> drawInput, double timeToLiveInput,
		int radiusInput);
	TempObject(TempObject*OldObject);
	TempObject();

	void setTimeToLive(int newTime);
};

