#include <stdio.h>

int main() {
    int count_student = 0;
    int count_subject = 0;
    scanf("%d", &count_student);
    scanf("%d", &count_subject);
    int data[count_student][count_subject]; //data of the students' scores

    for (int i = 0; i < count_student; i++) {
        for (int j = 0; j < count_subject; j++) {
            scanf("%d", &data[i][j]);
        }
    }

    // Step 1 avg of every stuents
    for (int i = 0; i < count_student; i++) {
        float sum_score = 0;
        for (int j = 0; j < count_subject; j++) {
            sum_score += data[i][j];
        }
        double avg_student = sum_score/count_subject;
        printf("%.6f\n", avg_student);
    }

    // Step 2 avg of every subjects
    for (int i = 0; i < count_subject; i++) {
        float sum_subject = 0;
        for (int j = 0; j < count_student; j++) {
            sum_subject += data[j][i];
        }
        double avg_subject = sum_subject / count_student;
        printf("%.6f ", avg_subject);
    }
}