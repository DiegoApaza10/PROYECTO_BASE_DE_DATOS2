#include <iostream>
template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    Node* head;
    int size;
    
public:
    LinkedList() : head(nullptr), size(0) {}
    ~LinkedList() {
        clear();
    }
    
    void insert(const T& value) {
        Node* newNode = new Node(value);
        
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
        
        size++;
    }
    
    void remove(const T& value) {
        Node* current = head;
        Node* previous = nullptr;
        
        while (current != nullptr) {
            if (current->data == value) {
                if (previous == nullptr) {
                    head = current->next;
                } else {
                    previous->next = current->next;
                }
                
                delete current;
                size--;
                return;
            }
            
            previous = current;
            current = current->next;
        }
    }
    
    void clear() {
        Node* current = head;
        
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        
        head = nullptr;
        size = 0;
    }
    void mostrarNodos() const {
        Node* current = head;
        
        while (current != nullptr) {
            std::cout << current->data << std::endl;
            current = current->next;
        }
    }
    int getSize() const {
        return size;
    }
};