
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    int thread_id;
    int thread_num;
    long N;
    double partial_sum;
} thread_arg_t;

void *thread_func(void *arg) {
    thread_arg_t *targ = (thread_arg_t *)arg;
    long id = targ->thread_id;
    long num = targ->thread_num;
    long N = targ->N;

    long chunk = N / num;
    long start = id * chunk;
    long end = (id == num - 1) ? N : start + chunk;

    double sum = 0.0;
    for (long i = start; i < end; ++i) {
        double ai, bi;
        switch (i % 3) {
            case 0: ai = bi =  1.0; break;
            case 1: ai = bi = -1.0; break;
            default: ai = bi = 0.0; break;
        }
        sum += ai * bi;
    }
    targ->partial_sum = sum;
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <thread_num> <N>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int thread_num = atoi(argv[1]);
    long N = atol(argv[2]);
    if (thread_num < 1 || thread_num > 16 || N < 100000) {
        fprintf(stderr, "参数错误：thread_num 应在 1~16 之间，N >= 100000\n");
        return EXIT_FAILURE;
    }

    pthread_t *threads = malloc(thread_num * sizeof(pthread_t));
    thread_arg_t *args = malloc(thread_num * sizeof(thread_arg_t));
    if (!threads || !args) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    struct timespec t_start, t_end;
    clock_gettime(CLOCK_MONOTONIC, &t_start);

    for (int t = 0; t < thread_num; ++t) {
        args[t].thread_id = t;
        args[t].thread_num = thread_num;
        args[t].N = N;
        args[t].partial_sum = 0.0;
        pthread_create(&threads[t], NULL, thread_func, &args[t]);
    }

    double result = 0.0;
    for (int t = 0; t < thread_num; ++t) {
        pthread_join(threads[t], NULL);
        result += args[t].partial_sum;
    }

    clock_gettime(CLOCK_MONOTONIC, &t_end);
    long sec_diff = t_end.tv_sec - t_start.tv_sec;
    long nsec_diff = t_end.tv_nsec - t_start.tv_nsec;
    long total_ns = sec_diff * 1000000000LL + nsec_diff;
    double elapsed_ms = total_ns / 1e6;

    printf("s=%.2f t=%f(ms)\n", result, elapsed_ms);

    free(threads);
    free(args);
    return EXIT_SUCCESS;
}
