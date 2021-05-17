//
// Created by Neron on 24/4/2021.
//
#include <iostream>
#include "orderedArray.h"
#include <string>

using namespace std;

orderedArray::orderedArray() {      //Initializing the array with null pointers and a size of zero
    data = nullptr;
    num = nullptr;
    size = 0;
}

void orderedArray::swap(int &a, int &b) {
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void orderedArray::swap(string &a, string &b) {
    string temp;
    temp = a;
    a = b;
    b = temp;
}


void orderedArray::quicksort(long start, long end) {        //Standard recursive quicksort implementation
    long i, j, pivot;                                       //With the pivot on the 1st element
    string tempWord;

    if (start < end) {
        pivot = start;
        i = start;
        j = end;

        while (i < j) {
            for (; data[i] <= data[pivot] && i < end; ++i) {}
            for (; data[j] > data[pivot]; --j) {}

            if (i < j) {
                swap(data[i], data[j]);
                swap(num[i], num[j]);
            }
        }

        swap(data[pivot], data[j]);
        swap(num[pivot], num[j]);

        quicksort(start, j - 1);
        quicksort(j + 1, end);

    }
}

void orderedArray::copyFromUnordered(string *newData, int *newNum, long arraySize) {    //Implement quicksort on a string array
    this->size = arraySize;                                                             //and keep it in relation to an int array
    this->data = new string[size];
    this->num = new int[size];
    if (size == 1){
        this->data[0] = newData[0];
        this->num[0] = newNum[0];
        return;
    }
    copy(&newData[0], &newData[arraySize - 1], this->data);                     //Copy two arrays passed by reference locally
    copy(&newNum[0], &newNum[arraySize - 1], this->num);
    quicksort(0, size - 1);

}

bool orderedArray::binSearch(const string &word, long &pos) {       //Implementation of binary search
    if (size == 0) {                                                //If it's empty, it returns false (not found)
        pos = 0;
        return false;
    }
    if (data[0] == word){
        pos = 0;
        return true;
    }


    long begin = 0, end = size - 1;                         //Initializing the pointers to the front, middle and end.
    long mid = (begin + end) / 2;

    while (begin <= end){                                   //Main loop, checking where the sought-after word is in
        if (word > data[mid]) {                             //relation to the mid pointer.
            begin = mid + 1;                                //Depending on that, the array is divided.
        } else if (data[mid] == word) {
            pos = mid;
            return true;
        } else {
            end = mid - 1;
        }
        mid = (begin + end) / 2;
    }

    pos = mid;                                                      //Returning the position of the word (by reference).
    return data[mid] == word;                                       //Returning a bool value depending on if it's found.

}

void orderedArray::insert(const string &word) {                      //Insert single word into array/Increment if already in.

    if (size == 0) {                                                 //If the array is empty, initializing with one cell.
        size++;
        data = new string[size];
        num = new int[size];
        data[0] = word;
        num[0] = 1;
        return;
    }

    long pos;                                                 //Check if the word already exists in array.
    if (binSearch(word, pos)) {                            //If the search returns true, it's appearance num gets incremented.
        num[pos] += 1;
        return;
    }

    string *newData = new string[size + 1];                    //Initializing a temporary 2nd array with n+1 cells
    int *newNum = new int[size + 1];                           //Then all the cells up to where the new word should be placed
    copy(&data[0], &data[pos], newData);              //are copied over. After that, the word gets inserted
    copy(&num[0], &num[pos], newNum);                 //and the rest of the cells are copied over, 1 position after
    newData[pos + 1] = word;
    newNum[pos + 1] = 1;
    for (long i = pos + 1; i < size; ++i) {
        newData[i + 1] = data[i];
        newNum[i + 1] = num[i];
    }
    size++;
    delete[] data;
    data = newData;
    delete[] num;
    num = newNum;

}

void orderedArray::insertUnique(const string& word, const int occurrences) {    //Identical to insert, but takes a set
                                                                                //amount of occurrences, instead of
    if (size == 0) {                                                            //manually incrementing.
        size++;
        data = new string[size];
        num = new int[size];
        data[0] = word;
        num[0] = occurrences;
        return;
    }

    long pos;
    if (binSearch(word, pos)) {  //If the word already exists, discard the operation
        return;
    }

    string *newData = new string[size + 1];
    int *newNum = new int[size + 1];
    copy(&data[0], &data[pos], newData);
    copy(&num[0], &num[pos], newNum);
    newData[pos + 1] = word;
    newNum[pos + 1] = occurrences;
    for (long i = pos + 1; i < size; ++i) {
        newData[i + 1] = data[i];
        newNum[i + 1] = num[i];
    }
    size++;
    delete[] data;
    data = newData;
    delete[] num;
    num = newNum;
}

int orderedArray::search(const string& word) {       //Implementation of the binary search algo, but for public use.
    if (size == 0) {                                 //Returns the occurrences of a word (0 if none)
        return 0;
    }
    long pos;
    return binSearch(word, pos) ? num[pos] : 0;
}

void orderedArray::remove(const string &word) {      //The insert algorithm in reverse.
    //Check if the word exists, then reduce the array size by one
    //and slide the cells after the removed word one position down.
    long pos;
    if (!binSearch(word, pos)) {  //If the word doesn't exist, discard the operation.
        return;
    }

    string *newData = new string[size - 1];
    int *newNum = new int[size - 1];
    for (long i = 0; i < pos; ++i) {
        newData[i] = data[i];
        newNum[i] = num[i];
    }

    for (long i = pos; i < size - 1; ++i) {
        newData[i] = data[i + 1];
        newNum[i] = num[i + 1];
    }
    size--;

    delete[] num;
    delete[] data;
    data = newData;
    num = newNum;
}

long orderedArray::getSize() const {
    return size;
}

