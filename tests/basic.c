int main(void) {
    int b = 1, f = 2;
    //Type 1
    int* a = &b;
    //Type 2
    int c = b;
    //Type 3
    int* d = a;
    //Type 4
    *a = f;

    return 0;
}