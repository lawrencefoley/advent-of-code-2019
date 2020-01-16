#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arraylist.h"

int main() {
    printf("Day 3\n");

	char * inputFileName = "input.txt";
	FILE * inputStream;
	inputStream = fopen(inputFileName, "r");

	// Check if file has been opened
	if (!inputStream)
	{
		printf("Can't open file %s", inputFileName);
		exit(1);
	}

	char fileString[1024000];
    // Allocate memory for an array of char pointer pointers
	int numArrays = 2;
	int currentArraySize = 100;
	int defaultStringLength = 5;
	char ***inputData = malloc(numArrays * sizeof(char **));
	int index = 0;
	int currentStringIndex = 0;
	// Read each line of file
	while (fscanf(inputStream, "%s", fileString) != EOF)
	{
		if(index >= numArrays) {
			printf("We need to realloc memory for more arrays");
			exit(1);
		}
		inputData[index] = calloc(currentArraySize, sizeof(char*));
        // Split the line on commas
        char* token = strtok(fileString, ",");
		char* currentString;
        while(token != NULL)
        {
			if(currentStringIndex >= currentArraySize) {
				currentArraySize *= 2;
				inputData[index] = (char**)realloc(inputData[index], currentArraySize * sizeof(char*));
			}
			// Allocate memory for the current string
			inputData[index][currentStringIndex] = calloc(defaultStringLength, sizeof(char));
			// Copy the string int the new memory
			strcpy(inputData[index][currentStringIndex], token);
            
            // Pass null to go to next token in the file string
            token = strtok(NULL, ",");	
			currentStringIndex++;
        }
		currentStringIndex = 0;
		index++;
	}
	// Close the file
	fclose(inputStream);

	int i;
	int j;
	for(i = 0; i < index; i++)
    {
		// TODO Keep track of each array size
        for(j = 0; j <= 300; j++) {
            printf("Data at array[%d][%d]: \"%s\", address=%p\n", i, j, inputData[i][j], &inputData[i][j]);
            free(inputData[i][j]);
        }
        free(inputData[i]);
    }
    free(inputData);


    exit(0);
}

