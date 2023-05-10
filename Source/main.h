#ifndef HEADER_H
#define HEADER_H

#include <json-c/json.h>
#include <stddef.h>

int student_inf_managerment();
int add_student(char *name, size_t age, char *phone, char *parent_phone, char *class_time);
int add_class(char *name, size_t start_time, size_t end_time, char *subject);

#endif