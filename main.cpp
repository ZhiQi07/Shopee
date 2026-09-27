#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// 1. 数据结构定义
struct Product {
    int id;
    string name;
    double price;
    int stock;
    string category;
};

struct CartItem {
    Product product;
    int quantity;
};

// 2. 全局数据初始化
Product products[] = {
    {101, "Wireless Bluetooth Earbuds", 45.00, 15, "Electronics & Gadgets"},
    {102, "Fast Charging USB-C Cable", 8.00, 50, "Electronics & Gadgets"},
    {103, "10000mAh Powerbank", 35.00, 20, "Electronics & Gadgets"},
    {104, "Strong wind 100 Gear High Speed Handheld Fan", 53.35, 121, "Electronics & Gadgets"},
    {105, "Foldable Headphones HiFi Stereo Sound", 33.00, 38, "Electronics & Gadgets"},
    {201, "Oversized Cotton T-Shirt", 25.00, 40, "Fashion & Apparel"},
    {202, "Denim Jacket", 68.00, 10, "Fashion & Apparel"},
    {203, "Canvas Sneakers", 55.00, 15, "Fashion & Apparel"},
    {204, "Women Yoga Pants Fitness Pants Legging", 13.99, 225, "Fashion & Apparel"},
    {205, "Cool Feeling Short Sleeve T-Shirt Men", 29.99, 103, "Fashion & Apparel"},
    {301, "Ayam Brand Sardines in Tomato Sauce 155g", 5.70, 50, "Groceries & Essentials"},
    {302, "Siew Pak Choy 250g", 1.29, 5, "Groceries & Essentials"},
    {303, "Korean Original Luncheon Meat 340g", 8.16, 39, "Groceries & Essentials"},
    {304, "Purple Sweet Potato", 3.60, 26, "Groceries & Essentials"},
    {305, "Vietnam Cavendish Banana 1kg", 4.99, 14, "Groceries & Essentials"}
};

const int TOTAL_PRODUCTS = 15;
vector cart;
int cartSize = 0;

// 3. 函数声明
void showCategoryMenu(string categoryTitle, int startId, int endId);
void handlePurchase(int startId, int endId, string categoryName, string shortCatName);
void viewCartAndCheckout();

// 4. 显示分类商品列表
void showCategoryMenu(string categoryTitle, int startId, int endId) {
    cout << "\n--------------------------------------------------" << endl;
    cout << "CATEGORY: " << categoryTitle << endl;
    cout << "--------------------------------------------------" << endl;
    cout << left << setw(7) << "ID" 
         << setw(42) << "Item Name" 
         << setw(12) << "Price (RM)" 
         << "Stock" << endl;
    
    for (int i = 0; i < TOTAL_PRODUCTS; i++) {
        if (products[i].id >= startId && products[i].id <= endId) {
            cout << left << setw(7) << products[i].id 
                 << setw(42) << products[i].name 
                 << right << setw(6) << fixed << setprecision(2) << products[i].price 
                 << "        " << products[i].stock << endl;
        }
    }
    cout << "--------------------------------------------------" << endl;
}

// 5. 处理购买逻辑
void handlePurchase(int startId, int endId, string categoryName, string shortCatName) {
    int itemId, qty;
    cout << "Enter Item ID to purchase (or 0 to return): ";
    cin >> itemId;

    if (itemId == 0) return;
    
    int index = -1;
    for (int i = 0; i < TOTAL_PRODUCTS; i++) {
        if (products[i].id == itemId) {
            index = i;
            break;
        }
    }
    
    if (index != -1 && products[index].id >= startId && products[index].id <= endId) {
        cout << "Enter Quantity: ";
        cin >> qty;
        
        if (qty > 0 && qty <= products[index].stock) {
            cart[cartSize].product = products[index];
            cart[cartSize].quantity = qty;
            cartSize++;
            
            products[index].stock -= qty; // 扣减库存
            
            cout << ">> Success: Added " << qty << "x " << products[index].name << " to cart.\n";
        } else {
            cout << ">> Error: Invalid quantity or insufficient stock.\n";
        }
    } else {
        cout << ">> Error: Invalid Item ID for this category.\n";
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

// 6. 结算与购物车查看
void viewCartAndCheckout() {
    if (cartSize == 0) {
        cout << "\n[NOTICE] Your cart is empty. Add products before checking out." << endl;
        return;
    }

    double subtotal = 0.0;

    cout << "\n==================================================" << endl;
    cout << "                 CHECKOUT SUMMARY                 " << endl;
    cout << "==================================================" << endl;
    cout << "Items in Cart:" << endl;

    for (int i = 0; i < cartSize; i++) {
        double lineTotal = cart[i].product.price * cart[i].quantity;
        subtotal += lineTotal;
        cout << " - " << cart[i].quantity << "x " << left << setw(35) << cart[i].product.name
             << ": RM " << right << setw(7) << lineTotal << endl;
    }

    cout << "--------------------------------------------------" << endl;
    cout << "Current Subtotal                  : RM " << right << setw(7) << subtotal << endl;
    cout << "--------------------------------------------------" << endl;

    string promoCode;
    double voucherDiscount = 0.0;
    cout << "\nEnter Promo Code (e.g., SHOPEE10, FREESHIP, or NONE): ";
    cin >> promoCode;

    if (promoCode == "SHOPEE10") {
        voucherDiscount = subtotal * 0.10;
        cout << ">> Voucher Applied: 10% Discount (-RM " << voucherDiscount << ")" << endl;
    } else if (promoCode == "FREESHIP") {
        cout << ">> Voucher Applied: Free Shipping Voucher Activated." << endl;
    } else if (promoCode == "NONE" || promoCode == "none") {
        cout << ">> No promo code applied." << endl;
    } else {
        cout << "[NOTICE] Invalid voucher code. Proceeding with RM 0.00 discount." << endl;
    }

    double finalTotal = subtotal - voucherDiscount;
    cout << "Final Total Amount                : RM " << right << setw(7) << finalTotal << endl;
    cout << "==================================================" << endl;
}

// 7. 主程序入口
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
                showCategoryMenu("Electronics & Gadgets", 101, 105);
                handlePurchase(101, 105, "Electronics & Gadgets", "Electronics");
                break;
            case 2:
                showCategoryMenu("Fashion & Apparel", 201, 205);
                handlePurchase(201, 205, "Fashion & Apparel", "Fashion");
                break;
            case 3:
                showCategoryMenu("Groceries & Essentials", 301, 305);
                handlePurchase(301, 305, "Groceries & Essentials", "Groceries");
                break;
            case 4:
                viewCartAndCheckout();
                break;
            case 5:
                cout << "\nThank you for visiting Shopee!" << endl;
                break;
            default:
                cout << "[ERROR] Invalid option. Please choose between 1 and 5." << endl;
                break;
        }
    }
    return 0;
}