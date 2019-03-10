#include "SmartGL.h"
#include <math.h>

using namespace std;



class fahad : public Activity    //In the momentum cpp other then image loading no smartl is used means yu can completely do it on your own
{
private:
	float accelaration;
	float distance;
	float velocity;
	float time;
	float velocity_shown;

	float xCordTrack1;
	float xCordTrack2;
	float xCordTrack3;
	

	Button increaseSpeed;
	Button decreaseSpeed;
	Button SpeedShow;
	Button Distance_Travelled;
	Button Increase_Accelaration;
	Button Decrease_Accelaration;
	Button ShowAccelaration;
	Button Time;
	Button Start;
	Button reset;

	int sentinel;
	int counter;
	ImageView background, car;

public:
	fahad() :increaseSpeed("Speed ++", 50, 500, 85, 25, Black),
		SpeedShow("Speed  =", 50, 550, 85, 25, Black),
		decreaseSpeed("Speed --", 50, 450, 85, 25, Black),
		Increase_Accelaration("Accel ++", 200, 500, 85, 25, Black),
		ShowAccelaration("Accel  = ", 200, 550, 85, 25, Black),
		Decrease_Accelaration("Accel --", 200, 450, 85, 25, Black),
		Time("Time:", 350, 500, 85, 25, Black),
		Distance_Travelled("Distance:", 500, 500, 85, 25, Black),
		Start("Start", 650, 525, 85, 25, Black),
		reset("Reset", 650, 475, 85, 25, Black)
	
	{
		
		sentinel = 0;
		counter = 0;

		xCordTrack1 = 100;
		xCordTrack2 = 400;
		xCordTrack3 = 700;

		velocity = 0;
		accelaration = 0;
		distance = 0;
		time = 0;
		velocity_shown = 0;

		background.loadFromFile("road.jpg");

		car.loadFromFile("car.tga");
		car.setPosition(350,290);
		car.setSize(100,100);
	};

	void Display() const
	{
		glClear(GL_COLOR_BUFFER_BIT);
		background.Display();
		



		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(0, 400);
		glVertex2f(800, 400);
		glVertex2f( 800, 407);
		glVertex2f(0, 407);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(0, 250);
		glVertex2f(800, 250);
		glVertex2f(800, 257);
		glVertex2f(0, 257);
		glEnd();


		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(xCordTrack1, 323);
		glVertex2f(xCordTrack1 + 80, 323);
		glVertex2f(xCordTrack1+80, 330);
		glVertex2f(xCordTrack1 , 330);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(xCordTrack2, 323);
		glVertex2f(xCordTrack2 + 80, 323);
		glVertex2f(xCordTrack2 + 80, 330);
		glVertex2f(xCordTrack2, 330);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(1.0, 1.0, 1.0);
		glVertex2f(xCordTrack3, 323);
		glVertex2f(xCordTrack3 + 80, 323);
		glVertex2f(xCordTrack3 + 80, 330);
		glVertex2f(xCordTrack3, 330);
		glEnd();

		car.Display();
		SpeedShow.Display();
		ShowAccelaration.Display();
		increaseSpeed.Display();
		decreaseSpeed.Display();
		Distance_Travelled.Display();
		Increase_Accelaration.Display();
		Decrease_Accelaration.Display();
		Time.Display();
		Start.Display();
		reset.Display();
		std::ostringstream stream1;
		gout.setPosition(100, 542);
		stream1 << velocity_shown;
		gout << stream1.str();


		std::ostringstream stream2;
		gout.setPosition(400, 492);
		stream2 << time;
		gout << stream2.str();

		std::ostringstream stream3;
		gout.setPosition(250, 542);
		stream3 << accelaration;
		gout << stream3.str();

		std::ostringstream stream4;
		gout.setPosition(550, 492);
		stream4 << distance;
		gout << stream4.str();



  	}

	void KeyboardEvents(unsigned char& key, int& mouseX, int& mouseY)
	{
		if (key == 8)
		{
			mActivityManager->setActive("Activity2");
		}

		glutPostRedisplay();
	}

	void Reset(){

		sentinel = 0;
		counter = 0;

		xCordTrack1 = 100;
		xCordTrack2 = 400;
		xCordTrack3 = 700;

		velocity = 0;
		accelaration = 0;
		distance = 0;
		time = 0;
		velocity_shown = 0;
	}
	void MouseEvents(int& button, int& state, int& x, int& y)
	{
		if (state == 0 && button == 0)
		{
			if (increaseSpeed.isClicked(x, y)){
				velocity -= 1;
				velocity_shown += 10;
	
				

		
			}
			if (Increase_Accelaration.isClicked(x, y)){
				accelaration++;
			}
			if (Start.isClicked(x, y)){
				START();
			}
			if (Decrease_Accelaration.isClicked(x, y)){
				accelaration--;
			}
			if (decreaseSpeed.isClicked(x, y)){
				velocity++;
				velocity_shown -= 10;
			}
			if (reset.isClicked(x, y)){
				Reset();
			}
		}
	}
	void START(){
		if (sentinel == 0){
			sentinel = 1;
		}
		else sentinel = 0;
		
	}
	
	void TimerGL(int &)
	{
		if (sentinel == 1){
			if (velocity <0){

				xCordTrack1 += velocity;
				xCordTrack2 += velocity;
				xCordTrack3 += velocity;

				if ((xCordTrack3 +80) <=0){
					xCordTrack3 = 800;
				}

				if ((xCordTrack2 + 80) <= 0){
					xCordTrack2 = 800;
				}
				if ((xCordTrack1 + 80) <= 0){
					xCordTrack1 = 800;
				}


			}
			else if (velocity>0) {
				xCordTrack1 += velocity;
				xCordTrack2 += velocity;
				xCordTrack3 += velocity;

				if ((xCordTrack3)  >= 800){
					xCordTrack3 = -80;
				}

				if ((xCordTrack2) >= 800){
					xCordTrack2 = -80;
				}
				if ((xCordTrack1) >= 800){
					xCordTrack1 = -80;
				}

			}
			

			counter++;
			if (counter % 60 == 0){
				time++;
				if (accelaration > 0){
					velocity -= accelaration*0.1;
					velocity_shown += accelaration;
					distance = 0.5*abs(accelaration)*time*time;

				}
				if (accelaration == 0){
					distance = distance + (velocity_shown);
				}
				if (accelaration < 0){
					velocity -= accelaration*0.1;
					velocity_shown += accelaration;
					distance = 0.5*(accelaration)*time*time;
				}
			
			}

		}
	}
};



