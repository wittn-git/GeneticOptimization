#include <string>

enum operator_type { E, LE, GE };

class Node {};

class IdentifierNode : public Node {
    public:
    IdentifierNode(std::string name);
    private:
    std::string name;
};

class NumericalNode : public Node {
    public:
    NumericalNode(int value);
    private:
    int value;
};

class TermNode : public Node {
    public:
    TermNode(IdentifierNode identfier, NumericalNode numerical);
    private:
    IdentifierNode identifier;
    NumericalNode numerical;
};

class EquationNode : public Node {
    public:
    EquationNode(TermNode term_1, TermNode term_2, operator_type op);
    private:
    TermNode term_1;
    TermNode term_2;
    operator_type op;
};