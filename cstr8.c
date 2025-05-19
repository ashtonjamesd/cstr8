#include <stdio.h>
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

static int _internal_len(char *str) {
    int t = 0;
    for (int i = 0; str[i]; i++) {
        t++;
    }

    return t;
}

static StringResult ok(char *value) {
    StringResult result;
    result.is_ok = 1;
    result.as.ok.value = string_new(value);

    return result;
}

static StringResult err(StringErrCode code) {
    StringResult result;
    result.is_ok = 0;
    result.as.err.code = code;

    return result;
}

int string_len(String str) {
    return _internal_len(str._value);
}

char string_char_at(int i, String s) {
    if (string_len(s) <= i) return '\0';
    return s._value[i];
}

String string_to_lower(String s) {
    String str = string_from(s);

    for (int i = 0; i < string_len(s); i++) {
        char c = string_char_at(i, s);

        if (c >= 'A' && c <= 'Z') {
            str._value[i] = c + ('a' - 'A');
        } else {
            str._value[i] = c;
        }
    }

    return str;
}

String string_to_upper(String s) {
    String str = string_from(s);

    for (int i = 0; i < string_len(s); i++) {
        char c = string_char_at(i, s);

        if (c >= 'a' && c <= 'z') {
            str._value[i] = c + ('A' - 'a');
        } else {
            str._value[i] = c;
        }
    }

    return str;
}

int string_starts_with(char c, String s) {
    if (string_len(s) == 0) return 0;
    return string_char_at(0, s) == c;
}

int string_ends_with(char c, String s) {
    if (string_len(s) == 0) return 0;
    return string_char_at(string_len(s) - 1, s) == c;
}

StringResult string_substring(int start, int len, String s) {
    if (len < 0) {
        return err(LENGTH_OF_SUBSTRING_LESS_THAN_0);
    }

    char *str = malloc(sizeof(len - start));

    for (int i = start; i < len + start; i++) {
        if (i >= _internal_len(s._value)) {
            return err(LENGTH_OF_SUBSTRING_EXCEEDS_STRING_ERR);
        }

        str[i - start] = s._value[i];
    }
    str[len] = '\0';

    return ok(str);
}

StringResult string_split(char c, String s) {
    return ok("");
}

int string_equals(String s1, String s2) {
    if (string_len(s1) != string_len(s2)) {
        return 0;
    }

    for (int i = 0; i < string_len(s1); i++) {
        if (s1._value[i] != s2._value[i]) {
            return 0;
        }
    }

    return 1;
}

int string_is_null_or_empty(String str) {
    return !str._value || string_equals(str, string_empty());
}

String string_empty() {
    String _str;
    _str._value = "";

    return _str;
}

String string_new(const char *str) {
    String _str;
    _str._value = malloc(sizeof(str));

    int i;
    for (i = 0; str[i] != '\0'; i++) {
        _str._value[i] = str[i];
    }
    _str._value[i] = '\0';

    return _str;
}

String string_from(String str) {
    return string_new(str._value);
}

void string_free(String str) {
    if (!str._value) return;
    free(str._value);
   
    str._value[0] = '\0';
}

int main() {
    String str = string_new("Hello, World!");
    String lowered = string_to_upper(str);

    printf("%s", lowered);


    return 0;
}
