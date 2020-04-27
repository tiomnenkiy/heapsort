#include <iostream>
#include <cstring>
using namespace std;

void SiftUp(int* arr, int* pos, int& size, int i) {
    if (i >= size || i < 0) {
        return;
    }
    while ( (pos[arr[i]] < pos[arr[(i - 1) / 2]]) && (i > 0)) {
        swap(arr[i], arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
};

void SiftDown(int* arr, int* pos, int& size, int i) {
    if (i >= size || i < 0) {
        return;
    }

    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int little_i = i;

    if (left < size && pos[arr[left]] < pos[arr[i]]) {
        little_i = left;
    }

    if (right < size && pos[arr[right]] < pos[arr[little_i]]) {
        little_i = right;
    }

    if (little_i != i) {
        swap(arr[i], arr[little_i]);
        SiftDown(arr, pos, size, little_i);
    }
};

void BuildHeap(int* arr, int* pos, int& size) {
    for (int i = size / 2 - 1; i >= 0; --i) {
        SiftDown(arr, pos, size, i);
    }
};

int insert (int* arr, int* pos, int elem, int& size, int& counter) {
    pos[counter] = elem;
    arr[size] = counter;
    ++counter;
    ++size;
    SiftUp(arr, pos, size, size - 1);
    return 1;
}

int get_min (int* arr, int* pos, int& size, int& counter) {
    if (size > 0) {
        return pos[arr[0]];
    } else {
        return 0;
    }
}

void extract_min (int* arr, int* pos, int& size, int& counter) {
    if (size > 0) {
        cout << pos[arr[0]];
        swap(arr[0], arr[size - 1]);
        --size;
        SiftDown(arr, pos, size, 0);
    } else {
        cout << "error" << endl;
    }
}

int findx (int* arr, int& size, int& x) {
    for (int i = 0; i < size; ++i) {
        if(arr[i] == x) {
            return i;
        }
    }
    return -1;
}

int del (int* arr, int* pos, int& size, int& x) {
    int num = findx(arr, size, x);
    //cout << num << endl;
    if (num == -1) {
        return 0;
    } else {
        bool ch;
        if (pos[num] >= pos[0]) {
            ch = 1;
        } else {
            ch = -1;
        }

        if (size > 0) {
            //cout << pos[arr[0]];
            swap(arr[num], arr[size - 1]);
            --size;
            SiftDown(arr, pos, size, num); // возможны ошибки
        } else {
            cout << "error" << endl;
        }
        /*if (ch == 1) {
            SiftDown(arr, pos, size, num);
        } else {
            SiftUp(arr, pos, size, num);
        }*/
    }
    return 1;
}

int change (int* arr, int* pos, int& size, int& x, int& n) {
    int num = findx(arr, size, x);
    //cout << num << endl;
    if (num == -1) {
        return 0;
    } else {
        bool ch;
        if (pos[num] >= n) {
            ch = 1;
        } else {
            ch = -1;
        }

        pos[arr[num]] = n;

        if (ch == 1) {
            SiftDown(arr, pos, size, num);
        } else {
            SiftUp(arr, pos, size, num);
        }
    }
    return 1;
}



int main() {
    int com_num;
    cin >> com_num;
    char str[100];
    int* arr = new int [com_num];
    int* pos = new int [com_num + 1];
    int size = 0;
    int counter = 1;
    int elem;
    int x;
    for(int i = 0; i < com_num; ++i) {
        cin >> str;
        if(!strcmp(str, "insert")) {
            cin >> elem;
            if (insert(arr, pos, elem, size, counter) == 1) {
                cout << "ok" << endl;
            }
            /*for (int i = 1; i < counter; ++i) {
                cout << pos[i] << " ";
            }*/
        }

        if(!strcmp(str, "extract_min")) {
            extract_min(arr, pos, size, counter);
        }

        if(!strcmp(str, "size")) {
            cout << size << endl;
        }

        if(!strcmp(str, "get_min")) {
            get_min(arr, pos, size, counter) != 0 ? cout << get_min(arr, pos, size, counter) << endl : cout << "error" << endl;
        }

        if(!strcmp(str, "clear")) {
            size = 0;
            cout << "ok" << endl;
        }

        if(!strcmp(str, "change")) {
            cin >> x;
            cin >> elem;
            if (change(arr, pos, size, x, elem) == 1) {
                cout << "ok" << endl;
            } else {
                cout << "error" << endl;
            }
            /*for (int i = 1; i < counter; ++i) {
                cout << pos[i] << " ";
            }*/
        }

        if(!strcmp(str, "delete")) {
            cin >> x;
            if (del(arr, pos, size, x) == 1) {
                cout << "ok" << endl;
            } else {
                cout << "error" << endl;
            }
            /*for (int i = 0; i < size; ++i) {
                cout << pos[arr[i]] << " ";
            }*/
        }
    }



    delete[] arr;
    delete[] pos;
    return 0;
}