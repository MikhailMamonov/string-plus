#include <check.h>
#include <stdlib.h>

// Suite *memchr_suite_create(void);
Suite *memcmp_suite_create(void);

int main(void) {
    int failed = 0;
    SRunner *sr = srunner_create(memcmp_suite_create());

    // когда добавишь другие suite — раскомментируй и добавь сюда:
    // srunner_add_suite(sr, memchr_suite_create());

    srunner_run_all(sr, CK_NORMAL);
    failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
