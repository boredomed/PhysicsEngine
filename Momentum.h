#include "SmartGL.h"
#include "math.h"
using namespace std;

#define INELASTICITY 0.65
#define _INELASTICITY 0.40 
#define __INELASTICITY 0.20 


#define RADIUS 35

float t = 0, finish = 0, start = 0;

int current_1 = 0;

extern int gHeight, gWidth;

typedef struct COLOR{
	float R;
	float G;
	float B;
};

ImageView i1;

namespace GFX{
	void renderBitmapString(float x, float y, char *string) {
		y = gHeight - y;
		char *c;
		glRasterPos2f(x, y);
		for (c = string; *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
		}
	}

	void renderBitmapString2(float x, float y, char *string) {
		y = gHeight - y;
		char *c;
		glRasterPos2f(x, y);
		for (c = string; *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
		}
	}

	void draw_Circle(float a, float b, float r, float initangle, COLOR c1)  //(a,b)=(x,y) of centre. R is radius
	{
		i1.setSize(r, r);
		i1.setPosition(a, gHeight - b);
		i1.Display();
	}
};

class BALL{
private:
	float
		posX,
		posY,
		velX,
		velY,
		accelX,
		accelY,
		rotation;
	bool gravity;
public:
	BALL()
	{
		posX = 0,
			posY = 0,
			velX = 0,
			velY = 0,
			accelX = 0,
			accelY = 0,
			rotation = 0;
		gravity = true;
	}

	BALL(float X, float Y, float VX, float VY, float AX, float AY, float theta)
	{
		    posX = X,
			posY = Y,
			velX = VX,
			velY = VY,
			accelX = AX,
			accelY = AY,
			rotation = theta;
		gravity = true;
	}

	void Move(float time)
	{
		posX += velX*time / 1000;
		posY += velY*time / 1000;
		velX += accelX*time / 1000;
		gravity ? velY += (accelY + 980)*time / 1000 : velY += accelY*time / 1000;
		if (posY > gHeight - RADIUS)
		{
			posY = gHeight - RADIUS;

			if (current_1 == 0)
			velY = -INELASTICITY*velY;

			else if (current_1 == 1)
			velY = -_INELASTICITY*velY;

			else if (current_1 == 2)
				velY = -__INELASTICITY*velY;
		}
		else if (posY < 0 + RADIUS)
		{
			posY = 0 + RADIUS;

			if (current_1 == 0)
			velY = -INELASTICITY*velY;

			else if (current_1 == 1)
			velY = -_INELASTICITY*velY;


			else if (current_1 == 2)
				velY = -__INELASTICITY*velY;
		}
		else if (posX < 0 + RADIUS)
		{
			posX = 0 + RADIUS;

			if (current_1 == 0)
			velX = -INELASTICITY*velX;

			else if (current_1 == 1)
			velX = -_INELASTICITY*velX;


			else if (current_1 == 2)
				velY = -__INELASTICITY*velY;
		}
		else if (posX > 800 - RADIUS)
		{
			posX = 800 - RADIUS;

			if (current_1 == 0)
			velX = -INELASTICITY*velX;

			else if (current_1 == 1)
			velX = -_INELASTICITY*velX;

			else if (current_1 == 2)
				velY = -__INELASTICITY*velY;
		}

	}

	void display()
	{
		COLOR c1 = { 0.3, 0.9, 0.2 };
		GFX::draw_Circle(posX, posY, RADIUS, rotation, c1);
		float angle = atan2f(velY, velX);
		float magnitude = sqrtf(velX * velX + velY * velY) / 100;


	}

	void SetValues()
	{

		start = 0, finish = 0;
		
	}

	void SetXY(const float& X, const float& Y)
	{
		posX = X;
		posY = Y;
	}

	void SetVelocity(const float& vx, const float& vy)
	{
		velX = vx;
		velY = vy;
	}

	void setaccel(const float& ax, const float& ay)
	{
		accelX = ax;
		accelY = ay;
	}

	void operator &(BALL &b2)
	{
		float Distance = sqrtf((posX - b2.posX)*(posX - b2.posX) + (posY - b2.posY)*(posY - b2.posY));
		if (Distance <= 2 * RADIUS)
		{
			float temp1, temp2, CollideAxis, VelParallel1, VelNormal1, VelParallel2, VelNormal2, velocity1, velocity2, angle1, angle2;
			velocity1 = sqrtf(velX * velX + velY * velY);
			velocity2 = sqrtf(b2.velX * b2.velX + b2.velY * b2.velY);

			angle1 = atan2f(velY, velX);
			angle2 = atan2f(b2.velY, b2.velX);

			CollideAxis = atan2f(b2.posY - posY, b2.posX - posX);
			VelParallel1 = velocity1 * cosf(CollideAxis - angle1);
			VelNormal1 = velocity1 * sinf(CollideAxis - angle1);
			VelParallel2 = velocity2 * cosf(CollideAxis - angle2);
			VelNormal2 = velocity2 * sinf(CollideAxis - angle2);


			temp1 = VelParallel1;

			if (current_1 == 0)
			{
				VelParallel1 = INELASTICITY*VelParallel2;
				VelParallel2 = INELASTICITY*temp1;
			}

			else if (current_1 == 1)
			{
				VelParallel1 = _INELASTICITY*VelParallel2;
				VelParallel2 = _INELASTICITY*temp1;
			}


			else if (current_1 == 2)
			{
				VelParallel1 = __INELASTICITY*VelParallel2;
				VelParallel2 = __INELASTICITY*temp1;
			}

			//FINDING VELOCITIES AFTER EXCHANGING PARALLEL COMPONENTS
			velocity1 = sqrtf(VelParallel1*VelParallel1 + VelNormal1*VelNormal1);
			velocity2 = sqrtf(VelParallel2*VelParallel2 + VelNormal2*VelNormal2);

			angle1 = atan2f(VelNormal1, VelParallel1);
			angle2 = atan2f(VelNormal2, VelParallel2);

			posX = posX - ((2 * RADIUS - Distance) / 2)*cosf(CollideAxis);
			posY = posY - ((2 * RADIUS - Distance) / 2)*sinf(CollideAxis);
			b2.posX = b2.posX + ((2 * RADIUS - Distance) / 2)*cosf(CollideAxis);
			b2.posY = b2.posY + ((2 * RADIUS - Distance) / 2)*sinf(CollideAxis);

			velX = velocity1 * cosf(CollideAxis - angle1);
			velY = velocity1 * sinf(CollideAxis - angle1);
			b2.velX = velocity2 * cosf(CollideAxis - angle2);
			b2.velY = velocity2 * sinf(CollideAxis - angle2);
		}
	}

	float GetPosX() const
	{
		return posX;
	}

	float GetPosY() const
	{
		return posY;
	}

	float GetVx()
	{
		return velX;
	}

	float GetVy()
	{
		return velY;
	}

	float GetAx()
	{
		return accelX;
	}

	float GetAy()
	{
		return (gravity ? accelY + 980 : accelY);
	}

private:
	BALL* next;
public:
	BALL* first;
};

class _INPUT{
private:
	bool KeyState[256];
	bool MouseState[3];
	float Mouse_X;
	float Mouse_Y;

public:
	_INPUT()
	{
		for (int i = 0; i < 256; i++)
			KeyState[i] = false;
	}

	bool GetKeyState(unsigned int key) const
	{
		return KeyState[key];
	}

	void GetMouseXY(float &X, float &Y) const
	{
		X = Mouse_X;
		Y = Mouse_Y;
	}

	bool GetMouseState(int button)
	{
		return MouseState[button];
	}

	void MouseEventFunc(int button, int state, int X, int Y)
	{
		state = !state;
		Mouse_X = X;
		Mouse_Y = Y;
		MouseState[button] = state;
	}

	void KeyDownFunc(unsigned char key)
	{
		KeyState[key] = true;
	}

	void KeyUpFunc(unsigned char key)
	{
		KeyState[key] = false;
	}
};

_INPUT m_input;
BALL b1(40, 600, 600, -1000, 0, 0, 5);
BALL b2(770, 600, -600, -970, 0, 0, 10);

int current = 0;

class momentum: public Activity
{
	ImageView back;
	
	float speed = 1;
	Button Speed;

	float speed2 = 1;
	Button Speed_2;

	Button IncElasticity;
	Button DecElasticity;

	float ax, ay;
	float accel;

public:
	momentum() : Speed("Velocity 1:", 57, 550, 130, 25, BlueViolet), Speed_2("Velocity2:+", 57, 520, 130, 25, Purple),
		IncElasticity("Elasticity+:", 250, 550, 130, 25,LightPurple), DecElasticity("-",340,550,20,25,LightGreen)
	{
		back.loadFromFile("backg.png");

		if (current_1 == 0)
			i1.loadFromFile("basket.png");
	}

	float get_Speed()
	{
		return speed;
	}

	float get_Speed2()
	{
		return speed2;
	}

	void keyOperations()			// FUNCTION FOR KEY OPERATIONS THAT ARE NOT OF TOGGLE TYPE
	{
		if (m_input.GetKeyState('s'))
		{
			cout << "Enter Values for Ball 1 : " << endl;
			b1.SetValues();
		}
		
		
			if (m_input.GetMouseState(GLUT_LEFT_BUTTON))
			{
				float x, y;
				m_input.GetMouseXY(x, y);
				b1.SetXY(x, y);
				b1.SetVelocity(0, 0);
			}

			if (m_input.GetMouseState(GLUT_RIGHT_BUTTON))
			{
				float x, y;
				m_input.GetMouseXY(x, y);
				b2.SetXY(x, y);
				b2.SetVelocity(0, 0);
			}
		
		if (m_input.GetKeyState('d'))
		{
			cout << "Enter Values for Ball 2 : " << endl;
			b2.SetValues();
		}
	}

	void MouseEvents(int& button, int& state, int& X, int& Y)
	{
		m_input.MouseEventFunc(button, state, X, Y);

		if (state == 0 && button == 0)
		{
			if (Speed.isClicked(X,Y))
			{}
			else if (IncElasticity.isClicked(X, Y))
			{
				current_1--;
				if (current_1 == 0)
					//current_1 = 0;
					i1.loadFromFile("basket.png");
			
			}
			else if (DecElasticity.isClicked(X, Y))
			{
				current_1++;
				if (current_1 == 1)
					i1.loadFromFile("football.png");
				else if (current_1 == 2)
				//	current_1 = 2;
					i1.loadFromFile("potato.png");
			}

		}
	}
	
	void KeyboardEvents(unsigned char& key, int& mouseX, int& mouseY)
	{
		m_input.KeyDownFunc(key);

		if (key == 8)
		{
			mActivityManager->setActive("Activity2");
		}
		else if (key == 'p')
		{
			current = 1;
		}
		else if (key == 'o')
		{
			current = 0;
		}
		else if (key == 'i')
		{
			current_1 = 1;
		}
		glutPostRedisplay();
	}

	void KeyboardUpEvents(unsigned char& key, int& x, int& y)
	{
		m_input.KeyUpFunc(key);
	}

	void TimerGL(int& val)
	{
		finish = glutGet(GLUT_ELAPSED_TIME);
		t = finish - start;
		start = finish;
		//if (!pause)
		{
			Display();
			keyOperations();
		}
		b1.Move(t);

		if (current == 1)
		b2.Move(t);
		b1 & b2;
	}

	void Display() const
	{
		glClear(GL_COLOR_BUFFER_BIT);		//clers the screen after display
	
		back.Display();
		Layout();

		IncElasticity.Display();
		DecElasticity.Display();

		b1.display();
		
		if (current == 1)
		{
			b2.display();
			Speed_2.Display();
		}

		Speed.Display();
		
		

		glutSwapBuffers();		//brings the openGl window on the front
	}
	//glColor4f(1, 1, 1, 0.7);

	void Layout() const
	{
		
		char temp[5];
	
		GFX::renderBitmapString(122, 60, "          m/s");
		float vel = sqrtf((b1.GetVx())*(b1.GetVx()) + (b1.GetVy())*(b1.GetVy())) / 100;
		GFX::renderBitmapString(130, 60, _itoa(vel, temp, 10));
		GFX::renderBitmapString(136, 60, ".");
		vel *= 10;
		vel = fmodf(vel, 10);
		GFX::renderBitmapString(138, 60, _itoa(vel, temp, 10));


		//float accel = sqrtf((b1.GetAx()*b1.GetAx()) + (b1.GetAy()*b1.GetAy())) / 100;
		//GFX::renderBitmapString(70, 35, "Accel.  =       m/s2");
		//GFX::renderBitmapString(130, 35, _itoa(accel, temp, 10));
		//GFX::renderBitmapString(136, 35, ".");
		//accel *= 10;
		//accel = fmodf(accel, 10);
		//GFX::renderBitmapString(138, 35, _itoa(accel, temp, 10));

		if (current == 1)
		{
			GFX::renderBitmapString(122, 90, "          m/s");
			vel = sqrtf((b2.GetVx())*(b2.GetVx()) + (b2.GetVy())*(b2.GetVy())) / 100;
			GFX::renderBitmapString(130, 90, _itoa(vel, temp, 10));
			GFX::renderBitmapString(136, 90, ".");
			vel *= 10;
			vel = fmodf(vel, 10);
			GFX::renderBitmapString(138, 90, _itoa(vel, temp, 10));
		}
		/*accel = sqrtf((b2.GetAx()*b2.GetAx()) + (b2.GetAy()*b2.GetAy())) / 100;
		GFX::renderBitmapString(270, 35, "Accel.  =       m/s2");
		GFX::renderBitmapString(330, 35, _itoa(accel, temp, 10));
		GFX::renderBitmapString(336, 35, ".");
		accel *= 10;
		accel = fmodf(accel, 10);
		GFX::renderBitmapString(338, 35, _itoa(accel, temp, 10));*/
	}
};