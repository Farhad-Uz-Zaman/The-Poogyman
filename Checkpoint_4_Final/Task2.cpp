# include "iGraphics.h"


int bckgrnd_x[1000], bckgrnd_y[1000];
int w;
int image1, image2, image3;
int LMouseX, LMouseY, RMouseX, RMouseY;


void iDraw()
{
	//place your drawing codes here

	iClear();
	iShowImage(0, 0, 1000, 600, image1);


	for (int i = 0; i < w; i++)
	{
		iShowImage(bckgrnd_x[i], bckgrnd_y[i], 150, 150, image2);
	}
	iShowImage(RMouseX, RMouseY, 150, 300, image3);

	iSetColor(255, 255, 255);
	iFilledRectangle(150, 5, 650, 25);

	iSetColor(0, 0, 0);

	iText(170, 15, "For draw click left button, For delete click right button ,'q' for exit");
}

/*
function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
	RMouseX = mx;
	RMouseY = my;
}
void iPassiveMouse(int mx, int my)
{
	LMouseX = mx;
	LMouseY = my;
	//place your codes here
}
/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
		if (w < 100)
		{
			bckgrnd_x[w] = mx;
			bckgrnd_y[w] = my;
			w++;
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
		if (w>0)
		{
			w--;
		}
	}
}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if (key == 'q')
	{
		exit(0);
	}
	//place your codes for other keys here
}

/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
	//place your codes for other keys here
}

int main()
{
	//place your own initialization codes here.

	RMouseX = 50, RMouseY = 300;
	w = 0;
	iInitialize(1000, 600, "MouseMove");


	image1 = iLoadImage("images//LAND.png");
	image2 = iLoadImage("images//mario.png");
	image3 = iLoadImage("images//tree.png");
	iStart();
	return 0;
}
