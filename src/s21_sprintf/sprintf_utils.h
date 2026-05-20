#ifndef SPRINTF_UTILS_H
#define SPRINTF_UTILS_H

typedef struct {
    unsigned int left_align : 1; // флаг '-'
    unsigned int show_sign : 1;// флаг '+'
    unsigned int space_sign : 1; // флаг ' ' 
    unsigned int alt_format : 1;  // флаг '#'
    unsigned int zero_padding : 1;   // флаг '0'
    int width; // ширина '-'
    int precision; // точность
    char length;// длина
    char specifier; // спецификатор
} formatSpec;


char* int_to_str(char *buf, int num);
int parseFlag(char input);
char* parseWidth(char *input, formatSpec * spec, va_list* args);
char* parsePrecision(char *input, formatSpec * spec, va_list* args);
char* parseLength(char *format, formatSpec * spec);
int parseSpecifier(char input, formatSpec *spec); 
char* parseFormat(char *format, formatSpec * spec, va_list* args,  char **out);
void formatBySpecifier(formatSpec *spec, va_list *args, char **out);


#endif
