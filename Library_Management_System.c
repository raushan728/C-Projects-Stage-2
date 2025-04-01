#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE 100
#define MAX_AUTHOR 100
#define MAX_ISBN 20

struct Book {
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    char isbn[MAX_ISBN];
};

void addBook();
void searchBook();
void updateBook();
void deleteBook();
void displayMenu();

int main() {
    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1: addBook(); break;
            case 2: searchBook(); break;
            case 3: updateBook(); break;
            case 4: deleteBook(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice, try again.\n");
        }
    } while (choice != 5);
    return 0;
}

void displayMenu() {
    printf("\nLibrary Management System\n");
    printf("1. Add Book\n");
    printf("2. Search Book\n");
    printf("3. Update Book\n");
    printf("4. Delete Book\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

void addBook() {
    struct Book book;
    FILE *file = fopen("books.dat", "ab");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter book title: ");
    fgets(book.title, MAX_TITLE, stdin);
    book.title[strcspn(book.title, "\n")] = 0;
    printf("Enter author name: ");
    fgets(book.author, MAX_AUTHOR, stdin);
    book.author[strcspn(book.author, "\n")] = 0;
    printf("Enter ISBN: ");
    fgets(book.isbn, MAX_ISBN, stdin);
    book.isbn[strcspn(book.isbn, "\n")] = 0;
    fwrite(&book, sizeof(struct Book), 1, file);
    fclose(file);
    printf("Book added successfully!\n");
}

void searchBook() {
    char title[MAX_TITLE];
    struct Book book;
    FILE *file = fopen("books.dat", "rb");
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter book title to search: ");
    fgets(title, MAX_TITLE, stdin);
    title[strcspn(title, "\n")] = 0;
    while (fread(&book, sizeof(struct Book), 1, file)) {
        if (strcmp(book.title, title) == 0) {
            printf("Book Found:\nTitle: %s\nAuthor: %s\nISBN: %s\n", book.title, book.author, book.isbn);
            fclose(file);
            return;
        }
    }
    printf("Book not found!\n");
    fclose(file);
}

void updateBook() {
    char title[MAX_TITLE];
    struct Book book;
    int found = 0;
    FILE *file = fopen("books.dat", "rb+"), *temp;
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter book title to update: ");
    fgets(title, MAX_TITLE, stdin);
    title[strcspn(title, "\n")] = 0;
    temp = fopen("temp.dat", "wb");
    while (fread(&book, sizeof(struct Book), 1, file)) {
        if (strcmp(book.title, title) == 0) {
            printf("Enter new author name: ");
            fgets(book.author, MAX_AUTHOR, stdin);
            book.author[strcspn(book.author, "\n")] = 0;
            printf("Enter new ISBN: ");
            fgets(book.isbn, MAX_ISBN, stdin);
            book.isbn[strcspn(book.isbn, "\n")] = 0;
            found = 1;
        }
        fwrite(&book, sizeof(struct Book), 1, temp);
    }
    fclose(file);
    fclose(temp);
    remove("books.dat");
    rename("temp.dat", "books.dat");
    if (found)
        printf("Book updated successfully!\n");
    else
        printf("Book not found!\n");
}

void deleteBook() {
    char title[MAX_TITLE];
    struct Book book;
    int found = 0;
    FILE *file = fopen("books.dat", "rb"), *temp;
    if (!file) {
        printf("Error opening file!\n");
        return;
    }
    printf("Enter book title to delete: ");
    fgets(title, MAX_TITLE, stdin);
    title[strcspn(title, "\n")] = 0;
    temp = fopen("temp.dat", "wb");
    while (fread(&book, sizeof(struct Book), 1, file)) {
        if (strcmp(book.title, title) != 0) {
            fwrite(&book, sizeof(struct Book), 1, temp);
        } else {
            found = 1;
        }
    }
    fclose(file);
    fclose(temp);
    remove("books.dat");
    rename("temp.dat", "books.dat");
    if (found)
        printf("Book deleted successfully!\n");
    else
        printf("Book not found!\n");
}
