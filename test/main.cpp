#include<iostream>
#include<time.h>

#include"../shell/shell_parser.h"
int main() {
	shell_parse(" repeat  ha ya -t 20 10 -f -q -c zzz");
}

#include"../tool/array/udlist.h"
#include"../memory/memory_manager.h"
void memory_test() {
	time_t now;
	time(&now);
	srand(now);

	udlist*head = NULL;

	memory_show_informations();
	while (true) {
		//Show elements.
		int index = 0;
		for (udlist*itr = head; itr != NULL; itr = itr->next) {
			int* value = (int*)itr->value;
			std::cout << index << "|" << *value<<" ";
			index++;
		}
		std::cout << std::endl;

		std::cout << "> ";
		char command = ' ';
		std::cin >> command;

		switch (command)
		{
		case'a'://Add new element.
		{
			int *random_value = (int*)memory_allocate(sizeof(int));
			if (!random_value)abort();
			*random_value = (1 + rand() % 100);
			if (head == NULL) {
				head = (udlist*)memory_allocate(sizeof(udlist));
				head->value = random_value;
			}
			else {
				udlist *new_elem = (udlist*)memory_allocate(sizeof(udlist));
				new_elem->value = random_value;
				udlist_add(head, new_elem);
			}
		}
			break;
		case'd'://Delete element.
		{
			if (!head) {
				std::cout << "No elements exist.";
				break;
			}
			std::cout << "Select to delete." << std::endl;
			int index = 0;
			std::cin >> index;
			if (index == 0) {
				udlist*new_head = head->next;
				memory_free(head->value);
				memory_free(head);
				head = new_head;
			}
			else {
				udlist*target=udlist_delete_at(head, index);
				if (!target) {
					std::cout << "Such element not found." << std::endl;
					break;
				}
				memory_free(target->value);
				memory_free(target);
			}
		}
			break;
		case'm'://Show memory informations
			memory_show_allocation_map();
			memory_show_usage_overview();
			break;
		case'e':
			exit(0);
			break;
		}
	}
}