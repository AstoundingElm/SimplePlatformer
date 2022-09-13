#include "types.h"
#include "platform.h"
#include "files.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "input.h"
#include "time.h"
#include "opengl_function.h"

int main(){
    
    load_functions();
    
    function_get_proc_address();
    
    initialize_window(&x_types, &screen_types_context);
    
    main_loop(&x_types);
    
    return 0;
    
}


