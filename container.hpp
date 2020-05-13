#include<iostream>
#ifndef CONTAINER_H
#define CONTAINER_H
using namespace std;
template<typename T>
//���������
class Container{
public:
    // ����������� ����������
    virtual ~Container(){};
    // �����
    virtual void print() const= 0;

    // ������� ��������
    virtual void insert(const T& value) = 0;

    // �������� ��������
    virtual void remove(const T& value) = 0;

    // �������� ������� ��������
    virtual bool exists(const T& value) const = 0;
};

//exeption ��� ��������� ������� �������������� (�������������/����������) c nullptr
class IncorrectIndexException: public std::runtime_error
{
public:
    IncorrectIndexException();
};

template<typename TYPE>
class AvlTreeIterator;

template<typename TYPE>
class AvlTree;

// ��������� ������� ������
template <typename T>
class node {
    friend class AvlTree<T>;
    friend class AvlTreeIterator<int>;
    friend class AvlTreeIterator<const int>;


private:
    int height;
    T key;         // ��������
    node* left;
    node* right;
    node* next; // ��������� �� ��������� ������� ��� ���������
public:

    node(const T& key);
};

/*
 * ���������� ���������
 */
template<typename T>
class AvlTreeIterator {
public:
    // ��� ���������
    // (��� ��������� �� �������� �����������)
    using iterator_category = std::forward_iterator_tag;

    // ���� ��������, ��������� �� ��������, ��������� �� ��������
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    // ��� ��������� ���� ����������
    using difference_type = std::ptrdiff_t;

    // ������������
    AvlTreeIterator();
    AvlTreeIterator(node<T>* el);

    // �������������, ��������� ��������
    // TODO: ��������� *list.end() � ��������
    reference operator*() const;

    // ���������� ���������
    // (��������� -- ������� � ���������� ��������)

    AvlTreeIterator& operator++();
    AvlTreeIterator operator++(int);

    // ��������� *����������*

    bool operator==(const AvlTreeIterator& it) const;
    bool operator!=(const AvlTreeIterator& it) const;

private:
    // ��������� �� ������� �������
    node<T>* p;
};


template<typename T>
class AvlTree: public Container<T>{
    friend class AvlTreeIterator<int>;
    friend class AvlTreeIterator<const int>;
private:

    int height(node<T>* p);
    int bfactor(node<T>* p);
    void fixheight(node<T>* p);
    node<T>* rotateright(node<T>* p); // ������ ������� ������ p
    node<T>* rotateleft(node<T>* q); // ����� ������� ������ q
    node<T>* balance(node<T>* p); // ������������ ���� p
    node<T>* insertprivate(node<T>* p, const T& k); // ������� ����� k � ������ � ������ p
    node<T>* findmin(node<T>* p) const; // ����� ���� � ����������� ������ � ������ p
    node<T>* removemin(node<T>* p); // �������� ���� � ����������� ������ �� ������ p
    node<T>* removeprivate(node<T>* p, const T& k); // �������� ����� k �� ������ p
    void printPrivate(node<T> *p) const;
    void copy_construct_private(node<T>* p);
    void what_next(node<T>* p);
    void update_all(node<T> *p);

    node<T> *root;
public:
    AvlTree();
    AvlTree<T>(const AvlTree<T>& tree);
    void insert(const T& value);
    void remove(const T& value);
    AvlTree& operator =(const AvlTree &tree);
    bool exists(const T& value) const;
    void print() const;

    ~AvlTree();

    using iterator = AvlTreeIterator<int>;
    using const_iterator = AvlTreeIterator<const int>;

    // ��������� ������ ����� �������� ��������� ���������:
    // - �� ������ �������;
    iterator begin() const;
    // - �� ������� "����� ���������� ��������".
    iterator end() const;

    // � ������ ��� � ����������� const-���� ���������
    const_iterator cbegin() const;
    const_iterator cend() const;
};
#endif
