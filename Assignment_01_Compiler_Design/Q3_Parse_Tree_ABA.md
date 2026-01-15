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

    
<img width="1408" height="768" alt="Gemini_Generated_Image_b7r1nfb7r1nfb7r1" src="https://github.com/user-attachments/assets/3579635f-4d95-421d-adae-8c4bdfc1cbdc" />



---

### 🍃 Leaf Nodes (Left to Right)
a b c b a

This corresponds to the string **`"abcba"`**, **not** `"aba"`.

---

### ✅ Conclusion
- The grammar generates **palindromes with center `c`**
- The string **`"aba"` is NOT generated** by this grammar
- Therefore, **no valid parse tree exists** for `"aba"`
