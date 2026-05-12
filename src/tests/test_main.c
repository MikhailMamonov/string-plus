#include <check.h>
#include <stdlib.h>

Suite *memchr_suite_create(void);

int main(void) {
    int failed = 0;
    SRunner *sr = srunner_create(memchr_suite_create()); // Создаем раннер с первой сюитой

   /* // Добавляем остальные сюиты (из других файлов)
    srunner_add_suite(sr, string_suite_create());*/

    srunner_run_all(sr, CK_NORMAL);
    failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
