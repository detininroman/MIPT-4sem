#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct thread_data {
    double from;
    double to;
    double dx;
    double pieces_num;
    double sum;
} thread_data;

double f(double x)
{
    return x*x;
}

void* integrate(void* arg)
{
    thread_data* data = (thread_data*) arg;
    
    for (double x = data->from; x < data->to; x += data->dx)
        data->sum += f(x) * data->dx;
    
    return NULL;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "Error: %s\n", strerror(EINVAL));
        exit(EXIT_FAILURE);
    }

    double A = 0;
    double B = 50;
    double N = 1000000;

    long n_threads = strtoll(argv[1], NULL, 10);
    double segment_length = (B - A) / n_threads; 
    double total = 0;

    thread_data* data = calloc(n_threads, sizeof(*data));
    
    for (int i = 0; i < n_threads; i++) {
        data[i].from       = A + segment_length * i;
        data[i].to         = data[i].from + segment_length;
        data[i].pieces_num = N / n_threads;
        data[i].dx         = segment_length / data[i].pieces_num;
        data[i].sum        = 0;
             
        integrate(data + i);
        total += data[i].sum;
    }
    free(data);
 
    printf("Result: %lg\n", total);
    return 0;
}
