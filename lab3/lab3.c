#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define user_inputs 5

int main(void) {
  char *store[user_inputs] = {NULL}; // pointers to store inputs
  char *line = NULL;                 // buffer
  ssize_t n;                         // this will be the characters read
  int first = 0;
  size_t capacity = 0;
  int count = 0;

  while (1) {
    printf("Enter input: ");
    fflush(stdout);
    n = getline(&line, &capacity, stdin);
    if (n == -1)
      break;

    if (n > 0 && line[n - 1] == '\n')
      line[n - 1] = '\0';

    free(store[first]);
    store[first] = strdup(line);

    first = (first + 1) % user_inputs;
    if (count < user_inputs)
      count++;

    if (strcmp(line, "print") == 0) { // what happens when print is typed
      for (int i = 0; i < count; i++) {
        int idx = (count < user_inputs) ? i : (first + i) % user_inputs;
        puts(store[idx]);
      }
    }
  }

  free(line); // free memory
  for (int i = 0; i < user_inputs; i++)
    free(store[i]);
  return 0;
}
