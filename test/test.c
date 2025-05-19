#include <stdio.h>
#include "../src/cstr8.h"
#include "tests.c"

void test_string_new() {
    String str = string_new("Hello, World!\n");

    assert_string_eq(string_str(str), "Hello, World!\n");

    string_free(str);
}

void test_string_from() {
    String str1 = string_new("Hello, World!\n");
    String str2 = string_from(str1);

    assert_string_eq(string_str(str2), "Hello, World!\n");

    string_free(str1);
    string_free(str2);
}

void test_string_empty() {
    String str = string_empty();

    assert_string_eq(string_str(str), "");

    string_free(str);
}

void test_string_substring() {
    String str = string_new("Hello, World!\n");
    StringResult result = string_substring(0, 5, str);

    assert_true(result.is_ok);
    assert_string_eq(string_str(result.as.ok.value), "Hello");

    string_free(str);
    string_result_free(result);
}

void test_string_substring_empty() {
    String str = string_new("Hello, World!\n");
    StringResult result = string_substring(0, 0, str);

    assert_true(result.is_ok);
    assert_string_eq(string_str(result.as.ok.value), "");

    string_free(str);
    string_result_free(result);
}

void test_string_len() {
    String str = string_new("Hello, World!\n");

    assert_true(string_len(str) == 14);

    string_free(str);
}

void test_string_equals() {
    String str1 = string_new("Hello, World!\n");
    String str2 = string_new("Hello, World!\n");

    assert_true(string_equals(str1, str2));

    string_free(str1);
    string_free(str2);
}

void test_string_not_equals() {
    String str1 = string_new("Hello, World!\n");
    String str2 = string_new("Helrld!\n");

    assert_false(string_equals(str1, str2));

    string_free(str1);
    string_free(str2);
}

void test_string_starts_with_char() {
    String str = string_new("Hello, World!\n");

    assert_true(string_starts_with('H', str));

    string_free(str);
}

void test_string_ends_with_char() {
    String str = string_new("Hello, World!\n");

    assert_true(string_ends_with('\n', str));

    string_free(str);
}

void test_string_to_lower() {
    String str1 = string_new("Hello, World!\n");
    String str2 = string_to_lower(str1);

    assert_string_eq(string_str(str2), "hello, world!\n");

    string_free(str1);
    string_free(str2);
}

void test_string_to_upper() {
    String str1 = string_new("Hello, World!\n");
    String str2 = string_to_upper(str1);

    assert_string_eq(string_str(str2), "HELLO, WORLD!\n");

    string_free(str1);
    string_free(str2);
}

void test_char_at() {
    String str = string_new("Hello, World!\n");
    assert_char_eq(string_char_at(0, str), 'H');

    string_free(str);
}

void test_char_at_null() {
    String str = string_new("Hello, World!\n");
    assert_char_eq(string_char_at(100, str), '\0');

    string_free(str);
}

void test_string_is_empty() {
    String str1 = string_empty();
    String str2 = string_new("Hello, World!\n");

    assert(string_is_empty(str1));
    assert(!string_is_empty(str2));

    string_free(str1);
    string_free(str2);
}

void test_string_first() {
    String str = string_new("Hello, World!\n");
    assert(string_first(str) == 'H');

    string_free(str);
}

void test_string_last() {
    String str = string_new("Hello, World!\n");
    assert(string_last(str) == '\n');

    string_free(str);
}

void test_string_contains() {
    String str = string_new("Hello, World!\n");

    assert_true(string_contains('H', str));
    assert_true(string_contains('\n', str));
    assert_true(string_contains(',', str));

    assert_false(string_contains('a', str));

    string_free(str);
}

void test_string_index_of() {
    String str = string_new("Hello, World!\n");

    assert_true(string_index_of('l', str) == 2);
    assert_true(string_index_of(',', str) == 5);

    string_free(str);
}

void test_string_split() {
    String str = string_new("Hello, World!");
    StringArrayResult result = string_split(' ', str);

    StringArray *arr = result.as.ok.arr;

    assert_true(result.is_ok);
    assert_true(result.as.ok.arr->count == 2);
    assert_string_eq(arr->items[0]._value, "Hello,");
    assert_string_eq(arr->items[1]._value, "World!");

    string_array_result_free(result);

    string_free(str);
}

void test_string_array() {
    StringArray *arr = string_array_empty();

    string_array_add(string_new("String 1"), arr);
    string_array_add(string_new("String 2"), arr);
    string_array_add(string_new("String 3"), arr);

    assert_string_eq(string_str(arr->items[0]), "String 1");
    assert_string_eq(string_str(arr->items[1]), "String 2");
    assert_string_eq(string_str(arr->items[2]), "String 3");

    string_array_free(arr);
}

void test_string_array_from() {
    StringArray *arr1 = string_array_empty();

    string_array_add(string_new("String 1"), arr1);
    string_array_add(string_new("String 2"), arr1);
    string_array_add(string_new("String 3"), arr1);
    
    StringArray *arr2 = string_array_from(arr1);

    assert_string_eq(string_str(arr2->items[0]), "String 1");
    assert_string_eq(string_str(arr2->items[1]), "String 2");
    assert_string_eq(string_str(arr2->items[2]), "String 3");

    string_array_free(arr1);
    string_array_free(arr2);
}

int main(void) {
    test_string_new();
    test_string_from();
    test_string_empty();
    test_string_substring();
    test_string_substring_empty();
    test_string_len();
    test_string_equals();
    test_string_not_equals();
    test_string_starts_with_char();
    test_string_ends_with_char();
    test_string_to_lower();
    test_string_to_upper();
    test_char_at();
    test_char_at_null();
    test_string_is_empty();
    test_string_first();
    test_string_last();
    test_string_array();
    test_string_array_from();
    test_string_contains();
    test_string_index_of();
    test_string_split();

    return test_finish();
}