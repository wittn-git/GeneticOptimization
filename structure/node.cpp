#include "node.hpp"

EquationNode::EquationNode(AtomNode atom_1, AtomNode atom_2, comparer_type cp) : atom_1(atom_1), atom_2(atom_2), cp(cp) {};
std::string EquationNode::to_string(){
    return atom_1.to_string() + comparer_type_str[cp] + atom_2.to_string();
}

OperationNode::OperationNode(AtomNode atom_1, AtomNode atom_2, operator_type op) : atom_1(atom_1), atom_2(atom_2), op(op) {};
std::string OperationNode::to_string(){
    return atom_1.to_string() + operator_type_str[op] + atom_2.to_string();
}

AtomNode::AtomNode(IdentifierNode identifier, NumericalNode numerical) : identifier(identifier), numerical(numerical) {};
std::string AtomNode::to_string(){
    return numerical.to_string() + identifier.to_string();
}

IdentifierNode::IdentifierNode(std::string name) : name(name) {};
std::string IdentifierNode::to_string(){
    return name;
}

NumericalNode::NumericalNode(int value) : value(value) {};
std::string NumericalNode::to_string(){
    return std::to_string(value);
}