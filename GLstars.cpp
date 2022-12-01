#include "GLstars.hpp"
#include <cmath>
#include <iostream>
#include <string>

GLstars::GLstars(){
    // std::cout << "A star with No parameters! " << std::endl;
}

GLstars::GLstars(GLfloat selfRadius, GLfloat aroundRadius, GLfloat selfSpeed, GLfloat aroundSpeed, GLstars* father, string Name)
{
    this->self_Name = Name;
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

void GLstars::Material_Sun()
{
    GLfloat sun_mat_ambient[]  = {0.0f, 0.0f, 0.0f, 1.0f};  //定义材质的环境光颜色
    GLfloat sun_mat_diffuse[]  = {1.0f, 1.0f, 1.0f, 1.0f};  //定义材质的漫反射光颜色
    GLfloat sun_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};  //定义材质的镜面反射光颜色
    GLfloat sun_mat_emission[] = {0.5f, 0.5f, 0.0f, 1.0f};  //定义材质的辐射广颜色
	GLfloat sun_mat_shininess = 0.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
}

void GLstars::Material_Mercury()
{
	// GLfloat earth_mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };  
    GLfloat earth_mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };  
	GLfloat earth_mat_diffuse[] = { 0.0f, 0.5f, 1.0f, 1.0f }; 
	GLfloat earth_mat_specular[] = { 0.8f, 0.8f, 0.8f, 0.2f };  
	GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };  
	GLfloat earth_mat_shininess = 5.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
}

void GLstars::Material_Venus()
{
	GLfloat earth_mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };  
	GLfloat earth_mat_diffuse[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat earth_mat_specular[] = { 0.8f, 0.8f, 0.8f, 0.2f };  
	GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f }; 
	GLfloat earth_mat_shininess = 5.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
}

void GLstars::Material_Earth()
{
	GLfloat earth_mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
	GLfloat earth_mat_diffuse[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	GLfloat earth_mat_specular[] = { 0.8f, 0.8f, 0.8f, 0.2f }; 
	GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };  
	GLfloat earth_mat_shininess = 5.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
}

void GLstars::Material_Moon()
{
	GLfloat earth_mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };  
	GLfloat earth_mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  
	GLfloat earth_mat_specular[] = { 0.8f, 0.8f, 0.8f, 0.2f }; 
	GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f }; 
	GLfloat earth_mat_shininess = 5.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
}

void GLstars::Material_Mars()
{
	GLfloat earth_mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
	GLfloat earth_mat_diffuse[] = { 0.8f, 0.5f, 0.2f, 1.0f };  
	GLfloat earth_mat_specular[] = { 0.8f, 0.8f, 0.8f, 0.2f }; 
	GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };  
	GLfloat earth_mat_shininess = 5.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
}

void GLstars::Material_Jupiter()
{
	GLfloat earth_mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };  
	GLfloat earth_mat_diffuse[] = { 0.0f, 1.0f, 0.0f, 1.0f };  
	GLfloat earth_mat_specular[] = { 0.8f, 0.8f, 0.8f, 0.2f };  
	GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };   
	GLfloat earth_mat_shininess = 5.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
}

void GLstars::Material_Saturn()
{
	GLfloat earth_mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
	GLfloat earth_mat_diffuse[] = { 0.0f, 1.0f, 1.0f, 1.0f }; 
	GLfloat earth_mat_specular[] = { 0.8f, 0.8f, 0.8f, 0.2f };  
	GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f }; 
	GLfloat earth_mat_shininess = 5.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
}

void GLstars::Material_Uranus()
{
	GLfloat earth_mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };  
	GLfloat earth_mat_diffuse[] = { 0.2f, 0.4f, 1.0f, 1.0f };  
	GLfloat earth_mat_specular[] = { 0.8f, 0.8f, 0.8f, 0.2f };   
	GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };  
	GLfloat earth_mat_shininess = 5.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
}

void GLstars::Material_Neptune()
{
	GLfloat earth_mat_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };  
	GLfloat earth_mat_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
	GLfloat earth_mat_specular[] = { 0.8f, 0.8f, 0.8f, 0.2f };  
	GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };  
	GLfloat earth_mat_shininess = 5.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
}

void GLstars::GL_stars_material(){
    if(this->self_Name == "Sun"){
        Material_Sun();
    }else if(this->self_Name == "Mercury"){
        Material_Mercury();
    }else if(this->self_Name == "Venus"){
        Material_Venus();
    }else if(this->self_Name == "Earth"){
        Material_Earth();
    }else if(this->self_Name == "Moon"){
        Material_Moon();
    }else if(this->self_Name == "Mars"){
        Material_Mars();
    }else if(this->self_Name == "Jupiter"){
        Material_Jupiter();
    }else if(this->self_Name == "Saturn"){
        Material_Saturn();
    }else if(this->self_Name == "Uranus"){
        Material_Uranus();
    }else if(this->self_Name == "Neptune"){
        Material_Neptune();
    }
}

void GLstars::GLstars_Draw(){
    glEnable(GL_LINE_SMOOTH); 
    
    glPushMatrix();
    this->GL_stars_material();
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
    // if(this->father)
    //     glutSolidSphere(this->selfRadius, 100, 100); // R 经线 纬线
    glutSolidSphere(this->selfRadius, 100, 100); // R 经线 纬线
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
    GLfloat selfSpeed, GLfloat aroundSpeed, GLstars* father, GLfloat rgbColor[3], string Name):
    GLstars(selfRadius, aroundRadius, selfSpeed, aroundSpeed, father, Name)
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
    GLfloat selfSpeed, GLfloat aroundSpeed, GLstars* father, GLfloat rgbColor[3], string Name):
    GLplanet(selfRadius, aroundRadius, selfSpeed, aroundSpeed, father, rgbColor, Name){;}


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
