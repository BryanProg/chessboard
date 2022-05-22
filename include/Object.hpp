/*
    Nome: Bryan Keven Rocha Brauna
    Matricula: 499427
*/

#pragma once

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <vector>
#include <cstdint>

#include "Overboard.hpp"

namespace CBL
{
    /**
     * @brief This class represents 3D and 2D world objects
     * 
     */
    class object
    {
        public:
            using vertices     = std::vector<glm::vec3>;
            using vertx_colors = std::vector<glm::vec3>;

        public:
            object () = default;

            object (const object&) = default;
            object (object&&)      = default;

            object& operator= (const object&) = default;
            object& operator= (object&&)      = default;

            object ( const vertices& obj_v, const vertx_colors& obj_c)
            :   vertxs     { obj_v },
                color      { obj_c },
                init_x     {       },
                init_y     {       },
                flag       {       },
                color_2D   {0.2, 0.7f, 0.433f},
                v_translat {       }
            {
            }

            object ( const vertices& obj_v, 
                     const vertx_colors& obj_c, 
                     overboard::flag_draw f
                   )
            :   vertxs     { obj_v },
                color      { obj_c },
                init_x     {       },
                init_y     {       },
                flag       {   f   },
                color_2D   {0.2, 0.7f, 0.433f},
                v_translat {       }
            {
            }

            object ( const vertices& obj_v, const vertx_colors& obj_c, float x, float y)
            :   vertxs     { obj_v },
                color      { obj_c },
                init_x     {   x   },
                init_y     {   y   },
                flag       {       },
                color_2D   {0.2, 0.7f, 0.433f},
                v_translat { x, y, 0.f}
            {
            }

            object ( const vertices& obj_v, 
                     const vertx_colors& obj_c, 
                     float x, float y, 
                     overboard::flag_draw f
                   )
            :   vertxs     { obj_v },
                color      { obj_c },
                init_x     {   x   },
                init_y     {   y   },
                flag       {   f   },
                color_2D   {0.2, 0.7f, 0.433f},
                v_translat { x, y, 0.f}
            {
            }

        public:
            inline void set_color(float, float, float);
            inline void set_color_2D(float, float, float);
            inline void set_vertices(const vertices&);
            inline void translate(const glm::vec3&);
            inline void translate(float, float, float);
            inline void set_pos_init(float, float);

            void draw_obj();
            void draw_circle();

        private:
            vertices     vertxs;
            vertx_colors color;

            float        init_x, 
                         init_y;

            overboard::flag_draw flag;

            glm::vec3    color_2D;
            glm::vec3    v_translat;
    };

    inline void object::set_color_2D(float r, float g, float b)
    {
        color_2D = {r, g, b};
    }

    inline void object::set_color(float r, float g, float b)
    {
        for(auto& element : color)
        {
            element[0] = r;
            element[1] = g;
            element[2] = b;
        }
    }
    
    inline void object::set_vertices(const object::vertices& obj)
    {
        vertxs = obj;
    }

    inline void object::translate(const glm::vec3& vetor_t)
    {
        v_translat += vetor_t;
    }

    inline void object::translate(float x, float y, float z)
    {
        v_translat += glm::vec3{x, y, z};
    }

    inline void object::set_pos_init(float x, float y)
    {
        init_x = x;
        init_y = y;
        v_translat = glm::vec3(x, y, 0.f);
    }
}