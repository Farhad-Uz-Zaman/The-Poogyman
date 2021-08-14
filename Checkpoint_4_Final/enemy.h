
struct Enemy{
	int enImg, enemyxpos,mainx; 
	Enemy(){;}
	Enemy(int enImg,int enemyxpos){ 
	this->enImg=enImg; 
	this->enemyxpos=enemyxpos;
	mainx=enemyxpos;}
	int CollisionEnemy(int x)
	{ 
	if (x == enemyxpos)
		return 0;
   }
	int CollisionClub(int x,int state){
if (state==1 && enemyxpos<=x+186 && enemyxpos>=x+150){
	   return 0;} 
	else return 1; 
	}
};

typedef struct Enemy Enemy;

