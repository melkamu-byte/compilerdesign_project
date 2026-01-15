# Semantic Analysis — try / catch / finally

This note describes how to handle scopes and symbol-table actions for exception-handling constructs (try / catch / finally) during semantic analysis. It summarizes scope rules, resource-management considerations, common semantic errors, and an attribute-grammar perspective.

## Table of contents
- [Introduction](#introduction)
- [Scope rules for exception handling](#scope-rules-for-exception-handling)
  - [try block scope](#try-block-scope)
  - [catch block scope](#catch-block-scope)
  - [multiple catch blocks](#multiple-catch-blocks)
  - [finally block scope](#finally-block-scope)
- [Resource scope management](#resource-scope-management)
- [Symbol-table handling strategy](#symbol-table-handling-strategy)
- [Semantic errors detected](#semantic-errors-detected)
- [Attribute-grammar perspective](#attribute-grammar-perspective)
- [Conclusion](#conclusion)

---

## Introduction

Semantic analysis ensures identifiers are declared, correctly scoped, and type-correct. Exception-handling constructs (try, catch, finally) introduce nested and often temporary scopes that must be handled carefully to avoid illegal variable access and runtime failures.

## Scope rules for exception handling

### try block scope
- `try` introduces a new local scope.
- Variables declared inside a `try` are not visible outside that `try` block.

Example:
```java
try {
    int x = 10;
}
x++; // Error: 'x' is not visible here
```

### catch block scope
- Each `catch` block has its own scope.
- The exception variable declared in the `catch` (for example, `e` in `catch (IOException e)`) exists only inside that `catch` block and cannot be accessed outside.

Example:
```java
catch (IOException e) {
    int code = 1;
}
e = null; // Semantic error: 'e' is not visible here
```

### multiple catch blocks
- Each `catch` block uses a separate scope.
- The compiler must ensure the catch sequence respects the exception hierarchy and that no catch is unreachable.
  - For example, placing a broad `Exception` catch before a more specific `IOException` catch makes the latter unreachable.

Example (problematic ordering):
```java
catch (Exception e) { }
catch (IOException e) { } // Unreachable if Exception is placed first
```

### finally block scope
- `finally` is always executed after try/catch.
- It introduces its own independent scope; variables declared inside `finally` are local to that block.

Example:
```java
finally {
    int cleanup = 1;
}
cleanup++; // Error: 'cleanup' is not visible here
```

## Resource scope management

For languages with resource-management syntax (e.g., Java's try-with-resources):

```java
try (File f = open()) {
    use(f);
}
```

Semantic checks:
- The resource variable scope is limited to the `try` header/body.
- Resource type must implement the required interface/protocol (e.g., `AutoCloseable` in Java).
- Resources must be safely closed — static analysis can help verify no leaks in normal and exceptional paths.

## Symbol-table handling strategy

Use a scope-stack model. When entering or exiting blocks, push/pop appropriate scopes and update the symbol table.

Scope stack actions (summary):

| Construct / Event         | Semantic action                  |
|--------------------------|----------------------------------|
| Enter `try`              | Push new scope                   |
| Enter `catch`            | Push new scope                   |
| Declare exception var    | Insert exception variable in current scope |
| Enter `finally`          | Push new scope                   |
| Exit any block           | Pop scope                        |

Notes:
- Exception variables are inserted into the scope for the associated `catch` only.
- Resource variables declared in a `try` header are scoped to the `try` region.

## Semantic errors detected

Common errors the analyzer should detect:
- Undeclared exception variables (using `e` when none is declared)
- Redeclaration of an identifier in the same scope
- Accessing variables outside their valid scope
- Unreachable catch blocks (due to ordering or type hierarchy)
- Invalid exception types (non-exception types in catch)
- Improper resource usage (resource type not implementing required interface, failing to close where required)

## Attribute-grammar perspective

- Inherited attributes: current scope, enclosing type information
- Synthesized attributes: exception type, variable type, effect information (e.g., resource-closure intent)
- Attribute propagation ensures semantic information (types, symbol table entries) is available where needed and that checks such as reachability and redeclaration can be performed.

## Conclusion

Proper scope management for `try` / `catch` / `finally`:
- Prevents illegal variable access
- Ensures exception handling is correct and non-redundant
- Detects subtle runtime errors at compile-time
- Improves program reliability through early detection of resource and scope misuse

---


