using namespace std;

/*Basic c library*/
#include <iostream>
#include <map>
#include <string>
#include <vector>

/*Open GL*/
#include "GL/glut.h"

/*My library*/
#include "engine/core.h"
#include "engine/console.h"
#include "engine/ic_strings.h"
#include "ships.h"

/*#####################Class Console implementation###################*/
// constructor
ClassConsole::ClassConsole(){
    for(unsigned short int i = 0; i <= 13; i++){
        ClassConsole::console_str[i] = "";
    }
    ClassConsole::dualcommands["goto"] = &ClassConsole::Goto_x_y;
    ClassConsole::singlecommands["addobj"] = &ClassConsole::AddSceneObject;
}

// painting Console
void ClassConsole::Draw(ClassScene &Object, unsigned short int console, unsigned short int wnd){
    glutSetWindow(console);
    if (!ClassConsole::visible){
        glutHideWindow();
    }
    else{
        glutShowWindow();
    }

    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    glColor3f(0.0, 0.0, 0.0);

    // drawing fps
    ClassConsole::fps++;
    ClassConsole::t = glutGet(GLUT_ELAPSED_TIME);
    if (ClassConsole::t - ClassConsole::dt > 1000){
        ClassConsole::console_str[0] = "FPS:" + Int_To_Str((int)(ClassConsole::fps * 1000.0 / (ClassConsole::t - ClassConsole::dt)));
        ClassConsole::dt = ClassConsole::t;
        ClassConsole::fps = 0;
    }
    ClassConsole::str_current_pos = ClassConsole::str_start_pos;
    Object.DrawStaticString(-0.99, ClassConsole::str_current_pos, 0.0, GLUT_BITMAP_8_BY_13, ClassConsole::console_str[0]);
    ClassConsole::str_current_pos -= ClassConsole::str_height;

    // drawing coordinates
    ClassConsole::console_str[1] = "X: ";
    ClassConsole::console_str[1] += Int_To_Str(Object.xpos);
    ClassConsole::console_str[1] += "; Y: ";
    ClassConsole::console_str[1] += Int_To_Str(Object.ypos);
    Object.DrawStaticString(-0.99, ClassConsole::str_current_pos, 0.0, GLUT_BITMAP_8_BY_13, ClassConsole::console_str[1]);
    ClassConsole::str_current_pos -= ClassConsole::str_height;

    for (unsigned short int i = 4; i <= 13; i++){
        Object.DrawStaticString(-0.99, ClassConsole::str_current_pos, 0.0, GLUT_BITMAP_8_BY_13, ClassConsole::console_str[i]);
        ClassConsole::str_current_pos -= ClassConsole::str_height;
    }

    Object.DrawStaticString(-0.99, ClassConsole::str_current_pos, 0.0, GLUT_BITMAP_8_BY_13, (ClassConsole::command_str + ClassConsole::current_key + "_"));

    glFlush();

    glutSetWindow(wnd);
}

// set 2d mode
void ClassConsole::Reshape(GLsizei Width, GLsizei Height){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, Width, Height);
    gluOrtho2D(0, 0, Width, Height);
    glMatrixMode(GL_MODELVIEW);
}

// pressing Enter
void ClassConsole::Enter(ClassScene &active_scene){
    // moving console strings up
    for (unsigned short int i = 4; i <= 12; i++){
        ClassConsole::console_str[i] = ClassConsole::console_str[i + 1];
    }
    // running entered to console command
    unsigned short int i = 0;
    unsigned short int len = ClassConsole::current_key.length();
    string command = "";
    while ((ClassConsole::current_key[i] != ' ') && (i < len)){
        command += ClassConsole::current_key[i];
        i++;
    }
    i++;
    string param1 = "";
    while ((ClassConsole::current_key[i] != ' ') && (i < len)){
        param1 += ClassConsole::current_key[i];
        i++;
    }
    i++;
    string param2 = "";
    while ((ClassConsole::current_key[i] != ' ') && (i < len)){
        param2 += ClassConsole::current_key[i];
        i++;
    }
    // preparing to call function
    bool valid1 = false;
    bool valid2 = false;
    int intparam1 = Str_To_Int(param1, &valid1);
    int intparam2 = Str_To_Int(param2, &valid2);
    ClassConsole::console_str[13] = "error command | ";
    // call function with two parameters
    if (valid1 && valid2){
        if (ClassConsole::dualcommands.count(command) > 0){
            (this->*ClassConsole::dualcommands[command])(active_scene, intparam1, intparam2);
            ClassConsole::console_str[13] = "done command | ";
        }
    }
    // call function with one parameter
    if (valid1 && !valid2){
        if (ClassConsole::singlecommands.count(command) > 0){
            (this->*ClassConsole::singlecommands[command])(active_scene, intparam1);
            ClassConsole::console_str[13] = "done command | ";
        }
    }
    // saving entered value to down string
    ClassConsole::console_str[13] += ClassConsole::current_key;
    // clear entering string
    ClassConsole::current_key = "";
}

// goto x and y coordinates
void ClassConsole::Goto_x_y(ClassScene &active_scene, int x, int y){
    std::cout << x;
    std::cout << ";";
    std::cout << y;
    std::cout << ";\n";
}

// add new scene object by type
void ClassConsole::AddSceneObject(ClassScene &active_scene, int object_type){
    intPoint2d position;
    position.x = rand() % 130 - 65;
    position.y = rand() % 70 - 35;
    switch (object_type){
        case 0:
            active_scene.scene_objects.push_back(new ClassTriangleShip(position));
        break;
        case 1:
            active_scene.scene_objects.push_back(new ClassQuadShip(position));
        break;
    }
}

// destructor
ClassConsole::~ClassConsole(){
    ClassConsole::dualcommands.clear();
    ClassConsole::singlecommands.clear();
}
