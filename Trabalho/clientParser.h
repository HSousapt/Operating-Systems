#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>


ssize_t readln(int, char*);

void send_request(char*);

void handle_cmd_shell(char*);

void handle_cmd_line(char**, int);
