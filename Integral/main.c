#define _GNU_SOURCE    
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

struct thread_data {
    double from;
    double to;
    double sum;
    double dx;
    pthread_t thread_id;
    int cpu_number;
};

void* doNothing()
{
    while (1);
}

void* integrate(void* arg)
{
    struct thread_data* data = (struct thread_data*)arg;
   
    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    CPU_SET(data->cpu_number, &cpu_set);
	pthread_setaffinity_np(data->thread_id, sizeof(cpu_set_t), &cpu_set);

    double SUM = 0;
 
    for (double x = data->from; x < data->to; x += data->dx)
        SUM += x * x * data->dx; 

    data->sum = SUM;
    return NULL;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "Error: %s\n", strerror(EINVAL));
        exit(EXIT_FAILURE);
    }

    long n_threads = strtol(argv[1], NULL, 10);
    int cpu_max = sysconf(_SC_NPROCESSORS_ONLN);
    if (n_threads > cpu_max)
        n_threads = cpu_max;
    
    double A = 0;    // from
    double B = 50;   // to
    double N = 5e+9; // 5*10^9
    double dx = (B - A) / N;
    double segment_length = (B - A) / (double) n_threads; 
    double total = 0;

    struct thread_data* data = calloc(n_threads, sizeof(*data));
   
    for (int i = 0; i < n_threads; i++) {
        data[i].from       = A + segment_length * i;
        data[i].to         = data[i].from + segment_length;
        data[i].cpu_number = i % n_threads;
        data[i].dx         = dx;
    }
    
    for (int i = 0; i < n_threads; i++) 
        pthread_create(&data[i].thread_id, NULL, integrate, (void*)(data + i));

    for (int i = n_threads; i < cpu_max; i++)
        pthread_create(&data[i].thread_id, NULL, doNothing, NULL);

    for (int i = 0; i < n_threads; i++) {
        pthread_join(data[i].thread_id, NULL);
        total += data[i].sum;
    }

    free(data);
    return 0;
}
