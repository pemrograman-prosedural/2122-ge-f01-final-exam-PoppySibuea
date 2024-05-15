// 12S23004 - Poppy Sibuea
// 12S23020 - Rachel C.P. Simorangkir

#include <stdio.h>
#include "./libs/dorm.h"
#include "./libs/student.h"
#include <string.h>
#include <stdlib.h>

int main(int _argc, char **_argv)
{
    Dorm* LEFT = (Dorm*) malloc(sizeof(Dorm));
    strcpy(LEFT->name, "left");
    LEFT->capacity = 10;
    LEFT->gender = GENDER_FEMALE;
    LEFT->residents_num = 0;
    Dorm *dorm = (Dorm*) malloc(1 *sizeof(Dorm));
    Student *students = (Student*) malloc(1 * sizeof(Student));
    unsigned short totalDorm;
    unsigned short totalStudent;
    char line[255];
    char delim[2] = "#";

    while(1) {
        line[0] = '\0';
        fgets(line, 255, stdin);
        fflush(stdin);

        { 
            int len = strlen(line);
            for (short a = 0; a < len; a++) {
                if(line[a] == '\r' || line[a] == '\n'){
                    for(short b = a; b < len; b++) { line[b] = line[b+1]; }
                    len--;
                    a--;

                }
            }
        }
        
        if (strcmp(line, "---") == 0 ) break;

        else if( strcmp(line, "student-print-all") == 0 ){
            for (short i=0; i<totalStudent; i++) {
                printStudent(students[i]);
            }
        }
        
        else if( strcmp(line, "dorm-print-all") == 0 ){
            for (short i=0; i<totalDorm; i++) {
                print_dorm(dorm[i]);
            }
        }
        
        else if( strcmp(line, "student-print-all-detail") == 0 ){
            for (short i=0; i<totalStudent; i++) {
                printStudentDetails(students[i]);
            }
        }

        else if( strcmp(line, "dorm-print-all-detail") == 0 ){
            for (short i=0; i<totalDorm; i++) {
                printDormDetails(dorm[i]);
            }
        }

        else {
            char *token = strtok(line, delim);

            if ( strcmp(token, "student-add") == 0 ) {
                token = strtok(NULL, delim) ; char *_id = token;
                token = strtok(NULL, delim) ; char *_name = token;
                token = strtok(NULL, delim) ; char *_year = token;

                token = strtok(NULL, delim);
                if ( totalStudent > 0 ) {
                    students = (Student*) realloc(students, (totalStudent+1) * sizeof(Student));
                }
                if ( strcmp(token, "male") == 0 ) {
                    students[totalStudent] = create_student(_id, _name, _year, GENDER_MALE);
                }
                else if ( strcmp(token, "female") == 0 ) {
                    students[totalStudent] = create_student(_id, _name, _year, GENDER_FEMALE);
                    totalStudent++;
                }
            }

            else if ( strcmp(token, "dorm-add") == 0 ){
                token = strtok(NULL, delim); char *_name = token;
                token = strtok(NULL, delim); unsigned short _capacity = atoi(token);
                token = strtok(NULL, delim);
                if ( totalDorm > 0 ) {
                    dorm = (Dorm*) realloc(dorm, (totalDorm+1) * sizeof(Dorm));
                }
                if ( strcmp(token, "male") == 0 ) {
                    dorm[totalDorm] = create_dorm(_name, _capacity, GENDER_MALE);
                    totalDorm++;
                }
                else if ( strcmp(token, "female") == 0 ) {
                    dorm[totalDorm] = create_dorm(_name, _capacity, GENDER_FEMALE);
                    totalDorm++;
                }
            }

            else if ( strcmp(token, "move-student") == 0) {
                token = strtok(NULL, delim); char *_id = token;
                token = strtok(NULL, delim); char *dorm_name = token;

                short studentIdx = findStudentIdx(_id, students, totalStudent);
                short newDormIdx = findDormIdx(dorm_name, dorm, totalDorm);
                char *_name = students[studentIdx].dorm->name;
                if (_name != NULL){
                    short oldDormIdx = findDormIdx(_name, dorm, totalDorm);

                    if (studentIdx>=0 && newDormIdx>=0 && oldDormIdx>=0){
                        moveStudent(&students[studentIdx],&dorm[newDormIdx] , &dorm[oldDormIdx]);
                    }
                } else {
                    assign(&students[studentIdx], &dorm[newDormIdx]);
                }
            }

            else if (strcmp(token, "dorm-empty") == 0) {
                token - strtok(NULL, delim);
                char *dorm_name = token;
                short target = findDormIdx(dorm_name, dorm, totalDorm);

                for (short i=0; i<totalStudent; i++) {
                    if (students[i].dorm != NULL) {
                        if (strcmp(students[i].dorm->name, dorm_name) == 0) {
                            unassign(&students[i], &dorm[target]);

                        }
                    }
                }
            }

            else if (strcmp(token, "student-leave") == 0) {
                token = strtok(NULL, delim);
                short studentIdx = findStudentIdx(token, students, totalStudent);
                short dormIdx = findDormIdx(students->dorm->name, dorm, totalDorm);
                unassign(&students[studentIdx], &dorm[dormIdx]);
                students[studentIdx].dorm = LEFT;
            }
        }
    }

    free(dorm);
    free(students);
    free(LEFT);

    return 0;
}
