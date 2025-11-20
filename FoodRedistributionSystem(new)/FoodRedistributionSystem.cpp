#include "redistribution.hpp"
#include <iostream>


using namespace std;

DonorLinkedList donors;
DonationLinkedList donations;
PriorityQueue<Request> requestPQ;
Queue<Request> pendingQueue;       
Stack<Request> fulfilledStack;

int main() {
   
    int choice;
    do {
        cout << "==================================================" << endl;
        cout << "     FOOD REDISTRIBUTION SYSTEM - MAIN MENU     " << endl;
        cout << "==================================================" << endl << endl;

        cout << "1. Donor Management" << endl;
        cout << "2. Donation Management" << endl;
        cout << "3. Request Management" << endl;
        cout << "4. Recipient Reports" << endl;
        cout << "5. Exit" << endl << endl;

        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        // 1. DONOR MANAGEMENT
        if (choice == 1) {
            int sub;
            do {
                cout << "--- DONOR MANAGEMENT ---\n\n";
                cout << "1. Add New Donor\n";
                cout << "2. Display All Donors\n";
                cout << "3. Search Donor\n";
                cout << "4. Remove Donor\n";
                cout << "5. Back to Main Menu\n\n";
                cout << "Enter choice: ";
                cin >> sub; cin.ignore();

                if (sub == 1) {
                    int id; string name, contact, type, address;
                    cout << "Enter Donor ID: ";
                    cin >> id; 
                    cin.ignore();
                    cout << "Donor Name: "; 
                    getline(cin, name);
                    cout << "Contact Info: "; getline(cin, contact);
                    cout << "Donor Type (Indivisual / Organization): "; getline(cin, type);
                    cout << "Address: "; getline(cin, address);
                    Donor d(id, name, contact, type, address);
                    donors.addDonor(d);
                    cout << "Donor added successfully!\n";
                }
                else if (sub == 2) {
                    cout << "\n--- ALL DONORS ---\n";
                    donors.displayDonors();
                }
                else if (sub == 3) {
                    int id; cout << "Enter Donor ID: "; cin >> id;
                    cout << (donors.searchDonor(id) ? "\nDonor FOUND!\n" : "\nDonor not found!\n");
                }
                else if (sub == 4) {
                    int id; cout << "\nEnter Donor ID to remove: "; cin >> id;
                    cout << (donors.removeDonor(id) ? "\nDonor removed successfully!\n" : "\nDonor not found!\n");
                }
                else if (sub == 5) {
                    cout << "\nReturning to menu...\n";
                }
                else {
                    cout << "\nInvalid option!\n";
                }
                if (sub != 5) {
                    cout << "Returning to Main menu\n";
                }
            } while (sub != 5);
        }
        // 2. DONATION MANAGEMENT
        else if (choice == 2) {
            int sub;
            do {
                cout << "\n--- DONATION MANAGEMENT ---\n\n";
                cout << "1. Add New Donation\n";
                cout << "2. View All Donations\n";
                cout << "3. View Donations by Donor\n";
                cout << "4. Mark Donation as Completed\n";
                cout << "5. Remove Expired Donations\n";
                cout << "6. Back to Main Menu\n\n";
                cout << "Enter choice: ";
                cin >> sub; cin.ignore();

                if (sub == 1) {
                    int donationId, donorId, quantity; string foodType, expiry;
                    cout << "\nEnter Donation ID: "; cin >> donationId;
                    cout << "Enter Donor ID: "; cin >> donorId;
                    if (!donors.searchDonor(donorId)) {
                        cout << "\nDonor not found! Cannot add donation.\n";
                    }
                    else {
                        cin.ignore();
                        cout << "Food Type: "; getline(cin, foodType);
                        cout << "Quantity: "; cin >> quantity; cin.ignore();
                        cout << "Expiry Date (YYYY-MM-DD): "; getline(cin, expiry);
                        FoodDonation f(donationId, donorId, foodType, quantity, expiry, "Pending");
                        donations.addDonation(f);
                        cout << "\nDonation added successfully!\n";
                    }
                }
                else if (sub == 2) {
                    cout << "\n--- ALL DONATIONS ---\n";
                    donations.displayDonations();
                }
                else if (sub == 3) {
                    int id; cout << "\nEnter Donor ID: "; cin >> id;
                    cout << "\n--- Donations by Donor " << id << " ---\n";
                    donations.displayDonationsByDonor(id);
                }
                else if (sub == 4) {
                    int id; cout << "\nEnter Donation ID: "; cin >> id;
                    FoodDonation* d = donations.searchDonation(id);
                    if (d) { d->setStatus("Completed"); cout << "\nStatus updated to Completed!\n"; }
                    else cout << "\nDonation not found!\n";
                }
                else if (sub == 5) {
                    string today; cout << "\nEnter today's date (YYYY-MM-DD): "; cin >> today;
                    donations.removeExpiredDonations(today);
                }
                else if (sub == 6) {
                    cout << "\nReturning to menu...\n";
                }
                else cout << "\nInvalid option!\n";

                if (sub != 6) {
                    cout << "Returning to Main menu\n";
                }
            } while (sub != 6);
        }

        // 3. REQUEST MANAGEMENT
        else if (choice == 3) {
            int sub;
            do {
                cout << "\n--- REQUEST MANAGEMENT ---\n\n";
                cout << "1. Add New Request\n";
                cout << "2. View Urgent Requests\n";
                cout << "3. Fulfill Urgent Requests (Priority Order)\n";
                cout << "4. View Pending Requests\n";
                cout << "5. Rebook a Pending Request\n";   
                cout << "6. Back to Main Menu\n\n";
                cout << "Enter choice: ";
                cin >> sub; cin.ignore();

                if (sub == 1) {
                    string name, food, orgType, orgName, loc, date; int qty;
                    cout << "\n=== ADD NEW REQUEST ===\n";
                    donations.displayDonationItemsOnly();
                    cout << "\n";
                    cout << "Recipient Name: "; getline(cin, name);
                    cout << "Food Type: "; getline(cin, food);
                    cout << "Quantity: "; cin >> qty; cin.ignore();
                    cout << "Organization Type (Hospital/OldAge Home/Charity): "; getline(cin, orgType);
                    cout << "Organization Name: "; getline(cin, orgName);
                    cout << "Location: "; getline(cin, loc);
                    cout << "Request Date (YYYY-MM-DD): "; getline(cin, date);

                    Request r(name, food, qty, orgType, orgName, loc, date);
                    requestPQ.push(r);
                    cout << "\nRequest added to URGENT queue successfully!\n";
                }
                else if (sub == 2) {
                    cout << "\n=== URGENT REQUESTS (Highest Priority First) ===\n";
                    if (requestPQ.isEmpty()) cout << "No urgent requests.\n\n";
                    else requestPQ.display();
                }
                else if (sub == 3) {
                    cout << "\n=== FULFILLING URGENT REQUESTS ===\n\n";
                    int fulfilled = 0;
                    while (!requestPQ.isEmpty()) {
                        Request r = requestPQ.top(); requestPQ.pop();
                        FoodDonation* match = donations.findMatchingDonation(r.foodType, r.quantity, r.requestDate, r);
                        if (match) {
                            match->reduceQuantity(r.quantity);
                            r.isFulfilled = true;
                            fulfilledStack.push(r);
                            fulfilled++;
                            cout << r.recipientName << " : " << r.quantity << " " << r.foodType
                                << " delivered successfully!\n";
                        }
                        else {
                            pendingQueue.enqueue(r);
                            break;
                        }
                    }
                    if (fulfilled > 0) {
                        cout << "SUCCESS: " << fulfilled << " request(s) fulfilled and delivered!\n\n";
                    }
                   
                    else if (!requestPQ.isEmpty())
                        cout << "No requests could be fulfilled (no matching stock).\n\n";
                    else
                        cout << "No urgent requests to process.\n\n";
                }
                else if (sub == 4) {
                    cout << "\n=== PENDING REQUESTS (Waiting for donations) ===\n";
                    if (pendingQueue.isEmpty()) {
                        cout << "No pending requests.\n\n";
                    }
                    else {
                        Queue<Request> temp = pendingQueue;
                        while (!temp.isEmpty()) {
                            Request r = temp.frontItem(); temp.dequeue();
                            cout << r.recipientName << " (" << r.organizationName << ") needs "
                                << r.quantity << " " << r.foodType << " {Waiting}\n";
                        }
                        cout << endl;
                    }
                }
                else if (sub == 5) {
    if (pendingQueue.isEmpty()) {
        cout << "\nNo pending requests to rebook.\n\n";
    }
    else {
        cout << "\n=== REBOOK A PENDING REQUEST ===\n";
        
        // Step 1: Show list with numbers
        Queue<Request> temp = pendingQueue;
        vector<Request> requests;
        int index = 1;
        
        cout << "Pending Requests:\n";
        cout << "----------------------------------------\n";
        while (!temp.isEmpty()) {
            Request r = temp.frontItem(); 
            temp.dequeue();
            cout << index << ". " << r.recipientName 
                 << " (" << r.organizationName << ") → "
                 << r.quantity << " " << r.foodType 
                 << " (Date: " << r.requestDate << ")\n";
            requests.push_back(r);
            index++;
        }
        cout << "----------------------------------------\n";

        int choice;
        cout << "\nEnter the number to rebook (1-" << (index-1) << ") or 0 to cancel: ";
        cin >> choice; 
        cin.ignore();

        if (choice < 1 || choice >= index) {
            cout << "\nRebook cancelled.\n\n";
        }
        else {
            // Save the old request to remove it later
            Request oldRequest = requests[choice - 1];

            // Step 2: Let user enter updated details
            string name, food, orgType, orgName, loc, date;
            int qty;

            cout << "\n=== ENTER UPDATED REQUEST DETAILS ===\n";
            donations.displayDonationItemsOnly();
            cout << "\n";
            cout << "Recipient Name       : "; getline(cin, name);
            cout << "Food Type            : "; getline(cin, food);
            cout << "Quantity             : "; cin >> qty; cin.ignore();
            cout << "Organization Type    : "; getline(cin, orgType);
            cout << "Organization Name    : "; getline(cin, orgName);
            cout << "Location             : "; getline(cin, loc);
            cout << "Request Date (YYYY-MM-DD): "; getline(cin, date);

            // Create new updated request
            Request newRequest(name, food, qty, orgType, orgName, loc, date);
            requestPQ.push(newRequest);

            // Step 3: Remove the old request from pending queue
            Queue<Request> cleanedQueue;
            temp = pendingQueue;
            while (!temp.isEmpty()) {
                Request r = temp.frontItem(); 
                temp.dequeue();
                // Skip the old one (compare name + org + date to be safe)
                if (!(r.recipientName == oldRequest.recipientName &&
                      r.organizationName == oldRequest.organizationName &&
                      r.requestDate == oldRequest.requestDate)) {
                    cleanedQueue.enqueue(r);
                }
            }
            pendingQueue = cleanedQueue;

            cout << "\nRequest successfully REBOOKED !\n";
        }
    }
}
                else if (sub == 6) {
                    cout << "\nReturning to menu...\n";
                }
                else cout << "\nInvalid option!\n";

            } while (sub != 6);
        }

        // 4. RECIPIENT REPORTS
else if (choice == 4) {
    cout << "\n==================================================" << endl;
    cout << "       RECIPIENT REPORTS & STATISTICS            " << endl;
    cout << "==================================================\n\n";

    // FULFILLED REQUESTS (Latest First)
    cout << "FOOD DELIVERED TO RECIPIENTS\n";
    cout << "--------------------------------------------------\n";

    if (fulfilledStack.isEmpty()) {
        cout << "No food delivered yet.\n\n";
    }
    else {
        Stack<Request> temp = fulfilledStack;
        int count = 1;
        while (!temp.isEmpty()) {
            Request r = temp.top();
            temp.pop();
            cout << count++ << ". Delivered "
                << r.quantity << " " << r.foodType
                << " : " << r.recipientName
                << " (" << r.organizationName
                << ", " << r.organizationType << ")"
                << " on " << r.requestDate << endl;
        }
        cout << endl;
    }

    // STATISTICS
    cout << "CURRENT SYSTEM STATISTICS\n";
    cout << "--------------------------------------------------\n";
    cout << "Urgent Requests     : " << requestPQ.size() << endl;
    cout << "Pending Requests    : " << pendingQueue.size() << endl;
    cout << "Total Delivered     : " << fulfilledStack.size() << endl;
    cout << "--------------------------------------------------\n";
    cout << "Grand Total Requests: " << (requestPQ.size() + pendingQueue.size() + fulfilledStack.size()) << endl << endl;

    cout << "Returning to menu...\n\n";
}
        // 5. EXIT
        // ========================================
        else if (choice == 5) {
            cout << "\nThank you for using Food Redistribution System!\n";
            cout << "Together, we are reducing hunger and food waste.\n\n";
        }
        else {
            cout << "\nInvalid choice! Please enter 1 to 5.\n";
            cout  << "Returning to Main menu\n";
        }

    } while (choice != 5);

    return 0;
}