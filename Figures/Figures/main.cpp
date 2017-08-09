#include <iostream>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>

#include "Trigonometry.h"
#include "Point.h"

using namespace std;

#define pause { Sleep(2000);InvalidateRect(hwnd, 0, TRUE);UpdateWindow(hwnd);}



HWND hwnd = GetConsoleWindow();
HDC hdc = GetDC(hwnd);

class Figure
{protected:
	Point * points_;
	int count_;
	int Ix;
	int Iy;
	

public:
	Figure()
	{ 
		count_ = 0;
		points_ = nullptr;
	}
	Figure(int p_count, int _Ix, int _Iy)
	{
		if (p_count < 2) p_count = 2;
		count_ = p_count;
		Ix=_Ix;
		Iy=_Iy;
		points_ = new Point [count_] ;
		if (! points_) exit(0);
		points_[0].x_ = Ix;
		points_[0].y_=Iy;
		for (int i = 1; i<count_; i++){
			points_[i].SetPoint(rand() % 600, rand() % 400);
		}
	}


	virtual double p()
	{ double P=0;
		for (int i = 1; i < count_; i++)
		{ double px=(points_[i].x_-points_[i-1].x_);
		double py=(points_[i].y_- points_[i-1].y_);
		double p=sqrt((px*px)+(py*py));
		P+=p;
		}
	   double px0=(points_[count_-1].x_-points_[0].x_);
	   double py0=(points_[count_-1].y_-points_[0].y_);
	   double p0=sqrt ((px0*px0)+(py0*py0));
	   P+=p0;

		return P;
	}

	virtual double s ()
	{cout<<"S is not found\n";
	return 0;}

	
	virtual void Show()
	{   system ("cls");
		ReleaseDC(hwnd, hdc);
		hdc = GetDC(hwnd);
		HPEN pen = CreatePen(rand() % 5, 1, RGB(100, 100, 100));
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));

		SelectObject(hdc, brush);
		
		SelectObject(hdc, pen);
		POINT p;
		MoveToEx(hdc, points_[0].x_, points_[0].y_, &p);
		for (int i = 1; i<count_; i++){
			LineTo(hdc, points_[i].x_, points_[i].y_);
			Sleep(1500 / count_);
		}
		LineTo(hdc, points_[0].x_, points_[0].y_);
		DeleteObject(pen);
		DeleteObject(brush);

	}

	


	virtual~Figure()
	{
		if (points_) delete[] points_;
		
	}

};


class Polygon:public Figure
{

public:
	Polygon():Figure()
	{
		cout<<"polygon def constr\n";
	}



	Polygon(int count, int Ix, int Iy):Figure(count, Ix, Iy)
	{
		if (count<3) count=3;
	}

	
	


	virtual~Polygon()
	{
		/*if (obj) delete[] obj;*/
		
	}

};


class Quadrangle : public Polygon
{   
  
public:
	Quadrangle ():Polygon()
		{ 
			count_=4;
	cout<<"Quadrangle def constr\n";
	}


	Quadrangle(int count, int Ix, int Iy):Polygon(4, Ix, Iy)
	{
		if (count != 4) count = 4;
		
		}

	


	~Quadrangle()
	{
		/*if (obj) delete[] obj;*/
		

	}

};

class Parallelogramm:public Quadrangle
{protected:
 int height;
 int width;
 double angle;
public:
	Parallelogramm ():Quadrangle()
	{}

	Parallelogramm (int count, int Ix, int Iy, int _height, int _width, double _angle):Quadrangle(count, Ix, Iy)
	{
		
		this->count_ = 4;
		this->height = _height;
		this->width = _width;
		this->angle = _angle;
		points_ = new Point[count];
		if (!points_) exit(0);
		int h=height * Trigonometry :: MySinus (angle);
		int w=height * Trigonometry :: MyCosinus (angle);
		

		points_[0].SetPoint (Ix,Iy);
		points_[1].SetPoint (Ix+width,Iy);
			points_[2].SetPoint (Ix+width-w, Iy+h);
			points_[3].SetPoint (Ix-w,Iy+h);


     }

	double s ()
	{  /* double a=(obj[1].X-obj[0].X);
	double h=(obj[3].Y-obj[0].Y);
	double S=a*h;*/
		double S=height * width * Trigonometry :: MySinus(angle);
	return S;
	}

	~Parallelogramm()
	{}
};

class _Rectangle:public Parallelogramm
{
public :
	_Rectangle():Parallelogramm()
	{}


	 _Rectangle(int count, int Ix, int Iy, int height, int width, double angle=90) : Parallelogramm(count, Ix, Iy, height, width, 90)
	{
		
		this->count_ = 4;
		this->angle=90;


	}

	double s ()
	{return Parallelogramm::s();}

	~_Rectangle()
	{
	}
};


class Square: public _Rectangle
{  public:
	Square() : _Rectangle()
	{}

	Square(int count, int Ix, int Iy, int height, int width, double angle=90):_Rectangle(count, Ix, Iy, height, height)
	{
		
		this->count_ = 4;
		this->angle=90;
		this->width=height;
		
	}

	double s ()
	{return Parallelogramm::s();}


	~Square()
	{
	}

};


class Trapecia:public Quadrangle
{ protected:
int base_1;
int base_2;
int height;
 double angle;

public:
	Trapecia():Quadrangle()
	{cout<<"trapecia def constr\n";}


	Trapecia(int count, int Ix, int Iy, int _base_1, int _base_2, int _height, double _angle):Quadrangle(count, Ix, Iy)
	{ 
		
		this->count_ = 4;
		this->base_1=_base_1;
		this->base_2=_base_2;
		this->height=_height;
		this->angle=_angle;
		int w=height * Trigonometry :: MyCosinus(angle);
		points_ = new Point[count];
		if (!points_) exit(0);
		points_[0].SetPoint (Ix,Iy);
		points_[1].SetPoint (Ix+w,Iy-height);
			points_[2].SetPoint (Ix+w+base_1, Iy-height);
			points_[3].SetPoint (Ix+base_2,Iy);


	}

	double s ()
	{
		/*double S=((obj[1].X-obj[0].X)+(obj[2].X-obj[3].X)/2)*(obj[3].Y-obj[0].Y);*/
		double S=(base_1+base_2)/2*height;
	
	 return S;
	}

	

	~Trapecia()
	{
	}
};

class Deltoid :public Quadrangle
{ int width;
int height;
double angle;
 

public:
	Deltoid ():Quadrangle()
	{cout<<"deltoid def constr\n";}

	Deltoid(int count, int Ix, int Iy, int _height, int _width, double _angle):Quadrangle(count, Ix, Iy)
	{
		
		this->count_ = 4;
		this->height=_height;
		this->width=_width;
		this->angle=_angle;
		int h=width/2*(Trigonometry :: MyCosinus(angle/2) / Trigonometry :: MySinus(angle/2));
	
		points_ = new Point[count];
		if (!points_) exit(0);
		points_[0].SetPoint (Ix,Iy);
		points_[1].SetPoint (Ix+width/2,Iy+h);
			points_[2].SetPoint (Ix, Iy+height);
			points_[3].SetPoint (Ix-width/2,Iy+h);


	}

	double  s ()
	{
		double S=height*width/2;
		return S;
	}

	~Deltoid()
	{
	}
};


class romb:public Parallelogramm
{  public:
	romb():Parallelogramm()
	{cout<<"romb def constr\n";}

	romb(int count,int Ix, int Iy, int height, int width, double angle) : Parallelogramm(count, Ix, Iy, height, height, angle)
	{
		
		this->count_ = 4;
		
		this->width=this->height;
		
	}

	double s ()
	{return Parallelogramm::s();
	}

	~romb()
	{ 
	}
};

class triangle :public Polygon
{protected:
int height;
int width;
double angle;

public:
   triangle():Polygon()
   {this->count_ = 3;
   cout<<"triangle def constr\n";
   }

   triangle(int count, int Ix, int Iy, int _height, int _width, double _angle):Polygon(count, Ix, Iy)
	{  
		this->count_ = 3;
		this->height=_height;
		this->width=_width;
		this->angle=_angle;
		int h=height*Trigonometry:: MySinus(angle);
		int w=height*Trigonometry:: MyCosinus(angle);
		points_ = new Point[count];
		if (!points_) exit(0);

		points_[0].SetPoint (Ix,Iy);
		points_[1].SetPoint (Ix+w,Iy-h);
			points_[2].SetPoint (Ix+width, Iy);

	}

   ~triangle()
   {}

   double s()
   {
	   double ax=(points_[0].x_ - points_[1].x_);
	   double ay=(points_[0].y_ -points_[1].y_);
	   double bx=(points_[2].x_ -points_[1].x_);
	   double by=(points_[2].y_ - points_[1].y_);
	   double cx=(points_[2].x_ -points_[0].x_);
	   double cy=(points_[2].y_ - points_[0].y_);
	   double a=sqrt ((ax*ax)+(ay*ay));
	   double b=sqrt ((bx*bx)+(by*by));
	   double c=sqrt ((cx*cx)+(cy*cy));
	   double pp=(a+b+c)/2;
	   double S=sqrt(pp*(pp-a)*(pp- b )*(pp-c));
	   return S;

   }

};


class TriangleEquilateral : public  triangle
{

public:
	TriangleEquilateral () : triangle()
	{cout<<"ravnostor_tr def constr\n";}

	TriangleEquilateral(int count, int Ix, int Iy, int height, int width, double angle=60) : triangle (count,Ix, Iy, height, height, 60)
		
	{	this->count_ = 3;
		this->width=this->height;
		this->angle=60;
		
		
			
	}

	~TriangleEquilateral()
	{
	}

	double s()
	{return triangle::s();}
};

class TriangleAcuteAngled : public  triangle
{ 

public:
	TriangleAcuteAngled():triangle()
	{cout<<"ravnober_ostr_tr def constr\n";
	}

TriangleAcuteAngled(int count, int Ix, int Iy, int height, int width, double angle):triangle (count,Ix, Iy, height, width, angle)
	{
		if (this->angle>90) cout<<"triangle is not acute-angled\n";
		this->count_ = 3;
		
	}


   ~TriangleAcuteAngled()
   {
   }

   double s()
	{
		return triangle::s();
   }

};


class TriangleObtuseAngled : public  triangle
{ 
	

public:
	TriangleObtuseAngled():triangle()
	{};

	TriangleObtuseAngled(int count, int Ix, int Iy, int height, int width, double angle):triangle (count,Ix, Iy, height, width, angle)
	{
		if (this->angle<90) cout<<"triangle is not obtuse-angled\n";
		this->count_ = 3;
		
		
		


	}

	~TriangleObtuseAngled()
   {}


	double s()
	{return triangle::s();}
};


class pryamoug_tr:public  triangle
{


public:
	pryamoug_tr():triangle()
	{}

	pryamoug_tr(int count, int Ix, int Iy, int height, int width, double angle=90):triangle (count,Ix, Iy, height, width, 90)
	{
		
		this->count_ = 3;
		this->angle=90;
		
		
		
		
			
	}

	double s()
	{return triangle::s();}

	~pryamoug_tr()
	{}
};


class pryamoug_ravnostor_tr:public  triangle
{



public:
	pryamoug_ravnostor_tr():triangle()
	{}

	pryamoug_ravnostor_tr(int count, int Ix, int Iy, int height, int width, double angle):triangle (count,Ix, Iy, height, height, 90)
	{
		
		this->count_ = 3;
		
		this->width=this->height;
		this->angle=90;
		
		
	}


	double s()
	{return triangle::s();}
};



class _ellipse:public Figure
{  protected:
  int height;
  int width;
public:
	_ellipse():Figure()
     {}


_ellipse(int count, int Ix, int Iy, int _height, int _width):Figure(count, Ix, Iy)
{ this->height=_height;
this->width=_width;
		
		this->count_=4;
		points_ = new Point[count];
		if (!points_) exit(0);

		
		points_[0].SetPoint (Ix,Iy);
		points_[1].SetPoint (Ix+width,Iy+height);
			points_[2].SetPoint (Ix, Iy);
			points_[3].SetPoint(Ix, Iy);

	}


    void Show()
     {system ("cls");
	ReleaseDC(hwnd, hdc);
		hdc = GetDC(hwnd);
		HPEN pen = CreatePen(rand() % 5, 1, RGB(100, 100, 100));
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));

		SelectObject(hdc, brush);
		
		SelectObject(hdc, pen);
		POINT p;
		
		Arc (hdc, points_[0].x_, points_[0].y_, points_[1].x_, points_[1].y_, points_[2].x_, points_[2].y_, points_[3].x_, points_[3].y_);
		DeleteObject(pen);
		DeleteObject(brush);
	}
	
	double  p ()
	{double a=(points_[1].x_ - points_[0].x_)/2;
	double b=(points_[1].y_ - points_[0].y_)/2;

	double P=3.14*(a+b);
	return P;
	}

  double  s ()
  {double a=(points_[1].x_ - points_[0].x_)/2;
	double b=(points_[1].y_-points_[0].y_)/2;

	double S=PI*a*b;
	return S;

  }


	~_ellipse()
	{
	
	}

};


class circle:public _ellipse
{
public:
	circle():_ellipse()
	{}

	circle(int count, int Ix, int Iy, int height, int width):_ellipse(count, Ix, Iy,height,height)
	{   
		this->width=this->height;
		this->count_= 4;
		

	}


	void Show ()
	{
	  
		_ellipse :: Show();

		}
	
	double p()
	{return _ellipse :: p();}

	double s ()
	{return _ellipse::s();}

	~circle()
	{}


};


class ellips_in_rect:public _ellipse, public _Rectangle
{ public:
  ellips_in_rect():_Rectangle()
  {}

  ellips_in_rect(int count, int Ix, int Iy, int height, int width, double angle=0):_Rectangle(count, Ix,  Iy,  height, width,  0),_ellipse( count, Ix,  Iy,height, width  )
  {
	  _Rectangle::count_=4;
	  _ellipse::count_=4;
		  
  }

  void Show()
  {
   _Rectangle::Show();
   _ellipse::Show();
  }

  double p ()
  {   double P=_Rectangle::p()+_ellipse::p();
  return P;

  }

  double s ()
  {double S=_Rectangle::s()-_ellipse::s();
  return S;
  }


  ~ellips_in_rect()
  {}
};

class tochka:public Figure
{  public:
	tochka():Figure()
       {this->count_=1;
       }
	
	
		tochka(int count,int Ix, int Iy): Figure (1, Ix, Iy)
		{  this->count_=1;
			points_ = new Point;
		if (!points_) exit(0);

		
			points_->SetPoint(Ix, Iy);
		}

		void Show ()
		{   system("cls");
			ReleaseDC(hwnd, hdc);
		hdc = GetDC(hwnd);
		
	COLORREF COLOR= RGB(255,255,255);
		SetPixel(hdc, points_->x_, points_->y_, COLOR);
		
		}
		
		double p ()
		{return 0;}

		double s ()
		{return 0;}
};

class pryamaya:public Figure
{protected:
 int X2;
 int Y2;

public:
	pryamaya():Figure()
	{ count_ = 2;
	}

	pryamaya(int count, int Ix, int Iy, int _X2, int _Y2):Figure(2, Ix, Iy)
	{this->X2 = _X2;
	this->Y2 = _Y2;
	this->count_ = 2;
	points_ = new Point[count];
		if (!points_) exit(0);

		int X_start = 0;
		int Y_start = (Y2-Iy) * (X_start-Ix)/(X2-Ix)+Iy;
		int X_fin = 1000;
		int Y_fin = (Y2-Iy) * (X_fin-Ix)/(X2-Ix)+Iy;
		points_[0].SetPoint(X_start,Y_start);
		points_[count-1].SetPoint(X_fin,Y_fin);
		
	}

	~pryamaya()
	{
	
	}
	
};
void main()
{
	system("mode con cols=80 lines=50");
	srand(time(0));
		COORD c = { 0, 0 };
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(h, c);
		/*cout<<"figura\n";
		Figura f(6,150,150);
		f.Show();
		pause;
		 
		 cout<<"qudrangle\n";
		 Sleep(1000);
		Quadrangle Q(4,150,150);
		Q.Show();
		pause;*/

		 cout<<"parallelogramm\n";
		 Sleep(1000);
		Parallelogramm a(4,200,200,200,100,40);
		a.Show();
		cout<<"parallelogramm\n";
		cout<<"S="<<a.s()<<endl;
		cout<<"P="<<a.p()<<endl;
		pause;

	_Rectangle r(4,100,100,200,100);
	r.Show();
	cout<<"Rectangle\n";
	cout<<"S="<<r.s()<<endl;
	cout<<"P="<<r.p()<<endl;
	pause;

		Square s(4,150,150,200,100);
		s.Show();
		cout<<"square\n";
		cout<<"S="<<s.s()<<endl;
		cout<<"P="<<s.p()<<endl;

		pause;

		Trapecia t(4,150,150,200,350,40, 30);
		t.Show();
		cout<<"trapecia\n";
		cout<<"S="<<t.s()<<endl;
		cout<<"P="<<t.p()<<endl;
		pause;

		Deltoid d(4,200,200,300,200,40);
		d.Show();
		cout<<"deltoid\n";
		cout<<"S="<<d.s()<<endl;
		cout<<"P="<<d.p()<<endl;
		pause;

		romb ro(4,150,150,200,200,60);
		ro.Show();

		cout<<"romb\n";
		cout<<"S="<<ro.s()<<endl;
		cout<<"P="<<ro.p()<<endl;
		pause;

		triangle tr(3,250,250, 200, 400,40);
		tr.Show();
		cout<<"triangle\n";
		cout<<"S="<<tr.s()<<endl;
		cout<<"P="<<tr.p()<<endl;

		

	pause;
		
		 TriangleEquilateral rstr(3,200,200,200,200,60);
		rstr.Show();
		cout<<"Equilateral triangle\n";
		cout<<"S="<<rstr.s()<<endl;
		cout<<"P="<<rstr.p()<<endl;
		
		 
		 pause;

		TriangleAcuteAngled rbostr(4,150,150,200,200,30);
		rbostr.Show();
		cout<<"ravnobedr. ostroug. treug\n";
		cout<<"S="<<rbostr.s()<<endl;
		cout<<"P="<<rbostr.p()<<endl;
		 
		pause;
		TriangleObtuseAngled rbtptr(3, 200,200,150,150,100);
		rbtptr.Show();
		cout<<"ravnobedr tupoug. tr\n";
		cout<<"S="<<rbtptr.s()<<endl;
		cout<<"P="<<rbtptr.p()<<endl;
		pause;

		pryamoug_tr pmgtr(3,200,200,100,220,90);
		pmgtr.Show();
		cout<<"pryamoug.treug\n";
		cout<<"S="<<pmgtr.s()<<endl;
		cout<<"P="<<pmgtr.p()<<endl;
		pause;

		pryamoug_ravnostor_tr pmgrstr(3,200,200,200,200,90);
		pmgrstr.Show();
		cout<<"pryamoug_ravnostor_tr\n";
		cout<<"S="<<pmgrstr.s()<<endl;
		cout<<"P="<<pmgrstr.p()<<endl;
		pause;


		_ellipse el(4,150,150,200,400);
		el.Show();
		cout<<"ellips\n";
		cout<<"S="<<el.s()<<endl;
		cout<<"P="<<el.p()<<endl;
		pause;


		circle cir(4,150,150,200,200);
		cir.Show();
		cout<<"circle\n";
		cout<<"S="<<cir.s()<<endl;
		cout<<"P="<<cir.p()<<endl;
		pause;

		ellips_in_rect eir(4,150,150,200,300);
		eir.Show();
		cout<<"ellips in rectangle\n";
		cout<<"S="<<eir.s()<<endl;
		cout<<"P="<<eir.p()<<endl;
	   pause;


		 ellips_in_rect ciq(4,150,150,200,200);
		ciq.Show();
		cout<<"circle in square\n";
		cout<<"S="<<ciq.s()<<endl;
		cout<<"P="<<ciq.p()<<endl;
		pause;

		tochka T(1,100, 150);
		T.Show();
		cout<<"tochka\n";
		pause;
		
  pryamaya AB (2, 150,150,200,300);
  AB.Show();
  cout<<"praymaya\n";
  pause;




}

















