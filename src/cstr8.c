#include <stdlib.h>

#include "cstr8.h"

static char *err_str(StringErrCode code) {
    switch (code)  {
        case LENGTH_OF_SUBSTRING_EXCEEDS_STRING_ERR:
            return "the length of the string_substring exceeds the length of the source string.";
        case LENGTH_OF_SUBSTRING_LESS_THAN_0:
            return "the length of the string_substring is less than zero";
        default:
            return "umm something went wrong";
    }
}

static int _len(char *str) {
    int i, t = 0;
    for (i = 0; str[i]; i++) {
        t++;
    }

    return t;
}

static StringResult string_ok(char *value) {
    StringResult result;
    result.is_ok = 1;
    result.as.ok.value = string_new(value);

    return result;
}

static StringArrayResult string_array_ok(String *items, int count) {
    StringArrayResult result;
    result.as.ok.arr = string_array_new(items, count);

    return result;
}

static StringResult err(StringErrCode code) {
    StringResult result;
    result.is_ok = 0;
    result.as.err.code = code;

    return result;
}

int string_len(String str) {
    return _len(str._value);
}

char *string_str(String str) {
    return str._value;
}

char string_char_at(int i, String str) {
    if (string_len(str) <= i) return '\0';
    return str._value[i];
}

char string_first(String str) {
    return string_char_at(0, str);
}

char string_last(String str) {
    return string_char_at(string_len(str) - 1, str);
}

char string_char_to_upper(char c) {
    if (c >= 'a' && c <= 'z')
        return c - ('a' - 'A');
    return c;
}

char string_char_to_lower(char c) {
    if (c >= 'A' && c <= 'Z')
        return c + ('a' - 'A');
    return c;
}

static void _set_char_at(int i, char c, String str) {
    str._value[i] = c;
}

String string_to_lower(String str) {
    String _str = string_from(str);

    StringIterator iter = string_iterator_new(&str);
    int i = 0;
    while (string_iterator_has_next(&iter)) {
        char c = string_iterator_next(&iter);
        
        if (string_char_is_upper_letter(c)) {
            _set_char_at(i++, c + ('a' - 'A'), _str);
        } else {
            _set_char_at(i++, c, _str);
        }
    }

    return _str;
}

static void _terminate_string(String s, int len) {
    _set_char_at(len, '\0', s);
}

String string_reverse(String s) {
    int len = string_len(s);
    String reversed = string_empty();

    free(reversed._value);
    reversed._value = malloc(len + 1);

    int i;
    for (i = 0; i < len; i++) {
        _set_char_at(i, s._value[len - 1 - i], reversed);
    }

    _terminate_string(reversed, len);
    return reversed;
}

String string_to_upper(String str) {
    String _str = string_from(str);
    StringIterator iter = string_iterator_new(&str);
    
    while (string_iterator_has_next(&iter)) {
        char c = string_iterator_next(&iter);

        if (string_char_is_lower_letter(c)) {
            _set_char_at(iter.index - 1, c + ('A' - 'a'), _str);
        } else {
            _set_char_at(iter.index - 1, c, _str);
        }
    }

    return _str;
}

int string_char_is_lower_letter(char c) {
    return ('a' <= c && c <= 'z');
}

int string_char_is_upper_letter(char c) {
    return ('A' <= c && c <= 'Z');
}

int string_char_is_letter(char c) {
    return string_char_is_lower_letter(c) || string_char_is_upper_letter(c);
}

int string_char_is_digit(char c) {
    return ('0' <= c && c <= '9');
}

int string_char_is_space(char c) {
    return c == ' '
        || c == '\t'
        || c == '\r'
        || c == '\n'
        || c == '\v'
        || c == '\f';
}

int string_char_is_hex(char c) {
    return (c >= '0' && c <= '9') ||
           (c >= 'a' && c <= 'f') ||
           (c >= 'A' && c <= 'F');
}


int string_char_is_bin(char c) {
    return c == '1' || c == '0';
}

int string_char_is_control(char c) {
    return (c >= 0 && c <= 31) || c == 127;
}

int string_char_is_punctuation(char c) {
    return (c >= 33  && c <=  47)  || /* !"#$%&'()*+,-./ */
           (c >= 58  && c <=  64)  || /* :;<=>?@ */
           (c >= 91  && c <=  96)  || /* [\]^_` */
           (c >= 123 && c <= 126);    /* {|}~ */
}

int string_char_is_alphanumeric(char c) {
    return string_char_is_letter(c) || string_char_is_digit(c);
}

int string_char_is_vowel(char c) {
    c = string_char_to_lower(c);
    
    return c == 'a'
        || c == 'e'
        || c == 'i'
        || c == 'o'
        || c == 'u';
}

int string_char_is_consonant(char c) {
    return string_char_is_letter(c) && !string_char_is_vowel(c);
}

String string_replace_char(char replace, char with, String str) {
    String _str = string_from(str);
    StringIterator iter = string_iterator_new(&str);

    while (string_iterator_has_next(&iter)) {
        if (string_iterator_next(&iter) == replace) {
            _set_char_at(iter.index - 1, with, _str);
        }
    }

    return _str;
}

String string_trim(String s) {
    int len = string_len(s);
    int start = 0;
    int end = len - 1;

    while (start <= end && string_char_is_space(s._value[start])) {
        start++;
    }

    if (start > end) {
        return string_empty();
    }

    while (end >= start && string_char_is_space(s._value[end])) {
        end--;
    }

    int new_len = end - start + 1;
    StringResult result = string_substring(start, new_len, s);
    if (!result.is_ok) {
        return string_empty();
    }

    return result.as.ok.value;
}


String string_trim_left(String s) {
    int len = string_len(s);
    int start = 0;

    while (start < len && string_char_is_space(s._value[start])) {
        start++;
    }

    if (start == len) {
        return string_empty();
    }

    StringResult result = string_substring(start, len - start, s);
    if (!result.is_ok) {
        return string_empty();
    }
    
    String trimmed = string_from(result.as.ok.value);
    string_result_free(result);

    return trimmed;
}

String string_trim_right(String s) {
    int len = string_len(s);
    int end = len - 1;

    while (end >= 0 && string_char_is_space(s._value[end])) {
        end--;
    }

    if (end < 0) {
        return string_empty();
    }

    StringResult result = string_substring(0, end + 1, s);
    if (!result.is_ok) {
        return string_empty();
    }

    String trimmed = string_from(result.as.ok.value);
    string_result_free(result);
    
    return trimmed;
}


int string_index_of(char c, String str) {
    StringIterator iter = string_iterator_new(&str);

    while (string_iterator_has_next(&iter)) {
        if (string_iterator_next(&iter) == c) {
            return iter.index - 1;
        }
    }

    return -1;
}

int string_char_count(char c, String s) {
    int count = 0;
    
    StringIterator iter = string_iterator_new(&s);
    while (string_iterator_has_next(&iter)) {
        if (string_iterator_next(&iter) == c) {
            count++;
        }
    }

    return count;
}

int string_starts_with_char(char c, String str) {
    if (string_len(str) == 0) return 0;
    return string_first(str) == c;
}

int string_starts_with_string(String a, String b) {
    StringIterator iter = string_iterator_new(&b);

    while (string_iterator_has_next(&iter)) {
        char c = string_iterator_next(&iter);

        if (string_char_at(iter.index - 1, a) != c) {
            return 0;
        }
    }

    return 1;

    for (int i = 0; i < string_len(b); i++) {
        char c = string_char_at(i, b);

        if (string_char_at(i, a) != c) {
            return 0;
        }
    }

    return 1;
}

int string_ends_with(char c, String str) {
    if (string_len(str) == 0) return 0;
    return string_last(str) == c;
}

StringResult string_substring(int start, int len, String str) {
    if (len < 0) {
        return err(LENGTH_OF_SUBSTRING_LESS_THAN_0);
    }

    char *_str = (char *)malloc(len + 1);

    int i;
    for (i = start; i < len + start; i++) {
        if (i >= string_len(str)) {
            free(_str);
            return err(LENGTH_OF_SUBSTRING_EXCEEDS_STRING_ERR);
        }

        _str[i - start] = str._value[i];
    }
    _str[len] = '\0';

    StringResult result = string_ok(_str);
    free(_str);

    return result;
}

String string_concat_char(String str, char c) {
    int len = string_len(str);

    char *new_val = malloc(len + 2);
    
    StringIterator iter = string_iterator_new(&str);
    while (string_iterator_has_next(&iter)) {
        new_val[iter.index] = string_iterator_next(&iter);
    }

    new_val[len] = c;
    new_val[len + 1] = '\0';
    
    String _str;
    _str._value = new_val;

    return _str;
}

String string_concat_string(String s1, String s2) {
    int len1 = string_len(s1);
    int len2 = string_len(s2);
    int total_len = len1 + len2;

    char *new_val = malloc(total_len + 1);

    int i;
    for (i = 0; i < len1; i++) {
        new_val[i] = s1._value[i];
    }

    for (i = 0; i < len2; i++) {
        new_val[len1 + i] = s2._value[i];
    }

    new_val[total_len] = '\0';

    String result;
    result._value = new_val;

    return result;
}


StringArrayResult string_split(char c, String str) {
    StringArray *parts = string_array_empty();
    StringIterator iter = string_iterator_new(&str);

    String current = string_empty();

    while (string_iterator_has_next(&iter)) {
        char _c = string_iterator_next(&iter);

        if (_c == c) {
            string_array_add(current, parts);
            string_free(current);
            current = string_empty();
        } else {
            int len = string_len(current);
            current._value = realloc(current._value, len + 2);
            _set_char_at(len, _c, current);
            _terminate_string(current, len + 1);
        }
    }

    string_array_add(current, parts);
    string_free(current);

    StringArrayResult result;
    result.is_ok = 1;
    result.as.ok.arr = parts;

    return result;
}

void string_result_free(StringResult result) {
    if (result.is_ok) {
        string_free(result.as.ok.value);
    }
}

void string_array_result_free(StringArrayResult result) {
    if (result.is_ok) {
        string_array_free(result.as.ok.arr);
    }
}

StringArray *string_array_from(StringArray *arr) {
    StringArray *_arr = string_array_empty();

    int i;
    for (i = 0; i < arr->count; i++) {
        string_array_add(arr->items[i], _arr);
    }

    return _arr;
}

StringArray *string_array_new(String *strs, int count) {
    StringArray *_arr = string_array_empty();
    
    int i;
    for (i = 0; i < count; i++) {
        string_array_add(strs[i], _arr);
    }

    return _arr;
}

StringArray *string_array_empty() {
    StringArray *_array = malloc(sizeof(StringArray));
    _array->capacity = 1;
    _array->items = malloc(sizeof(String) * _array->capacity);
    _array->count = 0;

    return _array;
}

void string_array_add(String str, StringArray *arr) {
    if (arr->count >= arr->capacity) {
        arr->capacity *= 2;
        arr->items = realloc(arr->items, sizeof(String) * arr->capacity);
    }

    arr->items[arr->count++] = string_from(str);
}

void string_array_free(StringArray *arr) {
    if (!arr) return;

    int i;
    for (i = 0; i < arr->count; i++) {
        free(arr->items[i]._value);
    }

    free(arr->items);
    free(arr);
}

int string_equals(String str1, String str2) {
    if (string_len(str1) != string_len(str2)) {
        return 0;
    }

    StringIterator iter1 = string_iterator_new(&str1);
    StringIterator iter2 = string_iterator_new(&str2);

    while (string_iterator_has_next(&iter1) && string_iterator_has_next(&iter2)) {
        if (string_iterator_next(&iter1) != string_iterator_next(&iter2)) {
            return 0;
        }
    }

    return 1;
}

int string_equals_ignore_case(String s1, String s2) {
    String s1lower = string_to_lower(s1);
    String s2lower = string_to_lower(s2);

    int equal = string_equals(s1lower, s2lower);

    string_free(s1lower);
    string_free(s2lower);

    return equal;
}

int string_is_empty(String str) {
    String empty = string_empty();
    
    int result = !str._value || string_equals(empty, str);
    string_free(empty);

    return result;
}

int string_contains(char c, String s) {
    StringIterator iter = string_iterator_new(&s);

    while (string_iterator_has_next(&iter)) {
        if (string_iterator_next(&iter) == c) {
            return 1;
        }
    }

    return 0;
}

String string_empty() {
    String _str;
    _str._value = malloc(1);
    _terminate_string(_str, 0);

    return _str;
}

String string_new(const char *str) {
    String _str;

    int len = _len((char *)str);
    _str._value = malloc(len + 1);

    int i;
    for (i = 0; i < len; i++) {
        _str._value[i] = str[i];
    }
    _str._value[len] = '\0';

    return _str;
}


String string_from(String str) {
    return string_new(str._value);
}

String string_repeat(char c, int n) {
    String base_str = string_empty();
    
    int i;
    for (i = 0; i < n; i++) {
        String _str = string_concat_char(base_str, c);
        string_free(base_str);
        base_str = string_from(_str);
        string_free(_str);
    }

    return base_str;
}

void string_free(String str) {
    if (!str._value) return;
    free(str._value);
}

StringIterator string_iterator_new(String *str) {
    StringIterator iterator;
    iterator.string = str;
    iterator.index = 0;

    return iterator;
}

int string_iterator_has_next(StringIterator *iter) {
    return iter->index < string_len(*iter->string);
}

char string_iterator_next(StringIterator *iter) {
    return string_str(*iter->string)[iter->index++];
}