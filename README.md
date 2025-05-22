# Cstr8

Cstr8 (see-straight) is (another) modern string utility library, designed for safety and readability.

<br/>

## Get Started

### Clone the repository

```
git clone https://github.com/ashtonjamesd/cstr8.git
```

<br/>

## Usage

### Include the library

```c
#include "cstr8.h"
```

### Example usage

```c
// allocates and returns a String with a pointer to a char *
String s = string_new("Hello,World,Again");
StringArrayResult result = string_split(',', s);

if (result.is_ok) {
    StringArray *arr = result.as.ok.arr;

    // Prints:
    //   Part 0: Hello
    //   Part 1: World
    //   Part 2: Again
    for (int i = 0; i < arr->count; i++) {
        printf("  Part %d: %s\n", i, string_str(arr->items[i]));
    }

    // result is ok here
    string_array_free(result.as.ok.arr);
}

string_free(s);
```


<br/>

### Char Predicate Utilities
```
int string_char_is_lower_letter(char c);
int string_char_is_upper_letter(char c);
int string_char_is_letter(char c);
int string_char_is_digit(char c);
int string_char_is_space(char c);
int string_char_is_hex(char c);
int string_char_is_bin(char c);
int string_char_is_control(char c);
int string_char_is_punctuation(char c);
int string_char_is_alphanumeric(char c);
int string_char_is_vowel(char c);
int string_char_is_consonant(char c);
```


<br/>

### String Iterators
Safely traverse strings with string iterators.

```
StringIterator iter = string_iterator_new(&str2);

while (string_iterator_has_next(&iter)) {
    char c = string_iterator_next(&iter);

    if (string_char_at(iter.index - 1, str1) != c) {
        return 0;
    }
}

return 1;
```


<br/>

### API

#### String Construction and Destruction

```c
String str1 = string_new("Hello, World!");

string_free(str1);

String str2 = string_empty();
string_free(str2);
```


<br/>

#### String Utilities
A wide range of utilities for manipulating strings.

```c
String string_new(const char *val);
String string_empty();
String string_from(String s);
String string_repeat(char c, int n);
StringResult string_substring(int start, int len, String s);
String string_concat_string(String s1, String s2);
int string_len(String s);
int string_equals(String s1, String s2);
int string_equals_ignore_case(String s1, String s2);
int string_starts_with_string(String a, String b);
char string_char_at(int i, String s);
String string_to_lower(String s);
String string_reverse(String s);
String string_to_upper(String s);
String string_replace_char(char replace, char with, String s);
String string_trim(String s);
int string_index_of(char c, String s);
StringArrayResult string_split(char c, String s);

// see src/cstr8.h for a full list
```


<br/>

### Result Error Handling

Use `StringResult` and `StringArrayResult` to safely handle errors.

```
if (!result.is_ok) {
    // Handle error: result.as.err.code
}
```


<br/>

### Dependencies

The library is intentionally minimal and only depends on:
- The C Standard Library (`stdlib.h`)

No third-party libraries are required.

