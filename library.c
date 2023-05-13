#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100 // maximum number of books the library can hold
#define MAX_BORROWERS 100 // maximum number of borrowers the library can have

struct book {
    char title[50];
    char author[50];
    int id;
    int borrowed;
};

struct borrower {
    char name[50];
    int borrowed_books[MAX_BOOKS];
};

void add_book(struct book books[], int *num_books) {
    if (*num_books == MAX_BOOKS) {
        printf("The library is already at maximum capacity.\n");
        return;
    }

    struct book new_book;
    printf("Enter the title of the book: ");
    scanf("%s", new_book.title);
    printf("Enter the name of the author: ");
    scanf("%s", new_book.author);
    new_book.id = *num_books + 1;
    new_book.borrowed = 0;

    books[*num_books] = new_book;
    *num_books += 1;

    printf("Book added successfully.\n");
}

void remove_book(struct book books[], int *num_books) {
    int id;
    printf("Enter the ID of the book to remove: ");
    scanf("%d", &id);

    int index = -1;
    for (int i = 0; i < *num_books; i++) {
        if (books[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("No book found with ID %d.\n", id);
        return;
    }

    for (int i = index; i < *num_books - 1; i++) {
        books[i] = books[i+1];
    }
    *num_books -= 1;

    printf("Book removed successfully.\n");
}

void display_books(struct book books[], int num_books) {
    printf("%-5s %-30s %-20s %s\n", "ID", "Title", "Author", "Borrowed?");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < num_books; i++) {
        printf("%-5d %-30s %-20s %s\n", books[i].id, books[i].title, books[i].author, books[i].borrowed ? "Yes" : "No");
    }
}

void borrow_book(struct book books[], int num_books, struct borrower borrowers[], int *num_borrowers) {
    int id;
    printf("Enter the ID of the book to borrow: ");
    scanf("%d", &id);

    int book_index = -1;
    for (int i = 0; i < num_books; i++) {
        if (books[i].id == id) {
            book_index = i;
            break;
        }
    }

    if (book_index == -1) {
        printf("No book found with ID %d.\n", id);
        return;
    }

    int borrower_index = -1;
    char borrower_name[50];
    printf("Enter your name: ");
    scanf("%s", borrower_name);
    for (int i = 0; i < *num_borrowers; i++) {
        if (strcmp(borrowers[i].name, borrower_name) == 0) {
            borrower_index = i;
            break;
        }
    }

    if (borrower_index == -1) {
        struct borrower new_borrower;
        strcpy(new_borrower.name, borrower_name);
        new_borrower.borrowed_books[0] = id;
        *num_borrowers += 1;
        borrower_index = *num_borrowers - 1;
        borrowers[borrower_index] = new_borrower;
    } 
    else {
        for (int i = 0; i < MAX_BOOKS; i++) {
            if (borrowers[borrower_index].borrowed_books[i] == 0) {
                borrowers[borrower_index].borrowed_books[i] = id;
                break;
            }
        }
    }
    books[book_index].borrowed = 1;

printf("Book borrowed successfully.\n");
}

void return_book(struct book books[], int num_books, struct borrower borrowers[], int num_borrowers) {
int id;
printf("Enter the ID of the book to return: ");
scanf("%d", &id);
int book_index = -1;
for (int i = 0; i < num_books; i++) {
    if (books[i].id == id) {
        book_index = i;
        break;
    }
}

if (book_index == -1) {
    printf("No book found with ID %d.\n", id);
    return;
}

int borrower_index = -1;
char borrower_name[50];
printf("Enter your name: ");
scanf("%s", borrower_name);
for (int i = 0; i < num_borrowers; i++) {
    if (strcmp(borrowers[i].name, borrower_name) == 0) {
        borrower_index = i;
        break;
    }
}

if (borrower_index == -1) {
    printf("No borrower found with name %s.\n", borrower_name);
    return;
}

int borrowed_index = -1;
for (int i = 0; i < MAX_BOOKS; i++) {
    if (borrowers[borrower_index].borrowed_books[i] == id) {
        borrowed_index = i;
        break;
    }
}

if (borrowed_index == -1) {
    printf("Book with ID %d not found in borrower's record.\n", id);
    return;
}

for (int i = borrowed_index; i < MAX_BOOKS - 1; i++) {
    borrowers[borrower_index].borrowed_books[i] = borrowers[borrower_index].borrowed_books[i+1];
}
borrowers[borrower_index].borrowed_books[MAX_BOOKS-1] = 0;

books[book_index].borrowed = 0;

printf("Book returned successfully.\n");
}

int main() {
struct book books[MAX_BOOKS];
int num_books = 0;
struct borrower borrowers[MAX_BORROWERS];
int num_borrowers = 0;

int choice;
do {
    printf("\nLibrary Management System\n");
    printf("--------------------------\n");
    printf("1. Add Book\n");
    printf("2. Remove Book\n");
    printf("3. Display Books\n");
    printf("4. Borrow Book\n");
    printf("5. Return Book\n");
    printf("6. Exit\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            add_book(books, &num_books);
            break;
        case 2:
            remove_book(books, &num_books);
            break;
        case 3:
            display_books(books, num_books);
            break;
        case 4:
            borrow_book(books, num_books, borrowers, &num_borrowers);
            break;
        case 5:
            return_book(books, num_books, borrowers, num_borrowers);
            break;
        case 6:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
    }
} 
while (choice != 6);
return 0;
}

