#pragma once

#include "types.h"

#define DEFINE_KEY(name, code) KEY_##name = code

typedef enum keys {
    DEFINE_KEY(BACKSPACE, 0x08),
    DEFINE_KEY(ENTER, 0x0D),
    DEFINE_KEY(TAB, 0x09),
    DEFINE_KEY(SHIFT, 0x10),
    DEFINE_KEY(CONTROL, 0x11),
    
    DEFINE_KEY(PAUSE, 0x13),
    DEFINE_KEY(CAPITAL, 0x14),
    
    DEFINE_KEY(ESCAPE, 0x1B),
    
    DEFINE_KEY(CONVERT, 0x1C),
    DEFINE_KEY(NONCONVERT, 0x1D),
    DEFINE_KEY(ACCEPT, 0x1E),
    DEFINE_KEY(MODECHANGE, 0x1F),
    
    DEFINE_KEY(SPACE, 0x20),
    DEFINE_KEY(PRIOR, 0x21),
    DEFINE_KEY(NEXT, 0x22),
    DEFINE_KEY(END, 0x23),
    DEFINE_KEY(HOME, 0x24),
    DEFINE_KEY(LEFT, 0x25),
    DEFINE_KEY(UP, 0x26),
    DEFINE_KEY(RIGHT, 0x27),
    DEFINE_KEY(DOWN, 0x28),
    DEFINE_KEY(SELECT, 0x29),
    DEFINE_KEY(PRINT, 0x2A),
    DEFINE_KEY(EXECUTE, 0x2B),
    DEFINE_KEY(SNAPSHOT, 0x2C),
    DEFINE_KEY(INSERT, 0x2D),
    DEFINE_KEY(DELETE, 0x2E),
    DEFINE_KEY(HELP, 0x2F),
    
    DEFINE_KEY(A, 0x41),
    DEFINE_KEY(B, 0x42),
    DEFINE_KEY(C, 0x43),
    DEFINE_KEY(D, 0x44),
    DEFINE_KEY(E, 0x45),
    DEFINE_KEY(F, 0x46),
    DEFINE_KEY(G, 0x47),
    DEFINE_KEY(H, 0x48),
    DEFINE_KEY(I, 0x49),
    DEFINE_KEY(J, 0x4A),
    DEFINE_KEY(K, 0x4B),
    DEFINE_KEY(L, 0x4C),
    DEFINE_KEY(M, 0x4D),
    DEFINE_KEY(N, 0x4E),
    DEFINE_KEY(O, 0x4F),
    DEFINE_KEY(P, 0x50),
    DEFINE_KEY(Q, 0x51),
    DEFINE_KEY(R, 0x52),
    DEFINE_KEY(S, 0x53),
    DEFINE_KEY(T, 0x54),
    DEFINE_KEY(U, 0x55),
    DEFINE_KEY(V, 0x56),
    DEFINE_KEY(W, 0x57),
    DEFINE_KEY(X, 0x58),
    DEFINE_KEY(Y, 0x59),
    DEFINE_KEY(Z, 0x5A),
    
    DEFINE_KEY(LWIN, 0x5B),
    DEFINE_KEY(RWIN, 0x5C),
    DEFINE_KEY(APPS, 0x5D),
    
    DEFINE_KEY(SLEEP, 0x5F),
    
    DEFINE_KEY(NUMPAD0, 0x60),
    DEFINE_KEY(NUMPAD1, 0x61),
    DEFINE_KEY(NUMPAD2, 0x62),
    DEFINE_KEY(NUMPAD3, 0x63),
    DEFINE_KEY(NUMPAD4, 0x64),
    DEFINE_KEY(NUMPAD5, 0x65),
    DEFINE_KEY(NUMPAD6, 0x66),
    DEFINE_KEY(NUMPAD7, 0x67),
    DEFINE_KEY(NUMPAD8, 0x68),
    DEFINE_KEY(NUMPAD9, 0x69),
    DEFINE_KEY(MULTIPLY, 0x6A),
    DEFINE_KEY(ADD, 0x6B),
    DEFINE_KEY(SEPARATOR, 0x6C),
    DEFINE_KEY(SUBTRACT, 0x6D),
    DEFINE_KEY(DECIMAL, 0x6E),
    DEFINE_KEY(DIVIDE, 0x6F),
    DEFINE_KEY(F1, 0x70),
    DEFINE_KEY(F2, 0x71),
    DEFINE_KEY(F3, 0x72),
    DEFINE_KEY(F4, 0x73),
    DEFINE_KEY(F5, 0x74),
    DEFINE_KEY(F6, 0x75),
    DEFINE_KEY(F7, 0x76),
    DEFINE_KEY(F8, 0x77),
    DEFINE_KEY(F9, 0x78),
    DEFINE_KEY(F10, 0x79),
    DEFINE_KEY(F11, 0x7A),
    DEFINE_KEY(F12, 0x7B),
    DEFINE_KEY(F13, 0x7C),
    DEFINE_KEY(F14, 0x7D),
    DEFINE_KEY(F15, 0x7E),
    DEFINE_KEY(F16, 0x7F),
    DEFINE_KEY(F17, 0x80),
    DEFINE_KEY(F18, 0x81),
    DEFINE_KEY(F19, 0x82),
    DEFINE_KEY(F20, 0x83),
    DEFINE_KEY(F21, 0x84),
    DEFINE_KEY(F22, 0x85),
    DEFINE_KEY(F23, 0x86),
    DEFINE_KEY(F24, 0x87),
    
    DEFINE_KEY(NUMLOCK, 0x90),
    DEFINE_KEY(SCROLL, 0x91),
    
    DEFINE_KEY(NUMPAD_EQUAL, 0x92),
    
    DEFINE_KEY(LSHIFT, 0xA0),
    DEFINE_KEY(RSHIFT, 0xA1),
    DEFINE_KEY(LCONTROL, 0xA2),
    DEFINE_KEY(RCONTROL, 0xA3),
    DEFINE_KEY(LMENU, 0xA4),
    DEFINE_KEY(RMENU, 0xA5),
    
    DEFINE_KEY(SEMICOLON, 0xBA),
    DEFINE_KEY(PLUS, 0xBB),
    DEFINE_KEY(COMMA, 0xBC),
    DEFINE_KEY(MINUS, 0xBD),
    DEFINE_KEY(PERIOD, 0xBE),
    DEFINE_KEY(SLASH, 0xBF),
    DEFINE_KEY(GRAVE, 0xC0),
    
    KEYS_MAX_KEYS
} keys;

keys translate_keycode(u32 x_keycode) {
    switch (x_keycode) {
        case XK_Escape:
        return KEY_ESCAPE;
        case XK_space:
        running = 0;
        return KEY_SPACE;
        case XK_Prior:
        return KEY_PRIOR;
        case XK_Next:
        return KEY_NEXT;
        case XK_End:
        return KEY_END;
        case XK_Home:
        return KEY_HOME;
        case XK_Left:
        return KEY_LEFT;
        case XK_Up:
        return KEY_UP;
        case XK_Right:
        return KEY_RIGHT;
        case XK_Down:
        
        
        return KEY_DOWN;
        case XK_a:
        case XK_A:
        pos[0] -= 10 * delta;
        return KEY_A;
        case XK_b:
        case XK_B:
        return KEY_B;
        case XK_c:
        case XK_C:
        return KEY_C;
        case XK_d:
        case XK_D:
        pos[0] += 5 * delta;
        return KEY_D;
        case XK_e:
        case XK_E:
        return KEY_E;
        case XK_f:
        case XK_F:
        return KEY_F;
        case XK_g:
        case XK_G:
        return KEY_G;
        case XK_h:
        case XK_H:
        return KEY_H;
        case XK_i:
        case XK_I:
        return KEY_I;
        case XK_j:
        case XK_J:
        return KEY_J;
        case XK_k:
        case XK_K:
        return KEY_K;
        case XK_l:
        case XK_L:
        return KEY_L;
        case XK_m:
        case XK_M:
        return KEY_M;
        case XK_n:
        case XK_N:
        return KEY_N;
        case XK_o:
        case XK_O:
        return KEY_O;
        case XK_p:
        case XK_P:
        return KEY_P;
        case XK_q:
        case XK_Q:
        return KEY_Q;
        case XK_r:
        case XK_R:
        return KEY_R;
        case XK_s:
        case XK_S:
        pos[1] -= 10 * delta;
        return KEY_S;
        
        case XK_t:
        case XK_T:
        return KEY_T;
        case XK_u:
        case XK_U:
        return KEY_U;
        case XK_v:
        case XK_V:
        return KEY_V;
        case XK_w:
        case XK_W:
        pos[1] += 10 * delta;
        return KEY_W;
        case XK_x:
        case XK_X:
        return KEY_X;
        case XK_y:
        case XK_Y:
        return KEY_Y;
        case XK_z:
        case XK_Z:
        return KEY_Z;
        
        default:
        return KEY_NUMPAD0;
    }
}
