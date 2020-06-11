#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>


void handle_cmd_shell(void);

void handle_cmd_line(char**, int);

void receive_reply(void);
