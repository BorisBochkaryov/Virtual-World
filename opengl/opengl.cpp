/* Бочкарев Борис. СибГУТИ. Виртуальный мир с применением ООП и OpenGL. 
Мир может развиваться по различным ветвям, которые не известны в начале.*/
#include "stdafx.h"
#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <time.h>
#include <iostream>
// размеры окна
#define WinWid 1350
#define WinHei 650
#include "Town.h"
#include "People.h"
int count = 10; // количество жителей
int countPicea = 0; // количество домов
std::vector<People> Peoples(1024);
std::vector<Picea> Piceas(1024);

void NewClass(int id, int idMarriage){ // создание нового класса ("рождение")
	if(abs(Peoples[id].Getx() - Peoples[idMarriage].Getx()) < 10 && count < 100 && Peoples[id].GetChildren() < 5 && Peoples[id].GetSex() != Peoples[idMarriage].GetSex()){
		People People1(count,Peoples[id].Getx(),Peoples[idMarriage].Gety());
		Peoples[count] = People1;
		printf("%d родился!\n",count);
		Peoples[id].SetChildren();
		Peoples[idMarriage].SetChildren();
		count++;
	}
}
void Merriage(int id, int sex){ // "свадьба" людей
	if(Peoples[id].GetIdMarriage() == -1){
		for(int i = 0; i < count; i++){
			if(i == id) continue;
			else { if(abs(Peoples[i].Getx() - Peoples[id].Getx()) < 10 && abs(Peoples[i].Gety() - Peoples[id].Gety()) < 10 && Peoples[i].GetIdMarriage() == -1 && sex != Peoples[i].GetSex()){
					Peoples[i].SetIdMarriage(id);
					Peoples[id].SetIdMarriage(i);
					printf("%d и %d теперь семья!\n",i,id);
				}
			}
		}
	}
}

int NewHome(Home myHome, int x, int y, int id){ // постройк дома
	int status = 1;
	for(int i = 0; i < count; i++){
		if(i == id) continue; 
		else if(abs(Peoples[id].Getx() - Peoples[i].GetHome().GetX())<60 && abs(Peoples[id].Gety() - Peoples[i].GetHome().GetY())<60){
			status = 0;
		}
	}
	return status;
}

void War(int id){ // война
	if(Peoples[id].GetIdWar() == -1){ // если ещё не было врагов
		for(int i = 0; i < count; i++){
			if(i == id) continue;
			else { if(abs(Peoples[i].Getx() - Peoples[id].Getx()) < 10 && Peoples[i].GetIdWar() == -1){
					Peoples[i].SetIdWar(id);
					Peoples[id].SetIdWar(i);
					printf("%d и %d объявили войну!\n",i,id);
				}
			}
		}
	} else { // если уже есть враг 
		if(abs(Peoples[Peoples[id].GetIdWar()].Getx() - Peoples[id].Getx()) < 10){
			if(Peoples[Peoples[id].GetIdWar()].GetHealth() > Peoples[id].GetHealth()){
				People item = Peoples[count-1];
				Peoples.pop_back();
				Peoples[id] = item;
				printf("%d был убит!\n",id);
				count--;
			} else {
				People item = Peoples[count-1];
				Peoples.pop_back();
				Peoples[Peoples[id].GetIdWar()] = item;
				printf("%d был убит!\n",Peoples[id].GetIdWar());
				count--;
			}
		}
	}
}

void DrawWorld(){ // главный цикл рисования
	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix(); // сохранить матрицу
		for(int i = 0; i < count; i++){
			Peoples[i].Live();
		}
		for(int i = 0; i < countPicea; i++){
			Piceas[i].Draw();
		}
		if(rand()%800 == 42){
			int status = 1;
			int rX = rand()%((int)WinWid)-WinWid/2;
			int rY = rand()%((int)WinHei)-WinHei/2;
			for(int i = 0; i < count; i++){
				if(abs(Peoples[i].GetHome().GetX() - rX) < 25 && abs(Peoples[i].GetHome().GetY() - rY) < 25 ){
					status = 0;
				}
			}
			if(status == 1){
				Picea Picea1(rX,rY);
				Piceas[countPicea] = Picea1;
				countPicea++;
				printf("Дерево выросло!\n");
			}
		}
	glPopMatrix(); // восстановить матрицу
	glutSwapBuffers();   // смена буферов
}

void Timer(int=0){
	//glutPostRedisplay(); // обновить весь экран
	DrawWorld(); // тоже обновляет экран
	glutTimerFunc(10,Timer,0);
}

void Initialize(){
	glClearColor(0.0,0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION); // тип матрицы
	glLoadIdentity();
	glOrtho(-WinWid/2,WinWid/2,-WinHei/2,WinHei/2,-200.0,200.0); // система координат
	glMatrixMode(GL_MODELVIEW); // не касается моделей
	for(int i = 0; i < count; i++){
		People People1(i,rand()%((int)WinWid)-WinWid/2,rand()%((int)WinHei)-WinHei/2);
		Peoples[i] = People1;
	}
}

int main(int argc, char** argv){
	setlocale(LC_ALL,"Russian");
	srand(time(NULL));
	// Инициализация
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // как рисуем
	glutInitWindowSize(WinWid,WinHei); // размер окна
	glutInitWindowPosition(0,0); // положение окна
	glutCreateWindow("Курсовая. Бочкарев");
	//Регистрация
	glutDisplayFunc(DrawWorld); // рисование
	glutTimerFunc(10, Timer, 0); // за анимацию
	Initialize(); 
	glutMainLoop();
	return 0;
}