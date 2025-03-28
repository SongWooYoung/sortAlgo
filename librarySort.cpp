#include <iostream>
#include <vector>

using namespace std;


int main() {

    vector<int> array = {1, -1, 9, 6, 8, 7, -4, 50, 8, 10};
    vector<int> array1 = {1, 2, 3, 4, 5};
    vector<int> array2 = {7, 7, 7, 7, 7, 7};
    vector<int> array3 = {3, 2, 1, 0, -1, 99};
    vector<int> array4 = {4, -5, 0, 4, 4, -10, 20, 3};
    vector<int> array5 = {2, 1, 3};
    librarySort(array);
    librarySort(array1);
    librarySort(array2);
    librarySort(array3);
    librarySort(array4);
    librarySort(array5);

    cout << array << endl;
    cout << array1 << endl;
    cout << array2 << endl;
    cout << array3 << endl;
    cout << array4 << endl;
    cout << array5 << endl;


    return 0;
}