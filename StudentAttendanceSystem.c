#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100

struct Student {
    char name[MAX_NAME];
    int present;
};

void markAttendance();
void viewAttendance();
void updateAttendance();
void displayMenu();

int main() {
    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1: markAttendance(); break;
            case 2: viewAttendance(); break;
            case 3: updateAttendance(); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice, try again.\n");
        }
    } while (choice != 4);
    return 0;
}

void displayMenu() {
    printf("\nStudent Attendance System\n");
    printf("1. Mark Attendance\n");
    printf("2. View Attendance\n");
    printf("3. Update Attendance\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

void markAttendance() {
    struct Student student;
    FILE *file = fopen("attendance.dat", "ab");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter student name: ");
    fgets(student.name, MAX_NAME, stdin);
    student.name[strcspn(student.name, "\n")] = 0;
    student.present = 1;
    fwrite(&student, sizeof(struct Student), 1, file);
    fclose(file);
    printf("Attendance marked successfully!\n");
}

void viewAttendance() {
    struct Student student;
    FILE *file = fopen("attendance.dat", "rb");
    if (!file) {
        printf("No attendance records found!\n");
        return;
    }
    printf("\nAttendance Records:\n");
    while (fread(&student, sizeof(struct Student), 1, file)) {
        printf("Student: %s - %s\n", student.name, student.present ? "Present" : "Absent");
    }
    fclose(file);
}

void updateAttendance() {
    char searchName[MAX_NAME];
    struct Student student;
    int found = 0;
    FILE *file = fopen("attendance.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (!file || !temp) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter student name to update attendance: ");
    fgets(searchName, MAX_NAME, stdin);
    searchName[strcspn(searchName, "\n")] = 0;
    while (fread(&student, sizeof(struct Student), 1, file)) {
        if (strcmp(student.name, searchName) == 0) {
            printf("Mark student as present (1) or absent (0): ");
            scanf("%d", &student.present);
            found = 1;
        }
        fwrite(&student, sizeof(struct Student), 1, temp);
    }
    fclose(file);
    fclose(temp);
    remove("attendance.dat");
    rename("temp.dat", "attendance.dat");
    if (found)
        printf("Attendance updated successfully!\n");
    else
        printf("Student not found!\n");
}
