#include<stdio.h>
#include<string>
#include<iostream>
#include<vector>

// Single Responsibility Principle (SRP):
// Each class should have only ONE job / one reason to change.

// Job: represent a single product (just data).
class product{
    public:
        std::string name;
        int price;
        product(std::string name, int price){
            this->name = name;   // this->name = member, name = parameter
            this->price = price;
        }
};

// Job: manage the cart (add products, calculate total).
// It does NOT know anything about databases.
class checkout{
    private:
    std::vector<product*> products;   // addresses of products in the cart

    public:

        void addProduct(product* p){
            products.push_back(p);
        }

        const std::vector<product*> getProducts(){
            return products;
        }

        double calculateTotal(){
            double total=0;
            for(int i=0;i<products.size();i++){
                total += products[i]->price;
            }
            return total;
        }


};

// Job: save checkout data to the database.
// Kept separate from checkout so DB changes don't affect cart logic (SRP).
class addDataToDB {
    private:
        // Pointer to an EXISTING checkout (not a new cart).
        // checkout = type it points to, * = stores an address, c = variable name.
        // Private so outside code can't change which cart we point to.
        checkout* c;

    public:
        // Constructor: receives the cart from outside (dependency injection).
        // Stores its address so every method of this class can use the same cart.
        addDataToDB(checkout* c){
            this->c = c;   // this->c = member pointer, c = parameter
        }

        void saveToDb(){
            // Simulate saving to database
            std::cout << "Saving products to database..." << std::endl;
            // Reach the real cart through the stored pointer
            for (const auto& product : c->getProducts()) {
                std::cout << "Product: " << product->name << ", Price: " << product->price << std::endl;
            }
        }
};

int main(){
    checkout c;                                    // the real cart
    product* p1 = new product("Product 1", 100);
    product* p2 = new product("Product 2", 200);
    c.addProduct(p1);
    c.addProduct(p2);
    std::cout<<"Total: "<<c.calculateTotal()<<std::endl;
    return 0;
}
