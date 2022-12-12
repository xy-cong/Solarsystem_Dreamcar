#include "GLstars.hpp"
#include <cmath>
#include <iostream>
#include <string>

// ------------------------------------------------------------------------------ //
const int VertexCount = (90 / SPACE) * (360 / SPACE) * 4;

typedef struct
{
    double X;
    double Y;
    double Z;
    double U;
    double V;
} VERTICES;
VERTICES VERTEX_STARS[Stars_N][VertexCount];

GLuint textures[Stars_N];
// ------------------------------------------------------------------------------ //
 
GLstars::GLstars(){
    // std::cout << "A star with No parameters! " << std::endl;
}


GLstars::GLstars(GLfloat selfRadius, GLfloat aroundRadius, GLfloat selfSpeed, GLfloat aroundSpeed, GLstars* father, string Name, const char* TexturePath, GLint index)
{
	this->idx = index;
    this->LoadTextureRAW(TexturePath);
    this->self_Name = Name;
    this->selfRadius = selfRadius;
    this->aroundRadius = aroundRadius;
    this->selfSpeed = selfSpeed;
    if (aroundSpeed)
        this->aroundSpeed = 360.0f/aroundSpeed;
    this->father = father;
    this->aroundAlpha = this->selfAlpha = 0;
	this->CreateSphere(this->selfRadius);

}

void GLstars::LoadTextureRAW( const char * filename )
{
	GLuint texture;
	int width, height;
	unsigned char * data;
	FILE * file;
	file = fopen( filename, "rb" );
	if ( file == NULL ) return;
	width = 2048;
	height = 1024;
	data = (unsigned char *)malloc( width * height * 3 );
	fread( data, width * height * 3, 1, file );
	fclose( file );
	for(int i = 0; i < width * height ; ++i)
	{
		int index = i*3;
		unsigned char B,R;
		B = data[index];
		R = data[index+2];
		data[index] = R;
		data[index+2] = B;
	}
	glGenTextures( 1, &texture );
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glBindTexture( GL_TEXTURE_2D, texture );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );

	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data ); 

	this->GLstars_texture_idx = texture;
	free( data );
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
    // glutSolidSphere(this->selfRadius, 100, 100); // R 经线 纬线

	this->DisplaySphere(this->GLstars_texture_idx);
	glFlush();
}

void GLstars::DisplaySphere (GLuint texture)
{

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int b;
    glBindTexture (GL_TEXTURE_2D, texture);
    glBegin (GL_TRIANGLE_STRIP);

    // assigning the values to the triangle strips
    // assigning values for the sfirst half of the sphere on the strip
    for ( b = 0; b <VertexCount; b++)
    {
        glTexCoord2f (VERTEX_STARS[this->idx][b].U, VERTEX_STARS[this->idx][b].V);
        glVertex3f (VERTEX_STARS[this->idx][b].X, VERTEX_STARS[this->idx][b].Y, -VERTEX_STARS[this->idx][b].Z);
    }

    // assigning values for the other half of the sphere on the triangle strip
    for ( b = 0; b <VertexCount; b++)
    {
        glTexCoord2f (VERTEX_STARS[this->idx][b].U, -VERTEX_STARS[this->idx][b].V);
        glVertex3f (VERTEX_STARS[this->idx][b].X, VERTEX_STARS[this->idx][b].Y, VERTEX_STARS[this->idx][b].Z);
    }
    glEnd();
}

// the function for creating the sphere
void GLstars::CreateSphere (double R) {
    int n;
    double a;
    double b;
    double len, len2;
    n = 0;

    for( b = 0; b <= 90 - SPACE; b+=SPACE){

      for( a = 0; a <= 360 - SPACE; a+=SPACE)
      {
          VERTEX_STARS[this->idx][n].X = R * sin((a) / 180 * PI) * sin((b) / 180 * PI);
          VERTEX_STARS[this->idx][n].Y = R * cos((a) / 180 * PI) * sin((b) / 180 * PI);
          VERTEX_STARS[this->idx][n].Z = R * cos((b) / 180 * PI);
          len = sqrt(VERTEX_STARS[this->idx][n].X * VERTEX_STARS[this->idx][n].X + VERTEX_STARS[this->idx][n].Y * VERTEX_STARS[this->idx][n].Y + VERTEX_STARS[this->idx][n].Z * VERTEX_STARS[this->idx][n].Z);
        //   VERTEX_STARS[this->idx][n].X /= len;
        //   VERTEX_STARS[this->idx][n].Y /= len;
        //   VERTEX_STARS[this->idx][n].Z /= len;
          VERTEX_STARS[this->idx][n].V = (2 * b) / 360;
          VERTEX_STARS[this->idx][n].U = (a) / 360;
          len2 = sqrt(VERTEX_STARS[this->idx][n].V * VERTEX_STARS[this->idx][n].V + VERTEX_STARS[this->idx][n].U * VERTEX_STARS[this->idx][n].U);
          VERTEX_STARS[this->idx][n].V /= len2;
          VERTEX_STARS[this->idx][n].U /= len2;
          n++;

          VERTEX_STARS[this->idx][n].X = R * sin((a) / 180 * PI) * sin((b + SPACE) / 180 * PI);
          VERTEX_STARS[this->idx][n].Y = R * cos((a) / 180 * PI) * sin((b + SPACE) / 180 * PI);
          VERTEX_STARS[this->idx][n].Z = R * cos((b + SPACE) / 180 * PI);
          len = sqrt(VERTEX_STARS[this->idx][n].X * VERTEX_STARS[this->idx][n].X + VERTEX_STARS[this->idx][n].Y * VERTEX_STARS[this->idx][n].Y + VERTEX_STARS[this->idx][n].Z * VERTEX_STARS[this->idx][n].Z);
        //   VERTEX_STARS[this->idx][n].X /= len;
        //   VERTEX_STARS[this->idx][n].Y /= len;
        //   VERTEX_STARS[this->idx][n].Z /= len;
          VERTEX_STARS[this->idx][n].V = (2 * (b + SPACE)) / 360;
          VERTEX_STARS[this->idx][n].U = (a) / 360;
          len2 = sqrt(VERTEX_STARS[this->idx][n].V * VERTEX_STARS[this->idx][n].V + VERTEX_STARS[this->idx][n].U * VERTEX_STARS[this->idx][n].U);
          VERTEX_STARS[this->idx][n].V /= len2;
          VERTEX_STARS[this->idx][n].U /= len2;
          n++;

          VERTEX_STARS[this->idx][n].X = R * sin((a + SPACE) / 180 * PI) * sin((b) / 180 * PI);
          VERTEX_STARS[this->idx][n].Y = R * cos((a + SPACE) / 180 * PI) * sin((b) / 180 * PI);
          VERTEX_STARS[this->idx][n].Z = R * cos((b) / 180 * PI);
          len = sqrt(VERTEX_STARS[this->idx][n].X * VERTEX_STARS[this->idx][n].X + VERTEX_STARS[this->idx][n].Y * VERTEX_STARS[this->idx][n].Y + VERTEX_STARS[this->idx][n].Z * VERTEX_STARS[this->idx][n].Z);
        //   VERTEX_STARS[this->idx][n].X /= len;
        //   VERTEX_STARS[this->idx][n].Y /= len;
        //   VERTEX_STARS[this->idx][n].Z /= len;
          VERTEX_STARS[this->idx][n].V = (2 * b) / 360;
          VERTEX_STARS[this->idx][n].U = (a + SPACE) / 360;
          len2 = sqrt(VERTEX_STARS[this->idx][n].V * VERTEX_STARS[this->idx][n].V + VERTEX_STARS[this->idx][n].U * VERTEX_STARS[this->idx][n].U);
          VERTEX_STARS[this->idx][n].V /= len2;
          VERTEX_STARS[this->idx][n].U /= len2;
          n++;

          VERTEX_STARS[this->idx][n].X = R * sin((a + SPACE) / 180 * PI) * sin((b + SPACE) /180 * PI);
          VERTEX_STARS[this->idx][n].Y = R * cos((a + SPACE) / 180 * PI) * sin((b + SPACE) /180 * PI);
          VERTEX_STARS[this->idx][n].Z = R * cos((b + SPACE) / 180 * PI);
          len = sqrt(VERTEX_STARS[this->idx][n].X * VERTEX_STARS[this->idx][n].X + VERTEX_STARS[this->idx][n].Y * VERTEX_STARS[this->idx][n].Y + VERTEX_STARS[this->idx][n].Z * VERTEX_STARS[this->idx][n].Z);
        //   VERTEX_STARS[this->idx][n].X /= len;
        //   VERTEX_STARS[this->idx][n].Y /= len;
        //   VERTEX_STARS[this->idx][n].Z /= len;
          VERTEX_STARS[this->idx][n].V = (2 * (b + SPACE)) / 360;
          VERTEX_STARS[this->idx][n].U = (a + SPACE) / 360;
          len2 = sqrt(VERTEX_STARS[this->idx][n].V * VERTEX_STARS[this->idx][n].V + VERTEX_STARS[this->idx][n].U * VERTEX_STARS[this->idx][n].U);
          VERTEX_STARS[this->idx][n].V /= len2;
          VERTEX_STARS[this->idx][n].U /= len2;
          n++;
      }
    }
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
    GLfloat selfSpeed, GLfloat aroundSpeed, GLstars* father, GLfloat rgbColor[3], string Name, const char* TexturePath, GLint index):
    GLstars(selfRadius, aroundRadius, selfSpeed, aroundSpeed, father, Name, TexturePath, index)
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
    GLfloat selfSpeed, GLfloat aroundSpeed, GLstars* father, GLfloat rgbColor[3], string Name, const char* TexturePath, GLint index):
    GLplanet(selfRadius, aroundRadius, selfSpeed, aroundSpeed, father, rgbColor, Name, TexturePath, index){;}


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
