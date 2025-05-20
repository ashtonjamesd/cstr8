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
    int t = 0;
    for (int i = 0; str[i]; i++) {
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

    for (int i = 0; i < len; i++) {
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

int string_index_of(char c, String str) {
    StringIterator iter = string_iterator_new(&str);

    while (string_iterator_has_next(&iter)) {
        if (string_iterator_next(&iter) == c) {
            return iter.index - 1;
        }
    }

    return -1;
}

int string_starts_with(char c, String str) {
    if (string_len(str) == 0) return 0;
    return string_first(str) == c;
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

    for (int i = start; i < len + start; i++) {
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

StringArrayResult string_split(char c, String str) {
    StringArray *parts = string_array_empty();
    StringIterator iter = string_iterator_new(&str);

    String current = string_empty();

    while (string_iterator_has_next(&iter)) {
        char _c = string_iterator_next(&iter);

        if (_c == c) {
            string_array_add(current, parts);
            current = string_empty();
        } else {
            int len = string_len(current);
            current._value = realloc(current._value, len + 2);
            _set_char_at(len, _c, current);
            _terminate_string(current, len + 1);
        }
    }

    string_array_add(current, parts);

    StringArrayResult result;
    result.is_ok = 1;
    result.as.ok.arr = parts;

    return result;
}

void string_result_free(StringResult result) {
    if (result.is_ok) {
        free(result.as.ok.value._value);
    }
}

void string_array_result_free(StringArrayResult result) {
    if (result.is_ok) {
        string_array_free(result.as.ok.arr);
    }
}

StringArray *string_array_from(StringArray *arr) {
    StringArray *_arr = string_array_empty();

    for (int i = 0; i < arr->count; i++) {
        string_array_add(string_from(arr->items[i]), _arr);
    }

    return _arr;
}

StringArray *string_array_new(String *strs, int count) {
    StringArray *_arr = string_array_empty();
    _arr->items = malloc(sizeof(String) * count);
    _arr->capacity = count;
    
    for (int i = 0; i < count; i++) {
        _arr->items[i] = strs[i];
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

    arr->items[arr->count++] = str;
}

void string_array_free(StringArray *arr) {
    if (!arr) return;
    for (int i = 0; i < arr->count; i++) {
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
    _str._value = malloc(sizeof(str));

    int i;
    for (i = 0; str[i] != '\0'; i++) {
        _set_char_at(i, str[i], _str);
    }
    _terminate_string(_str, i);

    return _str;
}

String string_from(String str) {
    return string_new(str._value);
}

String string_repeat(char c, int n) {
    String base_str = string_empty();
    
    for (int i = 0; i < n; i++) {
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