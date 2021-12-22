/*
gpe_texture_target_raylib.h
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

#ifndef gpe_texture_target_raylib_h
#define gpe_texture_target_raylib_h


#include "gpe_renderer_raylib.h"
#include "../gpe/gpe_texture_target_base.h"
#include "../gpe/gpe.h"

namespace gpe
{
    class texture_target_raylib: public texture_target_base
    {
        protected:
            RenderTexture2D raylib_texture_target;
            Rectangle raylib_target_source;
            Rectangle raylib_target_dest;
            Vector2 raylib_target_origin;
            Color current_render_color;
        public:
            texture_target_raylib();
            ~texture_target_raylib();
            void change_alpha( uint8_t alpha );
            void change_color( color * color_new);
            void change_color( uint8_t red, uint8_t green, uint8_t blue );

            renderer_system_raylib * get_gpe_renderer_raylib(renderer_base * renderer);
            RenderTexture2D  get_raylib_render_texture();
            Texture  get_raylib_texture();

            texture_base * create_new();
            void render_overlay(  renderer_base * renderer,int x, int y, gpe::shape_rect* clip = nullptr, int alpha = 255  );
            void render_overlay_scaled(  renderer_base * renderer,int x, int y,float x_scale, float y_scale, gpe::shape_rect* clip = nullptr, color * render_color = nullptr, int alpha = 255 );

            void resize_target( renderer_base * renderer,int w, int h, int id = -1,bool useLinearScaling = true  );
            void set_blend_mode( int blend_mode_new);
    };
}
#endif //gpe_texture_target_raylib_h
