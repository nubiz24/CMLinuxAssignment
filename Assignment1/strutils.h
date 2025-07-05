#ifndef STRUTILS_H
#define STRUTILS_H

// Đảo ngược chuỗi tại chỗ
void str_reverse(char *str);

// Loại bỏ khoảng trắng đầu và cuối chuỗi
void str_trim(char *str);

// Chuyển đổi chuỗi sang số nguyên một cách an toàn
// Trả về 1 nếu thành công, 0 nếu thất bại
int str_to_int(const char *str, int *out_num);

#endif
