#include "ps4.h"
#include <iostream>

SLB::SLB(u8* buffer){
	this->header = *(SLB2 *)(buffer);

	if( this->header.magic != SLB_MAGIC){
		printf("Magic doesn't match PS4 SLB format: 'SLB2'\n");
		return;
	}

	if( this->header.version != SLB_VERS){
		printf("Version doesn't match PS4 SLB format: '1'\n");
		return;
	}

	for(int i=0; i<this->header.fileCount; i++)
		this->fileData[i] = &buffer[this->header.files[i].offset * SLB_BLOCK_SIZE];
}

void SLB::unpack(const char* folderPath){
	for(int i = 0; i < this->header.fileCount; i++){
		const char* fileName = (const char*)(this->header.files[i].fileName);
		printf("Writing file '%s'... ", fileName);
		write_file(str_c(folderPath, fileName), this->fileData[i], this->header.files[i].cryptSize);
		printf("Complete!\n");
	}
}
