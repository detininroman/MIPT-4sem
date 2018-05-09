#define _GNU_SOURCE    
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>

struct thread_data {
    double from;
    double to;
    double sum;
    double dx;
    pthread_t thread_id;
    int cpu_number;
};

void parseCpuInfo(int** cores, int cpu_max)
{
    for (int i = 0; i < cpu_max; i++)
        for (int j = 0; j < 2; j++)
            cores[i][j] = -1;

    FILE* src = fopen("info", "w+");
    system("lscpu --parse=cpu,core > info");

    struct stat buff;
    stat("info", &buff);
    long file_size = buff.st_size;

    char* buffer = (char*)calloc(file_size, sizeof(*buffer));
    fread(buffer, sizeof(char), (size_t)file_size, src);
    
    int left = -1;
    int right = -1;
    int cnt = 0;
    buffer = strchr(buffer, '0');
    while (1)
    {
        sscanf(buffer, "%d,%d%n", &left, &right, &cnt);
        buffer += cnt;
        if (*buffer == '\0')
            break;
       
        printf("%d,%d\n", left, right);
       
        if (cores[right][0] == -1)
            cores[right][0] = left;
        else 
            cores[right][1] = left;
    }
    fclose(src);
    
}

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

    double sum = 0;
 
    for (double x = data->from; x < data->to; x += data->dx)
        sum += x * x * data->dx; 

    data->sum = sum;
    return NULL;
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "Error: %s\n", strerror(EINVAL));
        exit(EXIT_FAILURE);
    }

    long n_threads = strtol(argv[1], NULL, 10);
    if (n_threads < 1) {
        fprintf(stderr, "Error: %s\n", strerror(EINVAL));
        exit(EXIT_FAILURE);
    }

    int cpu_max = sysconf(_SC_NPROCESSORS_ONLN) / 2;
    if (n_threads > cpu_max)
        n_threads = cpu_max;
    
    double A = 0;    
    double B = 50;  
    double N = 1e+9;
    double dx = (B - A) / N;
    double segment_length = (B - A) / (double) n_threads; 
    struct thread_data* data = calloc(n_threads, sizeof(*data));
   
    int** cores = (int**)calloc(cpu_max, sizeof(*cores));
    for (int i = 0; i < cpu_max; i++)
        cores[i] = (int*) calloc(2, sizeof(*(cores[i])));

    parseCpuInfo(cores, cpu_max);
     
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
    
    double total = 0;
    for (int i = 0; i < n_threads; i++) {
        pthread_join(data[i].thread_id, NULL);
        total += data[i].sum;
    }

    printf("Result: %lg\n", total);
   
    for (int i = 0; i < cpu_max; i++)
        free(cores[i]);
    free(cores);

   free(data);
    return 0;
}
