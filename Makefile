LIB_I = -I/usr/local/include
LIB_L = -L/usr/local/lib
GL 	  = -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
flags = -lglfw3 -std=c++11 -o game -g
assimp = /usr/local/lib/libassimp.3.2.0.dylib

all:	
	g++ -c window.cpp shader.cpp mesh.cpp \
			texture.cpp transform.cpp camera.cpp Model.cpp	${LIB_I} -std=c++11
	g++ main.cpp window.o shader.o mesh.o texture.o \
			transform.o	camera.o Model.o ${LIB_I} ${LIB_L} ${flags} ${GL} ${assimp}