class SymbolTable {
    stack<unordered_map<string, string>> scopes;
public:
    void enterScope() {
        scopes.push({});
    }
    void exitScope() {
        scopes.pop();
    }
    void declare(string name, string type) {
        scopes.top()[name] = type;
    }
    bool lookup(string name) {
        for (auto s = scopes; !s.empty(); s.pop())
            if (s.top().count(name)) return true;
        return false;
    }
};
