#include <iostream>
#include <map>
#include <string>
#include <stack>
#include <vector>
#include <cmath>
#include<queue>
#include<iomanip>
#include<algorithm>
#include<utility>
#include <exception>
#include "ExprNode.h"
using namespace std;

class Expression {
private:
    struct NodeInfo {
        string value;
        int serialNumber;
    };
    ExprNode* root; // expression tree's root
    map<char, int> variables;
    ExprNode* buildTree(const string &expr, int &pos);
    static ExprNode* copyTree(ExprNode* node) {
        if (!node) return nullptr;
        
        ExprNode* newNode = nullptr;
        
        // 根据节点类型创建新节点
        switch (node->type) {
            case ExprNode::NodeType::OPERATOR:
                newNode = new ExprNode(node->op);
                newNode->type = ExprNode::NodeType::OPERATOR;
                break;
                
            case ExprNode::NodeType::VARIABLE:
                newNode = new ExprNode(node->var, true);  // true indicates it's a variable
                newNode->type = ExprNode::NodeType::VARIABLE;
                break;
                
            case ExprNode::NodeType::CONSTANT:
                newNode = new ExprNode(node->val);
                newNode->type = ExprNode::NodeType::CONSTANT;
                break;
        }
        
        if (!newNode) return nullptr;
        
        // 复制子树
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        
        return newNode;
    }
    void deleteTree(ExprNode* root);
    void printInfix(ExprNode* root, int parentPrecedence); // print infix expression
    int evaluate(const string& res);
    int getPrecedence(ExprNode *node);
    void postOrder(ExprNode *root, string &res);
    ExprNode* diffHelper(ExprNode *node, char variable);
    void displayFormattedTree(const vector<NodeInfo> &array, int size, int depth);
    int getTreeDepth(ExprNode *node);
    ExprNode* mergeConstHelper(ExprNode *node);
    int countNodes(ExprNode* node);
    void markNodes(ExprNode *node, int number, vector<NodeInfo> &array, int &count);
    void fillMap(vector<ExprNode*>& map, ExprNode* node, int index);
    void printNode(ExprNode *node, int width);
    void printConnections(int depth, int j, int totalNodes, vector<ExprNode *> &map);

public:
    Expression();
    Expression(ExprNode* r):root(r){}
    Expression(const Expression& other) {
        root = copyTree(other.root);
    }
    Expression& operator=(const Expression& other) {
        if (this != &other) {
            deleteTree(root);
            root = copyTree(other.root);
        }
        return *this;
    }
    ~Expression();
    void ReadExpr(const string& expr);
    void WriteExpr(); // print infix expression
    void Assign(char v, int c); // assign value to expression
    int Value(); // evaluate
    // 在Expression类中的CompoundExpr实现
    static Expression CompoundExpr(char op, const Expression& e1, const Expression& e2) {
        // 检查操作符是否有效
        if (op != '+' && op != '-' && op != '*' && op != '/' && op != '^') {
            throw runtime_error("Invalid operator for compound expression");
        }
        
        // 检查输入表达式是否有效
        if (!e1.root || !e2.root) {
            throw runtime_error("Invalid input expressions for compound operation");
        }

        Expression result;
        result.root = new ExprNode(op);
        result.root->left = copyTree(e1.root);
        result.root->right = copyTree(e2.root);

        // 复制变量映射
        result.variables = e1.variables;
        for (const auto& pair : e2.variables) {
            result.variables[pair.first] = pair.second;
        }

        return result;
    }
    void DisplayTree(); // visualize tree
    Expression Diff(char variable);
    void MergeConst();
    ExprNode* getRoot() {
        return root;
    }
    class ExpressionException;
};

class Expression::ExpressionException {
private:
    string msg;
public:
    ExpressionException(const string& msg) : msg(msg) {}
    const string& what() const { return msg; }
};

Expression::Expression():root(nullptr){}
Expression::~Expression() {
    deleteTree(root);
}

void Expression::ReadExpr(const string& expr) {
    int pos = 0;
    root = buildTree(expr, pos);
}

ExprNode* Expression::buildTree(const string &expr, int &pos) {
    if (pos == expr.length()) {
        return nullptr;
    }
    char c = expr[pos++];

    if (isdigit(c)) {
        int num = c - '0';
        return new ExprNode(num);
    } else if (isalpha(c)) {
        variables.insert({c, 0});
        return new ExprNode(c, true);
    } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
        ExprNode *midnode = new ExprNode(c);
        midnode->left = buildTree(expr, pos);
        midnode->right = buildTree(expr, pos);
        return midnode;
    } else {
        throw runtime_error("Undefined character!");
    }
}

void Expression::WriteExpr() {
    if (!root) {
        cout << "Empty expression";
        return;
    }
    printInfix(root, 0);
    cout << endl;
}

int Expression::getPrecedence(ExprNode* node) {
    if (node->type != ExprNode::NodeType::OPERATOR) {
        return 100; // 非运算符返回最高优先级
    }

    switch (node->op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}


void Expression::printInfix(ExprNode* node, int parentPrecedence) {
    if (!node) return;

    int currentPrecedence = getPrecedence(node);
    bool needParentheses = currentPrecedence < parentPrecedence;

    if (needParentheses) cout << "(";

    if (node->type == ExprNode::NodeType::OPERATOR) {
        printInfix(node->left, currentPrecedence);
        cout << " " << node->op << " ";
        printInfix(node->right, currentPrecedence);
    } 
    else if (node->type == ExprNode::NodeType::VARIABLE) {
        cout << node->var;
    }
    else { // CONSTANT
        cout << node->val;
    }

    if (needParentheses) cout << ")";
}

void Expression::Assign(char v, int c) {
    variables[v] = c;
}

int Expression::Value() {
    
    string res;
    postOrder(root, res);
    return evaluate(res);
}

void Expression::postOrder(ExprNode* root, string& res) {
    if (root == nullptr)
        return;
    postOrder(root->left, res);
    postOrder(root->right, res);
    
    if (root->type == ExprNode::NodeType::OPERATOR) {
        res += root->op;
    } else if (root->type == ExprNode::NodeType::VARIABLE) {
        res += to_string(variables[root->var]);
    } else if (root->type == ExprNode::NodeType::CONSTANT) {
        res += to_string(root->val);
    }
    res += ' ';
}

int Expression::evaluate(const string& res) {
    if (res.empty()) return 0;
    stack<int> nums;
    string token;
    for (size_t i = 0; i < res.length(); i++) {
        if (isdigit(res[i]) || (res[i] == '-' && isdigit(res[i + 1]))) {
            int num = 0;
            while (isdigit(res[i])) {
                num = num * 10 + (res[i] - '0');
                ++i;
            }
            nums.push(num);
        } else if (isspace(res[i])) {
            continue;
        } else {
            int val2 = nums.top();
            nums.pop();
            int val1 = nums.top();
            nums.pop();
            switch (res[i]) {
                case '+':
                    nums.push(val1 + val2);
                    break;
                case '-':
                    nums.push(val1 - val2);
                    break;
                case '*':
                    nums.push(val1 * val2);
                    break;
                case '/':
                    if (val2 == 0) {
                        throw runtime_error("Division by zero!");
                    }
                    nums.push(val1 / val2);
                    break;
                case '^':
                    nums.push(pow(val1, val2));
                    break;
                default:
                    throw runtime_error("Undefined operator: " + string(1, res[i]));
            }
        }
    }
    return nums.top();
}

void Expression::fillMap(vector<ExprNode*>& map, ExprNode* node, int index) {
        if (!node) return;
        map[index] = node;
        fillMap(map, node->left, 2 * index + 1);
        fillMap(map, node->right, 2 * index + 2);
    }


 void Expression::printNode(ExprNode* node, int width) {
        if (!node) {
            cout << string(width, ' '); // Empty space for null nodes
            return;
        }

        switch (node->type) {
        case ExprNode::NodeType::OPERATOR:
            cout << string(width, ' ') << node->op;
            break;
        case ExprNode::NodeType::VARIABLE:
            cout << string(width, ' ') << node->var;
            break;
        case ExprNode::NodeType::CONSTANT:
            cout << string(width, ' ') << node->val;
            break;
        
        }
    }


void Expression::printConnections(int depth, int j, int totalNodes, vector<ExprNode*>& map) {
    int width = 1 << (depth - j);
    int preIndent = (1 << (depth - j - 1)) - 1;
    for (int i = 0; i < (1 << j); i++) {
        int index = (1 << j) + i;
        if (index < totalNodes && map[index]) {
            if (2 * index + 1 < totalNodes && map[2 * index + 1]) {
                cout << "/";
            } else {
                cout << " ";
            }
            cout << string(width * 2 - 2, ' ');
            if (2 * index + 2 < totalNodes && map[2 * index + 2]) {
                cout << "\\";
            } else {
                cout << " ";
            }
        } else {
            cout << string(width * 2, ' ');
        }
    }
    cout << endl;
}

void Expression::DisplayTree() {
    if (!root) {
        cout << "Empty tree!" << endl;
        return;
    }

    // 第一次遍历计算树的深度
    queue<ExprNode*> q1;
    q1.push(root);
    int max_depth = 0;
    while (!q1.empty()) {
        int level_size = q1.size();
        for (int i = 0; i < level_size; i++) {
            ExprNode* curr = q1.front();
            q1.pop();
            if (curr->left) q1.push(curr->left);
            if (curr->right) q1.push(curr->right);
        }
        max_depth++;
    }

    // 第二次遍历打印树
    queue<ExprNode*> q2;
    q2.push(root);
    int depth = 0;
    
    while (!q2.empty() && depth < max_depth) {
        int level_size = q2.size();
        int spaces = pow(2, max_depth - depth - 1); // 前导空格
        int between_spaces = pow(2, max_depth - depth) - 1; // 节点间空格
        
        // 打印前导空格
        cout << string(spaces - 1, ' ');
        
        // 打印当前层节点
        for (int i = 0; i < level_size; i++) {
            ExprNode* curr = q2.front();
            q2.pop();
            
            if (curr) {
                string value;
                switch (curr->type) {
                    case ExprNode::NodeType::OPERATOR:
                        value = string(1, curr->op);
                        break;
                    case ExprNode::NodeType::VARIABLE:
                        value = string(1, curr->var);
                        break;
                    case ExprNode::NodeType::CONSTANT:
                        value = to_string(curr->val);
                        break;
                }
                cout << value;
                q2.push(curr->left);
                q2.push(curr->right);
            } else {
                cout << " ";
                q2.push(nullptr);
                q2.push(nullptr);
            }
            
            // 打印节点间空格
            if (i < level_size - 1) {
                cout << string(between_spaces, ' ');
            }
        }
        cout << endl;
        
        // 如果不是最后一层，打印连接线
        if (depth < max_depth - 1) {
            // 打印连接线的前导空格
            cout << string(spaces - 2, ' ');
            
            for (int i = 0; i < level_size; i++) {
                ExprNode* curr = q2.front();
                if (curr && (curr->left || curr->right)) {
                    cout << "/";
                    cout << string(between_spaces/2, ' ');
                    cout << "\\";
                } else {
                    cout << " ";
                    cout << string(between_spaces/2, ' ');
                    cout << " ";
                }
                
                if (i < level_size - 1) {
                    cout << string(between_spaces - between_spaces/2 - 1, ' ');
                }
            }
            cout << endl;
        }
        
        depth++;
    }
}

int Expression::getTreeDepth(ExprNode* node) {
    if (!node) return 0;
    int leftDepth = getTreeDepth(node->left);
    int rightDepth = getTreeDepth(node->right);
    return max(leftDepth, rightDepth) + 1;
}

int Expression::countNodes(ExprNode* node) {
    if (!node) return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

void Expression::markNodes(ExprNode* node, int number, vector<NodeInfo>& array, int& count) {
    if (!node) return;
    
    string nodeValue;
    if (node->type == ExprNode::NodeType::OPERATOR) {
        nodeValue = string(1, node->op);
    } else if (node->type == ExprNode::NodeType::VARIABLE) {
        nodeValue = string(1, node->var);
    }else {
        nodeValue = to_string(node->val);
    }
    
    array[count].value = nodeValue;
    array[count].serialNumber = number;
    count++;
    
    markNodes(node->left, number * 2, array, count);
    markNodes(node->right, number * 2 + 1, array, count);
}

void Expression::displayFormattedTree(const vector<NodeInfo>& array, int size, int depth) {
    for (int level = 0; level < depth; level++) {
        int levelStart = pow(2, level);
        int levelEnd = pow(2, level + 1);
        int spacing = pow(2, depth - level + 1) - 1;
        
        for (int i = 0; i < spacing / 2; i++) cout << " ";
        
        for (int pos = levelStart; pos < levelEnd; pos++) {
            bool found = false;
            for (int i = 0; i < size; i++) {
                if (array[i].serialNumber == pos) {
                    cout << array[i].value;
                    found = true;
                    break;
                }
            }
            if (!found) cout << " ";
            
            for (int i = 0; i < spacing; i++) cout << " ";
        }
        cout << endl;
        
        if (level < depth - 1) {
            for (int i = 0; i < spacing / 2 - 1; i++) cout << " ";
            
            for (int pos = levelStart; pos < levelEnd; pos++) {
                bool hasChildren = false;
                for (int i = 0; i < size; i++) {
                    if (array[i].serialNumber == pos) {
                        bool hasLeft = false, hasRight = false;
                        for (int j = 0; j < size; j++) {
                            if (array[j].serialNumber == pos * 2) hasLeft = true;
                            if (array[j].serialNumber == pos * 2 + 1) hasRight = true;
                        }
                        
                        if (hasLeft && hasRight) cout << "/\\";
                        else if (hasLeft) cout << "/ ";
                        else if (hasRight) cout << " \\";
                        else cout << "  ";
                        
                        hasChildren = true;
                        break;
                    }
                }
                if (!hasChildren) cout << "  ";
                
                for (int i = 0; i < spacing - 2; i++) cout << " ";
            }
            cout << endl;
        }
    }
}



ExprNode* Expression::diffHelper(ExprNode* node, char variable) {
    if (!node) {
        return new ExprNode(0);
    }

    try {
        switch (node->type) {
            case ExprNode::NodeType::CONSTANT:
                return new ExprNode(0);  // 常数导数为0

            case ExprNode::NodeType::VARIABLE:
                return new ExprNode(node->var == variable ? 1 : 0);  // 变量导数

            case ExprNode::NodeType::OPERATOR: {
                // 确保是运算符节点
                if (!node->left || !node->right) {
                    throw ExpressionException("Invalid operator node: missing operands");
                }

                switch (node->op) {
                    case '+': {
                        ExprNode* result = new ExprNode('+');
                        result->type = ExprNode::NodeType::OPERATOR;
                        result->left = diffHelper(node->left, variable);
                        result->right = diffHelper(node->right, variable);
                        return result;
                    }
                    case '-': {
                        ExprNode* result = new ExprNode('-');
                        result->type = ExprNode::NodeType::OPERATOR;
                        result->left = diffHelper(node->left, variable);
                        result->right = diffHelper(node->right, variable);
                        return result;
                    }
                    case '*': {
                        ExprNode* result = new ExprNode('+');
                        result->type = ExprNode::NodeType::OPERATOR;
                        
                        ExprNode* term1 = new ExprNode('*');
                        term1->type = ExprNode::NodeType::OPERATOR;
                        term1->left = diffHelper(node->left, variable);
                        term1->right = copyTree(node->right);
                        
                        ExprNode* term2 = new ExprNode('*');
                        term2->type = ExprNode::NodeType::OPERATOR;
                        term2->left = copyTree(node->left);
                        term2->right = diffHelper(node->right, variable);
                        
                        result->left = term1;
                        result->right = term2;
                        return result;
                    }
                    case '^': {
                        // 只处理最简单的情况：常数幂
                        if (node->right->type == ExprNode::NodeType::CONSTANT) {
                            int power = node->right->val;
                            if (power == 0) return new ExprNode(0);
                            if (power == 1) return diffHelper(node->left, variable);
                            
                            ExprNode* result = new ExprNode('*');
                            result->type = ExprNode::NodeType::OPERATOR;
                            result->left = new ExprNode(power);
                            
                            ExprNode* powerTerm = new ExprNode('^');
                            powerTerm->type = ExprNode::NodeType::OPERATOR;
                            powerTerm->left = copyTree(node->left);
                            powerTerm->right = new ExprNode(power - 1);
                            
                            result->right = powerTerm;
                            return result;
                        }
                        throw ExpressionException("Only constant power is supported");
                    }
                    default:
                        throw ExpressionException("Unsupported operator");
                }
            }
            default:
                throw ExpressionException("Unknown node type");
        }
    } catch (const std::exception& e) {
        // 清理已分配的内存
        throw;
    }
}

Expression Expression::Diff(char variable) {
    // try {
        
    // } 
    if (!root) {
        return Expression(new ExprNode(0));
    }
    ExprNode* diffRoot = diffHelper(root, variable);
    return Expression(diffRoot);
    
    // catch (const std::exception& e) {
    //     throw ExpressionException(string("Derivative Error: ") + e.what());
    // }
}

// ExprNode* Expression::copyTree(ExprNode* root) {
//     if (!root) return nullptr;
    
//     ExprNode* newNode = nullptr;
//     switch (root->type) {
//         case ExprNode::NodeType::OPERATOR:
//             newNode = new ExprNode(root->op);
//             break;
//         case ExprNode::NodeType::VARIABLE:
//             newNode = new ExprNode(root->var, true);
//             break;
//         case ExprNode::NodeType::CONSTANT:
//             newNode = new ExprNode(root->val);
//             break;
//     }

//     newNode->type = root->type;  // 确保类型被正确复制
//     newNode->left = copyTree(root->left);
//     newNode->right = copyTree(root->right);

//     return newNode;
// }

void Expression::MergeConst() {
    root = mergeConstHelper(root);
}

ExprNode* Expression::mergeConstHelper(ExprNode* node) {
    // 空节点检查
    if (node == nullptr) {
        return nullptr;
    }

    // 如果是变量节点，检查是否已赋值
    if (node->type == ExprNode::NodeType::VARIABLE) {
        if (variables[node->var]) {  // 检查变量是否已赋值
            // 变量已赋值，转换为常量节点
            ExprNode* constNode = new ExprNode(variables[node->var]);
            delete node;
            return constNode;
        }
        return node;
    }

    // 如果是常量节点，直接返回
    if (node->type == ExprNode::NodeType::CONSTANT) {
        return node;
    }

    // 递归处理左右子树
    if (node->left) {
        node->left = mergeConstHelper(node->left);
    }
    if (node->right) {
        node->right = mergeConstHelper(node->right);
    }

    // 如果是运算符节点，且两个子节点都是常量，进行合并
    if (node->type == ExprNode::NodeType::OPERATOR &&
        node->left && node->right &&
        node->left->type == ExprNode::NodeType::CONSTANT &&
        node->right->type == ExprNode::NodeType::CONSTANT) {
        
        int result = 0;
        bool canMerge = true;

        switch (node->op) {
            case '+':
                result = node->left->val + node->right->val;
                break;
            case '-':
                result = node->left->val - node->right->val;
                break;
            case '*':
                result = node->left->val * node->right->val;
                break;
            case '/':
                if (node->right->val != 0) {
                    result = node->left->val / node->right->val;
                } else {
                    canMerge = false;
                }
                break;
            case '^':
                if (node->right->val >= 0) {
                    result = 1;
                    for (int i = 0; i < node->right->val; i++) {
                        result *= node->left->val;
                    }
                } else {
                    canMerge = false;
                }
                break;
            default:
                canMerge = false;
                break;
        }

        if (canMerge) {
            // 保存要删除的节点
            ExprNode* oldLeft = node->left;
            ExprNode* oldRight = node->right;

            // 修改当前节点为常量节点
            node->type = ExprNode::NodeType::CONSTANT;
            node->val = result;
            node->op = '\0';
            node->left = nullptr;
            node->right = nullptr;

            // 删除旧的子节点
            delete oldLeft;
            delete oldRight;
        }
    }

    return node;
}


void Expression::deleteTree(ExprNode* root){
    if (root) {
        deleteTree(root->left);   // 删除左子树
        deleteTree(root->right);  // 删除右子树
        delete root;              // 删除当前节点
    }
}
