#pragma once
#include <cassert>
class testing
{
public:
	testing() {
		chaser = DreamChaser();
		test1();
		test2();
		test2();
		test4();
		test5();
		test6();
		test7();
		test8();
		test9();
		test10();
		test11();
	}


private:
	// Evan Riker

	void test1() {
		List<Object*> ObjectList = List<Object*>();

		Object* testObject = new GPSSatellite();

		ObjectList.append(testObject);

		assert(ObjectList.count == 1);

		testObject.handelColision(ObjectList);

		assert(ObjectList.count == testObject.parts.count);
	}

	// the only other test i can think of are testing our translate method, but i have no
	// data about how that is suposed to behave.

	// my parner did not provide code for his tests, he only provided a txt file explaning them.
	// ive traslated his tests to code best i can, but he didnt include any data.

	DreamChaser chaser;

	//Update position and velocity:
	void test2() {
		double deltaTime = 0.1;
		bool leftKeyPressed = true;
		bool rightKeyPressed = false;
		bool upKeyPressed = true;

		

		chaser.handleUserInput(leftKeyPressed, rightKeyPressed, upKeyPressed);

		chaser.animate(deltaTime);

		// Expected Output: DreamChaser's position and velocity should be 
		// updated accordingly.

		// no data was provided to verify the results
	}

	// Launch projectile:
	void test3() {
		chaser = DreamChaser();
		// the above object should have some velocity and position, but none were spesified.

		chaser.animtate();

		
		// Expected Output: A Projectile object should be launched 
		// with appropriate velocity from the DreamChaser's position.
		
		// no data was provided to verify the results
		
	}

	// No key pressed:
	void test4() {
		double deltaTime = 0.1;
		bool leftKeyPressed = false;
		bool rightKeyPressed = false;
		bool upKeyPressed = false;

		chaser.handleUserInput(leftKeyPressed, rightKeyPressed, upKeyPressed);

		chaser.animate(deltaTime);

		// Expected Output : DreamChaser's position and velocity should remain unchanged.

		// no data was provided to verify the results
	}

	//Negative acceleration:
	void test5() {
		double deltaTime = 0.1;
		bool leftKeyPressed = false;
		bool rightKeyPressed = false;
		bool upKeyPressed = true;

		chaser.handleUserInput(leftKeyPressed, rightKeyPressed, upKeyPressed);

		chaser.animate(deltaTime);

		//Expected Output: DreamChaser should accelerate in the direction it is facing.

		// no data was provided to verify the results
	}

	// Large deltaTime:
	void test6() {
		bool deltaTime = 10.0;
		// other inputs according to test scenario

		chaser.animate(deltaTime);

		//Expected Output: Objects' positions should be updated 
		// correctly even with a large time step.
	}

	// Corner cases (e.g., orientation close to 0 or 2*pi):
	void test7() {
		double deltaTime = 0.1;
		bool leftKeyPressed = true;
		bool rightKeyPressed = false;
		bool upKeyPressed = true;

		chaser.handleUserInput(leftKeyPressed, rightKeyPressed, upKeyPressed);

		chaser.animate(deltaTime);

		// Expected Output: DreamChaser should handle 
		// corner cases gracefully without unexpected behavior.
	}

	// Edge cases (e.g., position or velocity very large or very small):
	void test8() {
		// Inputs: Appropriate inputs to test extreme values for position and velocity

		//Expected Output: Functions should handle extreme 
		// values without crashing or exhibiting unexpected behavior.
	}

	// Multiple key presses:
	void test9() {
		double deltaTime = 0.1;
		bool leftKeyPressed = true;
		bool rightKeyPressed = true;
		bool upKeyPressed = true;

		chaser.handleUserInput(leftKeyPressed, rightKeyPressed, upKeyPressed);

		chaser.animate(deltaTime);

		// Expected Output: DreamChaser should respond appropriately to multiple key presses, 
		// possibly by combining the effects of each key press.
	}
	
	//No key press :
	void test10() {
		double deltaTime = 0.1;
		bool leftKeyPressed = false;
		bool rightKeyPressed = false;
		bool upKeyPressed = false;

		chaser.handleUserInput(leftKeyPressed, rightKeyPressed, upKeyPressed);

		chaser.animate(deltaTime);
	}

	// Test Cases for Projectile Class:

	// Update projectile position :
	void test11() {
		double deltaTime = 0.1;

		Bullet bullet = Bullet();

		bullet.animate(deltaTime);

		//Expected Output : The position of the projectile 
		// should be updated based on its initial position and velocity.
	}

};

