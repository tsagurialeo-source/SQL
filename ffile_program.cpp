#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Функция для создания и заполнения файла
void createAndFillFile() {
    ofstream file("products.txt");
    if (!file.is_open()) {
        cout << "Ошибка создания файла!" << endl;
        return;
    }

    cout << "=== СОЗДАНИЕ ФАЙЛА ПРОДУКТОВ ===" << endl;
    cout << "Вводите данные о продуктах (для завершения введите пустую строку в названии)" << endl;

    string name;
    double price;
    int quantity;

    while (true) {
        cout << "Название продукта: ";
        getline(cin, name);

        if (name.empty()) {
            break;
        }

        cout << "Цена: ";
        cin >> price;
        cout << "Количество: ";
        cin >> quantity;
        cin.ignore(); // очистка буфера

        // Запись в файл
        file << name << " " << price << " " << quantity << endl;
        cout << "Продукт добавлен!" << endl << endl;
    }

    file.close();
    cout << "Файл products.txt создан и заполнен!" << endl;
}

// Функция для поиска продукта по названию
void searchProduct() {
    ifstream file("products.txt");
    if (!file.is_open()) {
        cout << "Файл products.txt не найден!" << endl;
        return;
    }

    string searchName;
    cout << "Введите название продукта для поиска: ";
    getline(cin, searchName);

    string name;
    double price;
    int quantity;
    bool found = false;

    ofstream output("output.txt", ios::app);
    output << "=== РЕЗУЛЬТАТЫ ПОИСКА ===" << endl;

    while (file >> name >> price >> quantity) {
        if (name == searchName) {
            cout << "Найден продукт: " << name << ", Цена: " << price
                 << ", Количество: " << quantity << endl;
            output << "Найден продукт: " << name << ", Цена: " << price
                   << ", Количество: " << quantity << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Продукт не найден!" << endl;
        output << "Продукт не найден!" << endl;
    }

    output << "=======================" << endl << endl;
    file.close();
    output.close();
}

// Функция для сортировки продуктов
void sortProducts() {
    ifstream file("products.txt");
    if (!file.is_open()) {
        cout << "Файл products.txt не найден!" << endl;
        return;
    }

    // Чтение всех продуктов в массивы
    const int MAX_PRODUCTS = 100;
    string names[MAX_PRODUCTS];
    double prices[MAX_PRODUCTS];
    int quantities[MAX_PRODUCTS];
    int count = 0;

    while (file >> names[count] >> prices[count] >> quantities[count]) {
        count++;
        if (count >= MAX_PRODUCTS) break;
    }
    file.close();

    // Выбор критерия сортировки
    int choice;
    cout << "Выберите критерий сортировки:" << endl;
    cout << "1 - По цене" << endl;
    cout << "2 - По количеству" << endl;
    cout << "Ваш выбор: ";
    cin >> choice;
    cin.ignore();

    // Сортировка пузырьком
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            bool needSwap = false;
            if (choice == 1 && prices[j] > prices[j + 1]) {
                needSwap = true;
            } else if (choice == 2 && quantities[j] > quantities[j + 1]) {
                needSwap = true;
            }

            if (needSwap) {
                // Обмен местами
                swap(names[j], names[j + 1]);
                swap(prices[j], prices[j + 1]);
                swap(quantities[j], quantities[j + 1]);
            }
        }
    }

    // Запись отсортированных данных обратно в файл
    ofstream outFile("products.txt");
    ofstream output("output.txt", ios::app);
    output << "=== РЕЗУЛЬТАТЫ СОРТИРОВКИ ===" << endl;

    for (int i = 0; i < count; i++) {
        outFile << names[i] << " " << prices[i] << " " << quantities[i] << endl;
        output << names[i] << " " << prices[i] << " " << quantities[i] << endl;
    }

    cout << "Продукты отсортированы!" << endl;
    output << "========================" << endl << endl;
    outFile.close();
    output.close();
}

// Функция для добавления нового продукта
void addProduct() {
    ofstream file("products.txt", ios::app);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }

    string name;
    double price;
    int quantity;

    cout << "=== ДОБАВЛЕНИЕ НОВОГО ПРОДУКТА ===" << endl;
    cout << "Название продукта: ";
    getline(cin, name);
    cout << "Цена: ";
    cin >> price;
    cout << "Количество: ";
    cin >> quantity;
    cin.ignore();

    file << name << " " << price << " " << quantity << endl;

    ofstream output("output.txt", ios::app);
    output << "=== ДОБАВЛЕН НОВЫЙ ПРОДУКТ ===" << endl;
    output << name << " " << price << " " << quantity << endl;
    output << "==========================" << endl << endl;

    cout << "Продукт добавлен!" << endl;
    file.close();
    output.close();
}

// Функция для вывода продуктов по цене
void showProductsByPrice() {
    ifstream file("products.txt");
    if (!file.is_open()) {
        cout << "Файл products.txt не найден!" << endl;
        return;
    }

    double maxPrice;
    cout << "Введите максимальную цену: ";
    cin >> maxPrice;
    cin.ignore();

    string name;
    double price;
    int quantity;
    bool found = false;

    ofstream output("output.txt", ios::app);
    output << "=== ПРОДУКТЫ ПО ЦЕНЕ (до " << maxPrice << ") ===" << endl;

    cout << "Продукты с ценой до " << maxPrice << ":" << endl;
    while (file >> name >> price >> quantity) {
        if (price <= maxPrice) {
            cout << name << " - Цена: " << price << ", Количество: " << quantity << endl;
            output << name << " - Цена: " << price << ", Количество: " << quantity << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Продукты не найдены!" << endl;
        output << "Продукты не найдены!" << endl;
    }

    output << "===============================" << endl << endl;
    file.close();
    output.close();
}

// Функция для отображения всех продуктов
void showAllProducts() {
    ifstream file("products.txt");
    if (!file.is_open()) {
        cout << "Файл products.txt не найден!" << endl;
        return;
    }

    string name;
    double price;
    int quantity;

    cout << "=== ВСЕ ПРОДУКТЫ ===" << endl;
    while (file >> name >> price >> quantity) {
        cout << "Название: " << name << ", Цена: " << price
             << ", Количество: " << quantity << endl;
    }
    cout << "===================" << endl;
    file.close();
}

// Главное меню
int main() {
    int choice;

    do {
        cout << "\n=== МЕНЮ УПРАВЛЕНИЯ ПРОДУКТАМИ ===" << endl;
        cout << "1. Создание и заполнение файла" << endl;
        cout << "2. Поиск продукта по названию" << endl;
        cout << "3. Сортировка продуктов" << endl;
        cout << "4. Добавление нового продукта" << endl;
        cout << "5. Показать продукты по цене" << endl;
        cout << "6. Показать все продукты" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                createAndFillFile();
                break;
            case 2:
                searchProduct();
                break;
            case 3:
                sortProducts();
                break;
            case 4:
                addProduct();
                break;
            case 5:
                showProductsByPrice();
                break;
            case 6:
                showAllProducts();
                break;
            case 0:
                cout << "Программа завершена!" << endl;
                break;
            default:
                cout << "Неверный выбор!" << endl;
        }

    } while (choice != 0);

    return 0;
}
