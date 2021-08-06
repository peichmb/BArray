#ifndef BARRAY_VECTOR_H
#define BARRAY_VECTOR_H

#include <assert.h>
#include <iostream>

// ------------------------
// -- Base class BVector --
// ------------------------

template<typename T>
class BVector {
public:
	// Constructors
	BVector(int size);
	BVector(int size, T ival);
	BVector(const BVector<T>& a);
	// Destructor
	~BVector();

	// Access
	T& operator() (int pos);
	T  operator() (int pos) const;

	// Operations
	BVector<T>& operator=(const BVector<T>& a);
	BVector<T>& operator+=(const BVector<T>& a);
	BVector<T>& operator-=(const BVector<T>& a);

	// Unary operators
	BVector<T> operator+() const;
	BVector<T> operator-() const;

	// Getters
	int get_size() const;

private:
	int size_;
	T* data_;
};


// Constructor
template<typename T>
BVector<T>::BVector(int size) {
	size_ = size;
	data_ = new T[size];
}


// Constructor with initialization value
template<typename T>
BVector<T>::BVector(int size, T ival) {
	size_ = size;
	data_ = new T[size];
	for (int i=0; i<size; i++) {
		data_[i] = ival;
	}
}


// Copy constructor
template<typename T>
BVector<T>::BVector(const BVector<T>& a) {
	size_ = a.get_size();
	data_ = new T[size_];
	for (int i=0; i<size_; i++) {
		(*this)(i) = a(i);
	}
}


// Destructor
template<typename T>
BVector<T>::~BVector() {
	delete[] data_;
}


// Access
template<typename T>
T& BVector<T>::operator() (int pos) {
	if (pos >= 0) {
		assert(pos < size_);
	} else {
		assert(pos >= -size_);
		pos += size_;
	}
	return data_[pos];
}


// Access (const)
template<typename T>
T BVector<T>::operator() (int pos) const {
	if (pos >= 0) {
		assert(pos < size_);
	} else {
		assert(pos >= -size_);
		pos += size_;
	}
	return data_[pos];
}

// Assignment
template<typename T>
BVector<T>& BVector<T>::operator=(const BVector<T>& a) {
	assert(a.get_size() == size_);
	for (int i=0; i<size_; i++) {
		(*this)(i) = a(i);
	}
	return *this;
}


// += operator
template<typename T>
BVector<T>& BVector<T>::operator+=(const BVector<T>& a) {
	assert(a.get_size() == size_);
	for (int i=0; i<size_; i++) {
		(*this)(i) += a(i);
	}
	return *this;
}


// -= operator
template<typename T>
BVector<T>& BVector<T>::operator-=(const BVector<T>& a) {
	assert(a.get_size() == size_);
	for (int i=0; i<size_; i++) {
		(*this)(i) -= a(i);
	}
	return *this;
}


// Unary + operator
template<typename T>
BVector<T> BVector<T>::operator+ () const {
	BVector<T> result(size_);
	for (int i=0; i<size_; i++) {
		result(i) = (*this)(i);
	}
	return result;
}


// Unary - operator
template<typename T>
BVector<T> BVector<T>::operator- () const {
	BVector<T> result(size_);
	for (int i=0; i<size_; i++) {
		result(i) = -(*this)(i);
	}
	return result;
}


// Getters
template<typename T>
int BVector<T>::get_size() const {
	return size_;
}


// ---------------------------------
// -- Insertion operator overload --
// ---------------------------------
	
template<typename T>
std::ostream& operator<<(std::ostream& output, const BVector<T>& vector);

template<typename T>
std::ostream& operator<<(std::ostream& output, const BVector<T>& vector) {
	
	int NMAX = 7; 
	int size = vector.get_size();
	output << "\nBVector (" << size << "):\n";
	output << "[ ";
	if (size <= NMAX) {
		for (int i=0; i<size; i++) {
			output << vector(i) << " ";
		}
	} else {
		for (int i=0; i<NMAX/2; i++) {
			output << vector(i) << " ";
		}
		output << "... ";
		for (int i=size-NMAX/2; i<size; i++) {
			output << vector(i) << " ";
		}
	}
	output << "]\n";
	return output;
}


#endif // BARRAY_VECTOR_H
