#ifndef HEADER_H
#define HEADER_H

#include <json-c/json.h>
#include <stddef.h>

json_object *add_student(char *name, size_t age, char *phone, char *parent_phone, char *class_time);

#endif