#include "node.hpp"

EquationNode::EquationNode(TermNode term_1, TermNode term_2, operator_type op) : term_1(term_1), term_2(term_2), op(op) {};

TermNode::TermNode(IdentifierNode identifier, NumericalNode numerical) : identifier(identifier), numerical(numerical) {};

IdentifierNode::IdentifierNode(std::string name) : name(name) {};

NumericalNode::NumericalNode(int value) : value(value) {};