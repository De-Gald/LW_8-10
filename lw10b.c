#include <stdio.h>
#include <pthread.h>

int number_of_groups = 5;
int number_of_students = 7;
int groups_performance[7][5] = {{3, 5, 5, 5, 3},
                                {4, 5, 5, 4, 3},
                                {5, 3, 5, 4, 3},
                                {4, 3, 5, 4, 3},
                                {5, 3, 5, 5, 4},
                                {5, 5, 5, 4, 3},
                                {4, 5, 5, 5, 3}};

void *average_grade(void *arg) {
    int * number = (int *) arg;
//    int group_number = (int) arg;
    int group_number = number;
    int count = 0;
    float grades_sum = 0;
    for (int i = 0; i < number_of_students; i++){
        grades_sum += groups_performance[i][group_number];
        count++;
    }
    float group_gpa = grades_sum / count;
    printf("The average grade of the group %d is %.2f\n", group_number, group_gpa);
    return NULL;
}

void *full_average(void *arg) {
    int count = 0;
    float grades_sum = 0;
    for (int i = 0; i < number_of_students; i++){
        for (int j = 0; j < number_of_groups; j++){
            grades_sum += groups_performance[i][j];
            count++;
        }
    }
    float full_gpa = grades_sum / count;
    printf("\nThe average grade of all groups is %.2f\n", full_gpa);
    return NULL;
}

int main() {
    for (int i = 0; i < number_of_groups; i++) {
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, average_grade, (void *) i);
        pthread_cancel(thread_id);
    }

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, full_average, NULL);
//    pthread_join(thread_id, NULL);
    pthread_cancel(thread_id);
    return 0;
}

