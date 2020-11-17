#include <iostream>
#include <stdio.h>
#include <ctime>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace chrono;

int main() {
	setlocale(LC_ALL, "RU");
	srand(time(NULL));

	long long int size;
	cout << "Write size of vectors: ";
	cin >> size;
	int* arr1 = new int[size];
	int* arr2 = new int[size];
	int result=0;
	for (long long int i = 0; i < size; ++i) {
		arr1[i] = rand() % 10;
		arr2[i] = rand() % 10;
	}
	int i;
	auto start = chrono::steady_clock::now();
#pragma omp parallel for private(i) reduction(+:result) shared(arr1,arr2)
	for (int i = 0; i < size; ++i) {
		result += arr1[i] * arr2[i];
	}
	auto end = chrono::steady_clock::now();
	auto duration = end - start;
	cout << "Результат при помощи OpenMP: " << result << endl;
	cout << "Время: " << (double)(duration.count() / pow(10, 9)) <<endl;
	result = 0;

	start = chrono::steady_clock::now();
	for (long long int i = 0; i < size; ++i) {
		result += arr1[i] * arr2[i];
	}
	end = chrono::steady_clock::now();
	duration = end - start;
	cout << "Правильный ответ: " << result << endl;
	cout << "Время: " << (double)(duration.count() / pow(10, 9)) << endl;
	return 0;
}