//#include <Rcpp.h>
//using namespace Rcpp;

/*// [[Rcpp::export]]
NumericVector calculateMeanInR(NumericVector x) {
	Environment base("package:base");
	Function mean_r = base["mean"];
	return mean_r(x);
}

int main() {
	NumericVector data = {1.2, 2.3, 3.4, 4.5, 5.6};

	NumericVector mean = calculateMeanInR(data);

	Rcout << "Mean calculated in R: " << mean << std::endl;

	return 0;
}*/
#define _CRT_USE_C_COMPLEX_H
#include <Rinternals.h>
#include <Rembedded.h>

int main() {
	// Intialize the embedded R environment.
	int r_argc = 2;
	const char* r_argv[] = { "R", "--silent" };
	Rf_initEmbeddedR(r_argc, const_cast<char**>(r_argv));

	return 0;
}