using namespace std;
/*Basic c library*/
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <algorithm>
#include <typeinfo>

/*Open GL*/
#include "GL/glut.h"
#include "IL/il.h"
#include "IL/ilu.h"

/*My library*/
#include "engine/core.h"
#include "ships.h"

/*#####################Class Scene Object implementation###################*/
// constructor
ClassSceneObject::ClassSceneObject(floatPoint3d position){
    this->position = position;
}

void ClassSceneObject::Draw(){}

void ClassSceneObject::Move(float deltaTime){
    this->position.x += direction.x * speed * deltaTime;
    this->position.y += direction.y * speed * deltaTime;
    this->position.z += direction.z * speed * deltaTime;
}

// destructor
ClassSceneObject::~ClassSceneObject(){}

/*#####################Class SceneSubWindow implementation###################*/
// constructor
ClassSceneSubWindow::ClassSceneSubWindow(){}

// painting window
void ClassSceneSubWindow::Draw(){}

// resizing window
void ClassSceneSubWindow::Reshape(GLsizei Width, GLsizei Height){}

// processing keyboard keys
void ClassSceneSubWindow::ProcessKeys(ClassScene &active_scene, unsigned char key, int x, int y){}

// register events for window in GL
void RegisterWindowEvents(){}

// destructor
ClassSceneSubWindow::~ClassSceneSubWindow(){}

/*#####################Class Scene implementation###################*/
// constructor
ClassScene::ClassScene(vector<string> &textures_list){
    this->previous_time = glutGet(GLUT_ELAPSED_TIME);

    this->xpos = 0;
    this->ypos = 0;

    // load Textures
    this->LoadTextures(textures_list);
    this->InitTextures(textures_list.size());

    scene_instance = this;
}

// initialization count of textures
void ClassScene::InitTextures(unsigned short int textures_count){
    // count of textures
    this->textures_count = textures_count;
    // index texture of tiles
    //texture_tiles = new GLuint[texture_tiles];
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
void ClassScene::LoadTextures(vector<string> &textures_list){
    // create array of textures
    glGenTextures(textures_count, &this->texture_tiles[0]);

    // initializing il and ilu library
    ilInit();
    iluInit();
    // loading textures
    unsigned short int val = 0;
    for(unsigned short int i = 1; i < textures_list.size(); i += 2){
        this->TextureManager.insert(pair<string, unsigned short int>(textures_list[i], val));
        string str = textures_list[0];
        str += textures_list[i + 1];
        this->LoadTextureImage(str.c_str(), ClassScene::texture_tiles[val]);
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
    glutSetWindow(this->main_window_id);

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(
        this->camera_xpos, this->camera_ypos, -6.0,
        this->camera_xpos, this->camera_ypos, 1.0,
        0.0, 1.0, 0.0
    );

    // painting world
    glScalef(scale, scale, 0.0);

    this->DrawSceneObjects();
    this->DrawStars();

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
    for ( ClassSceneObject* scene_object : this->scene_objects ){
        scene_object->Draw();
    }
}

// processing idle
void ClassScene::Idle(){
    this->Draw();
    this->MoveSceneObjects();

    if (this->subwindows.size() > 0){
        for (
            map<unsigned short int, ClassSceneSubWindow*>::iterator it = this->subwindows.begin();
            it != this->subwindows.end();
            ++it
        ){
            ClassSceneSubWindow subwindow = *it->second;
            glutSetWindow(subwindow.window_id);
            if (!subwindow.visible){
                glutHideWindow();
            } else {
                glutShowWindow();
                subwindow.Draw();
            }
        }
    }
}

// repainting OpenGL by reshape window
void ClassScene::Reshape(GLsizei Width, GLsizei Height){
    glutSetWindow(this->main_window_id);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glViewport(0, 0, Width, Height);
    gluPerspective(45.0, (GLfloat) Width / (GLfloat) Height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);

    if (this->subwindows.size() > 0){
        for (
            map<unsigned short int, ClassSceneSubWindow*>::iterator it = this->subwindows.begin();
            it != this->subwindows.end();
            ++it
        ){
            ClassSceneSubWindow subwindow = *it->second;
            glutSetWindow(subwindow.window_id);
            glutHideWindow();
            glutReshapeWindow( Width - 20, 200 );

            if (subwindow.visible){
                glutShowWindow();
            }
        }
    }

    glutSetWindow(this->main_window_id);
}

// processing keyboard keys
void ClassScene::ProcessKeys(unsigned char key, int x, int y){
    // select application mode
    switch (this->app_mode){
        // game mode
        case 0:
            switch (key){
            // escape - exit
            case 27:
                this->ClearTextures();
                glutDestroyWindow(this->main_window_id);
            break;
            // "`" key - enter console mode
            case 96:
                this->subwindows.begin()->second->visible = true;
                this->app_mode = 1;
            break;
        }
        break;
        // console mode
        case 1:
            this->subwindows.begin()->second->ProcessKeys(*this, key, x, y);
        break;
    }

}

// initialization main window
void ClassScene::MainWindowInit(int argc, char* argv[], const char* name, intPoint2d position, intPoint2d sizes, bool is_fullscreen){
    // initializing and create window GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(position.x, position.y);
    glutInitWindowSize(sizes.x, sizes.y);
    this->main_window_id = glutCreateWindow(name);
    if (is_fullscreen) {
        glutFullScreen();
    }

    // background color
    glClearColor(0, 0, 0, 0.0);
    // smoothing paint of color
    glShadeModel(GL_SMOOTH);
    // modified perspective
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // defining events of main window
    glutDisplayFunc(ClassScene::DrawCallback);
    glutReshapeFunc(ClassScene::ReshapeCallback);
    glutIdleFunc(ClassScene::IdleCallback);
    glutKeyboardFunc(ClassScene::KeyoardCallback);
}

// initialization subwindow
void ClassScene::SubWindowInit(ClassSceneSubWindow &subwindow_obj, intPoint2d position, intPoint2d sizes){
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);

    subwindow_obj.window_id = glutCreateSubWindow(this->main_window_id, position.x, position.y, sizes.x, sizes.y);
    this->subwindows.insert({subwindow_obj.window_id, &subwindow_obj});

    glClearColor(0.0, 1.0, 0.0, 0.0);

    subwindow_instance = &subwindow_obj;
    glutDisplayFunc(ClassSceneSubWindow::DrawCallback);
    glutReshapeFunc(ClassSceneSubWindow::ReshapeCallback);
}

// get delta time
float ClassScene::GetDeltaTime(){
    int t = glutGet(GLUT_ELAPSED_TIME);
    float dt = (t - this->previous_time) / 1000.0;
    this->previous_time = t;

    return dt;
}

// moving objects
void ClassScene::MoveSceneObjects(){
    float deltaTime = this->GetDeltaTime();
    for ( ClassSceneObject* scene_object : this->scene_objects ){
        scene_object->Move(deltaTime);
    }
}

// destructor
ClassScene::~ClassScene(){
    this->TextureManager.clear();
}
