#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

// === Constants ===
const int MAX_ENTRIES = 100;
const int MAX_ITEMS = 100;
const float TAX_RATE = 0.15;

// === Structs ===

// Struct to store service details

struct Service1 {
    string serviceName;
    int serviceCost;
    string name;
    int cost;

};

struct Tax {
    string taxName;
    float taxRate;
};

struct MaintenanceEntry {
    string carModel;
    int carYear;
    string carMileageOrMonths;
    string maintenanceItems[MAX_ITEMS];
    int itemCount;
};
struct Part {
    string name;
    int cost;
    string carModels[5];
    int modelCount;
    string partName;
    int partCost;
};
struct Maintenance {
    string model;
    int year;
    int mileage;
    int months;
    string parts2[5];
    int partCount;
    string services[5];
    int serviceCount;
};

Part parts1[100];
Service1 services1[100];
Maintenance maintenanceSchedules[100];
int maintenanceCount = 0;
















// === Global Variables ===
Part parts[MAX_ITEMS];
int partCount = 0;

Service1 services[MAX_ITEMS];
int serviceCount = 0;

Tax taxes[MAX_ITEMS];
int taxCount = 0;

MaintenanceEntry maintenanceTable[MAX_ENTRIES];
int entryCount = 0;

// === Functions ===


/////////////////////////
// LOAD FUNCTIONS
/////////////////////////

void loadParts(Part parts[], int& partCount) {
    ifstream file("parts.txt");
    while (file && partCount < MAX_ITEMS) {
        getline(file, parts[partCount].name);  // قراءة الاسم كاملاً
        file >> parts[partCount].cost;
        file.ignore();  // تجاهل السطر بعد قراءة التكلفة
        partCount++;
    }
    file.close();
}

void loadServices(Service1 services[], int& serviceCount) {
    ifstream file("services.txt");
    while (file && serviceCount < MAX_ITEMS) {
        getline(file, services[serviceCount].name);  // قراءة الاسم كاملاً
        file >> services[serviceCount].cost;
        file.ignore();  // تجاهل السطر بعد قراءة السعر
        serviceCount++;
    }
    file.close();
}
void loadTaxes(Tax taxes[], int& taxCount) {
    ifstream file("taxes.txt");
    while (file >> taxes[taxCount].taxName >> taxes[taxCount].taxRate) {
        taxCount++;
    }
    file.close();
}








/////////////////////////
// ADD FUNCTIONS
/////////////////////////

void addPart(Part parts[], int& partCount) {
    cout << "Enter part name: ";
    cin >> parts[partCount].name;
    cout << "Enter part cost: ";
    cin >> parts[partCount].cost;
    partCount++;  // increase counter
}

void addService(Service1 services[], int& count) {
    cout << "Enter service name: ";
    cin >> services[count].name;
    cout << "Enter service cost: ";
    cin >> services[count].cost;
    count++;  // زيادة العداد
}

void addTax(Tax taxes[], int& taxCount) {
    cout << "Enter tax name: ";
    cin >> taxes[taxCount].taxName;
    cout << "Enter tax rate (%): ";
    cin >> taxes[taxCount].taxRate;
    taxCount++;  // increase counter
}







/////////////////////////
// UPDATE FUNCTIONS
/////////////////////////

void updatePart(Part parts[], int partCount) {
    string target;
    cout << "Enter part name to update: ";
    cin >> target;

    for (int i = 0; i < partCount; i++) {
        if (parts[i].name == target) {
            cout << "Enter new cost: ";
            cin >> parts[i].cost;  // update cost
            return;
        }
    }
    cout << "Part not found.\n";
}

void updateService(Service1 services[], int serviceCount) {
    string target;
    cout << "Enter service name to update: ";
    cin >> target;

    for (int i = 0; i < serviceCount; i++) {
        if (services[i].name == target) {
            cout << "Enter new price: ";
            cin >> services[i].cost;  // update price
            return;
        }
    }
    cout << "Service not found.\n";
}

void updateTax(Tax taxes[], int taxCount) {
    string target;
    cout << "Enter tax name to update: ";
    cin >> target;

    for (int i = 0; i < taxCount; i++) {
        if (taxes[i].taxName == target) {
            cout << "Enter new rate: ";
            cin >> taxes[i].taxRate;  // update rate
            return;
        }
    }
    cout << "Tax not found.\n";
}





/////////////////////////
// SAVE TO FILE FUNCTIONS
/////////////////////////

void saveParts(const Part parts[], int partCount) {
    ofstream file("parts.txt");
    for (int i = 0; i < partCount; ++i) {
        file << parts[i].name << endl;
        file << parts[i].cost << endl;
    }
    file.close();
}


void saveServices(const Service1 services[], int count) {
    ofstream file("services.txt");
    for (int i = 0; i < count; ++i) {
        file << services[i].name << endl;
        file << services[i].cost << endl;
    }
    file.close();
}

void saveTaxes(const Tax taxes[], int taxCount) {
    ofstream file("taxes.txt");
    for (int i = 0; i < taxCount; i++) {
        file << taxes[i].taxName << " " << taxes[i].taxRate << endl;
    }
    file.close();
}





/////////////////////////
// ADMIN MENU
/////////////////////////















bool isModelApplicable(string carModels[], int modelCount, string target) {
    for (int i = 0; i < modelCount; i++) {
        if (carModels[i] == "All" || carModels[i] == target) return true;
    }
    return false;
}











void calculateEstimate(string model, int year, int mileage, int months) {
    string requiredParts[10];
    string requiredServices[10];
    int rpCount = 0, rsCount = 0;
    int total = 0;
    bool found = false;

    for (int i = 0; i < maintenanceCount; i++) {
        if (maintenanceSchedules[i].model == model && maintenanceSchedules[i].year == year &&
            maintenanceSchedules[i].mileage == mileage && maintenanceSchedules[i].months == months) {
            for (int j = 0; j < maintenanceSchedules[i].partCount; j++) {
                requiredParts[rpCount++] = maintenanceSchedules[i].parts2[j];
            }
            for (int j = 0; j < maintenanceSchedules[i].serviceCount; j++) {
                requiredServices[rsCount++] = maintenanceSchedules[i].services[j];
            }
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No maintenance schedule found for the given input." << endl;
        return;
    }

    cout << "Item - Cost" << endl;
    for (int i = 0; i < rpCount; i++) {
        for (int j = 0; j < partCount; j++) {
            if (parts[j].name == requiredParts[i] &&
                isModelApplicable(parts[j].carModels, parts[j].modelCount, model)) {
                cout << parts[j].name << " - " << parts[j].cost << endl;
                total += parts[j].cost;
                break;
            }
        }
    }

    for (int i = 0; i < rsCount; i++) {
        for (int j = 0; j < serviceCount; j++) {
            if (services[j].serviceName == requiredServices[i]) {
                cout << services[j].serviceName << " - " << services[j].serviceCost << endl;
                total += services[j].serviceCost;
                break;
            }
        }

    }

    int tax = total * TAX_RATE;
    cout << "Tax - " << tax << endl;
    total += tax;
    cout << "Total - " << total << endl;
}

















void loadMockData() {
    parts[0] = { "Battery", 1000, {"MG5", "MG6"}, 2 };
    parts[1] = { "Oil 10K", 900, {"All"}, 1 };
    parts[2] = { "Wipers", 200, {"MG5" , "MG6" }, 2 };
    parts[3] = { "wipers", 250, {"MG6"} , 1 };
    partCount = 4;

    services[0] = { "Change Oil", 150 };
    services[1] = { "Change Tyres", 300 };
    serviceCount = 2;

    maintenanceSchedules[0] = { "MG5", 2020, 10000, 6, {"Oil 10K", "Wipers"}, 2, {"Change Oil"}, 1 };
    maintenanceSchedules[1] = { "MG5", 2021, 10000, 6, {"Oil 10K", "Wipers"}, 2, {"Change Oil"}, 1 };
    maintenanceSchedules[2] = { "MG6", 2021, 10000, 6, {"Oil 10K", "wipers"}, 2, {"Change Oil"}, 1 };
    maintenanceSchedules[3] = { "MG6", 2022, 10000, 6, {"Oil 10K", "wipers"}, 2, {"Change Oil"}, 1 };
    maintenanceSchedules[4] = { "MG5", 2020, 20000, 12, {"Battery"}, 1, {"Change Tyres"}, 1 };
    maintenanceSchedules[5] = { "MG5", 2021, 20000, 12, {"Battery"}, 1, {"Change Tyres"}, 1 };
    maintenanceSchedules[6] = { "MG6", 2021, 20000, 12, {"Battery"}, 1, {"Change Tyres"}, 1 };
    maintenanceSchedules[7] = { "MG6", 2022, 20000, 12, {"Battery"}, 1, {"Change Tyres"}, 1 };
    maintenanceSchedules[8] = { "MG5" , 2022 , 10000 , 6 , {"Oil 10k " , "Wipers"} , 2 , {"Change Oil"} , 1 };
    maintenanceSchedules[9] = { "MG5" , 2022 , 20000 , 12 , { "Battery"} , 1, {"Change Tyres"} , 1 };
    maintenanceSchedules[10] = { "MG6" , 2020 , 10000 , 6 , { "Oil 10k" , "wipers"} , 2 , { "Change Oil"} , 1 };
    maintenanceSchedules[11] = { "MG6" , 2020 , 20000 , 12 , { "Battery" } , 1 , {"Change Tyres"} , 1 };
    maintenanceCount = 12;
}











void loadDataFromFile() {
    ifstream inFile("maintenance_data.txt");
    if (!inFile) {
        cout << ">> File not found.\n";
        return;
    }

    string line;
    while (getline(inFile, maintenanceTable[entryCount].carModel)) {
        inFile >> maintenanceTable[entryCount].carYear;
        inFile.ignore();
        getline(inFile, maintenanceTable[entryCount].carMileageOrMonths);
        inFile >> maintenanceTable[entryCount].itemCount;
        inFile.ignore();

        if (maintenanceTable[entryCount].itemCount > MAX_ITEMS) {
            cout << ">> Too many items in entry. Skipping...\n";
            continue;
        }

        for (int i = 0; i < maintenanceTable[entryCount].itemCount; i++) {
            getline(inFile, maintenanceTable[entryCount].maintenanceItems[i]);
        }

        getline(inFile, line); // skip ---
        entryCount++;
        if (entryCount >= MAX_ENTRIES) break;
    }

    inFile.close();
}

void saveDataToFile() {
    ofstream outFile("maintenance_data.txt");
    for (int i = 0; i < entryCount; i++) {
        outFile << maintenanceTable[i].carModel << "\n";
        outFile << maintenanceTable[i].carYear << "\n";
        outFile << maintenanceTable[i].carMileageOrMonths << "\n";
        outFile << maintenanceTable[i].itemCount << "\n";
        for (int j = 0; j < maintenanceTable[i].itemCount; j++) {
            outFile << maintenanceTable[i].maintenanceItems[j] << "\n";
        }
        outFile << "---\n";
    }
    outFile.close();
}

void addEntry() {
    if (entryCount >= MAX_ENTRIES) {
        cout << ">> Table is full.\n";
        return;
    }

    cout << "Enter car model: ";
    cin >> ws;
    getline(cin, maintenanceTable[entryCount].carModel);

    cout << "Enter year: ";
    cin >> maintenanceTable[entryCount].carYear;

    cout << "Enter mileage/months: ";
    cin.ignore();
    getline(cin, maintenanceTable[entryCount].carMileageOrMonths);

    cout << "Enter number of maintenance items: ";
    cin >> maintenanceTable[entryCount].itemCount;
    cin.ignore();

    if (maintenanceTable[entryCount].itemCount > MAX_ITEMS) {
        cout << "Too many items! Max is " << MAX_ITEMS << ".\n";
        return;
    }

    for (int i = 0; i < maintenanceTable[entryCount].itemCount; i++) {
        cout << "Enter item " << i + 1 << ": ";
        getline(cin, maintenanceTable[entryCount].maintenanceItems[i]);
    }

    entryCount++;
    saveDataToFile();
    cout << ">> Entry added.\n";
}

void displayEntries() {
    cout << "\n=== Maintenance Schedule ===\n";
    for (int i = 0; i < entryCount; i++) {
        cout << "Model: " << maintenanceTable[i].carModel
            << " | Year: " << maintenanceTable[i].carYear
            << " | Mileage/Months: " << maintenanceTable[i].carMileageOrMonths << "\n";
        for (int j = 0; j < maintenanceTable[i].itemCount; j++) {
            cout << "  - " << maintenanceTable[i].maintenanceItems[j] << "\n";
        }
        cout << "--------------------------\n";
    }
}

void searchEntry() {
    string keyword;
    cout << "Enter keyword to search: ";
    cin.ignore();
    getline(cin, keyword);

    bool found = false;
    for (int i = 0; i < entryCount; i++) {
        bool entryFound = false;

        if (maintenanceTable[i].carModel == keyword ||
            to_string(maintenanceTable[i].carYear) == keyword ||
            maintenanceTable[i].carMileageOrMonths == keyword) {
            entryFound = true;
        }

        for (int j = 0; j < maintenanceTable[i].itemCount; j++) {
            if (maintenanceTable[i].maintenanceItems[j] == keyword) {
                entryFound = true;
                break;
            }
        }

        if (entryFound) {
            found = true;
            cout << "\n>> Found Entry:\n";
            cout << "Model: " << maintenanceTable[i].carModel
                << " | Year: " << maintenanceTable[i].carYear
                << " | Mileage/Months: " << maintenanceTable[i].carMileageOrMonths << "\n";
            for (int j = 0; j < maintenanceTable[i].itemCount; j++) {
                cout << "  - " << maintenanceTable[i].maintenanceItems[j] << "\n";
            }
            cout << "--------------------------\n";
        }
    }

    if (!found) {
        cout << ">> No match found.\n";
    }
}

void updateEntry() {
    string carModel;
    int carYear;
    cout << "Enter model to update: ";
    cin >> ws;
    getline(cin, carModel);
    cout << "Enter year: ";
    cin >> carYear;

    for (int i = 0; i < entryCount; i++) {
        if (maintenanceTable[i].carModel == carModel && maintenanceTable[i].carYear == carYear) {
            cout << "Enter new mileage/months: ";
            cin.ignore();
            getline(cin, maintenanceTable[i].carMileageOrMonths);

            cout << "Enter number of maintenance items: ";
            cin >> maintenanceTable[i].itemCount;
            cin.ignore();

            if (maintenanceTable[i].itemCount > MAX_ITEMS) {
                cout << "Too many items! Max is " << MAX_ITEMS << ".\n";
                return;
            }

            for (int j = 0; j < maintenanceTable[i].itemCount; j++) {
                cout << "Enter item " << j + 1 << ": ";
                getline(cin, maintenanceTable[i].maintenanceItems[j]);
            }

            saveDataToFile();
            cout << ">> Entry updated.\n";
            return;
        }
    }

    cout << ">> Entry not found.\n";
}

void deleteEntry() {
    string carModel;
    int carYear;
    cout << "Enter model to delete: ";
    cin >> ws;
    getline(cin, carModel);
    cout << "Enter year: ";
    cin >> carYear;

    for (int i = 0; i < entryCount; i++) {
        if (maintenanceTable[i].carModel == carModel && maintenanceTable[i].carYear == carYear) {
            for (int j = i; j < entryCount - 1; j++) {
                maintenanceTable[j] = maintenanceTable[j + 1];
            }
            entryCount--;
            saveDataToFile();
            cout << ">> Entry deleted.\n";
            return;
        }
    }
    cout << ">> Entry not found.\n";
}

string username, userPassword, fileusername, filePassword;
// === Login System ===
bool signIn() {

    cout << "Enter your username: ";
    cin.ignore();
    getline(cin, username);
    cout << "Enter your password: ";
    getline(cin, userPassword);

    fstream file("users.txt", ios::in);
    while (getline(file, fileusername) && getline(file, filePassword)) {
        if (fileusername == username && filePassword == userPassword) {
            cout << "Login successful!\n";
            file.close();
            cout << "welcome " << "\t" << username << "!";
            return true;
        }
    }
    file.close();
    cout << "Login failed!\n";
    return false;
}

void sign_up()
{
    fstream file;

    cout << "Enter your username: ";
    cin.ignore();
    getline(cin, username);
    cout << "Enter your password: ";
    getline(cin, userPassword);
    file.open("users.txt", ios::app);
    file << username << endl << userPassword << endl;
    file.close();
    cout << "welcome" << "\t" << username << "!";



}



void maintenance_schedule()
{


    int choice;
    do {
        cout << "\nUser Menu:\n";
        cout << "1. Add Entry\n2. Display Entries\n3. Search Entry\n";
        cout << "4. Update Entry\n5. Delete Entry\n6. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
        case 1: addEntry(); break;
        case 2: displayEntries(); break;
        case 3: searchEntry(); break;
        case 4: updateEntry(); break;
        case 5: deleteEntry(); break;
        case 6: cout << "Goodbye!\n"; break;
        default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);






}
void adminMenu() {
    int choice;
    do {
        // Display menu options to Admin
        cout << "\nAdmin Menu:\n";
        cout << "1. Add Part\n2. Update Part\n";
        cout << "3. Add Service\n4. Update Service\n";
        cout << "5. Add Tax\n6. Update Tax\n";
        cout << "7. Save All\n8. maintenance_schedule\n9. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        // Execute based on choice
        switch (choice) {
        case 1: addPart(parts, partCount); break;
        case 2: updatePart(parts, partCount); break;
        case 3: addService(services, serviceCount); break;
        case 4: updateService(services, serviceCount); break;
        case 5: addTax(taxes, taxCount); break;
        case 6: updateTax(taxes, taxCount); break;
        case 7:
            saveParts(parts, partCount);
            saveServices(services, serviceCount);
            saveTaxes(taxes, taxCount);
            cout << "All data saved.\n";
            break;
        case 8: maintenance_schedule(); break;
        case 9: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice\n";
        }
    } while (choice != 9);  // loop until Exit is chosen
}

void userMenu() {
    loadMockData();
    string model;
    int year, mileage, months;
    int modelChoice;

    cout << "Choose car model:\n";
    cout << "1. MG5\n";
    cout << "2. MG6\n";
    cout << "Enter choice (1 or 2): ";
    cin >> modelChoice;

    if (modelChoice == 1) {
        model = "MG5";
    }
    else if (modelChoice == 2) {
        model = "MG6";
    }
    else {
        cout << "Invalid model choice.\n";
        return;
    }

    cout << "Enter year (e.g., 2020): ";
    cin >> year;
    cout << "Enter mileage (e.g., 10000 or 20000): ";
    cin >> mileage;
    cout << "Enter months (e.g., 6 or 12): ";
    cin >> months;

    calculateEstimate(model, year, mileage, months);
}

// === Main ===
int main() {
    loadDataFromFile();
    // Load existing data from files
    partCount = 0;
    loadParts(parts, partCount);
    serviceCount = 0;
    loadServices(services, serviceCount);
    taxCount = 0;
    loadTaxes(taxes, taxCount);


    int choice;
    cout << "1- Admin Sign Up\n2- Admin Sign In\n3- User Access\nChoose: ";
    cin >> choice;


    switch (choice) {
    case 1:
        sign_up();
        adminMenu();
        break;

    case 2:
        if (signIn()) {
            adminMenu();
        }
        break;

    case 3:
        userMenu();
        break;

    default:
        cout << "Invalid choice!\n";
    }

    return 0;
}
