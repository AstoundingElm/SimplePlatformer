#pragma once

#include <stdlib.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>

#include "types.h"

struct xwindow_types{
    
    Display * display;
    xcb_connection_t * connection;
    int default_screen;
    xcb_screen_t * screen;
    GLXContext context;
    xcb_window_t window;
    GLXWindow glx_window;
    GLXDrawable drawable;
    xcb_screen_iterator_t screen_iter;
    xcb_atom_t wm_delete_win;
    xcb_atom_t wm_protocols;
};

static xwindow_types x_types;