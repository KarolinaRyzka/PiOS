#include <stdio.h>
#include "fat.h"
#include "sd.h"
#include <string.h>

char bootSector[512]; //boot sector
char fat_table[8192]; //FAT table
struct boot_sector *bs;
unsigned int root_sector;

void extract_filename(struct root_directory_entry *rde, char *output) { //get filename to compare
	int i = 0, j = 0;

	for (i=0; i < 8 && rde->file_name[i] != ' '; i++){
		output[i] = rde->file_name[i];
	}
	if (rde->file_extension[0] != ' '){ //dot for extension
		output[i++] = '.';
	}
	for (j = 0; j < 3 && rde->file_extension[j] != ' '; j++) {
		output[i++] = rde->file_extension[j];
	}

	output[i] = '\0';
}



int fatInit() {
	//read from SD card
	if (sd_readblock(0, bootSector, 1) == 0) {
		return -1;
	}
	//point structure to array
	bs = (struct boot_sector *)bootSector;
	//validate boot signature at end of sector
	if (bs->boot_signature != 0xAA55) {
		return -1;
	}
	//validate FAT filesystem type
	int match = 1;
	const char *fs_type = "FAT12";
	for (int i = 0; i < 5; i++) {
		if (bs->fs_type[i] != fs_type[i]) {
			match = 0;
			break;
		}
	}
	if (!match) {
		return -1;
	}
	//root directory sector
	root_sector = bs->num_reserved_sectors + (bs->num_fat_tables * bs->num_sectors_per_fat);
	//read FAT table into mem
	if (sd_readblock(bs->num_reserved_sectors, fat_table, bs->num_sectors_per_fat) == 0) {
		return -1;
	}

	return 0; //else success
}

int fatOpen(const char *filename) {
	struct root_directory_entry rde;
	char upper_filename[12]; //stores uppercase filename
	
	for(int i = 0; i < bs->num_root_dir_entries; i++) { //iterate over root dir
		if (sd_readblock(root_sector + i / (512 / sizeof(rde)), (char *)&rde, 1) == 0) {
			return -1;
		}
		extract_filename(&rde, upper_filename);

		int match = 1;
		for(int j = 0; upper_filename[j] != '\0' || filename[j] != '\0'; j++) {
			if (upper_filename[j] != filename[j]) {
				match = 0;
				break;
			}
		}
		if (match) {
			return rde.cluster; //return starting cluster if file found
			}
	}
	return -1;
}


int fatRead(int start_cluster, char *buffer, int size){
	int cluster = start_cluster;
	int bytes_read = 0;
	int cluster_size = bs->bytes_per_sector * bs->num_sectors_per_cluster;

	while (cluster != 0xFFF && bytes_read < size) { //end of file for FAT 12
		if (sd_readblock(root_sector + cluster - 2, buffer + bytes_read, bs->num_sectors_per_cluster) == 0) { //cluster into the buffer
			return -1;
		}
		bytes_read += cluster_size;
		cluster = fat_table[cluster];
	}
	return bytes_read;
}






