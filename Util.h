#ifndef _UTIL_H_
#define _UTIL_H_

#if defined(_WIN32) && defined(_MSC_VER)
	typedef __int64 s64;
	typedef unsigned __int64 u64;
#else
	typedef long long int s64;
	typedef unsigned long long int u64;
#endif

typedef unsigned long int u32;
typedef signed long int s32;
typedef unsigned short int u16;
typedef signed short int s16;
typedef unsigned char u8;
typedef signed char s8;

int get_file_size(const char *file_path, u64 *size);
int read_file(const char *file_path, u8 *data, u64 size);
int write_file(const char *file_path, u8 *data, u64 size);
const char* str_c(const char* a, const char* b);

#endif
