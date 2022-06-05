using namespace std;
/*Basic c library*/
#include <iostream>
#include <vector>
#include <map>

/*Open GL*/
#include "GL/glut.h"
#include "IL/il.h"
#include "IL/ilu.h"

/*My library*/
#include "engine/core.h"
#include "ic_console.h"

// list of textures
vector<string> textures_list;

ClassScene Scene(textures_list);
ClassICConsole Console(200);

int main(int argc, char *argv[]){
    Scene.MainWindowInit(argc, argv, "ICommander 0.0.1", {0, 0}, {1024, 768}, true );

    // console subwindow
    Scene.SubWindowInit(Console, {10, 10}, {glutGet(GLUT_WINDOW_WIDTH) - 20, Console.window_height});

    glutMainLoop();

    // clear textures
    Scene.ClearTextures();
    glutDestroyWindow(Scene.main_window_id);

    return 0;
}
