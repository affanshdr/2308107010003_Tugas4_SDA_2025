#ifndef SORT_UTILS_H
#define SORT_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LEN 100

// Integer sort function prototypes
void bubble_sort_int(int arr[], int n);
void selection_sort_int(int arr[], int n);
void insertion_sort_int(int arr[], int n);
void merge_sort_int_wrapper(int arr[], int n);
void quick_sort_int_wrapper(int arr[], int n);
void shell_sort_int(int arr[], int n);

// String sort function prototypes
void bubble_sort_str(char **arr, int n);
void selection_sort_str(char **arr, int n);
void insertion_sort_str(char **arr, int n);
void merge_sort_str_wrapper(char **arr, int n);
void quick_sort_str_wrapper(char **arr, int n);
void shell_sort_str(char **arr, int n);

// Benchmark functions
void benchmark_sort_int(const char *label, void (*sort_func)(int*, int), int *arr, int n);
void benchmark_sort_str(const char *label, void (*sort_func)(char**, int), char **arr, int n);

// ======================= INTEGER SORT FUNCTIONS =======================
void bubble_sort_int(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selection_sort_int(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void insertion_sort_int(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Menggabungkan dua subarray terurut menjadi satu array terurut.
void merge_int(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L); free(R);
}

// Mengurutkan array menggunakan algoritma merge sort.

void merge_sort_int(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort_int(arr, l, m);
        merge_sort_int(arr, m + 1, r);
        merge_int(arr, l, m, r);
    }
}

// Fungsi pembungkus (wrapper) untuk memanggil merge_sort_int dengan parameter awal yang sederhana.
void merge_sort_int_wrapper(int arr[], int n) {
    merge_sort_int(arr, 0, n - 1);
}

// mempartisi array dengan memilih sebuah pivot dan mengatur elemen-elemen lainnya berdasarkan nilai pivot tersebut.
int partition_int(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

// Mengurutkan array secara rekursif dengan strategi divide-and-conquer
void quick_sort_int(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition_int(arr, low, high);
        quick_sort_int(arr, low, pi - 1);
        quick_sort_int(arr, pi + 1, high);
    }
}

// Menyederhanakan pemanggilan Quick Sort
void quick_sort_int_wrapper(int arr[], int n) {
    quick_sort_int(arr, 0, n - 1);
}

void shell_sort_int(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

// ======================= STRING SORT FUNCTIONS =======================
void bubble_sort_str(char **arr, int n) {
    char temp[MAX_WORD_LEN];
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j + 1]);
                strcpy(arr[j + 1], temp);
            }
        }
    }
}

void selection_sort_str(char **arr, int n) {
    char temp[MAX_WORD_LEN];
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[j], arr[min_idx]) < 0)
                min_idx = j;
        }
        if (min_idx != i) {
            strcpy(temp, arr[min_idx]);
            strcpy(arr[min_idx], arr[i]);
            strcpy(arr[i], temp);
        }
    }
}

void insertion_sort_str(char **arr, int n) {
    char key[MAX_WORD_LEN];
    for (int i = 1; i < n; i++) {
        strcpy(key, arr[i]);
        int j = i - 1;
        while (j >= 0 && strcmp(arr[j], key) > 0) {
            strcpy(arr[j + 1], arr[j]);
            j--;
        }
        strcpy(arr[j + 1], key);
    }
}

// Menggabungkan dua subarray terurut menjadi satu array terurut.
void merge_str(char **arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    char **L = (char **)malloc(n1 * sizeof(char *));
    char **R = (char **)malloc(n2 * sizeof(char *));
    
    for (int i = 0; i < n1; i++) {
        L[i] = (char *)malloc(MAX_WORD_LEN * sizeof(char));
        strcpy(L[i], arr[l + i]);
    }
    for (int j = 0; j < n2; j++) {
        R[j] = (char *)malloc(MAX_WORD_LEN * sizeof(char));
        strcpy(R[j], arr[m + 1 + j]);
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) {
            strcpy(arr[k], L[i]);
            i++;
        } else {
            strcpy(arr[k], R[j]);
            j++;
        }
        k++;
    }

    while (i < n1) {
        strcpy(arr[k], L[i]);
        i++;
        k++;
    }

    while (j < n2) {
        strcpy(arr[k], R[j]);
        j++;
        k++;
    }

    for (int i = 0; i < n1; i++) free(L[i]);
    for (int j = 0; j < n2; j++) free(R[j]);
    free(L);
    free(R);
}

// Membagi array secara rekursif dan memanggil merge_int untuk menggabungkannya.
void merge_sort_str(char **arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort_str(arr, l, m);
        merge_sort_str(arr, m + 1, r);
        merge_str(arr, l, m, r);
    }
}

// Fungsi pembungkus (wrapper) untuk memanggil merge_sort_int dengan parameter awal yang sederhana.
void merge_sort_str_wrapper(char **arr, int n) {
    merge_sort_str(arr, 0, n - 1);
}

// empartisi array menjadi dua bagian relatif terhadap pivot
int partition_str(char **arr, int low, int high) {
    char pivot[MAX_WORD_LEN];
    strcpy(pivot, arr[high]);
    int i = low - 1;
    char temp[MAX_WORD_LEN];
    
    for (int j = low; j <= high - 1; j++) {
        if (strcmp(arr[j], pivot) < 0) {
            i++;
            strcpy(temp, arr[i]);
            strcpy(arr[i], arr[j]);
            strcpy(arr[j], temp);
        }
    }
    strcpy(temp, arr[i + 1]);
    strcpy(arr[i + 1], arr[high]);
    strcpy(arr[high], temp);
    return i + 1;
}

// Mengurutkan array secara rekursif dengan strategi divide-and-conquer
void quick_sort_str(char **arr, int low, int high) {
    if (low < high) {
        int pi = partition_str(arr, low, high);
        quick_sort_str(arr, low, pi - 1);
        quick_sort_str(arr, pi + 1, high);
    }
}

// Menyederhanakan pemanggilan Quick Sort
void quick_sort_str_wrapper(char **arr, int n) {
    quick_sort_str(arr, 0, n - 1);
}

void shell_sort_str(char **arr, int n) {
    char temp[MAX_WORD_LEN];
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            strcpy(temp, arr[i]);
            int j;
            for (j = i; j >= gap && strcmp(arr[j - gap], temp) > 0; j -= gap) {
                strcpy(arr[j], arr[j - gap]);
            }
            strcpy(arr[j], temp);
        }
    }
}

void benchmark_sort_int(const char *label, void (*sort_func)(int*, int), int *arr, int n) {
    clock_t start = clock();
    sort_func(arr, n);
    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    double mem_MB = (sizeof(int) * n) / (1024.0 * 1024.0);
    printf("%s (int): %.3f sec | Memori: %.2f MB\n", label, elapsed, mem_MB);
}

void benchmark_sort_str(const char *label, void (*sort_func)(char**, int), char **arr, int n) {
    clock_t start = clock();
    sort_func(arr, n);
    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    double mem_MB = (n * MAX_WORD_LEN) / (1024.0 * 1024.0);
    printf("%s (str): %.3f sec | Memori: %.2f MB\n", label, elapsed, mem_MB);
}

#endif