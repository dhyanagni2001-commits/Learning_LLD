#include <stdio.h>
#include <iostream>



class manualCar{
    public:
        int speed;
        int accelerate;
    manualCar(int speed){
        this->speed = speed;
    }
    public:
        // Function overloading: same method name, different parameter lists (compile-time/static polymorphism)
        void accelerate() {
            accelerate += 2; 
            std::cout << "Manual car accelerating with engine noise\n";
        }

        void accelerate(int speed) {
            accelerate += speed;
            std::cout << "Manual car accelerating with engine noise at speed: " << this->speed << "\n";
        }
};

int main(){
    manualCar* car1 = new manualCar(10);
    car1->accelerate();
    car1->accelerate(20); // This line will cause a compilation error because the base class pointer cannot access the overloaded method in the derived class.

    delete car1;
}