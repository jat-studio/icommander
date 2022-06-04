using namespace std;

/*Basic c library*/
#include <string>

/*Open GL*/
#include "GL/glut.h"

// output string
void DrawStaticString(float x, float y, float z, void *font, string input){
    glRasterPos3f(x, y, z);
    unsigned short int len = input.length();
    for(unsigned short int i = 0; i < len; i++){
        glutBitmapCharacter(font, input[i]);
    }
}

// set 2d mode
void setOrthoProjection(GLsizei Width, GLsizei Height){
    glColor3f(0.0, 0.0, 0.0);
    glDisable(GL_BLEND);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 0, Width, Height);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glLoadIdentity();
}

// set 3d mode
void setPerspectiveProjection(){
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_BLEND);
}
