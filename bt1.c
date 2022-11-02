#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>
#define SEED 35791246

sem_t mutex;

int niter, range;
int count = 0;

void* thread(void* arg){
	sem_wait(&mutex);
	//
	srand(SEED);
	double x,y;
	int i;
	double z;
	//initialize random numbers
	
	for( i =0; i< range; i++){
		x = (double)rand () / RAND_MAX;
		y = (double) rand () / RAND_MAX;
		z = x*x + y*y;
		if(z<=1){
			count++;
		}
	}

	sem_post(&mutex);

}



int main(int argc, char* argv[]){


	
	int numthread ;
	double pi;
	struct timeval start, end;
	
	printf("Enter the number of iterations used to estimate pi: \n");
	scanf("%d", &niter);
	printf("Number thread: ");
	scanf("%d", &numthread);
	
	range = niter/numthread;

	pthread_t tid[numthread];
	
	int i,j; 
	sem_init(&mutex,0,1);
	
	gettimeofday(&start, NULL);
	for(i=0; i< numthread; i++){
	      pthread_create(&tid[i], NULL, thread, &range);
	}

	for(i = 0; i<numthread; i++){
		pthread_join(tid[i], NULL);
		
	}

	gettimeofday(&end, NULL);
	
	pi = ((double ) count/niter)*4;

	printf("pi = %.4lf\n",pi);
	double timespent = (double) ((double)(end.tv_usec - start.tv_usec)/1000000
			+ (double )(end.tv_sec - start.tv_sec));
	printf("Time taken for execution: %f seconds\n", timespent);
	
	sem_destroy(&mutex);	

	return 0;
}
