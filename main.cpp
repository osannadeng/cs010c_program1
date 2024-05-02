#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string payload;
    Node* next;
};

// creates a new node and sets payload and next outside of struct
// returns node pointer
Node* newNode(const string& payload) {
    Node * myNode = new Node();
    myNode->payload = payload;
    myNode->next = nullptr;
    return myNode;
}

// add all the names to nodes and in a circular linked list
Node* loadGame(int n, const vector<string>& names) {
    Node* head = nullptr;
    Node* prev = nullptr;
    string name;

    for (int i = 0; i < n; ++i) { // load first n names
        name = names.at(i);
	      // special edge case when the list is initially empty
        if (head == nullptr) {
            head = newNode(name);
            prev = head;
        } else {
            prev->next = newNode(name);
            prev = prev->next;
        }
    }

    if (prev != nullptr) {  // if n is not 0 aka list is not empty
      prev->next = head; // make circular
    }
    return head;
}

// prints list from a starting node
void print(const Node* start) {
  const Node* curr = start;
  // will check for nullptr to not run if list is empty
  // uses 'curr == start' to exit to check if loop is completed,
  // which would mean that curr node has return to the start
  while (curr != nullptr) {
    cout << curr->payload << endl;
    curr = curr->next;
    if (curr == start) {
      break; // exit circular list
    }
  }
}

// josephus w circular list, k = num skips
Node* runGame(Node* start, int k) {
    Node* curr = start;
    Node* prev = curr;
    while (curr->next != curr) { // exit condition, last person standing
        for (int i = 0; i < k; ++i) { // find kth node
        // if curr isnt't the first node
        // will not change prev if curr is at the start
          if (prev != curr) {
            prev = prev->next;
          }
          curr = curr->next;
        }

        prev->next = curr->next; // delete kth node
        delete curr;
        curr = prev->next;
    }

    return curr; // last person standing
}

/* Driver program to test above functions */
int main() {
    int n=1, k=1; // n = num names; k = num skips (minus 1)
    string name;
    vector<string> names;

    // get inputs
    cin >> n >> k;
    // check if theres an error before using
    if (!cin) throw runtime_error("error reading n and k from input");
    
    while (cin >> name && name != ".") { names.push_back(name); } // EOF or . ends input

    // initialize and run game
    Node* startPerson = loadGame(n, names);
    Node* lastPerson = runGame(startPerson, k);

    if (lastPerson != nullptr) {  // if a winner exists
        cout << lastPerson->payload << " wins!" << endl;
        delete lastPerson;  // only one left to deallocate
    } else {
        cout << "error: null game" << endl;
    }

    return 0;
}

