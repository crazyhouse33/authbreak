#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void error(char *msg) {
  puts(msg);
  exit(1);
}

int main(int argc, char **argv) {
  puts("Starting main");
  char *user = argv[1];
  char *password = argv[2];

  if (strcmp(user, "admin") != 0)
    error("invalid user");

  if (strcmp(password, "or") != 0)
    error("invalid password");

  char pin[100];
  printf("Hi admin, what's the secret pin?");
  scanf("%s", pin);
  if (strcmp(pin, "1234") != 0)
    error("invalid pin");
  return 0;
}

