#include <stdio.h>    // for printf, fgets
#include <stdlib.h>   // for exit
#include <string.h>   // for strcspn (remove newline)
#include <sys/wait.h> // for waitpid
#include <unistd.h>   // for fork, execl

int main() {
  char path[256]; // buffer to store the program path the user types in

  while (1) { // infinite loop, runs until you stop with Ctrl+C
    printf("Enter programs to run:\n> ");

    // read a line of input from the user
    if (!fgets(path, sizeof(path), stdin))
      break;

    // remove the newline character from the input (fgets keeps '\n')
    path[strcspn(path, "\n")] = 0;

    // create a new process
    pid_t pid = fork();

    if (pid == 0) {
      // this block runs in the child process
      execl(path, path, NULL); // replace child with the program
      perror("Exec failure");  // only runs if execl() fails
      exit(1);                 // exit child with error
    } else {
      // this block runs in the parent process
      waitpid(pid, NULL, 0); // wait for the child to finish
    }
  }

  return 0; // program ends if loop breaks
}
