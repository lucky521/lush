
#include <unistd.h>
#include <stdio.h>


#include "builtin.h"
/*
int lush_num_builtins();
int lush_cd(char **args);
//int lush_help(char **args);
int lush_exit(char **agrs);
*/

char *builtin_str[] = {
	"cd",
	//"help",
	"exit"
};

int (*builtin_func[])(char**) = {
	&lush_cd,
	//&lush_help,
	&lush_exit
};



int lush_num_builtins()
{
	return sizeof(builtin_str) / sizeof(char*);
}


int lush_cd(char **args)
{
	if(args[1] == NULL)
	{
		fprintf(stderr, "lush: expected argument to \"cd\" \n");
	}
	else
	{
		if (chdir(args[1]) != 0)
			perror("lush");
	}
	return 1;
}



int lush_exit(char **args)
{
	return 0;
}
