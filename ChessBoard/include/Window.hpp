/*
    Nome: Bryan Keven Rocha Brauna
    Matricula: 499427
*/

#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

namespace CBL
{
    /**
     * @brief Wrap class to send the window
     * 
     */
    class window
    {
        protected:
            GLFWwindow* handle;
        
        public:
            virtual ~window() {}
            operator GLFWwindow*() const { return handle;}
            operator GLFWwindow*() { return handle;}
    };
}

