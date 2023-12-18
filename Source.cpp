#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

struct Stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

Stats insertionSort(vector<int>& arr) {
    Stats stats;
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            stats.copy_count++;
            stats.comparison_count++;
            j--;
        }
        arr[j + 1] = key;
        stats.copy_count++;
    }
    return stats;
}

Stats cocktailSort(vector<int>& arr) {
    Stats stats;
    int n = arr.size();
    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = false;

        for (int i = start; i < end; i++) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                stats.copy_count += 3;
                stats.comparison_count++;
                swapped = true;
            }
            stats.comparison_count++;
        }

        if (!swapped)
            break;

        swapped = false;

        end--;

        for (int i = end - 1; i >= start; i--) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                stats.copy_count += 3;
                stats.comparison_count++;
                swapped = true;
            }
            stats.comparison_count++;
        }

        start++;
    }

    return stats;
}

Stats combSort(vector<int>& arr) {
    Stats stats;
    int n = arr.size();
    int gap = n;
    bool swapped = true;

    while (gap > 1 || swapped) {
        gap = max(1, (gap * 10) / 13);
        swapped = false;

        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                swap(arr[i], arr[i + gap]);
                stats.copy_count += 3;
                stats.comparison_count++;
                swapped = true;
            }
            stats.comparison_count++;
        }
    }

    return stats;
}

int main() {
    vector<int> arr_sizes = { 1000, 2000, 3000 };
    vector<int> arr;
    random_device rd;
    mt19937 gen(rd());

    for (int size : arr_sizes) {
        cout << "Array size: " << size << endl;

        Stats insertion_stats, cocktail_stats, comb_stats;
        for (int i = 0; i < 100; i++) {
            arr.clear();
            arr.resize(size);
            uniform_int_distribution<int> distrib(0, size);
            for (int& num : arr) {
                num = distrib(gen);
            }

            vector<int> insertion_arr = arr;
            vector<int> cocktail_arr = arr;
            vector<int> comb_arr = arr;

            insertion_stats.comparison_count += insertionSort(insertion_arr).comparison_count;
            insertion_stats.copy_count += insertionSort(insertion_arr).copy_count;

            cocktail_stats.comparison_count += cocktailSort(cocktail_arr).comparison_count;
            cocktail_stats.copy_count += cocktailSort(cocktail_arr).copy_count;

            comb_stats.comparison_count += combSort(comb_arr).comparison_count;
            comb_stats.copy_count += combSort(comb_arr).copy_count;
        }

        insertion_stats.comparison_count /= 100;
        insertion_stats.copy_count /= 100;

        cocktail_stats.comparison_count /= 100;
        cocktail_stats.copy_count /= 100;

        comb_stats.comparison_count /= 100;
        comb_stats.copy_count /= 100;

        cout << "Insertion Sort:" << endl;
        cout << "Comparison count: " << insertion_stats.comparison_count << endl;
        cout << "Copy count: " << insertion_stats.copy_count << endl;

        cout << "Cocktail Sort:" << endl;
        cout << "Comparison count: " << cocktail_stats.comparison_count << endl;
        cout << "Copy count: " << cocktail_stats.copy_count << endl;

        cout << "Comb Sort:" << endl;
        cout << "Comparison count: " << comb_stats.comparison_count << endl;
        cout << "Copy count: " << comb_stats.copy_count << endl;

        cout << endl;

        for (int i = 0; i < 100; i++) {
            arr.clear();
            arr.resize(size);
            uniform_int_distribution<int> distrib(0, size);

            // —генерируем полностью отсортированный массив
            for (int j = 0; j < size; j++) {
                arr[j] = j;
            }

            vector<int> insertion_arr = arr;
            vector<int> cocktail_arr = arr;
            vector<int> comb_arr = arr;

            insertion_stats.comparison_count += insertionSort(insertion_arr).comparison_count;
            insertion_stats.copy_count += insertionSort(insertion_arr).copy_count;

            cocktail_stats.comparison_count += cocktailSort(cocktail_arr).comparison_count;
            cocktail_stats.copy_count += cocktailSort(cocktail_arr).copy_count;

            comb_stats.comparison_count += combSort(comb_arr).comparison_count;
            comb_stats.copy_count += combSort(comb_arr).copy_count;
        }

        insertion_stats.comparison_count /= 100;
        insertion_stats.copy_count /= 100;

        cocktail_stats.comparison_count /= 100;
        cocktail_stats.copy_count /= 100;

        comb_stats.comparison_count /= 100;
        comb_stats.copy_count /= 100;

        cout << "Insertion Sort(Sorted):" << endl;
        cout << "Comparison count(Sorted): " << insertion_stats.comparison_count << endl;
        cout << "Copy count(Sorted): " << insertion_stats.copy_count << endl;

        cout << "Cocktail Sort(Sorted):" << endl;
        cout << "Comparison count(Sorted): " << cocktail_stats.comparison_count << endl;
        cout << "Copy count(Sorted): " << cocktail_stats.copy_count << endl;

        cout << "Comb Sort(Sorted):" << endl;
        cout << "Comparison count(Sorted): " << comb_stats.comparison_count << endl;
        cout << "Copy count(Sorted): " << comb_stats.copy_count << endl;

        cout << endl;

        for (int i = 0; i < 100; i++) {
            arr.clear();
            arr.resize(size);
            uniform_int_distribution<int> distrib(0, size);

            // —генерируем обратно отсортированный массив
            for (int j = 0; j < size; j++) {
                arr[j] = size - 1 - j;
            }

            vector<int> insertion_arr = arr;
            vector<int> cocktail_arr = arr;
            vector<int> comb_arr = arr;

            insertion_stats.comparison_count += insertionSort(insertion_arr).comparison_count;
            insertion_stats.copy_count += insertionSort(insertion_arr).copy_count;

            cocktail_stats.comparison_count += cocktailSort(cocktail_arr).comparison_count;
            cocktail_stats.copy_count += cocktailSort(cocktail_arr).copy_count;

            comb_stats.comparison_count += combSort(comb_arr).comparison_count;
            comb_stats.copy_count += combSort(comb_arr).copy_count;
        }

        insertion_stats.comparison_count /= 100;
        insertion_stats.copy_count /= 100;

        cocktail_stats.comparison_count /= 100;
        cocktail_stats.copy_count /= 100;

        comb_stats.comparison_count /= 100;
        comb_stats.copy_count /= 100;

        cout << "Insertion Sort:(Unsorted)" << endl;
        cout << "Comparison count(Unsorted): " << insertion_stats.comparison_count << endl;
        cout << "Copy count(Unsorted): " << insertion_stats.copy_count << endl;

        cout << "Cocktail Sort(Unsorted):" << endl;
        cout << "Comparison count(Unsorted): " << cocktail_stats.comparison_count << endl;
        cout << "Copy count(Unsorted): " << cocktail_stats.copy_count << endl;

        cout << "Comb Sort(Unsorted):" << endl;
        cout << "Comparison count(Unsorted): " << comb_stats.comparison_count << endl;
        cout << "Copy count(Unsorted): " << comb_stats.copy_count << endl;

        cout << endl;

    }

    return 0;
}
