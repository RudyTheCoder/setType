#include <string>
#include <iostream>
#include "SetType.h"

using namespace std;

template<class T>
SetType<T>::SetType() {
    // Create an array of forward_lists and initially set to an empty forward_list

    // Your code here
    buckets = new forward_list<T>[DEFAULT_BUCKETS];
    numElems = 0;
    maxLoad = DEFAULT_LOAD_FACTOR;
    numBuckets = DEFAULT_BUCKETS;
}


template<class T>
SetType<T>::SetType(int numBucks) {

    buckets = new forward_list<T>[numBucks];
    numElems = 0;
    maxLoad = DEFAULT_LOAD_FACTOR;
    numBuckets = numBucks;
}


template<class T>
SetType<T>::SetType(SetType &otherSet) {  // copy constructor
    // This should make use of copySet

    numElems = 0;
    copySet(otherSet);
}

template<class T>
SetType<T>& SetType<T>::operator=(SetType const &other) {
    // Your code here

    numBuckets =0;
    copySet(other);
    return *this;

}

template<class T>
void SetType<T>::copySet(const SetType &otherSet) {

    delete [] buckets;
    buckets = new forward_list<T>[otherSet.numBuckets];
    numBuckets = otherSet.numBuckets;
    numElems = 0;

    //copy over each element from otherSet
    for(int i = 0; i < otherSet.numBuckets; i++){
        for(auto it = otherSet.buckets[i].begin(); it != otherSet.buckets[i].end(); it++){
           Add(*it);
        }
    }

}

template<class T>
void SetType<T>::Add(T elem) {

    int bucket = GetHashIndex(elem);
    Remove(elem);
    buckets[bucket].push_front(elem); //adds element to the head of the forward list.
    numElems++;

    if(LoadFactor() > maxLoad){  // if loadFactor gets too big, need to rehash
        numBuckets = numBuckets *2; // doubles the amount of buckets.
        Rehash(numBuckets);
    }

    return;
}

 template<class T>
void SetType<T>::Rehash(int newNumBuckets) {
SetType<T> rehashedSet(newNumBuckets);

// Your code here
    numBuckets = newNumBuckets;
    ResetIterator();
    T element;
    for(int i = 0; i < numElems; ++i){
        element = GetNextItem();
        rehashedSet.Add(element);
    }

    *this = rehashedSet;
}

template<class T>
SetType<T>::~SetType() {
    delete [] buckets;
}


template<class T>
SetType<T> SetType<T>::operator+(T elem) {
    SetType<T> result;
    // Your code here

    result = *this;

    result.Add(elem);

    return result;
}

template<class T>
SetType<T> SetType<T>::operator-(T elem) {
    SetType<T> result;
    // Your code here

    result = *this;
    result.Remove(elem);

    return result;
}

template<class T>
SetType<T> SetType<T>::operator+(SetType& otherSet) {
    SetType<T> result;
    // Your code here

    result = *this;

    for(int i = 0; i < otherSet.numBuckets; i++){
        for(auto it = otherSet.buckets[i].begin(); it != otherSet.buckets[i].end(); it++){
            result.Add(*it); // is this the correct way to Add an element from otherSet to result? yes
        }
    }

    return result;
}

template<class T>
SetType<T> SetType<T>::operator*(SetType& otherSet) {
    SetType<T> result; // start it empty

    // Your code here

    for(int i = 0; i < otherSet.numBuckets; i++){
       for(auto it = otherSet.buckets[i].begin(); it != otherSet.buckets[i].end(); it++){
           if(this->Contains(*it)) { //if this contains an element from otherSet
               result.Add(*it);
               // only add elements that are in both

           }
        }
    }

    return result;
}

template<class T>
SetType<T> SetType<T>::operator-(SetType& otherSet) {
    SetType<T> result;

    // Your code here

    result = *this; // *this can either be SetA or SetB. Left side of the minus sign.
    for(int i = 0; i < otherSet.numBuckets; i++){
        for(auto it = otherSet.buckets[i].begin(); it != otherSet.buckets[i].end(); it++){
            result.Remove(*it);

        }
    }

    return result;
}


template<class T>
int SetType<T>::GetHashIndex(const T& key) {
    // This is done... No touching!
    unordered_map<T,T> mapper;
    typename unordered_map<T,T>::hasher hashFunction = mapper.hash_function();
    return static_cast<int>(hashFunction(key) % numBuckets);
}


template<class T>
void SetType<T>::SetMaxLoad(double max) {
    // This function is done
    if (max < 0.1)
        maxLoad = 0.1;
    else
        maxLoad = max;
}



template<class T>
T SetType<T>::GetNextItem() {
    // Returns the current item and then move to the next item
    T item;
    // Your code here
    if(iterCount >= numElems){
        throw "IteratorOutOfBounds";

    }

    while(bucketIter == buckets[currBucket].end()){ // if a bucket does not have any elements, move to next bucket.
    ++currBucket;
    bucketIter = buckets[currBucket].begin(); // start iterator at the beginning.
    }

    item = *bucketIter;
    ++bucketIter;
    ++iterCount;

    return item;

}


template<class T>
void SetType<T>::Remove(T elem) {
    int bucket = GetHashIndex(elem);
    for(auto it = buckets[bucket].begin(); it != buckets[bucket].end(); ++it){

        if(*it == elem){
            buckets[bucket].remove(*it);
            --numElems;
            return;
        }

    }
    return;
}


template<class T>
bool SetType<T>::Contains(T elem) {

    int bucket = GetHashIndex(elem);
    for(auto it = buckets[bucket].begin(); it != buckets[bucket].end(); ++it){
        if(*it == elem){
            return true;
        }
    }


    return false;
}

template<class T>
void SetType<T>::MakeEmpty() {

        for(int i = 0; i < numBuckets; ++i){
            buckets[i].clear();

       }
        numBuckets = 0;
        numElems = 0;

    }


template<class T>
double SetType<T>::LoadFactor() const {
    return (double) numElems/ (double) numBuckets;
}

template<class T>
void SetType<T>::ResetIterator() {
    bucketIter = buckets[0].begin();
    currBucket = 0;
    iterCount = 0;
}






