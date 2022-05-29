using namespace std;
#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED

// scale of scene
const float scale = 0.07;

/*#######################   structures   #######################*/
struct intPoint2d{
    int x;
    int y;
};

/*#######################   classes   #######################*/
class ClassSceneObject{
    private:
    public:
        intPoint2d position;

        // constructor
        ClassSceneObject(intPoint2d position);
        // painting object
        virtual void Draw();
        // moving object
        virtual void ProcessMoving(unsigned short int direction, float speed);
        // destructor
        ~ClassSceneObject();
};

class ClassSceneSubWindow;

class ClassScene{
    private:
        void DrawSceneObjects();
        void DrawStars();
    public:
        // application mode:
        // 0 - game
        // 1 - console
        unsigned short int app_mode = 0;
        unsigned short int main_window_id;
        // subwindows
        map<unsigned short int, ClassSceneSubWindow*> subwindows;
        // scene objects
        vector<ClassSceneObject*> scene_objects;

        unsigned short int textures_count;
        // index texture of tiles
        GLuint *texture_tiles;
        // array for loading textures
        map <string, unsigned short int> TextureManager;
        // coordinates of tiles
        int xpos;
        int ypos;

        float camera_xpos = 0.0;
        float camera_ypos = 0.0;

        // constructor
        ClassScene(vector<string> &textures_list);
        // initialization count of textures
        void InitTextures(unsigned short int textures_count);
        // loading texture by filename
        void LoadTextureImage(const char *texture_name, GLuint texture);
        // enter to ortho mode
        void setOrthoProjection(GLsizei Width, GLsizei Height);
        // exit of ortho mode
        void setPerspectiveProjection();
        // output string
        void DrawStaticString(float x, float y, float z, void *font, string input);
        // repainting OpenGL by reshape window
        void Reshape(GLsizei Width, GLsizei Height);
        // loading textures
        void LoadTextures(vector<string> &textures_list);
        // processing keyboard keys
        void ProcessKeys(unsigned char key, int x, int y);
        // deleting textures
        void ClearTextures();
        // painting Scene
        void Draw();
        /*processing move camera
          variable direction:
          0 - left
          1 - right
          2 - up
          3 - down*/
        void ProcessMoving(unsigned short int direction);
        // destructor
        ~ClassScene();

        // friendly classes
        friend class ClassConsole;
};

class ClassSceneSubWindow{
    private:
    public:
        bool visible = false;

        // constructor
        ClassSceneSubWindow();
        // painting window
        virtual void Draw();
        // resizing window
        virtual void Reshape(GLsizei Width, GLsizei Height);
        // processing keyboard keys
        virtual void ProcessKeys(ClassScene &active_scene, unsigned char key, int x, int y);
        // destructor
        ~ClassSceneSubWindow();
};

#endif
