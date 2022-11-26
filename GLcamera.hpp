#ifndef __GLcamera__
#define __GLcamera__

#include <GL/glut.h>

class GLcamera{
public:
    GLcamera();
    GLcamera(GLfloat EYEX, GLfloat EYEY, GLfloat EYEZ, GLfloat VIEW);
    void GLmove(GLfloat move_up_and_down, GLfloat move_right_and_left, GLfloat move_forward_and_backward);
    void GLRotate(GLfloat VIEW_ROTATE);
    ~GLcamera(){};

    GLfloat EYEX, EYEY, EYEZ, VIEW;
};

#endif