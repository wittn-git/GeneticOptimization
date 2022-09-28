#include "node.hpp"

EquationNode::EquationNode(TermNode* term_1, TermNode* term_2, comparator_type comparator_) : term_1(term_1), term_2(term_2), comparator_(comparator_) {};

std::string EquationNode::to_string(){
    return term_1->to_string() + comparator_type_str[comparator_] + term_2->to_string();
}

std::tuple<bool, double> EquationNode::eval(std::map<std::string, double> values){
    double term_1_value = term_1->eval(values); 
    double term_2_value = term_2->eval(values);
    bool fulfilled;
    switch (comparator_){
    case E:
        fulfilled = term_1_value == term_2_value;
        break;
    case GE:
        fulfilled = term_1_value >= term_2_value;
        break;
    case LE:
        fulfilled = term_1_value <= term_2_value;
        break;
    }
    return {fulfilled, abs(term_1_value - term_2_value)};
}

std::set<std::string> EquationNode::getVariables(){
    std::set<std::string> v1 = term_1->getVariables();
    std::set<std::string> v2 = term_2->getVariables();
    v1.insert(v2.begin(), v2.end());
    return v1;
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

std::set<std::string> OperationNode::getVariables(){
    std::set<std::string> v1 = term_1->getVariables();
    std::set<std::string> v2 = term_2->getVariables();
    v1.insert(v2.begin(), v2.end());
    return v1;
}

IdentifierNode::IdentifierNode(std::string name) : name(name) {};

std::string IdentifierNode::to_string(){
    return name;
}

double IdentifierNode::eval(std::map<std::string, double> values){
    return values[name];
}

std::set<std::string> IdentifierNode::getVariables(){
    return { name };
}

std::string IdentifierNode::getName(){
    return name;
}

NumericalNode::NumericalNode(double value) : value(value) {};
std::string NumericalNode::to_string(){
    return std::to_string(value);
}

double NumericalNode::eval(std::map<std::string, double> values){
    return value;
}

std::set<std::string> NumericalNode::getVariables(){
    return { };
}

double NumericalNode::getValue(){
    return value;
}

ConcatNode::ConcatNode(double value, std::string name) : value(value), name(name) {};

std::string ConcatNode::to_string() {
    return std::to_string(value) + name;
}

double ConcatNode::eval(std::map<std::string, double> values){
    return values[name]*value;
}

std::set<std::string> ConcatNode::getVariables(){
    return { name };
}