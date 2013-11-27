#include <sys\stat.h>
#include <iostream>
#include "Util.h"

int get_file_size(const char *file_path, u64 *size) {
	struct stat stat_buf;

	if (!file_path || !size)
		return -1;

	if (stat(file_path, &stat_buf) < 0)
		return -1;

	*size = stat_buf.st_size;

	return 0;
}

int read_file(const char *file_path, u8 *data, u64 size) {
	FILE *fp;
	struct stat stat_buf;

	if (!file_path || !data)
		return -1;

	fp = fopen(file_path, "rb");
	if (!fp)
		return -1;

	if (fstat(fileno(fp), &stat_buf) < 0)  {
		fclose(fp);
		return -1;
	}

	if (stat_buf.st_size < size) {
		fclose(fp);
		return -1;
	}

	memset(data, 0, size);

	if (fread(data, 1, size, fp) != size) {
		fclose(fp);
		return -1;
	}

	fclose(fp);

	return 0;
}

int write_file(const char *file_path, u8 *data, u64 size) {
	FILE *fp;

	if (!file_path || !data)
		return -1;

	fp = fopen(file_path, "wb");
	if (!fp)
		return -1;

	if (fwrite(data, 1, size, fp) != size) {
		fclose(fp);
		return -1;
	}

	fclose(fp);

	return 0;
}

const char* str_c(const char* a, const char* b){
	size_t len1 = strlen(a);
	size_t len2 = strlen(b);
	char *s = new char[len1 + len2 + 1];
	memcpy(s, a, len1);
	memcpy(s + len1, b, len2);
	s[len1 + len2] = '\0';
	return (const char*)s;
}
