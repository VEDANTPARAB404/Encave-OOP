// Chomp & Co. - Simple Restaurant Management System
// Concepts used: classes & objects, constructors, encapsulation (private/public), composition (has-a)
// Compile:  g++ resto.cpp -o resto
// Run:      ./restaurant      -> take an order, then open bill.html in your browser
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <ctime>
using namespace std;

// ---------- Class 1: one dish on the menu ----------
class MenuItem {
private:                       // encapsulation: data is hidden
    string name;
    double price;
public:
    MenuItem(string n, double p) {   // constructor
        name = n;
        price = p;
    }
    string getName() { return name; }      // getters
    double getPrice() { return price; }
};

// ---------- Class 2: a dish + how many were ordered ----------
class OrderLine {
private:
    MenuItem item;            
    int qty;
public:
    OrderLine(MenuItem i, int q) : item(i), qty(q) {}
    string getName() { return item.getName(); }
    double getPrice() { return item.getPrice(); }
    int getQty() { return qty; }
    void addQty(int q) { qty = qty + q; }
    double getAmount() { return item.getPrice() * qty; }
};

// ---------- Class 3: all the lines for one table ----------
class Order {
private:
    int tableNo;
    vector<OrderLine> lines;
public:
    Order(int t) { tableNo = t; }
    int getTableNo() { return tableNo; }
    bool isEmpty() { return lines.empty(); }
    vector<OrderLine> getLines() { return lines; }

    void addItem(MenuItem item, int qty) {
        for (int i = 0; i < lines.size(); i++) {      // same dish again? just increase qty
            if (lines[i].getName() == item.getName()) {
                lines[i].addQty(qty);
                return;
            }
        }
        lines.push_back(OrderLine(item, qty));
    }
    double getSubtotal() {
        double sum = 0;
        for (int i = 0; i < lines.size(); i++) sum += lines[i].getAmount();
        return sum;
    }
    double getGst() { return getSubtotal() * 0.05; }   // 5% GST
    double getTotal() { return getSubtotal() + getGst(); }
};

// ---------- Class 4: the restaurant and its menu ----------
class Restaurant {
private:
    vector<MenuItem> meals;
    vector<MenuItem> sides;
public:
    Restaurant() {
        meals.push_back(MenuItem("Paneer Butter Masala", 220));
        meals.push_back(MenuItem("Veg Burger", 120));
        meals.push_back(MenuItem("Margherita Pizza", 249));
        meals.push_back(MenuItem("Veg Noodles", 150));
        meals.push_back(MenuItem("Masala Dosa", 90));
        sides.push_back(MenuItem("French Fries", 70));
        sides.push_back(MenuItem("Filter Coffee", 60));
        sides.push_back(MenuItem("Cold Drink", 50));
        sides.push_back(MenuItem("Ice Cream", 80));
    }
    int getMealCount() { return meals.size(); }
    int getSideCount() { return sides.size(); }
    MenuItem getMeal(int number) { return meals[number - 1]; }
    MenuItem getSide(int number) { return sides[number - 1]; }

    void showMeals() {
        cout << "\n------ MEALS ------\n";
        for (int i = 0; i < meals.size(); i++)
            cout << i + 1 << ". " << meals[i].getName() << "  Rs." << meals[i].getPrice() << "\n";
    }

    void showSides() {
        cout << "\n------ SIDES ------\n";
        for (int i = 0; i < sides.size(); i++)
            cout << i + 1 << ". " << sides[i].getName() << "  Rs." << sides[i].getPrice() << "\n";
    }
};

// ---------- Class 5: the bill, saved as a cartoon HTML page ----------
class Bill {
private:
    int billNo;
    Order order;
public:
    Bill(int no, Order o) : billNo(no), order(o) {}

    void saveHtml(string fileName) {
        ofstream f(fileName.c_str());
        f << fixed << setprecision(2);

        time_t now = time(0);
        char date[50];
        strftime(date, 50, "%d %b %Y, %I:%M %p", localtime(&now));

        double total = order.getTotal();
        double rounded = round(total);

        f << "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"utf-8\">\n<title>Chomp & Co. Bill</title>\n"
          << "<link href=\"https://fonts.googleapis.com/css2?family=Bangers&family=Special+Elite&display=swap\" rel=\"stylesheet\">\n"
          << "<link rel=\"stylesheet\" href=\"style.css\">\n</head>\n<body>\n";

        f << "<div class=\"banner\"><span class=\"chef\">&#128104;&#8205;&#127859;</span><h1>Chomp & Co.</h1></div>\n";
        f << "<div class=\"receipt\">\n";
        f << "  <div class=\"center\"><h2>&#127836; CHOMP & CO.</h2>Doodle Street, Toonville<br>GSTIN: 27ABCDE1234F1Z5</div>\n  <hr>\n";
        f << "  <div class=\"line\"><span>Bill No: #" << setw(4) << setfill('0') << billNo << setfill(' ')
          << "</span><span>Table " << order.getTableNo() << "</span></div>\n";
        f << "  <div>" << date << "</div>\n  <hr>\n";

        f << "  <div class=\"row head\"><span>ITEM</span><span>QTY</span><span>AMT</span></div>\n";
        vector<OrderLine> lines = order.getLines();
        for (int i = 0; i < lines.size(); i++) {
            f << "  <div class=\"row\"><span>" << lines[i].getName() << "</span><span>" << lines[i].getQty()
              << "</span><span>" << lines[i].getAmount() << "</span></div>\n";
        }
        f << "  <hr>\n";
        f << "  <div class=\"line\"><span>Subtotal</span><span>" << order.getSubtotal() << "</span></div>\n";
        f << "  <div class=\"line\"><span>GST 5%</span><span>" << order.getGst() << "</span></div>\n";
        f << "  <div class=\"line\"><span>Round off</span><span>" << rounded - total << "</span></div>\n";
        f << "  <div class=\"line grand\"><span>GRAND TOTAL</span><span>Rs. " << rounded << "</span></div>\n";
        f << "  <div class=\"center\">*** THANK YOU! VISIT AGAIN ***</div>\n";

        f << "  <div class=\"bars\">";                         // fake barcode made from the bill number
        for (int i = 0; i < 36; i++)
            f << "<i style=\"width:" << 1 + (billNo * 7919 * (i + 3)) % 4 << "px\"></i>";
        f << "</div>\n</div>\n</body>\n</html>\n";
        f.close();
    }
};

// ---------- main: take an order in the console ----------
int main() {
    Restaurant restaurant;
    int tableNo;

    cout << "=== Chomp & Co. ===\nEnter table number: ";
    cin >> tableNo;
    Order order(tableNo);

    cout << "\nChoose your meals (0 when finished):\n";
    while (true) {
        restaurant.showMeals();
        int choice, qty;
        cout << "Enter meal number (0 to finish meals): ";
        if (!(cin >> choice) || choice == 0) break;
        if (choice < 1 || choice > restaurant.getMealCount()) {
            cout << "Invalid item, try again.\n";
            continue;
        }
        cout << "Quantity: ";
        cin >> qty;
        if (qty < 1) {
            cout << "Quantity must be at least 1.\n";
            continue;
        }
        order.addItem(restaurant.getMeal(choice), qty);
        cout << "Meal added!\n";
    }

    cout << "\nChoose your sides (0 when finished):\n";
    while (true) {
        restaurant.showSides();
        int choice, qty;
        cout << "Enter side number (0 to finish sides): ";
        if (!(cin >> choice) || choice == 0) break;
        if (choice < 1 || choice > restaurant.getSideCount()) {
            cout << "Invalid side, try again.\n";
            continue;
        }
        cout << "Quantity: ";
        cin >> qty;
        if (qty < 1) {
            cout << "Quantity must be at least 1.\n";
            continue;
        }
        order.addItem(restaurant.getSide(choice), qty);
        cout << "Side added!\n";
    }

    if (order.isEmpty()) {
        cout << "No items ordered.\n";
        return 0;
    }
    Bill bill(1, order);
    bill.saveHtml("bill.html");
    cout << "\nTotal: Rs." << order.getTotal() << "\nBill saved to bill.html - open it in your browser!\n";
    return 0;
}