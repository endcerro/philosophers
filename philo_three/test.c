# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <semaphore.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct test
{
	sem_t **sems;	
} m_test;

void loop(m_test *test)
{
	int i = 0;
	printf("WELCOME TO LOOP\n");
	while (++i < 10)
	{
		sem_wait(test->sems[0]);
		sem_wait(test->sems[1]);
		printf("GOT BOTH\n");
		// printf("VALUES ARE %d %d\n", (test->sems[1]), (test->sems[0]) );
		usleep(5000);
		sem_post(test->sems[0]);
		sem_post(test->sems[1]);
		printf("DROPPED BOTH\n");
	}
	printf("I AM DONE\n");
}

int main()
{
	
	m_test test;
	test.sems = malloc(sizeof(sem_t *) * 3);
	pthread_t pid[20];
	sem_unlink("s0");
	sem_unlink("s1");
	test.sems[0] = sem_open("s0", O_CREAT, 0664, 1);
	test.sems[1] = sem_open("s1", O_CREAT, 0664, 1);

	pid_t f1;
	pid_t f2;

	if ((f1 = fork()) == 0)
	{
		loop(&test);
	}
	else if ((f2 = fork()) == 0)
	{
		loop(&test);
	}
	else
	{
		waitpid(f1, (int *)WUNTRACED, 0);
		waitpid(f2, (int *)WUNTRACED, 0);
		printf("BOTH DONE\n");
	}



	// pthread_create(&(pid[0]), 0, (void*)loop, (void*)&(test));
	// pthread_create(&(pid[1]), 0, (void*)loop, (void*)&(test));
	
	// pthread_join(pid[0], 0);
	// pthread_join(pid[1], 0);

	return 0;
}