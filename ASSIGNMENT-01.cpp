#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    cout << "=================================================" << endl;
    cout << "   RELIEF SUPPLY DISTRIBUTION SYSTEM SETUP       " << endl;
    cout << "=================================================" << endl;

    // Trackers for end-of-program summary stats
    int deferred_requests = 0;
    int successful_requests = 0;

    int trucks;
    int packs;

    cout << "Press 1 to use full resources (5 trucks and 120 supply packs)" << endl;
    cout << "Press 2 to use partial resources (2 trucks and 70 supply packs)" << endl;

    int choice;
    while (!(cin >> choice) || (choice < 1 || choice > 2)) {
        // These two functions are used incase user enter any character or special character 
        cin.clear();                   // Clears the error/fail state of cin caused by invalid input
        cin.ignore(999, '\n');        // Clears the input buffer to remove leftover bad characters up to the newline
        cout << "Invalid command, press 1 or 2: ";
    }

    switch (choice) {
    case 1:
        trucks = 5;
        packs = 120;
        break;
    case 2:
        trucks = 2;
        packs = 70;
        break;
    }

    if (choice == 1) {
        cout << "You are using full resources: 5 trucks and 120 supply packs \n";
    }
    else if (choice == 2) {
        cout << "You are now starting with partial or limited resources: 2 trucks and 70 supply packs. \n";
    }

    cout << "Enter the amount of requests to be made: ";
    int requests_count;
    while (!(cin >> requests_count) || requests_count <= 0) {
        cin.clear();
        cin.ignore(999, '\n');
        cout << "Invalid input! Enter a positive integer: ";
    }

    // Main loop to process each disaster relief request sequentially
    for (int i = 1; i <= requests_count; i++) {
        cout << "\nTaking request NO." << i << endl;
        cout << "Current resources are as follows:" << endl;
        cout << "Trucks: " << trucks << endl;
        cout << "Supply packs: " << packs << endl;

        cout << "Enter location name: ";
        string location_name;
        getline(cin >> ws, location_name);   // Clears leading whitespace and reads the full location name including spaces

        cout << "Enter damage (H for high , M for medium , L for low): ";
        char damage;
        cin >> damage;
        while (damage != 'h' && damage != 'H' && damage != 'm' && damage != 'M' && damage != 'L' && damage != 'l') {
            cout << "Invalid command, enter again (H, M, or L): ";
            cin.clear();
            cin.ignore(999, '\n');
            cin >> damage;
        }

        cout << "Enter the amount of families affected (10 to 200): ";
        int families_affected;
        while (!(cin >> families_affected) || families_affected < 10 || families_affected > 200) {
            cout << "Invalid command, enter again (between 10 and 200): ";
            cin.clear();
            cin.ignore(999, '\n');
        }

        cout << "Access route condition (O for open and D for damaged): ";
        char access_route;
        cin >> access_route;
        while (access_route != 'O' && access_route != 'o' && access_route != 'd' && access_route != 'D') {
            cout << "Invalid command, enter again (O or D): ";
            cin.clear();
            cin.ignore(999, '\n');
            cin >> access_route;
        }

        cout << "Flood warning? (Y for yes and N for no): ";
        char flood_warning;
        cin >> flood_warning;
        while (flood_warning != 'y' && flood_warning != 'Y' && flood_warning != 'n' && flood_warning != 'N') {
            cout << "Invalid command, enter again (Y or N): ";
            cin.clear();
            cin.ignore(999, '\n');
            cin >> flood_warning;
        }

        cout << "Medical need? (Y for yes and N for no): ";
        char medical_need;
        cin >> medical_need;
        while (medical_need != 'y' && medical_need != 'Y' && medical_need != 'n' && medical_need != 'N') {
            cout << "Invalid command, enter again (Y or N): ";
            cin.clear();
            cin.ignore(999, '\n');
            cin >> medical_need;
        }

        cout << "Previous aid received? (Y for yes and N for no): ";
        char previous_aid;
        cin >> previous_aid;
        while (previous_aid != 'y' && previous_aid != 'Y' && previous_aid != 'n' && previous_aid != 'N') {
            cout << "Invalid command, enter again (Y or N): ";
            cin.clear();
            cin.ignore(999, '\n');
            cin >> previous_aid;
        }

        cout << endl;

        // CALCULATING SCORES

        // 1. Damage score using a switch statement because we know the assigned values
        int damage_score;
        switch (damage) {
        case 'H':
        case 'h':
            damage_score = 30;
            break;
        case 'M':
        case 'm':
            damage_score = 20;
            break;
        case 'L':
        case 'l':
            damage_score = 0;
            break;
        default:
            damage_score = 0;  // For deferred case
            break;
        }

        // 2. Family score
        int family_score;
        if (families_affected < 90) {
            family_score = 0;
        }
        else if (families_affected <= 150) {
            family_score = 20;
        }
        else {
            family_score = 30;
        }

        // 3. Route condition score
        int route_score;
        if (access_route == 'D' || access_route == 'd') {
            route_score = 10;
        }
        else {
            route_score = 0;
        }

        // 4. Flood warning score
        int flood_score;
        if (flood_warning == 'y' || flood_warning == 'Y') {
            flood_score = 10;
        }
        else {
            flood_score = 0;
        }

        // 5. Medical need score
        int medical_score;
        if (medical_need == 'y' || medical_need == 'Y') {
            medical_score = 15;
        }
        else {
            medical_score = 0;
        }

        // 6. Previous aid score
        int previous_aid_score;
        if (previous_aid == 'y' || previous_aid == 'Y') {
            previous_aid_score = -5;
        }
        else {
            previous_aid_score = 5;
        }

        // Sum total score and apply defensive boundaries
        int total_score = damage_score + route_score + family_score + flood_score + medical_score + previous_aid_score;
        if (total_score > 100) {
            total_score = 100;
        }
        if (total_score < 0) {
            total_score = 0;
        }

        // DISPLAYING FORMATTED BREAKDOWN TABLE 
        cout << left << setw(25) << "Factor" << setw(20) << "Values" << setw(10) << "Scores" << endl;
        cout << left << setw(25) << "Request Location" << setw(20) << location_name << setw(10) << "-" << endl;
        cout << left << setw(25) << "Damage Level" << setw(20) << damage << setw(10) << damage_score << endl;
        cout << left << setw(25) << "Families Affected" << setw(20) << families_affected << setw(10) << family_score << endl;
        cout << left << setw(25) << "Access Route" << setw(20) << access_route << setw(10) << route_score << endl;
        cout << left << setw(25) << "Flood Warning" << setw(20) << flood_warning << setw(10) << flood_score << endl;
        cout << left << setw(25) << "Medical Need" << setw(20) << medical_need << setw(10) << medical_score << endl;
        cout << left << setw(25) << "Previous Aid" << setw(20) << previous_aid << setw(10) << previous_aid_score << endl;
        cout << endl;

        cout << "The total score for " << location_name << " is: " << total_score << endl;
        cout << endl;

        // DECISION LOGIC & RESOURCE FALLBACKS
        int trucks_used = 0;
        int packs_used = 0;

        if (total_score > 75) {
            if ((access_route == 'd' || access_route == 'D') && trucks >= 1 && packs >= 30) {
                cout << "Damaged route restricts heavy convoy! Capped Fallback: Standard relief (1 Truck and 30 supply packs)." << endl;
                trucks_used = 1;
                packs_used = 30;
                trucks -= 1;
                packs -= 30;
                successful_requests++;
            }
            else if (trucks >= 2 && packs >= 50) {
                cout << "Sending total relief: 2 Trucks and 50 supply packs." << endl;
                trucks_used = 2;
                packs_used = 50;
                trucks -= 2;
                packs -= 50;
                successful_requests++;
            }
            else if (trucks >= 1 && packs >= 30) {
                cout << "Insufficient resources for full relief! Fallback: Standard relief (1 Truck and 30 supply packs)." << endl;
                trucks_used = 1;
                packs_used = 30;
                trucks -= 1;
                packs -= 30;
                successful_requests++;
            }
            else if (trucks >= 1 && packs >= 10) {
                cout << "Insufficient resources for standard relief! Fallback: Emergency kit (1 Truck and 10 supply packs)." << endl;
                trucks_used = 1;
                packs_used = 10;
                trucks -= 1;
                packs -= 10;
                successful_requests++;
            }
            else {
                cout << "Defer: insufficient resources" << endl;
                deferred_requests++;
            }
        }
        else if (total_score > 50 && total_score <= 75) {
            if (trucks >= 1 && packs >= 30) {
                cout << "Standard relief: 1 Truck and 30 supply packs." << endl;
                trucks_used = 1;
                packs_used = 30;
                trucks -= 1;
                packs -= 30;
                successful_requests++;
            }
            else if (trucks >= 1 && packs >= 10) {
                cout << "Insufficient resources for standard relief! Fallback: Emergency kit (1 Truck and 10 supply packs)." << endl;
                trucks_used = 1;
                packs_used = 10;
                trucks -= 1;
                packs -= 10;
                successful_requests++;
            }
            else {
                cout << "Defer: insufficient resources" << endl;
                deferred_requests++;
            }
        }
        else if (total_score >= 25 && total_score <= 50) {
            if (trucks >= 1 && packs >= 10) {
                cout << "Sending emergency kit only: 1 Truck and 10 supply packs." << endl;
                trucks_used = 1;
                packs_used = 10;
                trucks -= 1;
                packs -= 10;
                successful_requests++;
            }
            else {
                cout << "Defer: insufficient resources" << endl;
                deferred_requests++;
            }
        }
        else {
            cout << "Defer: no aid" << endl;
            deferred_requests++;
        }

        cout << "Resources used for this request:" << endl;
        cout << "Trucks used: " << trucks_used << endl;
        cout << "Supply packs used: " << packs_used << endl;
        cout << endl;
        cout << "Remaining resources:" << endl;
        cout << "Trucks: " << trucks << endl;
        cout << "Supply packs: " << packs << endl;
        cout << endl;
    }

    // END OF EXECUTION SUMMARY 
    cout << "==============SUMMARY==================" << endl;
    cout << "Total requests: " << requests_count << endl;
    cout << "Successful requests: " << successful_requests << endl;
    cout << "Deferred requests: " << deferred_requests << endl;
    cout << "Trucks left after " << requests_count << " request/s : " << trucks << endl;
    cout << "Supply packs left after " << requests_count << " request/s : " << packs << endl;

    return 0;
}