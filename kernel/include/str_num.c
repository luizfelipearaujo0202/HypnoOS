int strcmp(char *s1, char *s2) {

    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0') {

        if (s1[i] != s2[i]) {
            return s1[i] - s2[i];
        }

        i++;
    }

    return s1[i] - s2[i];
}

int strlen(char *texto) {
    int i = 0;
    while (texto[i] != '\0') {
        i++;
    }
    return i;
}

void strcpy(char *dest, char *src) {
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    dest[i] = '\0';
}

void strcat(char *str1, char *str2) {
    int i = 0;
    int j = 0;

    // vai até o fim da primeira string
    while (str1[i] != '\0') {
        i++;
    }

    // copia a segunda string
    while (str2[j] != '\0') {
        str1[i] = str2[j];
        i++;
        j++;
    }

    str1[i] = '\0';
}



int atoi_simple(char* str) {
    int resultado = 0;

    while (*str)
    {
        resultado = resultado * 10 + (*str - '0');
        str++;
    }

    return resultado;
}

char* itoa_simple(int num, char* buffer) {
    int i = 0;

    if (num == 0)
    {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    while (num > 0) {
        buffer[i] = (num % 10) + '0';
        num /= 10;
        i++;
    }

    buffer[i] = '\0';


    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;

        start++;
        end--;
    }
}

int is_number(char* str) {
    while (*str)
    {
        if (*str < '0' || *str > '9') {
            return 0;
        }
        str++;
    }
    return 1;
}

int numcmp(int num, int num2) {
    if (num < num2) {
        return 1;
    }
    else return 0;
}

int split(char *line, char **argv) {
    int argc = 0;

    while (*line){

        while((*line) == ' ') {
            line ++;
        }

        if (*line == '\0') {
            break;
        }

        argv[argc++] = line;

        while (*line && *line != ' ') {line ++;}

        if (*line){
            *line = '\0';
            line++;
        }
    }

    return argc;
}