/* Using the standard output for fprintf */
#include <stdio.h>
#include <stdlib.h>

#include <iostream>

/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>

/* Using the GLUT library for the base windowing setup */
#include <GL/freeglut.h>
#include "shader_utils.h"

/* GLM stuff for matrix transformations */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* Math */
#define _USE_MATH_DEFINES
#include <math.h>

GLint uniform_m_transform;
GLuint program;
GLint uniform_fade;
GLuint vbo_triangle, vbo_triangle_colors;
GLint attribute_coord2d, attribute_v_color, attribute_coord3d;

struct attributes {
    GLfloat coord3d[3];
    GLfloat v_color[3];
};

int init_resources(void)
{
    GLint link_ok;
    
    struct attributes triangle_attributes[] = {
        {{ 0.0,  0.8, 0.0}, {1.0, 1.0, 0.0}},
        {{-0.8, -0.8, 0.0}, {0.0, 0.0, 1.0}},
        {{ 0.8, -0.8, 0.0}, {1.0, 0.0, 0.0}}
    };
    
  glGenBuffers(1, &vbo_triangle);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_attributes), triangle_attributes,
               GL_STATIC_DRAW);
  
  GLuint vs, fs;
  
  if ((vs = create_shader("triangle.v.glsl", GL_VERTEX_SHADER))   == 0) return 0;
  if ((fs = create_shader("triangle.f.glsl", GL_FRAGMENT_SHADER)) == 0) return 0;
  
  program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
  if (!link_ok) {
    fprintf(stderr, "glLinkProgram:");
    return 0;
  }

  const char* uniform_name;
  uniform_name = "fade";
  uniform_fade = glGetUniformLocation(program, uniform_name);
  if (uniform_fade == -1) {
      fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
      return 0;
  }
  
  const char* attribute_name = "v_color";
  attribute_v_color = glGetAttribLocation(program, attribute_name);
  if (attribute_v_color == -1) {
      fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
      return 0;
  }

  attribute_name = "coord3d";
  attribute_coord3d = glGetAttribLocation(program, attribute_name);
  if (attribute_coord3d == -1) {
      fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
      return 0;
  }

  // pass transform matrix
  uniform_name = "m_transform";
  uniform_m_transform = glGetUniformLocation(program, uniform_name);
  if (uniform_m_transform == -1) {
      fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
      return 0;
  }

  return 1;
}
 
void onDisplay()
{
    // Enable alpha
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Clear the background as white */
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
 
    glUseProgram(program);
    glEnableVertexAttribArray(attribute_coord2d);
    glEnableVertexAttribArray(attribute_v_color);
    
    // Setup buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo_triangle);
    
    /* Describe our vertices array to OpenGL (it can't guess its format 
     * automatically) 
     *
     */
    glVertexAttribPointer(
            attribute_coord3d,      // attribute
            3,                      // number of elements per vertex, here (r,g,b)
            GL_FLOAT,               // the type of each element
            GL_FALSE,               // take our values as-is
            sizeof(struct attributes),    // no extra data between each position
            0                       // offset of first element
    );
    
    /* Describe our vertices array to OpenGL (it can't guess its format 
     * automatically) 
     */
    glVertexAttribPointer(
            attribute_v_color,      // attribute
            3,                      // number of elements per vertex, here (r,g,b)
            GL_FLOAT,               // the type of each element
            GL_FALSE,               // take our values as-is
            5 * sizeof(GLfloat),    // no extra data between each position
            (GLvoid*) (2 * sizeof(GLfloat))  // offset of first element
    );
 
    /* Push each element in buffer_vertices to the vertex shader */
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(attribute_v_color);
    glDisableVertexAttribArray(attribute_coord2d);
 
    /* Display the result */
    glutSwapBuffers();
}

void onIdle()
{
    float tau = 2 * M_PI;
    float elapsedSeconds = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    
    // Rotation with translation.
    // -1 <->+1 every 5 seconds
    float move = sinf(elapsedSeconds * tau / 5);

    // Rotation
    float angle = elapsedSeconds * 45;

    glm::vec3 axis_z(0, 0, 1);

    // Defining translate and rotate matrices for convenience.
    glm::mat4 translate = glm::translate(glm::mat4(1.0f),
                                         glm::vec3(move, 0.0, 0.0));
    glm::mat4 rotate    = glm::rotate(glm::mat4(1.0f), angle, axis_z);

    // Creating transform matrix.
    glm::mat4 m_transform = translate * rotate;

    // Fade in and out
    float cur_fade = sinf(elapsedSeconds * tau / 5) / 
        2 + 1; // 0->1->0 every 5 seconds
    glUseProgram(program);
    glUniform1f(uniform_fade, cur_fade);
    
    glUniformMatrix4fv(uniform_m_transform, 1, GL_FALSE, 
            glm::value_ptr(m_transform));
    
    // Redisplay?
    glutPostRedisplay();
}
 
void free_resources()
{
    glDeleteProgram(program);
    glDeleteBuffers(1, &vbo_triangle);
}

void reshape (int w, int h) 
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void keyboard(unsigned char key, int x, int y)
{
    std::cout << "Keycode is: " << key << std::endl;
    glm::mat4 translate; 
    switch (key)
    {
        case 27:
            glutLeaveMainLoop();
            return;
        case 'w':
            std::cout << "asdf" << std::endl;
            std::cout << "Up!" << std::endl;
            translate = glm::translate(glm::mat4(1.0f),
                                         glm::vec3(0.0, 1.0, 0.0));
            glUseProgram(program);
            glUniformMatrix4fv(uniform_m_transform, 1, GL_FALSE, 
            glm::value_ptr(translate));
            // Redisplay?
            //glutPostRedisplay();
            return;
    }
}

int main(int argc, char* argv[])
{
  /* Glut-related initialising functions */
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_ALPHA|GLUT_DOUBLE|GLUT_DEPTH);
  glutInitWindowSize(640, 480);
  glutCreateWindow("OpenGL Test");
 
  /* Extension wrangler initialising */
  GLenum glew_status = glewInit();
  if (glew_status != GLEW_OK)
  {
    fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
    return EXIT_FAILURE;
  }
 
  /* When all init functions run without errors,
  the program can initialise the resources */
  if (1 == init_resources())
  {
    /* We can display it if everything goes OK */
    glutDisplayFunc(onDisplay);
    glutIdleFunc(onIdle);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
  }
 
  /* If the program exits in the usual way,
  free resources and exit with a success */
  free_resources();
  return EXIT_SUCCESS;
}
