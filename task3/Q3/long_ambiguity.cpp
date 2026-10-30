// A pitfall that remains: long converts to int AND to double equally well
long long charge(int grams)   { return grams; }
long long charge(double kg)   { return static_cast<long long>(kg); }
int main() { return static_cast<int>(charge(1500L)); }
