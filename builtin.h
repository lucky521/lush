
int lush_num_builtins();
int lush_cd(char **args);
//int lush_help(char **args);
int lush_exit(char **agrs);



extern char *builtin_str[];

extern int (*builtin_func[])(char**);


