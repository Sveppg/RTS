#ifndef FUNCTIONS_H
#define FUNCTIONS_H


int sum_of_digits(char *num);
void trim(char *str);
char *read_line(FILE *f, ssize_t *len);
char **read_file(const char *filename);
void test();
int child_sum(char **numers, int offset, int count);
void gen_workers(char **numbers, int pfd[], int n);

#endif