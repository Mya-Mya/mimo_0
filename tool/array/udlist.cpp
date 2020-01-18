#include "udlist.h"

int udlist_add(udlist * head, udlist * new_element)
{
	if (!head)return FAILURE;
	udlist*itr=NULL;
	while (TRUE) {
		itr = head->next;
		if (!itr) break;
		head = itr;
	}
	head->next = new_element;
	return TRUE;
}

int udlist_add_to(udlist * head, udlist * new_element, int index)
{
	if (!head)return FAILURE;
	for (; index > 0; index--) {
		head = head->next;
		if (!head)return FAILURE;
	}
	head->next = new_element;
	return TRUE;
}

int get_index(udlist * head, udlist * element)
{
	if (!head)return FAILURE;
	int index = 0;
	for (; head != element;head=head->next) {
		if (!head)return FAILURE;
		index++;
	}
	return index;
}

udlist * udlist_get_at(udlist * head, int index)
{
	if (!head)return NULL;
	for (; index >0; index--) {
		head = head->next;
		if (!head)break;
	}
	return head;
}

int udlist_delete(udlist * head, udlist * element)
{
	if (!head||!element)return FAILURE;

	udlist*one_before_target=head;
	for (; head != element; head = head->next) {
		if (!head)return FAILURE;
		one_before_target = head;
	}

	udlist*one_after_target = element->next;
	one_before_target->next = one_after_target;
	return TRUE;
}

udlist* udlist_delete_at(udlist * head, int index)
{
	if (index <= 0)return NULL;
	index--;
	udlist*one_before_target = head;
	for (; index > 0; index--) {
		one_before_target = one_before_target->next;
		if (!one_before_target)return NULL;
	}
	udlist*target = one_before_target->next;
	if (!target)return NULL;
	one_before_target->next = target->next;
	return target;
}
