#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

typedef enum configOutputType {
    STRING,
    INT
} configOutputType;

typedef struct config_fetch_options {
    char name[MAX_LINE];
    void* value_ptr;
    configOutputType outputType;
} config_fetch_options;

int getConfigurations(char* filename, config_fetch_options* options, int optionsCount)
{
    //read config.ini for values
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open %s\n", filename );
        exit(1);
    }

    char line[MAX_LINE];
    int lineNumber = 0;
    while(fgets(line, sizeof(line), fp) != NULL)
    {
        int lineOffset = 0;
        while(lineOffset < MAX_LINE && line[lineOffset] == ' ') lineOffset++;
        if(lineOffset >= MAX_LINE || line[lineOffset] == '\n' || line[lineOffset] =='#') continue;

        char name[MAX_LINE];
        char value[MAX_LINE];
        memset(name, 0, MAX_LINE);
        memset(value, 0, MAX_LINE);
        int resultOffset = 0;
        while(lineOffset < MAX_LINE && line[lineOffset] != '=')
        {   
            if(line[lineOffset] == '\n')
            {
                printf("%s line %i is missing =\n", filename, lineNumber);
                exit(1);
            }
            if(line[lineOffset] != ' ')
            {
                name[resultOffset] = line[lineOffset];
                resultOffset++;
            }
            lineOffset++;
        }
        lineOffset++;
        resultOffset = 0;
        while(lineOffset < MAX_LINE && line[lineOffset] != '\n')
        {
            if(line[lineOffset] != ' ')
            {
                value[resultOffset] = line[lineOffset];
                resultOffset++;
            }
            lineOffset++;
        }

        int matchingOptionIndex = -1;
        for(int i = 0; i < optionsCount; i++)
        {
            if(!strcmp(options[i].name, name))
            {
                matchingOptionIndex = i;
                break;
            }
        }
        
        if(matchingOptionIndex == -1)
        {
            printf("%s line %i doesn't match any read option.\n", filename, lineNumber);
        }

        switch (options[matchingOptionIndex].outputType) {
            case STRING:
                strcpy((char*)options[matchingOptionIndex].value_ptr, value);
                break;
            case INT:
                *((int*)options[matchingOptionIndex].value_ptr) = atoi(value);
                break;
        }

        lineNumber++;
    }

    fclose(fp);
}

void main()
{
    int x = 0;
    char TEST_TEXT[MAX_LINE];
    memset(TEST_TEXT, 0, MAX_LINE);
    config_fetch_options config_fetch_optionss[] = {
        {"TEST_TEXT", &TEST_TEXT, STRING},
        {"WINDOW_X", &x, INT},
    };
    getConfigurations("config.ini", config_fetch_optionss, 2);

    printf("string: %s\nint: %i", TEST_TEXT, x);
}