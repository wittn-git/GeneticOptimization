#include <string>

enum comparer_type { E, LE, GE };
static const char *comparer_type_str[] = { "=", "<=", ">=" };
enum operator_type { P, M };
static const char *operator_type_str[] = { "+", "-" };

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

class AtomNode : public Node {
    public:
    AtomNode(IdentifierNode identfier, NumericalNode numerical);
    virtual std::string to_string();
    private:
    IdentifierNode identifier;
    NumericalNode numerical;
};

class EquationNode : public Node {
    public:
    EquationNode(AtomNode term_1, AtomNode term_2, comparer_type cp);
    virtual std::string to_string();
    private:
    AtomNode term_1;
    AtomNode term_2;
    comparer_type cp;
};

class OperationNode : public Node {
    public:
    OperationNode(AtomNode term_1, AtomNode term_2, operator_type op);
    virtual std::string to_string();
    private:
    AtomNode term_1;
    AtomNode term_2;
    operator_type op;
};