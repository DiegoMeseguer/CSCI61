// FILE: carwash.cxx
// A small test program to test the car_wash_simulate function.

#include <iostream>   // Provides cout
#include <cstdlib>    // Provides EXIT_SUCCESS
#include <queue>      // Provides queue
#include "washing.h"  // Provides averager, bool_source, washer
#include <time.h>
using namespace std;
using namespace main_savitch_8A;

void car_wash_simulate
(unsigned int wash_time, double arrival_prob, unsigned int total_time);
// Precondition: 0 <= arrival_prob <= 1.
// Postcondition: The function has simulated a car wash where wash_time is the
// number of seconds needed to wash one car, arrival_prob is the probability
// of a customer arriving in any second, and total_time is the total number
// of seconds for the simulation. Before the simulation, the function has
// written its three parameters to cout. After the simulation, the function
// has written two pieces of information to cout: (1) The number of
// cars washed, and (2) The average waiting time of a customer.

int main( )
{
    // Wash takes 240 seconds
    // Customers arrive on average once every 400 seconds
    // Total simulation time is 6000 seconds
    
    srand(time(0)); //This let's us get a different result each time we run the simulation.

    car_wash_simulate(220, 1.0/2, 8000);

    return EXIT_SUCCESS;
}

void car_wash_simulate
(unsigned int wash_time, double arrival_prob, unsigned int total_time)
// Library facilities used: iostream, queue, washing.h
{
    queue<unsigned int> arrival_times; // Waiting customers time stamps, this is the queue that stores our customers
    unsigned int next;                 // A value taken from the queue
    bool_source arrival(arrival_prob);  // query() queries this to get the probability each second
    washer machine(wash_time);
    averager wait_times;                // starts with count & sum set to 0
    unsigned int current_second;        // keeps track of seconds

    // Write the parameters to cout.
    cout << "Seconds to wash one car: " << wash_time << endl;
    cout << "Probability of customer arrival during a second: ";
    cout << arrival_prob << endl;
    cout << "Total simulation seconds: " << total_time << endl;      

    for (current_second = 1; current_second <= total_time; ++current_second)
    {   // Simulate the passage of one second of time.

        // Check whether a new customer has arrived.
        if (arrival.query( ))   //if this is true add the customer to the queue
            arrival_times.push(current_second);

        // Check whether we can start washing another car.
        if ((!machine.is_busy( ))  &&  (!arrival_times.empty( )))
        {
            next = arrival_times.front( );
            arrival_times.pop( );
            wait_times.next_number(current_second - next); //after the car lefts de queue we also add it to the averager
            machine.start_washing( );
        }

        // Tell the washer to simulate the passage of one second.
        machine.one_second( );
    }

    //While loop makes sure that the queue is empty at the end and all cars have been washed and counted.
    if(!arrival_times.empty())
    {
        while(arrival_times.size() != 0) {
            if ((!machine.is_busy( ))  &&  (!arrival_times.empty( )))
            {
            next = arrival_times.front( );
            arrival_times.pop( );
            wait_times.next_number(current_second - next); //after the car lefts de queue we also add it to the averager
            machine.start_washing( );
            }

        // Tell the washer to simulate the passage of one second.
        machine.one_second( );
            
        }
    }

    // Write the summary information about the simulation.
    cout << "Customers served: " << wait_times.how_many_numbers( ) << endl;
    if (wait_times.how_many_numbers( ) > 0)
        cout << "Average wait: " << wait_times.average( ) << " sec" << endl;
}

