#include "test_memcpy.h"

TEST_CASES(string_tests,
    {"Hello",5 ,  "basic"},
    {"Hello, world.",13, "full"},
    {"World", 6, "with null terminator"},
    {"Test", 4, "partial" },
    {"Hello, world.",5 , "partial_5_bytes"},
    {"", 1, "null terminator"}, 
    {"A", 1, "single char"},
    {"Long string for testing purposes", 30, "long string"}
)

TEST_CASES(int_tests,
    {(int[]){1,2,3,4,5}, 5* sizeof(int),  "5 ints"},
    {(int[]){100,200,300},3 * sizeof(int), "3 ints"}, 
    {(int[]){-1, -2, -3}, 3 * sizeof(int), "negative ints"}
)


TEST_CASES(edge_tests,
    {"", 0, "zero size"},
    {"\x00\x01\x02\x03", 4, "binary with nulls"}, 
    {"Hello\x00World", 11, "string with embedded null"},
    {"\x00\x00\x00\x00", 4, "all nulls"},  
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

    TCase *tc_edge = tcase_create("Edge tests");
    tcase_add_test(tc_edge, test_edge_tests);
    suite_add_tcase(s, tc_edge);
    return s;
}
