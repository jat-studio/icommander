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
ClassConsole::ClassConsole(unsigned short int window_height){
    ClassConsole::window_height = window_height;
    ClassConsole::str_height = float(ClassConsole::CONSOLE_FONT_PIXELS_HEIGHT * ClassConsole::CONSOLE_WINDOW_SIZE) / float(window_height);
    ClassConsole::lines_count = int( window_height / (ClassConsole::CONSOLE_FONT_PIXELS_HEIGHT + ClassConsole::CONSOLE_FONT_PIXELS_LINE_SPACING) );
    ClassConsole::font_line_spacing = float(ClassConsole::CONSOLE_FONT_PIXELS_LINE_SPACING * ClassConsole::CONSOLE_WINDOW_SIZE) / float(window_height);

    for(unsigned short int i = 0; i < ClassConsole::lines_count; i++){
        ClassConsole::console_str.push_back("");
    }

    ClassConsole::commands["help"] = &ClassConsole::ViewHelp;
    ClassConsole::commands["addobj"] = &ClassConsole::AddSceneObject;
}

// painting Console
void ClassConsole::Draw(ClassScene &active_scene, unsigned short int console, unsigned short int wnd){
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

    // calculate fps
    ClassConsole::fps++;
    ClassConsole::t = glutGet(GLUT_ELAPSED_TIME);
    if (ClassConsole::t - ClassConsole::dt > 1000){
        ClassConsole::console_str[0] = "FPS:" + Int_To_Str((int)(ClassConsole::fps * 1000.0 / (ClassConsole::t - ClassConsole::dt)));
        ClassConsole::dt = ClassConsole::t;
        ClassConsole::fps = 0;
    }

    ClassConsole::str_current_pos = 1.0 - ClassConsole::str_height;
    for (unsigned short int i = 0; i < ClassConsole::lines_count - 1; i++){
        active_scene.DrawStaticString(-0.99, ClassConsole::str_current_pos, 0.0, GLUT_BITMAP_8_BY_13, ClassConsole::console_str[i]);
        ClassConsole::str_current_pos -= ClassConsole::str_height + ClassConsole::font_line_spacing;
    }

    active_scene.DrawStaticString(-0.99, ClassConsole::str_current_pos, 0.0, GLUT_BITMAP_8_BY_13, (ClassConsole::command_str + ClassConsole::current_key + "_"));

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

// processing keyboard keys in console mode
void ClassConsole::ProcessKeys(ClassScene &active_scene, unsigned char key){
    // escape - exit to game mode
    if (key == 27){
        this->visible = false;
        active_scene.app_mode = 0;
    }
    // saving pressed keys to current_key variable if key and length of string is valid
    if ((key >= 32) && (key <= 126) && (this->current_key.length() < 50)){
        this->current_key += key;
    }
    // pressing enter
    if (key == 13){
        this->Enter(active_scene);
    }
    // pressing backspace
    if (key == 8){
        string tmp = this->current_key;
        this->current_key = "";
        if (tmp.length() > 0){
            for (unsigned short int i = 0; i < (tmp.length() - 1); i++){
                this->current_key += tmp[i];
            }
        }
    }
}

// pressing Enter
void ClassConsole::Enter(ClassScene &active_scene){
    // moving console strings up
    for (unsigned short int i = 1; i < ClassConsole::lines_count - 1; i++){
        ClassConsole::console_str[i] = ClassConsole::console_str[i + 1];
    }

    // parse command and arguments
    const string command_value = ClassConsole::current_key;
    vector<string> parsed_command;
    Split_Str( command_value, parsed_command, ' ' );

    //call function
    ClassConsole::console_str[ ClassConsole::lines_count - 2 ] = "error command | ";
    if (ClassConsole::commands.count(parsed_command[0]) > 0){
        (this->*ClassConsole::commands[ parsed_command[0] ])(active_scene, parsed_command);
        ClassConsole::console_str[ ClassConsole::lines_count - 1 ] = "done command | ";
    }

    // saving entered value to last string
    ClassConsole::console_str[ ClassConsole::lines_count - 2 ] += ClassConsole::current_key;

    // clear entering string
    ClassConsole::current_key = "";
}

// add new scene object by type
void ClassConsole::AddSceneObject(ClassScene &active_scene, vector<string> parsed_command){
    unsigned short int object_type = Str_To_Int( parsed_command[1] );

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

// view console commands help
void ClassConsole::ViewHelp(ClassScene &active_scene, vector<string> parsed_command){

}

// destructor
ClassConsole::~ClassConsole(){
    ClassConsole::commands.clear();
}
