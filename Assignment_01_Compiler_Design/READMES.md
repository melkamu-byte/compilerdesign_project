## 3. Problem-Solving: Parse Tree for the String `"aba"`

### 📌 Given Grammar
S → aSa | bSb | c

---

### 🔍 Attempted Derivation of `"aba"`

1. Start with `S`
2. Apply production rule:  
S → aSa
3. Replace the inner `S` with:
S → bSb
4. Replace the innermost `S` with:
S → c

---

### 🌳 Parse Tree (Derived)

    S
  / | \
 a  S  a
     |
     S
   / | \
  b  S  b
     |
     c


---

### 🍃 Leaf Nodes (Left to Right)
a b c b a

This corresponds to the string **`"abcba"`**, **not** `"aba"`.

---

### ✅ Conclusion
- The grammar generates **palindromes with center `c`**
- The string **`"aba"` is NOT generated** by this grammar
- Therefore, **no valid parse tree exists** for `"aba"`
