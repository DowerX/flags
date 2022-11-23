#include <stdio.h>
#include "flags.h"

int main(int argc, char** argv){
    flag* intarg = flag_add("--int", "An integer.");
    //flag* intarg = flag_add("--int", NULL);
    flag* stringarg = flag_add("--string", "A string.");
    flag* floatarg = flag_add("--float", "A float.");
    flag_parse(argc, argv, "Help: i'am terribly depressed");
    //flag_parse(argc, argv, NULL);

    if(flag_has(intarg)&&flag_has(floatarg)&&flag_has(stringarg)){
        printf(
            "int: %d, float: %f, string:%s\n",
            flag_as_int(intarg),
            flag_as_float(floatarg),
            flag_as_string(stringarg)
        );

        printf("positionals: %d\n", flag_positionals_count());
        for(int i = flag_positionals_index(); i<argc; i++){
            printf("\t%s\n", argv[i]);
        }
    }
    else{
        flag_help();
    }

    flag_destory();
    return 0;
}