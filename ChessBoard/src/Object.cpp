/*
    Nome: Bryan Keven Rocha Brauna
    Matricula: 499427
*/

#include "../include/Object.hpp"

namespace CBL
{

    /**
     * @brief function responsible for drawing the 3D object
     *  
     */
    void object::draw_obj()
    {

        const auto sz_v = vertxs.size();

        glPushMatrix();
        glTranslatef(v_translat[0], v_translat[1], v_translat[2]);

        glBegin(GL_TRIANGLES);

            for(size_t idx{}; idx < sz_v; ++idx)
            {
                glColor3f(color[idx][0], color[idx][1], color[idx][2]);
                glVertex3f(vertxs[idx][0], vertxs[idx][1], vertxs[idx][2]);
            }
        glEnd();

        overboard{}(flag);
        
        glPopMatrix();
    }

    /**
     * @brief function responsible for drawing the circle 
     *        that represents the object in 2D
     *  
     */
    void object::draw_circle()
    {
        glPushMatrix();
        glColor3f(color_2D[0], color_2D[1], color_2D[2]);

        float degres_v1 {}, degres_v2 {};
        constexpr const uint8_t n_points = 40;

        glTranslatef(v_translat[0] + 0.5, v_translat[1] + 0.5, v_translat[2]);
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
}