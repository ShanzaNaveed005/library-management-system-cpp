#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

// ================= Structures =================
struct Book {
    int id;
    char title[50];
    char author[30];
    int quantity; // available copies
};

struct Member {
    int id;
    char name[30];
};

// ================= File Names =================
const char* bookFile = "library.txt";
const char* memberFile = "member.txt";

// ================= Function Prototypes =================
void mainMenu();
void bookMenu();
void memberMenu();
void borrowReturnMenu();
void addBook();
void displayBooks();
void displayAvailableBooks();
void searchBook();
void updateBook();
void deleteBook();
void addMember();
void displayMembers();
void searchMember();
void updateMember();
void deleteMember();
void borrowBook();
void returnBook();

// ================= Main Function =================
int main() {
    mainMenu();
    return 0;
}

// ================= Main Menu =================
void mainMenu() {
    int choice;
    do {
        cout << "\n=========== LIBRARY MANAGEMENT SYSTEM ==========\n";
        cout << "1. Book Management\n";
        cout << "2. Member Management\n";
        cout << "3. Borrow / Return Book\n";
        cout << "0. Exit\n";
        cout << "===============================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: bookMenu(); break;
            case 2: memberMenu(); break;
            case 3: borrowReturnMenu(); break;
            case 0: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while(choice != 0);
}

// ================= Book Menu =================
void bookMenu() {
    int choice;
    do {
        cout << "\n=========== BOOK MANAGEMENT ==========\n";
        cout << "1. Add Book\n2. Display All Books\n3. Search Book\n4. Update Book\n5. Delete Book\n6. Display Available Books\n0. Back to Main Menu\n";
        cout << "=====================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: updateBook(); break;
            case 5: deleteBook(); break;
            case 6: displayAvailableBooks(); break;
            case 0: break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while(choice != 0);
}

// ================= Member Menu =================
void memberMenu() {
    int choice;
    do {
        cout << "\n=========== MEMBER MANAGEMENT ==========\n";
        cout << "1. Add Member\n2. Display Members\n3. Search Member\n4. Update Member\n5. Delete Member\n0. Back to Main Menu\n";
        cout << "=======================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: addMember(); break;
            case 2: displayMembers(); break;
            case 3: searchMember(); break;
            case 4: updateMember(); break;
            case 5: deleteMember(); break;
            case 0: break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while(choice != 0);
}

// ================= Borrow / Return Menu =================
void borrowReturnMenu() {
    int choice;
    do {
        cout << "\n=========== BORROW / RETURN BOOK ==========\n";
        cout << "1. Borrow Book\n2. Return Book\n0. Back to Main Menu\n";
        cout << "==========================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: borrowBook(); break;
            case 2: returnBook(); break;
            case 0: break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while(choice != 0);
}

// ================= Add Book =================
void addBook() {
    Book b;
    cout << "\nEnter Book ID: ";
    cin >> b.id;
    cin.ignore();
    cout << "Enter Book Title: ";
    cin.getline(b.title,50);
    cout << "Enter Author Name: ";
    cin.getline(b.author,30);
    cout << "Enter Quantity: ";
    cin >> b.quantity;

    ofstream outFile(bookFile, ios::app);
    if(!outFile){ cout<<"Error opening file!\n"; return; }

    outFile << b.id << "\t" << b.title << "\t" << b.author << "\t" << b.quantity << "\n";
    outFile.close();
    cout << "Book added successfully!\n";
}

// ================= Display Books =================
void displayBooks() {
    ifstream inFile(bookFile);
    if(!inFile){ cout<<"No books found.\n"; return; }

    Book b;
    cout << "\n================ All Books ================\n";
    cout << left << setw(5) << "ID" << setw(30) << "Title" << setw(20) << "Author" << setw(10) << "Qty\n";
    cout << "==========================================\n";

    while(inFile >> b.id){
        inFile.ignore();
        inFile.getline(b.title,50,'\t');
        inFile.getline(b.author,30,'\t');
        inFile >> b.quantity;
        inFile.ignore();

        cout << left << setw(5) << b.id << setw(30) << b.title << setw(20) << b.author << setw(10) << b.quantity << endl;
    }
    inFile.close();
}

// ================= Display Available Books =================
void displayAvailableBooks() {
    ifstream inFile(bookFile);
    if(!inFile){ cout<<"No books found.\n"; return; }

    Book b;
    cout << "\n================ Available Books ================\n";
    cout << left << setw(5) << "ID" << setw(30) << "Title" << setw(20) << "Author" << setw(10) << "Qty\n";
    cout << "================================================\n";

    while(inFile >> b.id){
        inFile.ignore();
        inFile.getline(b.title,50,'\t');
        inFile.getline(b.author,30,'\t');
        inFile >> b.quantity;
        inFile.ignore();

        if(b.quantity > 0)
            cout << left << setw(5) << b.id << setw(30) << b.title << setw(20) << b.author << setw(10) << b.quantity << endl;
    }
    inFile.close();
}

// ================= Search Book =================
void searchBook() {
    int choice;
    cout << "Search by: 1. ID  2. Title : ";
    cin >> choice;
    cin.ignore();

    ifstream inFile(bookFile);
    if(!inFile){ cout<<"No books found.\n"; return; }

    Book b;
    bool found=false;

    if(choice == 1) {
        int searchId;
        cout<<"Enter Book ID: ";
        cin >> searchId;
        cin.ignore();

        while(inFile >> b.id){
            inFile.ignore();
            inFile.getline(b.title,50,'\t');
            inFile.getline(b.author,30,'\t');
            inFile >> b.quantity;
            inFile.ignore();
            if(b.id == searchId){
                found=true;
                break;
            }
        }
    }
    else if(choice == 2) {
        char searchTitle[50];
        cout<<"Enter Book Title: ";
        cin.getline(searchTitle,50);

        while(inFile >> b.id){
            inFile.ignore();
            inFile.getline(b.title,50,'\t');
            inFile.getline(b.author,30,'\t');
            inFile >> b.quantity;
            inFile.ignore();
            if(strcmp(b.title,searchTitle)==0){
                found=true;
                break;
            }
        }
    }
    if(found)
        cout << "\nBook Found: ID:" << b.id << "  Title:" << b.title << "  Author:" << b.author << "  Qty:" << b.quantity << endl;
    else
        cout << "Book not found.\n";

    inFile.close();
}

// ================= Update Book =================
void updateBook() {
    int updateId;
    cout<<"Enter Book ID to update: ";
    cin>>updateId;

    ifstream inFile(bookFile);
    ofstream outFile("temp.txt");
    if(!inFile || !outFile){ cout<<"Error opening file!\n"; return; }

    Book b;
    bool found=false;
    while(inFile >> b.id){
        inFile.ignore();
        inFile.getline(b.title,50,'\t');
        inFile.getline(b.author,30,'\t');
        inFile >> b.quantity;
        inFile.ignore();

        if(b.id == updateId){
            cout<<"Enter new Title: ";
            cin.ignore();
            cin.getline(b.title,50);
            cout<<"Enter new Author: ";
            cin.getline(b.author,30);
            cout<<"Enter new Quantity: ";
            cin>>b.quantity;
            found=true;
        }
        outFile << b.id << "\t" << b.title << "\t" << b.author << "\t" << b.quantity << "\n";
    }
    inFile.close();
    outFile.close();
    remove(bookFile);
    rename("temp.txt", bookFile);

    if(found) cout<<"Book updated successfully!\n";
    else cout<<"Book not found.\n";
}

// ================= Delete Book =================
void deleteBook() {
    int deleteId;
    cout<<"Enter Book ID to delete: ";
    cin>>deleteId;

    ifstream inFile(bookFile);
    ofstream outFile("temp.txt");
    if(!inFile || !outFile){ cout<<"Error opening file!\n"; return; }

    Book b;
    bool found=false;
    while(inFile >> b.id){
        inFile.ignore();
        inFile.getline(b.title,50,'\t');
        inFile.getline(b.author,30,'\t');
        inFile >> b.quantity;
        inFile.ignore();

        if(b.id != deleteId)
            outFile << b.id << "\t" << b.title << "\t" << b.author << "\t" << b.quantity << "\n";
        else found=true;
    }
    inFile.close();
    outFile.close();
    remove(bookFile);
    rename("temp.txt", bookFile);

    if(found) cout<<"Book deleted successfully!\n";
    else cout<<"Book not found.\n";
}

// ================= Add Member =================
void addMember() {
    Member m;
    cout<<"\nEnter Member ID: ";
    cin>>m.id;
    cin.ignore();
    cout<<"Enter Member Name: ";
    cin.getline(m.name,30);

    ofstream outFile(memberFile, ios::app);
    if(!outFile){ cout<<"Error opening file!\n"; return; }

    outFile << m.id << "\t" << m.name << "\n";
    outFile.close();
    cout<<"Member added successfully!\n";
}

// ================= Display Members =================
void displayMembers() {
    ifstream inFile(memberFile);
    if(!inFile){ cout<<"No members found.\n"; return; }

    Member m;
    cout<<"\n============= Members List =============\n";
    cout<<left<<setw(5)<<"ID"<<setw(30)<<"Name\n";
    cout<<"=======================================\n";

    while(inFile >> m.id){
        inFile.ignore();
        inFile.getline(m.name,30);
        cout<<left<<setw(5)<<m.id<<setw(30)<<m.name<<endl;
    }
    inFile.close();
}

// ================= Search Member =================
void searchMember() {
    int searchId;
    cout<<"Enter Member ID to search: ";
    cin>>searchId;

    ifstream inFile(memberFile);
    if(!inFile){ cout<<"No members found.\n"; return; }

    Member m;
    bool found=false;
    while(inFile >> m.id){
        inFile.ignore();
        inFile.getline(m.name,30);
        if(m.id==searchId){
            cout<<"\nMember Found: ID:"<<m.id<<"  Name:"<<m.name<<endl;
            found=true;
            break;
        }
    }
    if(!found) cout<<"Member not found.\n";
    inFile.close();
}

// ================= Update Member =================
void updateMember() {
    int updateId;
    cout<<"Enter Member ID to update: ";
    cin>>updateId;

    ifstream inFile(memberFile);
    ofstream outFile("temp_member.txt");
    if(!inFile || !outFile){ cout<<"Error opening file!\n"; return; }

    Member m;
    bool found=false;
    while(inFile >> m.id){
        inFile.ignore();
        inFile.getline(m.name,30);
        if(m.id==updateId){
            cout<<"Enter new Name: ";
            cin.ignore();
            cin.getline(m.name,30);
            found=true;
        }
        outFile << m.id << "\t" << m.name << "\n";
    }
    inFile.close();
    outFile.close();

    remove(memberFile);
    rename("temp_member.txt", memberFile);

    if(found) cout<<"Member updated successfully!\n";
    else cout<<"Member not found.\n";
}

// ================= Delete Member =================
void deleteMember() {
    int deleteId;
    cout<<"Enter Member ID to delete: ";
    cin>>deleteId;

    ifstream inFile(memberFile);
    ofstream outFile("temp_member.txt");
    if(!inFile || !outFile){ cout<<"Error opening file!\n"; return; }

    Member m;
    bool found=false;
    while(inFile >> m.id){
        inFile.ignore();
        inFile.getline(m.name,30);
        if(m.id!=deleteId)
            outFile << m.id << "\t" << m.name << "\n";
        else found=true;
    }
    inFile.close();
    outFile.close();

    remove(memberFile);
    rename("temp_member.txt", memberFile);

    if(found) cout<<"Member deleted successfully!\n";
    else cout<<"Member not found.\n";
}

// ================= Borrow Book =================
void borrowBook() {
    int bookId, memberId;
    cout << "Enter Member ID: ";
    cin >> memberId;

    ifstream memberIn(memberFile);
    bool memberFound=false;
    Member m;
    while(memberIn >> m.id){
        memberIn.ignore();
        memberIn.getline(m.name,30);
        if(m.id==memberId){ memberFound=true; break; }
    }
    memberIn.close();
    if(!memberFound){ cout<<"Member not found.\n"; return; }

    cout << "Enter Book ID to borrow: ";
    cin >> bookId;

    ifstream inFile(bookFile);
    ofstream outFile("temp.txt");
    Book b;
    bool bookFound=false;
    bool borrowed=false;

    while(inFile >> b.id){
        inFile.ignore();
        inFile.getline(b.title,50,'\t');
        inFile.getline(b.author,30,'\t');
        inFile >> b.quantity;
        inFile.ignore();

        if(b.id==bookId){
            bookFound=true;
            if(b.quantity>0){
                b.quantity--;
                borrowed=true;
                cout<<"Book borrowed successfully!\n";
            } else cout<<"Book not available.\n";
        }
        outFile << b.id << "\t" << b.title << "\t" << b.author << "\t" << b.quantity << "\n";
    }
    inFile.close();
    outFile.close();
    remove(bookFile);
    rename("temp.txt", bookFile);

    if(!bookFound) cout<<"Book not found.\n";
}

// ================= Return Book =================
void returnBook() {
    int bookId;
    cout << "Enter Book ID to return: ";
    cin >> bookId;

    ifstream inFile(bookFile);
    ofstream outFile("temp.txt");
    Book b;
    bool bookFound=false;

    while(inFile >> b.id){
        inFile.ignore();
        inFile.getline(b.title,50,'\t');
        inFile.getline(b.author,30,'\t');
        inFile >> b.quantity;
        inFile.ignore();

        if(b.id==bookId){
            b.quantity++;
            bookFound=true;
            cout<<"Book returned successfully!\n";
        }
        outFile << b.id << "\t" << b.title << "\t" << b.author << "\t" << b.quantity << "\n";
    }
    inFile.close();
    outFile.close();
    remove(bookFile);
    rename("temp.txt", bookFile);

    if(!bookFound) cout<<"Book not found.\n";
}

