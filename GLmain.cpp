
#include <GL/glut.h>
#include "GLparameters.hpp"
#include "GLsolarsystem.hpp"

#include "ObjLoader.hpp"
// string filePath = "../Car_Obj/Porsche_911_GT2.obj";
// ObjLoader objModel = ObjLoader(filePath);
// Bessel_Obj_Loader Bessel_Flag_Obj = Bessel_Obj_Loader("/home/cxy/CG-2022/hw6/Bessel_flag.obj");
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

GLsolarsystem My_SolarSystem(_CenterX_, _CenterY_, _CenterZ_, _upX_, _upY_, _upZ_);

// -------------------------------------------------------------------------- //
//安置光源
// void setLightRes() {
//     GLfloat lightPosition[] = { 0.0f, 0.0f, 1.0f, 0.0f };
//     glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
//     glEnable(GL_LIGHTING); //启用光源
//     glEnable(GL_LIGHT0);   //使用指定灯光
// }

// //初始化
// void init() {
//     glEnable(GL_DEPTH_TEST);
//     glShadeModel(GL_SMOOTH);
//     setLightRes();
//     glEnable(GL_DEPTH_TEST);
//     // Bessel_Flag_Obj.init();
// }
void init() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 1280);
    glutCreateWindow("ObjLoader");
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    setLightRes();
    glEnable(GL_DEPTH_TEST);
    My_SolarSystem.Bessel_Flag_Obj.init();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (GLdouble)width / (GLdouble)height, 1.0f, 200.0f);
    glMatrixMode(GL_MODELVIEW);
}

//移动鼠标360观察模型
void moseMove(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN) {
        oldPosX = x; oldPosY = y;
    }
}

void changeViewPoint(int x, int y)
{
    int temp = x - oldPosX, temp_y = y - oldPosY;
    degree += temp;
    eyeY += temp_y/100.0;
    oldPosX = x;
    oldPosY = y;
}

void myIdle()
{
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    cout << key << endl;
   switch (key) {
	  case 27:			// Esc - Exit the program
		 exit(0);
		 break;
   }
}

// -------------------------------------------------------------------------- //

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
    // fieldOfView = 45;
	// eyeX = 250;
	// eyeY = 0;
	// eyeZ = 100;
	// lookX = 0;
	// lookY = 50;
	// lookZ = 0;
    glutInit(&argc, argv);
    init();
    // glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    // glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
    // glutInitWindowSize(WIDTH, HEIGHT);
    // glutCreateWindow("SolarSystem created by XiaoyanCong");
    glutDisplayFunc(My_SolarSystem_Display);
    glutIdleFunc(My_SolarSystem_Update);
    glutKeyboardFunc(My_SolarSystem_Update_Keyboard);
	glutMouseFunc(MY_SolarSystem_Mouse_Hit);
	glutMotionFunc(MY_SolarSystem_Mouse_Move);
    glutReshapeFunc(reshape);
    // glutKeyboardFunc(keyboard);
    // glutMouseFunc(moseMove);
    // glutMotionFunc(changeViewPoint);
    glutMainLoop();
    return 0;
}


// int main(int argc, char* argv[])
// {
//     glutInit(&argc, argv);
//     init();
//     glutDisplayFunc(My_SolarSystem_Display);
//     // glutReshapeFunc(reshape);
//     glutKeyboardFunc(keyboard);
//     glutMouseFunc(moseMove);
//     glutMotionFunc(changeViewPoint);
//     glutIdleFunc(My_SolarSystem_Update);
//     glutMainLoop();
//     return 0;
// }