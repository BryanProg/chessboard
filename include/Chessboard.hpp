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

#include <cstdint>
#include <vector>
#include <memory>
#include <iostream>
#include <cmath>

#include "Cboard_Tile.hpp"
#include "Window.hpp"
#include "Utils.hpp"
#include "Camera.hpp"
#include "highlighting.hpp"

namespace CBL
{
    /**
     * @brief Main class. This class is the board itself
     * 
     */
    class chessboard : public window
    {
        public:
            using iterator = std::vector<std::unique_ptr<cboard_tile>>::iterator;
            
        public:
            chessboard() = delete;
            chessboard(int32_t, int32_t, uint8_t);

            void run();

            ~chessboard();

        private:
            enum class horizontal_move
            {
                left = -1, right = 1
            };

            enum class vertical_move
            {
                down = -1, up = 1
            };

        private:
            bool init();
            void window_settings();
            void additional_settings();
            void apply_2D_settings();
            void apply_3D_settings();
            void load_vertex();
            
            inline double get_aspect_ratio() const;
            
            inline bool is_target_cam(const glm::vec3&) const;
            inline bool is_target_cam(float, float, float) const;

            inline bool is_pos_cam(const glm::vec3&) const;
            inline bool is_pos_cam(float, float, float) const;

            inline bool is_max_y_pos(float) const;
            inline bool is_max_x_pos(float) const;

            inline bool is_min_y_pos(float) const;
            inline bool is_min_x_pos(float) const;

            inline bool next_is_target_tile(glm::vec3&) const;
            inline bool next_is_target_tile(float, float, float) const;

            inline bool status_obj_in(int32_t, int32_t)const;
            inline bool target_over_cam() const;

            void draw_board() const;
            
            void key_handle(int, int, int, int);
            void move_mouse_handle(double xpos, double ypos);
            
            inline std::unique_ptr<cboard_tile>* get_tile(std::size_t, std::size_t);
            
            inline void resize_window_handle(int width, int height);

            inline void camera_translate_tgt(const glm::vec3&);
            inline void camera_translate_tgt(float, float, float);

            inline void camera_translate_pos(const glm::vec3&);
            inline void camera_translate_pos(float, float, float);

            inline void create_obj(uint32_t);
            
            inline void pass_object_property(std::unique_ptr<cboard_tile>*);
            
            void target_horizontal_move(horizontal_move);
            void target_vertical_move(vertical_move);

            void cam_horizontal_move(horizontal_move);
            void cam_vertical_move(vertical_move);
            
        private:
            uint8_t                       n_tiles;
            int32_t                       width;
            int32_t                       height;
            const int32_t                 tab_side_sz;
            GLfloat                       tile_width;
            GLfloat                       tile_height;
            highlighting                  tile_edge;
            std::unique_ptr<cboard_tile>* target_plate;
            camera                        cam;
            std::vector<std::unique_ptr<object>(*)()> funct;
            std::vector<std::unique_ptr<cboard_tile>> board;
        
        private:

            static void ErrorCallBack(int err_code, const char* msg)
            {
                std::cerr << "Error: " << msg << std::endl;
            }
            
            static void key_call_back(GLFWwindow* pwindow, 
                                    int key   , int scand, 
                                    int action, int mods)
            {
                if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
                {
                    glfwSetWindowShouldClose(pwindow, GLFW_TRUE);
                }
                else
                {
                    chessboard* obj = (chessboard*)glfwGetWindowUserPointer(pwindow);
                    obj->key_handle(key, scand, action, mods);
                }
            }

            static void window_size_callback(GLFWwindow* pwindow, int width, int height)
            {
                chessboard* obj = (chessboard*)glfwGetWindowUserPointer(pwindow);
                obj->resize_window_handle(width, height);
            } 

            static void mouse_button_callback(GLFWwindow* pwindow, int button, int action, int mods)
            {
                chessboard* obj = (chessboard*)glfwGetWindowUserPointer(pwindow);

                double pos_x, pos_y;

                if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
                {
                    glfwGetCursorPos(obj->handle, &pos_x, &pos_y);
                    obj->move_mouse_handle(pos_x, pos_y);
                }
            }
    };

    inline double chessboard::get_aspect_ratio() const
    {
        return static_cast<double>(width)/height;
    }

    inline bool chessboard::is_target_cam(const glm::vec3& obj) const
    {
        return obj == cam.target;
    }

    inline bool chessboard::is_target_cam(float x, float y, float z) const
    {
        return cam.target == glm::vec3{x, y, z};
    }

    inline bool chessboard::is_pos_cam(const glm::vec3& obj) const
    {
        return obj == cam.pos_cam;
    }

    inline bool chessboard::is_pos_cam(float x, float y, float z) const
    {
        return cam.pos_cam == glm::vec3{x, y, z};
    }

    inline std::unique_ptr<cboard_tile>* chessboard::get_tile(std::size_t i, std::size_t j)
    {
        return &(board[(j * tab_side_sz) + i]);
    }

    inline void chessboard::camera_translate_tgt(const glm::vec3& vetor_t)
    {
        cam.target += vetor_t;
    }

    inline void chessboard::camera_translate_tgt(float x, float y, float z)
    {
        cam.target += glm::vec3{x, y, z};
    }

    inline void chessboard::camera_translate_pos(const glm::vec3& vetor_t)
    {
        cam.pos_cam += vetor_t;
    }

    inline void chessboard::camera_translate_pos(float x, float y, float z)
    {
        cam.pos_cam += glm::vec3{x, y, z};
    }

    inline void chessboard::pass_object_property(std::unique_ptr<cboard_tile>* p_obj)
    {
        (*(p_obj))->set_obj((*target_plate)->drop_obj());
        target_plate = p_obj;
    }

    inline void chessboard::resize_window_handle(int width, int height)
    {
        this->width  = width;
        this->height = height;
    }

    inline bool chessboard::is_max_y_pos(float y) const
    {
        return cam.pos_cam[1] < tab_side_sz - 1;
    }

    inline bool chessboard::is_max_x_pos(float x) const
    {
        return cam.pos_cam[0] < tab_side_sz - 1;
    }

    inline bool chessboard::is_min_y_pos(float y) const
    {
        return cam.pos_cam[1] > 0.5;
    }

    inline bool chessboard::is_min_x_pos(float x) const
    {
        return cam.pos_cam[0] > 0.5;
    }

    inline bool chessboard::next_is_target_tile(glm::vec3& obj) const
    {
        return is_target_cam(cam.pos_cam + obj);
    }

    inline bool chessboard::next_is_target_tile(float x, float y, float z) const
    {
        return is_target_cam(cam.pos_cam + glm::vec3{x, y, z});
    }

    inline bool chessboard::status_obj_in(int32_t row, int32_t col) const
    {
        return board[row * tab_side_sz + col]->state_object;
    }

    inline void chessboard::create_obj(uint32_t key)
    {
        (*target_plate)->load_obj(funct[key - GLFW_KEY_1]());
    }

    inline bool chessboard::target_over_cam() const
    {
        return (*target_plate)->pos_w + 0.5 == cam.pos_cam[0] && 
               (*target_plate)->pos_h + 0.5 == cam.pos_cam[1];
    }
}