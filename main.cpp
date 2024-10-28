#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(set<Goat> &trip);
void delete_goat(set<Goat> &trip);
void add_goat(set<Goat> &trip, string[], string[]);
void display_trip(set<Goat> &trip);
int main_menu();

int main() {
    srand(time(0));

    // read & populate arrays for names and colors
    string names[SZ_NAMES];
    string colors[SZ_COLORS];

    ifstream fin("names.txt");
    if (!fin) {
        cerr << "Error" << endl;
        return 1;
    }

    int i = 0;
    while (fin >> names[i] && i < SZ_NAMES) {
        i++;
    }
    fin.close();

    ifstream fin1("colors.txt");
    if (!fin1) {
        cerr << "Error2" << endl;
        return 1;
    }
    i = 0;
    while (fin1 >> colors[i] && i < SZ_COLORS) {
        i++;
    }
    fin1.close();

    set<Goat> trip;

    int choice = 0;
    do {
       choice = main_menu();

       switch (choice) {
       case 1:
            add_goat(trip, names, colors);
            break;
       case 2:
            delete_goat(trip);
            break;
        case 3:
            display_trip(trip);
            break;
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;        
       } 
    } while (choice != 4);
    
    return 0;
}

int main_menu() {
    int choice;
    cout << "\n*** GOAT MANAGER 3001 ***" << endl;
    cout << "[1] Add a goat" << endl;
    cout << "[2] Delete a goat" << endl;
    cout << "[3] List goats" << endl;
    cout << "[4] Quit" << endl;
    cout << "Choice --> ";
    cin >> choice;
    cout << endl;
    return choice;
}

int select_goat(set<Goat>& trip) {
    if (trip.empty()) {
        cout << "Nothing selected" << endl << endl;
        return -1;
    }

    int num = 1;
    cout << "Select a goat:" << endl;
    for (const auto& goat : trip) {
        cout << "[" << num << "] " << goat.get_name() << " (" 
             << goat.get_age() << ", " << goat.get_color() << ")" << endl;
        num++;
    }

    int choice;
    cin >> choice;
    cout << endl;

    if (choice < 1 || choice > static_cast<int>(trip.size())) {
        return -1;
    }

    return choice;
}

void delete_goat(set<Goat>& trip) {
    if (trip.empty()) {
        cout << "Empty goats" << endl << endl;
        return;
    }

    int index = select_goat(trip);
    if (index < 0) {
        cout << "Invalid index" << endl << endl;
        return;
    }

    auto it = trip.begin();
    advance(it, index - 1);
    cout << "Deleted: " << it->get_name() << " (" << it->get_age() 
         << ", " << it->get_color() << ")" << endl << endl;
    trip.erase(it);
}

void add_goat(set<Goat>& trip, string names[], string colors[]) {
    int random_name = rand() % SZ_NAMES;
    int random_color = rand() % SZ_COLORS;
    int random_age = rand() % MAX_AGE;

    Goat new_goat(names[random_name], random_age, colors[random_color]);
    // trip.push_back(new_goat);
    auto result = trip.insert(new_goat);
    if (result.second) {
        cout << "Added: " << new_goat.get_name() << " (" << new_goat.get_age() 
            << ", " << new_goat.get_color() << ")" << endl << endl;
    } else {
        cout << "Choose another goat" << endl;
    }
}

void display_trip(set<Goat>& trip) {
    if (trip.empty()) {
        cout << "Empty list" << endl << endl;
        return;
    }
    
    int num = 1;
    for (const auto& goat : trip) {
        cout << "[" << num << "] " << goat.get_name() << " (" 
             << goat.get_age() << ", " << goat.get_color() << ")" << endl;
        num++;
    }
    cout << endl;
}
