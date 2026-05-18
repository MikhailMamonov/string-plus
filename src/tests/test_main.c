#include "../s21_string.h"
#include <check.h>
#include <stdlib.h>

Suite *memchr_suite_create(void);
Suite *memcpy_suite_create(void);
Suite *strerror_suite_create(void);
Suite *strchr_suite_create(void);
Suite *memset_suite_create(void);
Suite *strcspn_suite_create(void);
Suite *strrchr_suite_create(void);

void assemble_srunner(SRunner *sr) {
  srunner_add_suite(sr, memcpy_suite_create());
  srunner_add_suite(sr, strerror_suite_create());
  srunner_add_suite(sr, strchr_suite_create());
  srunner_add_suite(sr, strcspn_suite_create());
  srunner_add_suite(sr, memset_suite_create());
  srunner_add_suite(sr, strrchr_suite_create());
}

int main(void) {
  int failed = 0;
  SRunner *sr = srunner_create(memchr_suite_create());
  assemble_srunner(sr);

  srunner_run_all(sr, CK_NORMAL);
  failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
