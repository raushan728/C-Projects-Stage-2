#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 100

struct Account {
    int accountNumber;
    char name[MAX_NAME];
    float balance;
};

void createAccount();
void depositMoney();
void withdrawMoney();
void checkBalance();
void displayMenu();

int main() {
    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice, try again.\n");
        }
    } while (choice != 5);
    return 0;
}

void displayMenu() {
    printf("\nBank Management System\n");
    printf("1. Create Account\n");
    printf("2. Deposit Money\n");
    printf("3. Withdraw Money\n");
    printf("4. Check Balance\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

void createAccount() {
    struct Account acc;
    FILE *file = fopen("accounts.dat", "ab");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter account number: ");
    scanf("%d", &acc.accountNumber);
    getchar();
    printf("Enter account holder name: ");
    fgets(acc.name, MAX_NAME, stdin);
    acc.name[strcspn(acc.name, "\n")] = 0;
    printf("Enter initial deposit: ");
    scanf("%f", &acc.balance);
    fwrite(&acc, sizeof(struct Account), 1, file);
    fclose(file);
    printf("Account created successfully!\n");
}

void depositMoney() {
    int accNum;
    float amount;
    struct Account acc;
    int found = 0;
    FILE *file = fopen("accounts.dat", "rb+"), *temp;
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter account number: ");
    scanf("%d", &accNum);
    temp = fopen("temp.dat", "wb");
    while (fread(&acc, sizeof(struct Account), 1, file)) {
        if (acc.accountNumber == accNum) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            acc.balance += amount;
            found = 1;
        }
        fwrite(&acc, sizeof(struct Account), 1, temp);
    }
    fclose(file);
    fclose(temp);
    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");
    if (found)
        printf("Amount deposited successfully!\n");
    else
        printf("Account not found!\n");
}

void withdrawMoney() {
    int accNum;
    float amount;
    struct Account acc;
    int found = 0;
    FILE *file = fopen("accounts.dat", "rb+"), *temp;
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter account number: ");
    scanf("%d", &accNum);
    temp = fopen("temp.dat", "wb");
    while (fread(&acc, sizeof(struct Account), 1, file)) {
        if (acc.accountNumber == accNum) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            if (amount > acc.balance) {
                printf("Insufficient balance!\n");
            } else {
                acc.balance -= amount;
                printf("Withdrawal successful!\n");
            }
            found = 1;
        }
        fwrite(&acc, sizeof(struct Account), 1, temp);
    }
    fclose(file);
    fclose(temp);
    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");
    if (!found)
        printf("Account not found!\n");
}

void checkBalance() {
    int accNum;
    struct Account acc;
    int found = 0;
    FILE *file = fopen("accounts.dat", "rb");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter account number: ");
    scanf("%d", &accNum);
    while (fread(&acc, sizeof(struct Account), 1, file)) {
        if (acc.accountNumber == accNum) {
            printf("Account Holder: %s, Balance: %.2f\n", acc.name, acc.balance);
            found = 1;
            break;
        }
    }
    fclose(file);
    if (!found)
        printf("Account not found!\n");
}
