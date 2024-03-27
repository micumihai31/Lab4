/*
 Programul utilizeaza evaluatorii pentru determinarea punctelor de pe curba Bezier
*/
#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

GLfloat ctrlpoints[4][3] = {
	// coordonatele celor 4 puncte de control
	{ -1.0, 0.0, 0.0}, { 0.0, 2.0, 0.0}, {2.0, 2.0, 0.0}, {3.0, 0.0, 0.0} };

GLfloat ctrlpoints1[5][3] = {
	// coordonatele celor 4 puncte de control
	{ 3.0, 0.0, 0.0}, { 4.0, -2.0, 0.0}, {6.0, -2.0, 0.0}, {7.0, 0.0, 0.0} };
	
void myInit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0); // culoarea background-ului
	glLineStipple(1, 0x0F0F); // forma liniei punctate
	glEnable(GL_MAP1_VERTEX_3);
}

void CALLBACK display(void)
{
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 0.0f); // culoarea curenta de desenare

	//functia glMap1f defineste caracteristicile curbei:
	// - tipul punctelor de control date in vectorul ctrlpoints, si al datelor de iesire generate
	//   de functia de evaluare glEvalCoord1f
	// - valorile extreme luate de parametrul u (0 si 1 in acst caz)
	// - numarul coordonatelor date pentru fiecare punct de control, in tabloul ctrlpoints
	// - numarul punctelor de control pe baza carora se va determina ordinul curbei (numar puncte-1)
	// - vectorul punctelor de control
	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
	glBegin(GL_LINE_STRIP); // se deseneaza curba prin segmente de dreapta
	{
		for (int i = 0; i <= 30; i++) {
			glEvalCoord1f((GLfloat)i / 30.0f); // pentru cele 30 varfuri determinate de functia glEvalCoord1f
		}
	}
	glEnd();

	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints1[0][0]);
	glBegin(GL_LINE_STRIP); // se deseneaza curba prin segmente de dreapta
	{
		for (int i = 0; i <= 30; i++) {
			glEvalCoord1f((GLfloat)i / 30.0f); // pentru cele 30 varfuri determinate de functia glEvalCoord1f
		}
	}
	glEnd();

	// se afiseaza punctele de control
	glPointSize(5.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	{
		for (int i = 0; i < 4; i++) {
			glVertex3fv(&ctrlpoints[i][0]);
		}
	}
	glEnd();

	glPointSize(5.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	{
		for (int i = 0; i < 4; i++) {
			glVertex3fv(&ctrlpoints[i][0]);
		}
	}
	glEnd();

	// se afiseaza poligonul caracteristic
	glColor3f(1.0f, 0.0f, 1.0f);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINE_STRIP);
	{
		for (int i = 0; i < 4; i++) {
			glVertex3fv(&ctrlpoints[i][0]);
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
		glOrtho(-5.0, 5.0, -5.0 * (GLfloat)h / (GLfloat)w, 5.0 * (GLfloat)h / (GLfloat)w, -5.0, 5.0);
	}
	else {
		glOrtho(-5.0 * (GLfloat)w / (GLfloat)h, 5.0 * (GLfloat)w / (GLfloat)h, -5.0, 5.0, -5.0, 5.0);
	}
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_SINGLE | AUX_RGB);
	auxInitPosition(0, 0, 500, 500);
	auxInitWindow("Curbe Bezier");
	myInit();
	auxReshapeFunc(myReshape);
	auxMainLoop(display);
	return 0;
}
