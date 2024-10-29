// HW3.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <list>
#include <forward_list>
#include <vector>
#include <string>
#include <regex>
#include <algorithm>

using namespace std;

struct Book {
    string title;
    string author;
    string id;

    Book(string t, string a, string i) : title(t), author(a), id(i) {}
};

struct Borrower {
    string name;
    vector<string> borrowedBooks;

    Borrower(string n, vector<string> books) : name(n), borrowedBooks(books) {}
};

bool isValidBookId(const string& id) {
    return regex_match(id, regex("^[A-Za-z][0-9]{4}$")); // Validates format A1234
}

void addBook(list<Book>& books) {
    string title, author, id;
    cout << "輸入書名: ";
    cin.ignore();
    getline(cin, title);
    cout << "輸入作者: ";
    getline(cin, author);

    do {
        cout << "輸入圖書編號 (格式: A1234): ";
        cin >> id;
    } while (!isValidBookId(id));

    books.emplace_back(title, author, id);
    cout << "圖書添加成功。" << endl;
}

void removeBook(list<Book>& books) {
    string id;
    cout << "輸入要刪除的圖書編號: ";
    cin >> id;

    auto it = find_if(books.begin(), books.end(), [&id](const Book& book) { return book.id == id; });
    if (it != books.end()) {
        books.erase(it);
        cout << "圖書刪除成功。" << endl;
    }
    else {
        cout << "未找到該圖書編號。" << endl;
    }
}

void searchBook(const list<Book>& books) {
    string id;
    cout << "輸入要搜索的圖書編號: ";
    cin >> id;

    auto it = find_if(books.begin(), books.end(), [&id](const Book& book) { return book.id == id; });
    if (it != books.end()) {
        cout << "書名: " << it->title << ", 作者: " << it->author << endl;
    }
    else {
        cout << "未找到該圖書編號。" << endl;
    }
}

void listBooks(const list<Book>& books) {
    list<Book> sortedBooks = books; // Create a copy to sort
    sortedBooks.sort([](const Book& a, const Book& b) { return a.id < b.id; });

    cout << "所有圖書:\n";
    for (const auto& book : sortedBooks) {
        cout << "書名: " << book.title << ", 作者: " << book.author << ", 圖書編號: " << book.id << endl;
    }
}

void addBorrower(forward_list<Borrower>& borrowers) {
    string name;
    cout << "輸入借閱者姓名: ";
    cin.ignore();
    getline(cin, name);

    borrowers.emplace_front(name, vector<string>{});
    cout << "借閱者添加成功。" << endl;
}

void removeBorrower(forward_list<Borrower>& borrowers) {
    string name;
    cout << "輸入要刪除的借閱者姓名: ";
    cin >> name;

    forward_list<Borrower> newList;
    bool found = false;

    for (const auto& borrower : borrowers) {
        if (borrower.name != name) {
            newList.emplace_front(borrower.name, borrower.borrowedBooks);
        }
        else {
            found = true;
        }
    }

    borrowers = newList; // Reset borrowers to newList (in reverse order)

    if (found) {
        cout << "借閱者刪除成功。" << endl;
    }
    else {
        cout << "未找到該借閱者姓名。" << endl;
    }
}

void searchBorrower(const forward_list<Borrower>& borrowers) {
    string name;
    cout << "輸入要搜索的借閱者姓名: ";
    cin >> name;

    for (const auto& borrower : borrowers) {
        if (borrower.name == name) {
            cout << "借閱者: " << borrower.name << ", 借閱的圖書: ";
            for (const auto& bookId : borrower.borrowedBooks) {
                cout << bookId << " ";
            }
            cout << endl;
            return;
        }
    }
    cout << "未找到該借閱者姓名。" << endl;
}

void listBorrowers(const forward_list<Borrower>& borrowers) {
    cout << "所有借閱者:\n";
    for (const auto& borrower : borrowers) {
        cout << "借閱者姓名: " << borrower.name << ", 借閱的圖書: ";
        for (const auto& bookId : borrower.borrowedBooks) {
            cout << bookId << " ";
        }
        cout << endl;
    }
}

void displayMenu() {
    cout << "\n--- 圖書館管理系統 ---" << endl;
    cout << "1. 添加新圖書" << endl;
    cout << "2. 刪除指定圖書編號的圖書" << endl;
    cout << "3. 搜索指定圖書編號的圖書" << endl;
    cout << "4. 列出所有圖書" << endl;
    cout << "5. 添加新借閱者" << endl;
    cout << "6. 刪除指定姓名的借閱者" << endl;
    cout << "7. 搜索指定姓名的借閱者" << endl;~
    cout << "8. 列出所有借閱者" << endl;
    cout << "0. 退出系統" << endl;
    cout << "請選擇操作: ";
}

int main() {
    list<Book> books; // Initialize an empty list of books
    forward_list<Borrower> borrowers; // Initialize an empty list of borrowers

    // Sample books
    books = {
        {"紅樓夢", "曹雪芹", "A1234"},
        {"西遊記", "吳承恩", "B2345"},
        {"水滸傳", "施耐庵", "B3456"},
        {"三國演義", "羅貫中", "C4567"},
        {"金瓶梅", "蘭陵笑笑生", "C5678"},
        {"聊齋志異", "蒲松齡", "D6789"},
        {"儒林外史", "吳敬梓", "D7890"},
        {"封神演義", "許仲琳", "E8901"},
        {"鏡花緣", "李汝珍", "E9012"},
        {"老殘遊記", "劉鶚", "F0123"}
    };

    // Sample borrowers
    borrowers.emplace_front("小明", vector<string>{"A1234", "B2345"});
    borrowers.emplace_front("小華", vector<string>{"C4567"});
    borrowers.emplace_front("小美", vector<string>{"D6789", "E8901"});
    borrowers.emplace_front("小強", vector<string>{"F0123"});
    borrowers.emplace_front("小麗", vector<string>{"B3456", "C5678"});

    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1: addBook(books); break;
        case 2: removeBook(books); break;
        case 3: searchBook(books); break;
        case 4: listBooks(books); break;
        case 5: addBorrower(borrowers); break;
        case 6: removeBorrower(borrowers); break;
        case 7: searchBorrower(borrowers); break;
        case 8: listBorrowers(borrowers); break;
        case 0: cout << "退出系統。" << endl; break;
        default: cout << "無效選擇，請重試。" << endl; break;
        }
    } while (choice != 0);

    return 0;
}


// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
