void NewClass(int id, int idMarriage);
void Merriage(int id, int sex);
void War(int id);
int NewHome(Home myHome, int x, int y, int id);

class People:public Atom{
	private:
		int id; // идентификатор жителя
		int statusGo; // в какую сторону движется
		int sex; // 0 - мужчина, 1 - женщина
		int x, y; // координаты людей
		int idMarriage; // "семья"
		int idWar; // "враг"
		int health; // здоровье
		int children; // количество детей
		int speed; // скорость
		Home myHome; // дом персонажа
	public: 
		int GetSex(){ return sex; }
		int Getx(){ return x; }
		int Gety(){ return y; }
		int GetIdMarriage(){ return idMarriage; }
		int GetIdWar(){ return idWar; }
		int GetHealth(){ return health; }
		int GetChildren(){ return children; }
		void SetIdMarriage(int id){ idMarriage = id; }
		void SetIdWar(int id){ idWar = id; }
		void SetChildren(){ children++; }
		Home GetHome(){ return myHome; }

		People(){}

		People(int idM, int X = 0, int Y = 0){ // конструктор с заданием начальных параметров
			speed = rand()%3+1;
			health = rand()%100+50;
			children = 0;
			id = idM;
			idWar = idMarriage = -1;
			if(idM == 0) sex = 0;
			else if(idM == 1) sex = 1;
			else sex = rand()%2;
			x = X;
			y = Y;
			statusGo = 0;
		}
		void Live(){ // главный цикл жизни
			Draw();
			Dvig();
			if(rand()%10 == 3){
				Merriage(id,sex);
			}
			if(rand()%50 == 5 && idMarriage != -1){
				NewClass(id,idMarriage);
			}
			if(rand()%500 == 8){
				War(id);
			}
			if(rand()%300 == 12 && this->myHome.Status() != 1){
				if(NewHome(this->myHome, this->x, this->y, this->id) == 1){
					this->myHome.Init(this->x,this->y,(float)rand()/10000,(float)rand()/100000,(float)rand()/100000);
					printf("%d построил дом!\n",this->id);
				}
			}
		}
		void Draw(){ // отрисовка персонажей
			int tempX = x, tempY = y;
			if(sex == 1){
				glBegin(GL_TRIANGLES);
				glColor3f(1.0,1.0,1.0);
				glVertex2f(tempX, tempY + 25/2);
				glColor3f(0.0,0.0,1.0);
				glVertex2f(tempX + 25/2, tempY-25/2);
				glColor3f(1.0,0.0,1.0);
				glVertex2f(tempX - 25/2, tempY-25/2);
				glEnd();
			} else if(sex == 0){
				glBegin(GL_TRIANGLES);
				glColor3f(0.0,0.0,1.0);
				glVertex2f(tempX-25/2, tempY+25/2);
				glColor3f(1.0,0.0,0.0);
				glVertex2f(tempX+25/2, tempY+25/2);
				glColor3f(1.0,1.0,0.0);
				glVertex2f(tempX, tempY-25/2);
				glEnd();
			}
			if(this->myHome.Status() == 1){
				this->myHome.Draw();
			}
		}
		void Dvig(){ // движение персонажа
			int go = rand()%100;
			switch(go){
			case 12: statusGo = 0; break;
			case 8: statusGo = 1; break;
			case 10: statusGo = 2; break;
			case 3: statusGo = 3; break;
			}
			switch(statusGo){
			case 0: if(x+25/2<WinWid/2) x+=speed; break;
			case 1: if(x-25/2>-WinWid/2) x-=speed; break;
			case 2: if(y+25/2<WinHei/2) y+=speed; break;
			case 3: if(y-25/2>-WinHei/2) y-=speed; break;
			}
		}
};