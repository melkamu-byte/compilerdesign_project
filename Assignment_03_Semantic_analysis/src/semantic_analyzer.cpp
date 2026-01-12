#include <iostream>
#include <unordered_map>
#include <stack>
#include "ast_nodes.cpp"
using namespace std;
/*
 Symbol Table with Scope Stack
*/
class SymbolTable {
    stack<unordered_map<string, string>> scopes
public:
    void enterScope() {
        scopes.push({});
    }
    void exitScope() {
        scopes.pop();
    }
  bool declare(string name, string type) {
        if (scopes.top().count(name)) {
            return false; // redeclaration error
        }
        scopes.top()[name] = type;
        return true;
    }
 bool lookup(string name) {
        stack<unordered_map<string, string>> temp = scopes;     while (!temp.empty()) {
   if (temp.top().count(name)) return true;
            temp.pop();
        }
        return false;
    }
};
/*
 Semantic Analyzer
*/
class SemanticAnalyzer {
    SymbolTable table;
public:
    void analyzeTryCatch(TryCatchFinally* node) {
        // TRY BLOCK
        table.enterScope();
        for (auto stmt : node->tryBlock) {
            analyzeStatement(stmt);
        }
        table.exitScope();
        // CATCH BLOCK
        table.enterScope();
        if (!table.declare(node->exceptionName, node->exceptionType)) {
            cout << "Semantic Error: Exception variable redeclared\n";
        }
        for (auto stmt : node->catchBlock) {
            analyzeStatement(stmt);  }
   table.exitScope();

        // FINALLY BLOCK
        table.enterScope();
        for (auto stmt : node->finallyBlock) {
            analyzeStatement(stmt);
        }
        table.exitScope();
    }

    void analyzeStatement(Statement* stmt) {
        if (auto var = dynamic_cast<VarDecl*>(stmt)) {
            if (!table.declare(var->name, var->type)) {
                cout << "Semantic Error: Variable redeclared -> "
                     << var->name << endl;
            }
        }
    }
};

/*
 Example Driver
*/
int main() {
    SemanticAnalyzer analyzer;

    TryCatchFinally* tcf = new TryCatchFinally("e", "Exception");

    tcf->tryBlock.push_back(new VarDecl("x", "int"));
    tcf->catchBlock.push_back(new VarDecl("y", "int"));
    tcf->finallyBlock.push_back(new VarDecl("z", "int"));

    analyzer.analyzeTryCatch(tcf);

    cout << "Semantic analysis completed.\n";
    return 0;
}

