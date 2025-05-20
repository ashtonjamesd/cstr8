#include <stdio.h>
#include "../src/cstr8.h"
#include "test.c"

void test_string_new() {
    String str = string_new("Hello, World!\n");

    assert_string_eq(string_str(str), "Hello, World!\n");

    string_free(str);
}

void test_string_new_empty() {
    String str = string_new("");

    assert_string_eq(string_str(str), "");

    string_free(str);
}

void test_string_from() {
    String str1 = string_new("Hello, World!\n");
    String str2 = string_from(str1);

    assert_string_eq(string_str(str2), "Hello, World!\n");

    string_free(str1);
    string_free(str2);
}

void test_string_from_empty() {
    String str1 = string_new("");
    String str2 = string_from(str1);

    assert_string_eq(string_str(str2), "");

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

void test_string_substring_length_err() {
    String str = string_new("Hello, World!\n");
    StringResult result = string_substring(0, 100, str);

    assert_false(result.is_ok);
    assert_true(result.as.err.code == LENGTH_OF_SUBSTRING_EXCEEDS_STRING_ERR);

    string_free(str);
    string_result_free(result);
}

void test_string_substring_less_than_zero_err() {
    String str = string_new("Hello, World!\n");
    StringResult result = string_substring(0, -1, str);

    assert_false(result.is_ok);
    assert_true(result.as.err.code == LENGTH_OF_SUBSTRING_LESS_THAN_0);

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

void test_string_equals_ignore_case() {
    String str1 = string_new("Hello, World!\n");
    String str2 = string_new("hello, world!\n");

    assert_true(string_equals_ignore_case(str1, str2));

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

void test_string_char_at() {
    String str = string_new("Hello, World!\n");
    assert_char_eq(string_char_at(0, str), 'H');

    string_free(str);
}

void test_string_char_at_null() {
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

void test_string_contains_single_char() {
    String str = string_new("H");
    assert_true(string_contains('H', str));

    string_free(str);
}

void test_string_contains_empty() { 
    String str = string_new("");
    assert_false(string_contains('x', str));

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

void test_string_split_empty() {
    String str = string_empty();
    StringArrayResult result = string_split(' ', str);

    StringArray *arr = result.as.ok.arr;

    assert_true(result.is_ok);
    assert_true(result.as.ok.arr->count == 1);
    assert_string_eq(arr->items[0]._value, "");

    string_array_result_free(result);

    string_free(str);
}

void test_string_concat_char() {
    String str1 = string_new("Hello, World!");
    String str2 = string_concat_char(str1, 'A');

    assert_string_eq(string_str(str2), "Hello, World!A");

    string_free(str1);
    string_free(str2);
}

void test_string_concat_char_empty() {
    String str1 = string_new("");
    String str2 = string_concat_char(str1, 'A');

    assert_string_eq(string_str(str2), "A");

    string_free(str1);
    string_free(str2);
}

void test_string_repeat() {
    String str = string_repeat('a', 5);

    assert_string_eq(string_str(str), "aaaaa");
    string_free(str);
}

void test_string_index_of_empty_string() {
    String str = string_new("");

    assert_true(string_index_of('l', str) == -1);
    assert_true(string_index_of('\0', str) == -1);
    assert_true(string_index_of(' ', str) == -1);

    string_free(str);
}

void test_string_replace_char() {
    String str1 = string_new("123");
    String str2 = string_replace_char('1', 'a', str1);

    assert_string_eq(string_str(str2), "a23");

    string_free(str1);
    string_free(str2);
}

void test_string_replace_char_empty() {
    String str1 = string_new("");
    String str2 = string_replace_char('1', 'a', str1);

    assert_string_eq(string_str(str2), "");

    string_free(str1);
    string_free(str2);
}

void test_string_replace_char_string() {
    String str1 = string_new("Hello, World!");
    String str2 = string_replace_char('l', 'o', str1);
    String str3 = string_replace_char('e', 'd', str2);
    String str4 = string_replace_char('d', 'o', str3);

    assert_string_eq(string_str(str2), "Heooo, Worod!");
    assert_string_eq(string_str(str3), "Hdooo, Worod!");
    assert_string_eq(string_str(str4), "Hoooo, Woroo!");

    string_free(str1);
    string_free(str2);
    string_free(str3);
    string_free(str4);
}

void test_string_reverse_normal() {
    String str = string_new("Hello, World!");
    String reversed = string_reverse(str);

    assert_string_eq(string_str(reversed), "!dlroW ,olleH");

    string_free(str);
    string_free(reversed);
}

void test_string_reverse_single_char() {
    String str = string_new("A");
    String reversed = string_reverse(str);

    assert_string_eq(string_str(reversed), "A");

    string_free(str);
    string_free(reversed);
}

void test_string_reverse_empty() {
    String str = string_new("");
    String reversed = string_reverse(str);

    assert_string_eq(string_str(reversed), "");

    string_free(str);
    string_free(reversed);
}

void test_string_reverse_with_special_chars() {
    String str = string_new("\n\t!ab");
    String reversed = string_reverse(str);

    assert_string_eq(string_str(reversed), "ba!\t\n");

    string_free(str);
    string_free(reversed);
}

void test_string_char_count() {
    String str = string_new("Hello, World!");

    int count1 = string_char_count('l', str);
    int count2 = string_char_count('\n', str);
    int count3 = string_char_count('W', str);
    int count4 = string_char_count(' ', str);

    assert_true(count1 == 3);
    assert_true(count2 == 0);
    assert_true(count3 == 1);
    assert_true(count4 == 1);

    string_free(str);
}

void test_string_concat_string() {
    String str1 = string_new("Hello,");
    String str2 = string_new(" World!");
    
    String both = string_concat_string(str1, str2);

    assert_string_eq("Hello, World!", string_str(both));

    string_free(str1);
    string_free(str2);
    string_free(both);
}

void test_string_trim_left() {
    String str = string_new("     Hello, World!");
    String trimmed = string_trim_left(str);

    assert_string_eq(string_str(trimmed), "Hello, World!");

    string_free(str);
    string_free(trimmed);
}

void test_string_trim_left_empty() {
    String str = string_new("     ");
    String trimmed = string_trim_left(str);

    assert_string_eq(string_str(trimmed), "");

    string_free(str);
    string_free(trimmed);
}

void test_string_trim_right() {
    String str = string_new("Hello, World!       ");
    String trimmed = string_trim_right(str);

    assert_string_eq(string_str(trimmed), "Hello, World!");

    string_free(str);
    string_free(trimmed);
}

void test_string_trim_right_empty() {
    String str = string_new("     ");
    String trimmed = string_trim_right(str);

    assert_string_eq(string_str(trimmed), "");

    string_free(str);
    string_free(trimmed);
}

void test_string_trim() {
    String str = string_new("        Hello, World!       ");
    String trimmed = string_trim(str);

    assert_string_eq(string_str(trimmed), "Hello, World!");

    string_free(str);
    string_free(trimmed);
}

void test_string_array() {
    StringArray *arr = string_array_empty();

    String str1 = string_new("String 1");
    String str2 = string_new("String 2");
    String str3 = string_new("String 3");

    string_array_add(str1, arr);
    string_array_add(str2, arr);
    string_array_add(str3, arr);

    assert_string_eq(string_str(arr->items[0]), "String 1");
    assert_string_eq(string_str(arr->items[1]), "String 2");
    assert_string_eq(string_str(arr->items[2]), "String 3");

    string_free(str1);
    string_free(str2);
    string_free(str3);

    string_array_free(arr);
}

void test_string_array_from() {
    StringArray *arr1 = string_array_empty();

    String str1 = string_new("String 1");
    String str2 = string_new("String 2");
    String str3 = string_new("String 3");

    string_array_add(str1, arr1);
    string_array_add(str2, arr1);
    string_array_add(str3, arr1);
    
    StringArray *arr2 = string_array_from(arr1);

    assert_string_eq(string_str(arr2->items[0]), "String 1");
    assert_string_eq(string_str(arr2->items[1]), "String 2");
    assert_string_eq(string_str(arr2->items[2]), "String 3");

    string_free(str1);
    string_free(str2);
    string_free(str3);

    string_array_free(arr1);
    string_array_free(arr2);
}

void test_string_array_create_from_loop() {
    StringArray *arr = string_array_empty();
    
    for (int i = 0; i < 10; i++) {
        string_array_add(string_new("String"), arr);
    }

    for (int i = 0; i < 10; i++) {
        assert_string_eq(arr->items[i]._value, "String");
    }

    string_array_free(arr);
}

int main(void) {
    run_test(test_string_new);
    run_test(test_string_new_empty);
    run_test(test_string_from);
    run_test(test_string_from_empty);
    run_test(test_string_empty);
    run_test(test_string_substring);
    run_test(test_string_substring_empty);
    run_test(test_string_substring_length_err);
    run_test(test_string_substring_less_than_zero_err);
    run_test(test_string_len);
    run_test(test_string_equals);
    run_test(test_string_not_equals);
    run_test(test_string_equals_ignore_case);
    run_test(test_string_starts_with_char);
    run_test(test_string_ends_with_char);
    run_test(test_string_to_lower);
    run_test(test_string_to_upper);
    run_test(test_string_char_at);
    run_test(test_string_char_at_null);
    run_test(test_string_is_empty);
    run_test(test_string_first);
    run_test(test_string_last);
    run_test(test_string_contains);
    run_test(test_string_contains_empty);
    run_test(test_string_contains_single_char);
    run_test(test_string_index_of);
    run_test(test_string_split);
    run_test(test_string_split_empty);
    run_test(test_string_concat_char);
    run_test(test_string_concat_char_empty);
    run_test(test_string_repeat);
    run_test(test_string_index_of_empty_string);
    run_test(test_string_replace_char);
    run_test(test_string_replace_char_empty);
    run_test(test_string_replace_char_string);
    run_test(test_string_reverse_normal);
    run_test(test_string_reverse_with_special_chars);
    run_test(test_string_reverse_empty);
    run_test(test_string_reverse_single_char);
    run_test(test_string_char_count);
    run_test(test_string_concat_string);
    run_test(test_string_trim_left);
    run_test(test_string_trim_left_empty);
    run_test(test_string_trim_right);
    run_test(test_string_trim_right_empty);
    run_test(test_string_trim);

    run_test(test_string_array);
    run_test(test_string_array_from);

    return test_finish();
}