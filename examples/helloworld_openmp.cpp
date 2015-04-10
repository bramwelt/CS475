#include <iostream>
 
using std::cout;

int main(void)
{
    #pragma omp parallel
    cout << "Hello, World!" << "\n";
    return 0;
}
