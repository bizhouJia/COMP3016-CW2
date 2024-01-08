#include "stdlib.h"
#include <GL/glut.h>
#include<iostream>
#include <math.h>

#define _USE_MATH_DEFINES

using namespace std;
GLfloat w = 1100;
GLfloat h = 1100;
double rotate_x = 0.0;
double rotate_y = 0.0;
double rotate_z = 0.0;

// Define color
# define white  1.0 ,  1.0  ,  1.0
# define green  0.0 ,  0.502,  0.0
# define red    0.8 ,  0.0  ,  0.0
# define gray   0.502, 0.502,0.502
# define hgray  0.117, 0.180,0.227
# define blue   0.0  , 0.0  ,  1.0
# define pi  3.14159265
# define gold   1.0,215.0/255.0,0.0
# define hgreen 0.0,100.0/255.0,0.0
# define brown  210.0/255.0, 105.0/255.0,  30.0/255.0
# define nbrown 128.0/255.0, 64.0/255.0, 64.0/255.0
# define door   244.0/255.0 ,164.0/255.0 , 96.0/255.0
# define doorknob   139.0/255.0 ,69.0/255.0,19.0/255.0
# define orange 255.0/255.0, 128.0/255.0, 0.0/255.0
# define sunshine 255.0/255.0, 210.0/255.0, 166.0/255.0

// define 8 points of the house
double house[8][3];

// define map
double map[8][3];

// define the texture of the map and floor
GLuint texGround;
GLuint texFloor;

// offset of image data in a memory block
#define BMP_Header_Length 54
// rotation angle
static GLfloat angle = 0.0f;
// material parameters
// specular reflection, intensity (Color) of the reflected light
GLfloat matiral_specular[4] = { 0.00, 0.00, 0.00, 1.00 };
GLfloat matiral_emission[4] = { 0.00, 0.00, 0.00, 1.00 };
const GLfloat matiral_shininess = 11.00;

// set material
GLfloat sca[3] = { 1.5, 1.5, 1.5 };
GLfloat tra[3] = { -300, 0, -470 };

GLfloat AngleX;
GLfloat AngleY;

// the coordinate of the character
GLfloat cx = 50;
GLfloat cy = 0;
GLfloat cz = 0;

// condition to test show house or not
bool showRoof = true;
bool showWall = true;

// the type of furniture
int tTable = 0;
int tChair = 0;
int tBed = 0;

void setMetiral(GLfloat matiral_diffuse_ambient[4])
{
	// set color
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matiral_diffuse_ambient);
	// set parameters
	// specular reflection, the intensity of the reflected light
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matiral_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, matiral_emission);
	glMaterialf(GL_FRONT_AND_BACK, matiral_shininess, 0);

}

// draw the map
void cons(double x, double y, double z, double x1, double y1, double z1)
{
	map[0][0] = x;
	map[0][1] = y;
	map[0][2] = z;

	map[1][0] = x;
	map[1][1] = y;
	map[1][2] = z + z1;

	map[4][0] = x;
	map[4][1] = y + y1;
	map[4][2] = z;

	map[5][0] = x;
	map[5][1] = y + y1;
	map[5][2] = z + z1 / 2;
	for (int i = 0; i<3; i++)
	{
		if (i == 0)
		{
			map[3][i] = map[0][i] + x1;
			map[2][i] = map[1][i] + x1;
			map[6][i] = map[4][i] + x1;
			map[7][i] = map[5][i] + x1;
		}
		else
		{
			map[3][i] = map[0][i];
			map[2][i] = map[1][i];
			map[6][i] = map[4][i];
			map[7][i] = map[5][i];
		}
	}
}

// draw the house
void construct(double x, double y, double z, double x1, double y1, double z1)
{
	house[0][0] = x;
	house[0][1] = y;
	house[0][2] = z;

	house[1][0] = x;
	house[1][1] = y;
	house[1][2] = z + z1;

	house[2][0] = x + x1;
	house[2][1] = y;
	house[2][2] = z + z1;

	house[3][0] = x + x1;
	house[3][1] = y;
	house[3][2] = z;

	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j<3; j++)
		{
			if (j == 1)
			{
				house[i + 4][j] = house[i][j] + y1;
			}	
			else
			{
				house[i + 4][j] = house[i][j];
			}
		}
	}
}

// to build the shape of the map
void build2()
{
	// bottom base
	glBegin(GL_POLYGON);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(map[0][0], map[0][1], map[0][2]);
	glVertex3f(map[1][0], map[1][1], map[1][2]);
	glVertex3f(map[2][0], map[2][1], map[2][2]);
	glVertex3f(map[3][0], map[3][1], map[3][2]);
	glEnd();

	// left
	glBegin(GL_POLYGON);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(map[1][0], map[1][1], map[1][2]);
	glVertex3f(map[0][0], map[0][1], map[0][2]);
	glVertex3f(map[4][0], map[4][1], map[4][2]);
	glVertex3f(map[5][0], map[5][1], map[5][2]);
	glEnd();

	// right
	glBegin(GL_POLYGON);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(map[7][0], map[7][1], map[7][2]);
	glVertex3f(map[6][0], map[6][1], map[6][2]);
	glVertex3f(map[3][0], map[3][1], map[3][2]);
	glVertex3f(map[2][0], map[2][1], map[2][2]);
	glEnd();

	// front
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(map[5][0], map[5][1], map[5][2]);
	glVertex3f(map[6][0], map[6][1], map[6][2]);
	glVertex3f(map[2][0], map[2][1], map[2][2]);
	glVertex3f(map[1][0], map[1][1], map[1][2]);	
	glEnd();

	// back
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(map[0][0], map[0][1], map[0][2]);
	glVertex3f(map[3][0], map[3][1], map[3][2]);
	glVertex3f(map[7][0], map[7][1], map[7][2]);
	glVertex3f(map[4][0], map[4][1], map[4][2]);
	glEnd();

	// up
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(map[4][0], map[4][1], map[4][2]);
	glVertex3f(map[7][0], map[7][1], map[7][2]);
	glVertex3f(map[6][0], map[6][1], map[6][2]);
	glVertex3f(map[5][0], map[5][1], map[5][2]);
	glEnd();
}

// to build the shape of the house and furniture
void build()
{
	// bottom base
	glBegin(GL_POLYGON);
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(house[0][0], house[0][1], house[0][2]);
	glVertex3f(house[1][0], house[1][1], house[1][2]);
	glVertex3f(house[2][0], house[2][1], house[2][2]);
	glVertex3f(house[3][0], house[3][1], house[3][2]);
	glEnd();

	// left
	glBegin(GL_POLYGON);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(house[1][0], house[1][1], house[1][2]);
	glVertex3f(house[0][0], house[0][1], house[0][2]);
	glVertex3f(house[4][0], house[4][1], house[4][2]);
	glVertex3f(house[5][0], house[5][1], house[5][2]);
	glEnd();

	// right
	glBegin(GL_POLYGON);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(house[7][0], house[7][1], house[7][2]);
	glVertex3f(house[6][0], house[6][1], house[6][2]);
	glVertex3f(house[2][0], house[2][1], house[2][2]);
	glVertex3f(house[3][0], house[3][1], house[3][2]);
	glEnd();

	// front
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(house[5][0], house[5][1], house[5][2]);
	glVertex3f(house[6][0], house[6][1], house[6][2]);
	glVertex3f(house[2][0], house[2][1], house[2][2]);
	glVertex3f(house[1][0], house[1][1], house[1][2]);
	glEnd();

	// back
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(house[0][0], house[0][1], house[0][2]);
	glVertex3f(house[3][0], house[3][1], house[3][2]);
	glVertex3f(house[7][0], house[7][1], house[7][2]);
	glVertex3f(house[4][0], house[4][1], house[4][2]);
	glEnd();

	// up
	glBegin(GL_POLYGON);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(house[4][0], house[4][1], house[4][2]);
	glVertex3f(house[7][0], house[7][1], house[7][2]);
	glVertex3f(house[6][0], house[6][1], house[6][2]);
	glVertex3f(house[5][0], house[5][1], house[5][2]);
	glEnd();
}

// put objects on the map
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	glRotatef(rotate_z, 0.0, 0.0, 1.0);

	glScalef(sca[0], sca[1], sca[2]);
	glTranslatef(tra[0], tra[1], tra[2]);

	// the base of the map
	glBegin(GL_POLYGON);
	construct(-200, 0, -200, 1100, 10, 800);
	glColor3f(green);
	build();

	// set the texture of the map
	GLfloat matiral_diffused[4] = { 0.20, 0.32, 0.80, 1.00 };
	setMetiral(matiral_diffused);
	
	// set the texture of grass
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texGround);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-200, 11, -200);
	glTexCoord2f(0.0f, 5.0f); glVertex3f(-200, 11, 600);
	glTexCoord2f(5.0f, 5.0f); glVertex3f(900, 11, 600);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(900, 11, -200);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// boundary wall

	// point 1
	glBegin(GL_POLYGON);
	construct(-180, 10, -180, 20, 20, 700);
	glColor3f(white);
	build();
	// point 2
	construct(-160, 10, -180, 1040, 20, 20);
	glColor3f(white);
	build();
	// point 3
	construct(860, 10, -180, 20, 20, 700);
	glColor3f(white);
	build();
	// point 4
	construct(-180, 10, 500, 200, 20, 20);
	glColor3f(white);
	build();
	// point 5
	construct(100, 10, 500, 780, 20, 20);
	glColor3f(white);
	build();

	// pillar of the boundary wall

	// point 1
	glBegin(GL_POLYGON);
	construct(-180, 10, -180, 20, 50, 20);
	glColor3f(white);
	build();
	// point 3
	glBegin(GL_POLYGON);
	construct(860, 10, -180, 20, 50, 20);
	glColor3f(white);
	build();
	// point 5
	glBegin(GL_POLYGON);
	construct(100, 10, 500, 20, 50, 20);
	glColor3f(white);
	build();
	// point 4
	glBegin(GL_POLYGON);
	construct(10, 10, 500, 20, 50, 20);
	glColor3f(white);
	build();
	// point 6
	glBegin(GL_POLYGON);
	construct(860, 10, 500, 20, 50, 20);
	glColor3f(white);
	build();
	// point 7
	glBegin(GL_POLYGON);
	construct(-180, 10, 500, 20, 50, 20);
	glColor3f(white);
	build();


	// the maze
	// left wall
	glColor3f(white);
	construct(450, 10, -100, 8, 100, 500);
	build();
	// right wall
	glColor3f(white);
	construct(850, 10, -150, 8, 100, 600);
	build();
	// back wall
	glColor3f(white);
	construct(450, 10, -150, 400, 100, 8);
	build();
	// front wall
	glColor3f(white);
	construct(450, 10, 450, 400, 100, 8);
	build();

	// interior wall
	{
		glColor3f(white);
		construct(450, 10, 400, 50, 100, 8);
		build();
		glColor3f(white);
		construct(500, 10, 350, 8, 100, 50);
		build();
		glColor3f(white);
		construct(550, 10, 300, 8, 100, 50);
		build();
		glColor3f(white);
		construct(500, 10, 300, 50, 100, 8);
		build();
		glColor3f(white);
		construct(500, 10, 250, 8, 100, 50);
		build();
		glColor3f(white);
		construct(500, 10, 250, 50, 100, 8);
		build();
		glColor3f(white);
		construct(550, 10, 250, 50, 100, 8);
		build();
		glColor3f(white);
		construct(600, 10, 250, 8, 100, 50);
		build();
		glColor3f(white);
		construct(600, 10, 300, 50, 100, 8);
		build();
		glColor3f(white);
		construct(550, 10, 400, 8, 100, 50);
		build();
		glColor3f(white);
		construct(550, 10, 350, 50, 100, 8);
		build();
		glColor3f(white);
		construct(600, 10, 350, 8, 100, 50);
		build();
		glColor3f(white);
		construct(600, 10, 400, 50, 100, 8);
		build();
		glColor3f(white);
		construct(650, 10, 400, 50, 100, 8);
		build();
		glColor3f(white);
		construct(700, 10, 400, 50, 100, 8);
		build();
		glColor3f(white);
		construct(750, 10, 400, 50, 100, 8);
		build();
		glColor3f(white);
		construct(800, 10, 350, 8, 100, 50);
		build();
		glColor3f(white);
		construct(750, 10, 350, 50, 100, 8);
		build();
		glColor3f(white);
		construct(750, 10, 300, 8, 100, 50);
		build();
		glColor3f(white);
		construct(700, 10, 350, 50, 100, 8);
		build();
		glColor3f(white);
		construct(750, 10, 250, 8, 100, 50);
		build();
		glColor3f(white);
		construct(700, 10, 250, 50, 100, 8);
		build();
		glColor3f(white);
		construct(700, 10, 300, 8, 100, 50);
		build();
		glColor3f(white);
		construct(700, 10, 200, 8, 100, 50);
		build();
		glColor3f(white);
		construct(650, 10, 250, 8, 100, 50);
		build();
		glColor3f(white);
		construct(650, 10, 200, 8, 100, 50);
		build();
		glColor3f(white);
		construct(800, 10, 250, 50, 100, 8);
		build();
		glColor3f(white);
		construct(800, 10, 200, 8, 100, 50);
		build();
		glColor3f(white);
		construct(800, 10, 150, 8, 100, 50);
		build();
		glColor3f(white);
		construct(800, 10, 100, 8, 100, 50);
		build();
		glColor3f(white);
		construct(800, 10, 50, 8, 100, 50);
		build();
		glColor3f(white);
		construct(750, 10, 50, 50, 100, 8);
		build();
		glColor3f(white);
		construct(750, 10, 0, 8, 100, 50);
		build();
		glColor3f(white);
		construct(800, 10, 0, 50, 100, 8);
		build();
		glColor3f(white);
		construct(800, 10, -50, 8, 100, 50);
		build();
		glColor3f(white);
		construct(800, 10, -100, 8, 100, 50);
		build();
		glColor3f(white);
		construct(750, 10, -100, 50, 100, 8);
		build();
		glColor3f(white);
		construct(700, 10, -100, 50, 100, 8);
		build();
		glColor3f(white);
		construct(650, 10, -100, 50, 100, 8);
		build();
		glColor3f(white);
		construct(600, 10, -100, 50, 100, 8);
		build();
		glColor3f(white);
		construct(450, 10, -100, 50, 100, 8);
		build();
		glColor3f(white);
		construct(500, 10, -100, 8, 100, 50);
		build();
		glColor3f(white);
		construct(550, 10, -100, 8, 100, 50);
		build();
		glColor3f(white);
		construct(600, 10, -100, 8, 100, 50);
		build();
		glColor3f(white);
		construct(550, 10, -50, 8, 100, 50);
		build();
		glColor3f(white);
		construct(500, 10, -50, 8, 100, 50);
		build();
		glColor3f(white);
		construct(500, 10, 0, 8, 100, 50);
		build();
		glColor3f(white);
		construct(550, 10, 0, 50, 100, 8);
		build();
		glColor3f(white);
		construct(600, 10, -50, 50, 100, 8);
		build();
		glColor3f(white);
		construct(650, 10, -50, 50, 100, 8);
		build();
		glColor3f(white);
		construct(700, 10, -50, 8, 100, 50);
		build();
		glColor3f(white);
		construct(650, 10, 0, 50, 100, 8);
		build();
		glColor3f(white);
		construct(650, 10, 0, 8, 100, 50);
		build();
		glColor3f(white);
		construct(650, 10, 50, 50, 100, 8);
		build();
		glColor3f(white);
		construct(700, 10, 50, 8, 100, 50);
		build();
		glColor3f(white);
		construct(700, 10, 100, 50, 100, 8);
		build();
		glColor3f(white);
		construct(750, 10, 100, 8, 100, 50);
		build();
		glColor3f(white);
		construct(700, 10, 200, 50, 100, 8);
		build();
		glColor3f(white);
		construct(600, 10, 200, 50, 100, 8);
		build();
		glColor3f(white);
		construct(550, 10, 200, 50, 100, 8);
		build();
		glColor3f(white);
		construct(500, 10, 200, 50, 100, 8);
		build();
		glColor3f(white);
		construct(450, 10, 200, 50, 100, 8);
		build();
		glColor3f(white);
		construct(450, 10, 150, 50, 100, 8);
		build();
		glColor3f(white);
		construct(500, 10, 100, 8, 100, 50);
		build();
		glColor3f(white);
		construct(650, 10, 150, 8, 100, 50);
		build();
		glColor3f(white);
		construct(600, 10, 150, 50, 100, 8);
		build();
		glColor3f(white);
		construct(550, 10, 150, 50, 100, 8);
		build();
		glColor3f(white);
		construct(500, 10, 50, 50, 100, 8);
		build();
		glColor3f(white);
		construct(550, 10, 50, 50, 100, 8);
		build();
		glColor3f(white);
		construct(600, 10, 0, 8, 100, 50);
		build();
		glColor3f(white);
		construct(650, 10, 50, 8, 100, 50);
		build();
		glColor3f(white);
		construct(600, 10, 100, 50, 100, 8);
		build();
		glColor3f(white);
		construct(550, 10, 100, 50, 100, 8);
		build();
		glColor3f(white);
		construct(700, 10, 150, 8, 100, 50);
		build();
	}

	// wall of the house
	if (showWall)
	{
		// left
		glColor3f(white);
		construct(-120, 10, -100, 12, 150, 300);
		build();
		// right
		glColor3f(white);
		construct(420, 10, -100, 12, 150, 300);
		build();
		// up
		glColor3f(white);
		construct(-120, 10, -100, 550, 150, 12);
		build();
		// down
		glColor3f(white);
		construct(-120, 10, 200, 550, 150, 12);
		build();
	}
	

	// the floor of the house
	glEnable(GL_TEXTURE_2D);   
	glBindTexture(GL_TEXTURE_2D, texFloor);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-120, 15, -100);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-120, 15, 200);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(420, 15, 200);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(420, 15, -100);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// window of the house
	if (showWall)
	{
		glColor4f(blue, 0.35);
		construct(0, 45, 200, 88, 65, 14);
		build();
	}

	// roof of the house
	if (showRoof)
	{
		glColor3f(gray);
		cons(-120, 160, 55, 550, 27, 155);
		build2();
		cons(-120, 187, 55, 550, 27, 135);
		build2();
		cons(-120, 214, 55, 550, 27, 115);
		build2();
		cons(-120, 241, 55, 550, 15, 95);
		build2();
		glColor3f(gray);
		cons(-120, 160, 55, 550, 27, -155);
		build2();
		cons(-120, 187, 55, 550, 27, -135);
		build2();
		cons(-120, 214, 55, 550, 27, -115);
		build2();
		cons(-120, 241, 55, 550, 15, -95);
		build2();
	}
	
	// door of the house
	if (showWall)
	{
		glColor3f(door);
		construct(200, 10, 210, 50, 100, 5);
		build();
		// doorknob
		glColor3f(doorknob);
		construct(200, 60, 215, 5, 5, 5);
		build();
	}

	// table
	// type 1
	if (tTable == 0)
	{
		// surface
		glColor3f(brown);
		construct(0, 50, 50, 50, 1, 50);
		build();
		// table leg
		glColor3f(brown);
		construct(20, 10, 70, 10, 40, 10);
		build();
	}
	// type 2
	else if (tTable == 1)
	{
		glColor3f(brown);
		construct(0, 50, 50, 50, 1, 50);
		build();
		glColor3f(brown);
		construct(0, 10, 50, 3, 40, 3);
		build();
		glColor3f(brown);
		construct(0, 10, 97, 3, 40, 3);
		build();
		glColor3f(brown);
		construct(47, 10, 50, 3, 40, 3);
		build();
		glColor3f(brown);
		construct(47, 10, 97, 3, 40, 3);
		build();
	}
	// type 3
	else if (tTable == 2)
	{
		glColor3f(white);
		construct(0, 50, 50, 50, 1, 50);
		build();
		glColor3f(white);
		construct(20, 10, 70, 10, 40, 10);
		build();
	}
	
	// chair
	// type 1
	if (tChair == 0)
	{
		glColor3f(white);
		construct(-30, 10, 65, 20, 30, 20);
		build();
		glColor3f(white);
		construct(60, 10, 65, 20, 30, 20);
		build();
	}
	// type 2
	else if (tChair == 1)
	{
		glColor3f(brown);
		construct(-30, 10, 65, 20, 30, 20);
		build();
		glColor3f(brown);
		construct(60, 10, 65, 20, 30, 20);
		build();
	}
	// type 3
	else if (tChair == 2)
	{
		glColor3f(white);
		construct(-30, 30, 65, 1, 40, 20);
		build();
		glColor3f(white);
		construct(-30, 10, 65, 20, 30, 20);
		build();
		glColor3f(white);
		construct(80, 30, 65, 1, 40, 20);
		build();
		glColor3f(white);
		construct(60, 10, 65, 20, 30, 20);
		build();
	}

	// bed
	// type 1
	if (tBed == 0)
	{
		glColor3f(brown);
		construct(200, 10, -90, 50, 20, 80);
		build();
		glColor3f(brown);
		construct(200, 10, -95, 50, 40, 5);
		build();
		glColor3f(white);
		construct(200, 30, -90, 50, 5, 80);
		build();
	}
	// type 2
	else if (tBed == 1)
	{
		glColor3f(gold);
		construct(200, 10, -90, 50, 20, 80);
		build();
		glColor3f(gold);
		construct(200, 10, -95, 50, 40, 5);
		build();
		glColor3f(gray);
		construct(200, 30, -90, 50, 5, 80);
		build();
	}
	// type 3
	else if (tBed == 2)
	{
		glColor3f(brown);
		construct(200, 10, -90, 50, 20, 80);
		build();
		glColor3f(brown);
		construct(200, 10, -95, 50, 40, 5);
		build();
		glColor3f(green);
		construct(200, 30, -90, 50, 5, 80);
		build();
	}
	
	if (showWall)
	{
		// tree
		glColor3f(brown);
		construct(-50, 10, 390, 15, 150, 15);
		build();
		// leaves
		// made by several spheres
		glColor3f(hgreen);
		glTranslatef(-50, 140, 400);
		glutSolidSphere(40, 20, 20);

		glTranslatef(20, 0, 0);
		glutSolidSphere(40, 20, 20);

		glTranslatef(-10, 0, -10);
		glutSolidSphere(40, 20, 20);

		glTranslatef(0, 0, 20);
		glutSolidSphere(40, 20, 20);

		glTranslatef(0, 10, -10);
		glutSolidSphere(40, 20, 20);
		glTranslatef(-70, -80, -400);

		// character represented by a sphere
		glColor4f(orange, 0.8);
		glTranslatef(565 - cx, 25 - cy, 250 - cz);
		glutSolidSphere(15, 20, 20);
		glTranslatef(-565, -25, -250);
	}

	// refresh
	glFlush();
	glutSwapBuffers();
}

GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_position[] = { 1.0,1.0,0,0};
GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };

void init(void)
{
	GLfloat sun_direction[] = { 700.0, 400.0, 100.0, 1.0 };
	GLfloat sun_intensity[] = { sunshine, 1.0 };
	GLfloat ambient_intensity[] = { 0.5, 0.5, 0.5, 1.0 };

	// set up ambient light
	glEnable(GL_LIGHTING);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);

	// set up sunlight
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, sun_direction);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_intensity);

	// define the background color to black
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glLineWidth(5);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// enable blending
	glEnable(GL_BLEND);
	// disable depth test
	glDisable(GL_DEPTH_TEST);
	// semi-transparent blending function based on the alpha channel value of the source pixel
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	// enable depth test
	glEnable(GL_DEPTH_TEST);

	// places the camera at (0,0,0) and faces it along(0,0,-1)
	glMatrixMode(GL_PROJECTION);
	// specify clipping volume
	glOrtho(-w, w, -h, h, -w, w);
}

// configuer keys to control the program
void specialkeys(int key, int x, int y)
{
	// movement of the character
	// go right
	if (key == GLUT_KEY_F1)
		cx -= 10;
	// go left
	else if (key == GLUT_KEY_F2)
		cx += 10;
	// go up
	else if (key == GLUT_KEY_F3)
		cz += 10;
	// go down
	else if (key == GLUT_KEY_F4)
		cz -= 10;

	// hide the house to display furniture
	if (key == GLUT_KEY_HOME)
	{
		showRoof = !showRoof;
		showWall = !showWall;
	}

	// change the type of table to display
	if (key == GLUT_KEY_F5)
	{
		tTable += 1;
		// go back to the first type
		if (tTable >= 3)
		{
			tTable = 0;
		}
	}
	
	// change the type of chair to display
	if (key == GLUT_KEY_F6)
	{
		tChair += 1;
		if (tChair >= 3)
		{
			tChair = 0;
		}
	}

	// change the type of bed to display
	if (key == GLUT_KEY_END)
	{
		tBed += 1;
		if (tBed >= 3)
		{
			tBed = 0;
		}
	}

	// rotation of the camera
	if (key == GLUT_KEY_RIGHT)
	{
		rotate_y -= 1;
	}
	else if (key == GLUT_KEY_LEFT)
	{
		rotate_y += 1;
	}	
	else if (key == GLUT_KEY_DOWN)
	{
		rotate_x -= 1;
	}
	else if (key == GLUT_KEY_UP)
	{
		rotate_x += 1;
	}
	
	// scene scaling
	if (key == GLUT_KEY_F7)
	{  
		for (int i = 0; i < 3; i++)
		{
			sca[i] = sca[i] + 0.1;
		}
	}
	else if (key == GLUT_KEY_F8)
	{ 
		for (int i = 0; i < 3; i++)
		{
			sca[i] = sca[i] - 0.1;
		}
	}

	glutPostRedisplay();
}

// to determine if an integer is a power of 2
int power_of_two(int n)
{
	if (n <= 0)
	{
		return 0;
	}
	return (n & (n - 1)) == 0;
}

// load a BMP file as a texture
GLuint load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint last_texture_ID = 0, texture_ID = 0;
	FILE *pFile;
	errno_t err;                                   

	// open the file, exits if fails
	if ((err = fopen_s(&pFile, file_name, "rb")) != 0)    
	{
		printf("Cannot open files\n");
		exit(0);
	}

	// read the width and height of the image from the file
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// calculate the number of bytes per pixel row, and based on this data
	// calculate the total number of bytes for the pixels
	GLint line_bytes = width * 3;
	while (line_bytes % 4 != 0)
	{
		++line_bytes;
	}
	total_bytes = line_bytes * height;

	// allocate memory based on the total number of bytes for the pixels
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return 0;
	}

	// load pixel data
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// if the width and height of the image are not powers of 2, scaling is required
	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if (!power_of_two(width)
			|| !power_of_two(height)
			|| width > max
			|| height > max)
		{
			// specify the new size after scaling as a square with equal side lengths
			const GLint new_width = 256;
			const GLint new_height = 256;
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;

			// calculate the number of bytes required per row and the total number of bytes
			new_line_bytes = new_width * 3;
			while (new_line_bytes % 4 != 0)
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

			// allocate memory
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if (new_pixels == 0)
			{
				free(pixels);
				fclose(pFile);
				return 0;
			}

			// perform pixel scaling
			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			// release the original pixel data, redirect pixels to the new pixel data, and reset the width and height
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}

	// allocate a new texture
	glGenTextures(1, &texture_ID);
	if (texture_ID == 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// bind the new texture, load the texture and set the texture parameters
	// before binding, obtain the ID of the previously bound texture for restoration at the end
	GLint lastTextureID = last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	// restore the previous texture binding
	glBindTexture(GL_TEXTURE_2D, lastTextureID);
	free(pixels);
	return texture_ID;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("The House");
	init();
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);

	cout << "Hi, welcome to my program. You can take some actions to control the character and furniture.\n\n";
	cout << "arrow button of the keyboard to rotate the camera.\n";
	cout << "[F1], [F2], [F3], and [F4] to control the movement of the character.\n";
	cout << "[F7] and [F8] to control the scaling of the camera.\n";
	cout << "[HOME] to hide the house and display furniture.\n";
	cout << "[F5] to change the type of the table.\n";
	cout << "[F6] to change the type of the chair.\n";
	cout << "[END] to change the type of the bed.";

	// enable texture
	glEnable(GL_TEXTURE_2D);
	// load texture
	texGround = load_texture("grass.bmp");
	texFloor = load_texture("floor.bmp");

	glutDisplayFunc(display);
	glutSpecialFunc(specialkeys);	
	glutMainLoop();
	system("pause");
	return 0;
}