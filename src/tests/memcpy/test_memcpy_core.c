#include "test_memcpy.h"
#include <string.h>
#include <stdlib.h>

// Выделение и инициализация буферов
static void allocate_dest_buffers(char **dest_std,
                                  char **dest_test,
                                  s21_size_t buf_size) {
    *dest_std = malloc(buf_size);
    *dest_test = malloc(buf_size);
    
    ck_assert_ptr_nonnull(*dest_std);
    ck_assert_ptr_nonnull(*dest_test);
    
    memset(*dest_std, 0xAA, buf_size);  // Паттерн для отладки
    memset(*dest_test, 0xAA, buf_size);
}

// Настройка указателей назначения
static void setup_dest_pointers(const MemCpyTestParams *params,
                                char *dest_std,
                                char *dest_test,
                                void **dest_ptr_std,
                                void **dest_ptr_test) {
    if (!params->is_dest_null) {
        *dest_ptr_std = dest_std;
        *dest_ptr_test = dest_test;
    } else {
        *dest_ptr_std = (void *)s21_NULL;
        *dest_ptr_test = (void *)s21_NULL;
    }
}

// Настройка указателя источника
static void setup_src_pointer(const MemCpyTestParams *params,
                              const void **src_ptr) {
    if (!params->is_src_null) {
        *src_ptr = params->src;
    } else {
        *src_ptr = s21_NULL;
    }
}

// Выполнение копирования
static void perform_copy(void *dest_test,
                         const void *src_ptr,
                         s21_size_t size,
                         void *dest_std) {
    if (dest_test != NULL && dest_std != NULL && src_ptr != NULL) {
        s21_memcpy(dest_test, src_ptr, size);
        memcpy(dest_std, src_ptr, size);
    }
}

// Проверка результата
static void verify_copy_result(const MemCpyTestParams *params,
                               char *dest_test,
                               char *dest_std,
                               s21_size_t buf_size) {
    if (!params->is_dest_null && !params->is_src_null && params->size > 0) {
        ck_assert_mem_eq(dest_test, dest_std, params->size);
    } else if (!params->is_dest_null && params->size == 0) {
        // При size=0 данные не должны измениться
        ck_assert_mem_eq(dest_test, dest_std, buf_size);
    }
}

// Очистка буферов
static void cleanup_buffers(const MemCpyTestParams *params,
                            char *dest_test,
                            char *dest_std) {
    if (!params->is_dest_null) {
        if (dest_std != NULL) {
            free(dest_std);
        }
        if (dest_test != NULL) {
            free(dest_test);
        }
    }
}

// Публичная функция запуска теста
void run_memcpy_test(MemCpyTestParams *params) {
    s21_size_t buf_size = params->size + 64;  // Запас для проверки границ
    char *dest_std = NULL;
    char *dest_test = NULL;
    const void *src_ptr = NULL;
    void *dest_ptr_std = NULL;
    void *dest_ptr_test = NULL;

    if (!params->is_dest_null) {
        allocate_dest_buffers(&dest_std, &dest_test, buf_size);
    }

    setup_dest_pointers(params, dest_std, dest_test, &dest_ptr_std, &dest_ptr_test);
    setup_src_pointer(params, &src_ptr);

    perform_copy(dest_ptr_test, src_ptr, params->size, dest_ptr_std);

    verify_copy_result(params, dest_test, dest_std, buf_size);
    
    cleanup_buffers(params, dest_test, dest_std);
}