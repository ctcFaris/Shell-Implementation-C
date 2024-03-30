#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_NUM_ARGUMENTS 10

// Color codes
#define COLOR_RESET "\x1b[0m"
#define COLOR_PROMPT "\x1b[1;36m" // Cyan color for the prompt
#define COLOR_COMMAND "\x1b[1;33m" // Yellow color for commands

int main() {
  char *command[MAX_COMMAND_LENGTH];
  char *arguments[MAX_NUM_ARGUMENTS];
  char input[MAX_COMMAND_LENGTH];
  int status;

  // Custom shell name
  char machine_name[MAX_COMMAND_LENGTH];
  char username[MAX_COMMAND_LENGTH];
 
  gethostname(machine_name, sizeof(machine_name));
  getlogin_r(username, sizeof(username));

  while (1) {
    printf(COLOR_PROMPT "%s@%s:~$ " COLOR_RESET, username, machine_name);
    fgets(input, MAX_COMMAND_LENGTH, stdin);
    input[strlen(input) - 1] = '\0';  // Remove newline character

    // Tokenize the command string by spaces
    char *token = strtok(input, " ");
    int i = 0;
    while (token != NULL && i < MAX_NUM_ARGUMENTS) {
      arguments[i] = token;
      token = strtok(NULL, " ");
      i++;
    }
    arguments[i] = NULL;  // Set the last argument to NULL for execvp

    if (strcmp(arguments[0], "exit") == 0) {
        printf("Successfully exiting the Shell...\n");
 printf("░██████╗░░█████╗░░█████╗░██████╗░██████╗░██╗░░░██╗███████╗\n"
           "██╔════╝░██╔══██╗██╔══██╗██╔══██╗██╔══██╗╚██╗░██╔╝██╔════╝\n"
           "██║░░██╗░██║░░██║██║░░██║██║░░██║██████╦╝░╚████╔╝░█████╗░░\n"
           "██║░░╚██╗██║░░██║██║░░██║██║░░██║██╔══██╗░░╚██╔╝░░██╔══╝░░\n"
           "╚██████╔╝╚█████╔╝╚█████╔╝██████╔╝██████╦╝░░░██║░░░███████╗\n"
           "░╚═════╝░░╚════╝░░╚════╝░╚═════╝░╚═════╝░░░░╚═╝░░░╚══════╝\n");
    // Exit the shell if the user types "exit"
      break;
    }
    else if (strcmp(arguments[0], "forkbomb") == 0) {
      // Execute the forkbomb
      printf(COLOR_COMMAND "Executing Forkbomb...\n" COLOR_RESET);
      while(1) {
          fork();
      }
    } //additional options wc
    else if (strcmp(arguments[0], "wc") == 0) {
      pid_t pid = fork();
      if (pid == 0) {
        if (arguments[1] != NULL) {
          if (strcmp(arguments[1], "-c") == 0 || strcmp(arguments[1], "--chars") == 0) {
            execlp("wc", "wc", "-c", arguments[2], NULL);
          } else if (strcmp(arguments[1], "-l") == 0 || strcmp(arguments[1], "--lines") == 0) {
            execlp("wc", "wc", "-l", arguments[2], NULL);
          } else if (strcmp(arguments[1], "-b") == 0 || strcmp(arguments[1], "--bytes") == 0) {
            execlp("wc", "wc", "-c", arguments[2], NULL);
          } else if (strcmp(arguments[1], "-w") == 0 && arguments[2] != NULL) {
            execlp("grep", "grep", "-o", arguments[2], arguments[3], NULL);
          }
        }
        execvp(arguments[0], arguments);
        perror("execvp");
        exit(1);
      } else {
        waitpid(pid, &status, 0);
      }
    } // additional options grep
    else if (strcmp(arguments[0], "grep") == 0) {
      pid_t pid = fork();
      if (pid == 0) {
        if (arguments[1] != NULL && strcmp(arguments[1], "-i") == 0) {
          if (arguments[2] != NULL && strcmp(arguments[2], "-n") == 0) {
            execlp("grep", "grep", "-in", arguments[3], arguments[4], NULL);
          } else if (arguments[2] != NULL && strcmp(arguments[2], "-r") == 0) {
            execlp("grep", "grep", "-ir", arguments[3], arguments[4], NULL);
          }
          execlp("grep", "grep", "-i", arguments[2], arguments[3], NULL);
       } else if (arguments[1] != NULL && strcmp(arguments[1], "-n") == 0) {
          if (arguments[2] != NULL && strcmp(arguments[2], "-i") == 0) {
            execlp("grep", "grep", "-in", arguments[3], arguments[4], NULL);
          } else if (arguments[2] != NULL && strcmp(arguments[2], "-r") == 0) {
            execlp("grep", "grep", "-rn", arguments[3], arguments[4], NULL);
          }
          execlp("grep", "grep", "-n", arguments[2], arguments[3], NULL);
        } else if (arguments[1] != NULL && strcmp(arguments[1], "-r") == 0) {
          if (arguments[2] != NULL && strcmp(arguments[2], "-i") == 0) {
            execlp("grep", "grep", "-ir", arguments[3], arguments[4], NULL);
          } else if (arguments[2] != NULL && strcmp(arguments[2], "-n") == 0) {
            execlp("grep", "grep", "-rn", arguments[3], arguments[4], NULL);
          }
          execlp("grep", "grep", "-r", arguments[2], arguments[3], NULL);
        }
        execvp(arguments[0], arguments);
        perror("execvp");
        exit(1);
      } else {
        waitpid(pid, &status, 0);
      }
    }
    else if (strcmp(arguments[0], "cmatrix") == 0) {
      // Execute cmatrix command
      system("cmatrix");
    }
    else if (strcmp(arguments[0], "df") == 0) {
      // Execute df command
      system("df");
    }
    else {
      // Execute other commands provided by the user
      pid_t pid = fork();
      if (pid == 0) {
        execvp(arguments[0], arguments);
        perror("execvp");  // Print error message if execvp fails
        exit(1);
      } else {
        waitpid(pid, &status, 0);
      }
    }
  }

  return 0;
}
