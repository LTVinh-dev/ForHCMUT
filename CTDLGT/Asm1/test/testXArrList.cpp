#include <sstream>
#include <iostream>
#include <type_traits>
#include <iomanip>
#include <sstream>
#include <string>
#include <math.h>
#include <random>
using namespace std;

#define EPSILON (1E-8)

class Point{
private:
    float x, y, z;
    friend ostream &operator<<( ostream &os, const Point& point);
    
public:
    Point(float x=0.0f, float y=0.0f, float z=0.0f){
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Point(const Point& point){
        this->x = point.x;
        this->y = point.y;
        this->z = point.z;
    }
    
    void setZ(float z) {
        this->z = z;
    }

    float getZ() const {
        return z;
    }
    
    void setY(float y) {
        this->y = y;
    }

    float getY() const {
        return y;
    }

    void setX(float x) {
        this->x = x;
    }

    float getX() const {
        return x;
    }
    float radius(){
        return sqrt(x*x + y*y + z*z);
    }

    //with point object
    bool operator==(Point rhs){
        return  (abs(this->x - rhs.x) < EPSILON) &&
                (abs(this->y - rhs.y) < EPSILON) &&
                (abs(this->z - rhs.z) < EPSILON);
    }
    
    //with pointer to point
    static bool pointEQ(Point& lhs, Point& rhs){
        return  lhs == rhs;
    }
    //with pointer to point
    static bool pointEQ(Point*& lhs, Point*& rhs){
        return  *lhs == *rhs;
    }
    
    static string point2str(Point& point){
        stringstream os;
        os  << point;
        return os.str();
    }
    static string point2str(Point*& point){
        return point2str(*point);
    }

    operator float(){
        return sqrt(x*x + y*y + z*z);
    }
     
    static Point* genPoints(int size, float minValue=0, float maxValue=1, 
                            bool manualSeed=false, int seedValue=0){
        
        Point* head = new Point[size];
        
        std::default_random_engine* engine;
        if(manualSeed)
            engine = new std::default_random_engine(static_cast<long unsigned int>(seedValue));
        else
            engine = new std::default_random_engine(static_cast<long unsigned int>(time(0)));
        uniform_real_distribution<double> dist(minValue, maxValue);
        
        //
        for(int idx=0; idx < size; idx++){
            float x = dist(*engine);
            float y = dist(*engine);
            float z = dist(*engine);
            head[idx] = Point(x,y,z);
        }
        delete engine;
        return head;
    }
    static void println(Point* head, int size){
        stringstream os;
        os << "[";
        for(int idx=0; idx < size-1; idx++)
            os << head[idx] << ", ";
        if(size > 0) os << head[size-1] << "]";
        else os << "]";
        cout << os.str() << endl;
        return;
    }
   
};
ostream &operator<<( ostream &os, const Point& point){
    os << "P(" << fixed 
            << setw(6) << setprecision(2) << point.x << "," 
            << setw(6) << setprecision(2) << point.y << ","
            << setw(6) << setprecision(2) << point.z
       << ")";
    return os;
}

template<class T>
class IList{
public:
    virtual ~IList(){};
    /* add(T e): append item "e" to the list
     */
    virtual void    add(T e)=0;
    
    
    
    /* add(int index, T e): insert item "e" at location "index";
     *      location is an integer started from 0
     */
    virtual void    add(int index, T e)=0;
    
    
    
    /* removeAt(int index): remove the item at location "index"
     * 
     * return:
     *  >> the item stored at index
     *  >> throw an exception (std::out_of_range) if index is invalid
     */
    virtual T       removeAt(int index)=0;
    
    
    /* removeItem(T item, void (*removeItemData)(T)=0): remove item stored in the list
     *   >> removeItemData: a function pointer (maybe NULL, default),
     *          that will be called inside of removeItem to delete the item's data stored in the list
     *   >> removeItemData, why need? because we DO NOT type T is a pointer or not.
     * 
     * return:
     *   >> true if "item" stored in the list; 
     *   >> otherwise, return false
     */
    virtual bool    removeItem(T item, void (*removeItemData)(T)=0)=0;
    
    
    
    /* empty(): return true if the list is empty; otherwise, return false
     */
    virtual bool    empty()=0;
    
    
    
    /* size(): return number of items stored in the list
     */
    virtual int     size()=0;
    
    
    
    /* clear(): make the list empty by clearing all data and putting the list to the initial condition
     */
    virtual void    clear()=0;
    
    
    
    /* get(int index): return a reference to the item at location "index"
     *      if index is invalid, this function will throw an exception "std::out_of_range"
     * 
     * NOTE: programmers can change the item returned by this function
     */
    virtual T&      get(int index)=0;
    
    
    /* indexOf(T item): return the index of item
     *      if item is not found, then return -1
     */
    virtual int     indexOf(T item)=0;
    
    
    
    /* contains(T item): return true if the list contains "item", else: return false
     */
    virtual bool    contains(T item)=0;
    
    
    
    /* toString(string (*item2str)(T&)=0 ): return a string describing the list.
     *    >> We do not know the item type, so we do not know how to convert each item to string.
     *       Therefore, we need a pointer to a function
     *          that can convert the item (passed to that function) to a string
     */
    virtual string  toString(string (*item2str)(T&)=0 )=0;
};

template <class T>
class XArrayList : public IList<T>
{
public:
    class Iterator; // forward declaration

protected:
    T *data;                                 // dynamic array to store the list's items
    int capacity;                            // size of the dynamic array
    int count;                               // number of items stored in the array
    bool (*itemEqual)(T &lhs, T &rhs);       // function pointer: test if two items (type: T&) are equal or not
    void (*deleteUserData)(XArrayList<T> *); // function pointer: be called to remove items (if they are pointer type)

public:
    XArrayList(
        void (*deleteUserData)(XArrayList<T> *) = 0,
        bool (*itemEqual)(T &, T &) = 0,
        int capacity = 10);
    XArrayList(const XArrayList<T> &list);
    XArrayList<T> &operator=(const XArrayList<T> &list);
    ~XArrayList();

    // Inherit from IList: BEGIN
    void add(T e);
    void add(int index, T e);
    T removeAt(int index);
    bool removeItem(T item, void (*removeItemData)(T) = 0);
    bool empty();
    int size();
    void clear();
    T &get(int index);
    int indexOf(T item);
    bool contains(T item);
    string toString(string (*item2str)(T &) = 0);
    // Inherit from IList: END

    void println(string (*item2str)(T &) = 0)
    {
        cout << toString(item2str) << endl;
    }
    void setDeleteUserDataPtr(void (*deleteUserData)(XArrayList<T> *) = 0)
    {
        this->deleteUserData = deleteUserData;
    }

    Iterator begin()
    {
        return Iterator(this, 0);
    }
    Iterator end()
    {
        return Iterator(this, count);
    }

    /** free:
     * if T is pointer type:
     *     pass THE address of method "free" to XArrayList<T>'s constructor:
     *     to:  remove the user's data (if needed)
     * Example:
     *  XArrayList<Point*> list(&XArrayList<Point*>::free);
     *  => Destructor will call free via function pointer "deleteUserData"
     */
    static void free(XArrayList<T> *list)
    {
        typename XArrayList<T>::Iterator it = list->begin();
        while (it != list->end())
        {
            delete *it;
            it++;
        }
    }

protected:
    void checkIndex(int index);     // check validity of index for accessing
    void ensureCapacity(int index); // auto-allocate if needed

    /** equals:
     * if T: primitive type:
     *      indexOf, contains: will use native operator ==
     *      to: compare two items of T type
     * if T: object type:
     *      indexOf, contains: will use native operator ==
     *      to: compare two items of T type
     *      Therefore, class of type T MUST override operator ==
     * if T: pointer type:
     *      indexOf, contains: will use function pointer "itemEqual"
     *      to: compare two items of T type
     *      Therefore:
     *      (1): must pass itemEqual to the constructor of XArrayList
     *      (2): must define a method for comparing
     *           the content pointed by two pointers of type T
     *          See: definition of "equals" of class Point for more detail
     */
    static bool equals(T &lhs, T &rhs, bool (*itemEqual)(T &, T &))
    {
        if (itemEqual == 0)
            return lhs == rhs;
        else
            return itemEqual(lhs, rhs);
    }

    void copyFrom(const XArrayList<T> &list);

    void removeInternalData();

    //////////////////////////////////////////////////////////////////////
    ////////////////////////  INNER CLASSES DEFNITION ////////////////////
    //////////////////////////////////////////////////////////////////////
public:
    // Iterator: BEGIN
    class Iterator
    {
    private:
        int cursor;
        XArrayList<T> *pList;

    public:
        Iterator(XArrayList<T> *pList = 0, int index = 0)
        {
            this->pList = pList;
            this->cursor = index;
        }
        Iterator &operator=(const Iterator &iterator)
        {
            cursor = iterator.cursor;
            pList = iterator.pList;
            return *this;
        }
        void remove(void (*removeItemData)(T) = 0)
        {
            T item = pList->removeAt(cursor);
            if (removeItemData != 0)
                removeItemData(item);
            cursor -= 1; // MUST keep index of previous, for ++ later
        }

        T &operator*()
        {
            return pList->data[cursor];
        }
        bool operator!=(const Iterator &iterator)
        {
            return cursor != iterator.cursor;
        }
        // Prefix ++ overload
        Iterator &operator++()
        {
            this->cursor++;
            return *this;
        }
        // Postfix ++ overload
        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
    };
    // Iterator: END
};

//////////////////////////////////////////////////////////////////////
////////////////////////     METHOD DEFNITION      ///////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
XArrayList<T>::XArrayList(
    void (*deleteUserData)(XArrayList<T> *),
    bool (*itemEqual)(T &, T &),
    int capacity)
{
    // TODO
    this->capacity = (capacity > 0) ? capacity : 10;
    this->deleteUserData = deleteUserData;
    this->itemEqual = itemEqual;
    this->count = 0;
    this->data = new T[capacity];
    if (this->data == 0)
        throw std::bad_alloc();
}

template <class T>
void XArrayList<T>::copyFrom(const XArrayList<T> &list)
{
    /*
     * Copies the contents of another XArrayList into this list.
     * Initializes the list with the same capacity as the source list and copies all elements.
     * Also duplicates user-defined comparison and deletion functions, if applicable.
     */
    // TODO
    capacity = list.capacity;
    count = list.count;
    data = new T[capacity];
    for (int i = 0; i < count; ++i)
        data[i] = list.data[i];
    itemEqual = list.itemEqual;
    deleteUserData = list.deleteUserData;
}

template <class T>
void XArrayList<T>::removeInternalData()
{
    /*
     * Clears the internal data of the list by deleting the dynamic array and any user-defined data.
     * If a custom deletion function is provided, it is used to free the stored elements.
     * Finally, the dynamic array itself is deallocated from memory.
     */
    // TODO
    delete[] data;
    data = 0;
    capacity = 0;
    count = 0;
}

template <class T>
XArrayList<T>::XArrayList(const XArrayList<T> &list)
{
    // TODO
    copyFrom(list);
}

template <class T>
XArrayList<T> &XArrayList<T>::operator=(const XArrayList<T> &list)
{
    // TODO
    if (this != &list)
    {
        removeInternalData();
        copyFrom(list);
    }
    return *this;
}

template <class T>
XArrayList<T>::~XArrayList()
{
    // TODO
    removeInternalData();
    if (deleteUserData != 0)
        deleteUserData(this);
}

template <class T>
void XArrayList<T>::add(T e)
{
    // TODO
    ensureCapacity(count);
    data[count++] = e;
}

template <class T>
void XArrayList<T>::add(int index, T e)
{
    // TODO 
    ensureCapacity(count+1);
    checkIndex(index);
    for (int i = count; i > index; --i)
        data[i] = data[i - 1];
    data[index] = e;
    count++;
}

template <class T>
T XArrayList<T>::removeAt(int index)
{
    // TODO
    checkIndex(index);
    T removedItem = data[index];
    for (int i = index; i < count - 1; ++i)
        data[i] = data[i + 1];
    count--;
    return removedItem;
}

template <class T>
bool XArrayList<T>::removeItem(T item, void (*removeItemData)(T))
{
    // TODO
    int index = indexOf(item);
    if (index != -1)
    {
        T removedItem = removeAt(index);
        if (removeItemData != 0)
            removeItemData(removedItem);
        return true;
    }
    return false;
}

template <class T>
bool XArrayList<T>::empty()
{
    // TODO
    return count == 0;
}

template <class T>
int XArrayList<T>::size()
{
    // TODO
    return count;
}

template <class T>
void XArrayList<T>::clear()
{
    // TODO
    count = 0;
}

template <class T>
T &XArrayList<T>::get(int index)
{
    // TODO
    checkIndex(index);
    return data[index];
}

template <class T>
int XArrayList<T>::indexOf(T item)
{
    // TODO
    for (int i = 0; i < count; ++i)
        if (equals(data[i], item, itemEqual))
            return i;
    return -1;
}
template <class T>
bool XArrayList<T>::contains(T item)
{
    // TODO
    return indexOf(item) != -1;
}

template <class T>
string XArrayList<T>::toString(string (*item2str)(T &))
{
    /**
     * Converts the array list into a string representation, formatting each element using a user-defined function.
     * If no function is provided, it uses the default string representation for each element.
     * Example: Given an array list with elements {1, 2, 3} and a function that converts integers to strings, calling toString would return "[1, 2, 3]".
     *
     * @param item2str A function pointer for converting items of type T to strings. If null, default to the string conversion of T.
     * @return A string representation of the array list with elements separated by commas and enclosed in square brackets.
     */

    // TODO
    stringstream ss;
    ss << "[";
    for (int i = 0; i < count; ++i)
    {
        if (i > 0)
            ss << ", ";
        if (item2str != 0)
            ss << item2str(data[i]);
        else
            ss << data[i];
    }
    ss << "]";
    return ss.str();
}

//////////////////////////////////////////////////////////////////////
//////////////////////// (private) METHOD DEFNITION //////////////////
//////////////////////////////////////////////////////////////////////
template <class T>
void XArrayList<T>::checkIndex(int index)
{
    /**
     * Validates whether the given index is within the valid range of the list.
     * Throws an std::out_of_range exception if the index is negative or exceeds the number of elements.
     * Ensures safe access to the list's elements by preventing invalid index operations.
     */
    // TODO
    if (index < 0 || index > count)
        throw std::out_of_range("Index out of range");
}
template <class T>
void XArrayList<T>::ensureCapacity(int index)
{
    /**
     * Ensures that the list has enough capacity to accommodate the given index.
     * If the index is out of range, it throws an std::out_of_range exception. If the index exceeds the current capacity,
     * reallocates the internal array with increased capacity, copying the existing elements to the new array.
     * In case of memory allocation failure, catches std::bad_alloc.
     */
    // TODO
    if (index >= capacity)
    {
        capacity = (int) capacity * 1.5;
        try {
            T *newData = new T[capacity];
            for (int i = 0; i < count; ++i)
                newData[i] = data[i];
            delete[] data;
            data = newData;
        }
        catch (const std::bad_alloc& e) {
            throw;
        }
    }
}



void xlistDemo1(){
    XArrayList<int> iList;
    for(int i = 0; i< 10 ; i++)
        iList.add(i, i*i);

    //iList.dump();
    for(XArrayList<int>::Iterator it=iList.begin(); it != iList.end(); it++ )
        cout << *it << ", found at: " << iList.indexOf(*it) << endl;
    cout << endl;
    int item = 120;
    int foundIdx = iList.indexOf(item);
    cout    << "lookup for " << item  << " found at: " << foundIdx << endl;
}

void xlistDemo2(){
    XArrayList<Point> alist;
    alist.add(Point(23.2f, 25.4f));
    alist.add(Point(24.6f, 23.1f));
    alist.println();
}

void xlistDemo3(){
    XArrayList<Point> alist;
    alist.add(Point(23.2f, 25.4f));
    alist.add(Point(24.6f, 23.1f));

    int idx1 = alist.indexOf(Point(24.6f, 23.1f));
    int idx2 = alist.indexOf(Point(24.61f, 23.1f));

    cout << "result 1 : " << idx1 << endl;
    cout << "result 2 : " << idx2 << endl;
}

void xlistDemo4(){
    XArrayList<Point*> list1(&XArrayList<Point*>::free, &Point::pointEQ);
    list1.add(new Point(23.2f, 25.4f));
    list1.add(new Point(24.6f, 23.1f));
    list1.add(new Point(12.5f, 22.3f));

    for(XArrayList<Point*>::Iterator it = list1.begin(); it != list1.end(); it++)
        cout << **it << endl;

    Point* p1 = new Point(24.6f, 23.1f); //found in list
    Point* p2 = new Point(124.6f, 23.1f); //not found
    cout << *p1 << "=> " << (list1.contains(p1)? "found; " : "not found; ")
                << " indexOf returns: " << list1.indexOf(p1) << endl;
    cout << *p2 << "=> " << (list1.contains(p2)? "found; " : "not found; ")
                << " indexOf returns: " << list1.indexOf(p2) << endl;

    ///Different results if not pass &Point::equals
    cout << endl << endl;
    XArrayList<Point*> list2(&XArrayList<Point*>::free);
    list2.add(new Point(23.2f, 25.4f));
    list2.add(new Point(24.6f, 23.1f));
    list2.add(new Point(12.5f, 22.3f));

    for(XArrayList<Point*>::Iterator it = list2.begin(); it != list2.end(); it++)
        cout << **it << endl;

    cout << *p1 << "=> " << (list2.contains(p1)? "found; " : "not found; ")
                << " indexOf returns: " << list2.indexOf(p1) << endl;
    cout << *p2 << "=> " << (list2.contains(p2)? "found; " : "not found; ")
                << " indexOf returns: " << list2.indexOf(p2) << endl;

    delete p1; delete p2;
}

int main(int argc, char **argv)
{
    // cout << "Assignment-1" << endl;
    xlistDemo4();
    cout << endl;
    return 0;
}

//passed sample test cases