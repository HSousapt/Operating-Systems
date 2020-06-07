#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <assert.h>
#include <sys/wait.h>
#include <signal.h>
#include "task.h"

void handle_client_request(char*, Tasks*);

ssize_t readln(int, char*);
