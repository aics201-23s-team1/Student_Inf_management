#include <stdio.h>
#include <json-c/json.h>
#include <stddef.h>

#define FILE_PATH "student.json"

typedef struct student{
	char name[5];
	int age;
	char phone[14];
	char parent_phone[14];
	char class_time[30];
}student_t;

json_object *add_student(char *name, size_t age, char *phone, char *parent_phone, char *class_time){
	json_object *phone_num, *rootValue;

	phone_num = json_object_new_object();
	rootValue = json_object_from_file(FILE_PATH);
    	if (!rootValue) {
        	printf("Failed to parse JSON data.\n");
        	return NULL;
    	}

	json_object *student = json_object_new_object();
	json_object_object_add(student, "name", json_object_new_string(name));
	json_object_object_add(student, "age", json_object_new_int(age));

	json_object_object_add(phone_num, "own", json_object_new_string(phone));
	json_object_object_add(phone_num, "p", json_object_new_string(parent_phone));
	json_object_object_add(student, "phone number", phone_num);

	json_object_object_add(student, "class_time", json_object_new_string(class_time));

	json_object_array_add(rootValue, student);
    
	json_object_to_file("student.json", rootValue);

	return rootValue;
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
			case 1:
				add_student("test", 21, "010-1234-1234", "010-4321-4321", "asdf : 12:30");
				add_student("test", 22, "010-1234-1234", "010-4321-4321", "asdf : 12:30");
				add_student("test", 23, "010-1234-1234", "010-4321-4321", "asdf : 12:30");
				add_student("test", 24, "010-1234-1234", "010-4321-4321", "asdf : 12:30");
				add_student("test", 25, "010-1234-1234", "010-4321-4321", "asdf : 12:30");
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
