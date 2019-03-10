#include "SmartGL.h"
#include "Colors.h"
#include "Projectile.h"
#include "Momentum.h"
#include "Header.h"
#include "Fahad.h"

//MENU of simulations
class Simulations
	: public Activity
{
	ImageView background;
	ImageView sim1, sim2, sim3, sim4;
	Button Simulation1, Simulation2, Simulation3, Simulation4;
public:
	Simulations()
		: Simulation1("",  20, 310, 370, 270, Cyan)
		, Simulation2("",  20,  20, 370, 270, VeryLightPurple)
		, Simulation3("", 410, 310, 370, 270, Blue_Clr)
		, Simulation4("", 410,  20, 370, 270, BlueViolet)
	{
		background.loadFromFile("sim.jpg");

		sim1.loadFromFile("angrybird.jpg");
		sim2.loadFromFile("Momentum.png");
		sim3.loadFromFile("eelec.jpg");
		sim4.loadFromFile("race.jpg");

		Simulation1.setImage(&sim1);
		Simulation2.setImage(&sim2);
		Simulation3.setImage(&sim3);
		Simulation4.setImage(&sim4);
	}

	void Display() const
	{
		glClear(GL_COLOR_BUFFER_BIT);

		background.Display();
		Simulation1.Display();
		Simulation2.Display();
		Simulation3.Display();
		Simulation4.Display();

		gout.setPosition(200, 5);
		gout.setFont(GLUT_BITMAP_9_BY_15);
		gout.setLineWidth(200);
	
	}

	void MouseEvents(int& button, int& state, int& x, int& y)    //Selection of simulation
	{
		// ImageButton.isClicked(x - width/2, y + height/2)

		if (Simulation1.isClicked(x - 185, y + 135))
		{
			mActivityManager->setActive("Projectile");
		}

		else if (Simulation2.isClicked(x - 185, y + 135))
		{
			mActivityManager->setActive("Momentum");
		}

		else if (Simulation3.isClicked(x - 185, y + 135))
		{
			mActivityManager->setActive("Mathh");
		}

		else if (Simulation4.isClicked(x - 185, y + 135))
		{
			mActivityManager->setActive("Fahad");
		}
	}

};

int gWidth = 800, gHeight = 600;

int main()
{
	SmartGL app(gWidth, gHeight, "Virtual Simulations");

	mActivityManager->addActivity(new Simulations(), "Activity2");
	mActivityManager->addActivity(new ProjectileSimulation(), "Projectile");
	mActivityManager->addActivity(new momentum(), "Momentum");
	mActivityManager->addActivity(new mathh(), "Mathh");
	mActivityManager->addActivity(new fahad(), "Fahad");
	

	mActivityManager->setActive("Activity2");    

	app.startProgram();
}