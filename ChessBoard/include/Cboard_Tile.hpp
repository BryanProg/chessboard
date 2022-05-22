/*
    Nome: Bryan Keven Rocha Brauna
    Matricula: 499427
*/

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <cstdint>
#include <array>
#include <memory>

#include "Object.hpp"

namespace CBL
{
    /**
     * @brief Class representing each block on the board
     * 
     */
    struct cboard_tile
    {
        using vertex = glm::vec2;
        using colors = glm::vec3;

        bool                    state_object;
        int32_t                 pos_w, pos_h;
        colors                  color;
        vertex                  points;
        std::unique_ptr<object> obj;

        cboard_tile();
        cboard_tile(const vertex&, int32_t, int32_t, const colors&);
        inline void object_on();
        inline void object_off();
        std::unique_ptr<object> drop_obj();
        void load_obj(const object::vertices&, const object::vertx_colors&);
        void load_obj(std::unique_ptr<object>);
        void set_obj(std::unique_ptr<object>);

    };

    void cboard_tile::object_on()  { state_object = true;  }
    void cboard_tile::object_off() { state_object = false; }
}