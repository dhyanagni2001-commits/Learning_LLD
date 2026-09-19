#include <stdio.h>
#include <string>
#include <iostream>

// Encapsulation: bundling an object's state (character) and behavior together,
// then using access modifiers to control what's exposed outside the class
class Car{
    // private: internal state, hidden from outside access
    private:
        std::string brand;
        std::string model;
        bool isEngineOn;
        int currentSpeed;
        int currentGear;
        std::string tyre;

    // public: behavior exposed to interact with the object's state
    public:
        Car(std::string brand, std::string model) {
            this->brand = brand;
            this->model = model;
            this->isEngineOn = false;
            this->currentSpeed = 0;
            this->currentGear = 0;
            this->tyre = "MRF";
        }
    void startEngine(){
        isEngineOn = true;
        std::cout << "Engine started\n";
    }

    int getCurrentSpeed() {
        return currentSpeed;
    }
    /*Setter for tyre*/
    void tyreChange(std::string tyre) {
        this->tyre = tyre;
        std::cout << "Tyre changed to: " << this->tyre << "\n";
    }

    ~Car(){
        std::cout << "Car deleted\n";
    }


};

int main(){
    Car* car1 = new Car("Fiat", "Punto");
    car1->startEngine();
    car1->tyreChange("Bridgestone");
    delete car1;
}