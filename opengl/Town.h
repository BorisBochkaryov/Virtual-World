class Atom{ 
      public:
             virtual void Draw() = 0;
};

class Town:public Atom{
protected:
	int status; // àêòèâíîñòü
	int x, y; // êîîğäèíàòû Îáúåêòîâ
public:
	Town(){}
	Town(int x, int y){
		this->x = x; 
		this->y = y;
	}
	int Status(){ return this->status; }
	int GetX(){ return this->x; }
	int GetY(){ return this->y; }
};

class Home:public Town{
protected:
	float color1; // öâåò äîìà
	float color2; // öâåò äîìà
	float color3; // öâåò äîìà
public:
	Home(){}
	void Init(int x, int y, float color1, float color2, float color3){
		this->x = x;
		this->y = y;
		this->status = 1;
		this->color1 = color1;
		this->color2 = color2;
		this->color3 = color3;
	}
	void Draw(){
		glBegin(GL_QUADS);
		glColor3f(this->color1,this->color2,this->color3);
		glVertex2f(this->x, this->y);
		glVertex2f(this->x + 25, this->y);
		glVertex2f(this->x+25, this->y+25);
		glVertex2f(this->x, this->y+25);
		glEnd();
		
		glBegin(GL_TRIANGLES);
        glVertex2f(this->x, this->y + 25);
        glVertex2f(this->x + 25/2, this->y + 25 + 25/2);
        glVertex2f(this->x + 25, this->y + 25);
		glEnd();
		
		glBegin(GL_LINES);// äîìèê
		glColor3f(1.0,1.0,1.0);
		
		glVertex2f(this->x+25/4,this->y+25-25/4); // îêîøêî
		glVertex2f(this->x+3*(25/4),this->y+25-25/4);
		glVertex2f(this->x+3*(25/4),this->y+25-25/4);
		glVertex2f(this->x+3*(25/4),this->y+25/4);
		glVertex2f(this->x+3*(25/4),this->y+25/4);
		glVertex2f(this->x+25/4,this->y+25/4);
		glVertex2f(this->x+25/4,this->y+25/4);
		glVertex2f(this->x+25/4,this->y+25-25/4);
		glVertex2f(this->x+2*25/4,this->y+25/4);
		glVertex2f(this->x+2*25/4,this->y+25-25/4);
		glVertex2f(this->x+25/4,this->y+2*(25/4));
		glVertex2f(this->x+2*25/4,this->y+2*(25/4));

		glEnd();
	}
};

class Picea:public Town{
public:
	Picea(){}
	Picea(int x, int y):Town(x,y){};
	void Draw(){
		glColor3f(0.0,1.0,0.0);
		glBegin(GL_TRIANGLES);
        glVertex2f(this->x-12, this->y);
        glVertex2f(this->x+12, this->y);
        glVertex2f(this->x, this->y+12);
		glEnd();
		glBegin(GL_TRIANGLES);
        glVertex2f(this->x-12/1.25, this->y+12);
        glVertex2f(this->x+12/1.25, this->y+12);
        glVertex2f(this->x, this->y+12+12/1.25);
		glEnd();
		glBegin(GL_TRIANGLES);
        glVertex2f(this->x-12/2, this->y+12/1.25);
        glVertex2f(this->x+12/2, this->y+12/1.25);
        glVertex2f(this->x, this->y+12+12/1.25+12/2);
		glEnd();
		glBegin(GL_QUADS);
		glColor3b(150,75,0);
		glVertex2f(this->x-12/4, this->y);
		glVertex2f(this->x+12/4, this->y);
		glVertex2f(this->x+12/4, this->y-12/4);
		glVertex2f(this->x-12/4, this->y-12/4);
		glEnd();
	}
};