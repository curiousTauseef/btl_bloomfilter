/*
 * BloomMap.hpp
 *
 *  Created on: Dec 17, 2015
 *      Author: gjahesh
 */

#ifndef BLOOMMAP_HPP_
#define BLOOMMAP_HPP_

#include <vector>

template<typename T>
class BloomMap {

public:

	BloomMap<T>(size_t filterSize, unsigned hashNum) :
			m_size(filterSize), m_hashNum(hashNum) {
		m_array.resize(filterSize);
	}

	void insert(std::vector<size_t> const &hashes, std::vector<T> &values) {

		//iterates through hashed values adding it to the filter
		for (size_t i = 0; i < m_hashNum; ++i) {
			size_t pos = hashes.at(i) % m_size;
			m_array[pos] = values[i];
		}
	}

	std::vector<T> query(std::vector<size_t> const &hashes) {

		std::vector<T> values;

		for (size_t i = 0; i < m_hashNum; ++i) {
			size_t pos = hashes.at(i) % m_size;
			values.push_back(m_array[pos]);

		}
		return values;
	}

private:

	size_t m_size;
	unsigned m_hashNum;
	std::vector<T> m_array;

};

#endif /* BLOOMMAP_HPP_ */
