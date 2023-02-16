#define CATCH_CONFIG_MAIN
#include <iostream>
#include "cs221util/catch.hpp"
#include "stack.h"
#include "queue.h"
#include "deque.h"
//using namespace cs221util;
using namespace std;

/*TEST_CASE("stack::basic functions","[weight=1][part=stack]"){
    //cout << "Testing Stack..." << endl;
    Stack<int> intStack;
    vector<int> result;
    vector<int> expected;
    for (int i = 10; i > 0; i--) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intStack.push(i);
    }
    while (!intStack.isEmpty()) {
        result.push_back(intStack.pop());
    }
    REQUIRE( result == expected);
}*/

TEST_CASE("queue::basic functions","[weight=1][part=queue]"){
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;
    Deque<int> sol;
    /*for (int i = 1; i <= 10; i++) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        cout << "still fine" << endl;
        intQueue.enqueue(i);
    }
    int i =0; 
    while (!intQueue.isEmpty()) {
        cout << "still fine " << i << endl;
        result.push_back(intQueue.dequeue());
        i++;
    }
    REQUIRE( result == expected);*/
    for (int i = 1; i <= 9; i++) {
        sol.pushR(i);
    }
    for (int i = 1; i <= 5; i++) {
        cout << sol.popL() << endl; 
    }
    
}