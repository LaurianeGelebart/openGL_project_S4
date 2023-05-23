#pragma once

#include "p6/p6.h"

struct ShadowMapProgram
{
    p6::Shader _Program;

    // GLint      uMVPMatrix;
    // GLint      uMVMatrix;
    // GLint      uNormalMatrix;

    // GLint uTexture;

    // GLint uKd;
    // GLint uKs;
    // GLint uShininess;

    // GLint uLightPos_vs;
    // GLint uLightDir_vs;
    // GLint uLightCharacter_vs;
    // GLint uLightIntensity;

    GLint uLightSpaceMatrix;
    GLint uModel;

    ShadowMapProgram() : _Program(p6::load_shader("./shaders/shadowMap.vs.glsl", "./shaders/shadowMap.fs.glsl"))
    {
        // uMVPMatrix    = glGetUniformLocation(_Program.id(), "uMVPMatrix");
        // uMVMatrix     = glGetUniformLocation(_Program.id(), "uMVMatrix");
        // uNormalMatrix = glGetUniformLocation(_Program.id(), "uNormalMatrix");
        
        // uTexture = glGetUniformLocation(_Program.id(), "uTexture");

        // uKd        = glGetUniformLocation(_Program.id(), "uKd");
        // uKs        = glGetUniformLocation(_Program.id(), "uKs");
        // uShininess = glGetUniformLocation(_Program.id(), "uShininess");

        // uLightPos_vs    = glGetUniformLocation(_Program.id(), "uLightPos_vs");
        // uLightDir_vs    = glGetUniformLocation(_Program.id(), "uLightDir_vs");
        // uLightCharacter_vs    = glGetUniformLocation(_Program.id(), "uLightCharacter_vs");
        // uLightIntensity = glGetUniformLocation(_Program.id(), "uLightIntensity");
    
        uLightSpaceMatrix = glGetUniformLocation(_Program.id(), "uLightSpaceMatrix");
        uModel = glGetUniformLocation(_Program.id(), "uModel");
    
    }
};