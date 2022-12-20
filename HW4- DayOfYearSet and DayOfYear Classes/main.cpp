#include <iostream> 
#include <fstream>
#include <stdexcept>
#include "DayOfYearSet.h"
using namespace GTUDate;
using std::cout;
using std::ofstream;
using std::invalid_argument;
using std::runtime_error;
using std::out_of_range;

void dayOfYear_callByValue(DayOfYearSet::DayOfYear date) {
	cout << "CallByValue Date: \n";
	cout << date << "\n";
}

void dayOfYear_callByReference(DayOfYearSet::DayOfYear& date) {
	cout << "CallByReference Date: \n";
	cout << date << "\n";
	
	date.setDate(2, 2);
	cout << "Date is changed to (2/2) inside the function \n";
}

void dayOfYearSet_callByValue(DayOfYearSet set) {
	cout << "CallByValue Set: \n";
	cout << set << "\n";
}

void dayOfYearSet_callByReference(DayOfYearSet& set) {
	cout << "CallByReference Set: \n";
	cout << set; 
	
	DayOfYearSet::DayOfYear day(7, 8);
	set.add(day);
	cout << "Added a day(7/8) to the set inside the function \n\n";
}


int main () {
	
	cout <<  "  ************************************************* DayOfYear Class Tests : **************************************************** \n\n";
	
	
	cout << "  ****************** DayOfYear Constructor Testing : ****************** \n\n";
	
	DayOfYearSet::DayOfYear day1(1, 1);
	cout << "Expected Day/Month: 1/1 \n";
	cout << "Result: " << day1.getDay() << "/" << day1.getMonth() << "\n\n";
	
	cout << "Expected an exception to be thrown below: \n";
	try {
		DayOfYearSet::DayOfYear badDay(-2, 6);
	} catch (const invalid_argument& e) {
		cout << "Exception : " << e.what();
	}
	cout << "\n\n";
	
	
	cout << "  ****************** DayOfYear Getters Testing : ****************** \n\n";
	
	DayOfYearSet::DayOfYear day2(16, 2);
	cout << "Expected Day/Month: 16/2 \n";
	cout << "Result: " << day2.getDay() << "/" << day2.getMonth() << "\n\n";
	
	
	cout << "  ****************** DayOfYear Setters Testing : ****************** \n\n";
	
	DayOfYearSet::DayOfYear day3(12, 8);
	day3.setDate(11, 12);
	cout << "Expected Day/Month: 11/12 \n";
	cout << "Result: " << day3.getDay() << "/" << day3.getMonth() << "\n\n";
	
	day3.setMonth(7);
	cout << "Expected Month: 7 \n";
	cout << "Result: " << day3.getMonth() << "\n\n";
	
	day3.setDay(11);
	cout << "Expected Day: 7 \n";
	cout << "Result: " << day3.getDay() << "\n\n";
	
	cout << "Expected an exception to be thrown below: \n";
	try {
		day3.setDate(33, 1);
	} catch (const invalid_argument& e) {
		cout << "Exception : " << e.what();
	}
	cout << "\n\n";
	
	
	cout << "  ****************** DayOfYear '==' and '!=' Operator Testing : ****************** \n\n";
	
	DayOfYearSet::DayOfYear day4(17, 9);
	DayOfYearSet::DayOfYear day5(10, 4);
	
	cout << "Expected Result: 0 \n";
	cout << "Result: " << (int) (day4 == day5) << "\n\n";
	
	cout << "Expected Result: 1 \n";
	cout << "Result: " << (int) (day4 != day5) << "\n\n";
	
	DayOfYearSet::DayOfYear day4Equal(17, 9);
	
	cout << "Expected Result: 1 \n";
	cout << "Result: " << (int) (day4 == day4Equal) << "\n\n";
	
	cout << "Expected Result: 0 \n";
	cout << "Result: " << (int) (day4 != day4Equal) << "\n\n";
	
	
	cout << "  ****************** DayOfYear '<<' Operator Testing : ****************** \n\n";
	
	DayOfYearSet::DayOfYear day6(24, 1);
	cout << "Expected Result: DD/MM: 24/1 \n";
	cout << day6 << "\n\n";
	
	DayOfYearSet::DayOfYear day7(9, 11);
	cout << "Expected Result: DD/MM: 9/11 \n";
	cout << day7 << "\n\n";
	
	
	cout << "  ****************** DayOfYear '++' Operator Testing : ****************** \n\n";
	
	cout << "Expected Result: DD/MM: 25/1 \n";
	cout << ++day6 << "\n\n";
	
	cout << "Expected Result: DD/MM: 26/1 \n";
	cout << ++day6 << "\n\n";
	
	
	cout << "  ****************** DayOfYear '--' Operator Testing : ****************** \n\n";
	
	cout << "Expected Result: DD/MM: 25/1 \n";
	cout << --day6 << "\n\n";
	
	cout << "Expected Result: DD/MM: 24/1 \n";
	cout << --day6 << "\n\n";
	
	
	cout << "  ****************** DayOfYear CallByValue and Reference Testing : ****************** \n\n";
	
	DayOfYearSet::DayOfYear day8(24, 1);
	cout << "Day to send as paramater : \n";
	cout << day8 << "\n\n";
	
	dayOfYear_callByValue(day8);
	cout << "\n";
	
	dayOfYear_callByReference(day8);
	cout << "\n";
		
	cout << "Day after sending as paramater: \n";
	cout << day8 << "\n\n";
	
		
	cout <<  "  ************************************************* DayOfYearSet Class Tests : **************************************************** \n\n";
	
	
	cout << "  ****************** DayOfYearSet Constructor Testing : ****************** \n\n";
	
	DayOfYearSet emptySet;
	cout << "EmptySet Expecting No Elements: \n";
	cout << "EmptySet: \n";
	cout << emptySet << "\n";
	
	DayOfYearSet::DayOfYear day9(1, 1);
	DayOfYearSet::DayOfYear day10(10, 7);
	DayOfYearSet::DayOfYear day11(26, 9);
	DayOfYearSet dateSet1 = {day9, day10, day11};
	
	cout << "Set1 Expected: \n";
	cout << day9 << "\n";
	cout << day10 << "\n";
	cout << day11 << "\n\n";
	
	cout << "Set1 Result: \n";
	cout << dateSet1 << "\n";
	
	DayOfYearSet::DayOfYear day12(20, 5);
	DayOfYearSet dateSet2 = {day9, day10, day12};
	
	cout << "Set2 Expected: \n";
	cout << day9 << "\n";
	cout << day10 << "\n";
	cout << day12 << "\n\n";
	
	cout << "Set2 Result: \n";
	cout << dateSet2 << "\n";
	
	
	cout << "  ****************** DayOfYearSet Add Function Testing : ****************** \n\n";
	
	DayOfYearSet::DayOfYear day13(3, 5);

	cout << "Set1 before adding a date (DD/MM: 3/5): \n";
	cout << dateSet1 << "\n"; 
	
	dateSet1.add(day13);
	cout << "Set1 after adding a date (DD/MM: 3/5): \n";
	cout << dateSet1 << "\n\n";
	
	DayOfYearSet::DayOfYear day14(2, 2);
	
	cout << "Set1 before adding a date (DD/MM: 2/2): \n";
	cout << dateSet1 << "\n"; 
	
	dateSet1.add(day14);
	cout << "Set1 after adding a date (DD/MM: 2/2): \n";
	cout << dateSet1 << "\n";
	
	cout << "Set1 after adding the date added before (DD/MM: 2/2): \n";
	dateSet1.add(day14);
	cout << dateSet1 << "\n\n";
	
	
	cout << "  ****************** DayOfYearSet Remove Function Testing : ****************** \n\n";
	
	cout << "Set1 before removing a date (DD/MM: 3/5): \n";
	cout << dateSet1 << "\n"; 
	
	dateSet1.remove(day13);
	cout << "Set1 after removing a date (DD/MM : 3/5): \n";
	cout << dateSet1 << "\n\n";
	
	
	cout << "Set1 before removing a date (DD/MM: 2/2): \n";
	cout << dateSet1 << "\n"; 
	
	dateSet1.remove(day14);
	cout << "Set1 after removing a date (DD/MM : 2/2): \n";
	cout << dateSet1 << "\n";
	
	cout << "Set1 after removing the date removed before (DD/MM: 2/2): \n";
	dateSet1.remove(day14);
	cout << dateSet1 << "\n\n";
	
	
	cout << "  ****************** DayOfYearSet Size Function Testing : ****************** \n\n";
	
	cout << "Set1: \n";
	cout << dateSet1;
	cout << "Size of Set1: " << dateSet1.size() << "\n\n";
	
	cout << "Set2: \n";
	cout << dateSet2;
	cout << "Size of Set2: " << dateSet2.size() << "\n\n";
	
	
	cout << "  ****************** DayOfYearSet Index Operator '[]' Testing : ****************** \n\n";
	
	DayOfYearSet testIndexSet = {DayOfYearSet::DayOfYear(1, 1), DayOfYearSet::DayOfYear(4, 2), DayOfYearSet::DayOfYear(21, 8)};
	
	cout << "Set: \n";
	cout << testIndexSet << "\n";
	
	try {
		cout << "Index [0]: " << testIndexSet[0] << "\n";
		cout << "Index[1]: " << testIndexSet[1] << "\n";
		cout << "Index[2]: " << testIndexSet[2] << "\n";
		cout << "Index[3]: " << testIndexSet[3] << "\n";
	} catch (const out_of_range& e) {
		cout << "Exception: " << e.what();
	} 
	cout << "\n\n";
	
	
	cout << "  ****************** DayOfYearSet Operator '==' and '!=' Testing : ****************** \n\n";
	
	DayOfYearSet testSet1 = {DayOfYearSet::DayOfYear(1, 1), DayOfYearSet::DayOfYear(4, 2), DayOfYearSet::DayOfYear(21, 8)};
	DayOfYearSet testSet2 = {DayOfYearSet::DayOfYear(1, 1), DayOfYearSet::DayOfYear(4, 2), DayOfYearSet::DayOfYear(21, 8)};
	
	cout << "Expected Result: 1 \n";
	cout << "Result: " << (int) (testSet1 == testSet2) << "\n\n";
	
	cout << "Expected Result: 0 \n";
	cout << "Result: " << (int) (testSet1 != testSet2) << "\n\n";
	
	DayOfYearSet testSet3;	// empty set.
	
	cout << "Expected Result: 0 \n";
	cout << "Result: " << (int) (testSet1 == testSet3) << "\n\n";
	
	cout << "Expected Result: 1 \n";
	cout << "Result: " << (int) (testSet1 != testSet3) << "\n\n";
	
	
	cout << "  ****************** DayOfYearSet Operator '<<' Testing : ****************** \n\n";
	
	cout << "TestSet1 Expected: \n";
	cout << "1/1 \n";
	cout << "4/2 \n";
	cout << "21/8 \n";
	cout << "TestSet1 Result: \n";
	cout << testSet1 << "\n\n";
	
	DayOfYearSet testSet4 = {DayOfYearSet::DayOfYear(6, 6), DayOfYearSet::DayOfYear(15, 1), DayOfYearSet::DayOfYear(13, 12)};
	
	cout << "TestSet4 Expected: \n";
	cout << "6/6 \n";
	cout << "15/1 \n";
	cout << "13/12 \n";
	cout << "TestSet4 Result: \n";
	cout << testSet4 << "\n\n";
	
	
	cout << "  ****************** DayOfYearSet Operator '+' for a new Date Testing : ****************** \n\n";
	
	DayOfYearSet::DayOfYear day15(19, 9);
	
	cout << "TestSet4 before '+' operator gets called with DayOfYear(19, 9): \n";
	cout << testSet4 << "\n";

	cout << "Set that '+' operator returned: \n";
	cout << testSet4 + day15 << "\n";
	
	cout << "TestSet4 after '+' operator gets called: \n";
	cout << testSet4 << "\n\n";
	
	DayOfYearSet::DayOfYear day16(20, 6);
	
	cout << "TestSet4 before '+' operator gets called with DayOfYear(20, 6): \n";
	cout << testSet4 << "\n";
	
	cout << "Set that '+' operator returned: \n";
	cout << testSet4 + day16 << "\n";
	
	cout << "TestSet4 after '+' operator gets called: \n";
	cout << testSet4 << "\n\n";
	
	
	cout << "  ****************** DayOfYearSet Operator '-' for a Date Testing : ****************** \n\n";
	
	cout << "TestSet4 before '-' operator gets called with DayOfYear(19, 9): \n";
	cout << testSet4 << "\n";

	cout << "Set that '-' operator returned: \n";
	cout << testSet4 - day15 << "\n";
	
	cout << "TestSet4 after '-' operator gets called: \n";
	cout << testSet4 << "\n\n";
	
	
	cout << "TestSet4 before '-' operator gets called with DayOfYear(20, 6): \n";
	cout << testSet4 << "\n";
	
	cout << "Set that '-' operator returned: \n";
	cout << testSet4 - day16 << "\n";
	
	cout << "TestSet4 after '-' operator gets called: \n";
	cout << testSet4 << "\n\n";
	
	
	cout << "  ****************** DayOfYearSet Operators '+', '-', '^' for Set Operations Testing : ****************** \n\n";
	
	cout << " ******* SET OPERATIONS TEST1 ****** \n";
	
	DayOfYearSet testSet5 = {DayOfYearSet::DayOfYear(6, 6), DayOfYearSet::DayOfYear(15, 1), DayOfYearSet::DayOfYear(13, 12)};
	DayOfYearSet testSet6 = {DayOfYearSet::DayOfYear(8, 7), DayOfYearSet::DayOfYear(4, 9), DayOfYearSet::DayOfYear(15, 1), DayOfYearSet::DayOfYear(22, 2)};
	
	cout << "Set1: \n";
	cout << testSet5 << "\n";
	
	cout << "Set2: \n";
	cout << testSet6 << "\n";
	
	cout << "UnionSet: \n";
	cout << testSet5 + testSet6 << "\n";
	
	cout << "Difference Set(s1-s2): \n";
	cout << testSet5 - testSet6 << "\n";
	
	cout << "Intersection Set: \n";
	cout << (testSet5 ^ testSet6) << "\n";
	
	
	cout << " ******* SET OPERATIONS TEST2 ****** \n";
	
	DayOfYearSet testSet7 = {DayOfYearSet::DayOfYear(27, 1), DayOfYearSet::DayOfYear(14, 10), DayOfYearSet::DayOfYear(16, 7)};
	DayOfYearSet testSet8 = {DayOfYearSet::DayOfYear(21, 7), DayOfYearSet::DayOfYear(27, 1), DayOfYearSet::DayOfYear(14, 10), DayOfYearSet::DayOfYear(22, 2), DayOfYearSet::DayOfYear(1, 1)};
	
	cout << "Set1: \n";
	cout << testSet7 << "\n";
	
	cout << "Set2: \n";
	cout << testSet8 << "\n";
	
	cout << "UnionSet: \n";
	cout << testSet7 + testSet8 << "\n";
	
	cout << "Difference Set(s1-s2): \n";
	cout << testSet7 - testSet8 << "\n";
	
	cout << "Intersection Set: \n";
	cout << (testSet7 ^ testSet8) << "\n";
	
	cout << "  ****************** DayOfYearSet Operator '!' Testing : ****************** \n\n";
	
	cout << "TestSet7: \n";
	cout << testSet7 << "\n";
	
	cout << "!TestSet7: \n";
	cout << !testSet7 << "\n";
	
	
	cout << "TestSet8: \n";
	cout << testSet8 << "\n";
	
	cout << "!(!TestSet8): \n";
	cout << !(!testSet8) << "\n";
	
	cout << "  ****************** DayOfYearSet CallByValue and Reference Testing : ****************** \n\n";
	
	cout << "Set to send as paramater : \n";
	cout << testSet7 << "\n";
	
	dayOfYearSet_callByValue(testSet7);
	dayOfYearSet_callByReference(testSet7);
	cout << "Set after calling call by reference : \n";
	cout << testSet7 << "\n\n";
	
	cout << "Set to send as paramater : \n";
	cout << testSet8 << "\n";
	
	dayOfYearSet_callByValue(testSet8);
	dayOfYearSet_callByReference(testSet8);
	cout << "Set after calling call by reference : \n";
	cout << testSet8 << "\n\n";
	
	cout << "  ****************** Writing sets to file : ****************** \n\n";
	
	DayOfYearSet fileSet1 = {DayOfYearSet::DayOfYear(8, 7), DayOfYearSet::DayOfYear(4, 9), DayOfYearSet::DayOfYear(15, 1), DayOfYearSet::DayOfYear(22, 2)};
	cout << "FileSet below is writing to the .txt file named 'set1.txt': \n";
	cout << fileSet1 << "\n";
	
	ofstream file1("set1.txt");
	if (file1.fail()) {
		cout << "Oops.. Fail cannot be opened this time. Check the folder and try again! \n";
	}
	else {
		file1 << fileSet1;
		file1.close();
	}
	
	DayOfYearSet fileSet2 = {DayOfYearSet::DayOfYear(1, 2), DayOfYearSet::DayOfYear(16, 2), DayOfYearSet::DayOfYear(16, 8), DayOfYearSet::DayOfYear(24, 12), DayOfYearSet::DayOfYear(12, 10)};
	cout << "FileSet below is writing to the .txt file named 'set2.txt': \n";
	cout << fileSet2 << "\n";
	
	ofstream file2("set2.txt");
	if (file2.fail()) {
		cout << "Oops.. Fail cannot be opened this time. Check the folder and try again! \n";
	}
	else {
		file2 << fileSet2;
		file2.close();
	}
	
	
	cout << "  ****************** TEST ENDED ****************** \n\n";
	
	return 0;
}	
