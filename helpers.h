#include <stddef.h>

#ifndef HELPERS_H
#define HELPERS_H

void print(const char* message);
void print_usage();
void show_logs();
void get_timestamp(char *buffer);
void log_success(const char *message);
void int_to_str2(int num, char *buf);

#endif