#pragma once
#include "types.h"
#include "opengl_render.h"
#include <stdio.h>
#include <dlfcn.h> 
#include <stdint.h>
#include "time.h"
#include "xlib_types.h"
#include "time.h"
#include "key_types.h"

static int visual_attribs[] =
{
    GLX_X_RENDERABLE, True,
    GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
    GLX_RENDER_TYPE, GLX_RGBA_BIT,
    GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
    GLX_RED_SIZE, 8,
    GLX_GREEN_SIZE, 8,
    GLX_BLUE_SIZE, 8,
    GLX_ALPHA_SIZE, 8,
    GLX_DEPTH_SIZE, 24,
    GLX_STENCIL_SIZE, 8,
    GLX_DOUBLEBUFFER, True,
    //GLX_SAMPLE_BUFFERS  , 1,
    //GLX_SAMPLES         , 4,
    None
};

PINLINE void  initialize_window(xwindow_types * x_context, screen_types * screen_context){
    
    int default_screen;
    x_context->display = XOpenDisplay(0);
    if(!x_context->display){
        
        fprintf(stderr, "cant open diplsaty");
        
    };
    
    default_screen = DefaultScreen(x_context->display);
    x_context->connection = XGetXCBConnection(x_context->display);
    if(!x_context->connection){
        
        printf("failed to get connection");
    };
    
    XSetEventQueueOwner(x_context->display, XCBOwnsEventQueue);
    x_context->screen = 0;
    x_context-> screen_iter = xcb_setup_roots_iterator(xcb_get_setup(x_context->connection));
    for(int screen_num = default_screen; x_context->screen_iter.rem && screen_num > 0; --screen_num, xcb_screen_next(&x_context->screen_iter));
    x_context->screen = x_context->screen_iter.data;
    
    int visual_id = 0;
    GLXFBConfig *fb_configs = 0;
    int num_fb_configs = 0;
    fb_configs = glXChooseFBConfig(x_context->display, default_screen, visual_attribs, &num_fb_configs);
    
    if(!fb_configs || num_fb_configs == 0){
        
        printf("glChooseFBConfig failed");
    };
    
    printf("Found %d matching FB configs", num_fb_configs);
    
    GLXFBConfig fb_config = fb_configs[0];
    glXGetFBConfigAttrib(x_context->display, fb_config, GLX_VISUAL_ID, &visual_id);
    
    
    x_context->context = glXCreateNewContext(x_context->display, fb_config, GLX_RGBA_TYPE, 0, True);
    if(!x_context->context){
        printf("failed to make context");
    };
    
    xcb_colormap_t colourmap = xcb_generate_id(x_context->connection);
    x_context->window = xcb_generate_id(x_context->connection);
    xcb_create_colormap(x_context->connection, XCB_COLORMAP_ALLOC_NONE,colourmap, x_context->screen->root, visual_id); 
    u32 event_mask = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS | XCB_EVENT_MASK_KEY_RELEASE;
    u32 value_list[] ={event_mask, colourmap, 0};
    u32 value_mask = XCB_CW_EVENT_MASK | XCB_CW_COLORMAP;
    
    xcb_create_window(x_context->connection, XCB_COPY_FROM_PARENT, x_context->window, x_context->screen->root, 0, 0, screen_context->render_width, screen_context->render_height, 0, XCB_WINDOW_CLASS_INPUT_OUTPUT, visual_id, value_mask, value_list);
    xcb_map_window(x_context->connection, x_context->window);
    x_context->drawable = 0;
    
    xcb_map_window(x_context->connection, x_context->window);
    xcb_flush(x_context->connection);
    
    xcb_intern_atom_cookie_t wmDeleteCookie = xcb_intern_atom(
                                                              x_context->connection, 0, strlen("WM_DELETE_WINDOW"), "WM_DELETE_WINDOW");
    xcb_intern_atom_cookie_t wmProtocolsCookie =
        xcb_intern_atom(x_context->connection, 0, strlen("WM_PROTOCOLS"), "WM_PROTOCOLS");
    xcb_intern_atom_reply_t *wmDeleteReply =
        xcb_intern_atom_reply(x_context->connection, wmDeleteCookie, NULL);
    xcb_intern_atom_reply_t *wmProtocolsReply =
        xcb_intern_atom_reply(x_context->connection, wmProtocolsCookie, NULL);
    
    x_context->wm_protocols = wmProtocolsReply->atom;
    
    x_context->wm_delete_win = wmDeleteReply->atom;
    xcb_change_property(x_context->connection, XCB_PROP_MODE_REPLACE, x_context->window,
                        wmProtocolsReply->atom, 4, 32, 1, &wmDeleteReply->atom);
    
    xcb_map_window(x_context->connection, x_context->window);
    xcb_flush(x_context->connection);
    
    x_context->glx_window = glXCreateWindow(x_context->display, fb_config, x_context->window, 0);
    if(!x_context->window){
        
        printf("failed to create window");
        xcb_destroy_window(x_context->connection, x_context->window);
        glXDestroyContext(x_context->display, x_context->context);
        
    };
    
    x_context->drawable = x_context->glx_window;
    if(!glXMakeContextCurrent(x_context->display, x_context->drawable, x_context->drawable, x_context->context)){
        
        xcb_destroy_window(x_context->connection,x_context->window);
        glXDestroyContext(x_context->display, x_context->context);
        printf("glxmakecontext failed");
        
    };
    
}

void platform_pump_messages(xwindow_types * x_context){
    
    xcb_generic_event_t * event;
    event= xcb_wait_for_event(x_context->connection);
    if(!event){
        fprintf(stderr, "eror in waitfor event");
        
    }
    xcb_client_message_event_t *cm;
    switch(event->response_type & ~0x80){
        case XCB_CLIENT_MESSAGE: {
            cm = (xcb_client_message_event_t *)event;
            
            if (cm->data.data32[0] == x_context->wm_delete_win)
                
                running = 0;
            break;
        };
        
        break;
        case XCB_KEY_PRESS:{
            /*
            xcb_key_press_event_t * key_press =(xcb_key_press_event_t *)event;
            printf("Key pressed in window %" PRIu32"\n",
                   key_press->event);
*/
            
            xcb_key_press_event_t * keyboard_event  =(xcb_key_press_event_t *)event;
            event->response_type == XCB_KEY_RELEASE;
            xcb_keycode_t code = keyboard_event->detail;
            KeySym key_sym = XkbKeycodeToKeysym(x_context->display, (KeyCode)code, 0, code & ShiftMask ? 1 : 0);
            
            
            keys key = translate_keycode(key_sym);
            
            break;
        };
        case XCB_KEY_RELEASE:{
            
            break;
        };
        case XCB_EXPOSE:{
            
            break;
        };
        default:
        break;
        
    }
    
    free(event);
}

static f64 last_time;

PINLINE void main_loop(xwindow_types * x_context){
    clock_start(&clock_context);
    clock_update(&clock_context);
    last_time = clock_context.elapsed;
    f64 running_time = 0;
    char frame_count = 0;
    f64 target_frame_seconds = 1.0f/60;
    pos[0] = screen_types_context.render_width * 0.5;
    pos[1] = screen_types_context.render_height * 0.5;
    while(running){
        
        clock_update(&clock_context);
        f64 current_time = clock_context.elapsed;
        
        delta = (current_time - last_time);
        f64 frame_start_time  =platform_get_absolute_time();
        
        
        render_loop(&x_types, &screen_types_context, delta);
        f64 frame_end_time = platform_get_absolute_time();
        f64 frame_elapsed_time = frame_end_time - frame_start_time;
        running_time += frame_elapsed_time;
        f64 remaining_seconds = target_frame_seconds - frame_elapsed_time;
        
        if (remaining_seconds > 0) {
            u64 remaining_ms = (remaining_seconds * 1000);
            
            // If there is time left, give it back to the OS.
            char limit_frames = false;
            if (remaining_ms > 0 && limit_frames) {
                platform_sleep(remaining_ms - 1);
            }
            
            frame_count++;
            
        }
        platform_pump_messages(&x_types);
    }
    
    glXDestroyWindow(x_context->display,x_context->glx_window);
    
    xcb_destroy_window(x_context->connection, x_context->window);
    
    glXDestroyContext(x_context->display, x_context->context);
    
    XCloseDisplay(x_context->display);
    
}


