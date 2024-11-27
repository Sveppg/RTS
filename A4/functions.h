#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int sum_of_digits(char *num);
void test_sum();
char *read_line(FILE *f, ssize_t *len);
void test_read();
char **read_file(const char *filename);
void test_read_file();

#endif