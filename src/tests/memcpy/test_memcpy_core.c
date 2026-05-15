#include "test_memcpy.h"
#include <string.h>
#include <stdlib.h>


// Публичная функция запуска теста
void run_memcpy_test(MemCpyTestParams *params) {
    s21_size_t buf_size = params->size + 64;  // Запас для проверки границ
    
    char *dest_std = malloc(buf_size);
    char *dest_test = malloc(buf_size);

    ck_assert_ptr_nonnull(dest_std);
    ck_assert_ptr_nonnull(dest_test);

    memset(dest_std, 0xAA, buf_size);  // Паттерн для отладки
    memset(dest_test, 0xAA, buf_size);

    //Тестируем только валидное поведение, как требует стандарт
    s21_memcpy(dest_test, params->src, params->size);
    memcpy(dest_std, params->src, params->size);

    // Проверяем всю область памяти, включая границы с паттерном 0xAA
    ck_assert_mem_eq(dest_test, dest_std, buf_size);

     free(dest_std);
     free(dest_test);

}