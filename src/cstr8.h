#ifndef CSTR8_H
#define CSTR8_H

/**
 * @brief Represents a dynamically allocated string.
 */
typedef struct {
    char *_value;
} String;


/**
 * @brief Represents a dynamic array of String instances.
 */
typedef struct {
    String *items;
    int count;
    int capacity;
} StringArray;


/**
 * @brief Represents an iterator for a cstr8 String.
 */
typedef struct {
    String *string;
    int index;
} StringIterator;


/**
 * @brief Error codes used in string operations.
 */
typedef enum {
    LENGTH_OF_SUBSTRING_EXCEEDS_STRING_ERR,
    LENGTH_OF_SUBSTRING_LESS_THAN_0,
} StringErrCode;


/**
 * @brief Represents an error returned from a string operation.
 */
typedef struct {
    StringErrCode code;
} StringErr;


/**
 * @brief Represents a successful result from a string operation.
 */
typedef struct {
    String value;
} StringOk;


/**
 * @brief Represents the result of a string operation.
 * 
 * If is_ok is true, use as.ok. Otherwise, use as.err.
 */
typedef struct {
    int is_ok;

    union {
        StringOk ok;
        StringErr err;
    } as;
} StringResult;


/**
 * @brief Represents a successful result from a string operation.
 */
typedef struct {
    StringArray *arr;
} StringArrayOk;


/**
 * @brief Represents the result of a string array operation.
 * 
 * If is_ok is true, use as.ok. Otherwise, use as.err.
 */
typedef struct {
    int is_ok;

    union {
        StringArrayOk ok;
        StringErr err;
    } as;
} StringArrayResult;


/** ========== Char Predicates ========== **/
/**
 * @brief Returns true if the given character is a lowercase letter
 */
extern int char_is_lower_letter(char c);


/**
 * @brief Returns true if the given character is an uppercase letter
 */
extern int char_is_upper_letter(char c);


/**
 * @brief Returns true if the given character is a letter
 */
extern int char_is_letter(char c);


/**
 * @brief Returns true if the given character is a digit
 */
extern int char_is_digit(char c);


/**
 * @brief Returns true if the given character is a whitespace character
 * 
 * whitespace characters:
 *   - ` `, `\t`, `\r`, `\n`, `\v`, `\f`
 * 
 */
extern int char_is_space(char c);


/**
 * @brief Returns true if the given character is a valid hexadecimal character
 */
extern int char_is_hex(char c);


/**
 * @brief Returns true if the given character is a valid binary character
 */
extern int char_is_bin(char c);


/**
 * @brief Returns true if the given character is a control character
 */
extern int char_is_control(char c);


/**
 * @brief Returns true if the given character is a punctuation character
 */
extern int char_is_punctuation(char c);


/**
 * @brief Returns true if the given character is a letter or digit character
 */
extern int char_is_alphanumeric(char c);


/**
 * @brief Returns true if the given character is a vowel
 */
extern int char_is_vowel(char c);


/**
 * @brief Returns true if the given character is a consonant
 */
extern int char_is_consonant(char c);



/** ========== String Utilities ========== **/

/**
 * @brief Creates a new cstr8 string instance from a null-terminated C string.
 * 
 * The returned string must be freed with string_free().
 */
extern String string_new(const char *val);


/**
 * @brief Creates a new empty cstr8 string.
 * 
 * The returned string must be freed with string_free().
 */
extern String string_empty();


/**
 * @brief Creates a new cstr8 string by copying another String instance.
 * 
 * The returned string must be freed with string_free().
 */
extern String string_from(String s);


/**
 * @brief Frees a cstr8 string instance.
 */
extern void string_free(String s);


/**
 * @brief Frees the result of a string operation.
 */
extern void string_result_free(StringResult result);


/**
 * @brief Creates a new cstr8 string filled with 'c', 'n' times
 * 
 * The returned string must be freed with string_free().
 */
extern String string_repeat(char c, int n);


/**
 * @brief Returns a substring from the given string starting at `start` with length `len`.
 * 
 * Returns a StringResult which must be checked for errors.
 * If successful, the result's value must be freed with string_free().
 */
extern StringResult string_substring(int start, int len, String s);


/**
 * @brief Returns a new string instance that is 's' with 'c' appended to the end.
 */
extern String string_concat_char(String s, char c);


/**
 * @brief Returns a new string instance that is the concatenation of 's1' and 's2'.
 */
extern String string_concat_string(String s1, String s2);


/**
 * @brief Returns the length of the string (number of characters).
 */
extern int string_len(String s);


/**
 * @brief Returns the underlying C string (char pointer).
 * 
 * Do not modify or free this pointer directly.
 */
extern char* string_str(String s);


/**
 * @brief Compares two strings for equality.
 * 
 * @return 1 if equal, 0 otherwise.
 */
extern int string_equals(String s1, String s2);


/**
 * @brief Compares two strings for equality ignoring case
 * 
 * @return 1 if equal, 0 otherwise.
 */
extern int string_equals_ignore_case(String s1, String s2);


/**
 * @brief Checks if the string starts with the specified character.
 * 
 * @return 1 if true, 0 otherwise.
 */
extern int string_starts_with_char(char c, String s);


/**
 * @brief Checks if the string 'a' starts with the string 'b'
 * 
 * @return 1 if true, 0 otherwise.
 */
extern int string_starts_with_string(String a, String b);


/**
 * @brief Checks if the string ends with the specified character.
 * 
 * @return 1 if true, 0 otherwise.
 */
extern int string_ends_with(char c, String s);


/**
 * @brief Checks if the string is empty.
 * 
 * @return 1 if empty, 0 otherwise.
 */
extern int string_is_empty(String s);


/**
 * @brief Checks if the string contains the specified character.
 * 
 * @return 1 if found, 0 otherwise.
 */
extern int string_contains(char c, String s);


/**
 * @brief Returns the character at the specified index in the string.
 */
extern char string_char_at(int i, String s);


/**
 * @brief Returns the first character of the string.
 */
extern char string_first(String s);


/**
 * @brief Returns the last character of the string.
 */
extern char string_last(String s);

/**
 * @brief Returns the uppercase variant of a lowercase character
 */
extern char string_char_to_upper(char c);


/**
 * @brief Returns the lowercase variant of an uppercase character
 */
extern char string_char_to_lower(char c);


/**
 * @brief Converts the string to lowercase.
 * 
 * The returned string must be freed with string_free().
 */
extern String string_to_lower(String s);


/**
 * @brief Returns a new string that is the reversal of 's'
 * 
 * The returned string must be freed with string_free().
 */
extern String string_reverse(String s);


/**
 * @brief Converts the string to uppercase.
 * 
 * The returned string must be freed with string_free().
 */
extern String string_to_upper(String s);

/**
 * @brief Returns a new instance of a string with all instances of 'replace' with 'with'.
 * 
 * The returned string must be freed with string_free().
 */
extern String string_replace_char(char replace, char with, String s);


/**
 * @brief Returns a new instance of a string with whitespace characters at the beginning and end removed.
 */
extern String string_trim(String s);


/**
 * @brief Returns a new instance of a string with leading whitespace characters removed.
 */
extern String string_trim_left(String s);


/**
 * @brief Returns a new instance of a string with trailing whitespace characters removed.
 */
extern String string_trim_right(String s);


/**
 * @brief Returns the index of the first occurrence of 'c'
 * 
 * Returns -1 if 'c' is not contained in 's'
 */
extern int string_index_of(char c, String s);


/**
 * @brief Returns the number of occurrences of 'c' in 's'
 */
extern int string_char_count(char c, String s);


/**
 * @brief Splits the given string into substrings by the specified delimiter character.
 * 
 * Returns a StringResult which must be checked for errors.
 * If successful, the result's items must be freed with string_array_free().
 */
extern StringArrayResult string_split(char c, String s);



/** ========== String Array Utilities ========== **/

/**
 * @brief Creates a new StringArray from an array of Strings.
 * 
 * The returned array must be freed with string_array_free().
 */
extern StringArray *string_array_new(String *strs, int count);


/**
 * @brief Creates an empty StringArray.
 * 
 * The returned array must be freed with string_array_free().
 */
extern StringArray *string_array_empty();


/**
 * @brief Creates a new StringArray by copying an existing one.
 * 
 * The returned array must be freed with string_array_free().
 */
extern StringArray *string_array_from(StringArray *arr);


/**
 * @brief Frees a StringArray and all of its contained Strings.
 */
extern void string_array_free(StringArray *arr);


/**
 * @brief Frees a instance of a StringArrayResult.
 */
extern void string_array_result_free(StringArrayResult result);


/**
 * @brief Adds a String to a StringArray.
 * 
 * The array will expand as needed.
 */
extern void string_array_add(String s, StringArray *arr);



/** ========== String Iterators ========== **/

/**
 * @brief Returns a new instance of a StringIterator
 */
extern StringIterator string_iterator_new(String *s);


/**
 * @brief Checks if there are more characters to iterate over.
 */
extern int string_iterator_has_next(StringIterator *iter);


/**
 * @brief Returns the next character and advances the iterator.
 */
extern char string_iterator_next(StringIterator *iter);


#endif