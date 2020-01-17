#pragma once
void memory_init();
void* memory_allocate(unsigned int size);
void memory_free(void*ptr);
void memory_show_allocation_map();
void memory_show_usage_overview();