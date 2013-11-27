#include <iostream>
#include "ps4.h"

#include <Windows.h> //console title

/*
	Commands
	=================================
	CMD			ARG 0			ARG1
	--help
	--about
	--info		"filepath"
	--unpack	"filepath"		directory

*/

void error_msg(int code);

int main(int argc, char* args[]){
	SetConsoleTitle(TEXT("PS4 PUP Tool"));

	if(argc < 2)
		error_msg(2);

	if(memcmp(args[1], "--", 2) != 0)
		error_msg(1);

	int CMD = -1;

	if(memcmp(&(args[1])[2], "about", 5) == 0) CMD = 0;
	if(memcmp(&(args[1])[2], "help", 4) == 0) CMD = 1;
	if(memcmp(&(args[1])[2], "info", 4) == 0) CMD = 2;
	if(memcmp(&(args[1])[2], "unpack", 6) == 0) CMD = 3;
	if(CMD > 1 && CMD < 4){
		u64 fileSize;
		if(get_file_size(args[2], &fileSize) < 0)
			error_msg(3);
		u8* fileData = new u8[fileSize];
		if(read_file(args[2], fileData, fileSize) < 0)
			error_msg(3);

		SLB ps4pup = SLB(fileData);

		if(CMD == 2){
			printf("Magic: %d\n", ps4pup.header.magic);
			printf("Version: %d\n", ps4pup.header.version);
			printf("File Count: %d\n", ps4pup.header.fileCount);
			printf("Block Count: %d\n", ps4pup.header.blockCount);
			printf("=====================================\n");
			for(int i=0; i<ps4pup.header.fileCount; i++){
				printf("File Info #%d\n", i);
				printf("\tOffset: %X\n", ps4pup.header.files[i].offset * SLB_BLOCK_SIZE);
				printf("\tEncrypted Size: %X\n", ps4pup.header.files[i].cryptSize);
				printf("\tFile Name: %s\n", ps4pup.header.files[i].fileName);

			}

		}

		if(CMD == 3){
			if(!args[3])
				error_msg(4);
			ps4pup.unpack(args[3]);
		}
	}
	else if(CMD == 0)
		printf("PS4 PUP Tool v0.0.1\nCopywright (c) Jakes625 2013");
	else if(CMD == 1){
		printf("CMD\t\tARG 1\t\tARG 2\n");
		printf("=================================================\n");
		printf("--help\n");
		printf("--about\n");
		printf("--info\t\t\"file path\"\n");
		printf("--unpack\t\"file path\"\toutput folder");
	}
	else
		error_msg(2);

	return 0;
}

void error_msg(int code){
	switch(code){
		case 1: printf("Invalid CMD Format."); break;
		case 2: printf("Unknown Command."); break;
		case 3: printf("Unable to read file."); break;
		case 4: printf("No Output Folder."); break;
		default: printf("Unknown Error."); break;
	}
	exit(code);
}
