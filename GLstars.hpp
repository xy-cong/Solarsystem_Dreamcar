#ifndef __GLstars__
#define __GLstars__

#include <GL/glut.h>
#include <iostream>
#include <string> 
using namespace std;

#define STEP 1
#define PI 3.1415926535

class GLstars{
public:
    GLfloat selfRadius, aroundRadius;
    GLfloat selfSpeed, aroundSpeed;
    GLfloat RGBAColor[4] = {1.0f,1.0f,1.0f,1.0f};
    GLfloat selfAlpha, aroundAlpha;

    GLstars* father;

    string self_Name;
    GLstars();
    GLstars(GLfloat selfRadius, GLfloat aroundRadius, GLfloat selfSpeed, GLfloat aroundSpeed, GLstars* father, string Name);
    void GLstars_Draw();
    void GL_stars_material();

    void Material_Sun();
    void Material_Mercury();
    void Material_Venus();
    void Material_Earth();
    void Material_Moon();
    void Material_Mars();
    void Material_Jupiter();
    void Material_Saturn();
    void Material_Uranus();
    void Material_Neptune();

    virtual void GL_Update();
    virtual void GLDraw();
    virtual ~GLstars();
};

class GLplanet: public GLstars{
public:
    GLplanet();
    GLplanet(GLfloat selfRadius, GLfloat aroundRadius, GLfloat selfSpeed, GLfloat aroundSpeed, GLstars* father, GLfloat rgbColor[3], string Name);
    void GLplanet_Draw();
    virtual void GLDraw();
    virtual ~GLplanet();
};

class GLsun: public GLplanet{
public:
    GLsun();
    GLsun(GLfloat selfRadius, GLfloat aroundRadius, GLfloat selfSpeed, GLfloat aroundSpeed, GLstars* father, GLfloat rgbColor[3], string Name);
    void GLsun_Draw();
    virtual void GLDraw();
    virtual ~GLsun();
};

#endif