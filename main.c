// lush - lucky implement of shell

// c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// linux
#include <sys/wait.h>
#include <unistd.h>



// builtin
#include "builtin.h"

////////////////////////////////////////////////////////
void lush_loop(void);
char* lush_readline(void);
char** lush_splitline(char *line);
int lush_launch(char **args);
int lush_exe(char **args);

////////////////////////////////////////////////////////
int main(int argc , char **argv)
{
	//load config files
	//

	lush_loop();
	
	// clean and shutdown
	//
	return EXIT_SUCCESS;
	
}

void lush_loop(void)
{
	char *line;
	char **args;
	int status;

	do {
		printf("lush> ");
		line = lush_readline();  	//read
		args = lush_splitline(line);	//split
		status = lush_exe(args);	//execute
		
		free(line);
		free(args);

	}while(status);
}

#define LUSH_RL_BUFSIZE 1024
// read from stdin to buffer
char* lush_readline(void)
{
	int bufsize = LUSH_RL_BUFSIZE;
	int position = 0;
	char* buffer = malloc(sizeof(char)*bufsize);
	int c;

	if(!buffer)
	{
		fprintf(stderr,"lush: allocation error.\n");
		exit(EXIT_FAILURE);
	}

	while(1)
	{
		c = getchar();
		if(c==EOF || c =='\n')
		{
			buffer[position++] = '\0';
			return buffer;
		}
		else
		{
			buffer[position++] = c;
		}

		if(position >= bufsize)
		{
			bufsize += LUSH_RL_BUFSIZE;
			buffer = realloc(buffer, bufsize);
			if(!buffer)
			{
				fprintf(stderr, "lush: allocation error.\n");
				exit(EXIT_FAILURE);
			}
		
		}
	}

}

#define LUSH_TOK_BUFSIZE 64
#define LUSH_TOK_DELIM " \t\r\n\a"

char** lush_splitline(char *line)
{
	int bufsize = LUSH_TOK_BUFSIZE;
	int position = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if(!tokens)
	{
		fprintf(stderr, "lush: allocation error.\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, LUSH_TOK_DELIM); // first call strtok
	while(token != NULL)
	{
		tokens[position++] = token;
		if(position >= bufsize)
		{
			bufsize += LUSH_TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if(!tokens)
			{
				fprintf(stderr,"lush: allocation error.\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, LUSH_TOK_DELIM);	// multi call strtok
	}	
	tokens[position] = NULL;
	return tokens;
}



int lush_launch(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if(pid == 0)
	{
		// in child process
		if(execvp(args[0], args) == -1)
			perror("lush");
		exit(EXIT_FAILURE);

	}
	else if(pid < 0)
	{
		// error fork happen
		perror("lush");
	}
	else
	{
		// in parent process
		do{
			wpid = waitpid(pid, &status, WUNTRACED);

		}while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return 1;
}



int lush_exe(char **args)
{
	int i;
	if(args[0] == NULL)
	{
		return 1;
	}
	for(i=0; i< lush_num_builtins();i++)
	{
		if(strcmp(args[0], builtin_str[i]) == 0)
			return (*builtin_func[i])(args);
	}
	return lush_launch(args);
}


//////////////////////////////////////////////////////////////////////////









































































































