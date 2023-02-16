#include "deque.h"
/**
 * @file deque.cpp
 * Implementation of the Deque class.
 *
 */

template <class T>
Deque<T>::Deque(){
    n1 = -1;
    n2 = 0;
}

/**
 * Adds the parameter object to the right of the Deque.
 *
 * @param newItem object to be added to the Deque.
 */
template <class T>
void Deque<T>::pushR(T newItem)
{
    if ((int)data.size() <= n1+1) {
        data.push_back(newItem);
        n1++;
        if (n1-n2+1 <= n2) {
            for (int i=0; i<n1-n2+1; i++) {
                data[i] = data[n2+i];
            }
            data.resize(n1-n2+1);
            n1 = data.size() - 1;
            n2 = 0;
        } 
    }
    else {
        data[n1+1] = newItem;
        n1++;
        if (n1-n2+1 <= n2) {
            for (int i=0; i<n1-n2+1; i++) {
                data[i] = data[n2+i];
            }
            data.resize(n1-n2+1);
            n1 = data.size() - 1;
            n2 = 0;
        } 
    }
    //data.push_back(newItem);
}

/**
 * Removes the object at the left of the Deque, and returns it to the
 * caller.
 *
 * See .h file for implementation notes. 
 *
 * @return The item that used to be at the left of the Deque.
 */
template <class T>
T Deque<T>::popL()
{
    T temp = data[n2];
    n2++;
    cout << "n1,n2: " << n1 << "," << n2 << endl;
    if (n1-n2+1 <= n2) {
        for (int i=0; i<n1-n2+1; i++) {
            data[i] = data[n2+i];
        }
        data.resize(n1-n2+1);
        n1 = data.size() - 1;
        n2 = 0;
    } 
    return temp;
    /*T temp = data.front();
    data.erase(data.begin());
    return temp;*/
}
/**
 * Removes the object at the right of the Deque, and returns it to the
 * caller.
 *
 * @return The item that used to be at the right of the Deque.
 */
template <class T>
T Deque<T>::popR()
{
    T temp = data[n1];
    n1--;
    if (n1-n2+1 <= n2) {
        for (int i=0; i<n1-n2+1; i++) {
            data[i] = data[n2+i];
        }
        data.resize(n1-n2+1);
        n1 = data.size() - 1;
        n2 = 0;
    } 
    return temp;
    /*T temp = data.back();
    data.pop_back();
    return temp;*/
}

/**
 * Finds the object at the left of the Deque, and returns it to the
 * caller. Unlike popL(), this operation does not alter the deque.
 *
 * @return The item at the front of the deque.
 */
template <class T>
T Deque<T>::peekL()
{
    return data[n2];
    //return data.front();
}

/**
 * Finds the object at the right of the Deque, and returns it to the
 * caller. Unlike popR(), this operation does not alter the deque.
 *
 * @return the value of The item at the right of the deque.
 */
template <class T>
T Deque<T>::peekR()
{
    return data[n1];
    //return data.back();
}

/**
 * Determines if the Deque is empty.
 *
 * @return bool which is true if the Deque is empty, false otherwise.
 */
template <class T>
bool Deque<T>::isEmpty() const
{
    if (n1-n2+1 == 0) {
        return true;
    }
    return false;
    //return data.empty();
}
