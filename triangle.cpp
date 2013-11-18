#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>
#include <algorithm>
#include <string>

#include <exception>
#include <stdexcept>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "triangle.h"

/***********************************************************************
This file contains all of the functions you need to implement, as well as
 when/why they are called. You can copy this file and simply implement
these function.
***********************************************************************/

// Global variables.
GLuint theProgram;
GLint attribute_coord2d;

//Called before FreeGLUT is initialized. It should return the FreeGLUT
//display mode flags that you want to use. The initial value are the standard ones
//used by the framework. You can modify it or just return you own set.
//This function can also set the width/height of the window. The initial
//value of these variables is the default, but you can change it.
unsigned int defaults(unsigned int displayMode, int &width, int &height) {
    return displayMode;
}

// This function creates all GLSL related stuff.
// Returns 1 when all is ok, 0 with a displayed error.
int init_resources(void)
{
    GLint compile_ok, link_ok = GL_FALSE;

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    const char *vs_source = 
        "#version 120\n"
        "attribute vec2 coord2d;\n"
        "void main(void) {\n"
        "   gl_Position = vec4(coord2d, 0.0, 1.0);\n"
        "}";

    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);

    if (0 == compile_ok) {
        fprintf(stderr, "Error in vertex shader\n");
        return 0;
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fs_source = 
        "#version 120\n"
        "void main(void) {\n"
        "   gl_FragColor[0] = gl_FragCoord.x/640.0;\n"
        "   gl_FragColor[1] = gl_FragCoord.y/480.0;\n"
        "   gl_FragColor[2] = 0.5;\n"
        "}\n";

    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);

    if (0 == compile_ok) {
        fprintf(stderr, "Error in fragment shader\n");
        return 0;
    }

    theProgram = glCreateProgram();
    glAttachShader(theProgram, vs);
    glAttachShader(theProgram, fs);
    glLinkProgram(theProgram);
    glGetProgramiv(theProgram, GL_LINK_STATUS, &link_ok);
    if (!link_ok) {
        fprintf(stderr, "glLinkProgram:");
        return 0;
    }

    const char* attribute_name = "coord2d";
    attribute_coord2d = glGetAttribLocation(theProgram, attribute_name);
    if (attribute_coord2d == -1) { 
        fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
        return 0;
    }

    return 1;
}

void onDisplay()
{
    /* Clear the background as white */
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(theProgram);
    glEnableVertexAttribArray(attribute_coord2d);
    GLfloat triangle_vertices[] = {
         0.0,   0.0,
         1.0,  1.0,
         -1.0,  -1.0
    };

    /* Describe our vertices array to OpenGL, as it can't guess the format 
     * automatically */
    glVertexAttribPointer(
            attribute_coord2d, // Attribute.
            2,                 // Number of elements per vertex, here (x,y).
            GL_FLOAT,          // The type of each element.
            GL_FALSE,          // Take our values as-is.
            0,                 // No extra data between each position.
            triangle_vertices  // Pointer to the C array.
    );

    /* Push each element in buffer_vertices to the vertex shader */
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(attribute_coord2d);

    /* Display the result */
    glutSwapBuffers();
}

void free_resources()
{
    glDeleteProgram(theProgram);
}

int main(int argc, char* argv[]) {

    
    std::cout << "Hello, world!" << std::endl;
    
    // Variables
    unsigned int displayMode = GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH | GLUT_STENCIL;
    
    // Glut initialization stuff.
    glutInit(&argc, argv);
    glutInitDisplayMode(displayMode);
    glutInitContextVersion(3, 1);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow("test");

    // Extension wrangler initializing
    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
        return EXIT_FAILURE;
    }

    if (1 == init_resources()) {
        // If everything is okay we can display.
        glutDisplayFunc(onDisplay);
        glutMainLoop();
    }

    /*
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    */

    /* Free resources and exit with success if everything is fine */
    free_resources();

    return EXIT_SUCCESS;
}


