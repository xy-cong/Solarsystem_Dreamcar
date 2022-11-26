#ifndef __GLstars__
#define __GLstars__

#include <GL/glut.h>

#define STEP 1
#define PI 3.1415926535

class GLstars{
public:
    GLfloat selfRadius, aroundRadius;
    GLfloat selfSpeed, aroundSpeed;
    GLfloat RGBAColor[4] = {1.0f,1.0f,1.0f,1.0f};
    GLfloat selfAlpha, aroundAlpha;

    GLstars* father;

    GLstars();
    GLstars(GLfloat selfRadius, GLfloat aroundRadius, GLfloat selfSpeed, GLfloat aroundSpeed, GLstars* father);
    void GLstars_Draw();
    virtual void GL_Update();
    virtual void GLDraw();
    virtual ~GLstars();
};

class GLplanet: public GLstars{
public:
    GLplanet();
    GLplanet(GLfloat selfRadius, GLfloat aroundRadius, GLfloat selfSpeed, GLfloat aroundSpeed, GLstars* father, GLfloat rgbColor[3]);
    void GLplanet_Draw();
    virtual void GLDraw();
    virtual ~GLplanet();
};

class GLsun: public GLplanet{
public:
    GLsun();
    GLsun(GLfloat selfRadius, GLfloat aroundRadius, GLfloat selfSpeed, GLfloat aroundSpeed, GLstars* father, GLfloat rgbColor[3]);
    void GLsun_Draw();
    virtual void GLDraw();
    virtual ~GLsun();
};

#endif