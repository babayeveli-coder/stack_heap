#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std; // std ad məkanını istifadə edirik

// 1. Dinamik yaddaş ayıran funksiya
int* createArray(int size) {
    if (size <= 0) {
        cerr << "Massivin ölçüsü mənfi və ya 0 ola bilməz!" << endl;
        return nullptr;
    }
    return new int[size];
}

// 2. Dinamik massivi random ədədlərlə dolduran funksiya
void fillArrayWithRandom(int* array, int size) {
    if (!array || size <= 0) return;

    srand(time(0)); // static_cast istifadə etmirik
    for (int i = 0; i < size; ++i) {
        array[i] = rand() % 100; // 0-99 arasında təsadüfi ədəd
    }
}

// 4. Dinamik massivi silən funksiya
void deleteArray(int* array) {
    delete[] array;
}

// 5. Dinamik massivin sonuna element əlavə edən funksiya
int* addElementToEnd(int* array, int& size, int element) {
    int* newArray = createArray(size + 1);
    if (!newArray) return nullptr;

    for (int i = 0; i < size; ++i) {
        newArray[i] = array[i];
    }
    newArray[size] = element;

    deleteArray(array);
    size++;
    return newArray;
}

// 6. Dinamik massivin göstərilən indexinə element əlavə edən funksiya
int* addElementAtIndex(int* array, int& size, int index, int element) {
    if (index < 0 || index > size) return nullptr;

    int* newArray = createArray(size + 1);
    if (!newArray) return nullptr;

    for (int i = 0; i < index; ++i) {
        newArray[i] = array[i];
    }
    newArray[index] = element;

    for (int i = index; i < size; ++i) {
        newArray[i + 1] = array[i];
    }

    deleteArray(array);
    size++;
    return newArray;
}

// 7. Dinamik massivdən göstərilən indexdəki elementin silinməsi
int* removeElementAtIndex(int* array, int& size, int index) {
    if (index < 0 || index >= size) return nullptr;

    int* newArray = createArray(size - 1);
    if (!newArray) return nullptr;

    for (int i = 0; i < index; ++i) {
        newArray[i] = array[i];
    }
    for (int i = index + 1; i < size; ++i) {
        newArray[i - 1] = array[i];
    }

    deleteArray(array);
    size--;
    return newArray;
}

// 8. Dinamik massivin sonuna bir blok element əlavə edən funksiya
int* addBlockToEnd(int* array, int& size, int* block, int blockSize) {
    if (!block || blockSize <= 0) return array;

    int* newArray = createArray(size + blockSize);
    if (!newArray) return nullptr;

    for (int i = 0; i < size; ++i) {
        newArray[i] = array[i];
    }
    for (int i = 0; i < blockSize; ++i) {
        newArray[size + i] = block[i];
    }

    deleteArray(array);
    size += blockSize;
    return newArray;
}

// 9. Dinamik massivin göstərilən indexindən sonra bir blok element əlavə edən funksiya
int* addBlockAtIndex(int* array, int& size, int index, int* block, int blockSize) {
    if (index < 0 || index > size || !block || blockSize <= 0) return nullptr;

    int* newArray = createArray(size + blockSize);
    if (!newArray) return nullptr;

    for (int i = 0; i < index; ++i) {
        newArray[i] = array[i];
    }
    for (int i = 0; i < blockSize; ++i) {
        newArray[index + i] = block[i];
    }
    for (int i = index; i < size; ++i) {
        newArray[i + blockSize] = array[i];
    }

    deleteArray(array);
    size += blockSize;
    return newArray;
}

// 10. Dinamik massivdən bir blok elementi silən funksiya
int* removeBlock(int* array, int& size, int index, int blockSize) {
    if (index < 0 || index >= size || blockSize <= 0 || index + blockSize > size) return nullptr;

    int* newArray = createArray(size - blockSize);
    if (!newArray) return nullptr;

    for (int i = 0; i < index; ++i) {
        newArray[i] = array[i];
    }
    for (int i = index + blockSize; i < size; ++i) {
        newArray[i - blockSize] = array[i];
    }

    deleteArray(array);
    size -= blockSize;
    return newArray;
}

// Main funksiyası
int main() {
    int size = 5;
    int* myArray = createArray(size);
    fillArrayWithRandom(myArray, size);

    // Massivi birbaşa ekrana çıxarırıq
    cout << "Başlanğıc massiv: ";
    for (int i = 0; i < size; ++i) {
        cout << myArray[i] << " ";
    }
    cout << endl;

    myArray = addElementToEnd(myArray, size, 42);
    cout << "Sonuna 42 əlavə edildikdən sonra: ";
    for (int i = 0; i < size; ++i) {
        cout << myArray[i] << " ";
    }
    cout << endl;

    myArray = addElementAtIndex(myArray, size, 2, 99);
    cout << "2-ci indexə 99 əlavə edildikdən sonra: ";
    for (int i = 0; i < size; ++i) {
        cout << myArray[i] << " ";
    }
    cout << endl;

    myArray = removeElementAtIndex(myArray, size, 1);
    cout << "1-ci indexdəki element silindikdən sonra: ";
    for (int i = 0; i < size; ++i) {
        cout << myArray[i] << " ";
    }
    cout << endl;

    int block[] = { 100, 101, 102 };
    myArray = addBlockToEnd(myArray, size, block, 3);
    cout << "Sonuna bir blok əlavə edildikdən sonra: ";
    for (int i = 0; i < size; ++i) {
        cout << myArray[i] << " ";
    }
    cout << endl;

    myArray = removeBlock(myArray, size, 2, 2);
    cout << "2-ci indexdən 2 element silindikdən sonra: ";
    for (int i = 0; i < size; ++i) {
        cout << myArray[i] << " ";
    }
    cout << endl;

    deleteArray(myArray);
    return 0;
}
