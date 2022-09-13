#pragma once

#include "types.h"
#include "linmath/linmath.h"
#include "files.h"
#include "xlib_types.h"

struct render_state{
    
    u32 vao;
    u32 vbo;
    u32 ebo;
    u32 shader_default;
    u32 texture_colour;
    
    mat4x4 projection;
};

static render_state render_context;

PINLINE void render_init_shaders(render_state * render_context, screen_types * screen_context){
    
    render_context->shader_default = render_shader_create("/home/petermiller/Desktop/4coder/2d/default.vert", "/home/petermiller/Desktop/4coder/2d/default.frag");
    
    mat4x4_ortho(render_context->projection, 0, screen_context->render_width, 0, screen_context->render_height, -2, 2);
    
    glUseProgram(render_context->shader_default);
    
    glUniformMatrix4fv(glGetUniformLocation(render_context->shader_default, "projection"),
                       1, GL_FALSE, &render_context->projection[0][0]);
    
}

PINLINE void render_init_colour_texture(render_state * render_context){
    
    glGenTextures(1, &render_context->texture_colour);
    glBindTexture(GL_TEXTURE_2D, render_context->texture_colour);
    u8 solid_white[4] = {255, 255, 255, 255};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, solid_white);
    glBindTexture(GL_TEXTURE_2D, 0);
    
}

PINLINE void render_init_quad(render_state * render_context){
    
    f32 vertices[] = {
        
        0.5, 0.5, 0, 0, 0,
        0.5, -0.5, 0, 0, 1,
        -0.5, -0.5, 0, 1, 1,
        -0.5, 0.5, 0, 1, 0
    };
    
    u32 indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    
    glGenVertexArrays(1, &render_context->vao);
    glGenBuffers(1,&render_context->vbo);
    glGenBuffers(1,&render_context->ebo);
    
    glBindVertexArray(render_context->vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, render_context->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices ),vertices, GL_STATIC_DRAW );
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render_context->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), NULL);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void *)(3 * sizeof(f32)));
    
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    
};

PINLINE void render_quad(render_state * render_context, vec2 pos, vec2 size, vec4 color){
    glUseProgram(render_context->shader_default);
    mat4x4 model;
    mat4x4_identity(model);
    mat4x4_translate(model, pos[0], pos[1], 0);
    mat4x4_scale_aniso(model, model, size[0], size[1], 1);
    glUniformMatrix4fv(glGetUniformLocation(render_context->shader_default, "model"), 1,  GL_FALSE, &model[0][0]);
    
    glUniform4fv(glGetUniformLocation(render_context->shader_default, "color"), 1, color);
    glBindVertexArray(render_context->vao);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindTexture(GL_TEXTURE_2D, render_context->texture_colour);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}

PINLINE void render_loop(xwindow_types * x_context, screen_types * screen_context, f64  delta){
    float test = screen_context->render_width *0.5;
    float test2 = screen_context->render_height *0.5;
    glClearColor(0.5, 0.5, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    render_init_shaders(&render_context,  &screen_types_context);
    render_init_colour_texture(&render_context);
    
    render_init_quad(&render_context);
    
    render_quad(&render_context, pos,
                (vec2){50, 50}, (vec4){0, 1, 0 , 1} );
    
    glXSwapBuffers(x_context->display, x_context->drawable); 
};
