
#include <GL/glut.h>
#include "GLparameters.hpp"
#include "GLsolarsystem.hpp"
#include "ObjLoader.hpp"
// #include "GLSkyBox.hpp"

static float c = 3.1415926 / 180.0f;
static float r = 1.0f; 
static int degree = 90;
static int oldPosY = -1;
static int oldPosX = -1;
float eyeX, eyeY, eyeZ, lookX, lookY, lookZ,
	upX, upY, upZ, fieldOfView;

#include <iostream>
using namespace std;

#define _CenterX_ 0
#define _CenterY_ 0
#define _CenterZ_ 0
#define _upX_ 0
#define _upY_ 1
#define _upZ_ 0

void setLightRes() {
	//光源设置在太阳中心
    // GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    // 光源在 上方
	GLfloat sun_light_position[] = { 0.0f, 100.0f, 0.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
    glEnable(GL_LIGHTING); //启用光源
    glEnable(GL_LIGHT0);   //使用指定灯光

}

GLsolarsystem My_SolarSystem(_CenterX_, _CenterY_, _CenterZ_, _upX_, _upY_, _upZ_);


void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable( GL_TEXTURE_2D );
    glShadeModel( GL_FLAT );
    glDepthFunc(GL_LEQUAL);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 1024);
    glutCreateWindow("SolarSystem"); 
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    setLightRes();
    glEnable(GL_DEPTH_TEST);
    My_SolarSystem.init(); // 一定要放在这里

    // skybox = new GLSkyBox(My_SolarSystem.Camera.EYEX, My_SolarSystem.Camera.EYEY, My_SolarSystem.Camera.EYEZ, SkyBox_Texture_Path, SKY_SIZE);
    My_SolarSystem.Bezier_Flag_Obj.init();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (GLdouble)width / (GLdouble)height, 1.0f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
}

void myIdle()
{
    glutPostRedisplay();
}

void My_SolarSystem_Display()
{
    My_SolarSystem.GLsolarsystem_Display();
}

void My_SolarSystem_Update()
{
    My_SolarSystem.GLsolarsystem_Update();
    // glutSwapBuffers();
    glutPostRedisplay();
}

void My_SolarSystem_Update_Keyboard(unsigned char key,int x,int y)
{
    My_SolarSystem.GLsolarsystem_Keyboard(key, x, y);
}

void MY_SolarSystem_Mouse_Hit(int button, int state, int x, int y)
{
    My_SolarSystem.GLsolarsystem_Mousehit(button, state, x, y);
}

void MY_SolarSystem_Mouse_Move(int x, int y)
{
    My_SolarSystem.GLsolarsystem_Mousemove(x, y);
}

int main(int argc, char*  argv[]) {
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(My_SolarSystem_Display);
    glutIdleFunc(My_SolarSystem_Update);
    glutKeyboardFunc(My_SolarSystem_Update_Keyboard);
	glutMouseFunc(MY_SolarSystem_Mouse_Hit);
	glutMotionFunc(MY_SolarSystem_Mouse_Move);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
