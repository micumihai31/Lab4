/*
 *  Programul realizeaza o reprezentare wireframe
 *  pentru o suprafata Bezier, utilizand evaluatori bidimensionali
 */
#include "glos.h"

#include "gl.h"
#include "glu.h"
#include "glaux.h"

// se definesc cele 16 puncte de control
GLfloat ctrlpoints[4][4][3] = {
    {{-1.5, -1.5, 4.0}, {-0.5, -1.5, 2.0},
    {0.5, -1.5, -1.0}, {1.5, -1.5, 2.0}},
    {{-1.5, -0.5, 1.0}, {-0.5, -0.5, 3.0},
    {0.5, -0.5, 0.0}, {1.5, -0.5, -1.0}},
    {{-1.5, 0.5, 4.0}, {-0.5, 0.5, 0.0},
    {0.5, 0.5, 3.0}, {1.5, 0.5, 4.0}},
    {{-1.5, 1.5, -2.0}, {-0.5, 1.5, -2.0},
    {0.5, 1.5, 0.0}, {1.5, 1.5, -1.0}}
};

void CALLBACK display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glLoadIdentity();
    glRotatef(85.0, 1.0, 1.0, 1.0);

    //functia glMap2f defineste caracteristicile suprafetei Bezier
    // - tipul punctelor determinate de functia glEvalCoord2f
    // - intervalul de variatie al parametrului u (0 -1 in acest caz)
    // - intervalul valorilor in tabloul ctrlpoints intre doua puncte de control pe directia u
    // - numarul punctelor de control pe directia u
    // - intervalul de variatie al parametrului v (0 -1 in acest caz)
    // - intervalul valorilor in tabloul ctrlpoints intre doua puncte de control pe directia v
    // - numarul punctelor de control pe directia v
    // - tabloul punctelor de control
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints[0][0][0]);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0); // intervalele de esantionare a suprafetei pentru parametrii u si v

    // urmeaza desenarea wireframe a suprafetei
    // fiecare patch (8X8 patch-uri) este desenat dintr-o linie franta din 30 de segmente de dreapta
    glColor3f(1.0, 0.0, 0.0);
    for (int j = 0; j <= 8; j++) {
        glBegin(GL_LINE_STRIP);
        {
            for (int i = 0; i <= 30; i++) {
                // evalueaza un punct pe suprafata pentru valorile u si v ale ale parametrilor
                glEvalCoord2f((GLfloat)i / 30.0, (GLfloat)j / 8.0); 
            }
        }
        glEnd();
        glBegin(GL_LINE_STRIP);
        {
            for (int i = 0; i <= 30; i++) {
                glEvalCoord2f((GLfloat)j / 8.0, (GLfloat)i / 30.0);
            }
        }
        glEnd();
    }

    glFlush();
}

void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // culoarea background-ului
    glEnable(GL_MAP2_VERTEX_3);
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) return;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) {
        glOrtho(-4.0, 4.0, -4.0 * (GLfloat)h / (GLfloat)w, 4.0 * (GLfloat)h / (GLfloat)w, -4.0, 4.0);
    }
    else {
        glOrtho(-4.0 * (GLfloat)w / (GLfloat)h, 4.0 * (GLfloat)w / (GLfloat)h, -4.0, 4.0, -4.0, 4.0);
    }
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    auxInitDisplayMode(AUX_SINGLE | AUX_RGB);
    auxInitPosition(0, 0, 500, 500);
    auxInitWindow("Suprafata Bezier wireframe");
    myInit();
    auxReshapeFunc(myReshape);
    auxMainLoop(display);
    return 0;
}
