#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <random>
#include <math.h>
#include <thread>
#include "matplot\matplot.h"
#include "sorts.h"

std::vector<double> bubbleTime, hoareTime, radixTime, shellTime, nlogn;

class Timer {
public:
	Timer() { start = std::chrono::high_resolution_clock::now(); }
	double getDuration() {

		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		return duration.count();
	}
	~Timer() {

	}
private:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;
};

void generateNumbers(std::vector<int> &arr, const int& amount) {
	srand(time(NULL));
	for (size_t i = 0; i < amount; i++)
		arr.push_back(rand());
}

float functionTime(void(*func)(std::vector<int>), std::vector<int> arr) {
	Timer t;

	func(arr);

	return t.getDuration();
}

float functionTime(void(*func)(std::vector<int>, int, int), std::vector<int> arr) {
	Timer t;

	func(arr, 0, arr.size());

	return t.getDuration();
}

void getData(const int& num) {
	std::vector<int> arr;
	generateNumbers(arr, num);

	double bubble, hoare, radix, shell;
	std::thread t1([&bubble, &arr]() { bubble = functionTime(&bubbleSort, arr); });
	std::thread t2([&hoare, &arr]() { hoare = functionTime(&hoareQS, arr); });
	std::thread t3([&radix, &arr]() { radix = functionTime(&radixSort, arr); });
	std::thread t4([&shell, &arr]() { shell = functionTime(&shellSort, arr); });

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	bubbleTime.push_back(bubble);
	hoareTime.push_back(hoare);
	radixTime.push_back(radix);
	shellTime.push_back(shell);
}

int main() {
	using namespace matplot;

	int start, end, step;
	start = 1000;
	end = 5000;
	step = 1000;

	for (size_t i = start; i <= end; i += step) {
		getData(i);
		nlogn.push_back((i * log10(i)) / 1000000);
	}

	vector_1d x = iota(start, step, end);
	vector_2d bubble = { bubbleTime, nlogn };
	vector_2d hoare = { hoareTime , nlogn };
	vector_2d radixShell = { radixTime, shellTime, nlogn };

	tiledlayout(3, 1);

	auto ax1 = nexttile();
	ax1->font("Roboto");
	ax1->font_size(6);
	plot(x, bubble);

	auto ax2 = nexttile();
	ax2->font("Roboto");
	ax2->font_size(6);
	plot(x, hoare);

	auto ax3 = nexttile();
	ax3->font("Roboto");
	ax3->font_size(6);
	xlabel("Amount of integers");
	ylabel("Time(s)");	
	plot(x, radixShell);

	auto l1 = legend(ax1, "Bubble","O(Nlog(N))");
	l1->location(legend::general_alignment::topleft);

	auto l2 = legend(ax2, "Hoare","O(Nlog(N))");
	l2->location(legend::general_alignment::topleft);

	auto l3 = legend(ax3, "Radix", "Shell", "O(Nlog(N))");
	l3->location(legend::general_alignment::topleft);

	show();
	return 0;
}