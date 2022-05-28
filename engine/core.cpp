using namespace std;
/*Basic c library*/
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <algorithm>

/*Open GL*/
#include "GL/glut.h"
#include "IL/il.h"
#include "IL/ilu.h"

/*My library*/
#include "engine/core.h"
#include "ships.h"

/*#####################Class Scene Object implementation###################*/
// constructor
ClassSceneObject::ClassSceneObject(intPoint2d position){
    ClassSceneObject::position = position;
}

void ClassSceneObject::Draw(){}

void ClassSceneObject::ProcessMoving(unsigned short int direction, float speed){}

// destructor
ClassSceneObject::~ClassSceneObject(){}

/*#####################Class Scene implementation###################*/
// initialization count of textures
void ClassScene::InitTextures(unsigned short int textures_count){
    // count of textures
    ClassScene::textures_count = textures_count;
    // index texture of tiles
    //texture_tiles = new GLuint[texture_tiles];
}

// set 2d mode
void ClassScene::setOrthoProjection(GLsizei Width, GLsizei Height){
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
void ClassScene::setPerspectiveProjection(){
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_BLEND);
}

// output string
void ClassScene::DrawStaticString(float x, float y, float z, void *font, string input){
    glRasterPos3f(x, y, z);
    unsigned short int len = input.length();
    for(unsigned short int i = 0; i < len; i++){
        glutBitmapCharacter(font, input[i]);
    }
}

// loading texture by filename
void ClassScene::LoadTextureImage(const char *texture_name, GLuint texture){
    // parameters of image
    int width;
    int height;
    int bpp;
    unsigned int type;
    unsigned char *image_data;

    // loading texture
    ilLoad(IL_TGA, texture_name);
    // processing of errors
    int err = ilGetError();
    if (err != IL_NO_ERROR){
        const char *strError = iluErrorString(err);
        cout << "Error loading texture!\n" << texture_name << "\n" << strError << "\n";
        exit(EXIT_FAILURE);
    }
    // getting parameters of image
    width  = ilGetInteger(IL_IMAGE_WIDTH);
    height = ilGetInteger(IL_IMAGE_HEIGHT);
    bpp    = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
    // getting data of image
    image_data = ilGetData();
    // determination type of image
    switch (bpp){
        case 1:
            type = GL_RGB8;
        break;
        case 3:
            type = GL_RGB;
        break;
        case 4:
            type = GL_RGBA;
        break;
    }
    // loading texture into memory
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, bpp, width, height, type, GL_UNSIGNED_BYTE, image_data);
}

// loading textures
void ClassScene::LoadTextures(vector<string> textures_list){
    // create array of textures
    glGenTextures(textures_count, &ClassScene::texture_tiles[0]);

    // initializing il and ilu library
    ilInit();
    iluInit();
    // loading textures
    unsigned short int val = 0;
    for(unsigned short int i = 1; i < textures_list.size(); i += 2){
        ClassScene::TextureManager.insert(pair<string, unsigned short int>(textures_list[i], val));
        string str = textures_list[0];
        str += textures_list[i + 1];
        ClassScene::LoadTextureImage(str.c_str(), ClassScene::texture_tiles[val]);
        val++;
    }
    // enabling textures
    glEnable(GL_TEXTURE_2D);
}

// deleting textures
void ClassScene::ClearTextures(){
    glDeleteTextures(ClassScene::textures_count, &ClassScene::texture_tiles[0]);
}

// painting Scene
void ClassScene::Draw(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(
        ClassScene::camera_xpos, ClassScene::camera_ypos, -6.0,
        ClassScene::camera_xpos, ClassScene::camera_ypos, 1.0,
        0.0, 1.0, 0.0
    );

    // painting world
    glScalef(scale, scale, 0.0);

    ClassScene::DrawSceneObjects();
    ClassScene::DrawStars();

    glutSwapBuffers();
}

void ClassScene::DrawStars(){
    glBegin(GL_POINTS);
    glColor3f(1, 1, 1);
    for (int i = 0; i < 100; i++){
        glVertex3f(rand() % 130 - 65, rand() % 70 - 35, 0);
    }
    glEnd();
}

void ClassScene::DrawSceneObjects(){
    for_each(ClassScene::scene_objects.begin(), ClassScene::scene_objects.end(), mem_fun(&ClassSceneObject::Draw));
}

// repainting OpenGL by reshape window
void ClassScene::Reshape(GLsizei Width, GLsizei Height){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glViewport(0, 0, Width, Height);
    gluPerspective(45.0, (GLfloat) Width / (GLfloat) Height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// destructor
ClassScene::~ClassScene(){
    ClassScene::TextureManager.clear();
}
