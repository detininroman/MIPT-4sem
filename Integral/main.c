#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

struct thread_data {
    double from;
    double to;
    double pieces_num;
    double sum;
    pthread_t thread_ptr;
};

double f(double x)
{
    return x*x + x/(1+x);
}

void* integrate(void* arg)
{
    struct thread_data* data = (struct thread_data*)arg;
    
    double dx = (data->to - data->from) / data->pieces_num;
    for (double x = data->from; x < data->to; x += dx)
        data->sum += f(x) * dx;
    
    return NULL;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "Error: %s\n", strerror(EINVAL));
        exit(EXIT_FAILURE);
    }

    double A = 0;    // from
    double B = 50;   // to
    double N = 1e+9; // 10^9

    long n_threads = strtol(argv[1], NULL, 10);
    double segment_length = (B - A) / n_threads; 
    double total = 0;

    struct thread_data* data = calloc(n_threads, sizeof(*data));

    for (int i = 0; i < n_threads; i++) {
        data[i].from       = A + segment_length * i;
        data[i].to         = data[i].from + segment_length;
        data[i].pieces_num = N / n_threads;
    }

    for (int i = 0; i < n_threads; i++)
        pthread_create(&data[i].thread_ptr, NULL, integrate, data + i);
    
    for (int i = 0; i < n_threads; i++) {
        pthread_join(data[i].thread_ptr, NULL);
        total += data[i].sum;
    }

    free(data);
 
    printf("Result: %lg\n", total);
    return 0;
}
