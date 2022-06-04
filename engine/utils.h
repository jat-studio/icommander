using namespace std;
#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

// output string
void DrawStaticString(float x, float y, float z, void *font, string input);
// enter to ortho mode
void setOrthoProjection(GLsizei Width, GLsizei Height);
// exit of ortho mode
void setPerspectiveProjection();

#endif // UTILS_H_INCLUDED
