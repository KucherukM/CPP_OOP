#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Product {
public:
    int id;
    string name;
    string description;
    double price_uah;
    double price_usd;
    int quantity;
    string brand;
    string type;

    Product(int id, string name, string description, double price_uah, double price_usd, int quantity, string brand, string type)
        : id(id), name(name), description(description), price_uah(price_uah), price_usd(price_usd), quantity(quantity), brand(brand), type(type) {}

    string to_string() const {
        return std::to_string(id) + "|" + name + "|" + description + "|" + std::to_string(price_uah) + "|" +
            std::to_string(price_usd) + "|" + std::to_string(quantity) + "|" + brand + "|" + type + "\n";
    }

    static Product from_string(const string& str) {
        stringstream ss(str);
        string token;
        vector<string> tokens;

        while (getline(ss, token, '|')) {
            tokens.push_back(token);
        }

        return Product(stoi(tokens[0]), tokens[1], tokens[2], stod(tokens[3]), stod(tokens[4]), stoi(tokens[5]), tokens[6], tokens[7]);
    }
};

class ProductDatabase {
private:
    vector<Product> products;
    string filename;

    void load() {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file!" << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                products.push_back(Product::from_string(line));
            }
        }

        file.close();
    }

    void save() const {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file!" << endl;
            return;
        }

        for (const auto& product : products) {
            file << product.to_string();
        }

        file.close();
    }

public:
    ProductDatabase(const string& filename) : filename(filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            ofstream new_file(filename);
            if (!new_file.is_open()) {
                cerr << "Error creating file!" << endl;
                return;
            }

            new_file << "1|Laptop|Powerful laptop with high-resolution display|25000.0|925.9|10|Dell|Electronics\n"
                << "2|Printer|Wireless printer with scanning and copying functions|5000.0|185.2|8|HP|Electronics\n"
                << "3|Mouse|Ergonomic mouse with customizable buttons|500.0|18.5|20|Logitech|Accessories\n"
                << "4|Monitor|27-inch gaming monitor with 144Hz refresh rate|8000.0|296.3|5|Asus|Electronics\n"
                << "5|Keyboard|Mechanical keyboard with RGB backlighting|1500.0|55.6|15|Razer|Accessories\n"
                << "6|Tablet|10-inch tablet with Android OS|3000.0|111.1|12|Samsung|Electronics\n"
                << "7|Smartphone|High-end smartphone with dual-camera setup|12000.0|444.4|7|Apple|Electronics\n"
                << "8|Headphones|Noise-canceling headphones with Bluetooth connectivity|2000.0|74.1|10|Sony|Accessories\n"
                << "9|Webcam|HD webcam with built-in microphone|1000.0|37.0|15|Logitech|Accessories\n"
                << "10|Router|Dual-band Wi-Fi router with MU-MIMO technology|1500.0|55.6|8|TP-Link|Networking\n";

            new_file.close();
        }
        else {
            file.close();
        }

        load();
    }

    void viewAllData() const {
        cout << "==============================" << endl;
        cout << "          All Products        " << endl;
        cout << "==============================" << endl;

        for (const auto& product : products) {
            cout << "ID: " << product.id << endl
                << "Name: " << product.name << endl
                << "Description: " << product.description << endl
                << "Price (UAH): " << product.price_uah << endl
                << "Price (USD): " << product.price_usd << endl
                << "Quantity: " << product.quantity << endl
                << "Brand: " << product.brand << endl
                << "Type: " << product.type << endl
                << "----------------------------------" << endl;
        }

        cout << "Total Products: " << products.size() << endl;
    }

    void addProduct(const Product& product) {
        products.push_back(product);
        save();
    }

    void deleteProduct(int id) {
        products.erase(remove_if(products.begin(), products.end(), [id](const Product& product) { return product.id == id; }), products.end());
        save();
    }

    void sortProducts(const string& field) {
        if (field == "name") {
            sort(products.begin(), products.end(), [](const Product& a, const Product& b) { return a.name < b.name; });
        }
        else if (field == "price_uah") {
            sort(products.begin(), products.end(), [](const Product& a, const Product& b) { return a.price_uah < b.price_uah; });
        }
        else if (field == "price_usd") {
            sort(products.begin(), products.end(), [](const Product& a, const Product& b) { return a.price_usd < b.price_usd; });
        }
        else if (field == "quantity") {
            sort(products.begin(), products.end(), [](const Product& a, const Product& b) { return a.quantity < b.quantity; });
        }
        else if (field == "brand") {
            sort(products.begin(), products.end(), [](const Product& a, const Product& b) { return a.brand < b.brand; });
        }
        else if (field == "type") {
            sort(products.begin(), products.end(), [](const Product& a, const Product& b) { return a.type < b.type; });
        }
    }

    void searchByBrand(const string& brand) const {
        bool found = false;
        for (const auto& product : products) {
            if (product.brand == brand) {
                found = true;
                cout << "ID: " << product.id << " | Name: " << product.name << " | Description: " << product.description
                    << " | Price (UAH): " << product.price_uah << " | Price (USD): " << product.price_usd
                    << " | Quantity: " << product.quantity << " | Brand: " << product.brand << " | Type: " << product.type << endl;
            }
        }
        if (!found) {
            cout << "No products found with brand: " << brand << endl;
        }
    }

    void selectProductsByPrice(double price) const {
        bool found = false;
        for (const auto& product : products) {
            if (product.price_uah <= price) {
                found = true;
                cout << "ID: " << product.id << endl
                    << "Name: " << product.name << endl
                    << "Description: " << product.description << endl
                    << "Price (UAH): " << product.price_uah << endl
                    << "Price (USD): " << product.price_usd << endl
                    << "Quantity: " << product.quantity << endl
                    << "Brand: " << product.brand << endl
                    << "Type: " << product.type << endl
                    << "----------------------------------" << endl;
            }
        }
        if (!found) {
            cout << "No products found within specified price range." << endl;
        }
    }

    void selectLowStock() const {
        bool found = false;
        for (const auto& product : products) {
            if (product.quantity < 5) {
                found = true;
                cout << "ID: " << product.id << " | Name: " << product.name << " | Description: " << product.description
                    << " | Price (UAH): " << product.price_uah << " | Price (USD): " << product.price_usd
                    << " | Quantity: " << product.quantity << " | Brand: " << product.brand << " | Type: " << product.type << endl;
            }
        }
        if (!found) {
            cout << "No products with low stock." << endl;
        }
    }

    int getNextId() const {
        int max_id = 0;
        for (const auto& product : products) {
            if (product.id > max_id) {
                max_id = product.id;
            }
        }
        return max_id + 1;
    }
};

int main() {
    ProductDatabase db("products.txt");

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. View all data\n";
        cout << "2. Add new product\n";
        cout << "3. Delete a product\n";
        cout << "4. Sort products by field\n";
        cout << "5. Search by brand\n";
        cout << "6. Select printers by price\n";
        cout << "7. Select low stock products\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            db.viewAllData();
            break;
        case 2: {
            string name, description, brand, type;
            double price_uah, price_usd;
            int quantity;

            cout << "Enter product name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter description: ";
            getline(cin, description);
            cout << "Enter price in UAH: ";
            cin >> price_uah;
            cout << "Enter price in USD: ";
            cin >> price_usd;
            cout << "Enter quantity: ";
            cin >> quantity;
            cout << "Enter brand: ";
            cin.ignore();
            getline(cin, brand);
            cout << "Enter type: ";
            getline(cin, type);


            int new_id = db.getNextId();
            Product product(new_id, name, description, price_uah, price_usd, quantity, brand, type);
            db.addProduct(product);

            break;
        }
        case 3: {
            int id;
            cout << "Enter product ID to delete: ";
            cin >> id;
            db.deleteProduct(id);
            break;
        }
        case 4: {
            string field;
            cout << "Enter field to sort by (name, price_uah, price_usd, quantity, brand, type): ";
            cin >> field;
            db.sortProducts(field);
            break;
        }
        case 5: {
            string brand;
            cout << "Enter brand to search for: ";
            cin.ignore();
            getline(cin, brand);
            db.searchByBrand(brand);
            break;
        }
        case 6: {
            double price;
            cout << "Enter maximum price in UAH: ";
            cin >> price;
            db.selectProductsByPrice(price);
            break;
        }
        case 7:
            db.selectLowStock();
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
