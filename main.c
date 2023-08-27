#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "List.h"
#include "utils.h"

#define BUFFER_SIZE 1024 * 1024 * 50 // 50MB buffer

int main(int argc, char const *argv[])
{
    FILE *input = fopen(argv[1], "r");
    char *buffer = malloc(BUFFER_SIZE);
    list *words = List();

    if (!input || !buffer || !words)
    {
        printf("Erro ao inicializar a aplicação. Saindo...");
        exit(1);
    }

    puts("Lendo arquivo...");

    while (fread(buffer, 1, BUFFER_SIZE, input))
    {
        puts("Removendo lixo...");
        clean_line(buffer);

        puts("Tokenizando palavras...");
        list* raw_words = split(buffer, " ");

        puts("Filtrando...");
        forEach(raw_words, (
        {
            void __fn__(char* str)
            {
                if ( strlen(str) < 3 || some(words, compare, str) ) return;

                push_back(words, copy(str));
            }
            __fn__;
        }));

        clear_list(raw_words);
        free(raw_words);
    }

    free(buffer);
    fclose(input);

    puts("Ordenando palavras...");
    sort_list(words, (
    {
        bool __fn__(char* str1, char* str2)
        {
            return strcmp(str1, str2) > 0;
        }
        __fn__;

    }));

    // forEach(words, printer);

    puts("Salvando palavras em arquivo...");
    outputList(words);

    clear_list(words);
    free(words);
    
    
    return 0;
}
