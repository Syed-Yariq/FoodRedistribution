#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>

using namespace std;

//Stack Template
template <typename T>
class Stack {
private:
    vector<T> data;

public:
    void push(const T& value);
    void pop();
    T top();
    bool isEmpty();
    size_t size();
    void display();
    void clear();
};

//Queue Template
template <typename T>
class Queue {
private:
    T arr[100];     
    int front, rear;

public:
    Queue();     
    void enqueue(const T& value);
    void dequeue();
    T frontItem();
    bool isEmpty();
    size_t size();
    void display();
    void clear();
};
//Request Class
class Request {
public:
    string recipientName;
    string foodType;
    int quantity;
    bool isUrgent;
    bool isFulfilled;
    string requestDate;
    string organizationType;  
    string organizationName;  
    string location;          
    int priorityLevel;        


    Request(); // default constructor
    Request(string name, string food, int qty, string orgType, string orgName, string loc, string date);
    bool operator<(const Request& other) const; // for priority queue
    string getFoodType() const { return foodType; }
    int getQuantity() const { return quantity; }
    string getRequestDate() const { return requestDate; }
    string getRecipientName() const { return recipientName; }

};


//Priority Queue
template <typename T>
class PriorityQueue {
private:
    priority_queue<T> pq;

public:
    void push(const T& value);
    void pop();
    T top();
    bool isEmpty();
    size_t size();
    void display();
};

//Graph 
template <typename T>
class Graph {
private:
    unordered_map<T, vector<pair<T, int>>> adj; // node -> [(neighbor, weight)]

public:
	void addNode(T node);
    void addEdge(T u, T v, int w);
    void display();
};

// ------------------- Donor Class -------------------
class Donor {
private:
    int donorId;            // Unique ID for donor
    string donorName;       // Name of person or organization
    string contactInfo;     // Phone/email
    string donorType;       // "Individual" or "Organization"
    string address;         // Optional, location of donor

public:
    Donor(int id = 0, string name = "", string contact = "", string type = "Individual", string addr = "");

    int getDonorId() const;
    string getDonorName() const;
    string getContactInfo() const;
    string getDonorType() const;
    string getAddress() const;

    void displayDonor() const;
};

// ------------------- Donor Node -------------------
class DonorNode {
public:
    Donor data;
    DonorNode* next;

    DonorNode(Donor d);
};

// ------------------- Donor Linked List -------------------
class DonorLinkedList {
private:
    DonorNode* head;

public:
    DonorLinkedList();

    void addDonor(Donor d);
    Donor* searchDonor(int id);
    bool removeDonor(int id);
    void displayDonors() const;

};

// ------------------- FoodDonation Class -------------------
class FoodDonation {
private:
    int donationId;      // Unique donation ID
    int donorId;         // Link to Donor
    string foodType;     // e.g., "Rice", "Vegetables"
    int quantity;        // Quantity in kg or units
    string expiryDate;   // Expiry date (if applicable)
    string status;       //Pending or Completed

public:
    FoodDonation(int dId = 0, int drId = 0, string type = "", int qty = 0, string date = "", string stat = "Pending" );

    int getDonationId() const;
    int getDonorId() const;
    string getFoodType() const;
    int getQuantity() const;
    string getExpiryDate() const;
    string getStatus() const;      
    void setStatus(string newStatus);

    void reduceQuantity(int usedQty);
    void displayDonation() const;

};

// ------------------- Donation Node -------------------
class DonationNode {
public:
    FoodDonation data;
    DonationNode* next;

    DonationNode(FoodDonation d);
};

// ------------------- Donation Linked List -------------------
class DonationLinkedList {
private:
    DonationNode* head;

public:
    DonationLinkedList();

    void addDonation(FoodDonation d);
    bool removeDonation(int donationId);
    FoodDonation* searchDonation(int donationId);
    void displayDonations() const;
    void displayDonationsByDonor(int donorId) const;  // Show all donations by a specific donor
    void displayDonationItemsOnly() const;
    void removeExpiredDonations(const string& todayDate);
    FoodDonation* findMatchingDonation(const string& foodTypeNeeded,
        int quantityNeeded,
        const string& requestDate,
        const Request& request);
};

//roads
template <typename T>   
class Roads {
private:
    unordered_map<T, vector<pair<T, int>>> roadMap; // node -> [(neighbor, weight)]

public:
    void addRoad(T from, T to, int distance);
    void addLocation(T node);
    void shortestPath(T start, T end);
};


//Include so compiler can see it at compile time (code above this, dont code after it)
#include "redistribution.cpp"
