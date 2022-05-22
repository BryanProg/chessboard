/*
    Nome: Bryan Keven Rocha Brauna
    Matricula: 499427
*/

#pragma once 

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Object.hpp"

namespace CBL
{
    /**
     * @brief This is a class for the project camera.
     * 
     */
    struct camera
    {
        glm::vec3 pos_cam;
        glm::vec3 target;
        glm::vec3 cam_heiht;
        glm::mat4 view;

        public:

        camera()
        :   pos_cam  {},
            target   {},
            cam_heiht{}
        {
        }

        camera(const glm::vec3& pc, 
               const glm::vec3& tg, 
               const glm::vec3& ch)
        :   pos_cam  {pc},
            target   {tg},
            cam_heiht{ch}
        {
        }

        camera(const float pc_x, const float pc_y, const float pc_z,
               const float tg_x, const float tg_y, const float tg_z,
               const float ch_x, const float ch_y, const float ch_z)
        :   pos_cam  {pc_x, pc_y, pc_z},
            target   {tg_x, tg_y, tg_z},
            cam_heiht{ch_x, ch_y, ch_z}
        {
        }

        /**
         * @brief function responsible for update matrix
         * 
         */
        void update_matriz()
        {
            view = glm::lookAt(pos_cam, target, cam_heiht);
        }

        operator const GLfloat*()
        {
            return glm::value_ptr(view);
        }

        /**
         * @brief function responsible for rendering camero representation on 2d board
         * 
         */
        void render_cam() const
        {
            glPushMatrix();
            glColor3f(0.5f, 0.5f, 0.5f);

            float degres_v1 {}, 
                  degres_v2 {};
                  
            constexpr const uint8_t n_points = 40;

            glTranslatef(pos_cam[0], pos_cam[1], 0.f);
            glScalef(0.25f, 0.25f, 1.f);

            for(uint8_t count = {0}; count < n_points; ++count)
            {
                degres_v1 = ((360.0f/n_points) * count);
                degres_v2 = ((360.0f/n_points) * (count + 1));

                glBegin(GL_TRIANGLES);

                    glVertex2f(0.5f, 0.5f);

                    glVertex2f(cos(degres_v1 * M_PI/180.f) * 1, 
                                sin(degres_v1 * M_PI/180.f) * 1);

                    glVertex2f(cos(degres_v2 * M_PI/180.f) * 1, 
                                sin(degres_v2 * M_PI/180.f) * 1);
                glEnd();
            }

            glPopMatrix();
        }
    };

}