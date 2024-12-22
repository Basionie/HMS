#include <iostream>
#include <vector>
#include <string>
using namespace std;
// ANSI Colors
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
// Global Variable
bool loggedIn = false;
bool superAdmin = false;
//validation
double getvaliddouble() {
    double userInput;
    // Loop until a valid double is entered
    while (true) {
        cin >> userInput;
     // Check if the input is a double
        if (cin.fail()) {
            // Clear the error flag and ignore the invalid input
            cin.clear();  // Clear the error flag
            cin.ignore(1000, '\n');  // Ignore the invalid input

            cout << "That's not a valid double. Please try again." << endl;
        } else {
            // If input is valid, break the loop
            break;
        }
    }

    return userInput;  // Return the valid double
}
int getvalidinteger() {
    int userInput;

    // Loop until a valid integer is entered
    while (true) {
        //cout << "Please enter an integer: ";
        cin >> userInput;

        // Check if the input is an integer
        if (cin.fail()) {
            // Clear the error flag and ignore the invalid input
            cin.clear();  // Clear the error flag
            cin.ignore(1000, '\n');  // Ignore the invalid input

            cout << "That's not a valid integer. Please try again." << endl;
        } else {
            // If input is valid, break the loop
            break;
        }
    }

    return userInput;  // Return the valid integer
}

///////////////////classes////////////////////////
class Customer 
{
    static int lastID;
    int customerID;
    string customerName;
    string customerAddress;
    string customerPhone;
    string customerEmail;
public:
    // Constructor
    Customer()
    {
        customerID = ++lastID;
        cout << "Customer ID: " << customerID <<endl;
        cin.ignore();
        cout << "Customer Name: ";
        getline(cin,customerName);
        cout << "Customer Address: ";
        getline(cin,customerAddress);
        cout << "Customer Phone: ";
        cin >> customerPhone;
        cout << "Customer Email: ";
        cin >> customerEmail;
    }

    string getName()
    {
        return customerName;
    }

    int getID()
    {
        return customerID;
    }
    void getDetails()
    {
        cout << "Customer ID: "<< customerID <<endl;
        cout << "Customer Name: "<< customerName<<endl;
        cout << "Customer Address: "<< customerAddress<<endl;
        cout << "Customer Phone: "<< customerPhone<<endl;
        cout << "Customer Email: "<< customerEmail<<endl;
    }

    // To Show as a List
    void getDetailsFlat()
    {
        cout <<CYAN<< "\n["<<(customerID < 10 ? "00" : (customerID < 100 ? "0" : ""))<<customerID<< "] "<<RESET;
        cout <<BOLD<<"NAME\t: "<<RESET << customerName <<"\n      "<<BOLD<<"ADDRESS\t: "<<RESET<< customerAddress ;
        cout <<"\n      "<<BOLD<<"PHONE\t: "<<RESET<< customerPhone<<"\n      "<<BOLD<<"EMAIL\t: "<<RESET<< customerEmail;
        cout <<endl;
    }
};

class Admin
{
    string username;
    string password;
    bool superAdmin;
public:
    // Constructor
    Admin(bool super = false)
    {
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
        superAdmin = super;
    }
    string getUsername()
    {
        return username;
    }
    string getPassword()
    {
        return password;
    }
    bool isSuper(){
        return superAdmin;
    }
};



class Food {
public:
    string foodName;
    double foodPrice;
    string mealType; // "Breakfast", "Lunch", or "Dinner"

    Food(string name, double price, string type) 
        : foodName(name), foodPrice(price), mealType(type) {}

    void getDetails() const {
        cout << foodName << " - $" << foodPrice << endl;
    }
};


class Room
{
    string roomNumber;
    bool isBooked;
    int customerID;
    double roomPrice;
    int roomFloor;
    int daysBooked;  // New variable to store the number of days
public:
    // Constructor
    Room(string number,double price,int floor)
    {
        roomNumber = number;
        isBooked = false;
        customerID = -1;
        roomPrice = price;
        roomFloor = floor;
        daysBooked = 0;  // Default to 0 days initially
    }

    string getRoomNumber()
    {
        return roomNumber;
    }

    int getCustomerID()
    {
        return customerID;
    }

    double getPrice()
    {
        return roomPrice;
    }

    void setPrice(double price)
    {
        roomPrice = price;
    }

    bool getIsBooked()
    {
        return isBooked;
    }

    void book(int customer, int days)
    {
        isBooked = true;
        customerID = customer;
        daysBooked = days;  // Store the number of days
    }

    void vacate()
    {
        isBooked = false;
        customerID = -1;
        daysBooked = 0;  // Reset days when the room is vacated
    }

    void getDetails()
    {
        cout << "Room No: "<< roomNumber << endl;
        cout << "Floor No: "<< roomFloor << endl;
        cout << "Price ($): "<< roomPrice << endl;
        cout << "Available: ";
        if (isBooked)
        {
            cout << RED << "No" << RESET << endl;
            cout << "Booked for " << daysBooked << " days" << endl;  // Display the number of days booked
            cout << "Total Bill: $" << roomPrice * daysBooked << endl;  // Display the total bill
        }
        else
        {
            cout << GREEN << "Yes" << RESET << endl;
        }
    }

    int getDaysBooked()
    {
        return daysBooked;
    }

    double getTotalBill()
    {
        return roomPrice * daysBooked;
    }
};




int Customer::lastID = 0;

// To get customer By ID
Customer* checkCustomer(vector<Customer>& customers, int id)
{
    for (int i =0;i < customers.size();i++)
    {
        if (customers[i].getID() == id)
        {
            customers[i].getDetails();
            return &customers[i];
        }
    }
    return nullptr;
}

// Get the list of Customers
void viewAllCustomers(vector<Customer>& customers)
{
    if(customers.size()==0){
        cout << "\nNo Registered Customers Yet!";
    } else {
        for (int i = 0; i < customers.size(); i++)
        {
            customers[i].getDetailsFlat();
        }
    }
}

   
class Guest 
{
public:
    int customerID;
    string name;
    double totalBill;
    int daysRemaining;
    bool isRoomBooked;
    string roomNumber;
    vector<Food> orderedFood;

    Guest(int id, string n) : customerID(id), name(n), totalBill(0), daysRemaining(0), isRoomBooked(false) {}

    void addFoodToOrder(const Food& food)
    {
        orderedFood.push_back(food);
        totalBill += food.foodPrice;
    }
        void getDetails()
    {
        cout << "Guest ID: "<< customerID <<endl;
        cout << "Gest Name: "<< name<<endl;
        cout << "Guest room number: "<< roomNumber<<endl;
        cout << "Guest days remaining: "<< daysRemaining<<endl;
        cout << "Guests totalBill "<< totalBill<<endl;
    }



void viewFoodMenu(const vector<Food>& menu, const string& mealType) {
    cout << mealType << " Menu\n=================\n";
    bool found = false;

    for (const Food& food : menu) { // Explicitly specifying the type as Food
        if (food.mealType == mealType) {
            food.getDetails();
            found = true;
        }
    }

    if (!found) {
        cout << "No items available for " << mealType << "." << endl;
    }
}



    void viewTotalBill()
    {
        cout << "Total Bill: $" << totalBill << endl;
        cout << "Room Price for " << daysRemaining << " nights: $" << (daysRemaining * 100) << endl;  // Assuming room price is $100 per night
        cout << "Total: $" << totalBill + (daysRemaining * 100) << endl;
    }

    void extendStay(int days)
    {
        daysRemaining += days;
        totalBill += 100 * days;  // Add cost of room for extended days
        cout << "Stay extended by " << days << " days. New total bill: $" << totalBill << endl;
    }
    
};


class Hotel
{
    string hotelName;
    vector<Room> rooms;
    int totalFloors;
    int eachFloorRoomCount;
public:
    // Constructor
        vector<Food> foodMenu;
      // Constructor for Hotel class
   Hotel(string name, int floors, int roomEach, double price) {
    hotelName = name;
    totalFloors = floors;
    eachFloorRoomCount = roomEach;

    // Populate foodMenu
     foodMenu.push_back(Food("Pancakes", 5.99, "Breakfast"));
    foodMenu.push_back(Food("Omelette", 4.99, "Breakfast"));
    foodMenu.push_back(Food("Burger", 8.99, "Lunch"));
    foodMenu.push_back(Food("Pizza", 10.50, "Lunch"));
    foodMenu.push_back(Food("Salad", 6.99, "Dinner"));
    foodMenu.push_back(Food("Steak", 15.99, "Dinner"));


    // Room initialization logic (already in your code)
    char floorChar = 'A';
    int floorExt = 1;
    for (int floor = 1; floor <= totalFloors; ++floor) {
        for (int roomNum = 1; roomNum <= eachFloorRoomCount; ++roomNum) {
            string roomNumber = floorChar + to_string(floorExt)
                + (roomNum < 10 ? "00" : (roomNum < 100 ? "0" : "")) + to_string(roomNum);
            rooms.push_back(Room(roomNumber, price, floor));
        }
        if (floorChar == 'Z') {
            floorChar = 'A';
            floorExt++;
        } else {
            floorChar++;
        }
    }
}

    
    
    
    // Check if a room is available
    bool isRoomAvailable(string roomNumber)
    {
        for (auto& room : rooms)
        {
            if (room.getRoomNumber() == roomNumber && !room.getIsBooked())
                return true;
        }
        return false;
    }

    // Extend stay for the guest
    void extendStay(string roomNumber, int days)
    {
        for (auto& room : rooms)
        {
            if (room.getRoomNumber() == roomNumber && room.getIsBooked())
            {
                room.book(room.getCustomerID(), room.getDaysBooked() + days); // Extend the stay
                cout << "Stay extended for " << days << " more days." << endl;
            }
        }
    }

    // Change room for the guest (if possible)
    bool changeRoom(Guest& guest, string newRoomNumber)
    {
        if (isRoomAvailable(newRoomNumber))
        {
            guest.roomNumber = newRoomNumber;
            cout << "Room changed to " << newRoomNumber << endl;
            return true;
        }
        else
        {
            cout << "Room not available!" << endl;
            return false;
        }
    }
  

    
	// Book a room for a customer
	bool bookRoom(string roomNumber, Customer& customer,const string& roomType)
	{
	    int days;
	    for (int i = 0; i < rooms.size(); i++)
	    {
	        if (rooms[i].getRoomNumber() == roomNumber && !rooms[i].getIsBooked())
	        {
	            cout << "Enter number of days for stay: ";
	            days = getvalidinteger();  // Get number of days from the admin
	            rooms[i].book(customer.getID(), days);  // Book the room for the specified number of days
	            cout << GREEN << "Room " << roomNumber << " Booked For " << customer.getName() << " for " << days << " days." << RESET << endl;
	            return true;
	        }
	    }
	    cout << RED << "Room " << roomNumber << " Is Not Available!" << RESET << endl;
	    return false;
	}

 // Get the total income from all booked rooms
double getTotalIncome()
{
    double totalIncome = 0;
    for (int i = 0; i < rooms.size(); i++)
    {
        if (rooms[i].getIsBooked())
        {
            totalIncome += rooms[i].getTotalBill();  // Add the total bill for each booked room
        }
    }
    return totalIncome;
}

    // Vacate a room
    void vacateRoom(string roomNumber)
    {
        for (int i =0;i < rooms.size();i++)
        {
            if (rooms[i].getRoomNumber() == roomNumber)
            {
                if(rooms[i].getIsBooked()){
                    rooms[i].vacate();
                    cout <<GREEN<< "Room " << roomNumber << " Vacated!"<<RESET << endl;
                } else {
                    cout <<GREEN<< "Room " << roomNumber << " Is Available To Book!"<<RESET << endl;
                }

                return;
            }
        }
        cout <<RED<< "Room " << roomNumber << " Doesn\'t Exist!"<<RESET << endl;
    }

    // Get Room Price
    double getRoomPrice(string roomNumber)
    {
        for (int i =0;i < rooms.size();i++)
        {
            if (rooms[i].getRoomNumber() == roomNumber)
            {
                return rooms[i].getPrice();
            }
        }
        cout <<RED<< "Room " << roomNumber << " Doesn\'t Exist!"<<RESET << endl;
        return -1;
    }

    //get room info and return customer id if booked
    int checkRoom(string roomNumber)
    {
        for (int i =0;i < rooms.size();i++)
        {
            if (rooms[i].getRoomNumber() == roomNumber)
            {
                rooms[i].getDetails();
                return rooms[i].getCustomerID();
            }
        }
        cout <<RED<< "Room " << roomNumber << " Doesn\'t Exist!"<<RESET << endl;
        return -1;
    }

    // Set Room Price
    bool editRoom(string roomNumber)
    {
        for (int i =0;i < rooms.size();i++)
        {
            if (rooms[i].getRoomNumber() == roomNumber)
            {
                double price;
                cout << "New Price ($):";
                cin >> price;
                rooms[i].setPrice(price);
                cout <<GREEN<< "Room " << roomNumber << " Price Updated To " << price<<RESET << endl;
                return true;
            }
        }
        cout <<RED<< "Room " << roomNumber << " Doesn\'t Exist!"<<RESET << endl;
        return false;
    }


    // Get The List of All Rooms
    void viewAllRooms()
    {
        char floorChar = 'A';
        int floorExt = 1;
        for (int floor = 1; floor <= totalFloors; ++floor)
        {
            cout << "FLOOR "<<(floor < 10 ? "00" : (floor < 100 ? "0" : "")) <<floor;
            cout << ":\n----------\n";
            for(int roomNum = 1; roomNum <= eachFloorRoomCount; ++roomNum)
            {
                // Room number format: Character Representing Floor + Floor Extension + 00 or 0 + Room Number
                string roomNumber = floorChar + to_string(floorExt)
                                    + (roomNum < 10 ? "00" : (roomNum < 100 ? "0" : ""))+ to_string(roomNum);
                if (isRoomAvailable(roomNumber))
                {
                    cout <<"["<<GREEN<< roomNumber << RESET<< "] ";
                }
                else
                {
                    cout <<"["<< RED << roomNumber << RESET<< "] ";
                }
            }
            cout <<endl<< endl;
            // Reset To Character Representing Floor To 'A' if it Exceeds 'Z'
            // Increase Floor Extension If Character Representing Floor Exceeds 'Z'
            if (floorChar == 'Z')
            {
                floorChar = 'A';
                floorExt++;
            }
            else
            {
                floorChar++;
            }
        }
        cout << endl;
    }
};



// Check If Admin Credentials Match
bool checkAdmin(vector<Admin>& admins, string username, string password)
{
    for (int i =0;i < admins.size();i++)
    {
        if (admins[i].getUsername() == username && admins[i].getPassword() == password)
        {
            if(admins[i].isSuper()){
                ::superAdmin = true;
            } else {
                ::superAdmin = false;
            }
            return true;
        }
    }
    return false;
}


// Enter to Continue
void continueProcess()
{
    cin.ignore();
    cout << "\n\nPress Enter To Continue...";
    cin.get();
    system("cls");
}

// Login Screen
bool loginScreen(vector<Admin>& admins)
{
    string username,password;
    cout << "\n\nLogin To Panel\n=================\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin>>password;
    if(checkAdmin(admins,username,password))
    {
        cin.get();
        system("cls");
        return true;
    }
    else
    {
        return false;
    }
}
// VIPCustomer class - Correctly overriding and calling base class methods
class VIPCustomer : public Customer {
public:
    double discountRate; // VIP customers get a discount on bills

    VIPCustomer() : Customer(), discountRate(0.1) {} // Default 10% discount

    void applyDiscount() {
        cout << "VIP Discount Applied: " << discountRate * 100 << "%" << endl;
    }

    void get_Details() {
        Customer::getDetails(); // Calls the base class method (Customer's getDetails)
        cout << "VIP Discount Rate: " << discountRate * 100 << "%" << endl;
    }
};

// ExtendedGuest class - Resolving ambiguity in getDetails()
class ExtendedGuest : public Guest, public Customer {
public:
    bool hasVIPStatus;

    ExtendedGuest(int id, string n, bool vipStatus)
        : Guest(id, n), Customer(), hasVIPStatus(vipStatus) {}

    void displayInfo() {
        Customer::getDetails(); // Call getDetails from Customer explicitly
        cout << "Guest Name: " << name << endl;
        if (hasVIPStatus) {
            cout << "VIP Status: Active" << endl;
        } else {
            cout << "VIP Status: Inactive" << endl;
        }
    }
};

// PremiumGuest class - Correct usage of base class method
class PremiumGuest : public Guest {
public:
    bool hasSpaAccess;

    PremiumGuest(int id, string n, bool spaAccess)
        : Guest(id, n), hasSpaAccess(spaAccess) {}

    void displayPremiumInfo() {
        getDetails(); // Calls Guest's getDetails method
        cout << "Spa Access: " << (hasSpaAccess ? "Yes" : "No") << endl;
    }
};

// DeluxeRoom class - No ambiguity, just a derived class
class DeluxeRoom : public Room {
public:
    DeluxeRoom(string number, double price, int floor)
        : Room(number, price, floor) {}

    void displaySpecialFeatures() {
        cout << "Deluxe Room Features: Luxury amenities included!" << endl;
    }
};

// StandardRoom class - No ambiguity, just a derived class
class StandardRoom : public Room {
public:
    StandardRoom(string number, double price, int floor)
        : Room(number, price, floor) {}

    void displayStandardFeatures() {
        cout << "Standard Room Features: Basic amenities included." << endl;
    }
};

// LuxuryCustomer class - Correctly handling multiple inheritance
class LuxuryCustomer : public VIPCustomer, public Guest {
public:
    bool hasExclusiveAccess;

    LuxuryCustomer(int id, string n, bool vipStatus, bool exclusiveAccess)
        : VIPCustomer(), Guest(id, n), hasExclusiveAccess(exclusiveAccess) {}

    void showLuxuryFeatures() {
        applyDiscount(); // Calls VIPCustomer's applyDiscount method
        Guest::getDetails(); // Calls Guest's displayInfo method
        cout << "Exclusive Access: " << (hasExclusiveAccess ? "Yes" : "No") << endl;
    }
};


// Menu Screen
void menuScreen(vector<Admin>& admins, vector<Customer>& customers, Hotel& hotel)
{
    int option;
    string id;
    int custType;
    int cust;
    Customer* tempCust;
    bool isGuest = false;
    bool isntOneOrTwo = true;
    Guest* guest = nullptr;

    while (isntOneOrTwo) {
        // Ask if the user is a guest or admin
        cout << "Are you a Guest or an Admin?\n";
        cout << "[1] Guest\n[2] Admin\n> ";
        int userType = getvalidinteger();

        if (userType == 1) {
            isGuest = true;
            cout << "Enter your Customer ID: ";
            cin >> cust;
            guest = new Guest(cust, "Guest"); // Dummy name for now
            isntOneOrTwo = false;
        }
        else if (userType == 2) {
            isGuest = false;
            isntOneOrTwo = false;
        }
    }

    if (isGuest) {
        do {
            cout << "Welcome, Guest! Please select an option:\n";
            cout << "[1] View Food Menu\n[2] Order Food\n[3] View Total Bill\n[4] Extend Stay\n[5] Change Room\n[6] Logout\n> ";
            int option = getvalidinteger();

            switch (option) {
            case 1: {
                // Choose meal type
                cout << "Select a meal type:\n[1] Breakfast\n[2] Lunch\n[3] Dinner\n> ";
                int mealChoice = getvalidinteger();
                string mealType;

                switch (mealChoice) {
                case 1: mealType = "Breakfast"; break;
                case 2: mealType = "Lunch"; break;
                case 3: mealType = "Dinner"; break;
                default:
                    cout << "Invalid choice. Returning to menu.\n";
                    continue;
                }

                guest->viewFoodMenu(hotel.foodMenu, mealType);
                continueProcess();
                break;
            }
            case 2: {
                // Order food by meal type
                cout << "Select a meal type to order from:\n[1] Breakfast\n[2] Lunch\n[3] Dinner\n> ";
                int mealChoice = getvalidinteger();
                string mealType;

                switch (mealChoice) {
                case 1: mealType = "Breakfast"; break;
                case 2: mealType = "Lunch"; break;
                case 3: mealType = "Dinner"; break;
                default:
                    cout << "Invalid choice. Returning to menu.\n";
                    continue;
                }

                guest->viewFoodMenu(hotel.foodMenu, mealType); 

                // Choose an item to order
                cout << "Enter the number of the food item to order: ";
                int foodChoice;
                cin >> foodChoice;

                // Ensure the selection is valid
                if (foodChoice > 0 && foodChoice <= hotel.foodMenu.size() && 
                    hotel.foodMenu[foodChoice - 1].mealType == mealType) {
                    guest->addFoodToOrder(hotel.foodMenu[foodChoice - 1]);
                    cout << "Food added to order.\n";
                } else {
                    cout << "Invalid food choice.\n";
                }

                continueProcess();
                break;
            }
            case 3:
                guest->viewTotalBill();
                continueProcess();
                break;
            case 4: {
                int days;
                cout << "How many days would you like to extend your stay? ";
                cin >> days;
                guest->extendStay(days);
                continueProcess();
                break;
            }
            case 5: {
                string newRoom;
                cout << "Enter the new room number: ";
                cin >> newRoom;
                hotel.changeRoom(*guest, newRoom);
                continueProcess();
                break;
            }
            case 6:
                cout << "Logging out as guest...\n";
                isGuest = false;  // Set isGuest to false to exit the guest menu loop
                continueProcess();
                break;
            default:
                cout << "Invalid Option! Try again...\n";
                break;
            }
        } while (isGuest);  // This will keep the loop running until `isGuest` is set to false
    } else {
        // Admin Menu
        do {
            cout << "Admin Panel\n=================\n";
            cout << "Select An Option (1-9)\n\n";
            cout << MAGENTA << "[1] " << RESET << "All Rooms" << endl;
            cout << MAGENTA << "[2] " << RESET << "All Customers" << endl;
            cout << MAGENTA << "[3] " << RESET << "Room Details" << endl;
            cout << MAGENTA << "[4] " << RESET << "Edit Room Price" << endl;
            cout << MAGENTA << "[5] " << RESET << "Book A Room" << endl;
            cout << MAGENTA << "[6] " << RESET << "Vacate A Room" << endl;
            cout << MAGENTA << "[7] " << RESET << "Add New Admin" << endl;
            cout << MAGENTA << "[8] " << RESET << "Logout" << endl;
            cout << MAGENTA << "[9] " << RESET << "Total Income" << endl;  // Added option for total income
            cout << "\n> ";
            option = getvalidinteger();
            system("cls");

            // Handle admin actions
            switch (option) {
            case 1:
                hotel.viewAllRooms();
                continueProcess();
                break;
            case 2:
                viewAllCustomers(customers);
                continueProcess();
                break;
            case 3:
                cout << "Room Number: ";
                cin >> id;
                hotel.checkRoom(id);
                continueProcess();
                break;
            case 4:
                cout << "Room No: ";
                cin >> id;
                hotel.editRoom(id);
                continueProcess();
                break;
case 5: {
    cout << "Room No:";
    cin >> id;
    
    if (hotel.isRoomAvailable(id)) {
        cout << "Room Price ($): " << hotel.getRoomPrice(id) << endl;
        
        // Ask for customer type (VIP or Premium)
        cout << "\nCustomer Type:\n[1] Existing\n[2] New Customer\n[3] VIP\n[4] Premium\n> ";
        cin >> custType;

        if (custType == 1) {
            cout << "Customer ID: ";
            cin >> cust;
            tempCust = checkCustomer(customers, cust);
            if (tempCust != nullptr) {
                // Ask for room type (Deluxe, Single, Double)
                int roomType;
                cout << "\nRoom Type:\n[1] Deluxe\n[2] Single\n[3] Double\n> ";
                cin >> roomType;

                if (roomType == 1) {
                    hotel.bookRoom(id, *tempCust, "Deluxe");
                } else if (roomType == 2) {
                    hotel.bookRoom(id, *tempCust, "Single");
                } else if (roomType == 3) {
                    hotel.bookRoom(id, *tempCust, "Double");
                } else {
                    cout << RED << "\nInvalid Room Type!" << RESET;
                }
            } else {
                cout << RED << "\nInvalid Customer ID!" << RESET;
            }
        } 
        else if (custType == 2) {
            customers.push_back(Customer());
            // Ask for room type (Deluxe, Single, Double)
            int roomType;
            cout << "\nRoom Type:\n[1] Deluxe\n[2] Single\n[3] Double\n> ";
            cin >> roomType;

            if (roomType == 1) {
                hotel.bookRoom(id, customers.back(), "Deluxe");
            } else if (roomType == 2) {
                hotel.bookRoom(id, customers.back(), "Single");
            } else if (roomType == 3) {
                hotel.bookRoom(id, customers.back(), "Double");
            } else {
                cout << RED << "\nInvalid Room Type!" << RESET;
            }
        } 
        else if (custType == 3) {  // VIP Customer
            // Create a VIP customer and book a room
            customers.push_back(VIPCustomer());
            cout << "\nVIP Customer has been added.\n";
            int roomType;
            cout << "\nRoom Type:\n[1] Deluxe\n[2] Single\n[3] Double\n> ";
            cin >> roomType;

            if (roomType == 1) {
                hotel.bookRoom(id, customers.back(), "Deluxe");
            } else if (roomType == 2) {
                hotel.bookRoom(id, customers.back(), "Single");
            } else if (roomType == 3) {
                hotel.bookRoom(id, customers.back(), "Double");
            } else {
                cout << RED << "\nInvalid Room Type!" << RESET;
            }
        }
        else if (custType == 4) {  // Premium Customer
            // Create a Premium customer and book a room
            customers.push_back(VIPCustomer());
            cout << "\nPremium Customer has been added.\n";
            int roomType;
            cout << "\nRoom Type:\n[1] Deluxe\n[2] Single\n[3] Double\n> ";
            cin >> roomType;

            if (roomType == 1) {
                hotel.bookRoom(id, customers.back(), "Deluxe");
            } else if (roomType == 2) {
                hotel.bookRoom(id, customers.back(), "Single");
            } else if (roomType == 3) {
                hotel.bookRoom(id, customers.back(), "Double");
            } else {
                cout << RED << "\nInvalid Room Type!" << RESET;
            }
        } else {
            cout << RED << "\nInvalid Choice!" << RESET;
        }
    }
    continueProcess();
    break;
}

            case 6:
                cout << "Room No:";
                cin >> id;
                hotel.vacateRoom(id);
                continueProcess();
                break;
            case 7:
                admins.push_back(Admin());
                continueProcess();
                break;
            case 8:
                loggedIn = false;
                system("cls");
                cout << GREEN << "Logged Out Successfully!...\n\n" << RESET;
                isGuest = true;
                break;
            case 9:  // Show total income
                cout << "Total Income from All Customers: $" << hotel.getTotalIncome() << endl;
                continueProcess();
                break;
            default:
                cout << RED << "Invalid Option! Try again..." << RESET;
                continueProcess();
                break;
            }
        } while (isGuest != true);
    }
}

int main()
{
    string tempStr1,tempStr2;
    int tempInt1,tempInt2;
    double tempDouble1;
    bool loggedIn = false;


    // Intro Screen
    cout << "======================================"<<endl;
    cout << "||     Hotel Management System       ||"<<endl;
    cout << "======================================"<<endl<<endl;

    cout << "\nYou are just one step away from having your hotel management system!";
    cout << "\nPress Enter To Continue...";
    cin.get();

    system("cls");


    // First Time Hotel Setup
    cout << "First Time Setup\n=================\n";
    cout << "Before we can continue, let\'s setup your hotel first. "
         "Please fill the form below:\n\n";
    cout << "Hotel Name:";
    getline(cin, tempStr1);
    cout << "Total Floors:";
    tempInt1=getvalidinteger();
    cout << "Rooms In Each Floors:";
    tempInt2=getvalidinteger();
    cout << "Default Room Cost ($):";
    tempDouble1=getvaliddouble();
    Hotel hotel(tempStr1,tempInt1,tempInt2,tempDouble1);
    vector<Customer> customers;
    cout <<GREEN<< "Hotel Information Saved!"<<RESET;


    // Super Admin Setup
    cout << "\n\nSuper Admin\n=================\n";
    cout << "Let\'s setup a super admin of your hotel. Only super admins have the power to"
         " add more admins and have all admin powers\n\n";
    vector<Admin> admins;
    admins.push_back(Admin(true));
    cout << "\nSuper Admin created! Now continue to the panel using your username "
         "and password to start managing your hotel";
    continueProcess();

    // Admin Panel
    while(true)
    {
        if(::loggedIn)
        {
            //Main Menu
            menuScreen(admins,customers,hotel);


        }
        else
        {
            // Login Screen
            if(loginScreen(admins))
            {
                ::loggedIn = true;
            }
            else
            {
                system("cls");
                cout <<RED<< "Invalid Iogin Credentials!"<<RESET;

            }
        }
    }
    return 0;
} 

