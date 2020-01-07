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

	int * programData;
	programData = malloc(sizeof(int) * 10);
	char fileString[1024000];

	char inputStrings[100][4];
	int index = 0;

    ArrayList *arrayList = arraylist_new(10);

	// Read each line of file
	while (fscanf(inputStream, "%s", fileString) != EOF)
	{
        // Split the line on commas
        char * token = strtok(fileString, ",");
        char * currentString;
        while(token != NULL)
        {
//            char *temp = "    ";
//            strcpy(&temp, token);
// TODO This isn't working
            arraylist_append(arrayList, *token);
            index++;
            // Pass null to go to next token
            token = strtok(NULL, ",");
        }
	}
	// Close the file
	fclose(inputStream);



	// Split the string on commas
	char * token = strtok(fileString, ",");
	int currentNum = 0;
	while( token != NULL )
	{
		if(sscanf(token, "%d", &currentNum) != 1) {
			printf("Error converting number: %s\n", token);
			exit(2);
		}

		// Pass null to go to next token
		token = strtok(NULL, ",");
	}


    exit(0);
}

