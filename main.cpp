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

// Customer active cart
vector<CartItem> cart;

// Function declarations
void displayCategoryCatalog(const string& categoryName);
void handleShopping(const string& categoryName);
void viewCartAndCheckout();
int findProductIndexById(int id);

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
                handleShopping("Electronics & Gadgets");
                break;
            case 2:
                handleShopping("Fashion & Apparel");
                break;
            case 3:
                handleShopping("Groceries & Essentials");
                break;
            case 4:
                viewCartAndCheckout();
                break;
            case 5:
                cout << "\nThank you for visiting Shopee CLI Store. Goodbye!" << endl;
                break;
            default:
                cout << "[ERROR] Invalid option. Please choose between 1 and 5." << endl;
                break;
        }
    }
    return 0;
}

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
    {301, "Ayam Brand Sardeines in Tomato Sauce 155g", 5.70, 50, "Groceries & Essentials},
    {302, "Siew Pak Choy 250g", 1.29, 5, "Groceries & Essentials},
    {303, "Korean Original Luncheon Meat 340g", 8.16, 39, "Groceries & Essentials"},
    {304, "Purple Sweet Potato", 3.60, 26, "Groceries & Essentials"},
    {305, "Vietnam Cavendish Banana 1kg", 4.99, 14, "Groceries & Essentials"}
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

// Review cart, apply promo codes, choose payment method, and render invoice
void viewCartAndCheckout() {
    if (cart.empty()) {
        cout << "\n[NOTICE] Your cart is empty. Add products before checking out." << endl;
        return;
    }

    double subtotal = 0.0;

    cout << "\n==================================================" << endl;
    cout << "                 CHECKOUT SUMMARY                 " << endl;
    cout << "==================================================" << endl;
    cout << "Items in Cart:" << endl;

    for (const auto& item : cart) {
        double lineTotal = item.product.price * item.quantity;
        subtotal += lineTotal;
        cout << " - " << item.quantity << "x " << left << setw(32) << item.product.name
             << ": RM " << right << setw(7) << lineTotal << endl;
    }

    cout << "--------------------------------------------------" << endl;
    cout << "Current Subtotal                  : RM " << right << setw(7) << subtotal << endl;
    cout << "--------------------------------------------------" << endl;

    // Promo code entry
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
        promoCode = "INVALID";
    }

// Shipping fee rule
    double shippingFee = 5.00;
    string shippingRemark = "Standard delivery";

    if (subtotal >= 40.00 || promoCode == "FREESHIP") {
        shippingFee = 0.00;
        shippingRemark = (promoCode == "FREESHIP") ? "Voucher free shipping" : "Free shipping >= RM40";
    }

    // Payment method selection
    int paymentChoice = 0;
    double paymentAdjustment = 0.0;
    string paymentMethodName = "";

    while (paymentChoice != 1 && paymentChoice != 2) {
        cout << "\nSelect Payment Method:" << endl;
        cout << " 1. ShopeePay (RM 3.00 Instant Rebate)" << endl;
        cout << " 2. Cash on Delivery (COD) (+RM 2.00 Handling Fee)" << endl;
        cout << "Enter choice (1-2): ";

        if (!(cin >> paymentChoice)) {
            cout << "[ERROR] Invalid input. Enter 1 or 2." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (paymentChoice == 1) {
            paymentAdjustment = -3.00;
            paymentMethodName = "ShopeePay (-RM 3.00)";
            cout << ">> Payment Selected: ShopeePay (RM 3.00 Rebate applied)" << endl;
        } else if (paymentChoice == 2) {
            paymentAdjustment = 2.00;
            paymentMethodName = "Cash on Delivery (+RM 2.00)";
            cout << ">> Payment Selected: COD (RM 2.00 handling surcharge applied)" << endl;
        } else {
            cout << "[ERROR] Invalid option. Please select 1 or 2." << endl;
        }
    }

// Final total calculation
    double grandTotal = subtotal + shippingFee - voucherDiscount + paymentAdjustment;
    if (grandTotal < 0.0) {
        grandTotal = 0.0;
    }

    double totalSavings = voucherDiscount + (5.00 - shippingFee) + (paymentAdjustment < 0 ? (-paymentAdjustment) : 0.0);

    cout << "\nProcessing order..." << endl;

    // Final official invoice
    cout << "\n==================================================================" << endl;
    cout << "                     SHOPEE OFFICIAL INVOICE                      " << endl;
    cout << "==================================================================" << endl;
    cout << "Purchased Items:" << endl;

    for (const auto& item : cart) {
        double lineTotal = item.product.price * item.quantity;
        cout << "  - " << item.quantity << "x " << left << setw(38) << item.product.name
             << ": RM " << right << setw(7) << lineTotal << endl;
    }

    cout << "------------------------------------------------------------------" << endl;
    cout << left << setw(48) << "Subtotal"
         << ": RM " << right << setw(7) << subtotal << endl;
    cout << left << setw(48) << ("Shipping Fee (" + shippingRemark + ")")
         << ": RM " << right << setw(7) << shippingFee << endl;
    cout << left << setw(48) << ("Voucher Discount [" + promoCode + "]")
         << ": -RM" << right << setw(6) << voucherDiscount << endl;
    cout << left << setw(48) << ("Payment Adjustment: " + paymentMethodName)
         << ": " << (paymentAdjustment < 0 ? "-RM" : " RM")
         << right << setw(6) << (paymentAdjustment < 0 ? -paymentAdjustment : paymentAdjustment) << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << left << setw(48) << "TOTAL AMOUNT PAYABLE"
         << ": RM " << right << setw(7) << grandTotal << endl;
    cout << left << setw(48) << "TOTAL AMOUNT SAVED"
         << ": RM " << right << setw(7) << totalSavings << endl;
    cout << "==================================================================" << endl;
    cout << "Thank you for shopping with Shopee!" << endl;

    // Reset cart and terminate session
    cart.clear();
    exit(0);
}