#ifndef cmp
#define cmp

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

int split(char *texto, char *argv[15]) {
    int i = 0;      // lê texto
    int w = 0;      // palavra atual (argv)
    int j = 0;      // letra dentro da palavra

    static char word[32]; // buffer da palavra

    while (texto[i] != '\0') {

        if (texto[i] != ' ') {
            word[j] = texto[i];
            j++;
        } 
        else {
            word[j] = '\0';
            argv[w] = word;
            w++;
            j = 0;
        }

        i++;
    }

    // última palavra
    word[j] = '\0';
    argv[w] = word;
    w++;

    return w; // quantidade de palavras
}

#endif