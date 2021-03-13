/*
 * Copyright (c) 2021 F. Lotfi & D. Kane All rights reserved.
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file.
 */

#ifndef __SHADER_H__
#define __SHADER_H__

#include <assert.h>
#include <glad/glad.h>
#include <string>

/* Loads and OpenGL vertex and fragment shader from a file
 * to create an OpenGL shader program.
 */
class Shader {
public:
  /**
   * Create a new shader object without loading any shaders. This
   * is a blank object and no program will be created until loadShaders()
   * has been called. Then bind() and unbind() will do something.
   */
  Shader(void);

  /**
   * Initialize a shader by loading a vertex and fragment shader. This
   * will create an OpenGL program object as long as the two shaders
   * provided are valid. loadShaders() does not need to be called after
   * using this constructor.
   *
   * @param vertexShaderPath The path to the vertex shader.
   *
   * @param fragmentShaderPath The path to the fragment shader.
   *
   * @throws A runtime_exception if one of the shaders was invalid.
   */
  Shader(const std::string &vertexShaderPath,
         const std::string &fragmentShaderPath);

  /**
   * Cleans up any allocated OpenGL objects.
   */
  ~Shader(void);

public:
  /**
   * Bind the shader program. Calls glUseProgram().
   */
  inline void begin(void) const {
    assert(program != 0);
    glUseProgram(program);
  }

  /**
   * Unbind the shader program. Call glUseProgram(0).
   */
  inline void end(void) const { glUseProgram(0); }

  /**
   * Loads a vertex and a fragment shader from a file. If there are already
   * shaders loaded it will delete those shaders and allocate new ones. This
   * method should be called after using the default constructor, because no
   * shaders are loaded with the default constructor.
   *
   * @param vertexShaderPath The path to the vertex shader source file.
   *
   * @param fragmentShaderPath The path to the fragment shader source file.
   *
   * @throws A runtime_exception if there was a problem loading any of the
   * shaders.
   */
  void loadShaders(const std::string &vertexShaderPath,
                   const std::string &fragmentShaderPath);

  /**
   * Get the OpenGL program identifier.
   *
   * @return The OpenGL program identifier. Do not delete
   *         this program, the class will handle that.
   */
  GLuint getProgram() const { return program; }

  /**
   * Get the location of an attribute by name.
   *
   * @return The attribute's index, or -1 if the attribute
   *         could not be found.
   */
  GLint getAttribLocation(const std::string &name) const;

  /**
   * Get the location of a uniform by name.
   *
   * @return The uniform's index, or -1 if the uniform
   *         could not be found.
   */
  GLint getUniformLocation(const std::string &name) const;

private:
  /**
   * A helper method that creates a new OpenGL shader object,
   * binds the source, and compiles the shader.
   *
   * @param shaderType Either GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
   *
   * @param source A pointer to the shaders source.
   *
   * @throws An exception if there was a problem loading the shader.
   *
   * @return The created shader object's OpenGL identifier.
   */
  GLuint createShader(int shaderType, const char *source);

  /**
   * A helper method to create a program from the two OpenGL shader
   * objects. Checks for linking errors and throws an exception with
   * the log output if there's a problem.
   *
   * @param vShader The vertex shader's identifier.
   *
   * @param fShader The fragment shader's identifier.
   *
   * @return The OpenGL program identifier.
   */
  GLuint createProgram(int vShader, int fShader);

private:
  GLuint program;
};

#endif // __SHADER_H__
