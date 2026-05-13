#include <check.h>
#include <stdlib.h>
#include "../s21_string.h"

Suite *memchr_suite_create(void);
Suite *memset_suite_create(void);

/*void srunner_assembler(SRunner *sr) {
    srunner_add_suite(sr, memset_suite_create());
}*/

int main(void) {
    int failed = 0;
    SRunner *sr = srunner_create(memchr_suite_create());
//  srunner_assembler(sr);

    srunner_run_all(sr, CK_NORMAL);
    failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
