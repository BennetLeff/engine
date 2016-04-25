LIB_I = -I/usr/local/include
LIB_L = -L/usr/local/lib
GL 	  = -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
flags = -lglfw3 -std=c++11

all:	
	g++ -c window.cpp shader.cpp mesh.cpp texture.cpp transform.cpp camera.cpp	${LIB_I}
	g++ main.cpp window.o shader.o mesh.o texture.o	transform.o	camera.o		${LIB_I} ${LIB_L} ${flags} ${GL} -o game -g