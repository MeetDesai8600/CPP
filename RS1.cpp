#include <iostream>
#include <cstring>
using namespace std;

//Train Class

class Train {
private:
    int trainNumber;
    char trainName[50];
    char source[50];
    char destination[50];
    char trainTime[10];
//Static member to track total trains
    static int trainCount;

public:
	//Default Constructor
    Train() {
        trainNumber = 0;
        strcpy(trainName, "");
        strcpy(source, "");
        strcpy(destination, "");
        strcpy(trainTime, "");
        trainCount++;
    }
    //Parameterized Constructor
	Train(int number, const char* name, const char* src, const char* dest, const char* time){
	trainNumber=number;
	strcpy(trainName,name);
	strcpy(source,src);
	strcpy(destination, dest);
	strcpy(trainTime, time);
	trainCount++;
	}
    ~Train() {
        trainCount--;
    }

    void setTrainNo(int no) { trainNumber = no; }
    int getTrainNo() const { return trainNumber; }

    void setTrainName(const char name[]) { strcpy(trainName, name); }
    const char* getTrainName() const { return trainName; }

    void setSource(const char src[]) { strcpy(source, src); }
    const char* getSource() const { return source; }

    void setDestination(const char dest[]) { strcpy(destination, dest); }
    const char* getDestination() const { return destination; }

    void setTrainTime(const char time[]) { strcpy(trainTime, time); }
    const char* getTrainTime() const { return trainTime; }

    void inputTrainDetails() {
        cout << "Enter Train Number: ";
        cin >> trainNumber;
        cin.ignore();

        cout << "Enter Train Name: ";
        cin.getline(trainName, 50);

        cout << "Enter Source: ";
        cin.getline(source, 50);

        cout << "Enter Destination: ";
        cin.getline(destination, 50);

        cout << "Enter Train Time: ";
        cin.getline(trainTime, 10);
    }

    void displayTrainDetails() const {
        cout << "\nTrain Details:\n";
        cout << "Train Number: " << trainNumber << endl;
        cout << "Train Name: " << trainName << endl;
        cout << "Source: " << source << endl;
        cout << "Destination: " << destination << endl;
        cout << "Train Time: " << trainTime << endl;
    }

    static int getTrainCount() {
        return trainCount;
    }
};

int Train::trainCount = 0;
//Railway System Class Defination
class RailwaySystem{
	private:
		Train trains[100];
		int totalTrains;
	public:
		RailwaySystem(){
			totalTrains=0;
		}
		//Add a new train
		void addTrain(){
			if(totalTrains<100){
				cout<<"\nEnter details for Train"<<totalTrains+1<<":\n";
				trains[totalTrains].inputTrainDetails();
				totalTrains++;
				cout<<"\nTrain record added successfully!\n";
			}else{
				cout<<"\nTrain list is full. Cannot add more records.\n";
			}
		}
		 // Display all trains
    void displayAllTrains() const {
        if (totalTrains == 0) {
            cout << "\nNo train records found.\n";
        } else {
            cout << "\n--- All Train Records ---\n";
            for (int i = 0; i < totalTrains; i++) {
                cout << "\nRecord " << i + 1 << ":";
                trains[i].displayTrainDetails();
            }
        }
    }
    // Search by Train Number
    void searchTrainByNumber(int number) const {
        bool found = false;
        for (int i = 0; i < totalTrains; i++) {
            if (trains[i].getTrainNo() == number) {
                cout << "\nTrain found:\n";
                trains[i].displayTrainDetails();
                found = true;
                break;
            }
        }
        if (!found)
            cout << "\nTrain with number " << number << " not found.\n";
    }
      // Get total number of trains (from Train class)
    void displayTrainCount() const {
        cout << "\nTotal Train Objects Created: " << Train::getTrainCount() << endl;
    }
};	

int main() {
   RailwaySystem system;
    int choice;

    cout << "===== Railway Management System =====\n";

    // Initially enter at least 3 trains
    cout << "\nEnter details for at least 3 trains:\n";
    for (int i = 0; i < 3; i++) {
        system.addTrain();
    }

    do {
        cout << "\n===== MENU =====";
        cout << "\n1. Add New Train";
        cout << "\n2. Display All Trains";
        cout << "\n3. Search Train by Number";
        cout << "\n4. Display Train Count";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                system.addTrain();
                break;
            case 2:
                system.displayAllTrains();
                break;
            case 3: {
                int num;
                cout << "\nEnter Train Number to Search: ";
                cin >> num;
                system.searchTrainByNumber(num);
                break;
            }
            case 4:
                system.displayTrainCount();
                break;
            case 5:
                cout << "\nExiting program...\n";
                break;
            default:
                cout << "\nInvalid choice! Try again.\n";
        }

    } while (choice != 5);


}

