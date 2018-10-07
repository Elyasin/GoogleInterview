#include <iostream>
#include <vector>

class Node {

protected:
    std::vector<Node *> children;

public:

    virtual ~Node() {
        for (int i=0; i<children.size(); i++) {
            delete children[i];
        }
    }

    void addChildNode(Node *node) {
        children.push_back(node);
    }

    virtual int getValue() =0;

};

class Number : public Node {

    int value;

public:

    Number(int val) {
        value = val;
    }

    int getValue() {
        return value;
    }

};

class PlusOperator : public Node {

public:

    int getValue() {
        int sum = 0;
        for (int i=0; i<children.size(); i++) {
            sum += children[i]->getValue();
        }
        return sum;
    }    

};

class MultiplyOperator : public Node {

public:

    int getValue() {
        int product = 1;
        for (int i=0; i<children.size(); i++) {
            product *= children[i]->getValue();
        }
        return product;
    }
};



Node *calculateValue(std::vector<std::string>&);
std::vector<std::string> get_tokens(std::string&);

//program assumes that input is correct
// tokens must be correct and well defined
// *1 2 - not good: no space between '*' and '2'
// + 99999999999999999999 1 - not good: first number is not within int range
// a 1 2 - not good: 'a' is not recognized token
int main(int argc, char **argv) {
    
    std::vector<std::string> tokens;
    for (std::string line; std::getline(std::cin, line); ) {
        tokens = get_tokens(line);
        Node *root = calculateValue(tokens);
        std::cout << root->getValue() << std::endl;
        delete root;
    }
    

    return 0;
}


Node *calculateValue(std::vector<std::string> &tokens) {

    Node *root = nullptr, *parent = nullptr;

    for (int i=0; i<tokens.size(); i++) {
        if (tokens[i] == "+") {
            PlusOperator *op = new PlusOperator();
            if (parent != nullptr) {
                parent->addChildNode(op);
            }
            parent = op;
        } else if (tokens[i] == "*") {
            MultiplyOperator *op = new MultiplyOperator();
            if (parent != nullptr) {
                parent->addChildNode(op);
            }
            parent = op;
        } else {
            //what if read input too large for int ???
            //what if string is not a number 
            // atoi returns 0 if string is not a number - ok for the moment
            Number *n = new Number(atoi(tokens[i].c_str()));
            if (parent != nullptr) {
                parent->addChildNode(n);
            } else {
                //Return here
                return n;
            }
        }
        if (i==0) root = parent;
    }
    return root; 
}

// token must be separated by space
// *1 2 is not going to be computer as expected
// * 1 2 will be computed as expected
std::vector<std::string> get_tokens(std::string &line) {
    std::vector<std::string> tokens;
    size_t pos = 0, last_pos = 0;
    std::string token;
    while ( (pos = line.find(' ', last_pos)) != std::string::npos ) {
        token = line.substr(last_pos, pos - last_pos );
        tokens.push_back(token);
        last_pos = pos + 1;
    }
    token = line.substr(last_pos);
    tokens.push_back(token);
    return tokens;
}

