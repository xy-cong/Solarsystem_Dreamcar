
#include "GLsolarsystem.hpp"
#include "ObjLoader.hpp"
#include <iostream>
#include <cmath>

int hit_pos_x, hit_pos_y;

int move_pos_x, move_pos_y;

int button_kind;


/*
idx:
0 -- 太阳
1 -- 水星
2 -- 金星
3 -- 地球
4 -- 月亮
5 -- 火星
6 -- 木星
7 -- 土星
8 -- 天王星
9 -- 海王星
*/

GLsolarsystem::GLsolarsystem(){
    // std::cout << "A solarsystem with No Parameters! " << std::endl;
}

const char * Texture_Path[Stars_N] = 
{
    "texture/sun.bmp",
    "texture/mercury.bmp",
    "texture/venus.bmp",
    "texture/earth.bmp",
    "texture/moon.bmp",
    "texture/mars.bmp",
    "texture/jupiter.bmp",
    "texture/saturn.bmp",
    "texture/uranus.bmp",
    "/texture/neptune.bmp",
};

GLSkyBox *skybox;
const char * SkyBox_Texture_Path[6]{
    "texture/sky_top.bmp",
    "texture/sky_bottom.bmp",
    "texture/sky_left.bmp",
    "texture/sky_right.bmp",
    "texture/sky_front.bmp",
    "texture/sky_back.bmp",
};


GLsolarsystem::GLsolarsystem(GLfloat centerX, GLfloat centerY, GLfloat centerZ, GLfloat upX, GLfloat upY, GLfloat upZ)
:Camera(_EYEX_, _EYEY_, _EYEZ_, _VIEW_), objModel("../Car_Obj/Porsche_911_GT2.obj"), Bezier_Flag_Obj("/home/cxy/CG-2022/myObj/Bezier_flag.obj")
{
    this->centerX = centerX;
    this->centerY = centerY;
    this->centerZ = centerZ;
    this->upX = upX;
    this->upY = upY;
    this->upZ = upZ;
}

void GLsolarsystem::init(){
    GLfloat RGBcolor[Stars_N][3] = {
        {1.0, 0.0, 0.0}, // 太阳
        {0.2, 0.2, 0.5}, // 水星
        {1.0, 0.7, 0.0}, // 金星
        {0, 1, 0}, // 地球
        {1, 1, 0}, // 月亮
        {1, 0.5, 0.5}, // 火星
        {1, 1, 0.5}, //木星
        {0.5, 1, 0.5}, //土星
        {0.4, 0.4, 0.4}, // 天王星
        {0.5, 0.5, 1} // 海王星
    };
    this->Stars[Sun] = new GLsun(SUN_SELF_RADIUS, 0, SUN_SELF_SPEED, 0, NULL, RGBcolor[Sun], "Sun", Texture_Path[0], 0); 
    this->Stars[Mercury] = new GLplanet(MER_SELF_RADIUS, MER_AROUND_RADIUS, MER_SELF_SPEED, MER_AROUND_SPEED, this->Stars[Sun], RGBcolor[Mercury], "Mercury", Texture_Path[1], 1);
    this->Stars[Venus] = new GLplanet(VEN_SELF_RADIUS, VEN_AROUND_RADIUS, VEN_SELF_SPEED, VEN_AROUND_SPEED, this->Stars[Sun], RGBcolor[Venus], "Venus", Texture_Path[2], 2);
    this->Stars[Earth] = new GLplanet(EAR_SELF_RADIUS, EAR_AROUND_RADIUS, EAR_SELF_SPEED, EAR_AROUND_SPEED, this->Stars[Sun], RGBcolor[Earth], "Earth", Texture_Path[3], 3);
    this->Stars[Moon] = new GLplanet(MOO_SELF_RADIUS, MOO_AROUND_RADIUS, MOO_SELF_SPEED, MOO_AROUND_SPEED, this->Stars[Earth], RGBcolor[Moon], "Moon", Texture_Path[4], 4);
    this->Stars[Mars] = new GLplanet(MAR_SELF_RADIUS, MAR_AROUND_RADIUS, MAR_SELF_SPEED, MAR_AROUND_SPEED, this->Stars[Sun], RGBcolor[Mars], "Mars", Texture_Path[5], 5);
    this->Stars[Jupiter] = new GLplanet(JUP_SELF_RADIUS, JUP_AROUND_RADIUS, JUP_SELF_SPEED, JUP_AROUND_SPEED, this->Stars[Sun], RGBcolor[Jupiter], "Jupiter", Texture_Path[6], 6);
    this->Stars[Saturn] = new GLplanet(SAT_SELF_RADIUS, SAT_AROUND_RADIUS, SAT_SELF_SPEED, SAT_AROUND_SPEED, this->Stars[Sun], RGBcolor[Saturn], "Saturn", Texture_Path[7], 7);
    this->Stars[Uranus] = new GLplanet(URA_SELF_RADIUS, URA_AROUND_RADIUS, URA_SELF_SPEED, URA_AROUND_SPEED, this->Stars[Sun], RGBcolor[Uranus], "Uranus", Texture_Path[8], 8);
    this->Stars[Neptune] = new GLplanet(NEP_SELF_RADIUS, NEP_AROUND_RADIUS, NEP_SELF_SPEED, NEP_AROUND_SPEED, this->Stars[Sun], RGBcolor[Neptune], "Neptune", Texture_Path[9], 9);

    skybox = new GLSkyBox(this->Camera.EYEX, this->Camera.EYEY, this->Camera.EYEZ, SkyBox_Texture_Path, SKY_SIZE);
}

void GLSetMateria(GLfloat ambient[], GLfloat diffuse[], GLfloat specular[])
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);// 设置环境光成分
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);// 设置镜面反射光成分
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);// 设置漫反射光成分
}
GLfloat mat_ambient_box[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat mat_diffuse_box[] = { 0.0f, 0.0f, 0.0f, 1.0f };
GLfloat mat_specular_box[] = { 0.0f, 0.0f, 0.0f, 1.0f };
float rotateAngle = 0.0f;

void Draw_Sky()
{
	GLSetMateria(mat_ambient_box, mat_diffuse_box, mat_specular_box);

	glPushMatrix(); 
	glTranslatef(skybox->POS_X, skybox->POS_Y, skybox->POS_Z);
	glRotatef(rotateAngle, 0.0f, 1.0f, 0.0f);
	glEnable(GL_TEXTURE_2D);
	skybox->DrawScence(); // 绘制天空盒
	rotateAngle -= 0.01f;
	if (rotateAngle < -360)
		rotateAngle = 0;
	glPopMatrix();
    glFlush();
}

void GLsolarsystem::GLsolarsystem_Update()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    for (int i = 0; i<Stars_N; i++){
        Stars[i]->GL_Update();
    }
}
// void setLightRes() {
//     // GLfloat lightPosition[] = { 0.0f, 1000.0f, 1.0f, 0.0f };
//     // GLfloat lightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//     // glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
//     // glEnable(GL_LIGHTING); //启用光源
//     // glEnable(GL_LIGHT0);   //使用指定灯光
// 	//光源设置在太阳中心
// 	GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
// 	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
//     glEnable(GL_LIGHTING); //启用光源
//     glEnable(GL_LIGHT0);   //使用指定灯光
// }

void GLsolarsystem::GLsolarsystem_Display()
{
    glColor3f(1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(75.0f, 1.0f, 1.0f, 40000000);
    glMatrixMode(GL_MODELVIEW);                            
    glLoadIdentity();                                     
    glTranslatef(0.0f, 0.0f, -5.0f);       
    gluLookAt(this->Camera.EYEX, this->Camera.EYEY, this->Camera.EYEZ, this->centerX, this->centerY, this->centerZ, this->upX, this->upY, this->upZ);
    glEnable(GL_TEXTURE_2D);

    Draw_Sky();

    for(int i = 0; i<Stars_N; i++){
        glPushMatrix();
        this->Stars[i]->GLDraw();
        glPopMatrix();
    }
    objModel.Draw();
    Bezier_Flag_Obj.Draw();
    
}

void GLsolarsystem::GLsolarsystem_Keyboard(unsigned char key,int x,int y)
{
    int move = 20;
    switch (key)
    {
    case 27:
        std::cout << "Exit(0)" << std::endl;
        exit(0);
        break;
    case 'q':
        this->Camera.GLmove(move, 0.0, 0.0); // Up
        break;
    case 'a':
        this->Camera.GLmove(-move, 0.0, 0.0); // Down
        break;
    case 'w':
        this->Camera.GLmove(0.0, move, 0.0); // Right 
        break;
    case 's':
        this->Camera.GLmove(0.0, -move, 0.0); // Left
        break;
    case 'e':
        this->Camera.GLmove(0.0, 0.0, move); // Forward
        break;
    case 'd':
        this->Camera.GLmove(0.0, 0.0, -move); // Backward
        break;
    default:
        break;
    }
}

void GLsolarsystem::GLsolarsystem_Mousehit(int button, int state, int x, int y)
{
    button_kind = button;
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if ( state == GLUT_DOWN ){
            hit_pos_x = x;
            hit_pos_y = y;
        }
        break;
    case GLUT_RIGHT_BUTTON:
        if ( state == GLUT_DOWN ){
            hit_pos_x = x;
            hit_pos_y = y;
        }
        break;
    
    default:
        break;
    }
}

void GLsolarsystem::GLsolarsystem_Mousemove(int x, int y)
{
	move_pos_x = x;
	move_pos_y = y;
    int delta_x = move_pos_x - hit_pos_x;
    int delta_y = move_pos_y - hit_pos_y;
    if(button_kind == 0)
    {
        GLfloat EYEX = this->Camera.EYEX;
        GLfloat EYEY = this->Camera.EYEY;
        GLfloat EYEZ = this->Camera.EYEZ;
        GLfloat theta_Z = 3*(delta_x/1280.0)*PI/180;
        this->Camera.EYEX = EYEX*cos(theta_Z) - EYEY*sin(theta_Z);
        this->Camera.EYEY = EYEX*sin(theta_Z) + EYEY*cos(theta_Z);

        GLfloat theta_X = (delta_y/1280.0)*PI/180;
        this->Camera.EYEY = EYEY*cos(theta_X) - EYEZ*sin(theta_X);
        this->Camera.EYEZ = EYEY*sin(theta_X) + EYEZ*cos(theta_X);
    }
        
    if(button_kind == 2)
    {
        GLfloat upX = this->upX;
        GLfloat upZ = this->upZ;
        GLfloat dis = sqrt(delta_x*delta_x+delta_y*delta_y);
        if (delta_y < 0)
            dis = -dis;
        GLfloat theta_Y = 3*(dis/1280.0)*PI/180;
        this->upX = upX*cos(theta_Y) - upZ*sin(theta_Y);
        this->upZ = upX*sin(theta_Y) + upZ*cos(theta_Y);
    }
        
}

GLsolarsystem::~GLsolarsystem(){
    for (int i = 0; i<Stars_N; i++){
        delete Stars[i];
    }
}