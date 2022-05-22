/*
    Nome: Bryan Keven Rocha Brauna
    Matricula: 499427
*/

#pragma once

#include <GL/glew.h>
#include <GL/gl.h>

namespace CBL
{
    /**
     * @brief Class responsible for making the arrows of 3D objects
     * 
     */
    struct overboard
    {
        enum struct flag_draw
        {
            cube    , 
            piramide, 
            cylinder, 
            prism   ,
            none
        };

        void operator() (flag_draw flag) const
        {
            switch (flag)
            {
                case flag_draw::cube:
                    draw_overboard_cube();
                    break;
                
                case flag_draw::piramide:
                    draw_overboard_piramide();
                    break;
                
                case flag_draw::cylinder:
                    draw_overboard_cylinder();
                    break;

                case flag_draw::prism:
                    draw_overboard_prism();
                    break;

                default:
                    break;
            }
        }

        void draw_overboard_cube() const
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            glColor3f(0.f, 0.f, 0.f);

            glBegin(GL_QUADS);
            
                glVertex3f(0.f, 0.f, 0.5f);
                glVertex3f(0.f, 1.f, 0.5f);
                glVertex3f(1.f, 1.f, 0.5f);            
                glVertex3f(1.f, 0.f, 0.5f);

                glVertex3f(0.f, 0.f, 0.f);
                glVertex3f(0.f, 1.f, 0.f);
                glVertex3f(1.f, 1.f, 0.f);            
                glVertex3f(1.f, 0.f, 0.f);

                glVertex3f(0.f, 0.f, 0.f);
                glVertex3f(0.f, 0.f, 0.5f);
                glVertex3f(1.f, 0.f, 0.5f);
                glVertex3f(1.f, 0.f, 0.f);

                glVertex3f(0.f, 1.f, 0.f);
                glVertex3f(0.f, 1.f, 0.5f);
                glVertex3f(1.f, 1.f, 0.5f);
                glVertex3f(1.f, 1.f, 0.f);

                glVertex3f(1.f, 0.f, 0.f);
                glVertex3f(1.f, 0.f, 0.5f);
                glVertex3f(1.f, 1.f, 0.5f);
                glVertex3f(1.f, 1.f, 0.f);

                glVertex3f(0.f, 0.f, 0.f);
                glVertex3f(0.f, 0.f, 0.5f);
                glVertex3f(0.f, 1.f, 0.5f);
                glVertex3f(0.f, 1.f, 0.f);

            glEnd();

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        void draw_overboard_piramide() const
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

            glColor3f(0.f, 0.f, 0.f);

            glBegin(GL_QUADS);
                glVertex3f(0.f, 0.f, 0.f);
                glVertex3f(0.f, 1.f, 0.f);
                glVertex3f(1.f, 1.f, 0.f);            
                glVertex3f(1.f, 0.f, 0.f);
            glEnd();

            glBegin(GL_TRIANGLES);
                // face esquerdo triang
                glVertex3f(0.f, 0.f, 0.f);
                glVertex3f(0.5f, 0.5f, 0.5f);
                glVertex3f(0.f, 1.f, 0.f);

                // face direito triang
                glVertex3f(1.f, 0.f, 0.f);
                glVertex3f(0.5f, 0.5f, 0.5f);
                glVertex3f(1.f, 1.f, 0.f);

                // face frontal triang
                glVertex3f(0.f, 0.f, 0.f);
                glVertex3f(0.5f, 0.5f, 0.5f);
                glVertex3f(1.f, 0.f, 0.f);

                // face posterior triang
                glVertex3f(1.f, 1.f, 0.f);
                glVertex3f(0.5f, 0.5f, 0.5f);
                glVertex3f(0.f, 1.f, 0.f);

            glEnd();
            
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        void draw_overboard_cylinder() const
        {
            float degres_v1 {}, 
                  degres_v2 {};

            constexpr const uint8_t n_edges = 40u;

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glLineWidth(1.0f);
            glColor3f(0.f, 0.f, 0.f);

            for(uint8_t count = {0}; count < n_edges; ++count)
            {
                degres_v1 = ((360.0f/n_edges) * count);
                degres_v2 = ((360.0f/n_edges) * (count + 1));

                glBegin(GL_LINES);

                    glVertex3f
                    (
                        (cos(degres_v1 * M_PI/180.f) * 0.25f) + 0.5f, 
                        (sin(degres_v1 * M_PI/180.f) * 0.25f) + 0.5f, 
                        0.f
                    );

                    glVertex3f
                    (
                        (cos(degres_v2 * M_PI/180.f) * 0.25f) + 0.5f, 
                        (sin(degres_v2 * M_PI/180.f) * 0.25f) + 0.5f,
                        0.f
                    );
                    

                    glVertex3f
                    (
                        (cos(degres_v1 * M_PI/180.f) * 0.25f) + 0.5f, 
                        (sin(degres_v1 * M_PI/180.f) * 0.25f) + 0.5f, 
                        1.f
                    );

                    glVertex3f
                    (
                        (cos(degres_v2 * M_PI/180.f) * 0.25f) + 0.5f, 
                        (sin(degres_v2 * M_PI/180.f) * 0.25f) + 0.5f,
                        1.f
                    );

                glEnd();
            }

            glLineWidth(4.0f);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        void draw_overboard_prism() const
        {
            float degres_v1 {}, degres_v2 {};
            const uint8_t n_edges = 5u;

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glLineWidth(1.0f);
            glColor3f(0.f, 0.f, 0.f);

            for(uint8_t count = {0}; count < n_edges; ++count)
            {
                degres_v1 = ((360.0f/n_edges) * count);
                degres_v2 = ((360.0f/n_edges) * (count + 1));


                glBegin(GL_LINES);

                    glVertex3f
                    (
                        (cos(degres_v1 * M_PI/180.f) * 0.25f) + 0.5f, 
                        (sin(degres_v1 * M_PI/180.f) * 0.25f) + 0.5f, 
                        0.f
                    );

                    glVertex3f
                    (
                        (cos(degres_v2 * M_PI/180.f) * 0.25f) + 0.5f, 
                        (sin(degres_v2 * M_PI/180.f) * 0.25f) + 0.5f,
                            0.f
                    );
                    

                    glVertex3f
                    (
                        (cos(degres_v1 * M_PI/180.f) * 0.25f) + 0.5f, 
                        (sin(degres_v1 * M_PI/180.f) * 0.25f) + 0.5f, 
                        1.f
                    );

                    glVertex3f
                    (
                        (cos(degres_v2 * M_PI/180.f) * 0.25f) + 0.5f, 
                        (sin(degres_v2 * M_PI/180.f) * 0.25f) + 0.5f,
                        1.f
                    );
                    
                glEnd();
            }

            glLineWidth(4.0f);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    };    
}