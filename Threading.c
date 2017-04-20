/*
 Name: Ryan Gibeault
 Course Section: 3600.001
 Due Date: 04/16/17
 Brief Description: Find prime numbers using the Sieve of Eratosthenes algorithm and 
					incorporate multithreading and piplining.
*/

#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void *find_primes(void *thread); // Thread function
void track_primes(int current_num, int prime, int size_of_array, bool *arr_ptr); //Keep track of non-primes

//define struct for prime calculations
struct values {
	int current_num;
	int prime;
	int size_of_array;
	bool *arr_ptr;
};

int main(int argc, char **argv) 
{
	//-----------------------------------------
	//     COMMAND LINE ERROR CHECKING           
	
	// Validate correct number of arguments
	if(argc != 2)
	{
		printf("Usage: %s [N>1]\n", argv[0]);
		exit(1);
	}

	int input = atoi(argv[1]);	// convert user input to integer	

	// Validate input of arg[1]
	if(input <= 1)
	{
		printf("Error: [N<=1] needs to be greater than 1\n");
		exit(1);
	}
	
	//		   END ERROR CHECKING
	//-----------------------------------------	
	
	pthread_t tid;	// Declare size of thread IDs
	pthread_attr_t attr;	// Set of thread attributes
	struct values thread;	// declare struct object
	int i;
	
	bool prime_arr[input];	//declare array for primes
	
	thread.size_of_array = input;	//appropriate values to struct values
	thread.arr_ptr = prime_arr;
	
	for(i = 2; i < input; i++)
	{
		if(prime_arr[i] != true)
		{
			thread.current_num = i;
			thread.prime = i;
			
			//Get the default attributes
			pthread_attr_init(&attr);
			//Create the thread with appropriate parameters
			pthread_create(&tid,&attr,find_primes,&thread);
			//Wait for the thread to exit
			pthread_join(tid,NULL);			
		}
	}	
	printf("}\n"); // Close brackets of prime numbers
}

// The thread function
void *find_primes(void *thread)
{
	struct values *my_vals = (struct values*)thread; //define struct variable for use in recursive call
	
	track_primes(my_vals->current_num, my_vals->prime, my_vals->size_of_array, my_vals->arr_ptr);	//call recursive funciton to find primes
	
	pthread_exit(0);
}

//recursive function used to find primes
void track_primes(int current_num, int prime, int size_of_array, bool *arr_ptr)
{
	if(current_num >= size_of_array)
	{
		return;	//reached upper limit of array
	}
	else if(current_num == prime)	//found prime number
	{
		printf("%d, ", prime);
		fflush(stdout);
		track_primes(current_num+prime, prime, size_of_array, arr_ptr);
	}
	else	//non-prime number
	{
		arr_ptr[current_num] = true;
		track_primes(current_num+prime, prime, size_of_array, arr_ptr);
	}
}