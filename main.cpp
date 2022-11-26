#include <iostream>
#include <GL/glut.h>
#include "ObjLoader.hpp"
// #include "Lsystem.hpp"

string filePath = "../Car_Obj/Porsche_911_GT2.obj";

ObjLoader objModel = ObjLoader(filePath);
Bessel_Obj_Loader Bessel_Flag_Obj = Bessel_Obj_Loader("/home/cxy/CG-2022/myObj/Bessel_flag.obj");
// Lsystem L_tree = Lsystem();
//实现移动鼠标观察模型所需变量
static float c = 3.1415926 / 180.0f;
static float r = 1.0f;
static int degree = 90;
static int oldPosY = -1;
static int oldPosX = -1;
// GLfloat eyeY = 1.0;

float eyeX, eyeY, eyeZ, lookX, lookY, lookZ,
	upX, upY, upZ, fieldOfView;

//安置光源
void setLightRes() {
    GLfloat lightPosition[] = { 0.0f, 0.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	// // set the ambient light colour    
	// GLfloat lightA[4] = {0.0,0.9,0.9,1};
	// glLightfv(GL_LIGHT0, GL_AMBIENT, lightA);

	// // set the specular light colour         
	// GLfloat lightS[4] = {0.9,0.9,0.9,1.0};
	// glLightfv(GL_LIGHT0, GL_SPECULAR, lightS);

	// // set the diffuse light colour
	// GLfloat lightD[4] = {0.9,0.9,0.9,1.0};
	// glLightfv(GL_LIGHT0, GL_DIFFUSE, lightD);  

    glEnable(GL_LIGHTING); //启用光源
    glEnable(GL_LIGHT0);   //使用指定灯光
}

//初始化
void init() {
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("ObjLoader");
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    setLightRes();
    glEnable(GL_DEPTH_TEST);
    Bessel_Flag_Obj.init();
    // L_tree.Init();
}

void display()
{
    glColor3f(1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective (45, 1.0, 1, 2000);
    glMatrixMode(GL_MODELVIEW);                            
    glLoadIdentity();                                     
    glTranslatef(0.0f, 0.0f, -5.0f);                                                              
    setLightRes();
    
    // gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, 0, 1, 0);
    // gluLookAt(r*cos(c*degree), eyeY, r*sin(c*degree), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glPushMatrix();
    objModel.Draw();//绘制obj模型
    Bessel_Flag_Obj.Draw();
    
    glPopMatrix();
    glutSwapBuffers();
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


int main(int argc, char* argv[])
{
    // fieldOfView = 45;
	// eyeX = 250;
	// eyeY = 100;
	// eyeZ = 100;
	// lookX = 0;
	// lookY = 50;
	// lookZ = 0;
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(moseMove);
    glutMotionFunc(changeViewPoint);
    glutIdleFunc(myIdle);
    glutMainLoop();
    return 0;
}
