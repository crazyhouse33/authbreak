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
char **argv_vector_from_string (char* input, size_t* given_argc){
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
//TODO make it cross platform
char** get_envp(){
	return environ;

}

char** dup_arg_vector(char ** vec){
	size_t size= get_vector_count(vec)+1;
	char** res= malloc(sizeof(char*)* size);
	memcpy(res, vec, size*sizeof(char*));
	return res;


}

void concatenate_arg_vector(char*** vec1, char** vec2){
	size_t size_1=get_vector_count(*vec1);
	size_t size_2=get_vector_count(vec2);
	size_t new_size =  size_1 + size_2;
	*vec1=realloc(*vec1,sizeof(char*)* (new_size+1));
	memcpy((*vec1+size_1),vec2, (size_2+1)* sizeof(char*));
}

char** concatenation_arg_vector(char** vec1, char** vec2){
	char** vec1_clone= dup_arg_vector(vec1);
	concatenate_arg_vector(&vec1_clone,vec2);
	return vec1_clone;
}




char** get_envp_appended(char** vector){
	char ** argp=get_envp();
	return concatenation_arg_vector(argp, vector);
}


//This maccro factorize the code
#define DEDUP_CODE_MODE( fd, string)\
	if (mode[fd] != DEFAULT_BUFFERING){\
		at_least_one=true;\
		end_argp[current++]= sstrcat_copy(string, mode[fd]);\
	}\

char** build_stdbuf_exec_envp(char** mode){
#if ! LIBSTDBUF_IS_FOUND
		return get_envp();
#else
	char** end_argp = malloc(sizeof(char*) * 5);

	size_t current=1;
	bool at_least_one=false;
	
	DEDUP_CODE_MODE(0, "_STDBUF_I=");
	DEDUP_CODE_MODE(1, "_STDBUF_O=");
	DEDUP_CODE_MODE(2, "_STDBUF_E=");

	if (at_least_one)
		end_argp[0]= "LD_PRELOAD="LIBSTDBUF_PATH; // set by compilation
	else
		current=0;


	end_argp[current]=NULL;	
	return get_envp_appended(end_argp);
#endif
}

