try {
    int x = 10;
}
catch (Exception e) {
    int y = 5;
}
finally {
    int z = 0;
}
x++; // error
e++; // error
z++; // error
