#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// Product blueprint
struct Product {
    int id;
    string name;
    string category;
    double price;
    int stock;
};

// Cart item structure
struct CartItem {
    Product product;
    int quantity;
};

int main() {
    int mainChoice = 0;
    cout << fixed << setprecision(2);

    cout << "==================================================" << endl;
    cout << "           WELCOME TO SHOPEE CLI STORE            " << endl;
    cout << "==================================================" << endl;

    while (mainChoice != 5) {
        cout << "\n--------------------------------------------------" << endl;
        cout << "                 MAIN CATEGORIES                  " << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "1. Electronics & Gadgets" << endl;
        cout << "2. Fashion & Apparel" << endl;
        cout << "3. Groceries & Essentials" << endl;
        cout << "4. View Cart & Proceed to Checkout" << endl;
        cout << "5. Exit Store" << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "Select an option (1-5): ";

        if (!(cin >> mainChoice)) {
            cout << "[ERROR] Invalid input. Please enter a numerical option (1-5)." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (mainChoice) {
            case 1:
            case 2:
            case 3:
                cout << ">> Category selected. (Catalog coming soon)" << endl;
                break;
            case 4:
                cout << ">> Cart is currently under development." << endl;
                break;
            case 5:
                cout << "\nThank you for visiting Shopee" << endl;
                break;
            default:
                cout << "[ERROR] Invalid option. Please choose between 1 and 5." << endl;
                break;
        }
    }
    return 0;
}