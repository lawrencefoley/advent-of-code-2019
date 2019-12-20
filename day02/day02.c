#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"


int main() {
	printf("Day 2\n");

	char * inputFileName = "test1.txt";
	FILE * inputStream;
	inputStream = fopen(inputFileName, "r");

	// Check if file has been opened
	if (!inputStream)
	{
		printf("Can't open file %s", inputFileName);
		exit(1);
	}

	int totalNums = 10;
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

	// Free memory
	vFinalize(&v);
}
