#include <stdexcept>
#include "Redistribution.hpp"

using namespace std;

// trim function 
string trim(const string& s) {
    string t = s;
    while (!t.empty() && (t.back() == ' ' || t.back() == '\r' || t.back() == '\n' || t.back() == '\t'))
        t.pop_back();
    size_t i = 0;
    while (i < t.size() && (t[i] == ' ' || t[i] == '\r' || t[i] == '\n' || t[i] == '\t'))
        i++;
    return t.substr(i);
}

//Stack
template <typename T>
void Stack<T>::push(const T& value) { data.push_back(value); }

template <typename T>
void Stack<T>::pop() {
    if (data.empty()) throw out_of_range("Stack is empty");
    data.pop_back();
}

template <typename T>
T Stack<T>::top() {
    if (data.empty()) throw out_of_range("Stack is empty");
    return data.back();
}

template <typename T>
bool Stack<T>::isEmpty() { 
    return data.empty();
}

template <typename T>
size_t Stack<T>::size() {
    return data.size(); 
}

template <typename T>
void Stack<T>::display() {
    for (const auto& item : data) cout << item << " ";
    cout << endl;
}

template <typename T>
void Stack<T>::clear() { 
    data.clear();
}


//Queue
template <typename T>
Queue<T>::Queue() {
    front = 0;
    rear = 0;
}

template <typename T>
void Queue<T>::enqueue(const T& value) {
    if (rear < 100) {
        arr[rear++] = value;
    }
    else {
        cout << "Queue is full.\n";
    }
}

template <typename T>
void Queue<T>::dequeue() {
    if (!isEmpty()) {
        front++;
    }
    else {
        cout << "Queue is empty.\n";
    }
}

template <typename T>
T Queue<T>::frontItem() {
    if (!isEmpty()) {
        return arr[front];
    }
    else {
        throw out_of_range("Queue is empty");
    }
}

template <typename T>
bool Queue<T>::isEmpty() {
    return front == rear;
}

template <typename T>
size_t Queue<T>::size() {
    return rear - front;
}

template <typename T>
void Queue<T>::display() {
    for (int i = front; i < rear; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

template <typename T>
void Queue<T>::clear() {
    front = 0;
    rear = 0;
}
//----------------RequestClass--------------
Request::Request() {
    recipientName = "";
    foodType = "";
    quantity = 0;
    organizationType = "";
    organizationName = "";
    location = "";
    priorityLevel = 3;
    isFulfilled = false;
    requestDate = "";
}

Request::Request(string name, string food, int qty, string orgType, string orgName, string loc, string date) {
    recipientName = name;
    foodType = food;
    quantity = qty;
    organizationType = orgType;
    organizationName = orgName;
    location = loc;
    isFulfilled = false;
    requestDate = date;
    isUrgent = false;

    for (char& c : organizationType) c = toupper(c);

    if (organizationType == "HOSPITAL") priorityLevel = 1;
    else if (organizationType == "OLDAGE HOME") priorityLevel = 2;
    else if (organizationType == "CHARITY") priorityLevel = 3;
    else priorityLevel = 4;

    isUrgent = (priorityLevel == 1);
}

bool Request::operator<(const Request& other) const {
    return priorityLevel > other.priorityLevel;
}

template <>
void Queue<Request>::display() {
    for (int i = front; i < rear; i++) {
        cout << i << ". " << arr[i].recipientName << " from " << arr[i].organizationName << " (" << arr[i].organizationType << ") wants "
            << arr[i].quantity << " of " << arr[i].foodType
            << (arr[i].isUrgent ? " [URGENT]" : "")
            << (arr[i].isFulfilled ? " [FULFILLED]" : " [PENDING]")
            << endl;
    }
}

//PriorityQueue
template <typename T>
void PriorityQueue<T>::push(const T& value) { pq.push(value); }

template <typename T>
void PriorityQueue<T>::pop() {
    if (pq.empty()) throw out_of_range("Priority queue is empty");
    pq.pop();
}

template <typename T>
T PriorityQueue<T>::top() {
    if (pq.empty()) throw out_of_range("Priority queue is empty");
    return pq.top();
}

template <typename T>
bool PriorityQueue<T>::isEmpty() { 
    return pq.empty(); 
}

template <typename T>
size_t PriorityQueue<T>::size() { return pq.size(); }

template <>
void PriorityQueue<Request>::display() {
    if (pq.empty()) {
        cout << "No requests available.\n";
        return;
    }

    priority_queue<Request> temp = pq;
    int i = 0;
    while (!temp.empty()) {
        Request r = temp.top();
        cout << i++ << ". " << r.recipientName << " from " << r.organizationName
            << " (" << r.organizationType << ", " << r.location << ") wants "
            << r.quantity << " of " << r.foodType
            << " [Priority: " << r.priorityLevel << "] "
            << (r.isFulfilled ? "[FULFILLED]" : "[PENDING]") << endl;
        temp.pop();
    }
}
//display fullfiled stack 
template <>
void Stack<Request>::display() {
    for (const auto& r : data) {
        cout << r.recipientName << " from " << r.organizationName
            << " (" << r.organizationType << ", " << r.location << ") received "
            << r.quantity << " of " << r.foodType
            << " [Priority: " << r.priorityLevel << "]\n";
    }
}

//Graph
template <typename T>
void Graph<T>::addEdge(T u, T v, int w) {
    adj[u].push_back({ v, w });
    adj[v].push_back({ u, w });
}
template <typename T>
void Graph<T>::addNode(T node) {
    // Only add the node if it doesn't already exist
    if (adj.find(node) == adj.end()) {
        adj[node] = {}; // create empty adjacency list
        cout << "Node added: " << node << endl;
    }
    else {
        cout << "Node already exists: " << node << endl;
    }
}
template <typename T>
void Graph<T>::display() {
    for (auto& node : adj) {
        cout << node.first << " -> ";
        for (auto& edge : node.second)
            cout << "(" << edge.first << ", " << edge.second << ") ";
        cout << endl;
    }
}


// ---------------- Donor Implementation ----------------
Donor::Donor(int id, string name, string contact, string type, string addr)
{
    donorId = id;
    donorName = name;
    contactInfo = contact;
    donorType = type;
    address = addr;
}

int Donor::getDonorId() const
{
    return donorId;
}

string Donor::getDonorName() const
{
    return donorName;
}

string Donor::getContactInfo() const
{
    return contactInfo;
}

string Donor::getDonorType() const
{
    return donorType;
}

string Donor::getAddress() const
{
    return address;
}

void Donor::displayDonor() const
{
    cout << "Donor ID: " << donorId
        << ", Name: " << donorName
        << ", Type: " << donorType
        << ", Contact: " << contactInfo
        << ", Address: " << address
        << endl;
}

// ---------------- DonorNode ----------------
DonorNode::DonorNode(Donor d)
{
    data = d;
    next = nullptr;
}

// ---------------- DonorLinkedList ----------------
DonorLinkedList::DonorLinkedList()
{
    head = nullptr;
}

void DonorLinkedList::addDonor(Donor d)
{
    DonorNode* newNode = new DonorNode(d);

    if (!head)
    {
        head = newNode;
        return;
    }

    DonorNode* temp = head;
    while (temp->next)
    {
        temp = temp->next;
    }

    temp->next = newNode;
}

Donor* DonorLinkedList::searchDonor(int id)
{
    DonorNode* temp = head;
    while (temp)
    {
        if (temp->data.getDonorId() == id)
            return &(temp->data);

        temp = temp->next;
    }
    return nullptr;
}

bool DonorLinkedList::removeDonor(int id)
{
    if (!head)
        return false;
    if (head->data.getDonorId() == id)
    {
        DonorNode* toDelete = head;
        head = head->next;
        delete toDelete;
        return true;
    }
    DonorNode* temp = head;
    while (temp->next && temp->next->data.getDonorId() != id)
    {
        temp = temp->next;
    }
    if (!temp->next)
        return false;

    DonorNode* toDelete = temp->next;
    temp->next = temp->next->next;
    delete toDelete;
    return true;
}

void DonorLinkedList::displayDonors() const
{
    if (head == nullptr) {
        cout << "\nNo donors to display." << endl;
    }
    DonorNode* temp = head;
    while (temp)
    {
        temp->data.displayDonor();
        temp = temp->next;
    }
}

// ---------------- FoodDonation ----------------
FoodDonation::FoodDonation(int dId, int drId, string type, int qty, string date, string stat)
{
    donationId = dId;
    donorId = drId;
    foodType = type;
    quantity = qty;
    expiryDate = date;
    status = stat;
}

int FoodDonation::getDonationId() const
{
    return donationId;
}
int FoodDonation::getDonorId() const
{
    return donorId;
}
string FoodDonation::getFoodType() const
{
    return foodType;
}
int FoodDonation::getQuantity() const
{
    return quantity;
}
string FoodDonation::getExpiryDate() const
{
    return expiryDate;
}
string FoodDonation::getStatus() const
{
    return status;
}
void FoodDonation::setStatus(string newStatus)
{
    status = newStatus;
}


void FoodDonation::displayDonation() const
{
    cout << "Donation ID: " << donationId
        << ", Donor ID: " << donorId
        << ", Food: " << foodType
        << ", Quantity: " << quantity
        << ", Expiry: " << expiryDate
        << ", Status: " << status
        << endl;
}

void FoodDonation::reduceQuantity(int usedQty) {
    quantity -= usedQty;
    if (quantity <= 0) {
        quantity = 0;
        status = "Completed";
    }
}

// ---------------- DonationNode ----------------
DonationNode::DonationNode(FoodDonation d)
{
    data = d;
    next = nullptr;
}
// ---------------- DonationLinkedList ----------------
DonationLinkedList::DonationLinkedList()
{
    head = nullptr;
}

void DonationLinkedList::addDonation(FoodDonation d)
{
    DonationNode* newNode = new DonationNode(d);
    if (!head)
    {
        head = newNode;
        return;
    }
    DonationNode* temp = head;
    while (temp->next)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

FoodDonation* DonationLinkedList::searchDonation(int donationId)
{
    DonationNode* temp = head;
    while (temp)
    {
        if (temp->data.getDonationId() == donationId)
            return &(temp->data);
        temp = temp->next;
    }
    return nullptr;
}

bool DonationLinkedList::removeDonation(int donationId)
{
    if (!head)
        return false;
    if (head->data.getDonationId() == donationId)
    {
        DonationNode* toDelete = head;
        head = head->next;
        delete toDelete;
        return true;
    }
    DonationNode* temp = head;
    while (temp->next && temp->next->data.getDonationId() != donationId)
    {
        temp = temp->next;
    }
    if (!temp->next)
        return false;

    DonationNode* toDelete = temp->next;
    temp->next = temp->next->next;
    delete toDelete;
    return true;
}

void DonationLinkedList::displayDonations() const
{
    if (head == nullptr) {
        cout << "\nNo donations to display." << endl;
    }
    DonationNode* temp = head;
    while (temp)
    {
        temp->data.displayDonation();
        temp = temp->next;
    }
}


void DonationLinkedList::displayDonationsByDonor(int donorId) const
{
    DonationNode* temp = head;
    bool found = false;
    while (temp)
    {
        if (temp->data.getDonorId() == donorId)
        {
            temp->data.displayDonation();
            found = true;
        }
        temp = temp->next;
    }
    if (!found)
        cout << "No donations found for donor ID: " << donorId << endl;
}

// to covert in lowercase
string toLower(const string& s) {
    string result = s;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}
FoodDonation* DonationLinkedList::findMatchingDonation(const string& foodTypeNeeded, int quantityNeeded, const string& requestDate, const Request& request)
{
    if (head == nullptr) {
        return nullptr;
    }

    string neededLower = toLower(foodTypeNeeded);
    DonationNode* temp = head;

    while (temp != nullptr) {
        FoodDonation& d = temp->data;

        // Food type mismatch
        if (toLower(d.getFoodType()) != neededLower) {
            temp = temp->next;
            continue;
        }

        // Insufficient quantity
        if (d.getQuantity() < quantityNeeded) {
            cout <<  request.recipientName
                << " (" << request.organizationName
                << "): insufficient quantity (need: " << quantityNeeded
                << ", available: " << d.getQuantity() << ")\n";
            temp = temp->next;
            continue;
        }

        // Not pending
        if (d.getStatus() != "Pending") {
            cout << request.recipientName
                << " (" << request.organizationName
                << "): not available (status: " << d.getStatus() << ")\n";
            temp = temp->next;
            continue;
        }

        // Expired
        string expiry = trim(d.getExpiryDate());
        string reqDate = trim(requestDate);
        if (expiry <= reqDate) {
            cout << request.recipientName
                << " (" << request.organizationName
                << "): expired (" << expiry << " <= " << reqDate << ")\n";
            temp = temp->next;
            continue;
        }

        return &d;
    }
    return nullptr;
}
void DonationLinkedList::displayDonationItemsOnly() const {
    DonationNode* temp = head;
    if (!temp) {
        cout << "No donations available.\n";
        return;
    }
    cout << "Available Food Items:\n";
    while (temp) {
        cout << "- " << temp->data.getFoodType();
        cout << " : " << temp->data.getQuantity() << endl;
        temp = temp->next;
    }
}
void DonationLinkedList::removeExpiredDonations(const string& todayDate) {
    DonationNode* temp = head;
    DonationNode* prev = nullptr;

    while (temp != nullptr) {
        // expired if expiry <= today
        if (temp->data.getExpiryDate() <= todayDate) {
            cout << "Removing expired donation: " << temp->data.getFoodType()
                << " (Expiry: " << temp->data.getExpiryDate() << ")\n";

            // remove node
            if (prev == nullptr) {
                head = temp->next;
                delete temp;
                temp = head;
            }
            else {
                prev->next = temp->next;
                delete temp;
                temp = prev->next;
            }
        }
        else {
            prev = temp;
            temp = temp->next;
        }

    }
}

//Roads
template <typename T>
void Roads<T>::addLocation(T location) {
    if (roadMap.find(location) == roadMap.end()) {
        roadMap[location] = {};
        cout << "Location added: " << location << endl;
    }
    else {
        cout << "Location already exists: " << location << endl;
    }
}

template <typename T>
void Roads<T>::addRoad(T from, T to, int distance) {
    roadMap[from].push_back({ to, distance });
    roadMap[to].push_back({ from, distance });
}

template <typename T>
void Roads<T>::shortestPath(T start, T end) {
    // Dijkstra's algorithm implementation
    unordered_map<T, int> dist;
    unordered_map<T, T> prev;
    PriorityQueue<pair<int, T>> pq;

    for (const auto& loc : roadMap) {
        dist[loc.first] = INT_MAX;
        prev[loc.first] = T();
    }

    dist[start] = 0;
    pq.push({ 0, start });

    while (!pq.isEmpty()) {
        T current = pq.top().second;
        pq.pop();

        if (current == end) break;

        for (const auto& neighbor : roadMap[current]) {
            T next = neighbor.first;
            int weight = neighbor.second;

            int alt = dist[current] + weight;
            if (alt < dist[next]) {
                dist[next] = alt;
                prev[next] = current;
                pq.push({ alt, next });
            }
        }
    }

    // Reconstruct path
    vector<T> path;
    for (T at = end; at != T(); at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    // Display path
    if (dist[end] == INT_MAX) {
        cout << "No path from " << start << " to " << end << endl;
    }
    else {
        cout << "Shortest path from " << start << " to " << end << ": ";
        for (const auto& loc : path) {
            cout << loc << " ";
        }
        cout << "(Distance: " << dist[end] << ")" << endl;
    }
}

