#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>

#define STACK_SIZE (1024 * 1024)

static char child_stack[STACK_SIZE];
char* const child_args[] = {
  "/bin/bash", NULL
};

int child_main(void* args) {
  printf("在子进程中\n");
  //  sethostname("NewNamespace", 12);
  execv(child_args[0], child_args);
  return 1;
}

int main() {
  printf("程序开始：\n");
  int child_pid = clone(child_main, child_stack + STACK_SIZE, SIGCHLD, NULL);
  /* int child_pid = clone(child_main, child_stack + STACK_SIZE, CLONE_NEWIPC | SIGCHLD, NULL); */
  /* we can not set CLONE_NEWPIC it will return -1*/
  printf("child_pid: %d \n", child_pid);
  waitpid(child_pid, NULL, 0);
  printf("己退出\n");
  return 0;
}
