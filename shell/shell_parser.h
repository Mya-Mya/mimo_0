#pragma once
#include"../tool/array/udlist.h"
#define SHELL_WORD_MAX_LENGTH 16
/*
One command has a command_t.
A command_t has a command_name and option_list header.
Each option_list element has an option_block_t.
An option_block_t has a tag and a option_values_list head.
Each option_values_list element has an option value.
*/
typedef udlist option_list;
struct command_t
{
	char *command_name;
	option_list *options_head;
};
typedef udlist option_values_list;
struct option_block_t{
	char *tag;
	option_values_list *values_head = NULL;
};

command_t shell_parse(char*command);