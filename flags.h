#ifndef FLAGS
#define FLAGS

typedef struct {
    const char* name;
    const char* description;
    unsigned int index;
} flag;

void flag_parse(int argc, char** argv, char* help);
void flag_help();
void flag_destory();

flag* flag_add(const char* name, const char* description);
int flag_has(flag* flag);

int flag_as_int(flag* flag);
float flag_as_float(flag* flag);;
char* flag_as_string(flag* flag);
int flag_positionals_index();
int flag_positionals_count();

#endif