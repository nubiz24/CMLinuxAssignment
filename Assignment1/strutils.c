#include "strutils.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Đảo ngược chuỗi tại chỗ
void str_reverse(char *str)
{
    if (str == NULL)
        return;

    int len = strlen(str);
    int i = 0, j = len - 1;
    while (i < j)
    {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i++;
        j--;
    }
}

// Loại bỏ khoảng trắng đầu và cuối
void str_trim(char *str)
{
    if (str == NULL)
        return;

    // Bỏ khoảng trắng đầu
    char *start = str;
    while (isspace((unsigned char)*start))
    {
        start++;
    }

    // Dời chuỗi về đầu nếu cần
    if (start != str)
    {
        memmove(str, start, strlen(start) + 1);
    }

    // Bỏ khoảng trắng cuối
    char *end = str + strlen(str) - 1;
    while (end >= str && isspace((unsigned char)*end))
    {
        *end = '\0';
        end--;
    }
}

// Chuyển đổi chuỗi sang số nguyên, kiểm tra lỗi
int str_to_int(const char *str, int *out_num)
{
    if (str == NULL || out_num == NULL)
        return 0;

    char *endptr;
    long val = strtol(str, &endptr, 10);

    // Kiểm tra có chuyển đổi hợp lệ không
    if (*endptr != '\0')
        return 0;

    *out_num = (int)val;
    return 1;
}
