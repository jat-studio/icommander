using namespace std;
/*Basic c library*/
#include <vector>
#include <string>
#include <map>

/*Open GL*/
#include "GL/glut.h"
#include "IL/il.h"
#include "IL/ilu.h"

/*My library*/
#include "engine/core.h"
#include "ships.h"

/*#####################Class Ship implementation###################*/
void ClassShip::Draw(){}

void ClassShip::ProcessMoving(unsigned short int direction, float speed){}

ClassShip::~ClassShip(){}

/*#####################Class Triangle Ship implementation###################*/
void ClassTriangleShip::ProcessMoving(unsigned short int direction, float speed){}

void ClassTriangleShip::Draw(){
    glBegin(GL_POLYGON);
    glColor3f(0, 1, 0);
    glVertex3f(ClassTriangleShip::position.x, ClassTriangleShip::position.y, 0);
    glVertex3f(ClassTriangleShip::position.x, ClassTriangleShip::position.y + 1, 0);
    glVertex3f(ClassTriangleShip::position.x + 1, ClassTriangleShip::position.y + 1, 0);
    glEnd();
}

ClassTriangleShip::~ClassTriangleShip(){}

/*#####################Class Quad Ship implementation###################*/
void ClassQuadShip::ProcessMoving(unsigned short int direction, float speed){}

void ClassQuadShip::Draw(){
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 1);
    glVertex3f(ClassQuadShip::position.x, ClassQuadShip::position.y, 0);
    glVertex3f(ClassQuadShip::position.x + 1, ClassQuadShip::position.y, 0);
    glVertex3f(ClassQuadShip::position.x + 1, ClassQuadShip::position.y + 1, 0);
    glVertex3f(ClassQuadShip::position.x, ClassQuadShip::position.y + 1, 0);
    glEnd();
}

ClassQuadShip::~ClassQuadShip(){}
