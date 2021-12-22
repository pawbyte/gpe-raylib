/*
gpe_texture_target_raylib.cpp
This file is part of:
GAME PENCIL ENGINE
https://www.pawbyte.com/gamepencilengine
Copyright (c) 2014-2021 Nathan Hurde, Chase Lee.

Copyright (c) 2014-2021 PawByte LLC.
Copyright (c) 2014-2021 Game Pencil Engine contributors ( Contributors Page )

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the “Software”), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

-Game Pencil Engine <https://www.pawbyte.com/gamepencilengine>


*/

#include "gpe_texture_target_raylib.h"

namespace gpe
{
    texture_target_raylib::texture_target_raylib()
    {
        textureType = "target-raylib";
        raylib_texture_target = LoadRenderTexture( screen_width, screen_height );
        texWid = screen_width;
        texHeight = screen_height;
        current_render_color.r = 255;
        current_render_color.g = 255;
        current_render_color.b = 255;
        current_render_color.a = 255;
    }

    texture_target_raylib::~texture_target_raylib()
    {
        if( raylib_texture_target.texture.id >= 0 || raylib_texture_target.texture.id != GetTextureDefault().id )
        {
            UnloadRenderTexture( raylib_texture_target );
        }
    }

    void texture_target_raylib::change_alpha( uint8_t alpha  )
    {
        lastAlphaRendered = alpha;
        current_render_color.a = alpha;
    }

    void texture_target_raylib::change_color( color * color_new)
    {
        if( color_new == nullptr)
        {
            return;
        }
        if( color_new->get_r() == currentR && color_new->get_g() == currentG && color_new->get_b() == currentB )
        {
                return;
        }
        currentR = color_new->get_r();
        currentG = color_new->get_g();
        currentB = color_new->get_b();

        current_render_color.r = currentR;
        current_render_color.g = currentG;
        current_render_color.b = currentB;
    }

    void texture_target_raylib::change_color( uint8_t red, uint8_t green, uint8_t blue )
    {
        if( red == currentR && green == currentG && blue == currentB )
        {
            return;
        }
        currentR = red;
        currentG = green;
        currentB = blue;

        current_render_color.r = red;
        current_render_color.g = green;
        current_render_color.b = blue;
    }

    renderer_system_raylib * texture_target_raylib::get_gpe_renderer_raylib(renderer_base * renderer)
    {
        if( renderer == nullptr)
        {
            return nullptr;
        }
        if( renderer->get_renderer_type() == "raylib")
        {
            renderer_system_raylib * raylibRenderer = (renderer_system_raylib * )renderer;
            return raylibRenderer;
        }
        return nullptr;
    }

    RenderTexture2D  texture_target_raylib::get_raylib_render_texture()
    {
        return raylib_texture_target;
    }

    Texture  texture_target_raylib::get_raylib_texture()
    {
        return raylib_texture_target.texture;
    }

    texture_base * texture_target_raylib::create_new()
    {
        return new texture_target_raylib();
    }

    void texture_target_raylib::render_overlay(  renderer_base * renderer,int x, int y, gpe::shape_rect* clip , int alpha  )
    {
        if( alpha == 0 ||  renderer == nullptr)
        {
            return;
        }
        renderer_system_raylib * raylibRenderer = get_gpe_renderer_raylib(renderer);

        if( raylibRenderer == nullptr)
        {
            return;
        }

        change_color( 255,255,255 );
        set_alpha( alpha );
        //Set clip rendering dimensions
        if( clip != nullptr )
        {
            raylib_target_source.x = clip->x;
            raylib_target_source.y = clip->y;
            raylib_target_source.width = clip->get_width();
            raylib_target_source.height = -clip->get_height();
        }
        else
        {
            raylib_target_source.x = 0;
            raylib_target_source.y = 0;
            raylib_target_source.width = raylib_texture_target.texture.width;
            raylib_target_source.height = -raylib_texture_target.texture.height;
        }

        int temp_blend = renderer_main->get_blend_mode();

        renderer_main->set_render_blend_mode( currentBlendMode );

        DrawTextureRec(raylib_texture_target.texture, raylib_target_source, (Vector2) { x, y }, current_render_color);
        EndBlendMode();

        //renderer_main->set_render_blend_mode( temp_blend );
    }

    void texture_target_raylib::render_overlay_scaled( renderer_base * renderer, int x, int y,float x_scale, float y_scale, gpe::shape_rect* clip, color * render_color, int alpha )
    {
        if( x_scale <= 0 || y_scale <= 0 || alpha == 0 || renderer == nullptr)
        {
            return;
        }
        renderer_system_raylib * raylibRenderer = get_gpe_renderer_raylib(renderer);

        if( raylibRenderer == nullptr)
        {
            return;
        }
        //raylib_Rect render_rect = { x, y, texWid, texHeight };

        change_color(render_color);
        set_alpha( alpha );

        int new_width = 0;
        int new_height = 0;
        bool flipHori = false,  flipVert = false;
        if( clip != nullptr )
        {
            raylib_target_source.x = clip->x;
            raylib_target_source.y = clip->y;
            raylib_target_source.width = clip->get_width();
            raylib_target_source.height = -clip->get_height();
        }
        else
        {
            raylib_target_source.x = 0;
            raylib_target_source.y = 0;
            raylib_target_source.width = raylib_texture_target.texture.width;
            raylib_target_source.height = -raylib_texture_target.texture.height;
        }

        raylib_target_dest.x = x;
        raylib_target_dest.y = y;
        raylib_target_dest.width = raylib_target_source.width * x_scale;
        raylib_target_dest.height = raylib_target_source.height * y_scale;

        raylib_target_origin.x = raylib_target_source.width;
        raylib_target_origin.y = raylib_target_source.height;

        int temp_blend = renderer_main->get_blend_mode();

        renderer_main->set_render_blend_mode( blend_mode_mod );

        DrawTextureRec(raylib_texture_target.texture, raylib_target_source, (Vector2) { x, y }, WHITE);

        DrawTexturePro(raylib_texture_target.texture, raylib_target_source, raylib_target_dest, raylib_target_origin, 0, current_render_color);
        EndBlendMode();

        //renderer_main->set_render_blend_mode( temp_blend );
    }

    void texture_target_raylib::resize_target(renderer_base * renderer, int w, int h, int id, bool useLinearScaling  )
    {
        if( w > 0 &&  h > 0)
        {
            UnloadRenderTexture( raylib_texture_target );
            raylib_texture_target = LoadRenderTexture( w, h);
            texWid = raylib_texture_target.texture.width;
            texHeight = raylib_texture_target.texture.height;
        }
    }


    void texture_target_raylib::set_blend_mode( int blend_mode_new)
    {
        if( currentBlendMode == blend_mode_new )
        {
            return;
        }
        currentBlendMode = blend_mode_new;
    }
}
