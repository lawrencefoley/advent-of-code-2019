#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calcFuel(int mass) {
	return mass / 3 - 2;
}

int main() {
 	printf("%s\n", "Day 1");

 	char inputFileName [] = "input.txt";
 	FILE * inputStream;
    inputStream = fopen(inputFileName, "r");
    
    // Check if file has been opened
    if(!inputStream)
    {
        printf("Can't open file %s", inputFileName);
        exit(1);   
    }
    
    // Read all the ints in the file
    int totalNums = 10;
    int * nums;
    nums = malloc(sizeof(int) * 10);
    int temp = 0;
    int index = 0;

    while(fscanf(inputStream, " %d", &temp) != EOF)
    {
    	if(index >= totalNums) {
    		// need to increase array size
    		int * tempArray;
    		totalNums *= 2;
    		tempArray = (int *)calloc(totalNums, sizeof(int));
    		memcpy(tempArray, nums, index * sizeof(int));
    		free(nums);
    		nums = tempArray;
    	}
        nums[index] = temp;
        index++;
    }
    // Close the file
    fclose(inputStream);

    long total = 0;
    int i;
    for(i = 0; i < index; i++) {
    	total += calcFuel(nums[i]);
    }

    printf("%d\n", total);

	return 0;
}
