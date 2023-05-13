#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <json-c/json.h>

#define MAX_SUBJECTS 10

typedef struct {
    char start_time[10];
    char end_time[10];
} Subject;

typedef struct {
    char name[20];
    char phone[20];
    int age;
    Subject subjects[MAX_SUBJECTS];
    int attendance[MAX_SUBJECTS][31];
} Student;

int saved_attendance(Student* student, int subject_index, int day) {
    if (subject_index < 0 || subject_index >= MAX_SUBJECTS) {
        fprintf(stderr, "Invalid subject index.\n");
        return -1;
    }
    if (day < 1 || day > 31) {
        fprintf(stderr, "Invalid day.\n");
        return -1;
    }

    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    char current_time[10];
    strftime(current_time, sizeof(current_time), "%H:%M:%S", tm);

    char* start_time = student->subjects[subject_index].start_time;
    char* end_time = student->subjects[subject_index].end_time;

    if (strcmp(current_time, start_time) < 0 || strcmp(current_time, end_time) > 0) {
        // 현재 시간이 수업 시간이 아님
        return 0;
    } else {
        // 출석 처리
        student->attendance[subject_index][day - 1] = 1;
        return 1;
    }
}

int check_attendacne(const char* phone_number) {
    FILE *fp = fopen("student.json", "r");
    char buffer[1024];
    fread(buffer, 1024, 1, fp);
    fclose(fp);

    // JSON 객체를 생성
    json_object *json_obj = json_tokener_parse(buffer);

    const char *search_value = &phone_number;
    const char *search_key = "phone";

    json_object *search_obj = json_object_object_get(json_obj, search_key);

    json_object *searched_objs[100];
    int searched_objs_count = 0;

    // JSON 객체 검색
    int i;
    for (i = 0; i < json_object_array_length(json_obj); i++) {
        json_object *obj = json_object_array_get_idx(json_obj, i);

        // 검색된 값과 일치하는 경우, 해당 객체를 배열에 추가
        if (json_object_get_string(search_obj) == search_value) {
            searched_objs[searched_objs_count++] = obj;
        }
    }

    // 검색된 객체들 중에서 정보 추출
    for (i = 0; i < searched_objs_count; i++) {
        json_object *obj = searched_objs[i];

        // 정보를 추출하는 코드
        json_object *name_obj = json_object_object_get(obj, "name");
        json_object *age_obj = json_object_object_get(obj, "age");
        const char *name = json_object_get_string(name_obj);
        int age = json_object_get_int(age_obj);
        printf("Name: %s, Age: %d\n", name, age);
    }

    // JSON 객체 해제
    json_object_put(json_obj);

    return 0;
}

