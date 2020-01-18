#pragma once
#include"../flag.h"
/*
It provides Undirectional List structure and functions.
You need to keep head element as an instance of your array.
And you need to free element pointer after you deleted it.
*/

struct udlist
{
	void*value=NULL;
	udlist*next=NULL;
};

int udlist_add(udlist*head, udlist*new_element);
int udlist_add_to(udlist*head, udlist*new_element, int index);
int get_index(udlist*head,udlist*element);
udlist* udlist_get_at(udlist*head,int index);
int udlist_delete(udlist*head,udlist*element);
udlist* udlist_delete_at(udlist*head,int index);
