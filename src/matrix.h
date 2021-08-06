#ifndef BARRAY_MATRIX_H
#define BARRAY_MATRIX_H

#include <assert.h>
#include <iostream>

// ------------------------
// -- Base class BMatrix --
// ------------------------

template<typename T>
class BMatrix {

public:
	// Constructors
	BMatrix(int nrows, int ncols) : BMatrix("BMatrix", nrows, ncols, nrows*ncols) {}
	BMatrix(int nrows, int ncols, T ival) : BMatrix("BMatrix", nrows, ncols, nrows*ncols, ival) {}
	// Copy constructor
	BMatrix(const BMatrix<T>& a);
	// Destructor
	~BMatrix();

	// Access
	virtual T& operator() (int row, int col);
	virtual T  operator() (int row, int col) const;

	// Operations
	virtual BMatrix<T>& operator=(const BMatrix<T>& a);
	virtual BMatrix<T>& operator+=(const BMatrix<T>& a);
	virtual BMatrix<T>& operator-=(const BMatrix<T>& a);
	virtual BMatrix<T> transpose() const;

	// Unary operation
	virtual BMatrix<T> operator+() const;
	virtual BMatrix<T> operator-() const;

	// Getters
	int get_ncols() const;
	int get_nrows() const;
	int get_size() const;
	std::string get_mtype() const;

protected:

	int get_nelem() const;
	BMatrix(std::string mtype, int nrows, int ncols, int nelem);
	BMatrix(std::string mtype, int nrows, int ncols, int nelem, T ival);
	int nrows_, ncols_, nelem_;
	std::string mtype_;
	T* data_;

};


// Constructor
template<typename T>
BMatrix<T>::BMatrix(std::string mtype, int nrows, int ncols, int nelem) {
	nrows_ = nrows;
	ncols_ = ncols;
	nelem_ = nelem;
	mtype_ = mtype;
	data_ = new T[nelem];
}


// Constructor with initialization value
template<typename T>
BMatrix<T>::BMatrix(std::string mtype, int nrows, int ncols, int nelem, T ival) {
	nrows_ = nrows;
	ncols_ = ncols;
	nelem_ = nelem;
	mtype_ = mtype;
	data_ = new T[nelem];
	for (int i=0; i<nelem; i++) {
		data_[i] = ival;
	}
}


// Copy constructor
template<typename T>
BMatrix<T>::BMatrix(const BMatrix<T>& mat) {
	nrows_ = mat.nrows_;
	ncols_ = mat.ncols_;
	nelem_ = mat.nelem_;
	mtype_ = mat.mtype_;
	data_ = new T[nelem_];
	for (int i=0; i<nelem_; i++) {
		data_[i] = mat.data_[i];
	}
}


// Destructor
template<typename T>
inline
BMatrix<T>::~BMatrix()
{
	delete[] data_;
}


// Access
template<typename T>
inline
T& BMatrix<T>::operator() (int row, int col)
{
	if (row >= 0) {
		assert(row < nrows_);
	} else {
		assert(row >= -nrows_);
		row += nrows_;
	}
	if (col >= 0) {
		assert(col < ncols_);
	} else {
		assert(col >= -ncols_);
		col += ncols_;
	}
	return data_[ncols_*row + col];
}


// Access (const)
template<typename T>
inline
T BMatrix<T>::operator() (int row, int col) const
{
	if (row >= 0) {
		assert(row < nrows_);
	} else {
		assert(row >= -nrows_);
		row += nrows_;
	}
	if (col >= 0) {
		assert(col < ncols_);
	} else {
		assert(col >= -ncols_);
		col += ncols_;
	}
	return data_[ncols_*row + col];
}


// Get number of columns
template<typename T>
inline
int BMatrix<T>::get_ncols() const { return ncols_; }

// Get number of rows
template<typename T>
inline
int BMatrix<T>::get_nrows() const { return nrows_; }

// Get size
template<typename T>
inline
int BMatrix<T>::get_size() const { return nrows_*ncols_; }

// Get size of data array
template<typename T>
inline
int BMatrix<T>::get_nelem() const { return nelem_; }

// Get matrix type
template<typename T>
inline
std::string BMatrix<T>::get_mtype() const { return mtype_; }

// Assignment
template<typename T>
BMatrix<T>& BMatrix<T>::operator= (const BMatrix<T>& a) {
	assert(a.get_nrows() == nrows_ && a.get_ncols() == ncols_);
	for (int i=0; i<nrows_; i++) {
		for (int j=0; j<ncols_; j++) {
			(*this)(i,j) = a(i,j);
		}
	}
	return *this;
}


// += operator
template<typename T>
BMatrix<T>& BMatrix<T>::operator+= (const BMatrix<T>& a) {
	assert(a.get_nrows() == nrows_ && a.get_ncols() == ncols_);
	for (int i=0; i<nrows_; i++) {
		for (int j=0; j<ncols_; j++) {
			(*this)(i,j) += a(i,j);
		}
	}
	return *this;
}


// -= operator
template<typename T>
BMatrix<T>& BMatrix<T>::operator-= (const BMatrix<T>& a) {
	assert(a.get_nrows() == nrows_ && a.get_ncols() == ncols_);
	for (int i=0; i<nrows_; i++) {
		for (int j=0; j<ncols_; j++) {
			(*this)(i,j) -= a(i,j);
		}
	}
	return *this;
}


// Unary + operator
template<typename T>
BMatrix<T> BMatrix<T>::operator+ () const {
	BMatrix result(nrows_, ncols_);
	for (int i=0; i<nrows_; i++) {
		for (int j=0; j<ncols_; j++) {
			result(i,j) = (*this)(i,j);	
		}
	}
	return result;
}


// Unary - operator
template<typename T>
BMatrix<T> BMatrix<T>::operator- () const {
	BMatrix result(nrows_, ncols_);
	for (int i=0; i<nrows_; i++) {
		for (int j=0; j<ncols_; j++) {
			result(i,j) = -(*this)(i,j);	
		}
	}
	return result;
}


// Transpose
template<typename T>
BMatrix<T> BMatrix<T>::transpose() const {
	BMatrix<T> result(ncols_, nrows_);
	for (int i=0; i<nrows_; i++) {
		for (int j=0; j<ncols_; j++) {
			result(j,i) = (*this)(i,j);
		}
	}
	return result;
}


// ----------------------------------
// -- Insertion operator overloads --
// ----------------------------------
	
template<typename T>
std::ostream& operator<<(std::ostream& output, const BMatrix<T>& matrix);
	

template<typename T>
std::ostream& operator<<(std::ostream& output, const BMatrix<T>& matrix) {

	int NMAX = 7; // This must be an odd number for now
	int nrows = matrix.get_nrows();
	int ncols = matrix.get_ncols();

	bool print_all_rows = true;
	bool print_all_cols = true;
	int nrows_print = nrows;
	int ncols_print = ncols;

	if (nrows > NMAX) {
		print_all_rows = false;
		nrows_print = NMAX;
	}
	if (ncols > NMAX) {
		print_all_cols = false;
		ncols_print = NMAX;
	}

	output << "\n" << matrix.get_mtype() << " (" << nrows << "," << ncols << "):\n";

	for (int i=0; i<nrows_print; i++) {
		int ip = i;
		if (!print_all_rows) {
			ip = i<nrows_print/2 ? i : nrows - nrows_print + i;
		}
		if (!print_all_rows && i==nrows_print/2) {
			output << " ... ...\n";
		} else {

			output << "[ ";
			for (int j=0; j<ncols_print; j++) {
				int jp = j;
				if (!print_all_cols) {
					jp = j < ncols_print/2 ? j : ncols - ncols_print + j;
				}
				if (!print_all_cols && j==ncols_print/2) {
					output << "... ";
				} else {
					output << matrix(ip,jp) << " ";
				}
			}
			output << "]\n";
		}
	}
	return output;
}


#endif // BARRAY_MATRIX_H
