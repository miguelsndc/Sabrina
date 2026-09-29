#ifndef sabrina_value_h
#define sabrina_value_h

typedef double Value;

typedef struct {
  int capacity;
  int count;
  Value *values;
} ValueArray;

void value_array_init(ValueArray *array);
void value_array_write(ValueArray *array, Value value);
void value_array_free(ValueArray *array);
void print_value(Value value);

#endif
