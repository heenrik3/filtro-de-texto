double calculatePercentage(long total, long current)
{
    return (double) ((double)current / (double)total) * 100.0;
}
void clean_line(char *line)
{
    for (int c = 0; line[c]; c++)
    {
        if (!isalpha(line[c]) || line[c] == '\n')
        {
            line[c] = ' ';
            continue;
        }

        line[c] = tolower(line[c]);
    }
}

void printer(void* item)
{
    printf("%s\n", (char*)item);
}

char* copy(char *str1)
{
    int size = strlen(str1) + 1;
    char* word = malloc(size);
    if (!word)
    {
        printf("Error allocating newWord");
        return NULL;
    }

    memcpy(word, str1, size);

    return word;
}

bool compare(char *str1, char *str2)
{
    return strcmp(str1, str2) == 0;
}

void* split(char *line, char delim[])
{
    list* l = List();

    char* token = strtok(line, delim);

    while (token)
    {
        push_back(l, copy(token));

        token = strtok(NULL, delim);
    }

    return l;
}

void outputList(list *words)
{
    FILE* output = fopen("output.txt", "w");

    forEach(words, (
    {
        void __fn__(char *word)
        {
            fprintf(output, "%s\n", word);
        }
        __fn__;
    }));

    fclose(output);
}

long getFileSize(FILE *f)
{
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    return size;
}


