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
// 预设商品数据库
Product products[] = {
    {101, "Wireless Bluetooth Earbuds", 45.00, 15, "Electronics & Gadgets"},
    {102, "Fast Charging USB-C Cable", 8.00, 50, "Electronics & Gadgets"},
    {103, "10000mAh Powerbank", 35.00, 20, "Electronics & Gadgets"},
    {104, "Strong wind 100 Gear High Speed Handheld Fan With Led Display", 53.35, 121, "Electronics & Gadgets"},
    {105, "Foldable Headphones HiFi Stereo Sound Bluetooth Long Battery Life Multi-mode Playback", 33.00, 38, "Electronics & Gadgets"},
    {201, "Oversized Cotton T-Shirt", 25.00, 40, "Fashion & Apparel"},
    {202, "Denim Jacket", 68.00, 10, "Fashion & Apparel"},
    {203, "Canvas Sneakers", 55.00, 15, "Fashion & Apparel"},
    {204, "Women Yoga Pants Fitness Pants Legging", 13.99, 225, "Fashion & Apparel"},
    {205, "Cool Feeling Comfortable Short Sleeve T-Shirt Men", 29.99, 103, "Fashion & Apparel"},
    {301, "Ayam Brand Sardeines in Tomato Sauce 155g", 5.70, 50, "Groceries & Essentials"},
    {302, "Siew Pak Choy 250g", 1.29, 5, "Groceries & Essentials"},
    {303, "Korean Original Luncheon Meat 340g", 8.16, 39, "Groceries & Essentials"},
    {304, "Purple Sweet Potato", 3.60, 26, "Groceries & Essentials"},
    {305, "Vietnam Cavendish Banana 1kg", 4.99, 14, "Groceries & Essentials"},
};
// 全局购物车数据
CartItem cart[50];
int cartSize = 0;
double subtotal = 0.0;
// 显示分类商品菜单
void showCategoryMenu(string categoryTitle, int startId, int endId) {
    cout << "\n--------------------------------------------------" << endl;
    cout << "CATEGORY: " << categoryTitle << endl;
    cout << "--------------------------------------------------" << endl;
    cout << left << setw(7) << "ID" 
         << setw(31) << "Item Name" 
         << setw(12) << "Price (RM)" 
         << "Stock" << endl;
    
    for (int i = 0; i < 6; i++) {
        if (products[i].id >= startId && products[i].id <= endId) {
            cout << left << setw(7) << products[i].id 
                 << setw(31) << products[i].name 
                 << right << setw(6) << fixed << setprecision(2) << products[i].price 
                 << "        " << products[i].stock << endl;
        }
    }
    cout << "--------------------------------------------------" << endl;
}
// 添加商品到购物车逻辑
void handlePurchase(int startId, int endId, string categoryName, string shortCatName) {
    int itemId, qty;
    cout << "Enter Item ID to purchase: ";
    cin >> itemId;
    
    int index = -1;
    for (int i = 0; i < 6; i++) {
        if (products[i].id == itemId) {
            index = i;
            break;
        }
    }
    
    if (index != -1 && products[index].id >= startId && products[index].id <= endId) {
        cout << "Enter Quantity: ";
        cin >> qty;
        
        if (qty > 0 && qty <= products[index].stock) {
            cart[cartSize].category = products[index].category;
            cart[cartSize].name = products[index].name;
            cart[cartSize].price = products[index].price;
            cart[cartSize].qty = qty;
            cartSize++;
            
            subtotal += (products[index].price * qty);
            products[index].stock -= qty;
            
            cout << ">> Success: Added " << qty << "x " << products[index].name << " to cart.\n";
        } else {
            cout << ">> Error: Invalid quantity or insufficient stock.\n";
        }
    } else {
        cout << ">> Error: Invalid Item ID.\n";
    }
    
    int actionChoice;
    cout << "\nAction: [1] Return to Main Menu  [2] Shop More in " << shortCatName << endl;
    cout << "Enter choice: ";
    cin >> actionChoice;
    
    if (actionChoice == 2) {
        showCategoryMenu(categoryName, startId, endId);
        handlePurchase(startId, endId, categoryName, shortCatName);
    }
}
