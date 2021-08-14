

# include "iGraphics.h"
#include<string.h>
#include<time.h>
#include<stdio.h>
#include "enemy.h"//contains enemy structure with collision Codes
#include "fireball.h"//contains fireball structure with collision Codes
#include <stdlib.h>
int image1; int heart[5];//heart for life icons, image1 for background
int poogyLife = 5;// life controlling variable
int ed = 5;//determines the incoming speed of the enemy
int lvl = 1; char lvlarray[20];//used to indicate level and show the level,lvlarray for itoa() function

int score = 0; char scorearray[20]; int savescore;//for storing the score and show them
int tc; //not implemented
int a1;//loadimage integer  for enemies;
int b1;//loadimage integer   for fireball;
Enemy enm1(a1, 1000), enm2(a1, 2000), enm3(a1, 3000), enm4(a1, 4000), enm5(a1, 5000);//constructors for enemy structures
Fireball fb1(b1, 2200), fb2(b1, 2000), fb3(b1, 3000), fb4(b1, 4000), fb5(b1, 5000);//constructors for fireball
int sm[5], t = 0;//slideshow images and timer
int  i = 0, a = 150, b = 50;//i is menu control variable and a and b are used to determine the postion of menu buttons
int poogy[2], bck, nm, bck2, dragon;//poggy stores images andbck andbck are backgrounds, dragon for dragon pic, which was no implimented
int width = 1000; //not implemented
char str[100], str2[100];// for stornig names
int len;// name length
int xpos = 30, ypos = 80;//starting positon of poogy
int backxpos = -500;// used for moving background
int back2xpos = (backxpos + 2400);
int state = 0, termination1[6] = { 1, 1, 1, 1, 1, 1 }, termination2[6] = { 1, 1, 1, 1, 1, 1 };//terminqtion1 showing images,termination2 for poogylife decrease and colt for scoring
int terminationfb1[6] = { 1, 1, 1, 1, 1, 1 }, terminationfb2[6] = { 1, 1, 1, 1, 1, 1 };//terminqtionfb1 showing images,terminationfb2 for poogylife decrease and fbolt for scoring,as flags
int colt[5];// for scoring flag
int fbolt[5];//scoring flag
int menut = 0;//menuflag

void sortScore()//manipulating scores
{
	int k;
	char s[10];
	char hi_name[4][100];
	int hiscore[4];
	FILE *fpp = fopen("highscore.txt", "r");
	for (int loop = 0; loop<3; loop++)
	{
		fscanf(fpp, "%s %d", &hi_name[loop], &hiscore[loop]);
	}
	fclose(fpp);
	strcpy(hi_name[3], str);//storing current game data
	hiscore[3] = score;

	for (int loop = 0; loop<4 - 1; loop++)//bubble sort implementation
	{
		for (int x = 0; x<4 - loop - 1; x++)
		if (hiscore[x]<hiscore[x + 1])
		{
			k = hiscore[x];
			hiscore[x] = hiscore[x + 1];
			hiscore[x + 1] = k;
			strcpy(s, hi_name[x]);
			strcpy(hi_name[x], hi_name[x + 1]);
			strcpy(hi_name[x + 1], s);
		}
	}
	FILE *fpwp = fopen("highscore.txt", "w");
	for (int loop = 0; loop<3; loop++)
	{
		fprintf(fpp, "%s %d\n", hi_name[loop], hiscore[loop]);
	}
	fclose(fpwp);


}



void scene()//slideshow which implements a timer
{

	iShowImage(0, 0, 1200, 675, sm[t]);
	iShowImage(0, 0, 1200, 675, sm[t]);
	iShowImage(0, 0, 1200, 675, sm[t]);
	iShowImage(0, 0, 1200, 675, sm[t]);
	iShowImage(0, 0, 1200, 675, sm[t]);

}
void EnemyScene()//controls the enemy structures which also implements a timer
{
	if (enm1.enemyxpos <= 0)
	{
		enm1.enemyxpos = 4250; termination1[0] = 1; termination2[0] = 1; colt[0] = 0;
	}
	if (enm2.enemyxpos <= 0)
	{
		enm2.enemyxpos = 4500; termination1[1] = 1; termination2[1] = 1; colt[1] = 0;
	}
	if (enm3.enemyxpos <= 0)
	{
		enm3.enemyxpos = 4750; termination1[2] = 1; termination2[2] = 1; colt[2] = 0;
	}
	if (enm4.enemyxpos <= 0)
	{
		enm4.enemyxpos = 5000; termination1[3] = 1; termination2[3] = 1; colt[3] = 0;
	}
	if (enm5.enemyxpos <= 0)
	{
		enm5.enemyxpos = 5250; termination1[4] = 1; termination2[4] = 1; colt[4] = 0;
	}
	enm1.enemyxpos -= ed;
	enm2.enemyxpos -= ed;
	enm3.enemyxpos -= ed;
	enm4.enemyxpos -= ed;
	enm5.enemyxpos -= ed;
}
void win()//Winning Screen
{
	sortScore();
	poogyLife = 5; score = 0; xpos = 30; lvl = 1;
	iClear();
	iSetColor(250, 0, 0);
	iFilledRectangle(0, 0, 1200, 675);
	iSetColor(255, 255, 255);
	iText(500, 600, "YOU WIN!!", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(200, 500, "YOU ARE NOW FINALLY ABLE TO RESSURECT YOUR FAMILY ", GLUT_BITMAP_TIMES_ROMAN_24);

}
void FireballScene()//controls the fireballs
{
	if (fb1.fbxpos <= 0)
	{
		fb1.fbxpos = 2250; terminationfb1[0] = 1; terminationfb2[0] = 1; fbolt[0] = 0;
	}
	fb1.fbxpos = fb1.fbxpos - 10;
}
void gameScene(){						//contains the actual gameplay codes
	iShowImage(backxpos, 0, 2400, 675, bck);
	iShowImage(backxpos + 2400, 0, 2400, 675, bck);
	if (!state)
		iShowImage(xpos, ypos, 300, 300, poogy[0]);
	else
		iShowImage(xpos, ypos, 300, 300, poogy[1]);
	if (enm1.CollisionEnemy(xpos + 150) == 0 && termination2[0] == 1 && termination1[0] == 1){	//controls the collisions and decreases scores if not hit
		termination2[0] = 0;
		poogyLife--;
		score = score - 5;
	}
	if (enm2.CollisionEnemy(xpos + 150) == 0 && termination2[1] == 1 && termination1[1] == 1){
		termination2[1] = 0;
		poogyLife--;
		score = score - 5;
	}
	if (enm3.CollisionEnemy(xpos + 150) == 0 && termination2[2] == 1 && termination1[2] == 1){
		termination2[2] = 0;
		poogyLife--; score = score - 5;
	}
	if (enm4.CollisionEnemy(xpos + 150) == 0 && termination2[3] == 1 && termination1[3] == 1){
		termination2[3] = 0;
		poogyLife--; score = score - 5;
	}
	if (enm5.CollisionEnemy(xpos + 150) == 0 && termination2[4] == 1 && termination1[4] == 1){
		termination2[4] = 0;
		poogyLife--;
		score = score - 5;
	}
	if (enm1.CollisionClub(xpos, state) == 1 && termination1[0] == 1) {//vanishes the image and increase points if hit,colt[] is used to flag the score
		iShowImage(enm1.enemyxpos, 110, 300, 350, enm1.enImg);
	}
	else{
		if (colt[0] == 0)
		{
			termination1[0] = 0;
			score = score + 20;
			colt[0] = 1;
		}
	}
	if (enm2.CollisionClub(xpos, state) == 1 && termination1[1] == 1) {
		iShowImage(enm2.enemyxpos, 110, 300, 350, enm2.enImg);
	}
	else {
		if (colt[1] == 0)
		{
			termination1[1] = 0;
			score = score + 20;
			colt[1] = 1;
		}
	}
	if (enm3.CollisionClub(xpos, state) == 1 && termination1[2] == 1) {
		iShowImage(enm3.enemyxpos, 110, 300, 350, enm3.enImg);
	}
	else{
		if (colt[2] == 0)
		{
			termination1[2] = 0;
			score = score + 20;
			colt[2] = 1;
		}
	}
	if (enm4.CollisionClub(xpos, state) == 1 && termination1[3] == 1) {
		iShowImage(enm4.enemyxpos, 110, 300, 350, enm4.enImg);
	}
	else{
		if (colt[3] == 0)
		{
			termination1[3] = 0;
			score = score + 20;
			colt[3] = 1;
		}
	}
	if (enm5.CollisionClub(xpos, state) == 1 && termination1[4] == 1) {
		iShowImage(enm5.enemyxpos, 110, 300, 350, enm5.enImg);
	}
	else{
		if (colt[4] == 0)
		{
			termination1[4] = 0;
			score = score + 20;
			colt[4] = 1;
		}
	}
	if (poogyLife == 5)//shows the life bar according to poogylife variable
	{
		iShowImage(100, 600, 30, 30, heart[0]);
		iShowImage(100 + 30, 600, 30, 30, heart[0]);
		iShowImage(100 + 60, 600, 30, 30, heart[0]);
		iShowImage(100 + 90, 600, 30, 30, heart[0]);
		iShowImage(100 + 120, 600, 30, 30, heart[0]);
	}
	if (poogyLife == 4)
	{
		iShowImage(100, 600, 30, 30, heart[0]);
		iShowImage(100 + 30, 600, 30, 30, heart[0]);
		iShowImage(100 + 60, 600, 30, 30, heart[0]);
		iShowImage(100 + 90, 600, 30, 30, heart[0]);
	}
	if (poogyLife == 3)
	{
		iShowImage(100, 600, 30, 30, heart[0]);
		iShowImage(100 + 30, 600, 30, 30, heart[0]);
		iShowImage(100 + 60, 600, 30, 30, heart[0]);
	}
	if (poogyLife == 2)
	{
		iShowImage(100, 600, 30, 30, heart[0]);
		iShowImage(100 + 30, 600, 30, 30, heart[0]);
	}
	if (poogyLife == 1)
	{
		iShowImage(100, 600, 30, 30, heart[0]);
	}
	if (poogyLife <= 0)
	{
		sortScore();
		i = 0; poogyLife = 5; score = 0; xpos = 30; lvl = 1;
	}
	if (score > 170 && score < 270){
		lvl = 2;
	}
	else if (score > 800)
		lvl = 3;


	if (lvl == 2)
		ed = 10;
	if (lvl == 3)
	{
		ed = 10;
		if (fb1.CollisionClub(xpos, state) == 1 && terminationfb1[0] == 1) {
			iShowImage(fb1.fbxpos, 210, 150, 150, fb1.fbImg);
		}
		else{
			if (fbolt[0] == 0)
			{
				terminationfb1[0] = 0;
				score = score + 20;
				fbolt[0] = 1;
			}
		}
		if (fb1.CollisionFireball(xpos + 150) == 0 && terminationfb2[0] == 1 && terminationfb1[0] == 1){
			termination2[0] = 0;
			poogyLife--;
			score = score - 5;
		}

		
		}
	

		
	

	if (score >= 500)
		i = 8;

	iSetColor(255, 0, 0);
	iText(40, 608, "LIFE:", GLUT_BITMAP_TIMES_ROMAN_24);
	_itoa(score, scorearray, 10);
	_itoa(lvl, lvlarray, 10);
	iText(1010, 608, "SCORE:", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(1100, 608, scorearray, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(500, 608, "LEVEL:", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(590, 608, lvlarray, GLUT_BITMAP_TIMES_ROMAN_24);
}
void changeState(){// controls the poogystate with a timer
	state = 0;
}


void save(){//saves game state if insert is pressed
	FILE *fp1 = fopen("save.txt", "w");
	fprintf(fp1, "%d %d %d", poogyLife, xpos, score);
	fclose(fp1);
}

void load(){//loads the game
	FILE *fp2 = fopen("save.txt", "r");
	fscanf(fp2, "%d %d %d", &poogyLife, &xpos, &score);
	fclose(fp2);
}
void nameInfo(){//inputs the name
	iShowImage(0, 0, 1200, 675, nm);
	iSetColor(255, 0, 0);

	iFilledRectangle(400, 300, 400, 60);
	iSetColor(255, 255, 255);
	iText(405, 325, str, GLUT_BITMAP_HELVETICA_18);
	iText(400, 365, "Enter Name", GLUT_BITMAP_HELVETICA_18);
	FILE *fp = fopen("NameInfo.txt", "w");
	fprintf(fp, "%s", str);
	fclose(fp);

}
void showScore()//Shows the score
{
	char hi_name[3][10];
	char hiscore[3][5];
	FILE *fpp = fopen("highscore.txt", "r");
	for (int loop = 0; loop<3; loop++)
	{
		fscanf(fpp, "%s %s", &hi_name[loop], &hiscore[loop]);
	}
	fclose(fpp);
	iClear();
	iSetColor(0, 0, 255);
	iFilledRectangle(0, 0, 1200, 675);
	iSetColor(255, 255, 255);
	iText(510, 610, "HighScore", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(500, 520, hi_name[0], GLUT_BITMAP_HELVETICA_18);
	iText(600, 520, hiscore[0], GLUT_BITMAP_HELVETICA_18);
	iText(500, 480, hi_name[1], GLUT_BITMAP_HELVETICA_18);
	iText(600, 480, hiscore[1], GLUT_BITMAP_HELVETICA_18);
	iText(500, 440, hi_name[2], GLUT_BITMAP_HELVETICA_18);
	iText(600, 440, hiscore[2], GLUT_BITMAP_HELVETICA_18);
}
void instruction()//Shows the instruction
{
	iSetColor(250, 150, 30);
	iFilledRectangle(0, 0, 1200, 675);
	iSetColor(0, 0, 0);
	iText(480, 620, "Instruction", GLUT_BITMAP_HELVETICA_18);
	iText(400, 520, "1.Use left/right to move", GLUT_BITMAP_HELVETICA_18);
	iText(400, 480, "2.press x or Enter anywhere to return to menu", GLUT_BITMAP_HELVETICA_18);
	iText(400, 440, "3.press 'Load' to run from the last progress", GLUT_BITMAP_HELVETICA_18);
	iText(400, 400, "4.press 'a' to hit enemies and fireball", GLUT_BITMAP_HELVETICA_18);
	iText(400, 360, "5.You will die if you are hit by a fireball and your points will heavily decrease", GLUT_BITMAP_HELVETICA_18);
}

void menu()//The menu and the buttons
{
	iShowImage(0, 0, 1200, 675, image1);
	iSetColor(255, 255, 255);
	iFilledRectangle(90, 365, 150, 50);
	iFilledRectangle(90, 295, 150, 50);
	iFilledRectangle(90, 225, 150, 50);
	iFilledRectangle(90, 155, 150, 50);
	iFilledRectangle(90, 85, 150, 50);
	iSetColor(0, 250, 0);
	iFilledRectangle(1000, 40, 150, 50);
	iFilledRectangle(600, 40, 150, 50);
	iSetColor(0, 0, 0);
	iText(140, 385, "Start", GLUT_BITMAP_HELVETICA_18);
	iText(140, 315, "Load", GLUT_BITMAP_HELVETICA_18);
	iText(127, 245, "Instruction", GLUT_BITMAP_HELVETICA_18);
	iText(130, 175, "HighScore", GLUT_BITMAP_HELVETICA_18);
	iText(140, 105, "Quit", GLUT_BITMAP_HELVETICA_18);
	//iText(140, 105, "Quit", GLUT_BITMAP_HELVETICA_18);g
	iText(1050, 60, "Story", GLUT_BITMAP_HELVETICA_18);
	iText(650, 60, "Name", GLUT_BITMAP_HELVETICA_18);
	menut = 1;
}

void iDraw()
{
	//place your drawing codes here
	iClear();
	menu();
	if (i == 1){ gameScene(); }
	if (i == 6){ nameInfo(); }
	if (i == 5){ scene(); }
	if (i == 4){ showScore(); }
	if (i == 3)
		instruction();
	if (i == 2){ load(); i = 0; }
	if (i == 8)win();
}

/*
function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
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
		if (i == 0){//manipulation of menu control variables according to mouse cursor positions
			if (menut&&mx > 90 && mx<90 + a &&my>365 && my < 365 + b)
			{
				i = 1; menut = 0;
			}
			if (menut&&mx > 90 && mx<90 + a &&my>295 && my < 295 + b)
			{
				i = 2; menut = 0;
			}
			if (menut&& mx > 90 && mx<90 + a &&my>225 && my < 225 + b)
			{
				i = 3; menut = 0;
			}
			if (menut&&mx > 90 && mx<90 + a &&my>155 && my < 155 + b)
			{
				i = 4; menut = 0;
			}
			if (menut&&mx > 1050 && mx<1050 + a &&my>60 && my < 60 + b)
			{
				i = 5;
				menut = 0;
			}
			if (menut&&mx>650 && mx<650 + a && my>60 && my<60 + b)
			{
				i = 6; menut = 0;
			}
			if (menut&& mx > 90 && mx<90 + a &&my>85 && my < 85 + b)
				exit(0);

		}

	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}
/*iPassiveMouseMove is called to detect and use
the mouse point without pressing any button */

void iPassiveMouse(int mx, int my)
{
	//place your code here



}

/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if (key == 'a')
	{
		if (state == 0)
			state = 1;
		else
			changeState();
		//do something with 'q'
	}

	int k;
	if (i == 6)
	{
		if (key == '\r')
		{
			k = 0;
			strcpy_s(str2, str);
			printf("%s\n", str2);
			for (k = 0; k < len; k++)
				str[i] = 0;
			len = 0;
		}
		else
		{
			str[len] = key;
			len++;
		}
	}

	if (key == 'x' || key == '\r')
	{
		//do something with 'x'
		i = 0;
		sortScore();
		poogyLife = 5; score = 0; xpos = 30; lvl = 1;
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
	if (key == GLUT_KEY_UP){}
	else if (key == GLUT_KEY_DOWN){}
	else if (key == GLUT_KEY_RIGHT)
	{
		xpos += 5;
		if (backxpos>-1200)
			backxpos -= 8;
		if (xpos>1100)
		{
			xpos = 0; backxpos = 0;
		}
		if (backxpos <= -2400)
			backxpos = back2xpos + 2400;
	}
	else if (key == GLUT_KEY_LEFT)
	{
		xpos -= 5;
		if (backxpos<0)
			backxpos += 8;
		if (xpos <= 0)
			xpos = 30;
	}
	if (key == GLUT_KEY_INSERT){ save(); }
	//place your codes for other keys her
}
void change()//changes the value of t which contorls the slideshow
{
	if (i == 5)t++;
	else
		t = 0;
}

int main()// loads resources for game into variables
{	//place your own initialization codes here.
	srand((unsigned)time(NULL));
	iSetTimer(4000, change);
	iSetTimer(05, EnemyScene);
	iSetTimer(15, FireballScene);
	iSetTimer(300, changeState);
	iInitialize(1200, 675, "demooo");
	image1 = iLoadImage("images//background.png");
	sm[0] = iLoadImage("slide1.png");
	sm[1] = iLoadImage("slide2.png");
	sm[2] = iLoadImage("slide3.png");
	sm[3] = iLoadImage("slide4.png");
	sm[4] = iLoadImage("slide5.png");
	poogy[0] = iLoadImage("images//poogy_final.png");
	poogy[1] = iLoadImage("images//ClubFinal.png");
	bck = iLoadImage("images//bg.png");
	nm = iLoadImage("images//nameInfo.png");
	a1 = iLoadImage("images//EnemyFinal.png");
	enm1 = Enemy(a1, 1000);
	enm2 = Enemy(a1, 2000);
	enm3 = Enemy(a1, 3000);
	enm4 = Enemy(a1, 4000);
	enm5 = Enemy(a1, 5000);
	b1 = iLoadImage("images//firaball_final.png");
	fb1 = Fireball(b1, 1000);
	fb2 = Fireball(b1, 2000);
	fb3 = Fireball(b1, 3000);
	fb4 = Fireball(b1, 4000);
	fb5 = Fireball(b1, 5000);
	heart[0] = iLoadImage("images//heart.png");
	heart[1] = iLoadImage("images//heart.png");
	heart[2] = iLoadImage("images//heart.png");
	heart[3] = iLoadImage("images//heart.png");
	heart[4] = iLoadImage("images//heart.png");
	dragon = iLoadImage("images//dragon.png");
	len = 0;
	len = 0;
	str[0] = 0;
	iStart();
	return 0;
}
