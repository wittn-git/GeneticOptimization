#include "node.hpp"

EquationNode::EquationNode(TermNode* term_1, TermNode* term_2, comparer_type cp) : term_1(term_1), term_2(term_2), cp(cp) {};
std::string EquationNode::to_string(){
    return term_1->to_string() + comparer_type_str[cp] + term_2->to_string();
}

OperationNode::OperationNode(AtomNode* term_1, TermNode* term_2, operator_type op) : term_1(term_1), term_2(term_2), op(op) {};
std::string OperationNode::to_string(){
    return term_1->to_string() + operator_type_str[op] + term_2->to_string();
}

AtomNode::AtomNode(IdentifierNode* identifier, NumericalNode* numerical) : identifier(identifier), numerical(numerical) {};
std::string AtomNode::to_string() {
    return numerical->to_string() + identifier->to_string();
}

IdentifierNode::IdentifierNode(std::string name) : name(name) {};
std::string IdentifierNode::to_string(){
    return name;
}

NumericalNode::NumericalNode(int value) : value(value) {};
std::string NumericalNode::to_string(){
    return std::to_string(value);
}