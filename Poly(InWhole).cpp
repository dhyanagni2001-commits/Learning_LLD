#include <stdio.h>
#include <string>
#include <iostream>

class Car{
    protected:
        std::string brand;
        std::string model;
        bool isEngineOn;
        int currentSpeed;
    public:
        virtual void acclerate() = 0;
        virtual void acclerate(int value) = 0;

        ~Car(){
            std::cout << "Car deleted\n";
        }
};

class manualCar: public Car{
    private:
        int fuel;
    public:
        manualCar(int fuel) {
            this->currentSpeed = 0;
            this->isEngineOn = false;
            this->fuel = fuel;
        }

        void acclerate() override {
            if (isEngineOn == true) {
                currentSpeed = currentSpeed + 5;
                std::cout << "Current speed: " << currentSpeed << "\n";
            } else {
                std::cout << "Engine is off\n";
            }
        }

        void acclerate(int fuel) override{
            if (isEngineOn == true) {
                currentSpeed = currentSpeed + 5;
                std::cout << "Current speed: " << currentSpeed << "\n";
                std::cout << "Fuel consumed: " << fuel << "\n";
            } else {
                std::cout << "Engine is off\n";
            }
        }
};

class electricCar: public Car{
    private:
        int battery;
    public:
        electricCar(int battery) {
            this->currentSpeed = 0;
            this->isEngineOn = false;
            this->battery = battery;
        }

        void acclerate() override {
            if (isEngineOn == true) {
                currentSpeed = currentSpeed + 5;
                std::cout << "Current speed: " << currentSpeed << "\n";
            } else {
                std::cout << "Engine is off\n";
            }
        }

        void acclerate(int battery) override {
            if (isEngineOn == true) {
                currentSpeed = currentSpeed + 5;
                std::cout << "Current speed: " << currentSpeed << "\n";
                std::cout << "Battery consumed: " << battery << "\n";
            } else {
                std::cout << "Engine is off\n";
            }
        }
};

int main(){
    Car* car1 = new manualCar(10);
    car1->acclerate();
    car1->acclerate(5); 
    Car* car2 = new electricCar(20);
    car2->acclerate();
    car2->acclerate(10);
    delete car1;
    delete car2;
}
