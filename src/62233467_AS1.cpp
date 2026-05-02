// Student Name: Frederick Antonie Roos
// Student Number: 62233467
// COS2611 Assignment 1

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <random>
#include <string>
#include <array>
using namespace std;

// Data structures

// A single order arriving at the warehouse.
struct Order {
    char type; // 'S', 'M', or 'B'
    int  remaining; // remaining processing time (decremented each step)
    int  processing_time; // original processing time (kept for the final report)
    int  time_step; // time step at which the order arrived
};

// A truck being filled or already dispatched.
struct Truck {
    int  number; // per-type sequence number: Truck1[S], Truck2[S], ...
    char type; // type of orders this truck carries
    vector<Order> orders;
};

// Output helpers (queues / stack are passed by value so we can drain them
// for printing without disturbing the live simulation state).
void printQueue(const string& label, queue<Order> q) {
    cout << "Queue " << label << ": [";
    bool first = true;
    while (!q.empty()) {
        if (!first) cout << ", ";
        cout << q.front().type << "(" << q.front().remaining << ")";
        q.pop();
        first = false;
    }
    cout << "]\n";
}

void printStack(stack<Truck> s) {
    if (s.empty()) {
        cout << "Stack: empty\n";
        return;
    }
    cout << "Stack of Dispatched Trucks:\n";
    cout << "  Top -> Truck" << s.top().number << "[" << s.top().type << "]\n";
    s.pop();
    while (!s.empty()) {
        cout << "         Truck" << s.top().number << "[" << s.top().type << "]\n";
        s.pop();
    }
    cout << "  Bottom\n";
}

// Simulation logic
// Decrement the front order's remaining time by one. When it hits zero, load
// it onto the current truck for that type. If the truck is full, dispatch it
// onto the LIFO stack and start a new truck with the next number.
void processQueue(queue<Order>& q,
                  Truck&             currentTruck,
                  stack<Truck>& dispatched,
                  int&               truckCounter,
                  int                truckCapacity) {
    if (q.empty()) return;

    q.front().remaining--;

    if (q.front().remaining <= 0) {
        Order completed = q.front();
        q.pop();
        currentTruck.orders.push_back(completed);

        if (static_cast<int>(currentTruck.orders.size()) >= truckCapacity) {
            dispatched.push(currentTruck);
            truckCounter++;
            currentTruck.number = truckCounter;
            currentTruck.orders.clear();
        }
    }
}

// Route a freshly generated order to the queue matching its type.
void enqueueOrder(const Order& o,
                  queue<Order>& qS,
                  queue<Order>& qM,
                  queue<Order>& qB) {
    switch (o.type) {
        case 'S': qS.push(o); break;
        case 'M': qM.push(o); break;
        case 'B': qB.push(o); break;
    }
}
  
int main() {
    // Simulation parameters. 
    // TRUCK_CAPACITY is configurable, change this single constant to retune the system.
    constexpr int TIME_STEPS     = 30;
    constexpr int TRUCK_CAPACITY = 5;

    // Three FIFO queues, one per order type.
    queue<Order> queueS, queueM, queueB;

    // LIFO stack of dispatched trucks.
    stack<Truck> dispatchedTrucks;

    // Per-type truck counters and the truck currently being filled.
    int   truckCountS = 1, truckCountM = 1, truckCountB = 1;
    Truck currentTruckS{1, 'S', {}};
    Truck currentTruckM{1, 'M', {}};
    Truck currentTruckB{1, 'B', {}};

    // Record of every generated order for the final report.
    vector<Order> allOrders;

    // Random generators (Mersenne Twister seeded from random_device).
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> arrivalDist(0, 3); // arrivals per step
    uniform_int_distribution<int> typeDist(0, 2);    // 0=S, 1=M, 2=B
    uniform_int_distribution<int> procDist(1, 4);    // processing time

    constexpr array<char, 3> types{'S', 'M', 'B'};

    cout << "=== Warehouse Order Dispatch Simulation ===\n";
    cout << "Time steps: " << TIME_STEPS
              << ", Truck capacity: " << TRUCK_CAPACITY << "\n\n";

    for (int t = 1; t <= TIME_STEPS; ++t) {
        cout << "--------------------------------------------\n";
        cout << "Time Step " << t << ":\n";

        // 1. Process the current front of each queue first, so that an order
        // arriving at step T is shown with its full processing time at T
        // and is only decremented from T+1 onward.
        processQueue(queueS, currentTruckS, dispatchedTrucks, truckCountS, TRUCK_CAPACITY);
        processQueue(queueM, currentTruckM, dispatchedTrucks, truckCountM, TRUCK_CAPACITY);
        processQueue(queueB, currentTruckB, dispatchedTrucks, truckCountB, TRUCK_CAPACITY);

        // 2. Generate 0 to 3 new arrivals.
        int numArrivals = arrivalDist(gen);
        vector<char> newArrivals;
        newArrivals.reserve(numArrivals);

        for (int i = 0; i < numArrivals; ++i) {
            char type = types[typeDist(gen)];
            int  proc = procDist(gen);
            Order o{type, proc, proc, t};
            allOrders.push_back(o);
            newArrivals.push_back(type);
            enqueueOrder(o, queueS, queueM, queueB);
        }

        // 3. Display new arrivals for this time step.
        cout << "New Orders: ";
        if (newArrivals.empty()) {
            cout << "none";
        } else {
            for (size_t i = 0; i < newArrivals.size(); ++i) {
                if (i > 0) cout << ", ";
                cout << newArrivals[i];
            }
        }
        cout << "\n";

        // 4. Display the state of all queues and the dispatched stack.
        printQueue("S", queueS);
        printQueue("M", queueM);
        printQueue("B", queueB);
        printStack(dispatchedTrucks);
        cout << "\n";
    }

    // Final reporting (bonus: enhanced output / reporting).
    cout << "Final Dispatched Trucks Stack:\n";
    printStack(dispatchedTrucks);

    const size_t totalDispatched = dispatchedTrucks.size();
    const size_t inQueues = queueS.size() + queueM.size() + queueB.size();
    const size_t inProgress = currentTruckS.orders.size() + currentTruckM.orders.size() + currentTruckB.orders.size();

    cout << "\nSummary:\n";
    cout << "  Total orders generated: " << allOrders.size() << "\n";
    cout << "  Total trucks dispatched: " << totalDispatched << "\n";
    cout << "  Orders still waiting in queues: " << inQueues << "\n";
    cout << "  Orders loaded on undispatched trucks: " << inProgress << "\n";

    // Final CSV-style table of every generated order.
    cout << "Final Generated Orders Table:\n";
    cout << "time_step,type,processing_time\n";
    for (const auto& o : allOrders) {
        cout << o.time_step << "," << o.type << "," << o.processing_time << "\n";
    }

    return 0;
}
