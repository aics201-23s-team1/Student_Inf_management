#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    char name[20];
    char p_num[12];
    bool attendance;
} Student;

typedef struct {
    char name[20];
    char day[10];
    char start_time[10];
    char end_time[10];
} Class;

void chk_attend() {
    FILE* fp = fopen("students.json", "r");
    if (fp == NULL) {
        printf("students.json 파일을 열 수 없습니다.\n");
        return 1;
    }

    char buffer[1000];
    fgets(buffer, sizeof(buffer), fp);
    fclose(fp);

    Student students[100];
    int num_students = 0;

    char* token;
    const char* delimiter = "\"name\": \"";
    token = strtok(buffer, delimiter);
    while (token != NULL) {
        token = strtok(NULL, delimiter);
        if (token == NULL) {
            break;
        }
        strcpy(students[num_students].name, token);

        delimiter = "\", \"phone number\": {";
        token = strtok(NULL, delimiter);

        delimiter = "\"own\": \"";
        token = strtok(NULL, delimiter);
        strcpy(students[num_students].p_num, token);

        delimiter = "\", \"age\": ";
        token = strtok(NULL, delimiter);

        delimiter = "\"class\": \"";
        token = strtok(NULL, delimiter);

        delimiter = "\", \"name\": \"";
        num_students++;
    }

    fp = fopen("schedule.json", "r");
    if (fp == NULL) {
        printf("schedule.json 파일을 열 수 없습니다.\n");
        return 1;
    }

    Class classes[100];
    int num_classes = 0;

    fgets(buffer, sizeof(buffer), fp);
    fclose(fp);

    delimiter = "\"name\": \"";
    token = strtok(buffer, delimiter);
    while (token != NULL) {
        token = strtok(NULL, delimiter);
        if (token == NULL) {
            break;
        }
        strcpy(classes[num_classes].name, token);

        delimiter = "\", \"day\": \"";
        token = strtok(NULL, delimiter);
        strcpy(classes[num_classes].day, token);

        delimiter = "\", \"start time\": \"";
        token = strtok(NULL, delimiter);
        strcpy(classes[num_classes].start_time, token);

        delimiter = "\", \"end time\": \"";
        token = strtok(NULL, delimiter);
        strcpy(classes[num_classes].end_time, token);

        delimiter = "\", \"name\": \"";
        num_classes++;
    }

    return 0;
}

int main(){
    chk_attend();
}
