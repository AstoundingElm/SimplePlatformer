#pragma once
#include <stdio.h>
#include <X11/Xlib.h>
#include <dlfcn.h>
#include <X11/Xlib-xcb.h> 

#include <xcb/xcb.h>
#include "linmath/linmath.h"
#include <GL/glx.h>
#include <GL/gl.h>
#include <stdint.h>
#include <stdarg.h>
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef float f32;
typedef double f64;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = NULL;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv  = NULL;
PFNGLGENBUFFERSPROC glGenBuffers = NULL;

PFNGLBINDVERTEXARRAYPROC glBindVertexArray = NULL;
PFNGLBINDBUFFERPROC  glBindBuffer = NULL;
PFNGLBUFFERDATAPROC  glBufferData = NULL;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = NULL;

PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNGLSHADERSOURCEPROC glShaderSource  = NULL;
PFNGLCOMPILESHADERPROC glCompileShader = NULL;
PFNGLGETSHADERIVPROC glGetShaderiv  = NULL;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;

PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLATTACHSHADERPROC glAttachShader = NULL;
PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
PFNGLUSEPROGRAMPROC glUseProgram = NULL;
PFNGLUNIFORM4FVPROC glUniform4fv = NULL;

void * libGL;

void load_functions(){
    
    libGL = dlopen("libGL.so", RTLD_LAZY);
    if(!libGL){
        printf("couldnt load function");
    }
    
};

static int running  = 1;

f64 delta = 0;
static vec2 pos;
#define PINLINE static inline 

#define ERROR_EXIT(...) {fprintf(stderr, __VA_ARGS__); exit(1);}
#define ERROR_RETURN(R,...) fprintf(stderr, __VA_ARGS__); return R;

struct screen_types{
    
    
    u32 render_width = 1280;
    u32 render_height = 720;
};

static screen_types  screen_types_context;

