#ifndef __GLstars__
#define __GLstars__

#include <GL/glut.h> 
#include "GLparameters.hpp"
#include <iostream>
#include <string> 



enum STARS
{
  SUN, MER, VEN, EAR, MOO, MAR, JUP, SAT, URA, NEP  
};
using namespace std;

#define STEP 1

class GLstars{
public:
    GLfloat selfRadius, aroundRadius;
    GLfloat selfSpeed, aroundSpeed;
    GLfloat RGBAColor[4] = {1.0f,1.0f,1.0f,1.0f};
    GLfloat selfAlpha, aroundAlpha;
    GLint idx;
    GLint GLstars_texture_idx;

    GLstars* father;

    string self_Name;
    GLstars();
    GLstars(GLfloat selfRadius, GLfloat aroundRadius, GLfloat selfSpeed, GLfloat aroundSpeed, GLstars* father, string Name, const char* TexturePath, GLint index);
    void GLstars_Draw();
    void GL_stars_material();

    void CreateSphere (double R);
    void DisplaySphere (GLuint texture);
    void LoadTextureRAW( const char * filename );

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
    GLplanet(GLfloat selfRadius, GLfloat aroundRadius, GLfloat selfSpeed, GLfloat aroundSpeed, GLstars* father, GLfloat rgbColor[3], string Name, const char* TexturePath, GLint index);
    void GLplanet_Draw();
    virtual void GLDraw();
    virtual ~GLplanet();
};

class GLsun: public GLplanet{
public:
    GLsun();
    GLsun(GLfloat selfRadius, GLfloat aroundRadius, GLfloat selfSpeed, GLfloat aroundSpeed, GLstars* father, GLfloat rgbColor[3], string Name, const char* TexturePath, GLint index);
    void GLsun_Draw();
    virtual void GLDraw();
    virtual ~GLsun();
};

#endif