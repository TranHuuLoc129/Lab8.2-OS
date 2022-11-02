#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>
#define SEED 35791246
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SIZE 256


sem_t mutex;
int i,j;
int numA;
int numB;
int *shm, shmid;

void* thread1(void* arg){   
	 i = 1;
	
	while(i<= numA || j<=numB){
		
		shm[0] = i;
		i++;
		
		sem_post(&mutex);

		sleep(1);
	
		if(shm[0] <= numB){
		    printf("Nguoi thu %d o phia Nam qua cau\n", shm[0]);
		}
		

	}
}

void* thread2(void* arg){ 
	
	j = 1;
	while(j<= numB || i<=numA){
		sem_wait(&mutex);
	
		if(shm[0] <= numA){
			printf("Nguoi thu %d o phia Bac qua cau\n", shm[0]);
		}
		
		shm[0] = j; 
		j++;
		
		
	}
	
}



int main(int argc, char* argv[]){

	
	
	key_t key;
	
	shmid = shmget(key, SIZE, IPC_CREAT | 0666);
	if(shmid == -1){
		perror ("Shared memory created.\n");
		return 2;

	}
	
	shm = (int *) shmat(shmid, 0,0);
	
	sem_init(&mutex,0,0);

	printf("So nguoi lang phia Bac: \n");
	scanf("%d", &numA);

	printf("So nguoi lang phia Nam: \n");
	scanf("%d", &numB);

	pthread_t tid[2];

	pthread_create(&tid[0], NULL, thread1, &numA);
	pthread_create(&tid[1], NULL, thread2, &numB);
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	sem_destroy(&mutex);	
	

	return 0;
}
