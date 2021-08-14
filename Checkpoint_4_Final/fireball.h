struct Fireball{
int fbImg, fbxpos,mainx;


Fireball(){;}

Fireball(int fbImg,int fbxpos){
	this->fbImg=fbImg;
	this->fbxpos=fbxpos;
	mainx = fbxpos;
}

int CollisionFireball(int x)
{
	if (x == fbxpos)
		return 0;
}
int CollisionClub(int x, int state){
	if (state == 1 && fbxpos <= x + 186 && fbxpos >= x + 150){
		return 0;
	}
	else return 1;
}



};

typedef struct Fireball Fireball;