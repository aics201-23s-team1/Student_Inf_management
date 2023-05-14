#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <json-c/json.h>

#define STUDENT_FILE "json/student.json"

int check_attendacne(const char* phone_number) {
    json_object *rootValue;

    rootValue = json_object_from_file(STUDENT_FILE);
	if (!rootValue){
		printf("Failed to parse JSON data. \n");
		return -1;
	}

    json_object *search_phone_number = NULL;

    json_object_object_foreach(rootValue, key, val){
		if(json_object_equal(val, json_object_new_string(phone_number))){
			search_phone_number = rootValue;
			break;
		}
	}
    
    // JSON에서 attendacne 정보 가져오기
    json_object *attendance_obj = json_object_object_get(search_phone_number, "attendance");

    if (attendance_obj == NULL) {
        printf("attendance information not found. \n");
        return -1;
    }

    int attendance = json_object_get_int(attendance_obj);

    if (attendance == -1) {
        //출석 저장
        json_object_object_add(search_phone_number, "attendance", json_object_new_int(1));

        if (json_object_to_file(STUDENT_FILE, rootValue) != 0) {
            printf("Failed to save JSON data. \n");
            return -1;
        }

        printf("attendance saved. \n");
    }

    else {
        printf("attendance: %d\n", attendance);
    }


    // JSON 객체 해제
    json_object_put(rootValue);

    return 0;
}

