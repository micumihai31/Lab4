#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

GLUnurbsObj *theNurb; // curba este un obiect de tipul GLUnurbsObj

void myInit()
{
	theNurb = gluNewNurbsRenderer();
	gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 10.0); // eroarea de esantionare a curbei la redare
	glLineStipple(1, 0x0F0F);
	glPointSize(5);
}

void CALLBACK display()
{	
	// 9 puncte de control
	GLfloat ctlpoints[9][3] = {
		{0.0, 0.0, 0.0},
		{1.0, 0.0, 0.0},
		{2.0, 0.0, 0.0},
		{2.0, 1.0, 0.0},
		{1.0, 2.0, 0.0},
		{0.0, 1.0, 0.0},
		{0.0, -2.0, 0.0},
		{1.0, -2.0, 0.0},
		{2.0, -1.0, 0.0},
	};

	// 13 noduri
	GLfloat knots[13] = { 0.0, 0.0, 0.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 6.0, 6.0, 6.0 };

	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0.2, 0.0, -1.0);
	glScalef(0.2, 0.2, 0.2);


	// redarea curbei Spline
	glColor3f(1.0, 1.0, 1.0); // culoarea curenta de desenare
	gluBeginCurve(theNurb);
	gluNurbsCurve(theNurb,	// pointer obiect NURBS
		13, knots,			// numar noduri, tablou noduri
		3,					// intervalul de valori dintre doua puncte de control consecutive
		&ctlpoints[0][0],	// vector puncte de control
		4,					// ordinul curbei 
		GL_MAP1_VERTEX_3);	// tip evaluator
	gluEndCurve(theNurb);

	// punctele de control
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POINTS);
	{
		for (int i = 0; i < 9; i++) {
			glVertex3fv(&ctlpoints[i][0]);
		}
	}
	glEnd();

	// poligonul caracteristic
	glEnable(GL_LINE_STIPPLE);
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	{
		for (int i = 0; i < 9; i++) {
			glVertex3fv(&ctlpoints[i][0]);
		}
	}
	glEnd();
	glDisable(GL_LINE_STIPPLE);

	glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		gluOrtho2D(-1.0, 1.0, -1.0 * (GLfloat)h / (GLfloat)w, 1.0 * (GLfloat)h / (GLfloat)w);
	}
	else {
		gluOrtho2D(-1.0 * (GLfloat)w / (GLfloat)h, 1.0 * (GLfloat)w / (GLfloat)h, -1.0, 1.0);
	}
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_SINGLE | AUX_RGB);
	auxInitPosition(0, 0, 500, 500);
	auxInitWindow("Curba B-spline");
	myInit();
	auxReshapeFunc(myReshape);
	auxMainLoop(display);
	return 0;
}
