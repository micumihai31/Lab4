/*
 *  Afiseaza o suprafata spline folosind biblioteca GLUT
 */
#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

GLfloat ctlpoints[4][4][3];

GLUnurbsObj *theNurb;

/*
 *  Initializeaza punctele de control pentru o suprafata de forma unei adancituri simetrice
 *  Domeniul punctelor de control intre -3 si +3 in x, y, si z
 */
void initSurface()
{
    for (int u = 0; u < 4; u++) {
        for (int v = 0; v < 4; v++) {
            ctlpoints[u][v][0] = 2.0f * ((GLfloat)u - 1.5f);
            ctlpoints[u][v][1] = 2.0f * ((GLfloat)v - 1.5f);
            if ((u == 1 || u == 2) && (v == 1 || v == 2)) {
                ctlpoints[u][v][2] = 3.0f;
            }
            else {
                ctlpoints[u][v][2] = -3.0f;
            }
        }
    }
}
            
void myInit()
{
    // initializarea buffer-ului de adancime
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    // initializarea atributelor materialului si sursei de lumina
    GLfloat mat_diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat mat_shininess[] = { 100.0f };

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);

    initSurface();

    theNurb = gluNewNurbsRenderer(); // crearea obiectului suprafata spline
    gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 25.0);
    gluNurbsProperty(theNurb, GLU_DISPLAY_MODE, GLU_FILL);
}

void CALLBACK display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(330.0f, 1.0f, 0.0f, 0.0f);
    glScalef(0.5f, 0.5f, 0.5f);

    GLfloat knots[8] = { 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 };
    gluBeginSurface(theNurb);
    gluNurbsSurface(theNurb,
        8, knots,
        8, knots,
        4 * 3,
        3,
        &ctlpoints[0][0][0],
        4, 4,
        GL_MAP2_VERTEX_3);
    gluEndSurface(theNurb);

    glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) return;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLdouble)w / (GLdouble)h, 3.0, 8.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    auxInitDisplayMode(AUX_SINGLE | AUX_RGB);
    auxInitPosition(0, 0, 500, 500);
    auxInitWindow("Suprafata B-Spline");
    myInit();
    auxReshapeFunc(myReshape);
    auxMainLoop(display);
    return 0;
}
