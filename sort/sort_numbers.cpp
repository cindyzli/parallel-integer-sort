// #include <pthread.h>
// #include <stdlib.h>
// #include "merge.h"
// #include <iostream>
// #include <vector>
// #include <sstream>
// #include <string>

// typedef struct
// {
//     int *arr;
//     size_t len;
// } ThreadArgs;

// void *merge_sort_thread(void *arg);

// void merge(int *dest, int *left, size_t left_len, int *right, size_t right_len)
// {
//     size_t i = 0, j = 0, k = 0;

//     while (i < left_len && j < right_len)
//     {
//         if (left[i] <= right[j])
//         {
//             dest[k++] = left[i++];
//         }
//         else
//         {
//             dest[k++] = right[j++];
//         }
//     }

//     while (i < left_len)
//     {
//         dest[k++] = left[i++];
//     }

//     while (j < right_len)
//     {
//         dest[k++] = right[j++];
//     }
// }

// void merge_sort(int *arr, size_t len)
// {
//     if (len <= 1)
//         return;

//     size_t mid = len / 2;
//     int *left = arr;
//     int *right = arr + mid;

//     pthread_t t1, t2;
//     ThreadArgs args1 = {left, mid};
//     ThreadArgs args2 = {right, len - mid};

//     pthread_create(&t1, NULL, merge_sort_thread, &args1);
//     pthread_create(&t2, NULL, merge_sort_thread, &args2);
//     pthread_join(t1, NULL);
//     pthread_join(t2, NULL);

//     int *temp = (int *)malloc(sizeof(int) * len);
//     // merge_asm(temp, left, mid, right, len - mid);
//     merge(temp, left, mid, right, len - mid);
//     for (size_t i = 0; i < len; ++i)
//         arr[i] = temp[i];
//     free(temp);
// }

// void *merge_sort_thread(void *arg)
// {
//     ThreadArgs *args = (ThreadArgs *)arg;
//     merge_sort(args->arr, args->len);
//     return NULL;
// }

// int main()
// {
//     std::string line;
//     std::vector<int> numbers;

//     while (std::getline(std::cin, line))
//     {
//         std::stringstream ss(line);
//         int num;
//         while (ss >> num)
//         {
//             numbers.push_back(num);
//             if (ss.peek() == ' ')
//                 ss.ignore();
//         }
//     }

//     if (!numbers.empty())
//     {
//         int *arr = numbers.data();
//         size_t n = numbers.size();
//         merge_sort(arr, n);

//         for (size_t i = 0; i < n; ++i)
//         {
//             std::cout << arr[i] << (i == n - 1 ? "" : " ");
//         }
//         std::cout << std::endl;
//     }

//     return 0;
// }

// #include <pthread.h>
// #include <stdlib.h>
// #include <iostream>
// #include <vector>
// #include <sstream>
// #include <string>

#include <pthread.h>
#include <stdlib.h>
#include "merge.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

typedef struct
{
    int *arr;
    size_t len;
} ThreadArgs;

void *merge_sort_thread(void *arg);

void *merge_sort_thread(void *arg);
// void merge_sort(int *arr, size_t len);

pthread_mutex_t thread_count_mutex = PTHREAD_MUTEX_INITIALIZER;
int active_threads = 0;
const int MAX_THREADS = 1000;

void merge(int *dest, int *left, size_t left_len, int *right, size_t right_len)
{
    size_t i = 0, j = 0, k = 0;

    while (i < left_len && j < right_len)
    {
        if (left[i] <= right[j])
        {
            dest[k++] = left[i++];
        }
        else
        {
            dest[k++] = right[j++];
        }
    }

    while (i < left_len)
    {
        dest[k++] = left[i++];
    }

    while (j < right_len)
    {
        dest[k++] = right[j++];
    }
}

void merge_sort(int *arr, size_t len)
{
    if (len <= 1)
        return;

    size_t mid = len / 2;
    int *left = arr;
    int *right = arr + mid;

    bool use_threads = false;

    pthread_mutex_lock(&thread_count_mutex);
    if (active_threads < MAX_THREADS)
    {
        active_threads += 2;
        use_threads = true;
    }
    pthread_mutex_unlock(&thread_count_mutex);

    if (use_threads)
    {
        pthread_t t1, t2;
        ThreadArgs args1 = {left, mid};
        ThreadArgs args2 = {right, len - mid};

        pthread_create(&t1, NULL, merge_sort_thread, &args1);
        pthread_create(&t2, NULL, merge_sort_thread, &args2);
        pthread_join(t1, NULL);
        pthread_join(t2, NULL);

        pthread_mutex_lock(&thread_count_mutex);
        active_threads -= 2;
        pthread_mutex_unlock(&thread_count_mutex);
    }
    else
    {
        merge_sort(left, mid);
        merge_sort(right, len - mid);
    }

    int *temp = (int *)malloc(sizeof(int) * len);
    // merge(temp, left, mid, right, len - mid);
    merge_asm(temp, left, mid, right, len - mid);
    for (size_t i = 0; i < len; ++i)
        arr[i] = temp[i];
    free(temp);
}

void *merge_sort_thread(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;
    merge_sort(args->arr, args->len);
    return NULL;
}

int main()
{
    std::string line;
    std::vector<int> numbers;

    while (std::getline(std::cin, line))
    {
        std::stringstream ss(line);
        int num;
        while (ss >> num)
        {
            numbers.push_back(num);
            if (ss.peek() == ' ')
                ss.ignore();
        }
    }

    if (!numbers.empty())
    {
        int *arr = numbers.data();
        size_t n = numbers.size();
        merge_sort(arr, n);

        for (size_t i = 0; i < n; ++i)
        {
            std::cout << arr[i] << (i == n - 1 ? "" : " ");
        }
        std::cout << std::endl;
    }

    return 0;
}
