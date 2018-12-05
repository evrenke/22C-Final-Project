#pragma once
template <class ot>
class HashNode {
private:
	ot data;
	HashNode<ot>* next;
	std::string key;
public:
	HashNode() {
		data = nullptr;
		next = nullptr;
		key = "";
	}
	HashNode(ot& obj, std::string str) {
		data = obj;
		next = nullptr;
		key = str;
	}
	~HashNode() {
		delete next;
	}

	std::string getKey() { return key; }
	void setKey(std::string in) { key = in; }

	ot* getData() { return &data; }

	void setData(ot in) { data = in; }
	

	void copy(HashNode<ot>* destination) {
		data = destination->data;
		key = destination->key;
		next = destination->next;
	}

	HashNode<ot>* getNext() { return next; }
	void setNext(HashNode<ot>* in) { next = in; }
};