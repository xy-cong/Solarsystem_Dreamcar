#ifndef __ObjLoader__
#define __ObjLoader__

#include <string>
#include <vector>
#include <iostream>
#include <GL/glut.h>
#include <fstream>
#include <sstream>
#include <cmath>
using namespace std;

class ObjLoader{
public:
    ObjLoader();
    ObjLoader(string filename);//构造函数
    // ~ObjLoader();
    void Draw();//绘制函数
    // GLfloat max_x, max_y, max_z;
private:
    vector<vector<GLfloat>> vSets;//存放顶点(x,y,z)坐标
    vector<vector<GLint>> fSets;//存放面的三个顶点索引
};

class Bessel_Obj_Loader{
public:
    Bessel_Obj_Loader();
    Bessel_Obj_Loader(string filename);
    void init();
    // ~Bessel_Obj_Loader();
    void Draw();
private:
    vector<vector<GLfloat>> vSets;
    GLfloat ctrlPoints[4][4][3];
};

#endif