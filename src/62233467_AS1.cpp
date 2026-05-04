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

// Data structure for one row of the final orders report
struct OrderLogEntry {
    int  time;
    char type;
    int  processing_time;
};

// Print a queue's contents in the form Queue S: [S(1), S(1), S(2)]
// The queue is taken by value so we can drain it without disturbing the simulation
void printQueue(char type, queue<int> queue) {
    cout << "Queue " << type << ": [";
    
    bool first = true;
    while (!queue.empty()) {
        // add comma in front of items that is not the first item
        if (!first) cout << ", ";
        cout << type << "(" << queue.front() << ")";
        // this only drains the local copy (by value) and not the original queue in memory
        queue.pop();
        first = false;
    }
    
    cout << "]" << endl;
}

// Print the dispatched truck stack from top to bottom.
void printStack(stack<string> truck_stack) {
    // simply print "Stack: empty" when the stack is empty and exit early
    if (truck_stack.empty()) {
        cout << "Stack: empty" << endl;
        return;
    }
    
    cout << "Stack of Dispatched Trucks:" << endl;
	// print the top item first and then drain the stack to print the rest
    cout << "  Top -> " << truck_stack.top() << endl;
    
	// pop the top item so we don't print it again in the loop
    // this also uses the local copy to display the stack without disturbing teh simulation
    truck_stack.pop();
    
	// print the rest of the stack until its empty and pop each item after printing it to move down the stack
	// we move down the stack in a LIFO (Last In First Out) manner by popping the top item after printing it until the stack is empty
    while (!truck_stack.empty()) {
        cout << "         " << truck_stack.top() << endl;
        truck_stack.pop();
    }
    
    cout << "  Bottom" << endl;
}

int main() {
    const int time_steps = 30;
    const int truck_capacity = 5;
    const array<char, 3> order_types{'S', 'M', 'B'};

    // Queues for each order type (holding the processing_time of each order).
    queue<int> queue_s;
    queue<int> queue_m;
    queue<int> queue_b;

    // Stack for dispatched trucks holding string labels like Truck1[S]
    stack<string> dispatched_trucks_stack;

    // Per-type truck counters and per-type processed counters.
    map<char, int> truck_counters {{'S', 0}, {'M', 0}, {'B', 0}};
    map<char, int> processed_count {{'S', 0}, {'M', 0}, {'B', 0}};

    // Log all generated orders for the final report.
    vector<OrderLogEntry> order_log;

	// random number generation setup using mt19937 (Mersenne Twister)
    // I used the following resources
    // for guidance on how to implement this random number generator from the std libary
    // https://www.geeksforgeeks.org/cpp/stdmt19937-class-in-cpp/
    // https://cplusplus.com/reference/random/mt19937/
    // https://en.wikipedia.org/wiki/Mersenne_Twister
    // it is a pseudo random number generator but random enough for the simulation :)
    random_device rd;
    mt19937 gen(rd());
	
    // there can be 0 to 3 new orders per time step, each order can be S/M/B and processing time is between 1 and 4
	// we define the ranges here so we can reuse them in each time step without reinitializing them
    uniform_int_distribution<int> arrival_range(0, 3); // 0 to 3 arrivals per step
    uniform_int_distribution<int> type_range(0, 2); // 0=S, 1=M, 2=B
    uniform_int_distribution<int> processing_time_range(1, 4); // processing time

    cout << "=== Warehouse Order Dispatch Simulation ===" << endl;
    cout << "Time steps: " << time_steps << endl;
    cout << "Truck capacity: " << truck_capacity << endl << endl;
    
    // Simulation loop
    // I used Claude Opus 4.7 for sanity checks and my rubber duck debugging via Claude Code 
    // but I have implemented the code myself using guidance from the pseudocode.txt provided
    // all the comments are my own reasoning to show how I have thought through the problem
    for (int time = 1; time <= time_steps; ++time) {

		// generate new random orders 0 to 3 and add them to the appropriate queues
        int num_new_orders = arrival_range(gen);
        vector<char> new_arrivals;
        new_arrivals.reserve(num_new_orders);

        for (int i = 0; i < num_new_orders; ++i) {
			// generate a random order type (S/M/B)
            char order_type = order_types[type_range(gen)];
            
			// generate a random processing time for this order between 1 and 4
            int  processing_time = processing_time_range(gen);

            // add to appropriate queue
            // could use a switch or map but I am keeping it simple
            if (order_type == 'S') {
                queue_s.push(processing_time);
            }
            else if (order_type == 'M') {
                queue_m.push(processing_time);
            }
            else if (order_type == 'B') {
                queue_b.push(processing_time);
            }

			// log the order for the final report table
            order_log.push_back({time, order_type, processing_time});
            new_arrivals.push_back(order_type);
        }

        // Process queues
        for (char queue_type : order_types) {
            
            // the queue here is a pointer to teh actual queue in memory
            // and not the same as the quee we are printing
            queue<int>* q = nullptr;
            
            // pick the correct queue for the queue_type from memory
            // could also use a switch or map but not neccesary for 3 sates
            if (queue_type == 'S') {
                q = &queue_s;
            } 
            else if(queue_type == 'M') {
                q = &queue_m;}
            else {
                q = &queue_b;
            }

            if (!q->empty()) {
                //decrement the front order processing_time
                q->front()--;

                if (q->front() <= 0) {
                    // remove front order from the queue FIFO (First In First Out)
                    q->pop();
                    processed_count[queue_type]++;

                    // check if the truck of this type is full
                    if (processed_count[queue_type] >= truck_capacity) {
                        // when the truck is full or at capacity we increment the truck counter
                        truck_counters[queue_type]++;
                        string truck = "Truck" + to_string(truck_counters[queue_type]) + "[" + string(1, queue_type) + "]";
                        
                        // add the dispatched truck onto the top of the stack
                        dispatched_trucks_stack.push(truck);
                        processed_count[queue_type] = 0;
                    }
                }
            }
        }

        // Display current state
        cout << "Time Step: " << time << endl;

        // Print new arrivals.
        cout << "New Orders: ";
        if (new_arrivals.empty()) {
            cout << "none";
        } else {
            for (size_t i = 0; i < new_arrivals.size(); ++i) {
                if (i > 0) cout << ", ";
                cout << new_arrivals[i];
            }
        }
        cout << endl;

        // print each queue state
        printQueue('S', queue_s);
        printQueue('M', queue_m);
        printQueue('B', queue_b);

        // print dispatched trucks stack LIFO (Last In First Out)
        printStack(dispatched_trucks_stack);

        cout << endl;
    }
    
    // Print final generated orders tabel
    cout << "time_step,type,processing_time" << endl;
    for (const auto& order : order_log) {
        cout << order.time << "," << order.type << "," << order.processing_time << endl;
    }

    return 0;
}
