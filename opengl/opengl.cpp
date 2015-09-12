/* �������� �����. �������. ����������� ��� � ����������� ��� � OpenGL. 
��� ����� ����������� �� ��������� ������, ������� �� �������� � ������.*/
#include "stdafx.h"
#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <time.h>
#include <iostream>
// ������� ����
#define WinWid 1350
#define WinHei 650
#include "Town.h"
#include "People.h"
int count = 10; // ���������� �������
int countPicea = 0; // ���������� �����
std::vector<People> Peoples(1024);
std::vector<Picea> Piceas(1024);

void NewClass(int id, int idMarriage){ // �������� ������ ������ ("��������")
	if(abs(Peoples[id].Getx() - Peoples[idMarriage].Getx()) < 10 && count < 100 && Peoples[id].GetChildren() < 5 && Peoples[id].GetSex() != Peoples[idMarriage].GetSex()){
		People People1(count,Peoples[id].Getx(),Peoples[idMarriage].Gety());
		Peoples[count] = People1;
		printf("%d �������!\n",count);
		Peoples[id].SetChildren();
		Peoples[idMarriage].SetChildren();
		count++;
	}
}
void Merriage(int id, int sex){ // "�������" �����
	if(Peoples[id].GetIdMarriage() == -1){
		for(int i = 0; i < count; i++){
			if(i == id) continue;
			else { if(abs(Peoples[i].Getx() - Peoples[id].Getx()) < 10 && abs(Peoples[i].Gety() - Peoples[id].Gety()) < 10 && Peoples[i].GetIdMarriage() == -1 && sex != Peoples[i].GetSex()){
					Peoples[i].SetIdMarriage(id);
					Peoples[id].SetIdMarriage(i);
					printf("%d � %d ������ �����!\n",i,id);
				}
			}
		}
	}
}

int NewHome(Home myHome, int x, int y, int id){ // �������� ����
	int status = 1;
	for(int i = 0; i < count; i++){
		if(i == id) continue; 
		else if(abs(Peoples[id].Getx() - Peoples[i].GetHome().GetX())<60 && abs(Peoples[id].Gety() - Peoples[i].GetHome().GetY())<60){
			status = 0;
		}
	}
	return status;
}

void War(int id){ // �����
	if(Peoples[id].GetIdWar() == -1){ // ���� ��� �� ���� ������
		for(int i = 0; i < count; i++){
			if(i == id) continue;
			else { if(abs(Peoples[i].Getx() - Peoples[id].Getx()) < 10 && Peoples[i].GetIdWar() == -1){
					Peoples[i].SetIdWar(id);
					Peoples[id].SetIdWar(i);
					printf("%d � %d �������� �����!\n",i,id);
				}
			}
		}
	} else { // ���� ��� ���� ���� 
		if(abs(Peoples[Peoples[id].GetIdWar()].Getx() - Peoples[id].Getx()) < 10){
			if(Peoples[Peoples[id].GetIdWar()].GetHealth() > Peoples[id].GetHealth()){
				People item = Peoples[count-1];
				Peoples.pop_back();
				Peoples[id] = item;
				printf("%d ��� ����!\n",id);
				count--;
			} else {
				People item = Peoples[count-1];
				Peoples.pop_back();
				Peoples[Peoples[id].GetIdWar()] = item;
				printf("%d ��� ����!\n",Peoples[id].GetIdWar());
				count--;
			}
		}
	}
}

void DrawWorld(){ // ������� ���� ���������
	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix(); // ��������� �������
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
				printf("������ �������!\n");
			}
		}
	glPopMatrix(); // ������������ �������
	glutSwapBuffers();   // ����� �������
}

void Timer(int=0){
	//glutPostRedisplay(); // �������� ���� �����
	DrawWorld(); // ���� ��������� �����
	glutTimerFunc(10,Timer,0);
}

void Initialize(){
	glClearColor(0.0,0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION); // ��� �������
	glLoadIdentity();
	glOrtho(-WinWid/2,WinWid/2,-WinHei/2,WinHei/2,-200.0,200.0); // ������� ���������
	glMatrixMode(GL_MODELVIEW); // �� �������� �������
	for(int i = 0; i < count; i++){
		People People1(i,rand()%((int)WinWid)-WinWid/2,rand()%((int)WinHei)-WinHei/2);
		Peoples[i] = People1;
	}
}

int main(int argc, char** argv){
	setlocale(LC_ALL,"Russian");
	srand(time(NULL));
	// �������������
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // ��� ������
	glutInitWindowSize(WinWid,WinHei); // ������ ����
	glutInitWindowPosition(0,0); // ��������� ����
	glutCreateWindow("��������. ��������");
	//�����������
	glutDisplayFunc(DrawWorld); // ���������
	glutTimerFunc(10, Timer, 0); // �� ��������
	Initialize(); 
	glutMainLoop();
	return 0;
}