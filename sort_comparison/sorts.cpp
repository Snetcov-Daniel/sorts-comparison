#include "sorts.h"

void bubbleSort(std::vector<int> arr) {

	for (size_t i = 0; i < arr.size(); i++) {
		for (size_t j = i + 1; j < arr.size(); j++) {

			if (arr[j] < arr[i]) {
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

void hoareQS(std::vector<int> arr, int l, int r) {

	if (l >= r) { return; }

	int pivot = hoarePartition(arr, l, r);

	hoareQS(arr, l, pivot);
	hoareQS(arr, pivot + 1, r);
}

int hoarePartition(std::vector<int> arr, int l, int r) {

	int pivot = arr[l], i = l - 1, j = r;
	while (1) {
		do  j--; while (arr[j] > pivot);
		do  i++; while (arr[i] < pivot);

		if (i < j) {

			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
		else
			return j;
	}
}

void countSort(std::vector<int> arr, int n, int e) {

	int* output = new int[n];
	int i, count[10] = { 0 };

	for (i = 0; i < n; i++)
		count[(arr[i] / e) % 10]++;

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = n - 1; i >= 0; i--) {
		output[count[(arr[i] / e) % 10] - 1] = arr[i];
		count[(arr[i] / e) % 10]--;
	}

	for (i = 0; i < n; i++)
		arr[i] = output[i];

	delete[] output;
}

void radixSort(std::vector<int> arr) {

	int max = arr[0];
	for (size_t i = 1; i < arr.size(); i++)
		if (arr[i] > max) { max = arr[i]; }

	for (size_t e = 1; max / e > 0; e *= 10)
		countSort(arr, arr.size(), e);
}

void shellSort(std::vector<int> arr) {

	for (int gap = arr.size() / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < arr.size(); i += 1) {
			int temp = arr[i];
			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
				arr[j] = arr[j - gap];

			arr[j] = temp;
		}
	}
}