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
#include "engine.h"
#include "ships.h"

/*#####################Class Ship implementation###################*/
void ClassShip::Draw(){}

void ClassShip::ProcessMoving(unsigned short int direction, float speed){}

ClassShip::~ClassShip(){}

/*#####################Class Triangle Ship implementation###################*/
void ClassTriangleShip::ProcessMoving(unsigned short int direction, float speed){}

void ClassTriangleShip::Draw(){
    glColor3f(1, 1, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);
    glVertex3f(1, 1, 0);
}

ClassTriangleShip::~ClassTriangleShip(){}

/*#####################Class Quad Ship implementation###################*/
void ClassQuadShip::ProcessMoving(unsigned short int direction, float speed){}

void ClassQuadShip::Draw(){
    glColor3f(1, 1, 1);
    glVertex3f(2, 0, 0);
    glVertex3f(3, 0, 0);
    glVertex3f(3, 1, 0);
    glVertex3f(2, 1, 0);
}

ClassQuadShip::~ClassQuadShip(){}
