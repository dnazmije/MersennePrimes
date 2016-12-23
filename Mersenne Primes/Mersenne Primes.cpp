// Mersenne Primes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h> // Using openMP for the parallel part of the app
#include <time.h> 

const int elements = 500; // Number of emelents in the prime array
const int elementsMersenne = 100; //Number of elements in Mersenne array
int primeArray[elements], mersenneArray[elementsMersenne]; //Arrays
int limit; //Limit for the primes

int detectPrime(int number) //Function for detecting if a number is prime
{
	int i;
	for (i = 2; i <= number / 2; i++)
	{
		if (number % i == 0)
			return 0;
	}
	return 1;
}

void printArray (int nameArray[], int boundary) //Funtion to print an array
{
	int i;
	for (i = 0; i< boundary; i++)
	{
		printf("%d\n", nameArray[i]);
	}
}

void askForNumbers() //Asking the user for a number that will be the limit to compute the primes
{
	printf("***This program is developed by Nazmije Denkoski and Nikolina Gjoreska \n Fall 2014. \n***The program computes and shows Mersenne primes in interval given by the user.\n\n");

	printf("Please, enter a number which will be the limit to compute the primes. \n");
	scanf_s("%d", &limit);

	if (iswalpha(limit) || limit <= 0) // if the input is not letter or less and equal to zero, show wrong input 
		printf("Wrong input!");
	else // otherwise, print the numbers that are one less than a power of 2
	{
		printf("\nIn %d numbers which are one less than a power of two, the program will find \nseveralMersenne primes.\n", limit);
		printf("\nFirstly, showing the numbers that are one less than a power of two or (2^n) - 1.\n\n");
	}
}


int main()
{
	askForNumbers(); // Calling askForNumbersFunction
	clock_t time = clock(); // start counting the time from here
	// time function is not included in the input operation
	int m, mersenne, k = 0;

#pragma omp parallel for private (mersenne, m) schedule (dynamic) // Using parallel for loop to calculate the Mersenne primes and setting the scheduale to dynamic
	for (m = 0; m < limit; m++)
	{
		mersenne = pow(2.0, m) - 1;
#pragma omp critical // Using clritial to show one prime at a time
		printf("Current number is %d\n ", mersenne);

		if (detectPrime(mersenne)) // When the Mersenne primes are detected, thay are shown
		{
			printf("---Mersenne number found %d\n", mersenne);
#pragma omp critical 
			mersenneArray[k] = mersenne; //Putting all Mersenne primes into the array
			k++;
		}
	}

	printf("\n The completed array of Mersenne primes is: \n");
	printArray(mersenneArray, k); //Printing the completed array of MErsenne primes

	time = clock() - time; // Time ends here
	printf("\nTime needed in miliseconds is %d\n", time, ((float)time) / CLOCKS_PER_SEC); // Displaying total time

	system("pause");
}





