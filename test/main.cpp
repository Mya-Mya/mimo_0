#include<iostream>
#include<time.h>

#include"../memory/memory_manager.h"
int main() {
	//mallocƒeƒXƒg
	time_t now;
	time(&now);
	srand(now);

	while (true) {
		unsigned int size = rand() % 50 + 1;
		void*address=memory_allocate(size);
		if (address == NULL)break;
		std::cout <<"+ "<<size<<" byte"<<std::endl;
		memory_show_allocation_map();
	}
}