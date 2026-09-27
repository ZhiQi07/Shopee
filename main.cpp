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
    cout << "                   WELCOME TO SHOPEE              " << endl;
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

vector<Product> inventory = {
    // Electronics & Gadgets
    {101, "Wireless Bluetooth Earbuds", "Electronics & Gadgets", 45.00, 15},
    {102, "Fast Charging USB-C Cable", "Electronics & Gadgets", 8.00, 50},
    {103, "10000mAh Powerbank", "Electronics & Gadgets", 35.00, 20},
    {104, "High Speed Handheld Fan", "Electronics & Gadgets", 53.35, 121},
    {105, "Foldable Bluetooth Headphones", "Electronics & Gadgets", 33.00, 38},

    // Fashion & Apparel
    {201, "Oversized Cotton T-Shirt", "Fashion & Apparel", 25.00, 40},
    {202, "Denim Jacket", "Fashion & Apparel", 68.00, 10},
    {203, "Canvas Sneakers", "Fashion & Apparel", 55.00, 15},
    {204, "Women Fitness Leggings", "Fashion & Apparel", 13.99, 225},
    {205, "Cool Short Sleeve T-Shirt", "Fashion & Apparel", 29.99, 103},

    // Groceries & Essentials
    {301, "Ayam Brand Sardines 155g", "Groceries & Essentials", 5.70, 50},
    {302, "Siew Pak Choy 250g", "Groceries & Essentials", 1.29, 5},
    {303, "Korean Luncheon Meat 340g", "Groceries & Essentials", 8.16, 39},
    {304, "Purple Sweet Potato 1kg", "Groceries & Essentials", 3.60, 26},
    {305, "Cavendish Banana 1kg", "Groceries & Essentials", 4.99, 14}
};

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