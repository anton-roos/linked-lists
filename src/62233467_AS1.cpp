// Student Name: Frederick Antonie Roos
// Student Number: 62233467
// COS2611 Assignment 1

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <random>
#include <string>
#include <map>
#include <array>

using namespace std;

// Data structures

// One row of the final "Generated Orders" report.
struct OrderLogEntry {
    int  time;
    char type;
    int  processing_time;
};

// Output helpers

// Print a queue's contents in the form "Queue X: [X(t), X(t), ...]". The queue
// is taken by value so we can drain it without disturbing the simulation.
void printQueue(char type, queue<int> q) {
    cout << "Queue " << type << ": [";
    bool first = true;
    while (!q.empty()) {
        if (!first) cout << ", ";
        cout << type << "(" << q.front() << ")";
        q.pop();
        first = false;
    }
    cout << "]\n";
}

// Print the dispatched truck stack from top (last dispatched) to bottom.
void printStack(stack<string> s) {
    if (s.empty()) {
        cout << "Stack: empty\n";
        return;
    }
    cout << "Stack of Dispatched Trucks:\n";
    cout << "  Top -> " << s.top() << "\n";
    s.pop();
    while (!s.empty()) {
        cout << "         " << s.top() << "\n";
        s.pop();
    }
    cout << "  Bottom\n";
}


int main() {
    // Initialize simulation parameters
    constexpr int time_steps     = 30;
    constexpr int truck_capacity = 5;
    constexpr array<char, 3> order_types{'S', 'M', 'B'};

    // Queues for each order type (holding the processing_time of each order).
    queue<int> Queue_S;
    queue<int> Queue_M;
    queue<int> Queue_B;

    // Stack for dispatched trucks, holding labels like "Truck1[S]".
    stack<string> TruckStack;

    // Per-type truck counters and per-type processed counters.
    map<char, int> truck_counters {{'S', 0}, {'M', 0}, {'B', 0}};
    map<char, int> processed_count{{'S', 0}, {'M', 0}, {'B', 0}};

    // Log all generated orders for the final report.
    vector<OrderLogEntry> OrderLog;

    // Random generators (Mersenne Twister seeded from random_device).
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> arrivalDist(0, 3); // arrivals per step
    uniform_int_distribution<int> typeDist(0, 2);    // 0=S, 1=M, 2=B
    uniform_int_distribution<int> procDist(1, 4);    // processing time

    cout << "=== Warehouse Order Dispatch Simulation ===\n";
    cout << "Time steps: " << time_steps
         << ", Truck capacity: " << truck_capacity << "\n\n";
    
    // Simulation loop
    for (int time = 1; time <= time_steps; ++time) {

        // Generate new random orders
        int num_new_orders = arrivalDist(gen);
        vector<char> newArrivals;
        newArrivals.reserve(num_new_orders);

        for (int i = 0; i < num_new_orders; ++i) {
            char order_type      = order_types[typeDist(gen)];
            int  processing_time = procDist(gen);

            // Add to appropriate queue.
            if      (order_type == 'S') Queue_S.push(processing_time);
            else if (order_type == 'M') Queue_M.push(processing_time);
            else if (order_type == 'B') Queue_B.push(processing_time);

            // Log the order.
            OrderLog.push_back({time, order_type, processing_time});
            newArrivals.push_back(order_type);
        }

        // Process queues
        for (char queue_type : order_types) {
            // Pick the queue corresponding to this type.
            queue<int>* q = nullptr;
            if      (queue_type == 'S') q = &Queue_S;
            else if (queue_type == 'M') q = &Queue_M;
            else                        q = &Queue_B;

            if (!q->empty()) {
                // Decrement the front order's processing_time by 1.
                q->front()--;

                if (q->front() <= 0) {
                    // Remove the front order from the queue.
                    q->pop();
                    processed_count[queue_type]++;

                    // Check if the truck for this type is full.
                    if (processed_count[queue_type] >= truck_capacity) {
                        truck_counters[queue_type]++;
                        string label = "Truck"
                            + to_string(truck_counters[queue_type])
                            + "[" + string(1, queue_type) + "]";
                        TruckStack.push(label);
                        processed_count[queue_type] = 0;
                    }
                }
            }
        }

        // Display current state
        cout << "Time Step: " << time << "\n";

        // Print new arrivals.
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

        // Print queue states.
        printQueue('S', Queue_S);
        printQueue('M', Queue_M);
        printQueue('B', Queue_B);

        // Print dispatched trucks stack (top first).
        printStack(TruckStack);

        cout << "\n";
    }
    
    // Print final generated orders tabel
    cout << "time_step,type,processing_time\n";
    for (const auto& o : OrderLog) {
        cout << o.time << "," << o.type << "," << o.processing_time << "\n";
    }

    return 0;
}
