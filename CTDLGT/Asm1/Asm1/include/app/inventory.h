#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "list/XArrayList.h"
#include "list/DLinkedList.h"
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>

using namespace std;

// -------------------- List1D --------------------
template <typename T>
class List1D
{
private:
    IList<T> *pList;

public:
    List1D();
    List1D(int num_elements);
    List1D(const T *array, int num_elements);
    List1D(const List1D<T> &other);
    virtual ~List1D();
    
    int size() const;
    T get(int index) const;
    void set(int index, T value);
    void add(const T &value);
    string toString() const;

    friend ostream &operator<<(ostream &os, const List1D<T> &list);

    void removeAt(int index);
};

// -------------------- List2D --------------------
template <typename T>
class List2D
{
private:
    IList<IList<T> *> *pMatrix;

public:
    List2D();
    List2D(List1D<T> *array, int num_rows);
    List2D(const List2D<T> &other);
    virtual ~List2D();

    int rows() const;
    void setRow(int rowIndex, const List1D<T> &row);
    T get(int rowIndex, int colIndex) const;
    List1D<T> getRow(int rowIndex) const;
    string toString() const;

    friend ostream &operator<<(ostream &os, const List2D<T> &matrix);

    void removeRow(int rowIndex);
};

struct InventoryAttribute
{
    string name;
    double value;
    InventoryAttribute(const string &name, double value) : name(name), value(value) {}
    string toString() const { return name + ": " + to_string(value); }

    friend ostream &operator<<(ostream &os, const InventoryAttribute &attr)
    {
        os << attr.toString();
        return os;
    }
};

// -------------------- InventoryManager --------------------
class InventoryManager
{
private:
    List2D<InventoryAttribute> attributesMatrix;
    List1D<string> productNames;
    List1D<int> quantities;

public:
    InventoryManager();
    InventoryManager(const List2D<InventoryAttribute> &matrix,
                     const List1D<string> &names,
                     const List1D<int> &quantities);
    InventoryManager(const InventoryManager &other);

    int size() const;
    List1D<InventoryAttribute> getProductAttributes(int index) const;
    string getProductName(int index) const;
    int getProductQuantity(int index) const;
    void updateQuantity(int index, int newQuantity);
    void addProduct(const List1D<InventoryAttribute> &attributes, const string &name, int quantity);
    void removeProduct(int index);

    List1D<string> query(string attributeName, const double &minValue,
                         const double &maxValue, int minQuantity, bool ascending) const;

    void removeDuplicates();

    static InventoryManager merge(const InventoryManager &inv1,
                                  const InventoryManager &inv2);

    void split(InventoryManager &section1,
               InventoryManager &section2,
               double ratio) const;

    List2D<InventoryAttribute> getAttributesMatrix() const;
    List1D<string> getProductNames() const;
    List1D<int> getQuantities() const;
    string toString() const;
};

// -------------------- List1D Method Definitions --------------------
template <typename T>
List1D<T>::List1D()
{
    // TODO
    this->pList = new DLinkedList<T>();
}

template <typename T>
List1D<T>::List1D(int num_elements)
{
    // TODO
    this->pList = new DLinkedList<T>();
    if (num_elements > 0)
    {
        T default_value{};
        for (int i = 0; i < num_elements; ++i)
        {
            this->pList->DLinkedList<T>::add(default_value);
        }
    }
}

template <typename T>
List1D<T>::List1D(const T *array, int num_elements)
{
    // TODO
    this->pList = new DLinkedList<T>();
    for (int i = 0; i < num_elements; ++i)
    {
        this->pList->add(array[i]);
    }

}

template <typename T>
List1D<T>::List1D(const List1D<T> &other)
{
    // TODO
    this->pList = new DLinkedList<T>(*other.pList);
}

template <typename T>
List1D<T>::~List1D()
{
    // TODO
    delete this->pList;
}

template <typename T>
int List1D<T>::size() const
{
    // TODO
    return this->pList->size();
}

template <typename T>
T List1D<T>::get(int index) const
{
    // TODO
    return this->pList->get(index);
}

template <typename T>
void List1D<T>::set(int index, T value)
{
    // TODO
    this->pList->set(index, value);
}

template <typename T>
void List1D<T>::add(const T &value)
{
    // TODO
    this->pList->add(value);
}

template <typename T>
string List1D<T>::toString() const
{
    // TODO
    return this->pList->toString();
}

template <typename T>
ostream &operator<<(ostream &os, const List1D<T> &list)
{
    // TODO
    os << list.toString();
    return os;
}

template <typename T>
void List1D<T>::removeAt(int index)
{
    pList->removeAt(index);
}

// -------------------- List2D Method Definitions --------------------
template <typename T>
List2D<T>::List2D()
{
    // TODO
    this->pMatrix = new DLinkedList<IList<T> *>();
}

template <typename T>
List2D<T>::List2D(List1D<T> *array, int num_rows)
{
    // TODO
    this->pMatrix = new DLinkedList<IList<T> *>();
    for (int i = 0; i < num_rows; ++i)
    {
        this->pMatrix->add(array + i);
    }
}

template <typename T>
List2D<T>::List2D(const List2D<T> &other)
{
    // TODO
    for (int i = 0; i < other.rows(); ++i)
    {
        this->pMatrix->add(new DLinkedList<T>(*other.getRow(i)));
    }
}

template <typename T>
List2D<T>::~List2D()
{
    // TODO
    for (int i = 0; i < this->pMatrix->size(); ++i)
    {
        delete this->pMatrix->get(i);
    }
    delete this->pMatrix;
}

template <typename T>
int List2D<T>::rows() const
{
    // TODO
    return this->pMatrix->size();
}

template <typename T>
void List2D<T>::setRow(int rowIndex, const List1D<T> &row)
{
    // TODO
    if (rowIndex < 0 || rowIndex >= this->pMatrix->size())
    {
        throw std::out_of_range("Row index out of bounds");
    }
    delete this->pMatrix->get(rowIndex); //delete the old row
    this->pMatrix->set(rowIndex, new DLinkedList<T>(row));
}

template <typename T>
T List2D<T>::get(int rowIndex, int colIndex) const
{
    // TODO
    if (rowIndex < 0 || rowIndex >= this->pMatrix->size())
    {
        throw std::out_of_range("Row index out of bounds");
    }
    IList<T> *row = this->pMatrix->get(rowIndex);
    return row->get(colIndex);
}

template <typename T>
List1D<T> List2D<T>::getRow(int rowIndex) const
{
    // TODO
    if (rowIndex < 0 || rowIndex >= this->pMatrix->size())
    {
       throw std::out_of_range("Row index out of bounds");
    }
    IList<T> *row = this->pMatrix->get(rowIndex);
    return List1D<T>(*row);
}

template <typename T>
string List2D<T>::toString() const
{
    // TODO
    string result = "";
    for (int i = 0; i < this->pMatrix->size(); ++i)
    {
        IList<T> *row = this->pMatrix->get(i);
        result += row->toString() + "\n";
    }
    return result;
}

template <typename T>
ostream &operator<<(ostream &os, const List2D<T> &matrix)
{
    // TODO
    os << matrix.toString();
    return os;
}

template <typename T>
void List2D<T>::removeRow(int rowIndex) {
    if (rowIndex < 0 || rowIndex >= this->pMatrix->size())
        throw std::out_of_range("Row index out of range");
    this->pMatrix->removeAt(rowIndex);
}

// -------------------- InventoryManager Method Definitions --------------------
InventoryManager::InventoryManager()
{
    // TODO
    this->attributesMatrix = List2D<InventoryAttribute>();
    this->productNames = List1D<string>();
    this->quantities = List1D<int>();
}

InventoryManager::InventoryManager(const List2D<InventoryAttribute> &matrix,
                                   const List1D<string> &names,
                                   const List1D<int> &quantities)
{
    // TODO
    for (int i = 0; i < matrix.rows(); ++i) {
        List1D<InventoryAttribute> row = matrix.getRow(i);
        List1D<InventoryAttribute> newRow;
        for(int j = 0; j < row.size(); ++j){
            newRow.add(row.get(j));
        }
        this->attributesMatrix.setRow(i, newRow);
    }
    for (int i = 0; i < names.size(); ++i) {
        this->productNames.add(names.get(i));
    }
    for (int i = 0; i < quantities.size(); ++i) {
        this->quantities.add(quantities.get(i));
    }
}

InventoryManager::InventoryManager(const InventoryManager &other)
{
    // TODO
    for (int i = 0; i < other.attributesMatrix.rows(); ++i) {
        List1D<InventoryAttribute> row = other.attributesMatrix.getRow(i);
        List1D<InventoryAttribute> newRow;
        for(int j = 0; j < row.size(); ++j){
            newRow.add(row.get(j));
        }
        this->attributesMatrix.setRow(i, newRow);
    }
    for (int i = 0; i < other.productNames.size(); ++i) {
        this->productNames.add(other.productNames.get(i));
    }
    for (int i = 0; i < other.quantities.size(); ++i) {
        this->quantities.add(other.quantities.get(i));
    }
}

int InventoryManager::size() const
{
    // TODO
    return this->productNames.size();
}

List1D<InventoryAttribute> InventoryManager::getProductAttributes(int index) const
{
    // TODO
    if (index < 0 || index >= this->size())
    {
        throw std::out_of_range("Index is invalid!");
    }
    return this->attributesMatrix.getRow(index);
}

string InventoryManager::getProductName(int index) const
{
    // TODO
    if (index < 0 || index >= this->size())
    {
        throw std::out_of_range("Index is invalid!");
    }
    return this->productNames.get(index);
}

int InventoryManager::getProductQuantity(int index) const
{
    // TODO
    if (index < 0 || index >= this->size())
    {
        throw std::out_of_range("Index is invalid!");
    }
    return this->quantities.get(index);
}

void InventoryManager::updateQuantity(int index, int newQuantity)
{
    // TODO
    if (index < 0 || index >= this->size())
    {
        throw std::out_of_range("Index is invalid!");
    }
    this->quantities.set(index, newQuantity);
}

void InventoryManager::addProduct(const List1D<InventoryAttribute> &attributes, const string &name, int quantity)
{
    // TODO
    this->attributesMatrix.setRow(this->size(), attributes); // Use setRow to add.  Assumes List2D add is broken.
    this->productNames.add(name);
    this->quantities.add(quantity);
}

void InventoryManager::removeProduct(int index)
{
    // TODO
    if (index < 0 || index >= this->size())
    {
        throw std::out_of_range("Index is invalid!");
    }
    
    this->attributesMatrix.removeRow(index);
    this->productNames.removeAt(index);
    this->quantities.removeAt(index);
}

List1D<string> InventoryManager::query(string attributeName, const double &minValue,
                                       const double &maxValue, int minQuantity, bool ascending) const
{
    // TODO
    List1D<string> result;
    for (int i = 0; i < this->size(); ++i)
    {
        List1D<InventoryAttribute> productAttributes = this->getProductAttributes(i);
        for (int j = 0; j < productAttributes.size(); ++j)
        {
            if (productAttributes.get(j).name == attributeName &&
                productAttributes.get(j).value >= minValue &&
                productAttributes.get(j).value <= maxValue &&
                this->quantities.get(i) >= minQuantity)
            {
                result.add(this->productNames.get(i));
                break;
            }
        }
    }
    // Sort
    for (int i = 0; i < result.size() - 1; ++i)
    {
        int minIndex = i;
        for (int j = i + 1; j < result.size(); ++j)
        {
            if (ascending)
            {
                if (result.get(j) < result.get(minIndex))
                    minIndex = j;
            }
            else
            {
                if (result.get(j) > result.get(minIndex))
                    minIndex = j;
            }
        }
        if (minIndex != i)
        {
            string temp = result.get(i);
            result.set(i, result.get(minIndex));
            result.set(minIndex, temp);
        }
    }
    return result;
}

void InventoryManager::removeDuplicates()
{
    // TODO
    for (int i = 0; i < this->size(); ++i)
    {
        for (int j = i + 1; j < this->size();)
        {
            if (this->productNames.get(i) == this->productNames.get(j) &&
                this->getProductAttributes(i).toString() == this->getProductAttributes(j).toString())
            {
                // Combine quantities
                int combinedQuantity = this->quantities.get(i) + this->quantities.get(j);
                this->quantities.set(i, combinedQuantity);
                this->removeProduct(j); // Remove the duplicate
            }
            else
            {
                ++j;
            }
        }
    }
}

InventoryManager InventoryManager::merge(const InventoryManager &inv1,
                                         const InventoryManager &inv2)
{
    // TODO
    InventoryManager mergedInventory;
    for (int i = 0; i < inv1.size(); ++i)
    {
        mergedInventory.addProduct(inv1.getProductAttributes(i), inv1.productNames.get(i), inv1.quantities.get(i));
    }
    for (int i = 0; i < inv2.size(); ++i)
    {
        mergedInventory.addProduct(inv2.getProductAttributes(i), inv2.productNames.get(i), inv2.quantities.get(i));
    }
    mergedInventory.removeDuplicates();
    return mergedInventory;
}

void InventoryManager::split(InventoryManager &section1,
                             InventoryManager &section2,
                             double ratio) const
{
    // TODO
    int section1Size = static_cast<int>(std::ceil(this->size() * ratio));
    section1 = InventoryManager(); // Initialize the sections
    section2 = InventoryManager();

    for (int i = 0; i < this->size(); ++i)
    {
        if (i < section1Size)
        {
            section1.addProduct(this->getProductAttributes(i), this->productNames.get(i), this->quantities.get(i));
        }
        else
        {
            section2.addProduct(this->getProductAttributes(i), this->productNames.get(i), this->quantities.get(i));
        }
    }
}

List2D<InventoryAttribute> InventoryManager::getAttributesMatrix() const
{
    // TODO
    return this->attributesMatrix;
}

List1D<string> InventoryManager::getProductNames() const
{
    // TODO
    return this->productNames;
}

List1D<int> InventoryManager::getQuantities() const
{
    // TODO
    return this->quantities;
}

string InventoryManager::toString() const
{
    // TODO
    ostringstream oss;
    oss << "InventoryManager[AttributesMatrix: " << this->attributesMatrix.toString()
        << ", ProductNames: " << this->productNames.toString()
        << ", Quantities: " << this->quantities.toString() << "]";
    return oss.str();
}

#endif /* INVENTORY_MANAGER_H */
