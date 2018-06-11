/** @file
 *  \brief implementation of the lists
 *
 */
#include "zimonzk/lists.h"

void arraylist_init(arraylist* list, uint16_t unit_size, uint16_t allocation_block_units)
{
    list->data = calloc(unit_size, allocation_block_units);
    list->used_units = 0;
    list->allocated_units = allocation_block_units;
    list->allocation_block_units = allocation_block_units;
    list->unit_size = unit_size;
}

void arraylist_delete(arraylist* list)
{
    free(list->data);
    list->used_units = 0;
    list->allocated_units = 0;
    list->allocation_block_units = 0;
    list->unit_size = 0;
}

static inline void copydata(uint16_t unit_size, void* dest, void* source)
{
    for(uint16_t i = 0; i < unit_size; i++) {
        *(((char*)dest)+i) = *(((char*)source)+i);
    }
}

static inline void shiftdata(uint64_t shiftwitdh)
{
    /*TODO shift elements efficiently*/
    /*for(uint64_t i = 0; i*/
}

void arraylist_append(arraylist* list, void* element_ptr)
{
    list->used_units++;
    if(list->used_units > list->allocated_units) {
        list->allocated_units += list->allocation_block_units;
        list->data = realloc(list->data, list->allocated_units * list->unit_size);
        if(list->data == 0) {
            exit(1);
        }
    }
    copydata(list->unit_size, (list->data + ((list->used_units - 1) * list->unit_size)), element_ptr);
}

void arraylist_instert(arraylist* list, void* element_ptr, uint64_t index)
{
    /*TODO shift the old entries up*/
    copydata(list->unit_size, (list->data + (index * list->unit_size)), element_ptr);
}

void arraylist_del_element(arraylist* list, uint64_t index)
{
    if(index != (list->used_units - 1)) {
        copydata(list->unit_size * (list->used_units - index), (list->data + (index * list->unit_size)), (list->data + (index * list->unit_size)) + 1);
    }
    list->used_units--;
    if(list->used_units <= (list->allocated_units - list->allocation_block_units)) {
        list->allocated_units -= list->allocation_block_units;
        list->data = realloc(list->data, list->allocated_units * list->unit_size);
    }
}

void arraylist_replace(arraylist* list, void* element_ptr, uint64_t index)
{
    copydata(list->unit_size, (list->data + (index * list->unit_size)), element_ptr);
}

void* arraylist_get(arraylist* list, uint64_t index)
{
    return (void*)(((char*)list->data) + (index * list->unit_size));
}

void arraylist_append_multi(arraylist* list, void* element0_ptr, uint64_t index, uint64_t ammount)
{
    list->used_units += ammount;
    if(list->used_units > list->allocated_units) {
        if((list->used_units % list->allocation_block_units) != 0) {
            list->allocated_units = (list->used_units / list->allocation_block_units) + 1;
				} else {
            list->allocated_units = (list->used_units / list->allocation_block_units);
				}
        list->data = realloc(list->data, list->allocated_units * list->unit_size);
        if(list->data == 0) {
            exit(1);
        }
    }
    copydata(list->unit_size * ammount, (list->data + (index * list->unit_size)), element0_ptr);
}

void arraylist_insert_multi(arraylist* list, void* element0_ptr, uint64_t index, uint64_t ammount)
{
    copydata(list->unit_size * ammount, (list->data + (index * list->unit_size)), element0_ptr);
}

void arraylist_replace_multi(arraylist* list, void* element0_ptr, uint64_t index, uint64_t ammount)
{
    /*TODO shift the old entries up*/	
    copydata(list->unit_size * ammount, (list->data + (index * list->unit_size)), element0_ptr);
}
