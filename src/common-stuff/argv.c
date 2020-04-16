//This functions come for libiberty, wich I just integrated to the sources cause could build there stuff
//https://opensource.apple.com/source/gcc/gcc-926/libiberty/argv.c.auto.html

#include <unistd.h> //environ
#include <concat_string.h> //sstrcat
#include "argv.h"
#include <stdbool.h>
#define EOS '\0'
#define INITIAL_MAXARGC 8	/* Number of args + NULL in initial argv */
#ifdef isspace
#undef isspace
#endif
#define isspace(ch) ((ch) == ' ' || (ch) == '\t')
char **buildargv (char* input, int* given_argc){
  char *arg;
  char *copybuf;
  int squote = 0;
  int dquote = 0;
  int bsquote = 0;
  int argc = 0;
  int maxargc = 0;
  char **argv = NULL;
  char **nargv;

  if (input != NULL)
    {
      copybuf = (char *) alloca (strlen (input) + 1);
      /* Is a do{}while to always execute the loop once.  Always return an
	 argv, even for null strings.  See NOTES above, test case below. */
      do
	{
	  /* Pick off argv[argc] */
	  while (isspace (*input))
	    {
	      input++;
	    }
	  if ((maxargc == 0) || (argc >= (maxargc - 1)))
	    {
	      /* argv needs initialization, or expansion */
	      if (argv == NULL)
		{
		  maxargc = INITIAL_MAXARGC;
		  nargv = (char **) malloc (maxargc * sizeof (char *));
		}
	      else
		{
		  maxargc *= 2;
		  nargv = (char **) realloc (argv, maxargc * sizeof (char *));
		}
	      if (nargv == NULL)
		{
		  if (argv != NULL)
		    {
		      free_arg_vector (argv);
		      argv = NULL;
		    }
		  break;
		}
	      argv = nargv;
	      argv[argc] = NULL;
	    }
	  /* Begin scanning arg */
	  arg = copybuf;
	  while (*input != EOS)
	    {
	      if (isspace (*input) && !squote && !dquote && !bsquote)
		{
		  break;
		}
	      else
		{
		  if (bsquote)
		    {
		      bsquote = 0;
		      *arg++ = *input;
		    }
		  else if (*input == '\\')
		    {
		      bsquote = 1;
		    }
		  else if (squote)
		    {
		      if (*input == '\'')
			{
			  squote = 0;
			}
		      else
			{
			  *arg++ = *input;
			}
		    }
		  else if (dquote)
		    {
		      if (*input == '"')
			{
			  dquote = 0;
			}
		      else
			{
			  *arg++ = *input;
			}
		    }
		  else
		    {
		      if (*input == '\'')
			{
			  squote = 1;
			}
		      else if (*input == '"')
			{
			  dquote = 1;
			}
		      else
			{
			  *arg++ = *input;
			}
		    }
		  input++;
		}
	    }
	  *arg = EOS;
	  argv[argc] = strdup (copybuf);
	  if (argv[argc] == NULL)
	    {
	      free_arg_vector (argv);
	      argv = NULL;
	      break;
	    }
	  argc++;
	  argv[argc] = NULL;

	  while (isspace (*input))
	    {
	      input++;
	    }
	}
      while (*input != EOS);
    }
  *given_argc=argc;
  return (argv);
}


void free_arg_vector (char** vector)
{
  register char **scan;

  if (vector != NULL)
    {
      for (scan = vector; *scan != NULL; scan++)
	{
	  free (*scan);
	}
      free (vector);
    }
}
	
size_t get_vector_count (char ** vector)
{
	size_t argc=0;
	while (vector[argc++]!=NULL);
	return argc - 1 ;
}

extern char** environ;
char** get_argp_appended(char** vector){
	size_t size_vec=get_vector_count(vector);
	size_t size_env=get_vector_count(environ);
	size_t new_size =  size_vec + size_env;
	char** res=malloc(sizeof(char*)*(new_size+1));
	size_t i=0;
	for (; i<size_env; i++)
		res[i]= environ[i];
	
	for (size_t j=0; j<= size_vec; j++)
		res[j+i]= vector[j];
	return res;
}


//This maccro factorize the code
#define DEDUP_CODE_MODE( fd, string)\
	if (mode[fd] != DEFAULT_BUFFERING){\
		at_least_one=true;\
		end_argp[current++]= sstrcat_copy(string, mode[fd]);\
	}\

char** build_argp_stdbuf_env(char* mode[3]){


	char** end_argp = malloc(sizeof(char*) * 5);
	size_t current;

	if (STDBUFLIBPATH==NULL) //STDBUFLIBPATH is set at compilation, and can be unfound. 
		current=0;
	else{

		current=1;
		bool at_least_one=false;
		/* this is the maccro expended	
		if (mode[0] != ((void *)0)){ 
			at_least_one=1; 
			
			end_argp[current++]= strcat("STDBUF_I=", mode[0]); 
		};

		if (mode[1] != ((void *)0)){ 
			at_least_one=1; 
			end_argp[current++]= strcat("STDBUF_O=", mode[1]); 
		};


		if (mode[2] != ((void *)0)){ 
			at_least_one=1; 
			end_argp[current++]= strcat("STDBUF_E=", mode[2]);
		};
		*/
		DEDUP_CODE_MODE(0, "STDBUF_I=");
		DEDUP_CODE_MODE(1, "STDBUF_O=");
		DEDUP_CODE_MODE(2, "STDBUF_E=");



		if (at_least_one)
			end_argp[0]= "LD_PRELOAD="STDBUFLIBPATH; // set by compilation
		else
			current=0;
	}

	end_argp[current]=NULL;	
	return get_argp_appended(end_argp);
}

