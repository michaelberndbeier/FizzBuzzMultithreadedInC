//
//  main.c
//  FizzBuzzMultithreadC
//
//  Created by mbb on 30.10.21.
//

#include <stdio.h>
#include <limits.h>


#include <pthread.h>

#define NUM_THREADS 16



enum FIZZBUZZ {
	number = 0,
	fizz = 1,
	buzz = 2,
	fizzBuzz = 3
};

struct fizzBuzzProcessSettings {
	int id;
	int start;
	int excludeUpperBound;
	int incrementSize;
};

int THREADS = NUM_THREADS;
struct fizzBuzzProcessSettings settings[NUM_THREADS];

enum FIZZBUZZ fizzBuzzEval(int input)
{
	if(input % 15 == 0)		return fizzBuzz;
	else if(input % 5 == 0) return buzz;
	else if(input % 3 == 0) return fizz;
	return number;
}

void process(struct fizzBuzzProcessSettings settings)
{
	int z = settings.start;
	for(z = 1;z<settings.excludeUpperBound;z+=settings.incrementSize) fizzBuzzEval(z);
	
	printf("ist huebsch\n");
	printf("%l interval done\n", settings.id);
}

void *processThread(void *threadid)
{
	process(settings[(long) threadid]);
	pthread_exit(NULL);
}

void initSetting(int start, int excludeUpperBound, int id)
{
	settings[id].id = id;
	settings[id].start = start + id;
	settings[id].excludeUpperBound = excludeUpperBound;
	settings[id].incrementSize = 1 + THREADS;
}

void initSettings(int start, int excludeUpperBound)
{
	for(int id = 0; id < THREADS; id++)
		initSetting(start, excludeUpperBound, id);
}

void multiThread(int start, int excludeUpperBound)
{
	initSettings(start, excludeUpperBound);
	pthread_t threads[THREADS];
	
	   for(int i = 0; i < THREADS; i++ ) {
		  int rc = pthread_create(&threads[i], NULL, process, (void *)i);
		  if (rc) {
			 printf("Error:unable to create thread, %d\n", rc);
		  }
	   }
	   pthread_exit(NULL);
}


int main(int argc, const char * argv[])
{
	multiThread(1, INT_MAX);
	return 0;
}
