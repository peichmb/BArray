#ifndef BARRAY_ARITHM_H
#define BARRAY_ARITHM_H

#include "./vector.h"
#include "./matrix.h"

// ------------------------------------------------
// -- Basic operations with matrices and vectors -- 
// ------------------------------------------------

// Scalar - Vector
template<typename T>
BVector<T> operator*(T, const BVector<T>&);

template<typename T>
BVector<T> operator*(const BVector<T>&, T);

template<typename T>
BVector<T> operator/(const BVector<T>&, T);


// Scalar - Matrix
template<typename T>
BMatrix<T> operator*(T, const BMatrix<T>&);

template<typename T>
BMatrix<T> operator*(const BMatrix<T>&, T);

template<typename T>
BMatrix<T> operator/(const BMatrix<T>&, T);


// Vector - Vector
template<typename T>
BVector<T> operator+(const BVector<T>&, const BVector<T>&);

template<typename T>
BVector<T> operator-(const BVector<T>&, const BVector<T>&);

template<typename T>
T operator*(const BVector<T>&, const BVector<T>&);


// Vector - Matrix
template<typename T>
BVector<T> operator*(const BVector<T>&, const BMatrix<T>&);

template<typename T>
BVector<T> operator*(const BMatrix<T>&, const BVector<T>&);


// Matrix - Matrix
template<typename T>
BMatrix<T> operator+(const BMatrix<T>&, const BMatrix<T>&);

template<typename T>
BMatrix<T> operator-(const BMatrix<T>&, const BMatrix<T>&);

template<typename T>
BMatrix<T> operator*(const BMatrix<T>&, const BMatrix<T>&);


// ------------------------------------------------------------------
// -- Implementation of basic operations with matrices and vectors -- 
// ------------------------------------------------------------------

// Scalar - Vector
template<typename T>
BVector<T> operator*(T scal, const BVector<T>& vec) {
	BVector<T> result(vec.get_size());
	for (int i=0; i<vec.get_size(); i++) {
		result(i) = scal*vec(i);
	}
	return result;
}

template<typename T>
BVector<T> operator*(const BVector<T>& vec, T scal) {
	return (scal*vec);
}

template<typename T>
BVector<T> operator/(const BVector<T>& vec, T scal) {
	assert (scal != (T)0);
	BVector<T> result(vec.get_size());
	for (int i=0; i<vec.get_size(); i++) {
		result(i) = vec(i)/scal;
	}
	return result;
}


// Scalar - Matrix
template<typename T>
BMatrix<T> operator*(T scal, const BMatrix<T>& mat) {

	BMatrix<T> result(mat.get_nrows(), mat.get_ncols());
	for(int i=0; i<mat.get_nrows(); i++) {
		for(int j=0; j<mat.get_ncols(); j++) {
			result(i,j) = scal*mat(i,j);
		}
	}
	return result;
}

template<typename T>
BMatrix<T> operator*(const BMatrix<T>& mat, T scal) {
	return (scal*mat);
}

template<typename T>
BMatrix<T> operator/(const BMatrix<T>& mat, T scal) {
	assert (scal != (T)0);
	BMatrix<T> result(mat.get_nrows(), mat.get_ncols());
	for(int i=0; i<mat.get_nrows(); i++) {
		for(int j=0; j<mat.get_ncols(); j++) {
			result(i,j) = mat(i,j)/scal;
		}
	}
	return result;
}


// Vector - Vector
template<typename T>
BVector<T> operator+(const BVector<T>& vecA, const BVector<T>& vecB) {
	assert(vecA.get_size() == vecB.get_size());
	BVector<T> result(vecA.get_size());
	for (int i=0; i<vecA.get_size(); i++) {
		result(i) = vecA(i) + vecB(i);
	}
	return result;
}

template<typename T>
BVector<T> operator-(const BVector<T>& vecA, const BVector<T>& vecB) {
	assert(vecA.get_size() == vecB.get_size());
	BVector<T> result(vecA.get_size());
	for (int i=0; i<vecA.get_size(); i++) {
		result(i) = vecA(i) - vecB(i);
	}
	return result;
}

template<typename T>
T operator*(const BVector<T>& vecA, const BVector<T>& vecB) {
	assert(vecA.get_size() == vecB.get_size());
	T result = (T)0;
	for (int i=0; i<vecA.get_size(); i++) {
		result += vecA(i) * vecB(i);
	}
	return result;
}


// Vector - Matrix
template<typename T>
BVector<T> operator*(const BVector<T>& vec, const BMatrix<T>& mat) {
	assert(vec.get_size() == mat.get_nrows());
	BVector<T> result(mat.get_ncols());
	for (int j=0; j<mat.get_ncols(); j++) {
		result(j) = (T)0;
		for (int i=0; i<mat.get_nrows(); i++) {
			result(j) += vec(i)*mat(i,j);
		}
	}
	return result;
}

template<typename T>
BVector<T> operator*(const BMatrix<T>& mat, const BVector<T>& vec) {
	assert(mat.get_ncols() == vec.get_size());
	BVector<T> result(mat.get_nrows());
	for (int i=0; i<mat.get_nrows(); i++) {
		result(i) = (T)0;
		for (int j=0; j<mat.get_ncols(); j++) {
			result(i) += vec(j)*mat(i,j);
		}
	}
	return result;
}


// Matrix - Matrix
template<typename T>
BMatrix<T> operator+(const BMatrix<T>& matA, const BMatrix<T>& matB) {
	int nrows = matA.get_nrows();
	int ncols = matA.get_ncols();
	assert(nrows == matB.get_nrows() && ncols == matB.get_ncols());
	BMatrix<T> result(nrows, ncols);
	for (int i=0; i<nrows; i++) {
		for (int j=0; j<ncols; j++) {
			result(i,j) = matA(i,j) + matB(i,j);
		}
	}
	return result;
}

template<typename T>
BMatrix<T> operator-(const BMatrix<T>& matA, const BMatrix<T>& matB) {
	int nrows = matA.get_nrows();
	int ncols = matA.get_ncols();
	assert(nrows == matB.get_nrows() && ncols == matB.get_ncols());
	BMatrix<T> result(nrows, ncols);
	for (int i=0; i<nrows; i++) {
		for (int j=0; j<ncols; j++) {
			result(i,j) = matA(i,j) - matB(i,j);
		}
	}
	return result;
}

template<typename T>
BMatrix<T> operator*(const BMatrix<T>& matA, const BMatrix<T>& matB) {
	assert( matA.get_ncols() == matB.get_nrows() );
	int m = matA.get_ncols();
	int result_nrows = matA.get_nrows();
	int result_ncols = matB.get_ncols();
	BMatrix<T> result(result_nrows, result_ncols);
	for (int i=0; i<result_nrows; i++) {
		for (int j=0; j<result_ncols; j++) {
			result(i,j) = (T)0;
			for (int k=0; k<m; k++) {
				result(i,j) += matA(i,k) * matB(k,j);
			}
		}
	}
	return result;
}


#endif //BARRAY_ARITHM_H
