#include <stdio.h>
#include "strutils.h"

int main()
{
    // Test str_reverse
    char s1[] = "Hello, World!";
    str_reverse(s1);
    printf("Reversed: \"%s\"\n", s1);

    // Test str_trim
    char s2[] = "   OpenAI GPT   ";
    str_trim(s2);
    printf("Trimmed: \"%s\"\n", s2);

    // Test str_to_int
    const char *s3 = "123";
    int value;
    if (str_to_int(s3, &value))
    {
        printf("Converted to int: %d\n", value);
    }
    else
    {
        printf("Failed to convert: \"%s\"\n", s3);
    }

    // Test str_to_int with invalid string
    const char *s4 = "abc123";
    if (str_to_int(s4, &value))
    {
        printf("Converted to int: %d\n", value);
    }
    else
    {
        printf("Failed to convert: \"%s\"\n", s4);
    }

    return 0;
}
