#include "flags.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct element element;
typedef struct element {
    flag* flag;
    struct element* next;
} element;

element flags = { .flag=NULL, .next=NULL};
char** flag_argv = NULL;
int flag_positional_index = 0;
int flag_positional_count = 0;
char* help_text = NULL;

int start_with(const char* base, const char* pattern){
    for(int i=0; pattern[i]!='\0'; i++){
        if(pattern[i]!=base[i]) return 0;
    }
    return 1;
}

void flag_help(){
    element* tmp = flags.next;
    if(help_text) printf("%s\n", help_text);
    int longest = 0;
    while(tmp->next != NULL){
        int i = 0;
        while(tmp->flag->name[i++]!='\0');
        longest = longest<i ? i : longest;
        tmp = tmp->next;
    }
    tmp = flags.next;
    while(tmp->next != NULL){
        printf("\t%-*s%c %s\n",
            longest, tmp->flag->name,
            tmp->flag->description ? ':' : ' ',
            tmp->flag->description ? tmp->flag->description : ""
        );
        tmp = tmp->next;
    }
    printf("\t%-*s%c %s\n",
        longest, tmp->flag->name,
        tmp->flag->description ? ':' : ' ',
        tmp->flag->description ? tmp->flag->description : ""
    );
}

void flag_parse(int argc, char** argv, char* help){
    flag_argv = argv;
    flag_positional_index = argc;
    help_text = help;

    for(int i = 1; i<argc; i++){
        element* tmp = flags.next;
        if(start_with(argv[i], "--help")) flag_help();
        int ispositional = 1;
        while(tmp->next != NULL){
            if(start_with(argv[i], tmp->flag->name)){
                tmp->flag->index = i;
                ispositional = 0;
            }
            tmp = tmp->next;
        }
        if(start_with(argv[i], tmp->flag->name)){
            tmp->flag->index = i;
            ispositional = 0;
        }
        if (ispositional){
            if(flag_positional_count==0) flag_positional_index = i;
            flag_positional_count++;
        }
    }
}

int flag_positionals_index(){
    return flag_positional_index;
}

int flag_positionals_count(){
    return flag_positional_count;
}

flag* flag_add(const char* name, const char* description){
    element* tmp = &flags;
    while(tmp->next != NULL) tmp = tmp->next;

    flag* new_flag = (flag*)malloc(sizeof(flag));
    new_flag->name = name;
    new_flag->description = description;
    new_flag->index = -1;
    
    element* next_element = (element*)malloc(sizeof(element));
    next_element->next = NULL;
    next_element->flag = new_flag;
    
    tmp->next = next_element;
    return new_flag;
};

void flag_destory(){
    element* next = flags.next;
    while(next->next != NULL){
        element* tmp = next->next;
        free(next->flag);
        free(next);
        next = tmp;
    }
    free(next->flag);
    free(next);
}

int flag_has(flag* flag){
    return flag->index==-1 ? 0 : 1;
}

char* clean_string(char* in){
    char* start = in;
    for(int i=0; in[i]!='\0'; i++){
        if(in[i]=='='){
            start = &in[i+1];
            break;
        }
        else start = &in[i+1];
    }
    return start;
}

int flag_as_int(flag* flag){
    return atoi(clean_string(flag_argv[flag->index]));
}
float flag_as_float(flag* flag){
    return atof(clean_string(flag_argv[flag->index]));
}
char* flag_as_string(flag* flag){
    return clean_string(flag_argv[flag->index]);
}