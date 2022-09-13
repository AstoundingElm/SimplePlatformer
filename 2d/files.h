#pragma once

#include "types.h"

#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#define IO_READ_CHUNK_SIZE 2097152
#define IO_READ_ERROR_GENERAL "error reading file, %s. errno: %d\n"
#define IO_READ_ERROR_MEMORY "Not eneough free memeory to read%s"
struct File{
    
    char * data;
    size_t len;
    bool is_valid;
};

static File file;

File io_file_read(const char * path){
    
    File file = {.is_valid = false};
    FILE * fp = fopen(path, "rb");
    if(ferror(fp)){
        ERROR_RETURN(file, IO_READ_ERROR_GENERAL, path, errno);
        
    };
    
    char * data = NULL;
    char * tmp = NULL;
    size_t used = 0;
    size_t size = 0;
    size_t n = 0;
    
    while(true){
        
        if(used + IO_READ_CHUNK_SIZE + 1 > size){
            
            size = used + IO_READ_CHUNK_SIZE + 1;
            
            if(size <= used){
                
                free(data);
                ERROR_RETURN(file, "input file too large%s\n", path);
                abort();
                
            }
            
            tmp  = (char *)realloc(data, size);
            if(!tmp){
                free(data);
                ERROR_RETURN(file, IO_READ_ERROR_MEMORY, path);
                abort();
            }
            data = tmp;
        }
        n = fread(data + used, 1, IO_READ_CHUNK_SIZE, fp);
        if(n == 0)
            break;
        
        used += n;
    }
    
    if(ferror(fp)){
        
        free(data);
        ERROR_RETURN(file, IO_READ_ERROR_GENERAL, path, errno);
        
    };
    
    tmp = (char *)realloc(data, used +1);
    if(!tmp){
        
        free(data);
        ERROR_RETURN(file, IO_READ_ERROR_MEMORY, path);
        abort();
    };
    
    data = tmp;
    data[used] = 0;
    file.data = data;
    file.len = used;
    file.is_valid = true;
    
    return file; 
};

int io_file_write(void * buffer, size_t size, const char * path){
    
    FILE * fp = fopen(path, "wb");
    if(!fp || ferror(fp))
        ERROR_RETURN(1, "cannot write file %s", path );
    
    
    size_t chunks_written =  fwrite(buffer, size, 1, fp);
    fclose(fp);
    
    if(chunks_written != 1)
        ERROR_RETURN(1, "wirte error%zu", chunks_written);
    return 0;
    
};

u32 render_shader_create(const char * path_vert, const char * path_frag){
    
    int success;
    
    char log[512];
    
    File vertex_file = io_file_read(path_vert);
    
    if(!vertex_file.is_valid){
        
        ERROR_EXIT("Error reading shader %s", path_vert);
        
        
    }
    
    u32 shader_vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader_vertex, 1, (const char * const*)&vertex_file, NULL);
    glCompileShader(shader_vertex);
    glGetShaderiv(shader_vertex, GL_COMPILE_STATUS, &success);
    
    if(!success){
        
        glGetShaderInfoLog(shader_vertex, 512, NULL, log);
        ERROR_EXIT("Error compiling vertex shader. %s\n", log);
    }
    
    File frag_file = io_file_read(path_frag);
    
    if(!frag_file.is_valid){
        
        ERROR_EXIT("Error reading shader %s", path_frag);
        
        
    }
    
    u32 shader_frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader_frag, 1, (const char * const*)&frag_file, NULL);
    glCompileShader(shader_frag);
    glGetShaderiv(shader_frag, GL_COMPILE_STATUS, &success);
    
    if(!success){
        
        glGetShaderInfoLog(shader_frag, 512, NULL, log);
        ERROR_EXIT("Error compiling vertex shader. %s\n", log);
        
    }
    
    
    u32 shader = glCreateProgram();
    glAttachShader(shader, shader_vertex);
    glAttachShader(shader, shader_frag);
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if(!success){
        
        glGetProgramInfoLog(shader, 512, NULL, log);
        ERROR_EXIT("error linking shaer. %s\n", log);
    };
    free(vertex_file.data);
    free(frag_file.data);
    
    return shader;
    
}
