#include<iostream>
#include<map>
using namespace std;

class ExprNode{
    private:
        enum class NodeType
        {
            OPERATOR,
            VARIABLE,
            CONSTANT
            // FUNCTION
        };
        NodeType type;
        char op;
        char var;
        int val;
        string func;
        ExprNode *left, *right;
    public:
        ExprNode();
        ExprNode(char op);
        ExprNode(char var,bool isVar);
        ExprNode(int val);
       // ExprNode(const string &function);
        ~ExprNode();
        friend class Expression;
};

ExprNode::ExprNode():left(nullptr),right(nullptr){}
ExprNode::ExprNode(char op):type(NodeType::OPERATOR),op(op),var('\0'),val(0),left(nullptr),right(nullptr){}
ExprNode::ExprNode(char var,bool isVar):type(NodeType::VARIABLE),op('\0'),var(var),val(0),left(nullptr),right(nullptr){}
ExprNode::ExprNode(int val):type(NodeType::CONSTANT),op('\0'),var('\0'),val(val),left(nullptr),right(nullptr){}
// ExprNode::ExprNode(const string &function):func(function),type(NodeType::FUNCTION),val(0),op('\0'),var('\0'),left(nullptr),right(nullptr){}
ExprNode::~ExprNode(){
    delete left;
    delete right;
}

