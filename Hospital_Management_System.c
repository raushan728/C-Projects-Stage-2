#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100
#define MAX_DISEASE 100

struct Patient {
    char name[MAX_NAME];
    int age;
    char disease[MAX_DISEASE];
};

void addPatient();
void viewPatients();
void updatePatient();
void deletePatient();
void displayMenu();

int main() {
    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: updatePatient(); break;
            case 4: deletePatient(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice, try again.\n");
        }
    } while (choice != 5);
    return 0;
}

void displayMenu() {
    printf("\nHospital Management System\n");
    printf("1. Add Patient Record\n");
    printf("2. View Records\n");
    printf("3. Update Record\n");
    printf("4. Delete Record\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

void addPatient() {
    struct Patient patient;
    FILE *file = fopen("patients.dat", "ab");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter patient name: ");
    fgets(patient.name, MAX_NAME, stdin);
    patient.name[strcspn(patient.name, "\n")] = 0;
    printf("Enter age: ");
    scanf("%d", &patient.age);
    getchar();
    printf("Enter disease: ");
    fgets(patient.disease, MAX_DISEASE, stdin);
    patient.disease[strcspn(patient.disease, "\n")] = 0;
    fwrite(&patient, sizeof(struct Patient), 1, file);
    fclose(file);
    printf("Patient record added successfully!\n");
}

void viewPatients() {
    struct Patient patient;
    FILE *file = fopen("patients.dat", "rb");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    printf("\nPatient Records:\n");
    while (fread(&patient, sizeof(struct Patient), 1, file)) {
        printf("Name: %s, Age: %d, Disease: %s\n", patient.name, patient.age, patient.disease);
    }
    fclose(file);
}

void updatePatient() {
    char name[MAX_NAME];
    struct Patient patient;
    int found = 0;
    FILE *file = fopen("patients.dat", "rb+"), *temp;
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter patient name to update: ");
    fgets(name, MAX_NAME, stdin);
    name[strcspn(name, "\n")] = 0;
    temp = fopen("temp.dat", "wb");
    while (fread(&patient, sizeof(struct Patient), 1, file)) {
        if (strcmp(patient.name, name) == 0) {
            printf("Enter new age: ");
            scanf("%d", &patient.age);
            getchar();
            printf("Enter new disease: ");
            fgets(patient.disease, MAX_DISEASE, stdin);
            patient.disease[strcspn(patient.disease, "\n")] = 0;
            found = 1;
        }
        fwrite(&patient, sizeof(struct Patient), 1, temp);
    }
    fclose(file);
    fclose(temp);
    remove("patients.dat");
    rename("temp.dat", "patients.dat");
    if (found)
        printf("Patient record updated successfully!\n");
    else
        printf("Patient not found!\n");
}

void deletePatient() {
    char name[MAX_NAME];
    struct Patient patient;
    int found = 0;
    FILE *file = fopen("patients.dat", "rb"), *temp;
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter patient name to delete: ");
    fgets(name, MAX_NAME, stdin);
    name[strcspn(name, "\n")] = 0;
    temp = fopen("temp.dat", "wb");
    while (fread(&patient, sizeof(struct Patient), 1, file)) {
        if (strcmp(patient.name, name) != 0) {
            fwrite(&patient, sizeof(struct Patient), 1, temp);
        } else {
            found = 1;
        }
    }
    fclose(file);
    fclose(temp);
    remove("patients.dat");
    rename("temp.dat", "patients.dat");
    if (found)
        printf("Patient record deleted successfully!\n");
    else
        printf("Patient not found!\n");
}
