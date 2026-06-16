#ifndef STR_NUM_H
#define STR_NUM_H

int strcmp(char *s1, char *s2);
int strlen(char *texto);
void strcpy(char *dest, char *src);
void strcat(char *str1, char *str2);
int atoi_simple(char* str);
char* itoa_simple(int num, char* buffer);
int is_number(char* str);
int numcmp(int num, int num2);
int split(char *line, char **argv);

void print(char* texto);
void print_address(void* p);
void print_int(int valor);
void print_char(char c);

#endif