#include "value.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "chunk.h"
#include "memory.h"

void value_array_init(ValueArray *array) {
    array->count = 0;
    array->capacity = 0;
    array->values = NULL;
}

void value_array_write(ValueArray *array, Value value) {
	if (array->capacity < array->count + 1) {
		int old_cap = array->capacity;
		array->capacity = GROW_CAPACITY(old_cap);
		array->values = GROW_ARRAY(Value, array->values, old_cap, array->capacity);
	}
	array->values[array->count] = value;
	array->count++;
}

void value_array_free(ValueArray *array) {
	FREE_ARRAY(Value, array->values, array->capacity);
	value_array_init(array);
}

void print_value(Value value) {
    printf("%g", value);
}
