#include "Util.h"

#define SLB_MAGIC 0x32424C53 //SLB2 (littleEndian)
#define SLB_VERS 1
#define SLB_BLOCK_SIZE 512

class SLB{
private:
	u8* fileData[10];

	#pragma pack (push, 1)
	typedef struct{
		u32 offset;
		u32 cryptSize;
		u64 reserved;
		u8 fileName[32];
	} fileEntry;

	typedef struct{
		u32 magic;
		u64 version;
		u32 fileCount;
		u32 blockCount;
		u8 reserved[12];
		fileEntry files[10];
	} SLB2;
	#pragma pack (pop)

public:
	SLB2 header;
	SLB(u8* buffer);
	void unpack(const char* folderPath);
};
