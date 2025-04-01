#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "commands.h"

#define BUF_SIZE 256

#define LOG_AND_PRINT(cmd, fmt, ...) \
    do { \
        char _buf[BUF_SIZE]; \
        snprintf(_buf, BUF_SIZE, fmt, ##__VA_ARGS__); \
        log_command(cmd, _buf); \
    } while (0)
