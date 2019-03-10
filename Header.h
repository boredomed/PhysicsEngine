#include "SmartGL.h"
#define PI 3.1415

using namespace std;

class mathh : public Activity    //In the momentum cpp other then image loading no smartl is used means yu can completely do it on your own
{
private:
	float resistance, current, voltage;

	Button Resistance_Increase;
	Button Resistance_Decrease;

	Button Voltage_Increase;
	Button Voltage_Decrease;

	Button Current_Increase;
	Button Current_Decrease;

	Button ComputeR, ComputeC, ComputeV;

	Button Reset;


	ImageView background, lamp;
public:
	mathh() : Resistance_Increase("R +", 100, 550, 85, 25, Black),
		Resistance_Decrease("R -", 100, 500, 85, 25, Black),
		Voltage_Increase("V +", 300, 550, 85, 25, Black),
		Voltage_Decrease("V -", 300, 500, 85, 25, Black),
		Current_Increase("I +", 500, 550, 85, 25, Black),
		Current_Decrease("I -", 500, 500, 85, 25, Black),
		ComputeC("Find C", 700, 450, 85, 25, Black),
		ComputeV("Find V", 700, 500, 85, 25, Black),
		ComputeR("Find R", 700, 550, 85, 25, Black),
		Reset("Reset", 700, 400, 85, 25, Black)
	{
		voltage = 0;
		current = 0;
		resistance = 0;
		background.loadFromFile("bablo.jpg");
		lamp.loadFromFile("lamp.png");

		lamp.setPosition(430, 300);
		lamp.setSize(40, 40);

	};
	void reset(){
		voltage = 0;
		current = 0;
		resistance = 0;
	}
	void Display() const
	{
		glClear(GL_COLOR_BUFFER_BIT);
	
		background.Display();
		lamp.Display();
		Resistance_Decrease.Display();
		Resistance_Increase.Display();
		Voltage_Decrease.Display();
		Voltage_Increase.Display();
		Current_Decrease.Display();
		Current_Increase.Display();
		ComputeC.Display();
		ComputeR.Display();
		ComputeV.Display();
		Reset.Display();

		glBegin(GL_POLYGON);
		glColor3f(0.5, 0.6, 1.0);
		glVertex2f(200, 300);
		glVertex2f(250, 300);
		glVertex2f(250, 303);
		glVertex2f(200, 303);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.5, 0.6, 1.0);
		glVertex2f(215, 292);
		glVertex2f(235, 292);
		glVertex2f(235, 297);
		glVertex2f(215, 297);
		glEnd();


		glBegin(GL_POLYGON);
		glColor3f(0.5, 0.6, 1.0);
		glVertex2f(225, 303);
		glVertex2f(226, 303);
		glVertex2f(226, 400);
		glVertex2f(225, 400);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.5, 0.6, 1.0);
		glVertex2f(225, 400);
		glVertex2f(360, 400);
		glVertex2f(360, 401);
		glVertex2f(225, 401);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.5, 0.6, 1.0);
		glVertex2f(360, 390);
		glVertex2f(400, 390);
		glVertex2f(400, 410);
		glVertex2f(360, 410);
		glEnd();



		glBegin(GL_POLYGON);
		glColor3f(0.5, 0.6, 1.0);
		glVertex2f(400, 400);
		glVertex2f(450, 400);
		glVertex2f(450, 401);
		glVertex2f(400, 401);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.5, 0.6, 1.0);
		glVertex2f(450, 400);
		glVertex2f(451, 400);
		glVertex2f(451, 340);
		glVertex2f(450, 340);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.5, 0.6, 1.0);
		glVertex2f(450, 300);
		glVertex2f(451, 300);
		glVertex2f(451, 250);
		glVertex2f(450, 250);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(0.5, 0.6, 1.0);
		glVertex2f(450, 250);
		glVertex2f(225, 250);
		glVertex2f(225, 249);
		glVertex2f(450, 249);
		glEnd();


		glBegin(GL_POLYGON);
		glColor3f(0.5, 0.6, 1.0);
		glVertex2f(225, 249);
		glVertex2f(226, 249);
		glVertex2f(226, 297);
		glVertex2f(225, 297);
		glEnd();

		std::ostringstream streamCurrent;
		gout.setPosition(485, 320);
		streamCurrent << current;
		gout << streamCurrent.str();

		std::ostringstream streamCurrentShow;
		gout.setPosition(485, 305);
		streamCurrentShow << "Amps";
		gout << streamCurrentShow.str();


		std::ostringstream streamVoltage;
		gout.setPosition(160, 320);
		streamVoltage << voltage;
		gout << streamVoltage.str();

		std::ostringstream streamVoltageShow;
		gout.setPosition(150, 300);
		streamVoltageShow << "Volts";
		gout << streamVoltageShow.str();


		std::ostringstream streamR;
		gout.setPosition(375, 435);
		streamR << resistance << " Ohms";
		gout << streamR.str();

		std::ostringstream streamRShow;
		gout.setPosition(350, 420);
		streamRShow << "Resistance";
		gout << streamRShow.str();


	}

	void KeyboardEvents(unsigned char& key, int& mouseX, int& mouseY)
	{
		if (key == 8)
		{
			mActivityManager->setActive("Activity2");
		}

		glutPostRedisplay();
	}
	void calculateR(){
		resistance = voltage / current;
	}
	void calculateV(){
		voltage = current*resistance;
	}
	void calculateI(){
		current = voltage / resistance;
	}

	void MouseEvents(int& button, int& state, int& x, int& y)
	{
		if (state == 0 && button == 0)
		{
			if (Resistance_Increase.isClicked(x,y)){
				resistance += 10;
			
			}
			if (Resistance_Decrease.isClicked(x, y)){
				if (resistance>=10)
				resistance -= 10;

			}
			if (Voltage_Increase.isClicked(x, y)){
				voltage += 10;

			}
			if (Voltage_Decrease.isClicked(x, y)){
				if (voltage>= 10)
				voltage -= 10;

			}

			if (Current_Increase.isClicked(x, y)){
				current += 10;

			}
			if (Current_Decrease.isClicked(x, y)){
				if (current >= 10)
				current -= 10;

			}
			if (ComputeC.isClicked(x, y)){
				calculateI();
			}
			if (ComputeR.isClicked(x, y)){
				calculateR();
			}
			if (ComputeV.isClicked(x, y)){
				calculateV();
			}
			if (Reset.isClicked(x, y)){
				reset();
			}
		}
	}

	void TimerGL(int &)
	{

	}
};

