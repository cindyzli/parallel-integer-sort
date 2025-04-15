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

void merge_sort(int *arr, size_t len)
{
    if (len <= 1)
        return;

    size_t mid = len / 2;
    int *left = arr;
    int *right = arr + mid;

    pthread_t t1, t2;
    ThreadArgs args1 = {left, mid};
    ThreadArgs args2 = {right, len - mid};

    pthread_create(&t1, NULL, merge_sort_thread, &args1);
    pthread_create(&t2, NULL, merge_sort_thread, &args2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    int *temp = (int *)malloc(sizeof(int) * len);
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