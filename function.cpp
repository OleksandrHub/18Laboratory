#include "function.h"
string base_data;
int user = 0;

// Функція: Меню
void menu(){
    clear();
    cout << "Вітаємо в базі даних учнів класу " << endl 
    << "Виберіть Користувача:" << endl 
    << "1 - Гість" << endl 
    << "2 - Адміністратор" << endl;
    cin >> user;
    switch(user){
        case 1: clear(); replaceBD(); break;
        case 2: clear(); password(); break;
        default: error_value();
    }
}

// Функція: Гість
void guest(){
    int oper;
    cout << "1 - Швидкий пошук" << endl 
    << "2 - Розширений пошук" << endl
    << "3 - Сортування учнів" << endl 
    << "4 - Список учнів" << endl
    << "5 - Сумарний рейтинг" << endl 
    << "6 - Зміна бази даних" << endl
    << "0 - Вихід" << endl;
    cin >> oper;
    switch (oper){
        case 1: clear(); speedSearch();break;
        case 2: clear(); advancedSearch();break;
        case 3: clear(); sortStudents();break;
        case 4: clear(); listStudents();break;
        case 5: clear(); sumRainting();break;
        case 6: clear(); replaceBD(); break;
        case 0: clear(); print_exit();break;
        default: error_value();
    }
}

// Функція: Адміністратор
void admin(){
    int oper;
    cout << "1 - Створення файла бази даних" << endl
    << "2 - Додати учня" << endl
    << "3 - Список учнів" << endl
    << "4 - Швидкий пошук" << endl
    << "5 - Сортування учнів" << endl
    << "6 - Редагування даних учня" << endl
    << "7 - Видалення учня" << endl
    << "8 - Розширений пошук" << endl
    << "9 - Сумарний рейтинг" << endl
    << "10 - Зміна бази даних" << endl
    << "0 - Вихід" << endl;
    cin >> oper;
    switch (oper){
        case 1: clear(); createBD();break;
        case 2: clear(); addStudent();break;
        case 3: clear(); listStudents();break;
        case 4: clear(); speedSearch();break;
        case 5: clear(); sortStudents();break;
        case 6: clear(); editStudentBD();break;
        case 7: clear(); deleteBD();break;
        case 8: clear(); advancedSearch();break;
        case 9: clear(); sumRainting();break;
        case 10: clear(); replaceBD();break;
        case 0: print_exit();break;
        default: error_value();
    }
}
#pragma region ОсновніФункції
// Створенння бази даних 
void createBD(){
    cout << "Введіть назву Бази Даних" << endl;
    cin.ignore(); getline(cin, base_data); base_data += ".bin";
    fstream file(base_data, ios::binary | ios::out);
    clear();
    if (file.is_open()) {
        cout << "Базу Даних створено! " << base_data << endl;
        file.close();
    } else  cout << "Помилка створення Бази даних!\n";
    returnUser();
}

// Зміна бази даних
void replaceBD(){
    cout << "Введіть назву Бази Даних (Якщо не хочете підклютатися натисніть Enter)" << endl;
    cin.ignore(); getline(cin, base_data); base_data += ".bin";
    clear();
    if (base_data != ".bin"){
        cout << "Базу Даних змінено! На " << base_data << endl;
    } else cout << "Ви не обрали базу даних\n";
    returnUser();
}

//Функція: Додати учня
void addStudent(){
    clear();cin.ignore();
    ifstream checkFile(base_data, ios::binary);
    error_openBD(checkFile);
    checkFile.close();
    Students student;
    cout << "Введіть Ім'я учня: "; cin.getline(student.firstName, 50);
    cout << "Введіть Прізвище учня: "; cin.getline(student.lastName, 50);
    cout << "Введіть Дату народження (Формат ХХ.ХХ.ХХХХ): "; cin.getline(student.date, 30);
    cout << "Введіть Стать Man/Woman учня: "; cin.getline(student.sex, 20);
    cout << "Введіть Номер (Формат +380ХХХХХХХХ): ";  cin.getline(student.phoneNumber, 30);
    cout << "Введіть Адресу учня: "; cin.getline(student.address, 200);
    cout << "Введіть Рейтинг учня: "; cin.getline(student.reiting, 10);
    ofstream file(base_data, ios::binary | ios::out | ios::app);
    file.write(reinterpret_cast<const char*>(&student), sizeof(Students));
    file.close();
    clear();
    cout << "Дані успішно записано у Базу даних!" << std::endl;
    returnUser();
}

//Функція: Читання з списку
void listStudents(){
    ifstream file(base_data, ios::binary);
    error_openBD(file);
    Students student;
    while (file.read(reinterpret_cast<char*>(&student), sizeof(Students))) {
        studentPrint(student);
        cout << "----------------------" << "\n";
    }
    if (file.eof()) cout << "\nЧитання завершено, всі дані були зчитані." << std::endl;
    else cout << "\nПомилка під час читання Бази даних!" << std::endl;
    file.close();
    Enter();
}

//Функція: швидкого пошуку
void speedSearch(){
    ifstream file(base_data, ios::binary);
    error_openBD(file);
    Students student;
    string name, lastName;
    bool info{false};
    cin.ignore();
    cout << "Введіть Ім'я: "; getline(cin, name);
    cout << "Введіть Прізвище: "; getline(cin, lastName); cout << "\n";
    while (file.read(reinterpret_cast<char*>(&student), sizeof(Students))) {
        if (student.firstName == name & student.lastName == lastName){
            studentPrint(student);
            cout << "----------------------" << "\n";
            info = true;
        }
    }
    if (info == false) cout << "Учня не знайдено!" << endl;
    file.close();
    Enter();
}

//Функція: Сортування
void sortStudents() {
    ifstream inputFile(base_data, ios::binary);
    error_openBD(inputFile);
    vector<Students> studentsList;
    Students student;

    while (inputFile.read(reinterpret_cast<char*>(&student), sizeof(Students))) {
        studentsList.push_back(student);
    }

    inputFile.close();
    if (studentsList.empty()) {
        cout << "База даних порожня! Немає що сортувати." << endl;
        returnUser();
    }

    cout << "Виберіть критерій сортування:\n" << "1 - Ім'я\n" << "2 - Прізвище\n" << "3 - Рейтинг\n";
    int choice; cin >> choice;

    switch (choice) {
        case 1:
            sort(studentsList.begin(), studentsList.end(), 
                 [](const Students &a, const Students &b) {
                     return strcmp(a.firstName, b.firstName) < 0;
                 });
            break;
        case 2:
            sort(studentsList.begin(), studentsList.end(), 
                 [](const Students &a, const Students &b) {
                     return strcmp(a.lastName, b.lastName) < 0;
                 });
            break;
        case 3:
            sort(studentsList.begin(), studentsList.end(), 
                 [](const Students &a, const Students &b) {
                     return stod(a.reiting) > stod(b.reiting);
                 });
            break;
        default:
            cout << "Невірний вибір!\n";
            returnUser();
    }

    ofstream outputFile(base_data, ios::binary | ios::trunc);
    for (const auto &s : studentsList) {
        outputFile.write(reinterpret_cast<const char*>(&s), sizeof(Students));
    }
    outputFile.close();

    clear();
    cout << "Сортування завершено!\n";
    returnUser();
}

//Функція: Редагування даних учня
void editStudentBD(){
    ifstream inFile(base_data, ios::binary);
    error_openBD(inFile);
    ofstream tempFile("$%&%$%&^.bin", ios::binary);

    Students student;
    string name, lastName;
    bool found = false;
    cin.ignore();
    cout << "Введіть Ім'я: "; getline(cin, name);
    cout << "Введіть Прізвище: "; getline(cin, lastName); cout << "\n";
    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(Students))) {
        if (student.firstName == name & student.lastName == lastName){
            found = true;
            cout << "\nЗнайдено учня:\n";
            studentPrint(student);
            cout << "\nВиберіть номер поля для редагування (1-7): ";
            int choice;
            cin >> choice;
            cin.ignore();
            switch (choice) {
                case 1: cout << "Нове ім'я: "; cin.getline(student.firstName, 50); break;
                case 2: cout << "Нове прізвище: "; cin.getline(student.lastName, 50); break;
                case 3: cout << "Нова дата народження: "; cin.getline(student.date, 30); break;
                case 4: cout << "Нова стать: "; cin.getline(student.sex, 10); break;
                case 5: cout << "Новий телефон: "; cin.getline(student.phoneNumber, 30); break;
                case 6: cout << "Нова адреса: "; cin.getline(student.address, 200); break;
                case 7: cout << "Новий рейтинг: "; cin.getline(student.reiting, 10); break;
                default: cout << "Невірний вибір!\n"; returnUser();
            } 
        }
        tempFile.write(reinterpret_cast<const char*>(&student), sizeof(Students));
    }
    inFile.close();
    tempFile.close();
    forDelete(found, name, lastName);
}

//Функція: Видалення з Бази Даних
void deleteBD(){
    ifstream inFile(base_data, ios::binary);
    error_openBD(inFile);
    ofstream tempFile("$%&%$%&^.bin", ios::binary);
    Students student;
    string name, lastName;
    bool found = false;
    cin.ignore();
    cout << "Введіть Ім'я: "; getline(cin, name);
    cout << "Введіть Прізвище: "; getline(cin, lastName); cout << "\n";
    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(Students))) {
        if (student.firstName == name & student.lastName == lastName){
            found = true;
        } else {
            tempFile.write(reinterpret_cast<const char*>(&student), sizeof(Students));
        }
    }
    inFile.close();
    tempFile.close();
    forDelete(found, name, lastName);
}

//Функція: розширений пошук
void advancedSearch(){
    ifstream file(base_data, ios::binary);
    error_openBD(file);
    Students student;
    string right;
    int oper;
    bool info{false};

    cout << "Виберіть параметр пошуку" << endl 
    << "1 - Ім'я" << endl
    << "2 - Прізвище" << endl
    << "3 - Телефон" << endl
    << "4 - Стать" << endl;
    cin >> oper; cout << endl;
    cin.ignore();
    cout << "Введіть значення: " << endl; getline(cin, right); cout << endl;
    clear();

    while (file.read(reinterpret_cast<char*>(&student), sizeof(Students))) {
        bool match = false;
        switch (oper) {
            case 1: match = (strcmp(student.firstName, right.c_str()) == 0); break;
            case 2: match = (strcmp(student.lastName, right.c_str()) == 0); break;
            case 3: match = (strcmp(student.phoneNumber, right.c_str()) == 0); break;
            case 4: match = (strcmp(student.sex, right.c_str()) == 0); break;
            default: clear(); cout << "Невірний параметр!"; returnUser();
        }
        if (match){
            studentPrint(student);
            cout << "----------------------" << "\n";
            info = true;
        }
    }
    if (info == false) cout << "Учня не знайдено!" << endl;
    file.close();
    Enter();
}

//Функція: Сумарний Рейтинг
void sumRainting(){
    ifstream file(base_data, ios::binary);
    error_openBD(file);
    Students student;
    double raiting{0};
    while (file.read(reinterpret_cast<char*>(&student), sizeof(Students))) {
        raiting += stod(student.reiting);
    }
    cout << "Сумарний рейтинг: " << raiting << endl;
    file.close(); 
    Enter();
}
#pragma endregion

#pragma region ДодатковіФункції
// Функція: Очищення екрану
void clear(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Функція: Пароль
void password(){
    int code;
    cout << "Вітаю у Базі даних учні класу" << endl
    << "Ви ввійшли як адміністратор" << endl
    << "Введіть пароль: " << endl;
    cin >> code;
    clear();
    if (code == 322){
        replaceBD();
    } else error_value();
}

// Функція: Виводу даних учня
void studentPrint(const Students &student){
    cout << "1. Ім'я: " << student.firstName << "\n"
    << "2. Прізвище: " << student.lastName << "\n"
    << "3. Дата народження: " << student.date << "\n"
    << "4. Стать: " << student.sex << "\n"
    << "5. Телефон: " << student.phoneNumber << "\n"
    << "6. Адреса: " << student.address << "\n"
    << "7. Рейтинг: " << student.reiting << "\n";
}

// Функція натисніть Ентер щоб продовжити
void Enter(){
    string fake;
    cout << "Натисніть Enter, щоб продовжити ";
    cin.ignore();
    getline(cin, fake);
    clear();
    returnUser();
}

// Функція для Видалення
void forDelete(bool &found, string &name, string &lastName){
    clear();
    const char* filename = base_data.c_str();;
    if (found){
        remove(filename); 
        rename("$%&%$%&^.bin", filename);
        cout << "Операцію виконано над '" << name << " " << lastName << "'\n" ; 
    } else {
        remove("$%&%$%&^.bin");
        cout << "Запис '" << name << " " << lastName << "' не знайдено." << endl;
    }
    returnUser();
}

// Функція: для повернення
void returnUser(){
    if (user == 2){
        admin();
    } else guest();
}

// Функція: перевірка чи існує БД
void error_openBD(ifstream &file) {
    if (!file) {
        clear();
        cout << "Помилка відкриття Бази даних!" << endl;
        returnUser();
    }
}

// Функція: Якщо введене не вірне значення
void error_value(){
    clear();
    cout << "Невірне значення!" << endl;
    print_exit();
}

// Функція: Виходу
void print_exit(){
    cout << "Роботу завершено!" << endl;
    exit(0);
}
#pragma endregion