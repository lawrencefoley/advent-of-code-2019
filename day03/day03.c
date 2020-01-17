#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int manhattanDistance(int x1, int y1, int x2, int y2) {
	// TODO
	int temp = abs(x1 - x2) + abs(y1 - y2);
	return temp;
}

int main() {
    printf("Day 3\n");

	char * inputFileName = "test1.txt";
	FILE * inputStream;
	inputStream = fopen(inputFileName, "r");

	// Check if file has been opened
	if (!inputStream)
	{
		printf("Can't open file %s", inputFileName);
		exit(1);
	}

	char fileString[1024000];
	int numArrays = 2;
	int currentArraySize = 100;
	int defaultStringLength = 5;
	// Allocate memory for an array of char pointer pointers
	char ***inputData = malloc(numArrays * sizeof(char **));
	// Keep trach of the lenth of each array
	int * stringArrayLengths = (int*)malloc(numArrays * sizeof(int));
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
		stringArrayLengths[index] = currentStringIndex;
		currentStringIndex = 0;
		index++;
	}
	// Close the file
	fclose(inputStream);


	int matrixSize = 1000;
	int ** matrix = (int**)calloc(matrixSize, sizeof(int*));
	int i;
	int j;
	for(i = 0; i <= matrixSize; i++) {
		matrix[i] = (int*)calloc(matrixSize, sizeof(int));
	}

	// Fill the matrix with .
	// for(i = 0; i <= matrixSize; i++) {
	// 	for(j = 0; j < matrixSize; j++) {
	// 		matrix[i][j] = 0;
	// 	}
	// }

	// We'll start in the middle of the matrix
	int matrixMiddle = matrixSize / 2;
	int currentX = matrixMiddle;
	int currentY = matrixMiddle;
	int minX = matrixSize;
	int minY = matrixSize;
	int minDistance = matrixSize;

	int arrayIndex;
	for(arrayIndex = 0; arrayIndex < numArrays; arrayIndex++) {
        for(j = 0; j < stringArrayLengths[arrayIndex]; j++) {
            char * currentString = inputData[arrayIndex][j];
			char directionChar = currentString[0];
			int lineLength = atoi(strncpy(currentString, currentString + 1, defaultStringLength));

			if(directionChar == 'U') {
				for(i = currentY; i < currentY + lineLength; i++) {
					if(matrix[i][currentX] != 0 && manhattanDistance(matrixMiddle, matrixMiddle, currentX, i) < minDistance) {
						minDistance = manhattanDistance(matrixMiddle, matrixMiddle, currentX, i);
					}
					matrix[i][currentX] = arrayIndex + 1;
				}
				currentY = i;
			}
			else if (directionChar == 'R') {
				for(i = currentX; i < currentX + lineLength; i++) {
					if(matrix[currentY][i] != 0 && manhattanDistance(matrixMiddle, matrixMiddle, i, currentY) < minDistance) {
						minDistance = manhattanDistance(matrixMiddle, matrixMiddle, i, currentY);
					}
					matrix[currentY][i] = arrayIndex + 1;
				}
				currentX = i;
			}
			else if (directionChar == 'D') {
				for(i = currentY; i > currentY - lineLength; i--) {
					if(matrix[i][currentX] != 0 && manhattanDistance(matrixMiddle, matrixMiddle, currentX, i) < minDistance) {
						minDistance = manhattanDistance(matrixMiddle, matrixMiddle, currentX, i);
					}
					matrix[i][currentX] = arrayIndex + 1;
				}
				currentY = i;
			}
			else if (directionChar == 'L') {
				for(i = currentX; i > currentX - lineLength; i--) {
					if(matrix[currentY][i] != arrayIndex + 1 && matrix[currentY][i] != 0 && manhattanDistance(matrixMiddle, matrixMiddle, i, currentY) < minDistance) {
						minDistance = manhattanDistance(matrixMiddle, matrixMiddle, i, currentY);
					}
					matrix[currentY][i] = arrayIndex + 1;
				}
				currentX = i;
			}
			else {
				printf("Invalid direction char %c", directionChar);
				exit(1);
			}
        }
    }







	// Print matrix
	for(i = 0; i <= matrixSize; i++) {
		for(j = 0; j < matrixSize; j++) {
			// printf("%d", matrix[i][j]);
		}
		// printf("\n");
	}



	// Free the inputData memory
	for(i = 0; i < index; i++)
    {
        for(j = 0; j < stringArrayLengths[i]; j++) {
            // printf("Data at array[%d][%d]: \"%s\", address=%p\n", i, j, inputData[i][j], &inputData[i][j]);
            free(inputData[i][j]);
        }
        free(inputData[i]);
    }
    free(inputData);

	printf("Min distance: %d", minDistance);
    exit(0);
}
