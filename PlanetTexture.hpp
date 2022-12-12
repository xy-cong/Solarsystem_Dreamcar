#include <GL/glut.h>

class PlanetTexture
{
public:
	GLuint texture; 


	PlanetTexture();

	PlanetTexture(const char * filename, GLuint texture);

	void GLBindTexture();
};

