#include <string>

enum operator_type { E, LE, GE };
static const char *operator_type_str[] = { "E", "LE", "GE" };

class Node {
    public:
    virtual std::string to_string() = 0;
};

class IdentifierNode : public Node {
    public:
    IdentifierNode(std::string name);
    virtual std::string to_string();
    private:
    std::string name;
};

class NumericalNode : public Node {
    public:
    NumericalNode(int value);
    virtual std::string to_string();
    private:
    int value;
};

class TermNode : public Node {
    public:
    TermNode(IdentifierNode identfier, NumericalNode numerical);
    virtual std::string to_string();
    private:
    IdentifierNode identifier;
    NumericalNode numerical;
};

class EquationNode : public Node {
    public:
    EquationNode(TermNode term_1, TermNode term_2, operator_type op);
    virtual std::string to_string();
    private:
    TermNode term_1;
    TermNode term_2;
    operator_type op;
};