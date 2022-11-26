#include "ObjLoader.hpp"
#include<iostream>
#include <string.h>

ObjLoader::ObjLoader(){

}


// ObjLoader::ObjLoader(string filename) : max_x(-100.0), max_y(-100.0),  max_z(-100.0)
ObjLoader::ObjLoader(string filename)
{
    std::ifstream file(filename);
    std::string line;
	char *pch, *pch_tmp;
	vector<int> faceIndex;
	GLint index;
    
    while (getline(file, line))
    {
        if (line.substr(0, 2) == "vt")
        {

        }
        else if (line.substr(0, 2) == "vn")
        {

        }
        else if (line.substr(0, 1) == "v")
        {
            vector<GLfloat> Point;
            GLfloat x, y, z;
            std::istringstream s(line.substr(2));
            s >> x; s >> y; s >> z;
            x *= 100;
            y = y*100+500;
            z *= 100;
            Point.push_back(x);
            Point.push_back(y);
            Point.push_back(z);
            vSets.push_back(Point);
            // if (x>max_x) {
            //     max_x = x;
            // }
            // if (y>max_y) {
            //     max_y = y;
            // }
            // if (z>max_z) {
            //     max_z = z;
            // }

        }
        else if (line.substr(0, 1) == "f")
        {
            char * c_line = (char*)line.c_str();
			pch = strtok(c_line," ");
            pch = strtok(NULL, "/");
            sscanf(pch, "%d", &index);
            faceIndex.push_back(index-1);

            pch = strtok(NULL, " ");
            pch = strtok(NULL, "/");
            sscanf(pch, "%d", &index);
            faceIndex.push_back(index-1);

            pch = strtok(NULL, " ");
            pch = strtok(NULL, "/");
            sscanf(pch, "%d", &index);
            faceIndex.push_back(index-1);

			fSets.push_back(faceIndex);
			faceIndex.clear();
        }
        else if (line.substr(0, 1) == "#")
        {

        }
        else
        {

        }
    }
    file.close();   
}



void ObjLoader::Draw(){
    glBegin(GL_TRIANGLES);//开始绘制
    for (int i = 0; i < fSets.size(); i++) {

        GLfloat VN[3];
        //三个顶点
        GLfloat SV1[3];
        GLfloat SV2[3];
        GLfloat SV3[3];
        if ((fSets[i]).size() != 3) {
            cout << "the fSetsets_Size is not correct" << endl;
        }
        else {

            GLint firstVertexIndex = (fSets[i])[0];//取出顶点索引
            GLint secondVertexIndex = (fSets[i])[1];
            GLint thirdVertexIndex = (fSets[i])[2];

            SV1[0] = (vSets[firstVertexIndex])[0];//第一个顶点
            SV1[1] = (vSets[firstVertexIndex])[1];
            SV1[2] = (vSets[firstVertexIndex])[2];

            SV2[0] = (vSets[secondVertexIndex])[0]; //第二个顶点
            SV2[1] = (vSets[secondVertexIndex])[1];
            SV2[2] = (vSets[secondVertexIndex])[2];

            SV3[0] = (vSets[thirdVertexIndex])[0]; //第三个顶点
            SV3[1] = (vSets[thirdVertexIndex])[1];
            SV3[2] = (vSets[thirdVertexIndex])[2];
            GLfloat vec1[3], vec2[3], vec3[3];//计算法向量
            //(x2-x1,y2-y1,z2-z1)
            vec1[0] = SV1[0] - SV2[0];
            vec1[1] = SV1[1] - SV2[1];
            vec1[2] = SV1[2] - SV2[2];
            //(x3-x2,y3-y2,z3-z2)
            vec2[0] = SV1[0] - SV3[0];
            vec2[1] = SV1[1] - SV3[1];
            vec2[2] = SV1[2] - SV3[2];

            //(x3-x1,y3-y1,z3-z1)
            vec3[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
            vec3[1] = vec2[0] * vec1[2] - vec2[2] * vec1[0];
            vec3[2] = vec2[1] * vec1[0] - vec2[0] * vec1[1];

            GLfloat D = sqrt(pow(vec3[0], 2) + pow(vec3[1], 2) + pow(vec3[2], 2));

            VN[0] = vec3[0] / D;
            VN[1] = vec3[1] / D;
            VN[2] = vec3[2] / D;

            glNormal3f(VN[0], VN[1], VN[2]);//绘制法向量

            glVertex3f(SV1[0], SV1[1], SV1[2]);//绘制三角面片
            glVertex3f(SV2[0], SV2[1], SV2[2]);
            glVertex3f(SV3[0], SV3[1], SV3[2]);    
        }
    }
    glEnd();
}
 
// ObjLoader::~ObjLoader(){
//     cout << "~ObjLoader" << endl;
//     cout << "max_x: " << max_x << ", max_y: " << max_y << ", max_z: " << max_z << endl; 
//     // max_x: 0.980019, max_y: 0.665978, max_z: 2.2003
// }

Bessel_Obj_Loader::Bessel_Obj_Loader(){

}


Bessel_Obj_Loader::Bessel_Obj_Loader(string filename){
    std::ifstream file(filename);
    std::string line;
    
    while (getline(file, line))
    {
        if (line.substr(0, 1) == "v")
        {
            vector<GLfloat> Point;
            GLfloat x, y, z;
            std::istringstream s(line.substr(2));
            s >> x; s >> y; s >> z;
            x *= 100;
            y = y*100+500;
            z *= 100;
            Point.push_back(x);
            Point.push_back(y);
            Point.push_back(z);
            vSets.push_back(Point);
            // if (x>max_x) {
            //     max_x = x;
            // }
            // if (y>max_y) {
            //     max_y = y;
            // }
            // if (z>max_z) {
            //     max_z = z;
            // }
        }
    }
    for ( int i = 0; i<4; i++ ) {
        for (int j = 0; j<4; j++ ) {
            for ( int k = 0; k<3; k++ ) {
                ctrlPoints[i][j][k] = vSets[i*4+j][k];
            }
        }
    }
    file.close();  
}
void Bessel_Obj_Loader::Draw(){
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glPopMatrix();
    glutSwapBuffers();
}

void Bessel_Obj_Loader::init(){
    // glClearColor(0.0, 0.0, 0.0, 1.0);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlPoints[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
    glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_NORMALIZE);
}