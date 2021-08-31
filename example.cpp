#include "barray.h"

int main() {

	BMatrix<double> a(5,3,0), b(a);

	for (int i=0; i<a.get_nrows(); i++) {
		for (int j=0; j<a.get_ncols(); j++) {
			a(i,j) = i+j+1;
			b(i,j) = (i+1)*(j-1) + 2*i - 4 + 3*j;
		}
	}
	BMatrix<double> c(b.transpose());
	std::cout << "A = " << a << "B = " << b << "C = " << c << "\n";

	std::cout << "A*C = " << a*c << "C*A = " << c*a << "\n";

	a = 2.*a + 3.*b;

	std::cout << "A = 2*A + 3*B; " << a << "\n";

	std::cout << "B += A; " << (b+=a) << "\n";

	std::cout << "B = " << b << "\n";

	std::cout << "B = -B; " << (b=-b) << "\n";

	std::cout << "B = " << b << "\n";

	std::cout << "B -= B + -B; " << (b-=b + -b) << "\n";

	std::cout << "B -= B" << (b-=b) << "\n";

	std::cout << "B = 2*A - A" << (b=2.*a - a) << "\n";

	std::cout << "B = 2*A - A*2" << (b=2.*a - a*2.) << "\n";

	BVector<double> v(3), u(3);
	for (int i=0; i<v.get_size(); i++) {
		v(i) = (i+1)*(i+2);
		u(i) = 1 + (i-1)*(i-2);
	}

	std::cout << "v = " << v << "u = " << u << "\n";

	std::cout << "u*v = " << u*v << "\n";

	std::cout << "3*u = " << 3.*u << "\n";

	std::cout << "u+=u; " << (u+=u) << "\n";

	std::cout << "u+=u-v; " << (u+=u-v) << "\n";

	std::cout << "u-=u; " << (u-=u) << "\n";

	std::cout << "u=v; " << (u=v) << "\n";

	std::cout << "u + v; " << (u + v) << "\n";

	std::cout << "u + -v; " << (u + -v) << "\n";

	std::cout << "u + +v; " << (u + +v) << "\n";

	std::cout << "u*2 = " << (u*2.) << "\n";

	std::cout << "A = " << a;
	std::cout << "u = " << u;
	std::cout << "A*u = " << a*u << "\n";

	BVector<double> w(5);
	for (int i=0; i<w.get_size(); i++) {
		w(i) = i;
	}

	std::cout << "A = " << a;
	std::cout << "w = " << w;
	std::cout << "w*A = " << w*a << "\n";

	std::cout << "w/5 = " << w/5. << "\n";

	std::cout << "a = " << a << "a/2 = " << a/2. << "\n";

	std::cout << "a += a + 2.*b -3.*a - 4.*b/2. + a*2. +-a; " << (a += a + 2.*b -3.*a - 4.*b/2. + a*2. +-a); 

}


