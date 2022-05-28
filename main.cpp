using namespace std;
/*Basic c library*/
#include <string>
#include <iostream>
#include <vector>
#include <map>

/*Open GL*/
#include "GL/glut.h"
#include "IL/il.h"
#include "IL/ilu.h"

/*My library*/
#include "engine/core.h"
#include "engine/ic_strings.h"
#include "ships.h"

// id GLwindow
unsigned short int wnd, console;

// application mode:
// 0 - game
// 1 - console
unsigned short int AppMode = 0;

// list of textures
vector<string> textures_list;

// Class for basic functions
ClassScene Scene;
// Class for console
ClassConsole Console;

// repainting OpenGL by reshape window
void SceneReshape(GLsizei Width, GLsizei Height){
    Scene.Reshape(Width, Height);
    // reshaping console window
    glutSetWindow(console);
    glutHideWindow();
    glutReshapeWindow(Width - 20, 200);
    glutShowWindow();
    glutSetWindow(wnd);
}

// repainting OpenGL by reshape window
void ConsoleReshape(GLsizei Width, GLsizei Height){
    Console.Reshape(Width, Height);
}

// painting Scene
void SceneDraw(){
    Scene.Draw();
}

// painting Console
void ConsoleDraw(){
    Console.Draw(Scene, console, wnd);
}

// processing keys in game mode
void GameModeKeys(unsigned char key){
    switch (key){
        // escape - exit
        case 27:
            Scene.ClearTextures();
            glutDestroyWindow(wnd);
        break;
        // "`" key - enter console mode
        case 96:
            Console.visible = true;
            AppMode = 1;
        break;
    }
}

// processing keys in game mode
void ConsoleModeKeys(unsigned char key){
    //std::cout << (int)key;
    // escape - exit to game mode
    if (key == 27){
        Console.visible = false;
        AppMode = 0;
    }
    // saving pressed keys to current_key variable if key and length of string is valid
    if ((key >= 32) && (key <= 126) && (Console.current_key.length() < 50)){
        Console.current_key += key;
    }
    // pressing enter
    if (key == 13){
        Console.Enter(Scene);
    }
    // pressing backspace
    if (key == 8){
        string tmp = Console.current_key;
        Console.current_key = "";
        if (tmp.length() > 0){
            for (unsigned short int i = 0; i < (tmp.length() - 1); i++){
                Console.current_key += tmp[i];
            }
        }
    }
}

// processing keys
void Keyboard(unsigned char key, int x, int y){
    // select application mode
    switch (AppMode){
        // game mode
        case 0:
            GameModeKeys(key);
        break;
        // console mode
        case 1:
            ConsoleModeKeys(key);
        break;
    }
}

// processing arrow keys
void ExtKeyboard(int key, int x, int y){
}

void Idle(){
    SceneDraw();
    ConsoleDraw();
}

int main(int argc, char *argv[]){
    // initializing and create window GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1024, 768);
    wnd = glutCreateWindow("ICommander 0.0.1");
    glutFullScreen();

    // coordinates and borders
    Scene.xpos = 0;
    Scene.ypos = 0;

    // load Textures
    Scene.LoadTextures(textures_list);
    Scene.InitTextures(textures_list.size());

    // defining events of window
    glutDisplayFunc(SceneDraw);
    glutReshapeFunc(SceneReshape);
    glutIdleFunc(Idle);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(ExtKeyboard);

    // background color
    glClearColor(0, 0, 0, 0.0);
    // smoothing paint of color
    glShadeModel(GL_SMOOTH);
    // modified perspective
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    console = glutCreateSubWindow(wnd, 10, 10, glutGet(GLUT_WINDOW_WIDTH) - 20, 200);
    glClearColor(0.0, 1.0, 0.0, 0.0);
    glutDisplayFunc(ConsoleDraw);
    glutReshapeFunc(ConsoleReshape);

    // processing events of window
    glutMainLoop();
    // clear textures
    Scene.ClearTextures();
    glutDestroyWindow(wnd);

    return 0;
}
