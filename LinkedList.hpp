#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;
};

template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const {
		printNodeF(tail);
	}
	void printReverse() const {
		printNodeB(head);
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {return count;}
	Node<T>* getHead() {return head;}
	const Node<T>* getHead() const {return head;}
	Node<T>* getTail() {return tail;}
	const Node<T>* getTail() const {return tail;}

	// Insertion
	void addHead(const T& data) {
		Node<T>* temp = new Node<T>;
		temp->data = data;
		temp->next = head;
		if (head != nullptr) {
			head->prev = temp;
		}
		head = temp;
		if (count == 0) {
			tail = head;
		}
		count ++;
	}

	void addTail(const T& data) {
		Node<T>* temp = new Node<T>;
		temp->data = data;
		temp->prev = tail;
		if (tail != nullptr) {
			tail->next = temp;
		}
		tail = temp;
		if (count == 0) {
			head = tail;
		}
		count ++;
	}

	// Removal
	bool removeHead() {
		if (count == 0) {return false;}
		Node<T>* prev_head = head;
		head = head->next;
		delete prev_head;
		if (count == 1) {
			tail = nullptr;
		}
		count--;
		return true;
	}
	bool removeTail() {
		if (count == 0) {return false;}
		Node<T>* prev_tail = tail;
		tail = tail->prev;
		delete prev_tail;
		tail->next = nullptr;
		if (count == 1) {
			head = nullptr;
		}
		count--;
		return true;
	}
	void clear() {
		if (head != nullptr) {
			removeNode(head);
			head = nullptr;
			tail = nullptr;
		}
		count = 0;
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		head = other.head;
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
		return *this;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		clear();
		addNode(rhs.getHead());
		count = rhs.count;
		return *this;
	}

	// Construction/Destruction
	LinkedList() {
		head = nullptr;
		tail = nullptr;
		count = 0;
	}
	LinkedList(const LinkedList<T>& list) {
		addNode(list.getHead());
		count = list.count;
	}
	LinkedList(LinkedList<T>&& other) noexcept {
		head = other.head;
		tail = other.tail;
		count = other.count;

		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	~LinkedList() {
		clear();
	}

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head = nullptr;
	Node<T>* tail = nullptr;
	unsigned int count = 0;

	void removeNode(Node<T>* address) {
		if (address == nullptr) {return;}
		if (address->next == nullptr) {
			delete address;
			return;
		}
		removeNode(address->next);
		delete address;
	}

	void addNode(const Node<T>* other_head) {
		if (other_head->next == nullptr) {
			addHead(other_head->data);
			return;
		}
		addNode(other_head->next);
		addHead(other_head->data);
	}

	void printNodeB(Node<T>* head) const{
		if (head->next == nullptr) {
			std::cout << head->data << std::endl;
			return;
		}
		printNodeB(head->next);
		std::cout << head->data << std::endl;
	}

	void printNodeF(Node<T>* tail) const{
		if (tail->prev == nullptr) {
			std::cout << tail->data << std::endl;
			return;
		}
		printNodeF(tail->prev);
		std::cout << tail->data << std::endl;
	}
};



