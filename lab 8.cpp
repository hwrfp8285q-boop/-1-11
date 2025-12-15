#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template<typename T>
int compare(const T& a, const T& b) {
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

template<typename T>
T median(T arr[], int n) {
    vector<T> v(arr, arr + n);
    sort(v.begin(), v.end());
    return n % 2 ? v[n/2] : (v[n/2-1] + v[n/2]) / 2;
}

template<typename T>
void sortCount(T arr[], int n) {
    T mx = *max_element(arr, arr+n);
    T mn = *min_element(arr, arr+n);
    vector<int> cnt(mx - mn + 1, 0);
    for (int i = 0; i < n; i++) cnt[arr[i] - mn]++;
    int k = 0;
    for (int i = 0; i < cnt.size(); i++)
        while (cnt[i]--) arr[k++] = mn + i;
}

template<typename T>
void quickSort(T arr[], int l, int r) {
    if (l >= r) return;
    T piv = arr[(l+r)/2];
    int i = l, j = r;
    while (i <= j) {
        while (arr[i] < piv) i++;
        while (arr[j] > piv) j--;
        if (i <= j) swap(arr[i++], arr[j--]);
    }
    quickSort(arr, l, j);
    quickSort(arr, i, r);
}

template<typename T>
void sortQuick(T arr[], int n) {
    quickSort(arr, 0, n-1);
}

template<typename T>
void sortInsert(T arr[], int n) {
    for (int i = 1; i < n; i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
            arr[j+1] = arr[j--];
        arr[j+1] = key;
    }
}

template<typename T>
void revers(T arr[], int n) {
    for (int i = 0; i < n/2; i++)
        swap(arr[i], arr[n-1-i]);
}

int main() {
    int n;
    cout << "Сколько элементов в массиве? ";
    cin >> n;

    int* arr = new int[n];
    cout << "Введи " << n << " чисел:\n";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    cout << "\nТвой массив: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n\n";

    sortQuick(arr, n);
    cout << "После быстрой сортировки: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n";

    revers(arr, n);
    cout << "После реверса: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n";

    cout << "Медиана: " << median(arr, n) << endl;

    delete[] arr;
    return 0;
}

