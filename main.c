#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sort_utils.h"

#define MAX_WORD_LEN 100

// Function prototypes
void load_data_int(const char *filename, int *arr, int n);
void load_data_str(const char *filename, char **arr, int n);
void jalankan_sorting_int(int n);
void jalankan_sorting_str(int n);
void cleanup_memory();

// Global variables for memory management
int *original_int = NULL;
int *copy_int = NULL;
char **original_str = NULL;
char **copy_str = NULL;
size_t current_allocated_size = 0;

void load_data_int(const char *filename, int *arr, int n) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Gagal membuka file");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        if (fscanf(fp, "%d", &arr[i]) != 1) {
            printf("Error membaca data di baris %d\n", i);
            fclose(fp);
            exit(EXIT_FAILURE);
        }
    }
    fclose(fp);
}

void load_data_str(const char *filename, char **arr, int n) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("File tidak dapat dibuka");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        if (fscanf(fp, "%s", arr[i]) != 1) {
            printf("Error membaca data di baris %d\n", i);
            fclose(fp);
            exit(EXIT_FAILURE);
        }
    }
    fclose(fp);
}

void jalankan_sorting_int(int n) {
    // Free previous memory if exists
    if (original_int) free(original_int);
    if (copy_int) free(copy_int);
    
    // Allocate new memory
    original_int = (int *)malloc(n * sizeof(int));
    copy_int = (int *)malloc(n * sizeof(int));
    
    if (!original_int || !copy_int) {
        printf("Gagal mengalokasikan memori untuk %d data integer\n", n);
        exit(EXIT_FAILURE);
    }

    load_data_int("data_angka.txt", original_int, n);

    memcpy(copy_int, original_int, sizeof(int) * n);
    benchmark_sort_int("Bubble Sort", bubble_sort_int, copy_int, n);

    memcpy(copy_int, original_int, sizeof(int) * n);
    benchmark_sort_int("Selection Sort", selection_sort_int, copy_int, n);

    memcpy(copy_int, original_int, sizeof(int) * n);
    benchmark_sort_int("Insertion Sort", insertion_sort_int, copy_int, n);

    memcpy(copy_int, original_int, sizeof(int) * n);
    benchmark_sort_int("Merge Sort", merge_sort_int_wrapper, copy_int, n);

    memcpy(copy_int, original_int, sizeof(int) * n);
    benchmark_sort_int("Quick Sort", quick_sort_int_wrapper, copy_int, n);

    memcpy(copy_int, original_int, sizeof(int) * n);
    benchmark_sort_int("Shell Sort", shell_sort_int, copy_int, n);
}

void jalankan_sorting_str(int n) {
    // Free previous memory if exists
    if (original_str) {
        for (size_t i = 0; i < current_allocated_size; i++) {
            free(original_str[i]);
            free(copy_str[i]);
        }
        free(original_str);
        free(copy_str);
    }
    
    // Allocate new memory
    original_str = (char **)malloc(n * sizeof(char *));
    copy_str = (char **)malloc(n * sizeof(char *));
    
    if (!original_str || !copy_str) {
        printf("Gagal mengalokasikan memori untuk %d data string\n", n);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        original_str[i] = (char *)malloc(MAX_WORD_LEN * sizeof(char));
        copy_str[i] = (char *)malloc(MAX_WORD_LEN * sizeof(char));
        if (!original_str[i] || !copy_str[i]) {
            printf("Gagal mengalokasikan memori untuk string ke-%d\n", i);
            exit(EXIT_FAILURE);
        }
    }
    current_allocated_size = n;

    load_data_str("data_kata.txt", original_str, n);

    for (int i = 0; i < n; i++) {
        strcpy(copy_str[i], original_str[i]);
    }
    benchmark_sort_str("Bubble Sort", bubble_sort_str, copy_str, n);

    for (int i = 0; i < n; i++) {
        strcpy(copy_str[i], original_str[i]);
    }
    benchmark_sort_str("Selection Sort", selection_sort_str, copy_str, n);

    for (int i = 0; i < n; i++) {
        strcpy(copy_str[i], original_str[i]);
    }
    benchmark_sort_str("Insertion Sort", insertion_sort_str, copy_str, n);

    for (int i = 0; i < n; i++) {
        strcpy(copy_str[i], original_str[i]);
    }
    benchmark_sort_str("Merge Sort", merge_sort_str_wrapper, copy_str, n);

    for (int i = 0; i < n; i++) {
        strcpy(copy_str[i], original_str[i]);
    }
    benchmark_sort_str("Quick Sort", quick_sort_str_wrapper, copy_str, n);

    for (int i = 0; i < n; i++) {
        strcpy(copy_str[i], original_str[i]);
    }
    benchmark_sort_str("Shell Sort", shell_sort_str, copy_str, n);
}

void cleanup_memory() {
    if (original_int) free(original_int);
    if (copy_int) free(copy_int);
    
    if (original_str) {
        for (size_t i = 0; i < current_allocated_size; i++) {
            free(original_str[i]);
            free(copy_str[i]);
        }
        free(original_str);
        free(copy_str);
    }
    
    original_int = NULL;
    copy_int = NULL;
    original_str = NULL;
    copy_str = NULL;
    current_allocated_size = 0;
}

int main() {
    int pilihan_utama, pilihan_data;
    int ukuran_data[] = {10000, 50000, 100000, 250000, 500000, 1000000, 1500000, 2000000};
    int jumlah_ukuran = sizeof(ukuran_data) / sizeof(ukuran_data[0]);

    do {
        printf("\n=== MENU UTAMA ===\n");
        printf("1. Data Angka\n");
        printf("2. Data Kata\n");
        printf("3. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &pilihan_utama);

        if (pilihan_utama == 1 || pilihan_utama == 2) {
            do {
                printf("\n=== PILIH UKURAN DATA ===\n");
                for (int i = 0; i < jumlah_ukuran; i++) {
                    printf("%d. Sorting %d data\n", i + 1, ukuran_data[i]);
                }
                printf("%d. Kembali\n", jumlah_ukuran + 1);
                printf("Pilih: ");
                scanf("%d", &pilihan_data);

                if (pilihan_data >= 1 && pilihan_data <= jumlah_ukuran) {
                    int n = ukuran_data[pilihan_data - 1];
                    printf("\nMenjalankan sorting untuk %d data...\n", n);
                    
                    // Cleanup before new operation
                    cleanup_memory();
                    
                    if (pilihan_utama == 1) {
                        jalankan_sorting_int(n);
                    } else {
                        jalankan_sorting_str(n);
                    }
                }
            } while (pilihan_data != jumlah_ukuran + 1);
        }
    } while (pilihan_utama != 3);

    cleanup_memory();
    printf("\nProgram selesai.\n");
    return 0;
}