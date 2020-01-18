#include "shell_parser.h"
#include"../memory/memory_manager.h"

void copy_memory(char*from, char*to, int length) {
	for (; length > 0; length--) {
		*to = *from;
		to++;
		from++;
	}
}

char* pickup_word(char*sentence, int word_index) {
	int is_before_space = TRUE;
	char*target_start = sentence;
	char*target_end = sentence;
	//Loop to find first char of the target word.
	while (TRUE) {
		char now_char = (char)*sentence;
		if (now_char == ' ') {
			is_before_space = TRUE;
		}
		else if (now_char == 0) {
			return NULL;
		}
		else {
			if (is_before_space) {
				is_before_space = FALSE;
				if (word_index == 0) {
					target_start = sentence;

					sentence++;
					//Loop to find final char of the target word.
					while (TRUE) {
						char now_char = (char)*sentence;
						if (now_char == ' ') {
							if (!is_before_space) {
								target_end = sentence - 1;

								//Pick up the word
								char res[SHELL_WORD_MAX_LENGTH] = { 0 };
								copy_memory(target_start, res, (int)(target_end - target_start+1));
								return res;
							}
							is_before_space = TRUE;
						}
						else {
							is_before_space = FALSE;
						}
						sentence++;
					}//while (TRUE)

					break;
				}//if (word_index == 0)
				word_index--;
			}
		}
		sentence++;
	}
}


command_t shell_parse(char * command)
{
	command_t res;
	int word_index = 0;
	char*word = NULL;
	//Search for command name
	word=pickup_word(command, word_index);
	res.command_name = word;

	word_index++;
	word = pickup_word(command, word_index);

	//First option list is used for option block which doesn't have tag
	option_list *option_list_element = (option_list*)memory_allocate(sizeof(option_list));
	
	option_block_t *option_block = (option_block_t*)memory_allocate(sizeof(option_block_t));
	option_block->tag = NULL;
	option_list_element->value = option_block;

	while (((char)*word) != '-') {
		option_values_list*option_value = (option_values_list*)memory_allocate(sizeof(option_values_list));
		option_value->value = word;
		
		if (!option_block->values_head) {
			option_block->values_head = option_value;
		}
		else {
			udlist_add(option_block->values_head, option_value);
		}

		word_index++;
		word = pickup_word(command, word_index);
	}
	res.options_head = option_list_element;

	while (word != NULL) {
		option_list *option_list_element = (option_list*)memory_allocate(sizeof(option_list));

		//word is tag
		option_block_t*option_block = (option_block_t*)memory_allocate(sizeof(option_block_t));
		option_list_element->value = option_block;

		option_block->tag = word;
		
		//words are value
		word_index++;
		word = pickup_word(command, word_index);
		while (word!=NULL && ((char)*word) != '-') {
			option_values_list*option_value = (option_values_list*)memory_allocate(sizeof(option_values_list));
			option_value->value = word;

			if (!option_block->values_head) {
				option_block->values_head = option_value;
			}
			else {
				udlist_add(option_block->values_head, option_value);
			}

			word_index++;
			word = pickup_word(command, word_index);
		}

		udlist_add(res.options_head, option_list_element);
	}

	return res;
}
