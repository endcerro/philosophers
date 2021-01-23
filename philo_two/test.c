# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <semaphore.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct test
{
	sem_t **sems;	
} m_test;

void loop(m_test *test)
{
	printf("WELCOME TO LOOP\n");
	while (1)
	{
		sem_wait(test->sems[0]);
		sem_wait(test->sems[1]);
		printf("GOT BOTH\n");
		usleep(5000000);
		sem_post(test->sems[0]);
		sem_post(test->sems[1]);
		printf("DROPPED BOTH\n");
	}
}

int main()
{
	
	m_test test;
	test.sems = malloc(sizeof(sem_t *) * 3);
	pthread_t pid[20];
	test.sems[0] = sem_open("s0", O_CREAT, 0664, 1);
	test.sems[1] = sem_open("s1", O_CREAT, 0664, 1);

	pthread_create(&(pid[0]), 0, (void*)loop, (void*)&(test));
	pthread_create(&(pid[1]), 0, (void*)loop, (void*)&(test));
	
	pthread_join(pid[0], 0);
	pthread_join(pid[1], 0);

	return 0;
}