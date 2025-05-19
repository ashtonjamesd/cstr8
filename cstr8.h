#ifndef CSTRING_H
#define CSTRING_H

typedef struct {
    char *_value;
} String;

typedef enum {
    LENGTH_OF_SUBSTRING_EXCEEDS_STRING_ERR,
    LENGTH_OF_SUBSTRING_LESS_THAN_0,
} StringErrCode;

typedef struct {
    StringErrCode code;
} StringErr;

typedef struct {
    String value;
    StringArray array;
} StringOk;

typedef struct {
    String *array;
    int count;
    int capacity;
} StringArray;

typedef struct {
    int is_ok;

    union {
        StringOk ok;
        StringErr err;
    } as;
} StringResult;

extern String string_new(const char *val);
extern String string_empty();
extern String string_from(String s);

extern void   string_free(String s);

extern        StringResult string_substring(int start, int len, String s);
extern        StringResult string_split(char c, String s);

extern int    string_len(String str);
extern int    string_equals(String s1, String s2);
extern int    string_starts_with(char c, String s);
extern int    string_ends_with(char c, String s);

extern char   string_char_at(int i, String s);
extern String string_to_lower(String s);
extern String string_to_upper(String s);

#endif
