#pragma once

#include "types.h"

enum input_key{
    
    INPUT_KEY_LEFT,
    INPUT_KEY_RIGHT,
    INPUT_KEY_UP,
    INPUT_KEY_DOWN,
    INPUT_KEY_ESCAPE
        
        
};

enum key_state{
    
    KS_UNPRESSED,
    KS_PRESSED,
    KS_HELD
};

struct input_state{
    
    key_state left;
    key_state right;
    key_state up;
    key_state down;
    key_state escape;
};


void update_key_state(u8 current_state,key_state * key_context){
    if(current_state){
        
        if(*key_context > 0)
            
            *key_context = KS_HELD;
        else 
            *key_context  = KS_PRESSED;
        
    }else{
        
        *key_context = KS_UNPRESSED;
    }
    
    
};
