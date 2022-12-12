#include <GL/glut.h>

class GLSkyBox
{
public:
	float POS_X;
	float POS_Y; 
	float POS_Z;
	GLuint texture_id[6]; 
	float size; 

	GLSkyBox();

	GLSkyBox(float pos_x, float pos_y, float pos_z, const char *texture_file[6], float size);

	void UpdatePosition(float pos_x, float pos_y, float pos_z);

	GLuint LoadTextureRAW( const char * filename );

	void DrawScence();
};

 