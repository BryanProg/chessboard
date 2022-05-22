/*
    Nome: Bryan Keven Rocha Brauna
    Matricula: 499427
*/

#pragma once

#include <iostream>
#include <memory>

#include "Object.hpp"

namespace CBL
{
    /**
     * @brief function responsible for creating a "CUBE" object
     * 
     */
    static inline std::unique_ptr<object> cube_obj()
    {
        static const std::vector<glm::vec3> cube =
        {
            // face superior triang #1
            {0.f, 0.f, 0.5f},
            {0.f, 1.f, 0.5f},
            {1.f, 1.f, 0.5f},

            // face superior triang #2
            {1.f, 1.f, 0.5f},
            {1.f, 0.f, 0.5f},
            {0.f, 0.f, 0.5f},

            // face inferior triang #1
            {0.f, 0.f, 0.f},
            {0.f, 1.f, 0.f},
            {1.f, 1.f, 0.f},

            // face inferior triang #2
            {1.f, 1.f, 0.f},
            {1.f, 0.f, 0.f},
            {0.f, 0.f, 0.f},

            // face frontal triang #1
            {0.f, 0.f, 0.f},
            {0.f, 0.f, 0.5f},
            {1.f, 0.f, 0.5f},

            // face frontal triang #2
            {1.f, 0.f, 0.5f},
            {1.f, 0.f, 0.f},
            {0.f, 0.f, 0.f},

            // face posterior triang #1
            {0.f, 1.f, 0.f},
            {0.f, 1.f, 0.5f},
            {1.f, 1.f, 0.5f},

            // face posterior triang #2
            {1.f, 1.f, 0.5f},
            {1.f, 1.f, 0.f},
            {0.f, 1.f, 0.f},

            // face direita triang #1
            {1.f, 0.f, 0.f},
            {1.f, 0.f, 0.5f},
            {1.f, 1.f, 0.5f},

            // face direita triang #2
            {1.f, 1.f, 0.5f},
            {1.f, 1.f, 0.f},
            {1.f, 0.f, 0.f},

            // face esquerda triang #1
            {0.f, 0.f, 0.f},
            {0.f, 0.f, 0.5f},
            {0.f, 1.f, 0.5f},

            // face esquerda triang #2
            {0.f, 1.f, 0.5f},
            {0.f, 1.f, 0.f},
            {0.f, 0.f, 0.f}
        };

        static const std::vector<glm::vec3> color_cube = cube;

        return std::make_unique<object>(cube, color_cube, overboard::flag_draw::cube);
    }

    /**
     * @brief function responsible for creating a "PIRAMIDE" object
     * 
     */
    static inline std::unique_ptr<object> piramide_obj()
    {
        static const std::vector<glm::vec3> piramide =
        {
            // face inferior triang #1
            {0.f, 0.f, 0.f},
            {0.f, 1.f, 0.f},
            {1.f, 1.f, 0.f},

            // face inferior triang #2
            {1.f, 1.f, 0.f},
            {1.f, 0.f, 0.f},
            {0.f, 0.f, 0.f},

            // face esquerda triang
            {0.f, 0.f, 0.f},
            {0.5f, 0.5f, 0.5f},
            {0.f, 1.f, 0.f},

            // face direita triang
            {1.f, 0.f, 0.f},
            {0.5f, 0.5f, 0.5f},
            {1.f, 1.f, 0.f},

            // face frontal triang
            {0.f, 0.f, 0.f},
            {0.5f, 0.5f, 0.5f},
            {1.f, 0.f, 0.f},

            // face posterior triang
            {1.f, 1.f, 0.f},
            {0.5f, 0.5f, 0.5f},
            {0.f, 1.f, 0.f}

        };

        std::vector<glm::vec3> color_pira(piramide.size(), {1.f, 0.f, 0.f});

        auto pira = std::make_unique<object>(piramide, color_pira, overboard::flag_draw::piramide);
        pira->set_color_2D(1.f, 0.f, 0.f);

        return std::move(pira);
    }

    /**
     * @brief function to create the bottom of the cylinder
     * 
     */
    inline static void load_lower_surface(std::vector<glm::vec3>& vetor, uint8_t n_edges)
    {
        float degres_v1 {}, 
              degres_v2 {};

        for(uint8_t count = {0}; count < n_edges; ++count)
        {
            degres_v1 = ((360.0f/n_edges) * count);
            degres_v2 = ((360.0f/n_edges) * (count + 1));

            vetor.push_back(glm::vec3{0.5f, 0.5f, 0.f});

            vetor.push_back(
                glm::vec3
                {
                    (cos(degres_v1 * M_PI/180.f) * 0.25f) + 0.5f, 
                    (sin(degres_v1 * M_PI/180.f) * 0.25f) + 0.5f, 
                    0.f
                });

            vetor.push_back(
                glm::vec3
                {
                    (cos(degres_v2 * M_PI/180.f) * 0.25f) + 0.5f, 
                    (sin(degres_v2 * M_PI/180.f) * 0.25f) + 0.5f,
                    0.f
                });
        }
    }

    /**
     * @brief function to create the top of the cylinder
     * 
     */
    inline static void load_upper_surface(std::vector<glm::vec3>& vetor, uint8_t n_edges)
    {
        float degres_v1 {}, degres_v2 {};

        for(uint8_t count = {0}; count < n_edges; ++count)
        {
            degres_v1 = ((360.0f/n_edges) * count);
            degres_v2 = ((360.0f/n_edges) * (count + 1));

            vetor.push_back(glm::vec3{0.5f, 0.5f, 1.f});

            vetor.push_back(
                glm::vec3
                {
                    (cos(degres_v1 * M_PI/180.f) * 0.25f) + 0.5f, 
                    (sin(degres_v1 * M_PI/180.f) * 0.25f) + 0.5f, 
                    1.f
                });

            vetor.push_back(
                glm::vec3
                {
                    (cos(degres_v2 * M_PI/180.f) * 0.25f) + 0.5f, 
                    (sin(degres_v2 * M_PI/180.f) * 0.25f) + 0.5f,
                    1.f
                });
        }
    }

    /**
     * @brief function to create the body of the cylinder
     * 
     */
    inline static void load_body_surface(std::vector<glm::vec3>& vetor, uint8_t n_edges)
    {
        float degres_v1 {}, degres_v2 {};

        for(uint8_t count = {0}; count < n_edges; ++count)
        {
            degres_v1 = ((360.0f/n_edges) * count);
            degres_v2 = ((360.0f/n_edges) * (count + 1));

            vetor.push_back(
                glm::vec3
                {
                    (cos(degres_v1 * M_PI/180.f) * 0.25f) + 0.5f, 
                    (sin(degres_v1 * M_PI/180.f) * 0.25f) + 0.5f, 
                    0.f
                });
            
            vetor.push_back(
                glm::vec3
                {
                    (cos(degres_v1 * M_PI/180.f) * 0.25f) + 0.5f, 
                    (sin(degres_v1 * M_PI/180.f) * 0.25f) + 0.5f, 
                    1.f
                });

            vetor.push_back(
                glm::vec3
                {
                    (cos(degres_v2 * M_PI/180.f) * 0.25f) + 0.5f, 
                    (sin(degres_v2 * M_PI/180.f) * 0.25f) + 0.5f,
                    1.f
                });

            vetor.push_back(
                glm::vec3
                {
                    (cos(degres_v2 * M_PI/180.f) * 0.25f) + 0.5f, 
                    (sin(degres_v2 * M_PI/180.f) * 0.25f) + 0.5f,
                    1.f
                });
            
            vetor.push_back(
                glm::vec3
                {
                    (cos(degres_v2 * M_PI/180.f) * 0.25f) + 0.5f, 
                    (sin(degres_v2 * M_PI/180.f) * 0.25f) + 0.5f,
                    0.f
                });
            
            vetor.push_back(
                glm::vec3
                {
                    (cos(degres_v1 * M_PI/180.f) * 0.25f) + 0.5f, 
                    (sin(degres_v1 * M_PI/180.f) * 0.25f) + 0.5f, 
                    0.f
                });
        }
    }

    /**
     * @brief function responsible for creating a "CYLINDER" object
     * 
     */
    static inline std::unique_ptr<object> cylinder()
    {
        float degres_v1 {}, degres_v2 {};
        constexpr const uint8_t n_points = 40;

        std::vector<glm::vec3> v_cylinder;

        load_lower_surface(v_cylinder, n_points);
        load_upper_surface(v_cylinder, n_points);
        load_body_surface(v_cylinder, n_points);

        auto obj_c = std::make_unique<object>(v_cylinder, v_cylinder, overboard::flag_draw::cylinder);
        obj_c->set_color_2D(0.f, 1.f, 1.f);

        return std::move(obj_c);
    }

    /**
     * @brief function responsible for creating a "PRISM" object
     * 
     */
    static inline std::unique_ptr<object> prism()
    {
        float degres_v1 {}, degres_v2 {};
        constexpr const uint8_t n_points = 5;

        std::vector<glm::vec3> v_prism;
        std::vector<glm::vec3> c_prism;

        load_lower_surface(v_prism, n_points);
        load_upper_surface(v_prism, n_points);
        load_body_surface(v_prism, n_points);

        for(int32_t idx = v_prism.size() - 1; idx >= 0; --idx)
            c_prism.push_back(v_prism[idx]);

        auto obj_p = std::make_unique<object>(v_prism, c_prism, overboard::flag_draw::prism);
        obj_p->set_color_2D(0.f, 0.f, 1.f);

        return std::move(obj_p);
    }
}