#include <stdio.h>
#include <string>
#include <iostream>

using std::cout;
using std::string;

// Car is the "base class" (also called parent class).
// Any class that inherits from Car will automatically get all of its
// protected/public members (variables and functions) without rewriting them.
class Car {
    // "protected" means: these variables are hidden from outside code (like private),
    // but child classes (like manualCar, SportsCar) ARE allowed to use them directly.
    // If this was "private" instead, child classes could not access them.
    protected:
        string brand;
        string model;
        bool isEngineOn;
        int currentSpeed;


    public:
        Car(string brand, string model) {
            this->brand = brand;
            this->model = model;
            this->isEngineOn = false;
            this->currentSpeed = 0;                 
            
        }

        void startEngine(){
            isEngineOn = true;
            cout << "Engine started\n";
        }

        
        void accelerate() {
            if (isEngineOn == true) {
                currentSpeed = currentSpeed + 5;
                cout << "Current speed: " << currentSpeed << "\n";
            } else {
                cout << "Engine is off\n";
            }
        }

        void brake() {
            if (currentSpeed == 0) {
                return;
            }

            if (isEngineOn == true) {
                currentSpeed = currentSpeed - 5;
                cout << "Current speed: " << currentSpeed << "\n";
            } else {
                cout << "Engine is off\n";
            }
        }


        void stopEngine() {
            currentSpeed = 0;
            isEngineOn = false;

            cout << "Engine stopped\n";
        }

    };

    // ": public Car" is the inheritance part.
    // It means manualCar IS-A Car, and it automatically gets brand, model,
    // isEngineOn, currentSpeed, and the functions startEngine(), accelerate(),
    // brake(), stopEngine() from Car — without copying that code here.
    class manualCar : public Car {
        public:
            int currentGear;

        // A child class must build its parent part first.
        // ": Car(brand, model)" calls Car's constructor to set up the
        // inherited variables (brand, model, isEngineOn, currentSpeed)
        // before manualCar sets up its own new variable (currentGear).
        manualCar(string brand, string model) : Car(brand, model) {
            this->currentGear = 0;
        }

        public:
            // gearShift() is a NEW function, not present in Car.
            // It can freely use isEngineOn because that variable was
            // inherited from Car (as "protected").
            void gearShift(int gear) {
                if (isEngineOn == true) {
                    currentGear = gear;
                    cout << "Car is in gear: " << currentGear << "\n";
                } else {
                    cout << "Engine is off\n";
                }
            }
           
    };

    // ": public manualCar" means SportsCar inherits from manualCar.
    // Since manualCar itself inherited from Car, SportsCar gets everything
    // from BOTH classes. This is called multi-level inheritance:
    //      Car  ->  manualCar  ->  SportsCar
    // (grandparent -> parent -> child)
    class SportsCar : public manualCar {
        private:
            int gearShiftTotal;

        public:
            // Same idea as before: build the parent (manualCar) part first
            // by calling manualCar(brand, model), which in turn calls Car(...).
            // So one line here triggers construction of the whole chain.
            // "gear" is a new parameter so the caller can set the starting
            // gear (currentGear, inherited from manualCar) at construction time.
            SportsCar(int gear) : manualCar(brand, model) {
                this->gearShiftTotal = 0;
                this->currentGear = gear;
            }

            // This gearShift() has the SAME name and parameters as the one
            // in manualCar, so it "overrides" (replaces) it for SportsCar objects.
            // "manualCar::gearShift(gear)" means: still run the parent's
            // original version first, then add extra behaviour (counting shifts)
            // on top of it, instead of rewriting the whole logic again.
            void gearShift(int gear) {
                manualCar::gearShift(gear);
                gearShiftTotal++;
                cout << "Gear shift count: " << gearShiftTotal << "\n";
            }
    };

    int main() {
        string brand = "Fiat";
        string model = "Punto";

        // car1 is a manualCar object. Even though startEngine(), accelerate(),
        // brake(), stopEngine() are written only in Car, manualCar inherited
        // them, so we can call them directly on car1.
        manualCar* car1 = new manualCar(brand, model);

        int startingGear;
        cout << "Enter starting gear for sports car: ";
        std::cin >> startingGear;

        // sportsCar1 is a SportsCar object. It has access to functions from
        // Car (startEngine, accelerate, brake, stopEngine) AND from manualCar,
        // because of the inheritance chain Car -> manualCar -> SportsCar.
        SportsCar* sportsCar1 = new SportsCar(startingGear);

        car1->startEngine();
        car1->accelerate();
        car1->brake();
        car1->stopEngine();

        sportsCar1->startEngine();
        // This calls SportsCar's own gearShift() (the overridden one),
        // which itself calls manualCar's gearShift() internally.
        sportsCar1->gearShift(1);
        sportsCar1->accelerate();
        sportsCar1->gearShift(2);
        sportsCar1->brake();
        sportsCar1->stopEngine();
        
        delete car1;
        delete sportsCar1;
    }
