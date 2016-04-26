/*
 * CountingBloomFilter.hpp
 *
 *  Created on: Dec 17, 2015
 *      Author: gjahesh
 */

#ifndef COUNTINGBLOOMFilter_HPP_
#define COUNTINGBLOOMFilter_HPP_

#include <vector>
#include <omp.h>
#include <valarray>
#include <math.h>
#include <cassert>
#include <string>
#include "BloomMap.hpp"

template<typename T>
class CountingBloomFilter {
public:

	/** Constructor */
	CountingBloomFilter(size_t filterSize, unsigned hashNum) :
		m_size(filterSize), m_hashNum(hashNum),
		m_bloomMap(filterSize, hashNum, 0) {
		//m_array.resize(filterSize);
		
}

	/** Destructor */
	virtual ~CountingBloomFilter() {
	}

	/** Return the count of the single element*/
	T operator[](size_t i) const {
		return m_bloomMap[i];
	}

	/** Add the object to this counting multiset.
	 *  If all values are the same update all
	 *  If some values are larger only update smallest counts*/
	void insert(std::vector<size_t> const &hashes) {
		//check for which elements to update, basically holding the minimum
		//hash value i.e counter value.
		T minEle = (*this)[hashes];

		//update only those elements that have a minimum counter value.
		for (unsigned int i = 0; i < m_hashNum; ++i) {
			size_t hashVal = hashes.at(i) % m_size;
			T val = m_bloomMap[hashVal];
			if (minEle == val) {
				insert(hashVal);
			}
		}
	}

	/** Add the object with the specified index (debug). */
	void insert(size_t index) {
#pragma omp atomic
		++m_bloomMap[index];
	}

	/** Return the count of an element based on a Minimum Selection */

	T operator[](std::vector<size_t> const &hashes) const {

		T currentMin = m_bloomMap[hashes.at(0) % m_size];
		for (unsigned int i = 1; i < m_hashNum; ++i) {
			T min = m_bloomMap[hashes.at(i) % m_size];
			if (min < currentMin) {
				currentMin = min;
			}
			if (0 == currentMin) {
				return (0);
			}
		}
		return currentMin;
	}

	/** Return the count of the single element*/

	T query(size_t i) const {
		return m_bloomMap[i];
	}

private:

	size_t m_size;
	unsigned m_hashNum;
	//std::vector<T> m_array;
	BloomMap<T> m_bloomMap;
};

#endif /* COUNTINGBLOOM_HPP_ */
