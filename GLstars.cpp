#include "GLstars.hpp"
#include <cmath>
#include <iostream>

GLstars::GLstars(){
    // std::cout << "A star with No parameters! " << std::endl;
}

GLstars::GLstars(GLfloat selfRadius, GLfloat aroundRadius, GLfloat selfSpeed, GLfloat aroundSpeed, GLstars* father)
{
    this->selfRadius = selfRadius;
    this->aroundRadius = aroundRadius;
    this->selfSpeed = selfSpeed;
    if (aroundSpeed)
        this->aroundSpeed = 360.0f/aroundSpeed;
    this->father = father;
    this->aroundAlpha = this->selfAlpha = 0;
}

void GLstars::GL_Update(){
    this->selfAlpha += STEP*this->selfSpeed;
    this->aroundAlpha += STEP*this->aroundSpeed;
}

void GLstars::GLstars_Draw(){
    glEnable(GL_LINE_SMOOTH); 
    
    glPushMatrix();
    if(this->father && this->father->aroundRadius){
        glRotatef(this->father->aroundAlpha, 0, 0, 1);
        glTranslatef(this->father->aroundRadius, 0.0, 0.0);
    }
    glBegin(GL_LINES);
    int points_N = 2000;
    for(int i = 0; i<points_N; i++){
        glVertex2f(this->aroundRadius*cos(2*PI*i/points_N), this->aroundRadius*sin(2*PI*i/points_N));
    }
    glEnd();
    glRotatef(this->aroundAlpha, 0, 0, 1);
    glTranslatef(this->aroundRadius, 0.0, 0.0);
    // 行星自转
    glRotatef(this->selfAlpha, 0, 0, 1);
    glColor3f(this->RGBAColor[0], this->RGBAColor[1], this->RGBAColor[2]);

    glutSolidSphere(this->selfRadius, 100, 100);

    glPopMatrix();
}

void GLstars::GLDraw(){
    this->GLstars_Draw();
}

GLstars::~GLstars(){
    // std::cout << "A star Deletes! " << std::endl;
}

GLplanet::GLplanet(){
    // std::cout << "A planet with No parameters! " << std::endl;
}

GLplanet::GLplanet(GLfloat selfRadius, GLfloat aroundRadius, 
    GLfloat selfSpeed, GLfloat aroundSpeed, GLstars* father, GLfloat rgbColor[3]):
    GLstars(selfRadius, aroundRadius, selfSpeed, aroundSpeed, father)
{
    this->RGBAColor[0] = rgbColor[0];
    this->RGBAColor[1] = rgbColor[1];
    this->RGBAColor[2] = rgbColor[2];
}

void GLplanet::GLplanet_Draw(){
    
}

void GLplanet::GLDraw(){
    this->GLplanet_Draw();
    this->GLstars_Draw();
}

GLplanet::~GLplanet(){
    // std::cout << "A planet Deletes! " << std::endl;
}



GLsun::GLsun(){
    // std::cout << "A sun with No parameters! " << std::endl;
}

GLsun::GLsun(GLfloat selfRadius, GLfloat aroundRadius, 
    GLfloat selfSpeed, GLfloat aroundSpeed, GLstars* father, GLfloat rgbColor[3]):
    GLplanet(selfRadius, aroundRadius, selfSpeed, aroundSpeed, father, rgbColor){;}


void GLsun::GLsun_Draw(){
    ;
}


void GLsun::GLDraw(){
    this->GLsun_Draw();
    this->GLplanet_Draw();
    this->GLstars_Draw();
}

GLsun::~GLsun(){
    // std::cout << "A sun Deletes! " << std::endl;
}
