#ifndef BARRAY_SPECIAL_H
#define BARRAY_SPECIAL_H

#include <iostream>

template<typename T>
class BMatrix;

// ----------------------------------------
// -- Implementation of special matrices --
// ----------------------------------------


template<typename T>
class BDiagonal : public BMatrix<T> {
public:
	BDiagonal(int size, T val) : BMatrix<T>("BDiagonal", size, size, size, val) {}
	// Access
	T& operator() (int row, int col);
	T  operator() (int row, int col) const;
	T& operator() (int pos);
	T  operator() (int pos) const;

};

template<typename T>
T& BDiagonal<T>::operator()(int row, int col) {
	assert(row < this->nrows_ && col < this->ncols_);
	assert(col == row);
	return this->data_[col];
}

template<typename T>
T BDiagonal<T>::operator()(int row, int col) const {
	assert(row < this->nrows_ && col < this->ncols_);
	if (row == col) {
		return this->data_[col];
	} else {
		return T(0);
	}
}

template<typename T>
T& BDiagonal<T>::operator()(int pos) {
	if (pos >= 0) {
		assert(pos < this->nelem_);
	} else {
		assert(pos >= -this->nelem_);
		pos += this->nelem_;
	}
	return this->data_[pos];
}

template<typename T>
T BDiagonal<T>::operator()(int pos) const {
	if (pos >= 0) {
		assert(pos < this->nelem_);
	} else {
		assert(pos >= -this->nelem_);
		pos += this->nelem_;
	}
	return this->data_[pos];
}


#endif
