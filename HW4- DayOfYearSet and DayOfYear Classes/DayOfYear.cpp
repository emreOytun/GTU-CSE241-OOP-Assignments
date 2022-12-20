#include <iostream>
#include <stdexcept>
#include <string>
#include "DayOfYearSet.h"

using std::ostream;
using std::to_string;
using std::invalid_argument;

/* Unnamed namespace to use helper variables and functions to implement DayOfYear class. */
namespace {
	const int dayNumOfMonths[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; /* Day numbers of months are kept inside this array (February is always 29 days according to the HW PDF.) */
	
	/* Check the validity of a date. */
	bool isValidDate(int day, int month) {
		bool result = true;
		if ( !(1<=month && month<=12) ) result = false;
		else if ( !(1<=day && day<=dayNumOfMonths[month-1]) ) result = false;
		
		return result;
	}	
}


namespace GTUDate {
	

	DayOfYearSet::DayOfYear::DayOfYear() : day(1), month(1) {

	}

	DayOfYearSet::DayOfYear::DayOfYear(int day_, int month_) {
		setDate(day_, month_);
	}
	
	void DayOfYearSet::DayOfYear::setDate(int day_, int month_) {
		if (!isValidDate(day_, month_)) {
			throw invalid_argument("Invalid day:" + std::to_string(day_) + " and month:" + std::to_string(month_) + " parameters.");
		}
		this->day = day_;
		this->month = month_;
	}
	
	void DayOfYearSet::DayOfYear::setMonth(int month_) {
		if (!isValidDate(day, month_)) {
			throw invalid_argument("Invalid month:" + std::to_string(month_) + " parameter.");
		}
		this->month = month_;	
	}
	
	void DayOfYearSet::DayOfYear::setDay(int day_) {
		if (!isValidDate(day_, month)) {
			throw invalid_argument("Invalid day:" + std::to_string(day_) + " parameter.");
		}
		this->day = day_;
	}
	
	int DayOfYearSet::DayOfYear::getMonth() const noexcept { return month; }
	
	int DayOfYearSet::DayOfYear::getDay() const noexcept { return day; }

	bool DayOfYearSet::DayOfYear::operator==(const DayOfYearSet::DayOfYear& oth) const noexcept {
		if (this == &oth) return true;
		if (day == oth.day && month == oth.month) return true;
		return false;
	}

	bool DayOfYearSet::DayOfYear::operator!=(const DayOfYearSet::DayOfYear& oth) const noexcept {
		return !((*this) == oth);
	}

	DayOfYearSet::DayOfYear& DayOfYearSet::DayOfYear::operator++() noexcept {
		/* Firstly, check if current date is at the end of the current month. */
		if (day == dayNumOfMonths[month-1]) {
			day = 1;
			if (month == 12) month = 1;
			else ++month;
		}
		
		else ++day;

		return *this;
	}

	const DayOfYearSet::DayOfYear DayOfYearSet::DayOfYear::operator++(int) noexcept {
		DayOfYear copy = *this;
		++(*this);
		return copy;
	}

	DayOfYearSet::DayOfYear& DayOfYearSet::DayOfYear::operator--() noexcept {
		/* Firstly, check if the current date is at the 1st day of the month. */
		if (day == 1) {
			if (month == 1) month = 12;
			else --month;
			
			day = dayNumOfMonths[month-1];
		}
		
		else --day;
		
		return *this;
	}

	const DayOfYearSet::DayOfYear DayOfYearSet::DayOfYear::operator--(int) noexcept {
		DayOfYear copy = *this;
		--(*this);
		return copy;
	}

	ostream& operator<<(ostream& ostream, const DayOfYearSet::DayOfYear& oth) {
		ostream << oth.day << "/" << oth.month;
		return ostream;
	}

}

