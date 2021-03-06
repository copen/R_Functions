#include<RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]])

using namespace Rcpp;
using namespace arma;


RcppExport SEXP ab_C(SEXP X, SEXP M, SEXP Y, SEXP IND){
	NumericVector x(X);
	NumericVector ms(M);
	NumericVector ys(Y);
	IntegerVector id(IND);
	int n=x.size(), ntotal=id.size();
	arma::mat onesx=ones<mat>(n, 2);
	arma::mat onesmx=ones<mat>(n, 3);
	int nboot=ntotal/n;
	NumericVector ab(nboot);
	arma::mat y=mat(n, 1);
	arma::mat m=mat(n, 1);
	for(int i=0; i<nboot; i++){
		for(int j=0; j<n; j++){
			onesx(j,1)  = x(id(n*i+j));
			onesmx(j,1) = ms(id(n*i+j));
			onesmx(j,2) = x(id(n*i+j));
			y(j,0)	    = ys(id(n*i+j));
			m(j,0)	    = ms(id(n*i+j));
			if(j==(n-1)){
				arma::mat b1 = (onesx.t()*onesx).i()*(onesx.t()*m);
				arma::mat b2 = (onesmx.t()*onesmx).i()*(onesmx.t()*y);
				ab(i) = b1(1,0)*b2(1,0);
			}
		} 
	}
	return ab;
}
