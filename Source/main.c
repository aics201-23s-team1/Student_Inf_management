#include <stdio.h>
#include <string.h>
#include <json-c/json.h>
#include <stddef.h>
#include <assert.h>

#define STUDENT_FILE "json/student.json"
#define CLASS_FILE "json/class.json"

int student_inf_managerment() {
	FILE *fp = fopen(STUDENT_FILE, "wt");
	FILE *fp2 = fopen(CLASS_FILE, "wt");

	if(fp == NULL || fp2 == NULL) {
		return -1;
	}
	
	fprintf(fp, "[]");
	fprintf(fp2, "[]");
	fclose(fp);
	fclose(fp2);

	return 0;
}

int time_check(char *time) {
	unsigned int year, month, day, hour, minute;
	int ok = 0;

	ok = sscanf(time, "%d-%d-%d-%d:%d", &year, &month, &day, &hour, &minute);
	assert(ok == 5);
	if(month < 13 && day < 32 && hour < 25 && minute < 61) {
		return 0;
	}
	return -1;
}

int add_student(char *name, size_t age, char *phone, char *parent_phone, char *class_time){
	json_object *phone_num, *rootValue, *student;

	phone_num = json_object_new_object();
	rootValue = json_object_from_file(STUDENT_FILE);
	if (!rootValue) {
		printf("Failed to parse JSON data.\n");
		return -1;
	}

	student = json_object_new_object();
	json_object_object_add(student, "name", json_object_new_string(name));
	json_object_object_add(student, "age", json_object_new_int(age));

	json_object_object_add(phone_num, "own", json_object_new_string(phone));
	json_object_object_add(phone_num, "p", json_object_new_string(parent_phone));
	json_object_object_add(student, "phone number", phone_num);

	json_object_object_add(student, "class_time", json_object_new_string(class_time));

	json_object_array_add(rootValue, student);
    
	json_object_to_file(STUDENT_FILE, rootValue);

	return 1;
}

int del_student(const char *name){
	json_object *rootValue, *del_student_name;

	rootValue = json_object_from_file(STUDENT_FILE);
	if (!rootValue){
		printf("Failed to parse JSON data. \n");
		return -1;
	}

	del_student_name = NULL;
	json_object_object_foreach(rootValue, key, val){
		if(json_object_equal(val, json_object_new_string(name))){
			del_student_name = rootValue;
			break;
		}
	}

	if(del_student_name == NULL){
		printf("No student with the name entered. \n");
		return -1;
	}

	json_object_put(del_student_name);

	json_object_to_file(STUDENT_FILE, rootValue);


	return 1;
}

int add_class(char *name, char *start_time, char *end_time, char *subject) {
	json_object *class, *rootValue;
	unsigned int year, month, day, hour, minute;
	int ok = 0;

	rootValue = json_object_from_file(CLASS_FILE);

	assert(rootValue);
	
	class = json_object_new_object();
	json_object_object_add(class, "name", json_object_new_string(name));
	
	ok = time_check(start_time);
	assert(ok != -1);
	json_object_object_add(class, "start_time", json_object_new_string(name));

	ok = time_check(end_time);
	assert(ok != -1);
	json_object_object_add(class, "end_time", json_object_new_string(name));

	json_object_object_add(class, "subject", json_object_new_string(subject));

	json_object_array_add(rootValue, class);
    
	json_object_to_file(CLASS_FILE, rootValue);

	return 1;
}


int main(int argc, char *argv[]){
	//사용할 기능의 번호 입력, 입력한 값에 따른 함수 사용
	int choice;
	while(1) {
		printf("1. 학생 정보 추가 \n");
		printf("2. 학생 정보 제거 \n");
		printf("3. 학생 정보 수정 \n");
		printf("4. 나가기 \n");
		printf("원하는 기능의 번호 입력: ");
		scanf("%d", &choice);
		switch (choice) {
			case 0:
				student_inf_managerment();
				break;
			case 1:
				add_student("test", 21, "010-1234-1234", "010-4321-4321", "asdf : 12:30");
				add_student("test", 22, "010-1234-1234", "010-4321-4321", "asdf : 12:30");
				add_student("test", 23, "010-1234-1234", "010-4321-4321", "asdf : 12:30");
				add_student("test", 24, "010-1234-1234", "010-4321-4321", "asdf : 12:30");
				add_student("test", 25, "010-1234-1234", "010-4321-4321", "asdf : 12:30");
				break;
			case 2:
				add_class("test", "2022-12-31-11:22", "2022-12-31-11:22", "asdf");
				break;
			case 3:
				del_student("test");
				break;
			case 4:
				break;
			default:
				printf("Error: 다시 입력하십시오. \n");
				return 0;
		}
	}
	return 0;
}