A. Semantic Analysis
 Manage Scopes Involving try / catch / finally
1. Introduction
Semantic analysis ensures that identifiers are declared, correctly scoped, and semantically valid.
Exception-handling constructs (try, catch, finally) introduce special nested scopes that must be handled carefully to prevent illegal variable access and runtime failures.
2. Scope Rules for Exception Handling
2.1 try Block Scope
Introduces a new local scope
Variables declared inside are not visible outside
try {
    int x = 10;
}
x++; 
2.2 catch Block Scope
Each catch block has:
oIts own scope
oAn exception variable
Exception variables:
oExist only inside the catch
oCannot be accessed outside
catch (IOException e) {
    int code = 1;
}
e = null;   // Semantic Error
2.3 Multiple catch Blocks
Each catch block has a separate scope
Compiler must ensure:
oCorrect exception hierarchy
oNo unreachable catch blocks
catch (Exception e) { }
catch (IOException e) { }  
2.4 finally Block Scope
Always executed
Introduces its own independent scope
Variables declared here are local to finally only
finally {
    int cleanup = 1;
}
cleanup++;  

3. Resource Scope Management
For languages supporting resource management:
try (File f = open()) {
    use(f);
}
Semantic checks:
Resource variable scope limited to try
Resource type must implement required interface
Resource must be closed safely

4. Symbol Table Handling Strategy
Scope Stack Model
Construct	Semantic Action
Enter try	Push new scope
Enter catch	Push new scope
Declare exception variable	Insert into symbol table
Enter finally	Push new scope
Exit block	Pop scope

5. Semantic Errors Detected
Undeclared exception variables
Redeclaration in same scope
Access outside valid scope
Unreachable catch blocks
Invalid exception types
Improper resource usage

6. Attribute Grammar Perspective
Inherited attributes: current scope
Synthesized attributes: exception type, variable type
Ensures correct propagation of semantic information
7. Conclusion
Managing scopes in try/catch/finally:
Prevents illegal variable access
Ensures exception correctness
Improves program reliability
Detects subtle runtime errors at compile time

