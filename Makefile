#
#  Makefile
#
#  Created by Changkun Ou on 16/06/07.
#  Copyright © 2016 Shiyanlou.com. All rights reserved.
#

CXX = g++
EXEC = solarsystem_DreamCar
SOURCES = GLmain.cpp GLstars.cpp GLsolarsystem.cpp GLcamera.cpp ObjLoader.cpp GLSkyBox.cpp
OBJECTS = GLmain.o GLstars.o GLsolarsystem.o GLcamera.o ObjLoader.o GLSkyBox.o
LDFLAGS = -lglut -lGL -lGLU -lMagick++ -std=c++11

all :
	$(CXX) $(SOURCES) $(LDFLAGS) -o $(EXEC)

clean:
	rm -f $(EXEC) *.gdb *.o
 