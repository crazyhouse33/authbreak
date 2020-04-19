
#include "argv.h"
#include <concat_string.h> //sstrcat
#include <stdbool.h>
#include <string.h>//strncmp
#include <unistd.h> //environ


// This functions come for libiberty, wich I just integrated to the sources cause could build there stuff
// https://opensource.apple.com/source/gcc/gcc-926/libiberty/argv.c.auto.html
#define EOS '\0'
#define INITIAL_MAXARGC 8 /* Number of args + NULL in initial argv */
#ifdef isspace
#undef isspace
#endif
#define isspace(ch) ((ch) == ' ' || (ch) == '\t')
char **arg_vector_from_string(char *input, size_t *argc) {
  char *arg;
  char *copybuf;
  int squote = 0;
  int dquote = 0;
  int bsquote = 0;
  *argc = 0;
  int maxargc = 0;
  char **argv = NULL;
  char **nargv;

  if (input != NULL) {
    copybuf = (char *)alloca(strlen(input) + 1);
    /* Is a do{}while to always execute the loop once.  Always return an
       argv, even for null strings.  See NOTES above, test case below. */
    do {
      /* Pick off argv[argc] */
      while (isspace(*input)) {
        input++;
      }
      if ((maxargc == 0) || (*argc >= (maxargc - 1))) {
        /* argv needs initialization, or expansion */
        if (argv == NULL) {
          maxargc = INITIAL_MAXARGC;
          nargv = (char **)malloc(maxargc * sizeof(char *));
        } else {
          maxargc *= 2;
          nargv = (char **)realloc(argv, maxargc * sizeof(char *));
        }
        if (nargv == NULL) {
          if (argv != NULL) {
            free_arg_vector(argv);
            argv = NULL;
          }
          break;
        }
        argv = nargv;
        argv[*argc] = NULL;
      }
      /* Begin scanning arg */
      arg = copybuf;
      while (*input != EOS) {
        if (isspace(*input) && !squote && !dquote && !bsquote) {
          break;
        } else {
          if (bsquote) {
            bsquote = 0;
            *arg++ = *input;
          } else if (*input == '\\') {
            bsquote = 1;
          } else if (squote) {
            if (*input == '\'') {
              squote = 0;
            } else {
              *arg++ = *input;
            }
          } else if (dquote) {
            if (*input == '"') {
              dquote = 0;
            } else {
              *arg++ = *input;
            }
          } else {
            if (*input == '\'') {
              squote = 1;
            } else if (*input == '"') {
              dquote = 1;
            } else {
              *arg++ = *input;
            }
          }
          input++;
        }
      }
      *arg = EOS;
      argv[*argc] = strdup(copybuf);
      if (argv[*argc] == NULL) {
        free_arg_vector(argv);
        argv = NULL;
        break;
      }
      (*argc)++;
      argv[*argc] = NULL;

      while (isspace(*input)) {
        input++;
      }
    } while (*input != EOS);
  }
  return (argv);
}

void free_arg_vector(char **vector) {
  register char **scan;

  if (vector != NULL) {
    for (scan = vector; *scan != NULL; scan++) {
      free(*scan);
    }
    free(vector);
  }
}

size_t get_vector_count(char **vector) {
  size_t argc = 0;
  while (vector[argc++] != NULL)
    ;
  return argc - 1;
}


char** create_arg_vector(size_t size){
	return malloc(sizeof(char*)*(size+1));
}

char** empty_vec= {NULL};

extern char **environ;
// TODO make it cross platform
char **get_envp() { return environ; }

char **dup_arg_vector(char **vec) {
  size_t size = get_vector_count(vec);
  char **res = create_arg_vector(size);
  memcpy(res, vec, (size+1) * sizeof(char *));
  return res;
}

size_t concatenate_arg_vector(char ***vec1, char **vec2) {
  size_t size_1 = get_vector_count(*vec1);
  size_t size_2 = get_vector_count(vec2);
  size_t new_size = size_1 + size_2;
  *vec1 = realloc(*vec1, sizeof(char *) * (new_size + 1));
  memcpy((*vec1 + size_1), vec2, (size_2 + 1) * sizeof(char *));
  return new_size;
}

char **concatenation_arg_vector(char **vec1, char **vec2) {
  char **vec1_clone = dup_arg_vector(vec1);
  concatenate_arg_vector(&vec1_clone, vec2);
  return vec1_clone;
}

char **get_envp_appended(char **vector) {
  char **argp = get_envp();
  return concatenation_arg_vector(argp, vector);
}

// This is just a macro to factorize code
#define DEDUP_CODE_MODE(fd, string)                                                                                                                                                                    \
  if (mode[fd] != DEFAULT_BUFFERING) {                                                                                                                                                                 \
    at_least_one = true;                                                                                                                                                                               \
    end_argp[current++] = get_concatenation_string(string, mode[fd]);                                                                                                                                              \
  }

char **build_stdbuf_exec_envp(char **mode) {
#if !LIBSTDBUF_IS_FOUND
  return empty_vec;
#else
  char **end_argp = create_arg_vector(4);

  size_t current = 1;
  bool at_least_one = false;

  DEDUP_CODE_MODE(0, "_STDBUF_I=");
  DEDUP_CODE_MODE(1, "_STDBUF_O=");
  DEDUP_CODE_MODE(2, "_STDBUF_E=");

  if (at_least_one){
    end_argp[0] = strdup("LD_PRELOAD=" LIBSTDBUF_PATH); // set by compilation
  }
  else
    current = 0;

  end_argp[current] = NULL;
  return end_argp;
#endif
}


static size_t _envp_get_var_index(char** envp, char* key, size_t len){
	size_t i=-1;
	while (envp[++i] != NULL)
		if ( ! strncmp(envp[i], key,len ))//key is equal
			return i;
	
	return -1;
}

static char* _envp_get_value(char** envp, char* key, size_t len) {
	size_t index= _envp_get_var_index(envp, key, len);
	if (index !=-1)
		return envp[index] + len+1;//ignoring '='
	return NULL;
}


char* envp_get_value(char** envp, char* key) {
	return _envp_get_value(envp, key, strlen(key));
}




size_t merge_envp(char*** envp1, char** envp2, char** key_to_merge, char* separator){
	
	char** to_append= create_arg_vector(get_vector_count(envp2));
	size_t cpt=0;
	size_t i=-1;
	while (envp2[++i] !=NULL){
		char* equal_char= strchr(envp2[i], '=');
		size_t offset= equal_char - envp2[i];
		size_t index= _envp_get_var_index( key_to_merge,envp2[i], offset); //return the index of key to merge
		if (index !=-1){// to merge
			size_t index_in_1= _envp_get_var_index(*envp1, envp2[i], offset);
			if (index_in_1 !=-1){//if it is allready there, concatenate in place and dont append
				char* string_in_1=(*envp1)[index_in_1];
				size_t new_size=concat_char(&string_in_1,separator[index]);
				concat_string_fast_left(&string_in_1, envp2[i]+offset+1, new_size);//we dont copy the =
				continue;//we dont append
			}
		}
		to_append[cpt++]=envp2[i];
	}
	to_append[cpt]=NULL;
	return concatenate_arg_vector(envp1, to_append);
}


char** get_envp_merged( char** envp1, char** envp2, char** key_to_merge, char* separator){
	char** envp1_clone= dup_arg_vector(envp1);;
	merge_envp(&envp1_clone, envp2, key_to_merge,separator);
	return envp1_clone;

}


