#include <string>
#include <iostream>

using std::cout;
using std::string;

/*
    ABSTRACT CLASS / INTERFACE

    This class defines WHAT every Car must be able to do.
    It does not define HOW a specific car performs those actions.

    Because it contains pure virtual functions (= 0),
    we cannot directly create a Car object.
*/
class Car {
public:
    // Pure virtual methods: child classes must implement them.
    virtual void startEngine() = 0;
    virtual void gearShift(int gear) = 0;
    virtual void accelerate() = 0;
    virtual void brake() = 0;
    virtual void stopEngine() = 0;

    /*
        DESTRUCTOR

        This runs when a Car object is deleted.

        "virtual" ensures that when we delete an object using
        a Car pointer, the child destructor runs first, followed
        by this Car destructor.
    */
    virtual ~Car() {
        cout << "Car deleted completely\n";
    }
};


/*
    SportsCar inherits from the Car interface.

    Therefore, SportsCar must implement all the pure virtual
    methods declared inside Car.
*/
class SportsCar : public Car {
public:
    string brand;
    string model;
    bool isEngineOn;
    int currentSpeed;
    int currentGear;

    /*
        CONSTRUCTOR

        A constructor:
        1. Has the same name as the class.
        2. Does not have a return type.
        3. Runs automatically when an object is created.
        4. Initializes the object's variables.
    */
    SportsCar(string b, string m) {

        /*
            "this" is a pointer to the current object.

            this->brand means:
            "the brand variable belonging to this SportsCar object."

            Here, using this-> is optional because the names are
            different: brand and b.
        */
        this->brand = b;
        this->model = m;

        // Initial values of this SportsCar object.
        this->isEngineOn = false;
        this->currentSpeed = 5;
        this->currentGear = 0;
    }

    /*
        "override" tells the compiler that this method is
        implementing a virtual method from the Car interface.
    */
    void startEngine() override {
        isEngineOn = true;

        cout << "Engine started\n";
        cout << brand << " : " << model << "\n";
    }

    void gearShift(int gear) override {
        if (isEngineOn == true) {
            currentGear = gear;
            cout << "Car is in gear: " << currentGear << "\n";
        } else {
            cout << "Engine is off\n";
        }
    }

    void accelerate() override {
        if (isEngineOn == true) {
            currentSpeed = currentSpeed + 5;
            cout << "Current speed: " << currentSpeed << "\n";
        } else {
            cout << "Engine is off\n";
        }
    }

    void brake() override {
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

    void stopEngine() override {
        currentSpeed = 0;
        currentGear = 0;
        isEngineOn = false;

        cout << "Engine stopped\n";
    }

    /*
        SPORTSCAR DESTRUCTOR

        This runs first when a SportsCar object is deleted.
        After this, the Car destructor runs automatically.
    */
    ~SportsCar() override {
        cout << "SportsCar deleted\n";
    }
};


int main() {
    string brand = "Fiat";
    string model = "Punto";

    /*
        "new SportsCar" creates a SportsCar object in dynamic memory.

        car1 is a Car pointer, but the actual object is a SportsCar.
        This is possible because SportsCar inherits from Car.
    */
    Car* car1 = new SportsCar(brand, model);

    car1->startEngine();
    car1->accelerate();
    car1->accelerate();
    car1->gearShift(1);
    car1->accelerate();
    car1->accelerate();
    car1->gearShift(2);
    car1->brake();
    car1->stopEngine();

    /*
        Deletes the object created using "new".

        Because Car's destructor is virtual, the order is:

        1. SportsCar destructor
        2. Car destructor
        3. Object memory is released
    */
    delete car1;

    return 0;
}