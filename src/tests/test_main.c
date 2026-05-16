#include <check.h>
#include <stdlib.h>
#include "../s21_string.h"

Suite *s21_memcmp_suite_create(void);

int main(void) {
    int failed = 0;
    SRunner *sr = srunner_create(s21_memcmp_suite_create());

    srunner_run_all(sr, CK_NORMAL);
    failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
