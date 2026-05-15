#include "test_memcpy.h"

TEST_CASES(string_tests,
    {"Hello",5 ,  "basic", 0, 0},
    {"Hello, world.",13, "full", 0, 0},
    {"World", 6, "with null terminator", 0, 0},
    {"Test", 4, "partial" , 0, 0},
    {"Hello, world.",5 , "partial_5_bytes", 0, 0},
    {"", 1, "null terminator", 0, 0}, 
    {"A", 1, "single char", 0, 0},
    {"Long string for testing purposes", 30, "long string", 0, 0}
)

TEST_CASES(int_tests,
    {(int[]){1,2,3,4,5}, 5* sizeof(int),  "5 ints", 0, 0},
    {(int[]){100,200,300},3 * sizeof(int), "3 ints", 0, 0}, 
    {(int[]){-1, -2, -3}, 3 * sizeof(int), "negative ints", 0, 0}
)

// Тестовые наборы с NULL
TEST_CASES(null_pointer_tests,
    {s21_NULL, 0, "src = NULL, size = 0", 1, 0},
    {s21_NULL, 5, "src = NULL, size > 0", 1, 0},
    {"test", 0, "dest = NULL, size = 0", 0, 1},
    {"test", 5, "dest = NULL, size > 0", 0, 1},
    {s21_NULL, 0, "both NULL, size = 0", 1, 1},
    {s21_NULL, 10, "both NULL, size > 0", 1, 1}
)

TEST_CASES(edge_tests,
    {"", 0, "zero size", 0, 0},
    {"\x00\x01\x02\x03", 4, "binary with nulls", 0, 0}, 
    {"Hello\x00World", 11, "string with embedded null", 0, 0},
    {"\x00\x00\x00\x00", 4, "all nulls", 0, 0},  
);



// Функция, которую вызовет Runner
Suite *memcpy_suite_create(void) {
    Suite *s = suite_create("memcpy");

    TCase *tc_string = tcase_create("String tests");
    tcase_add_test(tc_string, test_string_tests);
    suite_add_tcase(s, tc_string);
    
    TCase *tc_int = tcase_create("Integer tests");
    tcase_add_test(tc_int, test_int_tests);
    suite_add_tcase(s, tc_int);
    
    TCase *tc_null = tcase_create("NULL pointer tests");
    tcase_add_test(tc_null, test_null_pointer_tests);
    suite_add_tcase(s, tc_null);
    
    TCase *tc_edge = tcase_create("Edge tests");
    tcase_add_test(tc_edge, test_edge_tests);
    suite_add_tcase(s, tc_edge);
    return s;
}
