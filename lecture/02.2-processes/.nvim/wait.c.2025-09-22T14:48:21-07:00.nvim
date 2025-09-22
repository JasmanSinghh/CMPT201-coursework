#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();
  if (pid == 0) {
    printf("Child \n");
    char *args[] = {"/bin/ls", "-a", "-h", NULL};
    execv("/bin/ls", args);
  } else {
    printf("Parent \n");
    execl("/bin/ls", "/bin/ls", "-a", NULL);
    // why do we have two /bin/ls
    //
  }

  printf("end\n");
}
