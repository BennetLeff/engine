LIB_I = -I/usr/local/include
LIB_L = -L/usr/local/lib
GL 	  = -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
flags = -lglfw3 -std=c++11 -o game -g
assimp = /usr/local/lib/libassimp.3.2.0.dylib

all:	
	g++ -c Window.cpp Shader.cpp Mesh.cpp \
			Texture.cpp Transform.cpp Camera.cpp Model.cpp	${LIB_I} -std=c++11
	g++ main.cpp Window.o Shader.o Mesh.o Texture.o \
			Transform.o	Camera.o Model.o ${LIB_I} ${LIB_L} ${flags} ${GL} ${assimp}