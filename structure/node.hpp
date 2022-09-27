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
        std::string to_string() override;
    private:
        std::string name;
};

class NumericalNode : public Node {
    public:
        NumericalNode(int value);
        std::string to_string() override;
    private:
        int value;
};

class TermNode : public Node {
    public:
        virtual std::string to_string() = 0;
};

class AtomNode : public TermNode {
    public:
        AtomNode(IdentifierNode* identfier, NumericalNode* numerical);
        std::string to_string() override;
    private:
        IdentifierNode* identifier;
        NumericalNode* numerical;
};

class EquationNode : public Node {
    public:
        EquationNode(TermNode* term_1, TermNode* term_2, comparer_type cp);
        std::string to_string() override;
    private:
        TermNode* term_1;
        TermNode* term_2;
        comparer_type cp;
};

class OperationNode : public TermNode {
    public:
        OperationNode(AtomNode* term_1, TermNode* term_2, operator_type op);
        std::string to_string() override;
    private:
        AtomNode* term_1;
        TermNode* term_2;
        operator_type op;
};