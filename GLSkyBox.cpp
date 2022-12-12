#include "GLSkyBox.hpp"
#include <vector>
#include <iostream>


GLSkyBox::GLSkyBox()
{
	POS_X = 0;
	POS_Y = 0;
	POS_Z = 0;
	for (int i = 0; i < 6; i++)
	{
		texture_id[i] = 0;
	}
	size = 0;
}

GLSkyBox::GLSkyBox(float pos_x, float pos_y, float pos_z, const char *texture_file[6], float size)
{
	POS_X = pos_x;
	POS_Y = pos_y;
	POS_Z = pos_z;

	this->size = size;

	glEnable(GL_TEXTURE_2D);
	for (int i = 0; i < 6; i++)
	{
		this->texture_id[i] = this->LoadTextureRAW(texture_file[i]);
	}
}

GLuint GLSkyBox::LoadTextureRAW( const char * filename )
{
	GLuint texture;
	int width, height;
	unsigned char * data;
	FILE * file;
	file = fopen( filename, "rb" );
	if ( file == NULL ) return 0;
	width = 2048;
	height = 2048;
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

	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data ); 
	free( data );
	
	return texture;
}

void GLSkyBox::UpdatePosition(float pos_x, float pos_y, float pos_z)
{
	POS_X = pos_x;
	POS_Y = pos_y;
	POS_Z = pos_z;
}

void GLSkyBox::DrawScence()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, this->texture_id[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size, size, -size);
	glTexCoord2f(1, 0); glVertex3f(size, size, -size);
	glTexCoord2f(1, 1); glVertex3f(size, -size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, -size, -size);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, this->texture_id[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(size, size, size);
	glTexCoord2f(1, 0); glVertex3f(-size, size, size);
	glTexCoord2f(1, 1); glVertex3f(-size, -size, size);
	glTexCoord2f(0, 1); glVertex3f(size, -size, size);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, this->texture_id[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(size, size, -size);
	glTexCoord2f(1, 0); glVertex3f(size, size, size);
	glTexCoord2f(1, 1); glVertex3f(size, -size, size);
	glTexCoord2f(0, 1); glVertex3f(size, -size, -size);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, this->texture_id[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size, size, size);
	glTexCoord2f(1, 0); glVertex3f(-size, size, -size);
	glTexCoord2f(1, 1); glVertex3f(-size, -size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, -size, size);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, this->texture_id[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size, size, size);
	glTexCoord2f(1, 0); glVertex3f(size, size, size);
	glTexCoord2f(1, 1); glVertex3f(size, size, -size);
	glTexCoord2f(0, 1); glVertex3f(-size, size, -size);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, this->texture_id[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-size, -size, -size);
	glTexCoord2f(1, 0); glVertex3f(size, -size, -size);
	glTexCoord2f(1, 1); glVertex3f(size, -size, size);
	glTexCoord2f(0, 1); glVertex3f(-size, -size, size);
	glEnd();
}



// ---------------------------------------------------------------------------------- //