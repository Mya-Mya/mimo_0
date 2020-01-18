#include "memory_manager.h"
#include"../tool/math.h"
#include"../tool/flag.h"
#include<iostream>

const unsigned int block_size = 16;
const unsigned int num_block = 1024;
unsigned char user_runtime_space[block_size*num_block] = { 0 };
unsigned char allocation_map[num_block / 8] = { 0 };
unsigned char allocation_continue_map[num_block / 8] = { 0 };

unsigned int block_index_to_map_i(unsigned int block_index) {
	return block_index>>3;
}

unsigned int block_index_to_bit_i(unsigned int block_index) {
	return block_index % 8;
}

void memory_init()
{
}

void set_allocated(unsigned int block_index,unsigned int num_needed_block) {
	for (unsigned int k = 0; k < num_needed_block; k++) {
		unsigned int map_i = block_index_to_map_i(block_index+k);
		unsigned int bit_i = block_index_to_bit_i(block_index+k);
		allocation_map[map_i] |= (1 << bit_i);
	}

	if (num_needed_block > 1) {
		for (unsigned int k = 0; k < num_needed_block-1; k++) {
			unsigned int map_i = block_index_to_map_i(block_index+k);
			unsigned int bit_i = block_index_to_bit_i(block_index+k);
			allocation_continue_map[map_i] |= (1 << bit_i);
		}
	}
}

void set_free(unsigned int block_index) {
	for (; block_index < num_block; block_index++) {
		unsigned int map_i = block_index_to_map_i(block_index);
		unsigned int bit_i = block_index_to_bit_i(block_index);
		allocation_map[map_i] &= ~(1 << bit_i);
		if (!allocation_continue_map[map_i] & (1 << bit_i))break;//一連のアロケーション区間は終了した、
		allocation_continue_map[map_i] &= ~(1 << bit_i);
	}
	
}

void clear_block(unsigned int block_index) {
	//1つのBlock全体をcharを移動させながら0にする。
	for (unsigned char *cleaner = (unsigned char*)(user_runtime_space + block_size*block_index)
		; cleaner < user_runtime_space + block_size*(block_index + 1)
		; cleaner += 1) {
		*cleaner = 0;
	}
}

void* memory_allocate(unsigned int size) {
	unsigned int num_needed_block = CEIL_DIV(size,block_size);
	for (unsigned int block_index = 0; block_index < num_block; block_index++) {

		int allocatable_blocks_exist = TRUE;
		for (unsigned int k = 0; k < num_needed_block; k++) {
			unsigned int map_i = block_index_to_map_i(block_index+k);
			unsigned int bit_i = block_index_to_bit_i(block_index+k);
			if (allocation_map[map_i] & (1 << bit_i)) { 
				allocatable_blocks_exist = FALSE;
				break;
			}
		}

		if (allocatable_blocks_exist) {
			set_allocated(block_index,num_needed_block );
			void*res = user_runtime_space + block_size*block_index;
			return res;
		}

	}
	return NULL;
}

void memory_free(void * ptr)
{
	unsigned int block_index = ((int)ptr - (int)user_runtime_space) / block_size;
	set_free(block_index);
	clear_block(block_index);
	ptr = NULL;
}

void memory_show_allocation_map()
{
	for (unsigned int block_index = 0; block_index < num_block; block_index++) {
		unsigned int map_i = block_index_to_map_i(block_index);
		unsigned int bit_i = block_index_to_bit_i(block_index);
		if(allocation_map[map_i]&(1<<bit_i)){
			if (allocation_continue_map[map_i] & (1 << bit_i)) {
				std::cout << ">";
			}
			else {
				std::cout << "*";
			}
		}else{
			std::cout << "-";
		}
	}
	std::cout << std::endl;
}

void memory_show_usage_overview()
{
	std::cout << "Total block : " << num_block << " blocks" << std::endl;
	unsigned int num_allocated_block=0;
	unsigned int num_allocation_continued_block = 0;

	for (unsigned int block_index = 0; block_index < num_block; block_index++) {
		unsigned int map_i = block_index_to_map_i(block_index);
		unsigned int bit_i = block_index_to_bit_i(block_index);
		if (allocation_map[map_i] & (1 << bit_i))num_allocated_block++;
		if (allocation_continue_map[map_i] & (1 << bit_i))num_allocation_continued_block++;
	}
	std::cout << "Allocated block : " << num_allocated_block << " blocks" << std::endl;
	std::cout << "Allocation time : " << num_allocated_block - num_allocation_continued_block << " times" << std::endl;
	std::cout << "Free block : " << num_block - num_allocated_block << " blocks" << std::endl;
}

void memory_show_informations()
{
	std::cout << "Size : " << block_size << " byte/block" << std::endl;
	std::cout << "Total block : " << num_block << " blocks" << std::endl;
}
