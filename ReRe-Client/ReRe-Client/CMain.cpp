//
//  main.cpp
//  ReRe-Client
//
//  Created by Thomas Kipshagen on 23.04.13.
//  Copyright (c) 2013 Thomas Kipshagen. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "CPreRendering.h"

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>

void drawWarpedImg(void)
{
    // TODO: Warping
}

void MainLoop(void)
{
    CPreRendering* renderer = new CPreRendering();

    int i = 0;
    
    do{
        // Update Camera Matrix
        renderer->getSceneGraph()->returnCameraNode()->updateCameraView();
        
        // Test Movement
        i++;
        //renderer->getSceneGraph()->returnCameraNode()->automaticMovement(i);
        
        //renderer->writeToFBO();
        renderer->testDraw();
        
        drawWarpedImg();
        
        // Swap buffers
        glfwSwapBuffers();
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
          glfwGetWindowParam( GLFW_OPENED ) );
    
    delete renderer;
}


int main(int argc, const char * argv[])
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }
        
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4); // 4x antialiasing
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3); // OpenGL 3.2
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL
        
    // Open a window and create its OpenGL context
    if( !glfwOpenWindow( WIDTH, HEIGHT, 0,0,0,0, 32,0, GLFW_WINDOW ) )
    {
        fprintf( stderr, "Failed to open GLFW window\n" );
        glfwTerminate();
        return -1;
    }
        
    // Initialize GLEW
    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
        
    glfwSetWindowTitle( "Hello World!" );
    
    // Ensure we can capture the escape key being pressed below
    glfwEnable( GLFW_STICKY_KEYS );
    
    glEnable(GL_DEPTH_TEST);
    
    // Initialize Mouse Position
    glfwDisable( GLFW_MOUSE_CURSOR);
    glfwSetMousePos(WIDTH/2, HEIGHT/2);
    
    try
    {
        MainLoop();
    }
    catch (int i_ex)
    {
        cout << "Fehlercode: " << i_ex << endl;
        if (i_ex == 0x00)
            cout << "Keine .dae-Datei" << endl;
        else if (i_ex == 0x01)
            cout << "Fehler beim Laden der Datei" << endl;
    }
    
    // Close window and terminate GLFW
    glfwTerminate();
    
    std::cout << "Hello, World!\n";
    return 0;
}

