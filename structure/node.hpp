#pragma once
#include <string>
#include <set>
#include <map>
#include <tuple>
#include <cmath>

enum comparator_type { E, LE, GE };
static const char *comparator_type_str[] = { "=", "<=", ">=" };
enum operator_type { P, M };
static const char *operator_type_str[] = { "+", "-" };

struct Range{
    double min, max;
};

class Node {
    public:
        virtual std::string to_string() = 0;
        virtual std::set<std::string> getVariables() = 0;
};

class TermNode : public Node {
    public:
        virtual std::string to_string() = 0;
        virtual double eval(std::map<std::string, double> values) = 0;
        virtual std::set<std::string> getVariables() = 0;
};

class AtomNode : public TermNode {
    public:
        virtual std::string to_string() = 0;
        virtual double eval(std::map<std::string, double> values) = 0;
        virtual std::set<std::string> getVariables() = 0;
};

class EquationNode : public Node {
    public:
        EquationNode(TermNode* term_1, TermNode* term_2, comparator_type comparator_);
        std::string to_string() override;
        std::tuple<bool, double> eval(std::map<std::string, double> values);
        std::set<std::string> getVariables() override;
    private:
        TermNode* term_1;
        TermNode* term_2;
        comparator_type comparator_;
};

class OperationNode : public TermNode {
    public:
        OperationNode(AtomNode* term_1, TermNode* term_2, operator_type operator_);
        std::string to_string() override;
        double eval(std::map<std::string, double> values) override;
        std::set<std::string> getVariables() override;
    private:
        AtomNode* term_1;
        TermNode* term_2;
        operator_type operator_;
};

class IdentifierNode : public AtomNode {
    public:
        IdentifierNode(std::string name);
        std::string to_string() override;
        double eval(std::map<std::string, double> values) override;
        std::set<std::string> getVariables() override;
        std::string getName();
    private:
        std::string name;
};

class NumericalNode : public AtomNode {
    public:
        NumericalNode(double value);
        std::string to_string() override;
        double eval(std::map<std::string, double> values) override;
        std::set<std::string> getVariables() override;
        double getValue();
    private:
        double value;
};

class ConcatNode : public AtomNode {
    public:
        ConcatNode(double value, std::string name);
        std::string to_string() override;
        double eval(std::map<std::string, double> values) override;
        std::set<std::string> getVariables() override;
    private:
        double value;
        std::string name;
};
