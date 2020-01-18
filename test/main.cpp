#include<iostream>
#include<time.h>

#include"list_structure.h"
#include"../memory/memory_manager.h"
int main() {
	//memory test
	time_t now;
	time(&now);
	srand(now);

	undir_list_t*head = NULL;
	undir_list_t*tail = NULL;

	memory_show_informations();
	while (true) {



		std::cout << "> ";
		char command = ' ';
		std::cin >> command;

		switch (command)
		{
		case'a'://Add new element.
			
			int random_value = 1 + rand() % 100;
			if (head == NULL) {
				head = (undir_list_t*)malloc(sizeof(undir_list_t));
				head->value = (int*)random_value;
				head->next = NULL;
				tail = head;
			}
			else {
				undir_list_t *new_elem = (undir_list_t*)malloc(sizeof(undir_list_t));
				new_elem->value = (int*)random_value;
				new_elem->next = NULL;
				tail->next = new_elem;
				tail = new_elem;
			}
			break;
		case'd'://Delete element.
			
			std::cout << "Select to delete." << std::endl;
			int index=0;
			std::cin >> index;
			if (index == 0) {
				undir_list_t*new_head = head->next;
				memory_free(head);
				head = new_head;
			}
			else {
				undir_list_t *one_before_target = head;
				for (int i = 0; i < index-1; i++) {
					if (one_before_target == NULL)break;
					one_before_target = one_before_target->next;
				}
				if(one_before_target==NULL||one_before_target->next==NULL){
					std::cout << "Such element doesn't exist." << std::endl;
					break;
				}
				undir_list_t *target = one_before_target->next;
				undir_list_t *one_after_target = target->next;
				one_before_target->next = one_after_target;
				memory_free(target);
			}
			break;
		case'm'://show memory informations
			memory_show_allocation_map();
			memory_show_usage_overview();
			break;
		case'e':
			exit(0);
			break;
		default:
			break;
		}
	}
}