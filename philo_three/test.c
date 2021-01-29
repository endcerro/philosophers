# include <stdio.h>
# include <string.h>
# include <sys/time.h>
#include <signal.h>
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

int loop(m_test *test, int id)
{
	int i = 0;
	// printf("WELCOME TO LOOP\	n");
	while (++i < 100 * id)
	{
		sem_wait(test->sems[0]);
		sem_wait(test->sems[1]);
		// printf("GOT BOTH\n");
		// printf("VALUES ARE %d %d\n", (test->sems[1]), (test->sems[0]) );
		usleep(5000);
		sem_post(test->sems[0]);
		sem_post(test->sems[1]);
		// printf("DROPPED BOTH\n");
		printf("%d %d\n",id, i );
	}
	printf("I AM DONE\n");
	if ( id == 1)
		return 0;
	else 
		exit(1);
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
	pid_t f3;
	pid_t f4;

	if ((f1 = fork()) == 0)
	{
		loop(&test, 1);
	}
	else if ((f2 = fork()) == 0)
	{
		loop(&test, 2);
	}
	else if ((f3 = fork()) == 0)
	{
		loop(&test, 3);
	}
	else if ((f4 = fork()) == 0)
	{
		loop(&test, 4);
	}
	else
	{
		int ret = -50;
		int run = 4;
		while (run)
		{
			pid_t status = waitpid(-1, &ret, WUNTRACED);	
			// if (status == 0)
				// printf("NOTHING RETURNED\n");
			if (status != 0)
			{
				// if(WIFEXITED(ret))
				// 	printf("EXIT\n");
				// else
				// 	printf("RETURN\n");
				// kill(f1, SIGKILL);
				// kill(f2, SIGKILL);
				kill(f1, SIGKILL);
				kill(f2, SIGKILL);
				kill(f3, SIGKILL);
				kill(f4, SIGKILL);
				run--;
				printf("pid :%d ret:%d \n",status, ret);
			}
		
		}
		// int ret;
		// waitpid(0, &ret, WUNTRACED);
		// printf("%d finished first\n",ret );
		// waitpid(0, &ret, WUNTRACED);
		// printf("%d finished second\n",ret );
		// printf("BOTH DONE\n");
	}



	// pthread_create(&(pid[0]), 0, (void*)loop, (void*)&(test));
	// pthread_create(&(pid[1]), 0, (void*)loop, (void*)&(test));
	
	// pthread_join(pid[0], 0);
	// pthread_join(pid[1], 0);

	return 0;
}