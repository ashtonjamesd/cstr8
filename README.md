# Cstr8

Cstr8 (see-straight) is (another) modern string utility library, designed for safety and readability.

<br/>

## Get Started

### Clone the repository

```
git clone https://github.com/ashtonjamesd/cstr8.git
cd cstr8
```


## Usage

### Include the library

```c
#include "cstr8.h"
```

### Example usage

```c
String s = string_new("Hello,World,Again");
StringArrayResult result = string_split(',', s);

if (result.is_ok) {
    StringArray *arr = result.as.ok.arr;

    for (int i = 0; i < arr->count; i++) {
        printf("Part %d: %s\n", i, string_str(arr->items[i]));
    }
    string_array_free(result.as.ok.arr);
}

string_free(s);
```

***

### Result Error Handling

Use `StringResult` and `StringArrayResult` to safely handle errors.

```
if (!result.is_ok) {
    // Handle error: result.as.err.code
}
```

***

### Dependencies

The library is intentionally minimal and only depends on:
- The C Standard Library (`stdlib.h`)

No third-party libraries are required.

***

### API

#### String Construction and Destruction

```c
String str1 = string_new("Hello, World!");

string_free(str1);

String str2 = string_empty();
string_free(str2);
```

#### Utilities

```c
int string_len(String s);
char *string_str(String s);
int string_equals(String s1, String s2);
int string_contains(char c, String s);
```

#### Iteration

```
StringIterator iter = string_iterator_new(&s);

while (string_iterator_has_next(&iter)) {
    char c = string_iterator_next(&iter);
    ...
}
```