/*
    Nome: Bryan Keven Rocha Brauna
    Matricula: 499427
*/

#pragma once

namespace CBL
{
    /**
     * @brief Class responsible for highlighting each block
     * 
     */
    struct highlighting
    {
        bool light_on;
        int32_t x_pos, y_pos;

        highlighting()
            : light_on{false},
              x_pos   { },
              y_pos   { }
        {
        }

        highlighting(bool sig, int32_t x, int32_t y)
            : light_on{ sig },
              x_pos   {  x  },
              y_pos   {  y  }
        {
        }

        void on() { light_on = true; }
        void put_coordenate(int32_t x, int32_t y) 
        {
            x_pos = x;
            y_pos = y;
        }
    
        void operator() () const
        {
            glPushMatrix();
            
            glLineWidth(3.0f);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glColor3f(6.f, 0.f, 3.f);

            glTranslatef(x_pos, y_pos, 0.f);

            glBegin(GL_QUADS);
                glVertex3f(0.f, 0.f, 0.f);
                glVertex3f(1.f, 0.f, 0.f);
                glVertex3f(1.f, 1.f, 0.f);
                glVertex3f(0.f, 1.f, 0.f);
            glEnd();

            glFlush();

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glPopMatrix();
        }
    };
    
}