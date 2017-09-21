#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <curses.h>
#include <stdlib.h>
using namespace std;

void gameInit();
void gameUpdate();
void levelRender();
void updatePlayerPosition(double, double);
void updateLevelPosition(int, int);

double playerX, playerY, playerVelX, playerVelY;
int levelX, levelY;
const int SCREENSIZEX = 70;
const int SCREENSIZEY = 20;
const int FPS = 20;
const int SLEEPTIME= (int) 1000/FPS;

char levelChars [SCREENSIZEY][SCREENSIZEX];
char screenChars [SCREENSIZEY][SCREENSIZEX];


ifstream levelFile;

int main() {
	playerX=playerY=6;
	bool running=true;
	char k;
	
	gameInit();
	
	while(running) {
		
		
		

		k=getch();


		if(k!=ERR){

			switch(k){
				case 'q': running=false; break;
				case 'w': playerVelY -= 0.03; break;
				case 'a': playerVelX -= 0.05; break;
				case 's': playerVelY += 0.03; break;
				case 'd': playerVelX += 0.05; break;
				case 'j': updateLevelPosition(levelX-1, levelY); break;
				case 'k': updateLevelPosition(levelX+1, levelY); break;
			}


		}
		gameUpdate();
		usleep(SLEEPTIME);
		
	}
	endwin();
}

void gameUpdate(){
	


	if(levelChars[(int) playerY + 1][(int) playerX] != '#')
		playerVelY +=  0.0019/((double) FPS);

	else if (playerVelY>0)
		playerVelY = 0;

	if(levelChars[(int) playerY-1][(int) playerX] == '#' && playerVelY < 0)
		playerVelY = 0;
	

		if(levelChars[(int) playerY][(int) playerX + 1] != '#'
			&& playerVelX>0
			&& levelChars[(int) playerY + 1][(int) playerX] == '#')
			playerVelX -=  0.0029/(double) FPS;
		else if (levelChars[(int) playerY][(int) playerX - 1] != '#' 
			&& playerVelX<0
			&& levelChars[(int) playerY + 1][(int) playerX] == '#'
			)
			playerVelX += 0.0029/FPS;
		
		else if(
				(levelChars[(int) playerY][(int) playerX + 1] == '#'
				|| 
				abs(playerVelX - 0.0029/FPS)<0.0029/FPS)
				&& playerVelX >0
				
				)
				playerVelX = 0;
		else if(
				levelChars[(int) playerY][(int) playerX - 1] == '#'
				&& playerVelX <0
				)
				playerVelX = 0;				


	updatePlayerPosition(playerX+playerVelX, playerY+playerVelY);
	
	
}	
	
	

void levelRender() {
	
	for(int i=0; i<SCREENSIZEY; i++){
		move(i, 0);
		for(int j=0; j<SCREENSIZEX; j++){
			
			addch(levelChars[i][j]);
		}

	}
	refresh();



}


void gameInit() {
	levelX = 0;	
	levelY = 0;

	initscr();
	cbreak();
	noecho();
	timeout(1);
	levelFile.open("level1.lvl");
	string fileString;
	if(levelFile.is_open()){
		int i=0;
		while(getline(levelFile, fileString)){
			if(i<SCREENSIZEY){
				for(int j=0; j<fileString.length() && j<SCREENSIZEX; j++){
			
					levelChars[i][j] = fileString.at(j);
				}
				i++;
			}
			
		}

				
	} else cout << "Error, no level file found";

	levelRender();	



}
void updatePlayerPosition(double x, double y){

	if (levelChars[(int) y][(int) x] != '#') {
		if((  (int) playerX != (int) x )
			|| ( (int) playerY != (int) y ) ) {

			mvaddch((int) playerY, (int) playerX, ' ');
	
			mvaddch((int) y,(int) x, 'X');
			move(SCREENSIZEY, SCREENSIZEX);
		}
		
		playerX = x;
		playerY = y;

	}	
}
void updateLevelPosition(int x, int y) {
	string fileString;
	if (x != levelX || y != levelY){
		levelX = x;
		levelY = y;
		for (int i=0; i<y; i++) getline(levelFile, fileString);
		for (int i = 0; i < SCREENSIZEY; i++){
			getline(levelFile, fileString);
				for(int j=0; j<SCREENSIZEX; j++){
			
					if (fileString.length() > j+x)
					   levelChars[i][j] = fileString.at(j+x);
				}
				
			
		}
		levelRender();
	}
	
	
}
