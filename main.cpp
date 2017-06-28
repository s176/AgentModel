#include <math.h>
#include <GLCtrl/GLCtrl.h>
#include <CtrlLib/CtrlLib.h>

using namespace Upp;

FileOut out1("resultvalue.txt");
FileOut out2("resultsteps.txt");

struct OpenGLExample : public GLCtrl 
{
	//Властивості частки: координати, маса
	struct Particle
	{
		double x;
		double y;
		int m;
		double rent;
	};
	
	//Кількість часток
	static const int N = 6000;
	
	// Розмір карти
	static const int MapSize = 500000;

	static const int SearchNumber = 3;
	
	static const int local = 10000;
	
	//Колір
	float r;
	float g;
	float b;
	
	// Параметры системы
		
	float Value0;	
	float Value1;	
	float Value2;	
	float Value3;	
		
	int Step0Count;
	int Step1Count;
	int Step2Count;
	int Step3Count;
	
	static const int x00 = 15000;
	static const int x01 = -8;
	static const int x02 = -3;
	static const int x03 = 1000;
	
	static const int x10 = -800;
	static const int x11 = 2465;
	static const int x12 = -305;
	static const int x13 = 1091;
	
	static const int x20 = -540;
	static const int x21 = 10950;
	static const int x22 = 2185;
	static const int x23 = -620;
	
	static const int x30 = -2850;
	static const int x31 = -1510;
	static const int x32 = -1504;
	static const int x33 = 9000;
	
	float d;
	
	Particle particles[N]; 
		
virtual void GLPaint() 
{
	Size sz = GetSize();
	glViewport(0, 0, (GLsizei)sz.cx, (GLsizei)sz.cy);
	glOrtho(0, 16500, 16500, 0, -1, 1); //MapSize*0.034, MapSize*0.034
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
					
		for (int i = 0; i < N; ++i)
		{	
			
				if (particles[i].m == 0)
				{
					r = 1;
					g = 0.3;
					b = 0.3;
				};
				if (particles[i].m == 1)
				{
					r = 0.3;
					g = 1;
					b = 0.2;
				};
				if (particles[i].m == 2)
				{
					r = 1;
					g = 1;
					b = 0.3;
				};
				if (particles[i].m == 3)
				{
					r = 0.5;
					g = 0.8;
					b = 1;
				};				
			
				glBegin(GL_QUADS);		
				glColor3f(r,g,b);
				glVertex2f(particles[i].x - 30, particles[i].y - 30); 
				glVertex2f(particles[i].x + 30, particles[i].y - 30); 
				glVertex2f(particles[i].x + 30, particles[i].y + 30);
				glVertex2f(particles[i].x - 30, particles[i].y + 30);
				glEnd();
		}
					
		Move();
		out1.PutLine(Format("%d,%d,%d,%d", Value0, Value1, Value2, Value3)); // стоимость системы после каждого шага
		out2.PutLine(Format("%i,%i,%i,%i", Step0Count, Step1Count, Step2Count, Step3Count)); // стоимость системы после каждого шага
		
		Value0 = 0;
		Value1 = 0;
		Value2 = 0;
		Value3 = 0;
		
		Step0Count = 0;
		Step1Count = 0;
		Step2Count = 0;
		Step3Count = 0;
}

// Ініціалізація початкової карти
void InitGL()							
{
	glClearColor(0, 0, 0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
		
	for (int i = 0; i < N; i++)
	{
		particles[i].x = rand() % MapSize/2;
		particles[i].y = rand() % MapSize/2;
		particles[i].m = rand() % 4;
		particles[i].rent = 0;
	};
}

void Move() 
{ 
	float effect;
	float effectfact;
	effect = 0;
	effectfact = 0;
	
	Particle p0;
			
	// Для кожної частки робимо визначення нового місця
	for (int i = 0; i < N; ++i)
	{
		Particle &ptemp = particles[i];
		Particle ifptmoved;
		ifptmoved.x = ptemp.x;
		ifptmoved.y = ptemp.y;
		effect = 0;
		effectfact = 0;
		
		// Определяем текущий доход частицы
			if (ptemp.m == 0)
			{
				for (int j = 0; j < N; ++j)
				{
					if (j == i)
						continue;
					const Particle &p = particles[j];	
					d = (p0.x - p.x)*(p0.x - p.x) + (p0.y - p.y)*(p0.y - p.y);
					if (d < local)
						continue;
					if (p.m == 0)
					{
						effectfact += x00 / d;
					}
					if (p.m == 1)
					{
						effectfact += x01 / d;
					}
					if (p.m == 2)
					{
						effectfact += x02 / d ;
					}
					if (p.m == 3)
					{
						effectfact += x03 / d;
					}
				}
			}
		
			if (ptemp.m == 1)
			{
				for (int j = 0; j < N; ++j)
				{
					if (j == i)
						continue;
					const Particle &p = particles[j];	
					d = (p0.x - p.x)*(p0.x - p.x) + (p0.y - p.y)*(p0.y - p.y);
					if (d  < local)
						continue;
					if (p.m == 0)
					{
						effectfact += x10 / d;
					}
					if (p.m == 1)
					{
						effectfact += x11 / d;
					}
					if (p.m == 2)
					{
						effectfact += x12 / d;
					}
					if (p.m == 3)
					{
						effectfact += x13 / d;
					}
				}
			}
		
			if (ptemp.m == 2)
			{
				for (int j = 0; j < N; ++j)
				{
					if (j == i)
						continue;
					const Particle &p = particles[j];	
					d = (p0.x - p.x)*(p0.x - p.x) + (p0.y - p.y)*(p0.y - p.y);
					if (d  < local)
						continue;
					if (p.m == 0)
					{
						effectfact += x20 / d;
					}
					if (p.m == 1)
					{
						effectfact += x21 / d;
					}
					if (p.m == 2)
					{
						effectfact += x22 / d;
					}
					if (p.m == 3)
					{
						effectfact += x23 / d;
					}
				}
			}
		
			if (ptemp.m == 3)
			{
				for (int j = 0; j < N; ++j)
				{
					if (j == i)
						continue;
					const Particle &p = particles[j];	
					d = (p0.x - p.x)*(p0.x - p.x) + (p0.y - p.y)*(p0.y - p.y);
					if (d  < local)
						continue;
					if (p.m == 0)
					{
						effectfact += x30 / d;
					}
					if (p.m == 1)
					{
						effectfact += x31 / d;
					}
					if (p.m == 2)
					{
						effectfact += x32 / d;
					}
					if (p.m == 3)
					{
						effectfact += x33 / d;
					}
				}
			}
			ptemp.rent = effectfact;
		
		// ищем вариант
		for (int u = 0; u < SearchNumber; u++)
		{
			p0.x = rand() % MapSize/2;
			p0.y = rand() % MapSize/2;
						
			effect = 0;	
			if (ptemp.m == 0)
			{
				for (int j = 0; j < N; ++j)
				{
					if (j == i)
						continue;
					const Particle &p = particles[j];	
					d = (p0.x - p.x)*(p0.x - p.x) + (p0.y - p.y)*(p0.y - p.y);
					if (d < local)
						continue;
					if (p.m == 0)
					{
						effect += x00 / d;
					}
					if (p.m == 1)
					{
						effect += x01 / d;
					}
					if (p.m == 2)
					{
						effect += x02 / d ;
					}
					if (p.m == 3)
					{
						effect += x03 / d;
					}
				}
			}
		
			if (ptemp.m == 1)
			{
				for (int j = 0; j < N; ++j)
				{
					if (j == i)
						continue;
					const Particle &p = particles[j];	
					d = (p0.x - p.x)*(p0.x - p.x) + (p0.y - p.y)*(p0.y - p.y);
					if (d  < local)
						continue;
					if (p.m == 0)
					{
						effect += x10 / d;
					}
					if (p.m == 1)
					{
						effect += x11 / d;
					}
					if (p.m == 2)
					{
						effect += x12 / d;
					}
					if (p.m == 3)
					{
						effect += x13 / d;
					}
				}
			}
		
			if (ptemp.m == 2)
			{
				for (int j = 0; j < N; ++j)
				{
					if (j == i)
						continue;
					const Particle &p = particles[j];	
					d = (p0.x - p.x)*(p0.x - p.x) + (p0.y - p.y)*(p0.y - p.y);
					if (d  < local)
						continue;
					if (p.m == 0)
					{
						effect += x20 / d;
					}
					if (p.m == 1)
					{
						effect += x21 / d;
					}
					if (p.m == 2)
					{
						effect += x22 / d;
					}
					if (p.m == 3)
					{
						effect += x23 / d;
					}
				}
			}
		
			if (ptemp.m == 3)
			{
				for (int j = 0; j < N; ++j)
				{
					if (j == i)
						continue;
					const Particle &p = particles[j];	
					d = (p0.x - p.x)*(p0.x - p.x) + (p0.y - p.y)*(p0.y - p.y);
					if (d  < local)
						continue;
					if (p.m == 0)
					{
						effect += x30 / d;
					}
					if (p.m == 1)
					{
						effect += x31 / d;
					}
					if (p.m == 2)
					{
						effect += x32 / d;
					}
					if (p.m == 3)
					{
						effect += x33 / d;
					}
				}
			}
			if (effect > effectfact * 2 + 1)
			{
				d = (p0.x - ptemp.x)*(p0.x - ptemp.x) + (p0.y - ptemp.y)*(p0.y - ptemp.y);
				if (d < 70000000)
				{
					ptemp.rent = effect;
					ptemp.x = p0.x;
					ptemp.y = p0.y;
				}
			}
						
		}
		if(ifptmoved.x != ptemp.x || ifptmoved.y != ptemp.y)
		{
			if (ptemp.m == 0)
				++Step0Count;
			if (ptemp.m == 1)
				++Step1Count;
			if (ptemp.m == 2)
				++Step2Count;
			if (ptemp.m == 3)
				++Step3Count;
		}
		if (ptemp.m == 0)
			Value0 += ptemp.rent;
		if (ptemp.m == 1)
			Value1 += ptemp.rent;
		if (ptemp.m == 2)
			Value2 += ptemp.rent;
		if (ptemp.m == 3)
			Value3 += ptemp.rent;
		
	}
	
}

	OpenGLExample() 
	{
		InitGL();
	}	
};

class GLApp : public TopWindow {
	OpenGLExample gl;
	void timeTick() {
	Refresh();
	}
	
public:
	
	typedef GLApp CLASSNAME;
	GLApp() {
		// Розмір карти
		SetRect(0, 0, 50000, 50000);
		gl.InitGL();
		Add(gl.SizePos());
		Sizeable().Zoomable(); //.Maximize();
		Title("Agent Model");
		
		SetTimeCallback(-1, THISBACK(timeTick));
	}	
};



GUI_APP_MAIN
{
	GLApp().Run();
}

