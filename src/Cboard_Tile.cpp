/*
    Nome: Bryan Keven Rocha Brauna
    Matricula: 499427
*/

#include "../include/Cboard_Tile.hpp"

namespace CBL
{

    cboard_tile::cboard_tile()
    :    points{ },
         pos_w { },
         pos_h { },
         color { },
         state_object { false },
         obj          {   nullptr    }
    {
    }

    cboard_tile::cboard_tile(const vertex& v, int32_t w, int32_t h, const colors& c)
    :   points{ v },
        pos_w { w },
        pos_h { h },
        color { c },
        state_object { false },
        obj          {   nullptr    }
    {
    }

    /**
     * @brief function responsible for loading an object based on its vertices 
     *        and vertex colors
     *        
     * 
     * @param vtx list of vertices
     * @param c_vtx Vertex color list
     *
     */
    void cboard_tile::load_obj(const object::vertices& vtx, const object::vertx_colors& c_vtx)
    {
        obj = std::make_unique<object>(vtx, c_vtx, pos_w, pos_h);
        object_on();
    }

    /**
     * @brief function responsible for loading an object based on another object
     *        
     * 
     * @param obj pointer to another object
     *
     */
    void cboard_tile::load_obj(std::unique_ptr<object> obj)
    {
        set_obj(std::move(obj));
    }

    /**
     * @brief function responsible for dropping an object from this block
     * 
     */
    std::unique_ptr<object> cboard_tile::drop_obj()
    {
        object_off();
        return std::move(obj);
    }

    /**
     * @brief define an object for that block
     *        
     * 
     * @param new_obj pointer to a new object
     *
     */
    void cboard_tile::set_obj(std::unique_ptr<object> new_obj)
    {
        obj = std::move(new_obj);
        obj->set_pos_init(pos_w, pos_h);
        object_on();
    }
}
