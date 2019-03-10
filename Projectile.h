#include "SmartGL.h"
#include <sstream>
#include <vector>
#include "math.h"
using namespace std;

const float G = 0.0000098f;		// Gravitational acceleration in pixels per millisecond square
const float PI = 3.14159265359;	// Value of constant PI
vector<int> X, Y;				// Array to store the current coordinates of projectile

class Projectile : public ImageView
{
	float velocityX = 0.f;			// Horizontal component of the velocity
	float velocityY = 0.f;			// Vertical component of the velocity

	bool isMoving = false;			// Flag to check if the projectile is in motion or not
	float Range = 0.0F;
	float Height = 0.0F;

	int change = 2;

public:
	Projectile(int x, int y, int width, int height){
		if (change == 1)
		loadFromFile("monkey.png");
		else if (change == 2)
		loadFromFile("apple.png");

		setSize(width, height);
		setPosition(x, y);
	}

	void setchange(int x)   //To set the character
	{
		change = x;
	}

	/*
	Sets velocity of the projectile with which it will move. Note that the projectile
	would not start moving unless startSimulation() method is called.

	@param	speed	speed of motion in pixels per second
	@param	angle	direction of motion in degrees
	*/
	void setVelocity(float speed, float angle){
		// Convert from degrees to radians
		angle *= PI / 180.f;

		// Get velocity components
		velocityX = speed * cos(angle);
		velocityY = speed * sin(angle);

	}

	float getRange(float speed, float angle)
	{
		// Convert from degrees to radians
		angle *= PI / 180.f;

		Range = speed*speed*sin(2*angle) / G;
	
		return Range;

	}


	/**
	Updates the state of the Projectile after every frame.

	@param	time	milliseconds past since the last frame was updated.
	*/
	void update(int time){
		if (isMoving){
			// Get existing position
			int x = getX();
			int y = getY();

			// Apply gravitational effect
			velocityY = velocityY - G * time;				// v = u + at
			y += velocityY * time - 0.5 * G * time * time;	// s = ut + 1/2at^2

			// Move horizontally
			x += velocityX * time;	// s = ut + 1/2at^2

			X.push_back(x);
			Y.push_back(y);

			

			// Put the Projectile on ground
			if (y <= 0){
				y = 0;
				stopSimulation();
			}

			// Set new position
			setPosition(x, y);
		}
	}

	/*
	Starts the projectile's motion.
	*/
	void startSimulation(){
		isMoving = true;
	}

	/*
	Stops the projectlie's motion.
	*/
	void stopSimulation(){
		velocityX = 0.f;
		velocityY = 0.f;
		Range = 0;
		isMoving = false;
	}

	int draw_endpoint = 0;

};

class ProjectileSimulation : public Activity
{
	float speed = 0.f;
	Button incSpeed, decSpeed;

	float angle = 45.f;
	Button incAngle, decAngle;

	float heightt = 0;
	Button height;

	float Range = 0;
	Button range;

	Button reset;

	bool started = false;
	Button startAnimation;

	int change = 2;
	Button Change;

	ImageView background, plus, minus;
	Projectile box;

public:
	ProjectileSimulation() :
		box(25, 0, 50, 60),
		incSpeed("Speed: +", 50, 500, 85, 25, Black),
		decSpeed("-", 135, 500, 25, 25, Black),
		incAngle("Angle: +", 50, 450, 85, 20, Black),
		decAngle("-", 135, 450, 25, 25, Black),
		startAnimation("Start", 250, 450, 75, 25, Black),
		range("Range: ",450, 500, 85, 25, Black),
		height("Height:",450,470,85,25,Black),
        reset("Reset Path",450,430,150,25,Black)
	{
		// Load graphics
		background.loadFromFile("back.jpg");
	}

	void Display() const
	{
		glClear(GL_COLOR_BUFFER_BIT);
		background.Display();

		incSpeed.Display();
		decSpeed.Display();
		incAngle.Display();
		decAngle.Display();
		range.Display();
		height.Display();
		reset.Display();

		std::ostringstream stream1;
		gout.setPosition(100, 492);
		stream1 << speed;
		gout << stream1.str();

		std::ostringstream stream2;
		gout.setPosition(100, 442);
		stream2 << angle;
		gout << stream2.str();

		std::ostringstream stream3;
		gout.setPosition(500, 495);
		stream3 << Range;
		gout << stream3.str();

		std::ostringstream stream4;
		gout.setPosition(500, 460);
		stream4 << heightt;
		gout << stream4.str();

		startAnimation.Display();
		box.Display();

		glEnable(GL_BLEND);
		glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		for (int i = 0; i < X.size(), i < Y.size(); i++)
			glVertex2f(X[i], Y[i]);
		glEnd();
		glFlush();
		glDisable(GL_BLEND);
	}
	
	    void KeyboardEvents(unsigned char& key, int& mouseX, int& mouseY)
		{
			if (key == 8)
			{
				mActivityManager->setActive("Activity2");
			}
	
			glutPostRedisplay();
		}
	
	void MouseEvents(int& button, int& state, int& x, int& y){
		if (state == 0 && button == 0)
		{
			if (startAnimation.isClicked(x, y))
			{
				if (!started){
					box.setVelocity(speed / 100, angle);
					box.startSimulation();
					startAnimation.setLabel("Reset");
					started = true;
					
				}
				else{
					box.setPosition(25, 0);
					startAnimation.setLabel("Start");
					started = false;
				    }

		}
			else if (incSpeed.isClicked(x, y)){
				speed += 1.f;
				if (speed > 9.f) speed = 9.f;
			}
			else if (decSpeed.isClicked(x, y)){
				speed -= 1.f;
				if (speed < 2.f) speed = 2.f;
			}
			else if (incAngle.isClicked(x, y)){
				angle += 1.f;
				if (angle > 90.f) angle = 90.f;
			}
			else if (decAngle.isClicked(x, y)){
				angle -= 1.f;
				if (angle < 10.f) angle = 10.f;
			}
			else if (reset.isClicked(x, y)){
				//reset.setLabel("set");
				X.clear();
				Y.clear();
			}

			
		}
	}

	void TimerGL(int &)
	{
		box.update(125);                                 //Giving time to the box

	    Range = (box.getRange(speed / 100, angle))/100;
		Range = floorf(Range * 100) / 100;               //Rounding of to two decimal place
		
		heightt = ((box.getRange(speed / 100, angle))*tan(angle*PI/180))/400;
		heightt = floorf(heightt * 100) / 100;           //Rounding of to two decimal place

		box.setchange(change);
	
	}
};
