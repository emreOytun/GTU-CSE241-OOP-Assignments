#include <iostream>
#include <algorithm>
#include "PFArray.cpp"
using namespace std;
using namespace GTU;

void incrementFun(int& x) {
	x += 1;
}

void decrementFun(int& x) {
	x -= 3;
}


void test1() {
	cout << "  ****************** PFArray No Args Constructor, Conversion Constructor, Capacity Function Testing : ****************** \n\n";
	
	cout << "Expecting Size: 0\n";
	cout << "Expecting Capacity: 50\n";
	PFArray<int> arr1;
	cout << "Size: " << arr1.size() << "\n";
	cout << "Capacity: " << arr1.capacity() << "\n\n";
	
	cout << "Expecting Size: 0\n";
	cout << "Expecting Capacity: 30\n";
	PFArray<int> arr2(30);
	cout << "Size: " << arr2.size() << "\n";
	cout << "Capacity: " << arr2.capacity() << "\n\n";
}

void test2() {
	cout << "  ****************** PFArray Add Function and For-Each Loop Testing : ****************** \n\n";
	
	PFArray<int> arr1;
	
	cout << "Expecting Elements: 2 3 1\n";
	arr1.add(2);
	arr1.add(3);
	arr1.add(1);
	cout << "Result: ";
	for (auto element : arr1) {
		cout << element << " ";
	}
	cout << "\n\n";
	
	cout << "Expecting Elements: 12.2 32.13 34.34\n";
	PFArray<double> arr3;
	arr3.add(12.2);
	arr3.add(32.13);
	arr3.add(34.34);
	cout << "Result: ";
	for (auto element : arr3) {
		cout << element << " ";
	}
	cout << "\n\n";
}


void test3() {
	cout << "  ****************** PFArray Copy Constructor and Move Constructor Testing : ****************** \n\n";
	
	PFArray<int> arr1;
	arr1.add(3);
	arr1.add(77);
	arr1.add(11);
	
	PFArray<int> copyArr1(arr1);
	cout << "Expecting Result: 3 77 11\n";
	cout << "Result: ";
	for (auto e : copyArr1) cout << e << " ";
	cout << "\n\n";
	
	PFArray<int> arr2 = std::move(arr1);
	cout << "Expecting Result: 3 77 11\n";
	cout << "Result: ";
	for (auto e : arr2) cout << e << " ";
	cout << "\n\n";
	
}

void test4() {
	cout << "  ****************** PFArray Copy Assignment and Move Assignment Testing : ****************** \n\n";
	
	PFArray<int> arr1;
	arr1.add(3);
	arr1.add(77);
	arr1.add(11);
	
	PFArray<int> copyArr1;
	copyArr1 = arr1;
	cout << "Expecting Result: 3 77 11\n";
	cout << "Result: ";
	for (auto e : copyArr1) cout << e << " ";
	cout << "\n\n";
	
	PFArray<int> arr2;
	arr2 = std::move(arr1);
	cout << "Expecting Result: 3 77 11\n";
	cout << "Result: ";
	for (auto e : arr2) cout << e << " ";
	cout << "\n\n";
}

void test5() {
	cout << "  ****************** PFArray Size Function Testing : ****************** \n\n";
	
	PFArray<int> arr4;
	arr4.add(8);
	arr4.add(23);
	arr4.add(-2);
		
	cout << "Array: ";
	for (auto e : arr4) {
		cout << e << " ";
	}
	cout << "\n";
	cout << "Expecting Size: 3\n";
	cout << "Result: " << arr4.size() << "\n\n";
	
	
	arr4.add(9);
	arr4.add(213);
	
	cout << "Array: ";
	for (auto e : arr4) {
		cout << e << " ";
	}
	cout << "\n";
	cout << "Expecting Size: 5\n";

	cout << "Result: " << arr4.size() << "\n\n";
}

void test6() {
	cout << "  ****************** PFArray Index Operator '[]' Testing : ****************** \n\n";
	
	PFArray<int> arr4;
	arr4.add(8);
	arr4.add(23);
	arr4.add(-2);
		
	cout << "Array: ";
	for (auto e : arr4) {
		cout << e << " ";
	}
	cout << "\n";
	cout << "arr[0]: " << arr4[0] << "\n";
	cout << "arr[1]: " << arr4[1] << "\n";
	cout << "arr[2]: " << arr4[2] << "\n";
	cout << "arr[3]: Exception expected. \n";
	try {
		cout << arr4[3] << "\n";
	} catch (const out_of_range& e) {
		cout << e.what();
	}
	cout << "\n";
}

void test7() {
	cout << "  ****************** PFArray Empty Function Testing : ****************** \n\n";
	 
	PFArray<int> arr5;
	cout << "Expecting Result: 1\n";
	cout << "Result: " << (int) arr5.empty() << "\n\n";
	
	arr5.add(3);
	cout << "Expecting Result: 0\n";
	cout << "Result: " << (int) arr5.empty() << "\n\n";
}

void test8() {
	cout << "  ****************** PFArray Clear Function Testing : ****************** \n\n";
	
	PFArray<int> arr5;
	arr5.add(21);
	arr5.add(231);
	
	cout << "Array before clearing: ";
	for (auto e : arr5) cout << e << " ";
	cout << "\n";
	cout << "Array size before clearing: " << arr5.size() << "\n";
	
	cout << "Array after clearing: ";
	arr5.clear();
	for (auto e : arr5) cout << e << " ";
	cout << "\n";
	cout << "Array size after clearing: " << arr5.size() << "\n\n";

	PFArray<double> arr6;
	arr6.add(23.23);
	arr6.add(2.0);
	arr6.add(10.34);

	cout << "Array before clearing: ";
	for (auto e : arr6) cout << e << " ";
	cout << "\n";
	cout << "Array size before clearing: " << arr6.size() << "\n";
	
	cout << "Array after clearing: ";
	arr6.clear();
	for (auto e : arr6) cout << e << " ";
	cout << "\n";
	cout << "Array size after clearing: " << arr6.size() << "\n";
}

void test9() {
	cout << "  ****************** PFArray Begin, End And Iterator Functions/Operators Testing : ****************** \n\n";

	PFArray<int> arr;
	arr.add(-2);
	arr.add(0);
	arr.add(2);	
	arr.add(4);
	arr.add(6);
	arr.add(8);
	arr.add(10);
	
	cout << "Expecting Result: -2 0 2 4 6 8 10 \n";
	cout << "Result: ";
	for (auto it = arr.begin(); it != arr.end(); ++it) {
		cout << *it << " ";
	}
	cout << "\n\n";
	
	arr.clear();
	arr.add(32);
	arr.add(-23);
	cout << "Expecting Result: 32 -23 \n";
	cout << "Result: ";
	for (auto it = arr.begin(); it != arr.end(); ++it) {
		cout << *it << " ";
	}
	cout << "\n\n";
	
	arr.add(99);
	arr.add(22);
	arr.add(32);
	
	cout << "Array: ";
	for (auto it = arr.begin(); it != arr.end(); ++it) {
		cout << *it << " ";
	}
	cout << "\n\n";
	
	auto it = arr.begin();
	cout << "The element iterator currently points: " << *it << "\n\n";
	
	++it;
	cout << "The element iterator points after increment: " << *it << "\n\n";
	
	it++;
	cout << "The element iterator points after increment: " << *it << "\n\n";
	
	--it;
	cout << "The element iterator points after decrement: " << *it << "\n\n";
	
	--it;
	cout << "The element iterator points after decrement: " << *it << "\n\n";
	
	*it = 10;
	cout << "The element iterator points after modifying it to 10: " << *it << "\n\n";
	
	auto it2 = arr.begin();
	cout << "Iterator '==' operator Testing : ";
	cout << "Expecting Result: 1 \n";
	cout << "Result: " << (int) (it == it2) << "\n\n";
	
}

void test10() {
	cout << "  ****************** PFArray Cbegin, Cend And ConstIterator Functions/Operators Testing : ****************** \n\n";

	PFArray<int> arr;
	arr.add(-2);
	arr.add(0);
	arr.add(2);	
	arr.add(4);
	arr.add(6);
	arr.add(8);
	arr.add(10);
	
	cout << "Expecting Result: -2 0 2 4 6 8 10 \n";
	cout << "Result: ";
	for (auto it = arr.cbegin(); it != arr.cend(); ++it) {
		cout << *it << " ";
	}
	cout << "\n\n";
	
	arr.clear();
	arr.add(32);
	arr.add(-23);
	cout << "Expecting Result: 32 -23 \n";
	cout << "Result: ";
	for (auto it = arr.cbegin(); it != arr.cend(); ++it) {
		cout << *it << " ";
	}
	cout << "\n\n";
	
	arr.add(99);
	arr.add(22);
	arr.add(32);
	
	cout << "Array: ";
	for (auto it = arr.cbegin(); it != arr.cend(); ++it) {
		cout << *it << " ";
	}
	cout << "\n\n";
	
	auto cit = arr.cbegin();
	cout << "The element iterator currently points: " << *cit << "\n\n";
	
	++cit;
	cout << "The element iterator points after increment: " << *cit << "\n\n";
	
	cit++;
	cout << "The element iterator points after increment: " << *cit << "\n\n";
	
	--cit;
	cout << "The element iterator points after decrement: " << *cit << "\n\n";
	
	--cit;
	cout << "The element iterator points after decrement: " << *cit << "\n\n";
	
	auto cit2 = arr.cbegin();
	cout << "Iterator '==' operator Testing : ";
	cout << "Expecting Result: 1 \n";
	cout << "Result: " << (int) (cit == cit2) << "\n\n";
	
}

void test11() {
	cout << "  ****************** PFArray Erase Function Testing : ****************** \n\n";

	PFArray<int> arr;
	arr.add(1);
	arr.add(2);
	arr.add(3);
	arr.add(4);
	arr.add(5);

	cout << "Array: ";
	for (auto e : arr) cout << e << " ";
	cout << "\n";

	auto it = arr.begin();
	cout << "The element iterator points: " << *it << "\n";
	
	arr.erase(it);
	cout << "Array after erasing the element iterator points: ";
	for (auto e : arr) cout << e << " ";
	cout << "\n\n";
	
	
	cout << "Array: ";
	for (auto e : arr) cout << e << " ";
	cout << "\n";

	auto it2 = arr.begin() + 1;
	cout << "The element iterator points: " << *it2 << "\n";
	
	arr.erase(it2);
	cout << "Array after erasing the element iterator points: ";
	for (auto e : arr) cout << e << " ";
	cout << "\n\n";
	

	cout << "Array: ";
	for (auto e : arr) cout << e << " ";
	cout << "\n";
	
	auto it3 = arr.end();
	arr.erase(it3);
	cout << "Array after trying to erase an element using invalid iterator: ";
	for (auto e : arr) cout << e << " ";
	cout << "\n\n";
}

void test12() {
	cout << "  ****************** PFArray with STL Algorithm Functions Testing : ****************** \n\n";
	
	PFArray<int> arr;
	arr.add(2);
	arr.add(7);
	arr.add(3);
	arr.add(-1);
	
	PFArray<int> arr2;
	arr2.add(2);
	arr2.add(7);
	arr2.add(3);
	arr2.add(-1);
	
	cout << "  *************** std::sort Testing : ************* \n\n";
	
	cout << "Array: ";
	for (auto e : arr) cout << e << " ";
	cout << "\n";
	
	std::sort(arr.begin(), arr.end());
	cout << "Array after sort ascending: ";
	for (auto e : arr) cout << e << " ";
	cout << "\n\n";
	
	
	cout << "Array: ";
	for (auto e : arr2) cout << e << " ";
	cout << "\n";
	
	std::sort(arr2.begin(), arr2.end(), std::greater<int>());
	cout << "Array after sort descending: ";
	for (auto e : arr2) cout << e << " ";
	cout << "\n\n";
	
	
	cout << "  *************** std::find Testing : ************* \n\n";
	
	cout << "Array: ";
	for (auto e : arr) cout << e << " ";
	cout << "\n";
	
	cout << "Find for 3 Result: ";
	auto res = std::find(arr.begin(), arr.end(), 3);
	if (res != arr.end()) {
		cout << "Found\n";
	}
	else {
		cout << "Not found\n";
	}
	
	
	cout << "Find for 99 Result: ";
	res = std::find(arr.begin(), arr.end(), 99);
	if (res != arr.end()) {
		cout << "Found\n\n";
	}
	else {
		cout << "Not found\n\n";
	}
	
	
	cout << "  *************** std::for_each Testing : ************* \n\n";
	
	cout << "Array: ";
	for (auto e : arr) cout << e << " ";
	cout << "\n";
	
	cout << "Array After Incrementing Each Element By 1: ";
	std::for_each(arr.begin(), arr.end(), incrementFun);
	for (auto e : arr) cout << e << " ";
	cout << "\n\n";
	
	
	cout << "Array: ";
	for (auto e : arr) cout << e << " ";
	cout << "\n";
	
	cout << "Array After Decrementing Each Element By 3: ";
	std::for_each(arr.begin(), arr.end(), decrementFun);
	for (auto e : arr) cout << e << " ";
	cout << "\n\n";
	
}


int main () {
	
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();
	test11();	
	test12();
	
	return 0;
}
