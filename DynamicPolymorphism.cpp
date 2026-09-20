#include <iostream>

// Abstract base class: pure virtual accelerate() makes Car non-instantiable
// and forces every derived class to provide its own implementation.
class Car {
    public:
        bool isEngineOn; // shared state, common to every kind of car

        virtual void accelerate() = 0; // pure virtual -> makes Car abstract

        // Needed because we delete derived objects through a Car* below;
        // without this, that delete is undefined behavior (derived
        // destructor wouldn't run).
        virtual ~Car() = default;
};

class ElectricCar : public Car {
    public:
        ElectricCar() {
            this->isEngineOn = false;
        }

        // override on a virtual function is what enables dynamic dispatch:
        // the actual function called is resolved at runtime via the vtable,
        // based on the object's real type, not the pointer/reference type.
        void accelerate() override {
            std::cout << "Electric car accelerating silently\n";
        }
};

class ManualCar : public Car {
    public:
        ManualCar() {
            this->isEngineOn = false;
        }

        void accelerate() override {
            std::cout << "Manual car accelerating with engine noise\n";
        }
};

int main() {
    // Base-class pointers holding derived-class objects.
    Car* cars[] = { new ElectricCar(), new ManualCar() };

    // Same call site (`car->accelerate()`), different behavior at runtime
    // depending on the actual object type -> this is dynamic polymorphism.
    for (Car* car : cars) {
        car->accelerate();
    }

    for (Car* car : cars) {
        delete car;
    }

    return 0;
}
