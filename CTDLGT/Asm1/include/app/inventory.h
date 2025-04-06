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
    List1D(IList<T> *list) : pList(list) {} // Constructor to initialize with IList<T> pointer
    virtual ~List1D();
    
    int size() const;
    T get(int index) const;
    void set(int index, T value);
    void add(const T &value);
    string toString() const;
    
    friend ostream &operator<<(ostream &os, const List1D<T> &list);

    T removeAt(int index); //manually added
    void sort(bool (*compare)(const T &, const T &)); //manually added
    IList<T> *getList() const { return pList; } //manually added
};

//-------------------- List2D --------------------
template <typename T>
class List2D
{
private:
    IList<IList<T>*>* pMatrix;

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
};

struct InventoryAttribute
{
    string name;
    double value;
    InventoryAttribute(const string &name, double value) : name(name), value(value) {}
    string toString() const { return name + ": " + to_string(value); }
};
/*
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
*/
// -------------------- List1D Method Definitions --------------------
template <typename T>
List1D<T>::List1D()
{
    // TODO
    pList = new DLinkedList<T>();
}

template <typename T>
List1D<T>::List1D(int num_elements)
{
    pList = new DLinkedList<T>();
    for (int i = 0; i < num_elements; i++)
    {
        pList->add(T()); // Thêm các phần tử mặc định
    }
}

template <typename T>
List1D<T>::List1D(const T *array, int num_elements)
{
    pList = new DLinkedList<T>();
    for (int i = 0; i < num_elements; i++)
    {
        pList->add(array[i]); // Thêm các phần tử từ mảng
    }
}

template <typename T>
List1D<T>::List1D(const List1D<T> &other)
{
    // TODO
    pList = new DLinkedList<T>();
    for (int i = 0; i < other.size(); i++)
    {
        pList->add(other.get(i)); // Thêm các phần tử từ danh sách khác
    }
}

template <typename T>
List1D<T>::~List1D()
{
    // TODO
    delete pList; 
}

template <typename T>
int List1D<T>::size() const
{
    // TODO
    return pList->size(); 
}

template <typename T>
T List1D<T>::get(int index) const
{
    // TODO
    return pList->get(index);
}

template <typename T>
void List1D<T>::set(int index, T value)
{
    // TODO
    pList->get(index) = value;
}

template <typename T>
void List1D<T>::add(const T &value)
{
    // TODO
    pList->add(value); // Thêm phần tử vào cuối danh sách
}

template <typename T>
string List1D<T>::toString() const
{
    // TODO
    return pList->toString(nullptr); // Chuyển danh sách thành chuỗi
}

template <typename T>
ostream &operator<<(ostream &os, const List1D<T> &list)
{
    // TODO
    os << list.toString(); // Ghi danh sách ra luồng đầu ra
    return os;
}

//--------------------- --------------------- --------------------- --------------------- 
//--------------------- List1D Additional Methods Definitions --------------------
//--------------------- --------------------- --------------------- --------------------- 

template <typename T>
T List1D<T>::removeAt(int index)
{
    // Kiểm tra nếu index không hợp lệ
    if (index < 0 || index >= size())
    {
        throw std::out_of_range("Index is invalid!");
    }

    // gọi phương thức removeAt của DLinkedList
    return pList->removeAt(index);
}

template <typename T>
void List1D<T>::sort(bool (*compare)(const T &, const T &))
{
    // Nếu danh sách rỗng hoặc chỉ có một phần tử, không cần sắp xếp
    if (size() <= 1)
        return;

    // Sử dụng thuật toán Bubble Sort để sắp xếp danh sách
    for (int i = 0; i < size() - 1; i++)
    {
        for (int j = 0; j < size() - i - 1; j++)
        {
            // Lấy hai phần tử liên tiếp
            T &a = pList->get(j);
            T &b = pList->get(j + 1);

            // So sánh và hoán đổi nếu cần
            if (compare ? compare(b, a) : (b < a))
            {
                T temp = a;
                a = b;
                b = temp;
            }
        }
    }
}


// -------------------- List2D Method Definitions --------------------
template <typename T>
List2D<T>::List2D()
{
    // TODO
    pMatrix = new DLinkedList<IList<T>*>();
}

template <typename T>
List2D<T>::List2D(List1D<T> *array, int num_rows)
{
    // TODO
    pMatrix = new DLinkedList<IList<T>*>();
    for (int i = 0; i < num_rows; i++)
    {
        pMatrix->add(array[i].getList()); // Add pointers to List1D<T> objects
    }
}

template <typename T>
List2D<T>::List2D(const List2D<T> &other)
{
    // TODO
    pMatrix = new DLinkedList<DLinkedList<T>*>(); // Khởi tạo danh sách liên kết đôi
    for (int i = 0; i < other.rows(); i++)
    {
        pMatrix->add(other.getRow(i)); // Sao chép từng hàng từ ma trận khác
    }
}

template <typename T>
List2D<T>::~List2D()
{
    // TODO
    for (int i = 0; i < pMatrix->size(); i++)
    {
        delete pMatrix->get(i);
    }
    delete pMatrix;
}

template <typename T>
int List2D<T>::rows() const
{
    // TODO
    return pMatrix->size();
}

template <typename T>
void List2D<T>::setRow(int rowIndex, const List1D<T> &row)
{
    // TODO
    if (rowIndex < 0 || rowIndex >= rows())
        throw std::out_of_range("Row index out of range");

    pMatrix->get(rowIndex) = row; // Gán hàng mới tại vị trí rowIndex
}

template <typename T>
T List2D<T>::get(int rowIndex, int colIndex) const
{
    // TODO
    if (rowIndex < 0 || rowIndex >= rows())
        throw std::out_of_range("Row index out of range");

    List1D<T> row = pMatrix->get(rowIndex); // Lấy hàng tại vị trí rowIndex
    if (colIndex < 0 || colIndex >= row.size())
        throw std::out_of_range("Column index out of range");

    return row.get(colIndex); // Lấy giá trị tại vị trí colIndex trong hàng
}

template <typename T>
List1D<T> List2D<T>::getRow(int rowIndex) const
{
    // TODO
    if (rowIndex < 0 || rowIndex >= rows())
        throw std::out_of_range("Row index out of range");

    return new List1D<T>(pMatrix->DLinkedList<T>::get(rowIndex)); // Trả về hàng tại vị trí rowIndex
}

template <typename T>
string List2D<T>::toString() const
{
    // TODO
    // ostringstream oss;
    // oss << "["; // Bắt đầu chuỗi biểu diễn ma trận

    // for (int i = 0; i < rows(); i++)
    // {
    //     oss << getRow(i).toString(); // Chuyển từng hàng thành chuỗi
    //     if (i < rows() - 1)
    //         oss << ", "; // Thêm dấu phẩy giữa các hàng
    // }

    // oss << "]"; // Kết thúc chuỗi biểu diễn ma trận
    // return oss.str();
    return "a";
}

template <typename T>
ostream &operator<<(ostream &os, const List2D<T> &matrix)
{
    // TODO
    os << matrix.toString(); // Ghi ma trận ra luồng đầu ra
    return os;
}
/*
// -------------------- InventoryManager Method Definitions --------------------
InventoryManager::InventoryManager()
{
    // TODO
    attributesMatrix = List2D<InventoryAttribute>();
    productNames = List1D<string>();
    quantities = List1D<int>();
}

InventoryManager::InventoryManager(const List2D<InventoryAttribute> &matrix,
                                   const List1D<string> &names,
                                   const List1D<int> &quantities)
{
    // TODO

    this->attributesMatrix = matrix;
    this->productNames = names;
    this->quantities = quantities;
}

InventoryManager::InventoryManager(const InventoryManager &other)
{
    // TODO
    this->attributesMatrix = other.getAttributesMatrix();
    this->productNames = other.getProductNames();
    this->quantities = other.getQuantities();
}

int InventoryManager::size() const
{
    // TODO
    return productNames.size();
}

List1D<InventoryAttribute> InventoryManager::getProductAttributes(int index) const
{
    // TODO
    if (index < 0 || index >= size())
    {
        throw std::out_of_range("Index is invalid!");
    }
    return attributesMatrix.getRow(index);
}

string InventoryManager::getProductName(int index) const
{
    // TODO
    if (index < 0 || index >= size())
    {
        throw std::out_of_range("Index is invalid!");
    }
    return productNames.get(index);
}

int InventoryManager::getProductQuantity(int index) const
{
    // TODO
    if (index < 0 || index >= size())
    {
        throw std::out_of_range("Index is invalid!");
    }

    return quantities.get(index);
}

void InventoryManager::updateQuantity(int index, int newQuantity)
{
    // TODO
    if (index < 0 || index >= size())
    {
        throw std::out_of_range("Index is invalid!");
    }

    // Cập nhật số lượng tồn kho của sản phẩm tại vị trí index
    quantities.set(index, newQuantity);
}

void InventoryManager::addProduct(const List1D<InventoryAttribute> &attributes, const string &name, int quantity)
{
    // TODO
    // Thêm danh sách thuộc tính vào ma trận thuộc tính
    attributesMatrix.setRow(attributesMatrix.rows(), attributes);

    // Thêm tên sản phẩm vào danh sách tên sản phẩm
    productNames.add(name);

    // Thêm số lượng sản phẩm vào danh sách số lượng
    quantities.add(quantity);
}

void InventoryManager::removeProduct(int index)
{
    // TODO
    if (index < 0 || index >= size())
    {
        throw std::out_of_range("Index is invalid!");
    }

    // Xóa hàng thuộc tính của sản phẩm tại vị trí index
    attributesMatrix.setRow(index, List1D<InventoryAttribute>());

    // Xóa tên sản phẩm tại vị trí index
    productNames.removeAt(index);

    // Xóa số lượng sản phẩm tại vị trí index
    quantities.removeAt(index);
}

List1D<string> InventoryManager::query(string attributeName, const double &minValue,
                                       const double &maxValue, int minQuantity, bool ascending) const
{
    // TODO
    List1D<string> result;

    // Duyệt qua tất cả các sản phẩm
    for (int i = 0; i < size(); i++)
    {
        // Lấy danh sách thuộc tính của sản phẩm
        List1D<InventoryAttribute> attributes = getProductAttributes(i);

        // Tìm thuộc tính có tên attributeName
        bool attributeFound = false;
        for (int j = 0; j < attributes.size(); j++)
        {
            InventoryAttribute attr = attributes.get(j);
            if (attr.name == attributeName && attr.value >= minValue && attr.value <= maxValue)
            {
                attributeFound = true;
                break;
            }
        }
        // Kiểm tra số lượng tồn kho
        if (attributeFound && getProductQuantity(i) >= minQuantity)
        {
            result.add(getProductName(i));
        }
    }

    // Sắp xếp danh sách kết quả
    if (ascending)
    {
        result.sort([](const string &a, const string &b) { return a < b; });
    }
    else
    {
        result.sort([](const string &a, const string &b) { return a > b; });
    }

    return result;
}

void InventoryManager::removeDuplicates()
{
    // TODO
    for (int i = 0; i < size(); i++)
    {
        for (int j = i + 1; j < size(); j++)
        {
            // Kiểm tra nếu sản phẩm tại vị trí i và j giống hệt nhau
            if (getProductName(i) == getProductName(j) &&
                getProductAttributes(i).toString() == getProductAttributes(j).toString())
            {
                // Cộng dồn số lượng sản phẩm
                updateQuantity(i, getProductQuantity(i) + getProductQuantity(j));

                // Xóa sản phẩm trùng lặp tại vị trí j
                removeProduct(j);

                // Giảm chỉ số j để kiểm tra lại vị trí mới
                j--;
            }
        }
    }
}

InventoryManager InventoryManager::merge(const InventoryManager &inv1,
                                         const InventoryManager &inv2)
{
    // TODO
    List2D<InventoryAttribute> mergedAttributesMatrix;
    List1D<string> mergedProductNames;
    List1D<int> mergedQuantities;

    // Thêm các sản phẩm từ inv1 vào danh sách hợp nhất
    for (int i = 0; i < inv1.size(); i++)
    {
        mergedAttributesMatrix.setRow(mergedAttributesMatrix.rows(), inv1.getProductAttributes(i));
        mergedProductNames.add(inv1.getProductName(i));
        mergedQuantities.add(inv1.getProductQuantity(i));
    }

    // Thêm các sản phẩm từ inv2 vào danh sách hợp nhất
    for (int i = 0; i < inv2.size(); i++)
    {
        mergedAttributesMatrix.setRow(mergedAttributesMatrix.rows(), inv2.getProductAttributes(i));
        mergedProductNames.add(inv2.getProductName(i));
        mergedQuantities.add(inv2.getProductQuantity(i));
    }

    // Tạo đối tượng InventoryManager mới từ các danh sách hợp nhất
    InventoryManager mergedInventory(mergedAttributesMatrix, mergedProductNames, mergedQuantities);

    // Loại bỏ các sản phẩm trùng lặp trong kho hợp nhất
    mergedInventory.removeDuplicates();

    return mergedInventory;
}


void InventoryManager::split(InventoryManager &section1,
                             InventoryManager &section2,
                             double ratio) const
{
    // TODO
    int totalProducts = size();
    int section1Size = static_cast<int>(totalProducts * ratio); // Làm tròn lên
    int section2Size = totalProducts - section1Size;

    // Tạo các danh sách cho section1
    List2D<InventoryAttribute> section1AttributesMatrix;
    List1D<string> section1ProductNames;
    List1D<int> section1Quantities;

    // Tạo các danh sách cho section2
    List2D<InventoryAttribute> section2AttributesMatrix;
    List1D<string> section2ProductNames;
    List1D<int> section2Quantities;

    // Phân chia sản phẩm vào section1
    for (int i = 0; i < section1Size; i++)
    {
        section1AttributesMatrix.setRow(section1AttributesMatrix.rows(), getProductAttributes(i));
        section1ProductNames.add(getProductName(i));
        section1Quantities.add(getProductQuantity(i));
    }

    // Phân chia sản phẩm vào section2
    for (int i = section1Size; i < totalProducts; i++)
    {
        section2AttributesMatrix.setRow(section2AttributesMatrix.rows(), getProductAttributes(i));
        section2ProductNames.add(getProductName(i));
        section2Quantities.add(getProductQuantity(i));
    }

    // Gán các danh sách vào section1 và section2
    section1 = InventoryManager(section1AttributesMatrix, section1ProductNames, section1Quantities);
    section2 = InventoryManager(section2AttributesMatrix, section2ProductNames, section2Quantities);
}

List2D<InventoryAttribute> InventoryManager::getAttributesMatrix() const
{
    // TODO
    return attributesMatrix;
}

List1D<string> InventoryManager::getProductNames() const
{
    // TODO
    return productNames;
}

List1D<int> InventoryManager::getQuantities() const
{
    // TODO
    return quantities;
}

string InventoryManager::toString() const
{
    // TODO
    ostringstream oss;

    // Bắt đầu chuỗi biểu diễn InventoryManager
    oss << "InventoryManager[\n";

    // Thêm thông tin ma trận thuộc tính
    oss << "  AttributesMatrix: " << attributesMatrix.toString() << ",\n";

    // Thêm thông tin danh sách tên sản phẩm
    oss << "  ProductNames: " << productNames.toString() << ",\n";

    // Thêm thông tin danh sách số lượng tồn kho
    oss << "  Quantities: " << quantities.toString() << "\n";

    // Kết thúc chuỗi biểu diễn InventoryManager
    oss << "]";

    return oss.str();
}
*/
#endif /* INVENTORY_MANAGER_H */
