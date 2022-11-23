# Flags
A simple argument parser written in C, similar to the standard flag module in Golang.
## Usage
### Setup
- `void  flag_parse(int  argc, char**  argv, char*  help);` 
Parses the added arguments.

- `void  flag_help();`
Prints the provided help text + flag descriptions.

- `void  flag_destory();`
Frees the flags at the end.

- `flag*  flag_add(const  char*  name, const  char*  description);`
Adds a flag. The returned struct is later used to access the value of the flag
- `int  flag_has(flag*  flag);`
Checks if the given flag was found.
### Accessing the values
- `int  flag_as_int(flag*  flag);`
- `float  flag_as_float(flag*  flag);`
- `char*  flag_as_string(flag*  flag);`

### Positional arguments
- `int  flag_positionals_index();`
Returns the index of the first unknown token.

- `int  flag_positionals_count();`
Returns how many unknown tokens are there.
