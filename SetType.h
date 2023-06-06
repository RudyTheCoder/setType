#ifndef SET_TYPE
#define SET_TYPE

#include<string>
#include<iostream>
#include<forward_list>
#include<unordered_map>
using namespace std;

class IteratorOutOfBounds {
public:
    string Msg() {
        return "Iterator is out of bounds.  Nothing left to iterate over.";
    }
};

const int DEFAULT_BUCKETS = 10;
const double DEFAULT_LOAD_FACTOR = 1.0;

template<class T>
class SetType
{
public:
    // Constructors

/*Function: Initializes the private variables.
*
* Precondition: None
*
* Post-condition: Private variables will be set to default values.
*/

    SetType();

/*Function: Initializes the private variables. Set's buckets equal to numBucks.
*
* Precondition: None
*
* Post-condition: Private variables will be set to default values.
*/

    explicit SetType(int numBucks);

/*Function: Copy constructor.
*
* Precondition: Must have the function copySet implemented.
*
* Post-condition: Copies the contents of other to this.
*/


    SetType(SetType& other);

/*Function: Deconstructor.
*
* Precondition: None.
*
* Post-condition: Deallocates memory that was allocated for buckets.
*/

    ~SetType();

/*Function: This will add element to the set.
*
* Precondition: Must use a hash function to determine which bucket element goes into.
*
* Post-condition: Element has been added to set.
*/
    void Add(T elem);

/*Function: This will remove element from the set.
*
* Precondition: Must use a hash function to determine which bucket element is potentially in.
*
* Post-condition: Element has been removed to set.
*/
    void Remove(T elem);

/*Function: This function determines whether an element is in the set.
*
* Precondition: Must use a hash function to determine which bucket element goes into.
*
* Post-condition: Returns true if element is in the set and false otherwise.
*/
    bool Contains(T elem);

/*Function: This function will remove all the elements from the set.
*
* Precondition: None.
*
* Post-condition: The set has been emptied.
*/
    void MakeEmpty();

/*Function: This will return the number of elements in a set.
*
* Precondition: None.
*
* Post-condition: The total number of elements in the set is returned.
*/
    int Size() const {
        return numElems;
    }

/*Function: This function returns the load factor of the set.
*
* Precondition: Must know the total # of elements and buckets of the set.
*
* Post-condition: Returns the load factor of the set.
*/

    double LoadFactor() const;

    void SetMaxLoad(double max);

/*Function: Rehashes elements of a set once the load factor has been reached.
*
* Precondition: An implemented Operator Equals function.
*
* Post-condition: Elements are rehashed using newNumBuckets.
*/
    void Rehash(int newNumBuckets);

/*Function: This function will add an element to the set.
*
* Precondition: Must have Add and Operator Equals functions implemented.
*
* Post-condition: The element has been added to the set. Does not allow duplicates.
*/
    SetType operator+(T elem);				      // Add

/*Function: This function will remove an element from a set.
*
* Precondition: Must have Remove and Operator Equals functions implemented.
*
* Post-condition: Will return the set without the element in it.
*/
    SetType operator-(T elem);				      // Remove

/*Function: Union of two sets.
*
* Precondition: Must use functional Add and operator equals function.
*
* Post-condition: Will return the union of two sets.
*/

    SetType operator+(SetType& otherSet);         // Union

/*Function: The difference of two sets.
*
* Precondition: Must have Remove and operator equals functions implemented.
*
* Post-condition: Returns the difference of two sets.
*/
    SetType operator-(SetType& otherSet);         // Difference

/*Function: Intersection of two sets.
*
* Precondition: Must have Remove and operator equals functions implemented.
*
* Post-condition: Will return the intersection of two sets.
*/
    SetType operator*(SetType& otherSet);         // Intersection

/*Function: Copies the contents of otherSet to This.
*
* Precondition: Must have copySet function implemented.
*
* Post-condition: Will return the contents of otherSet to this.
*/
    SetType& operator=(SetType const& otherSet);  // Assignment (does deep copy)


/*Function: Resets the Iterator of SetType.
*
* Precondition: None.
*
* Post-condition: Sets the Iterator back to the beginning of Set.
*/
    void ResetIterator();	// Reset iterator

/*Function: Returns the element that the Iterator is pointing at.
*
* Precondition: Must keep track of the iterator and element count in the program.
*
* Post-condition: Returns the element of the next element each time it is called.
*/

    T GetNextItem();

private:
    forward_list<T>* buckets;	// An array of forward_list's
                                // (each index is a forward_list)

    int numBuckets;     // total number of buckets

    int GetHashIndex(const T& key);    // Gets the hash index given the elem

    int numElems;       // total number of elements

    double maxLoad;     // load factor of the Set

    // This function is used by the
    // copy constructor and the assignment operator.

/*Function: This will copy the contents of other to this.
*
* Precondition: Must have a functional Add function.
*
* Post-condition: Copies all the elements from otherSet to this.
*/
    void copySet(const SetType& otherSet);

    // Iterator variables
    int currBucket;											// What bucket is the iterator on?
    int iterCount;                                          // What element are we on?
    mutable typename forward_list<T>::iterator bucketIter;	// The iterator of the current bucket

    // Any other private functions and variables you want/need
};

#include "SetType.cpp"

#endif