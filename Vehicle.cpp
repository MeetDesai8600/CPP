#include <iostream>
#include <cstring>
using namespace std;

// ==========================
// Base Class: Vehicle
// ==========================
class Vehicle {
private:
    int vehicleID;
    char manufacturer[50];
    char model[50];
    int year;

public:
    static int totalVehicles;

    Vehicle() {
        vehicleID = 0;
        strcpy(manufacturer, "");
        strcpy(model, "");
        year = 0;
        totalVehicles++;
    }

    Vehicle(int id, const char* man, const char* mod, int yr) {
        vehicleID = id;
        strcpy(manufacturer, man);
        strcpy(model, mod);
        year = yr;
        totalVehicles++;
    }

    ~Vehicle() {
        totalVehicles--;
    }

    // Getters & Setters
    void setID(int id) { vehicleID = id; }
    int getID() const { return vehicleID; }

    void setManufacturer(const char* man) { strcpy(manufacturer, man); }
    const char* getManufacturer() const { return manufacturer; }

    void setModel(const char* mod) { strcpy(model, mod); }
    const char* getModel() const { return model; }

    void setYear(int yr) { year = yr; }
    int getYear() const { return year; }

    virtual void inputDetails() {
        cout << "Enter Vehicle ID: ";
        cin >> vehicleID;
        cin.ignore();

        cout << "Enter Manufacturer: ";
        cin.getline(manufacturer, 50);

        cout << "Enter Model: ";
        cin.getline(model, 50);

        cout << "Enter Year: ";
        cin >> year;
        cin.ignore();
    }

    virtual void displayDetails() const {
        cout << "\nVehicle ID: " << vehicleID;
        cout << "\nManufacturer: " << manufacturer;
        cout << "\nModel: " << model;
        cout << "\nYear: " << year;
    }

    virtual const char* getType() const {
        return "Vehicle";
    }
};

int Vehicle::totalVehicles = 0;


// ===============================
// Single Inheritance: Car
// ===============================
class Car : public Vehicle {
private:
    char fuelType[20];

public:
    Car() : Vehicle() {
        strcpy(fuelType, "");
    }

    void inputDetails() override {
        Vehicle::inputDetails();
        cout << "Enter Fuel Type (Petrol/Diesel/CNG): ";
        cin.getline(fuelType, 20);
    }

    void displayDetails() const override {
        Vehicle::displayDetails();
        cout << "\nFuel Type: " << fuelType;
    }

    const char* getType() const override {
        return "Car";
    }
};


// ===============================
// Multilevel Inheritance: ElectricCar
// ===============================
class ElectricCar : public Car {
private:
    int batteryCapacity;

public:
    ElectricCar() : Car() {
        batteryCapacity = 0;
    }

    void inputDetails() override {
        Car::inputDetails();
        cout << "Enter Battery Capacity (kWh): ";
        cin >> batteryCapacity;
        cin.ignore();
    }

    void displayDetails() const override {
        Car::displayDetails();
        cout << "\nBattery Capacity: " << batteryCapacity << " kWh";
    }

    const char* getType() const override {
        return "Electric Car";
    }
};


// ===================================
// Multilevel Inheritance: SportsCar
// (ElectricCar ? SportsCar)
// ===================================
class SportsCar : public ElectricCar {
private:
    int topSpeed;

public:
    SportsCar() {
        topSpeed = 0;
    }

    void inputDetails() override {
        ElectricCar::inputDetails();
        cout << "Enter Top Speed (km/h): ";
        cin >> topSpeed;
        cin.ignore();
    }

    void displayDetails() const override {
        ElectricCar::displayDetails();
        cout << "\nTop Speed: " << topSpeed << " km/h";
    }

    const char* getType() const override {
        return "Sports Car";
    }
};


// ===============================
// Base class for Multiple Inheritance: Aircraft
// ===============================
class Aircraft {
private:
    int flightRange;

public:
    Aircraft() {
        flightRange = 0;
    }

    void setFlightRange(int r) { flightRange = r; }
    int getFlightRange() const { return flightRange; }

    void inputAircraftDetails() {
        cout << "Enter Flight Range (km): ";
        cin >> flightRange;
        cin.ignore();
    }

    void displayAircraftDetails() const {
        cout << "\nFlight Range: " << flightRange << " km";
    }
};


// ===================================================
// Multiple Inheritance: FlyingCar (Car + Aircraft)
// ===================================================
class FlyingCar : public Car, public Aircraft {
public:
    FlyingCar() : Car(), Aircraft() {}

    void inputDetails() {
        Car::inputDetails();
        Aircraft::inputAircraftDetails();
    }

    void displayDetails() const {
        Car::displayDetails();
        Aircraft::displayAircraftDetails();
    }

    const char* getType() const {
        return "Flying Car";
    }
};


// =======================================
// Hierarchical Inheritance from Car
// =======================================
class Sedan : public Car {
public:
    const char* getType() const override {
        return "Sedan";
    }
};

class SUV : public Car {
public:
    const char* getType() const override {
        return "SUV";
    }
};


// ===============================
// VehicleRegistry Class
// ===============================
class VehicleRegistry {
private:
    Vehicle* registry[100]; // array of base class pointers
    int count;

public:
    VehicleRegistry() {
        count = 0;
    }

    void addVehicle(int type) {
        if (count >= 100) {
            cout << "\nRegistry Full!";
            return;
        }

        switch (type) {
            case 1: registry[count] = new Car(); break;
            case 2: registry[count] = new ElectricCar(); break;
            case 3: registry[count] = new SportsCar(); break;
            case 4: registry[count] = new Sedan(); break;
            case 5: registry[count] = new SUV(); break;
            case 6: registry[count] = new FlyingCar(); break;
            default: cout << "\nInvalid Type!"; return;
        }

        registry[count]->inputDetails();
        count++;

        cout << "\nVehicle Added Successfully!\n";
    }

    void displayAll() const {
        if (count == 0) {
            cout << "\nNo Vehicles in Registry.";
            return;
        }

        cout << "\n--------- VEHICLE LIST ---------\n";
        for (int i = 0; i < count; i++) {
            cout << "\nType: " << registry[i]->getType();
            registry[i]->displayDetails();
            cout << "\n--------------------------------\n";
        }
    }

    void searchByID(int id) const {
        for (int i = 0; i < count; i++) {
            if (registry[i]->getID() == id) {
                cout << "\nVehicle Found!";
                cout << "\nType: " << registry[i]->getType();
                registry[i]->displayDetails();
                return;
            }
        }
        cout << "\nVehicle Not Found!";
    }
};


// ===============================
// Main (Menu Driven)
// ===============================
int main() {
    VehicleRegistry vr;
    int choice;

    do {
        cout << "\n======= VEHICLE REGISTRY MENU =======";
        cout << "\n1. Add New Vehicle";
        cout << "\n2. Display All Vehicles";
        cout << "\n3. Search Vehicle by ID";
        cout << "\n4. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int type;
                cout << "\nSelect Vehicle Type:";
                cout << "\n1. Car"
                     << "\n2. Electric Car"
                     << "\n3. Sports Car"
                     << "\n4. Sedan"
                     << "\n5. SUV"
                     << "\n6. Flying Car";
                cout << "\nEnter Type: ";
                cin >> type;
                cin.ignore();

                vr.addVehicle(type);
                break;
            }

            case 2:
                vr.displayAll();
                break;

            case 3: {
                int id;
                cout << "\nEnter Vehicle ID to search: ";
                cin >> id;
                vr.searchByID(id);
                break;
            }

            case 4:
                cout << "\nExiting...";
                break;

            default:
                cout << "\nInvalid Choice!";
        }

    } while (choice != 4);
}

