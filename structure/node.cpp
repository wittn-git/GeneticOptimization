#include "node.hpp"

EquationNode::EquationNode(TermNode* term_1, TermNode* term_2, comparator_type comparator_) : term_1(term_1), term_2(term_2), comparator_(comparator_) {};

std::string EquationNode::to_string(){
    return term_1->to_string() + comparator_type_str[comparator_] + term_2->to_string();
}

bool EquationNode::eval(std::map<std::string, double> values){
    switch (comparator_){
    case E:
        return term_1->eval(values) == term_2->eval(values);
    case GE:
        return term_1->eval(values) >= term_2->eval(values);
    case LE:
        return term_1->eval(values) <= term_2->eval(values);
    }
    throw std::invalid_argument("Wrong evaluation of Equation.");
}

OperationNode::OperationNode(AtomNode* term_1, TermNode* term_2, operator_type operator_) : term_1(term_1), term_2(term_2), operator_(operator_) {};

std::string OperationNode::to_string(){
    return term_1->to_string() + operator_type_str[operator_] + term_2->to_string();
}

double OperationNode::eval(std::map<std::string, double> values){
    switch (operator_){
    case P:
        return term_1->eval(values) + term_2->eval(values);
    case M:
        return term_1->eval(values) - term_2->eval(values);
    }
    throw std::invalid_argument("Wrong evaluation of Operation.");
}

IdentifierNode::IdentifierNode(std::string name) : name(name) {};

std::string IdentifierNode::to_string(){
    return name;
}

double IdentifierNode::eval(std::map<std::string, double> values){
    return values[name];
}

NumericalNode::NumericalNode(int value) : value(value) {};
std::string NumericalNode::to_string(){
    return std::to_string(value);
}

double NumericalNode::eval(std::map<std::string, double> values){
    return value;
}

ConcatNode::ConcatNode(int value, std::string name) : value(value), name(name) {};

std::string ConcatNode::to_string() {
    return std::to_string(value) + name;
}

double ConcatNode::eval(std::map<std::string, double> values){
    return values[name]*value;
}