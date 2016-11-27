#include <iostream>
#include <string>
#include <vector>
#include <new>

using namespace std;

struct node {
	int data;
	string name;
	node *parent;
	std::vector<node> children;
};

class Tree {
	node root;
public:
	Tree() {
		root.data = 0;
		root.parent = NULL;
		root.name = "Root";
		node temp = addNode(root);
		root.children.push_back(temp);
	}
	int getData(node& n) {
		std::cout << "Data: " << n.data << '\n';
	}
	void setData(node& n, int data) {
		n.data = data;
	}
	int getName(node& n) {
		std::cout << "Name: " << n.name << '\n';
	}
	void setName(node& n, string name) {
		n.name = name;
	}
	node getRoot() {
		return root;
	}
	node addNode(node& parent) {
		int data;
		string name;
		std::cout << "Enter name of node: " << '\n';
		std::cin >> name;
		std::cout << "Enter data for node:" << '\n';
		std::cin >> data;
		node *tempNode = new node;
		tempNode->data = data;
		tempNode->name = name;
		tempNode->parent = &parent;
		addChildren(*tempNode);
		return *tempNode;
	}
	void addChildren(node& n) {
		char ch;
		std::cout << "Do you want to add child for " << n.name << " (y/n)?" << '\n';
		std::cin >> ch;
		while(ch == 'y' || ch == 'Y') {
			n.children.push_back(addNode(n));
			std::cout << "Do you want to add more child for " << n.name << " (y/n)?" << '\n';
			std::cin >> ch;
		}
		std::cout << "Addition of children finished for " << n.name << "!" << '\n';
	}
	void removeChildByName(node& n, string name) {
		int counter = 0;
		std::cout << "Removing only those nodes having no children..." << '\n';
		for (std::vector<node>::iterator i = n.children.begin(); i != n.children.end(); i++) {
			if((*i).name == name && (*i).children.size() == 0) {
				n.children.erase (n.children.begin() + counter);
			}
			counter++;
		}
	}
	void removeChildByData(node& n, int data) {
		int counter = 0;
		std::cout << "Removing only those nodes having no children..." << '\n';
		for (std::vector<node>::iterator i = n.children.begin(); i != n.children.end(); i++) {
			if((*i).data == data && (*i).children.size() == 0) {
				n.children.erase (n.children.begin() + counter);
			}
			counter++;
		}
	}
	void removeChildren(node& n) {
		n.children.clear();
	}
	void show(node n) {
		std::cout << "Name: " << n.name << '\n';
		std::cout << "Data: " << n.data << '\n';
		std::cout << "Number of children:" << n.children.size() << '\n';
		if(n.children.size()) {
			std::cout << "It has following children" << '\n';
			for (std::vector<node>::iterator i = n.children.begin(); i != n.children.end(); i++) {
				std::cout <<"Name: " << (*i).name << " Data: " << (*i).data << '\n';
			}
		} else {
			std::cout << "It has no child!" << '\n';
		}
	}
	void traverse() {
		char ch;
		node temp = root;
		string name;
		do {
			std::cout << "Current Node: " << '\n';
			show(temp);
			std::cout << "Do you want to explore more (y/n)?" << '\n';
			std::cin >> ch;
			if(ch == 'y' || ch == 'Y') {
				std::cout << "Name of child: " << '\n';
				std::cin >> name;
				for (std::vector<node>::iterator i = temp.children.begin(); i != temp.children.end(); i++) {
					if((*i).name == name) {
						temp = (*i);
						break;
					}
				}
			}
		} while(ch == 'y' || ch == 'Y');
	}
	void showAll(node n, int level) {
		string indent;
		if(n.children.size() == 0){
			return;
		}
		for (int j = 0; j < 2*level; j++) {
			indent += " ";
		}
		indent += "-";
		for (std::vector<node>::iterator i = n.children.begin(); i != n.children.end(); i++) {
			std::cout << indent << (*i).name << "(" << (*i).data <<")" << '\n';
			showAll((*i), level + 1);
		}
	}
};

int main(int argc, char const *argv[]) {
	Tree t;
	t.showAll(t.getRoot(), 0);
	std::cout << "Program terminated!!!" << '\n';
	return 0;
}
