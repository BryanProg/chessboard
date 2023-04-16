/*
    Nome: Bryan Keven Rocha Brauna
    Matricula: 499427
*/

#include "../include/Chessboard.hpp"

namespace CBL
{
    chessboard::chessboard(int32_t wid, int32_t hei, uint8_t n_til)
        : window       {       },
          width        { wid   },
          height       { hei   },
          n_tiles      { n_til },
          tab_side_sz  { 8u    },
          tile_width   { (tab_side_sz)/static_cast<float>(n_tiles)},
          tile_height  { (tab_side_sz)/static_cast<float>(n_tiles)},
          target_plate {nullptr},
          cam          {glm::vec3(0.5f, 0.5f, 1.f),
                        glm::vec3(7.5f, 7.5f, 0.f),
                        glm::vec3(0.f, 0.f, 1.f)   },
          funct        {        cube_obj, 
                                piramide_obj, 
                                cylinder, 
                                prism              },
          board        (n_tiles * n_tiles)
    {
        if (!init())
            exit(EXIT_FAILURE);
        
        glfwSetWindowUserPointer(handle, this);

        load_vertex();
        window_settings();
        additional_settings();
    }

    chessboard::~chessboard()
    {
        glfwDestroyWindow(handle);
        glfwTerminate();
    }

    /**
     * @brief function for initial settings
     *  
     */
    bool chessboard::init()
    {
        glfwSetErrorCallback(ErrorCallBack);

        if (!glfwInit())
            return false;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

        handle = glfwCreateWindow(width, height,"Chessboard",
                                  nullptr, nullptr);
        if (!handle)
        {
            glfwTerminate();
            return false;
        }

        return true;
    }

    /**
     * @brief function for window settings
     *  
     */
    void chessboard::window_settings()
    {
        glfwSetKeyCallback(handle, key_call_back);
        glfwSetWindowSizeCallback (handle, window_size_callback);
        glfwSetMouseButtonCallback(handle, mouse_button_callback);
        glfwSetInputMode (handle, GLFW_STICKY_MOUSE_BUTTONS , GLFW_TRUE );
        glfwMakeContextCurrent(handle);
    }

    /**
     * @brief function for additional settings
     *  
     */
    void chessboard::additional_settings()
    {
        glEnable(GL_DEPTH_TEST); // Depth Testing
        glDepthFunc(GL_LEQUAL);
        glDisable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        glPointSize(8.0f);
        glLineWidth(4.0f);
    }

    /**
     * @brief function for 2D settings
     *  
     */
    void chessboard::apply_2D_settings()
    {
        glViewport(0.0f, 0.0f, width/2, height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        glOrtho(0, 8.f, 0.f, 8.f, -1.0f, 1.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glClearColor(0.5f, 0.5f, 0.5f, 1.f);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
    }

    /**
     * @brief function for 3D settings
     *  
     */
    void chessboard::apply_3D_settings()
    {
        glViewport(width/2.0, 0, width/2.0, height);

        float aspect_ratio = get_aspect_ratio();
        auto proj{ glm::perspective(glm::radians(45.0f), aspect_ratio, 0.1f, 100.0f) };

        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(glm::value_ptr(proj));

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        cam.update_matriz();
        glMultMatrixf(cam);

    }

    /**
     * @brief function responsible for drawing the board
     *  
     */
    void chessboard::draw_board() const
    {
        glLineWidth(4.0f);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        for(auto& element : board)
        {
            glColor3f(element->color[0],
                      element->color[1],
                      element->color[2]);
            
            glBegin(GL_QUADS);
                glVertex3f(element->points[0], 
                            element->points[1],
                            0.f);

                glVertex3f(element->points[0] + tile_width, 
                            element->points[1],
                            0.f);

                glVertex3f(element->points[0] + tile_width, 
                            element->points[1] + tile_height,
                            0.f);
                
                glVertex3f(element->points[0], 
                            element->points[1] + tile_height,
                            0.f);
            glEnd();
        }

        if (tile_edge.light_on)
            tile_edge();

    }

    /**
     * @brief function responsible for load vertex of the board
     *  
     */
    void chessboard::load_vertex()
    {
        uint8_t idx{};
        bool state_color = true;

        for (float row{}; row < tab_side_sz; row += tile_height, state_color -= 1)
            for (float column{}; column < tab_side_sz; column += tile_width, ++idx, state_color -= 1)
                board[idx] = std::make_unique<cboard_tile>
                (
                    glm::vec2(0 + column, 0 + row),
                    (uint32_t)(column/tile_height), (uint32_t)(row/tile_width),
                    glm::vec3(state_color, state_color, state_color)
                );

        board[tab_side_sz * tab_side_sz - 1]->load_obj(cube_obj());
            
    }

    /**
     * @brief function responsible for main loop 
     *  
     */
    void chessboard::run()
    {
        while(!glfwWindowShouldClose(handle))
        {
            apply_2D_settings();
            draw_board();
            cam.render_cam();

            for(auto& element : board)
                if (element->state_object)
                    element->obj->draw_circle();

            apply_3D_settings();
            draw_board();

            for(auto& element : board)
                if (element->state_object)
                    element->obj->draw_obj();

            glFlush();

            glfwSwapBuffers(handle);
            glfwPollEvents();
        }
    }

    /**
     * @brief function that handles all events performed by the mouse
     *        
     * 
     * @param xpos X mouse position
     * @param ypos Y mouse position
     *
     */
    void chessboard::move_mouse_handle(double xpos, double ypos)
    {
        const double w = static_cast<double>(width)/2;

        const float curr_xpos = (xpos * tab_side_sz)/w;
        const float curr_ypos = ((height - ypos) * tab_side_sz)/height;

        if (xpos <= width/2)
        {
            if (!is_pos_cam((int32_t)curr_xpos + 0.5, 
                            (int32_t)curr_ypos + 0.5, 
                            cam.pos_cam[2]))
            {
                cam.target[0] = (int32_t)curr_xpos + 0.5;
                cam.target[1] = (int32_t)curr_ypos + 0.5;
            }

            target_plate = get_tile((int32_t)curr_xpos, (int32_t)curr_ypos);

            tile_edge.on();
            tile_edge.put_coordenate(curr_xpos, curr_ypos);
        }
    }

    /**
     * @brief function that handles all events performed by the keyboard
     * 
     * @param key    key value
     * @param scand  scan value
     * @param action action value
     * @param mods   value of mods
     *
     */
    void chessboard::key_handle(int key, int scand, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            switch (key)
            {   
                case GLFW_KEY_Z:
                    camera_translate_pos(0.f, 0.f, 0.5f);
                    break;
                
                case GLFW_KEY_X:
                    if (cam.pos_cam[2] > 1.f)
                        camera_translate_pos(0.f, 0.f, -0.5f);
                    break;

                case GLFW_KEY_RIGHT:

                    if (target_plate != nullptr && target_over_cam())
                    {
                        if (is_max_x_pos(cam.pos_cam[0])                            &&
                            !next_is_target_tile(tile_height, 0.f, -cam.pos_cam[2]) &&
                            !status_obj_in(cam.pos_cam[1], cam.pos_cam[0] + 1.f))
                        {   
                            cam_horizontal_move(horizontal_move::right);
                        }
                    }
                    else if (target_plate != nullptr                 && 
                            (*target_plate)->state_object            && 
                            (*target_plate)->pos_w < tab_side_sz - 1 &&
                            !is_pos_cam(cam.target[0] + 1, 
                                   cam.target[1], 
                                   cam.pos_cam[2]))
                    {
                        target_horizontal_move(horizontal_move::right);
                    }

                    break;
                
                case GLFW_KEY_LEFT:

                    if (target_plate != nullptr && target_over_cam())
                    {
                        if (is_min_x_pos(cam.pos_cam[0]) &&
                        !next_is_target_tile(-tile_height, 0.f, -cam.pos_cam[2]) &&
                        !status_obj_in(cam.pos_cam[1], cam.pos_cam[0] - 1.f))
                        {   
                            cam_horizontal_move(horizontal_move::left);
                        }
                    }
                    else if (target_plate != nullptr      && 
                            (*target_plate)->state_object && 
                            (*target_plate)->pos_w > 0    &&
                            !is_pos_cam(cam.target[0] - 1, 
                                   cam.target[1], 
                                   cam.pos_cam[2]))
                    {
                        target_horizontal_move(horizontal_move::left);
                    }

                    break;
                
                case GLFW_KEY_UP:
                    
                    if (target_plate != nullptr && target_over_cam())
                    {
                        if (is_max_y_pos(cam.pos_cam[1]) &&
                            !next_is_target_tile(0.f, tile_height, -cam.pos_cam[2]) &&
                            !status_obj_in(cam.pos_cam[1] + 1.f, cam.pos_cam[0]))
                        {   
                            cam_vertical_move(vertical_move::up);
                        }
                    }
                    else if (target_plate != nullptr                 &&
                       (*target_plate)->state_object            && 
                       (*target_plate)->pos_h < tab_side_sz - 1 &&
                       !is_pos_cam(cam.target[0], 
                                   cam.target[1] + 1, 
                                   cam.pos_cam[2]))
                    {
                        target_vertical_move(vertical_move::up);
                    }

                    break;

                case GLFW_KEY_DOWN:
                    
                    if (target_plate != nullptr && target_over_cam())
                    {
                        if (is_min_y_pos(cam.pos_cam[1]) &&
                            !next_is_target_tile(0.f, -tile_height, -cam.pos_cam[2]) &&
                            !status_obj_in(cam.pos_cam[1] - 1.f, cam.pos_cam[0]))
                        {
                            cam_vertical_move(vertical_move::down);
                        }
                    }
                    else if (target_plate != nullptr      && 
                            (*target_plate)->state_object && 
                            (*target_plate)->pos_h > 0    &&
                            !is_pos_cam(cam.target[0], 
                                        cam.target[1] - 1, 
                                        cam.pos_cam[2]))
                    {
                        target_vertical_move(vertical_move::down);
                    }

                    break;
                
                case GLFW_KEY_1:
                case GLFW_KEY_2:
                case GLFW_KEY_3:
                case GLFW_KEY_4:
                    if (target_plate != nullptr        &&
                        !(*target_plate)->state_object &&
                        !target_over_cam())
                    {
                        create_obj(key);
                    }

                    break;
                
                case GLFW_KEY_B:
                    if (target_plate != nullptr && 
                       (*target_plate)->state_object)
                    {
                        (*target_plate)->obj->set_color(0.f, 0.f, 1.f);
                        (*target_plate)->obj->set_color_2D(0.f, 0.f, 1.f);
                    }
                    break;
                
                case GLFW_KEY_G:
                    if (target_plate != nullptr && 
                       (*target_plate)->state_object)
                    {
                        (*target_plate)->obj->set_color(0.f, 1.f, 0.f);
                        (*target_plate)->obj->set_color_2D(0.f, 1.f, 0.f);
                    }
                    break;
                
                case GLFW_KEY_R:
                    if (target_plate != nullptr && 
                       (*target_plate)->state_object)
                    {
                        (*target_plate)->obj->set_color(1.f, 0.f, 0.f);
                        (*target_plate)->obj->set_color_2D(1.f, 0.f, 0.f);
                    }
                    break;

                default:
                    break;
            }    
        }
    }

    void chessboard::target_horizontal_move(horizontal_move move)
    {
        auto aux = get_tile((*target_plate)->pos_w + static_cast<int32_t>(move), (*target_plate)->pos_h);

        if((*aux)->state_object)
            return;

        (*target_plate)->obj->translate(glm::vec3{move, 0.f, 0.f});

        camera_translate_tgt((float)move, 0.f, 0.f);
        pass_object_property(aux);

        tile_edge.put_coordenate((int32_t)(*target_plate)->points[0],
                                 (int32_t)(*target_plate)->points[1]);
    }

    void chessboard::cam_horizontal_move(horizontal_move move)
    {
        camera_translate_pos(tile_width * (int32_t)move, 0.f, 0.f);
        
        auto aux = get_tile((*target_plate)->pos_w + (int32_t)move, (*target_plate)->pos_h);
        target_plate = std::move(aux);

        tile_edge.put_coordenate((int32_t)(*target_plate)->points[0],
                                (int32_t)(*target_plate)->points[1]);
    }

    void chessboard::target_vertical_move(vertical_move move)
    {
        auto aux = get_tile((*target_plate)->pos_w, (*target_plate)->pos_h + (int32_t)move);

        if((*aux)->state_object)
            return;

        (*target_plate)->obj->translate(glm::vec3{0.f, move, 0.f});

        camera_translate_tgt(0.f, (float)move, 0.f);
        pass_object_property(aux);

        tile_edge.put_coordenate((int32_t)(*target_plate)->points[0],
                                 (int32_t)(*target_plate)->points[1]);
    }

    void chessboard::cam_vertical_move(vertical_move move)
    {
        camera_translate_pos(0.f, tile_height * (int32_t)move, 0.f);

        auto aux = get_tile((*target_plate)->pos_w, (*target_plate)->pos_h + (int32_t)move);
        target_plate = std::move(aux);
        
        tile_edge.put_coordenate((int32_t)(*target_plate)->points[0],
                                 (int32_t)(*target_plate)->points[1]);
    }
}