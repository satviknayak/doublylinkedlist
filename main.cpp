#include <iostream>
#include <fstream>

using namespace std;

class Node {
public:
    int data;
    Node* prev;
    Node* next;

    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;

public:
    DoublyLinkedList() : head(nullptr) {}

    void insert(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
            newNode->prev = current;
        }
    }

    int findElement(int position) {
        Node* current = head;
        int count = 1;
        while (current && count < position) {
            current = current->next;
            count++;
        }
        if (current) {
            return current->data;
        } else {
            return -1;
        }
    }

    void persistToTextFile(const string& filename) {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            Node* current = head;
            while (current) {
                outFile << current->data << " ";
                current = current->next;
            }
            outFile.close();
            cout << "Data persisted to " << filename << " (text file)" << endl;
        } else {
            cerr << "Unable to open file: " << filename << endl;
        }
    }

    void persistToBinaryFile(const string& filename) {
        ofstream outFile(filename, ios::binary | ios::out);
        if (outFile.is_open()) {
            Node* current = head;
            while (current) {
                outFile.write(reinterpret_cast<char*>(&current->data), sizeof(int));
                current = current->next;
            }
            outFile.close();
            cout << "Data persisted to " << filename << " (binary file)" << endl;
        } else {
            cerr << "Unable to open file: " << filename << endl;
        }
    }
};

int main() {
    DoublyLinkedList list;
    int n,num,pos,flag=1;

    while(flag){
        printf("\nOptions:\n1.Insert Element   2.Find Element   3.Store in .txt   4.Store in .bin\nEnter Choice: ");
        scanf("%d",&n);
        switch(n){
            case 1: printf("Enter the number to be added: ");
                    scanf("%d",&num);
                    list.insert(num);
                    break;
            case 2: printf("Enter the postion to found: ");
                    scanf("%d",&pos);
                    num = list.findElement(pos);
                    if (num != -1)
                        cout << "Element at position " << pos << ": " << num << endl;
                    else
                        cout << "Element not found at position " << pos << endl;
                    break;
            case 3: list.persistToTextFile("doubly_linked_list.txt");
                    break;
            case 4: list.persistToBinaryFile("doubly_linked_list.bin");
                    break;
            default:flag=0;
                    break;
        }
    }

    return 0;
}
