/*************************************************************
 * 1. Name:
 *      Demo
 * 2. Assignment Name:
 *      Lab 07: Orbit Simulator
 * 3. Assignment Description:
 *      Simulate satellites orbiting the earth
 * 4. What was the hardest part? Be as specific as possible.
 *      ??
 * 5. How long did it take for you to complete the assignment?
 *      ??
 *****************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"      // for POINT

#include <algorithm>
#include <random>

#include "Object.h"
#include "Satalite.h"
#include "DreamChaser.h"
#include "Part.h"
#include "testing.h"
using namespace std;

vector<Object*> ObjectList;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
    Demo(Position ptUpperRight, vector<Object*>* objectListInput, DreamChaser* chaserInput, ogstream* goutInput) :
        ptUpperRight(ptUpperRight),
        ObjectList(objectListInput),
        chaser(chaserInput),
        gout(goutInput)
   {
      
   }

   vector<Object*>* ObjectList;
   
   Position ptStar;
   Position ptUpperRight;

   DreamChaser* chaser;

   ogstream* gout;

   unsigned char phaseStar;

   double angleEarth;
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Demo* pDemo = (Demo*)p;

   int timePerFrame = 48;

   // grab the object list for ease of refrance
   vector<Object*>* ObjectList = pDemo->ObjectList;

   //
   // accept input
   //

   // handle the user input
   pDemo->chaser->handleUserInput(pDemo->ObjectList, pUI, pDemo->gout);


   //
   // perform all the game logic
   //

   // rotate the earth
   pDemo->angleEarth += 0.01;
   pDemo->phaseStar++;

   //
   // draw/translate everything
   //

   for (Object* var : (*ObjectList)){
       var->animate(timePerFrame);
   }
   
   // would love to randomize this.
   // draw a single star
   pDemo->gout->drawStar(pDemo->ptStar, pDemo->phaseStar);

   // draw the earth
   Position pt = Position(0.0, 0.0);
   pDemo->gout->drawEarth(pt, pDemo->angleEarth);
}

double Position::metersFromPixels = 40.0;

Satalite* generateGPS(Position startLocation, Velocity startVelocity, ogstream* gout) {

    auto boundDrawGPSCenter = bind(&ogstream::drawGPSCenter, gout, placeholders::_1, placeholders::_2);

    // the below methods have an optional peramiter we are not using, so we put them in a wrapper instead.
    auto drawGPSLeft = [gout](const Position& center, double rotation) {
        gout->drawGPSLeft(center, rotation);
    };

    auto drawGPSRight = [gout](const Position& center, double rotation) {
        gout->drawGPSRight(center, rotation);
    };

    vector<Part*> GPSParts = vector<Part*>{
        new Part("GPSCenter", 3, boundDrawGPSCenter, 7),
        new Part("GPSLeft  ", 3, drawGPSLeft  , 8),
        new Part("GPSRight ", 3, drawGPSRight , 8)
    };

    int GPSFragments = 2;
    string gpsName = "GPS";
    auto DrawGPS = [gout](const Position& center, double rotation) {
        gout->drawGPS(center, rotation);
    };


    return new Satalite(gpsName, Angle(), startLocation, startVelocity, GPSFragments, GPSParts, DrawGPS, 12);
}

Position calculateOffsetPosition(const Position& initialPos, const Velocity& velocity, double distance) {
    // Calculate the magnitude of the velocity vector
    double magnitude = sqrt(velocity.xVelocity * velocity.xVelocity + 
        velocity.yVelocity * velocity.yVelocity);

    // Calculate the unit vector of the velocity vector
    double unitVx = velocity.xVelocity / magnitude;
    double unitVy = velocity.yVelocity / magnitude;

    // Calculate the displacement vector
    double deltaX = unitVx * distance;
    double deltaY = unitVy * distance;

    // Calculate the new position
    double x = initialPos.getMetersX() + deltaX;
    double y = initialPos.getMetersY() + deltaY;

    Position newPos(x,y);

    return newPos;
}

int getRandomNumber(int min, int max) {
    // Set up random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);

    // Generate and return the random number
    return dist(gen);
}

void HandleOffset(Object* parentObject, Object* childObject) {
    // Set up random number generation
   

    // Generate a random number between 5000 and 9000
    int randomNumber = getRandomNumber(5000, 9000);

    // Randomly determine whether the first number is positive or negative
    bool isPositive = getRandomNumber(0, 1);

    // If isFirstNumberPositive is true, keep the first number positive; otherwise, make it negative
    int firstPart;
    int secondPart;
    if (isPositive) {
        firstPart = getRandomNumber(0, randomNumber);
    }
    else {
        firstPart = getRandomNumber(-randomNumber, 0);
    }
    secondPart = randomNumber - firstPart;

    Velocity ObjectVelocity = parentObject->getVelocity();

    Velocity newVelocity = Velocity(ObjectVelocity.xVelocity + firstPart, ObjectVelocity.yVelocity + secondPart);

    Position objectLocation = parentObject->getLocation();

    Position newLocation = calculateOffsetPosition(objectLocation, newVelocity, parentObject->getRadius() + 4);

    childObject->setLocation(newLocation);
    childObject->setVelocity(newVelocity);
}

TempObject* basicFragment;

void HandleColission(Object* targetObject, vector<Object*>* ObjectList) {


    if (find(ObjectList->begin(), ObjectList->end(), targetObject) != ObjectList->end()) {

        // i should realy delete this out of memory when i am done spawning fragments and stuff.
        ObjectList->erase(remove(ObjectList->begin(), ObjectList->end(), targetObject), ObjectList->end());

        vector<Part*> objectParts = targetObject->getParts();

        // handle parts
        for (Part* part : objectParts) {

            HandleOffset(targetObject, part);

            ObjectList->push_back(part);
        }

        // handle fragments
        for (int i = 0; i < targetObject->getNumFragments(); i++){
            TempObject* newFragment = new TempObject(basicFragment);

            HandleOffset(targetObject, newFragment);

            newFragment->setTimeToLive(getRandomNumber(50, 100));
        }
    }
    
    
}

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
    // Initialize OpenGL
    Position ptUpperRight;
    ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
    ptUpperRight.setPixelsX(1000.0);
    ptUpperRight.setPixelsY(1000.0);
    Interface ui(0, NULL,
        "Demo",   /* name on the window */
        ptUpperRight);

    auto boundHandleColission = [](Object* targetObject, vector<Object*>* ObjectList) {
        HandleColission(targetObject, ObjectList);
    };

    testing newTest(boundHandleColission);


    Position pt;
    ogstream gout(pt);

    ogstream* goutPointer = &gout;

    auto boundDrawFragment = bind(&ogstream::drawFragment, goutPointer, placeholders::_1, placeholders::_2);

    basicFragment = new TempObject("Fragment", Angle(), Position(), Velocity(), boundDrawFragment, 0, 2);

    // before we start we need to create an object list with all our inital objects

    auto boundDrawSputnik = bind(&ogstream::drawSputnik, goutPointer, placeholders::_1, placeholders::_2);

    auto boundDrawHubble = bind(&ogstream::drawHubble, goutPointer, placeholders::_1, placeholders::_2);
    auto DrawHubbleTelescope = [goutPointer](const Position& center, double rotation) {
        goutPointer->drawHubbleTelescope(center, rotation);
    };
    auto DrawHubbleComputer = [goutPointer](const Position& center, double rotation) {
        goutPointer->drawHubbleComputer(center, rotation);
    };
    auto DrawHubbleRight = [goutPointer](const Position& center, double rotation) {
        goutPointer->drawHubbleRight(center, rotation);
    };
    auto DrawHubbleLeft = [goutPointer](const Position& center, double rotation) {
        goutPointer->drawHubbleLeft(center, rotation);
    };
    vector<Part*> hubbleParts = vector<Part*>{
        new Part("HubbleTelescope", 3, DrawHubbleTelescope, 10),
        new Part("HubbleComputer", 2, DrawHubbleComputer, 7),
        new Part("HubbleRight", 2, DrawHubbleRight, 8),
        new Part("HubbleLeft", 2, DrawHubbleLeft, 8)
    };

    auto boundDrawDragon = bind(&ogstream::drawCrewDragon, goutPointer, placeholders::_1, placeholders::_2);
    auto drawDragonCenter = [goutPointer](const Position& center, double rotation) {
        goutPointer->drawCrewDragonCenter(center, rotation);
        
    };
    auto drawDragonLeft = [goutPointer](const Position& center, double rotation) {
        goutPointer->drawCrewDragonLeft(center, rotation);
    };
    auto drawDragonRight = [goutPointer](const Position& center, double rotation) {
        goutPointer->drawCrewDragonRight(center, rotation);
    };
    vector<Part*> DragonParts = vector<Part*>{
        new Part("DragonCenter", 4, drawDragonCenter, 6),
        new Part("DragonLeft", 6, drawDragonLeft, 2),
        new Part("DragonRight", 6, drawDragonRight, 2)
    };

    auto boundDrawStarlink = bind(&ogstream::drawStarlink, goutPointer, placeholders::_1, placeholders::_2);
    auto drawStarlinkBody = [goutPointer](const Position& center, double rotation) {
        goutPointer->drawStarlinkBody(center, rotation);
    };
    auto drawStarlinkArray = [goutPointer](const Position& center, double rotation) {
        goutPointer->drawStarlinkArray(center, rotation);
    };
    vector<Part*> starLinkParts = vector<Part*>{
        new Part("StarlinkBody", 3, drawStarlinkBody, 2),
        new Part("StarlinkArray", 3, drawStarlinkArray, 4)
    };

    vector<Object*> MasterObjectList = vector<Object*>{
        new Satalite("Sputnik", Angle(), Position(-36515095.13, 21082000.0), Velocity(2050, 2684.68), 4, vector<Part*>(), boundDrawSputnik, 4),

        generateGPS(Position(0, 26560000), Velocity(-3880, 0), goutPointer),
        generateGPS(Position(0, -26560000), Velocity(3880, 0), goutPointer),
        generateGPS(Position(23001634.72, 13280000), Velocity(-1940, 3360.18), goutPointer),
        generateGPS(Position(23001634.72, -13280000), Velocity(1940, 3360.18), goutPointer),
        generateGPS(Position(-23001634.72, -13280000), Velocity(1940, -3360.18), goutPointer),
        generateGPS(Position(-23001634.72, 13280000), Velocity(-1940, -3360.18), goutPointer),


        new Satalite("Hubble", Angle(), Position(0, -42164000), Velocity(3100, 0), 0, hubbleParts, boundDrawHubble, 10),

        new Satalite("Dragon", Angle(), Position(0, 8000000), Velocity(-7900, 0), 2, DragonParts, boundDrawDragon, 7),

        new Satalite("StarLink", Angle(), Position(0, 13020000), Velocity(5800, 0), 2, starLinkParts, boundDrawStarlink, 6)
    };

    
    //auto boundDrawShip = bind(&ogstream::drawShip, uiPointer, placeholders::_1, placeholders::_2);
    auto boundDrawShip = bind(&ogstream::drawShip, &gout, placeholders::_1, placeholders::_2, placeholders::_3);

    DreamChaser* chaser = new DreamChaser(Position(-450, 450, true), Angle(), Velocity(0, -2),
        &MasterObjectList, boundDrawShip, 10);

    // Initialize the demo
    Demo demo(ptUpperRight, &MasterObjectList, chaser, &gout);


  

    // set everything into action
    ui.run(callBack, &demo);


    return 0;
}
