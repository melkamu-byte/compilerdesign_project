#include <string>
#include <vector>
using namespace std;
/*
 Base AST Node
*/
class ASTNode {
public:
    virtual ~ASTNode() {}
};
/*
 Statement Node
*/
class Statement : public ASTNode {};
/*
 Variable Declaration Node
*/
class VarDecl : public Statement {
public:
    string name;
    string type;

    VarDecl(string n, string t) : name(n), type(t) {}
};

/*
 Try-Catch-Finally Node
*/
class TryCatchFinally : public Statement {
public:
    vector<Statement*> tryBlock;
    vector<Statement*> catchBlock;
    vector<Statement*> finallyBlock;
    string exceptionName;
    string exceptionType;
    TryCatchFinally(string exName, string exType)
        : exceptionName(exName), exceptionType(exType) {}
};

