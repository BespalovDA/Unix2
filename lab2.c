#include <stdio.h>
#include <pthread.h>

typedef struct{
	int gotovn;
	int bal;
	pthread_mutex_t zakr;
	pthread_cond_t conddd;
} Args;

void supplier(Args *args)
{
	for(;;) {
	pthread_mutex_lock(&args->zakr);
	if (args->gotovn == 1)
	{
		pthread_mutex_unlock&args->zakr);
		continue;
	}
	sleep(1);
	args->bal = args->bal - 10;
	args->gotovn = 1;
	puts("done");
	pthread_cond_signal(&args->conddd);
	pthread_mutex_unlock(&args->zakr);
	}
}
void reciever(Args *args)
{
	for(;;) {
	pthread_mutex_lock(&args->zakr);
	while (args->gotovn == 0)
	{
		pthread_cond_wait(&args->conddd, &args->zakr);
		puts("wake");
	}
	args->bal = args->bal + 10;
	args->gotovn = 0;
	puts("potreblenie");
	pthread_mutex_unlock(&args->zakr);
	}
}


int main(int argc, char **argv)
{
	pthread_cond_t conddd = PTHREAD_COND_INITIALIZER;
	pthread_mutex_t zakr = PTHREAD_MUTEX_INITIALIZER;
	pthread_t id1, id2;
	Args args;
	int gotovn = 0;
	int bal = 100;
	args.zakr = zakr;
	args.conddd = conddd;
	args.gotovn = gotovn;
	args.bal = bal;
	pthread_create(&id1, NULL, supplier, &args);
	pthread_create(&id2, NULL, reciever, &args);
	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
	return 0;
}
