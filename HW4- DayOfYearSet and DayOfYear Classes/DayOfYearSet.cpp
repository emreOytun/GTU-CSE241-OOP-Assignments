#include <iostream>
#include <stdexcept>
#include "DayOfYearSet.h"

using std::initializer_list;
using std::runtime_error;
using std::out_of_range;

namespace GTUDate {
	
	const int DEFAULT_CAPACITY = 10;
	
	DayOfYearSet::DayOfYearSet() : len(0), capacity(0), data(nullptr) {
		adjustCapacity(DEFAULT_CAPACITY);
	}
	
	DayOfYearSet::DayOfYearSet(const initializer_list<DayOfYear>& list) : DayOfYearSet() {
		for (auto element : list) {
			add(element);
		}
	}
	
	DayOfYearSet::DayOfYearSet(const DayOfYearSet& oth) : len(0), capacity(0), data(nullptr) {
		decltype(oth.capacity) newCapacity = oth.capacity;
		adjustCapacity(newCapacity);
		len = oth.len;
		for (int i = 0; i < oth.len; ++i) {
			data[i] = oth.data[i];
		}
	}
	
	DayOfYearSet& DayOfYearSet::operator=(const DayOfYearSet& oth) {
		if (data != nullptr) delete [] data;
		
		decltype(oth.capacity) newCapacity = oth.capacity;
		adjustCapacity(newCapacity);
		len = oth.len;

		for (int i = 0; i < oth.len; ++i) {
			data[i] = oth.data[i];
		}
		
		return *this;
	}
	
	DayOfYearSet::~DayOfYearSet() noexcept {
		if (data != nullptr) delete [] data;
	}
	
	/* Adds the given date if it does not exist in the set. */
	void DayOfYearSet::add(const DayOfYearSet::DayOfYear& newDate) {
		if (!isExist(newDate)) {
			if (len == capacity) adjustCapacity(capacity*2); /* Check if capacity is enough; grow it otherwise. */
			data[len] = newDate;
			++len;
		}
	}
	
	/* Removes the given date if it exists in the set. */
	void DayOfYearSet::remove(const DayOfYearSet::DayOfYear& date) {
	
		/* Checks if the given date exists. */
		bool isFound = false;
		int idx = -1;
		for (int i = 0; i < len && !isFound; ++i) {
			if (date == data[i]) {
				isFound = true;
				idx = i;
			}
		}
		
		if (isFound) {
			/* Shift elements. */
			for (int i = idx+1; i < len; ++i) {
				data[i-1] = data[i];
			}
			
			--len;
			if (len > 0 && len % DEFAULT_CAPACITY == 0) adjustCapacity(len); /* Check if capacity is larger than enoguh; if so shrink it.*/
		}
		
	}
	
	int DayOfYearSet::size() const noexcept {
		return len;
	}
	
	DayOfYearSet::DayOfYear& DayOfYearSet::operator[](int idx) {
		if (idx < 0 || idx >= len) {
			throw out_of_range("Given index is out of the boundaries.");
		} 
	
		return data[idx];
	}
	
	const DayOfYearSet::DayOfYear DayOfYearSet::operator[](int idx) const {
		if (idx < 0 || idx >= len) {
			throw out_of_range("Given index is out of the boundaries.");
		} 
	
		return data[idx];	
	}
	
	bool DayOfYearSet::operator==(const DayOfYearSet& oth) const noexcept {
		if (this == &oth) return true; /* Check if the given set is the exact set as this. */
		if (len != oth.len) return false;
		
		bool isEqual = true;
		for (int i = 0; i < oth.len && isEqual; ++i) {
			if (!isExist(oth.data[i])) isEqual = false;
		}
		return isEqual;
	}
	
	bool DayOfYearSet::operator!=(const DayOfYearSet& oth) const noexcept {
		return !((*this) == oth);
	}
	
	DayOfYearSet& DayOfYearSet::operator+(const DayOfYearSet::DayOfYear& date) {
		add(date);
		return *this;
	}
	
	
	DayOfYearSet& DayOfYearSet::operator-(const DayOfYearSet::DayOfYear& date) {
		remove(date);
		return *this;
	}
	
	/* '+' operator to return Union Set. */
	const DayOfYearSet DayOfYearSet::operator+(const DayOfYearSet& oth) const {
		DayOfYearSet unionSet(*this);
		
		/* If unionSet does not have the element which other set has, then add this element into the unionSet. */
		for (int i = 0; i < oth.len; ++i) {
			if (!unionSet.isExist(oth.data[i])) {
				unionSet.add(oth.data[i]);
			}
		}
		
		return unionSet;
	}
	
	/* '-' operator to return Difference Set. */
	const DayOfYearSet DayOfYearSet::operator-(const DayOfYearSet& oth) const {
		DayOfYearSet diffSet(*this);
		
		/* If an element from diffSet exists inside other set, then remove this element from diffSet. */
		for (int i = 0; i < oth.len; ++i) {
			if (diffSet.isExist(oth.data[i])) {
				diffSet.remove(oth.data[i]);
			}
		}
	
		return diffSet;
	}
	
	/* '^' operator to return Intersection Set. */
	const DayOfYearSet DayOfYearSet::operator^(const DayOfYearSet& oth) const {
		DayOfYearSet interSet(*this);
		
		/* If other does not have the element which diffSet has, then remove this element from diffSet. */
		for (int i = 0; i < len; ++i) {
			if (!oth.isExist((*this)[i])) {
				interSet.remove((*this)[i]);
			}
		}
		
		return interSet;
	}
	
	const DayOfYearSet operator!(const DayOfYearSet& dateSet) {
		DayOfYearSet complementSet;
		
		/* Since February is 29 days as specified in the pdf, there are 366 days in the year. */
		DayOfYearSet::DayOfYear day(1, 1);
		for (int i = 0; i < 366; ++i) {
			if (!dateSet.isExist(day)) {
				complementSet.add(day);
			}
			++day;
		}
		
		return complementSet;
	}

	ostream& operator<<(ostream& ostream, const DayOfYearSet& dateSet) {
		for (int i = 0; i < dateSet.len; ++i) {
			ostream << dateSet.data[i] << "\n";
		}	
		return ostream;
	}
	
	/* Check if the given date exists in the set. */
	bool DayOfYearSet::isExist(const DayOfYearSet::DayOfYear& date) const noexcept {
		bool isFound = false;
		for (int i = 0; i < len && !isFound; ++i) {
			if (data[i] == date) isFound = true;
		}
		return isFound; 
	}
	
	/* Adjust the data capacity using given new capacity parameter. */
	void DayOfYearSet::adjustCapacity(int newCapacity) {
		auto newData = new DayOfYearSet::DayOfYear[newCapacity];
		for (int i = 0; i < len; ++i) newData[i] = data[i];
		
		if (data != nullptr) delete [] data;
		data = newData;
		capacity = newCapacity;
	}	

}
