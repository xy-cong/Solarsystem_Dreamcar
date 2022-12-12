#include "PlanetTexture.hpp"
#include <Magick++.h> 


#include <iostream>
#include <vector>
using namespace std;


PlanetTexture::PlanetTexture()
{
	texture = 0;
} 

PlanetTexture::PlanetTexture(const char * filename, GLuint texture)
{
	this->texture = texture;

	Magick::Blob m_blob;

	unsigned int width, height;
	Magick::InitializeMagick(nullptr);
	Magick::Image *image;
	try {
		image = new Magick::Image(filename);
		image->write(&m_blob, "RGBA");
	}
		catch (Magick::Error& Error) {
		std::cout << "Error loading texture '" <<filename << "': " << Error.what() << std::endl;
	}

	glEnable(GL_TEXTURE_2D);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glBindTexture(GL_TEXTURE_2D, texture);
	

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// gluBuild2DMipmaps(GL_TEXTURE_2D, 4, width, height, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
	glActiveTexture(GL_TEXTURE0);  
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->columns(),image->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
	glDisable(GL_TEXTURE_2D);
}

void PlanetTexture::GLBindTexture()
{
	glBindTexture(GL_TEXTURE_2D, texture);
}
