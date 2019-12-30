#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"


int main() {
	printf("Day 2\n");

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
	char fileString[1024];

	// Read the file to a string
	while (fscanf(inputStream, "%s", &fileString) != EOF)
	{
		printf("Reading data:");
		printf("%s\n", fileString);
	}
	// Close the file
	fclose(inputStream);

	Vector v;
	vInitialize(&v);

	// Split the string on commas
	char * token = strtok(fileString, ",");
	int currentNum = 0;
	while( token != NULL )
	{
		if(sscanf(token, "%d", &currentNum) != 1) {
			printf("Error converting number: %s\n", token);
			exit(2);
		}
		vPushBack(&v, currentNum);
		// Pass null to go to next token
		token = strtok(NULL, ",");
	}

	int i;
	currentNum = 0;
	for (i = 0; i < v.size; i++) {
		vGet(&v, i, &currentNum);
		printf("%d: %d\n", i, currentNum);
	}

    // Run the Intcode program
    int opcode = 0;
    int index1 = 0;
    int index2 = 0;
    int index3 = 0;
    int arg1 = 0;
    int arg2 = 0;
    int result = 0;
    for(i = 0; i < v.size; i+=4) {
        vGet(&v, i, &opcode);
        vGet(&v, i + 1, &index1);
        vGet(&v, i + 2, &index2);
        vGet(&v, i + 3, &index3);

        vGet(&v, index1, &arg1);
        vGet(&v, index2, &arg2);

        if(opcode == 99) {
            printf("opcode 99, exiting\n");
            break;
        }
        else if(opcode == 1) {
            result = arg1 + arg2;
        }
        else if(opcode == 2) {
            result = arg1 * arg2;
        }
        else {
            printf("Error: Unknown opcode=%d\n", opcode);
        }

        printf("result=%d\n", result);
        vSet(&v, index3, result);
    }


    for (i = 0; i < v.size; i++) {
		vGet(&v, i, &currentNum);
		printf("%d: %d\n", i, currentNum);
	}

	// Free memory
	vFinalize(&v);
	exit(0);
}
