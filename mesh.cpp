#include "mesh.h"

// Currently defaults to drawing a triangle
Mesh::Mesh(GLuint shaderProg)
{
    shaderProgram = shaderProg;

    // generate vertex array object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    // generate 1 vertex buffer
    glGenBuffers(1, &vbo); 

    float vertices[] = {
        0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
    };
    
    // Bind the buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // pass in to BufferData
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // get position attribute in shader
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    // glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    //glEnableVertexAttribArray(posAttrib);
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,
                          5*sizeof(float), 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
                          5*sizeof(float), (void*)(2*sizeof(float)));
}

void Mesh::draw()
{
    glDrawArrays(GL_TRIANGLES, 0, 3);
}