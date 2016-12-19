#include <Rcpp.h> 
using namespace Rcpp;




// [[Rcpp::export]]
int valSearch(const NumericVector& vals, const NumericVector& order,int val,bool low) {
    int start=0;
    int end=order.size()-1;
    int out;

    while(true) {
       int mid=(start+end)/2;

        if(val > vals[order[mid]-1]) {
            start = mid+1;
        }
        else if(val < vals[order[mid]-1]) {
            end=mid-1;

        } else  {
            out=mid;
        }
        if(start>end) {
            if(low) {
                out=end;
            }          
            else
                out=start;
            break;
        }
     }
    if(out<0) {
        return 1;
    }
    if(out>order.size()){
         return out;
    }
    return(out+1);

}

//


// [[Rcpp::export]]
List searchvalsL(const NumericVector& vals
        ,const NumericVector& order
        ,const double val, const double tol) {
    int min = valSearch(vals,order,val*(1-tol),true);
    int max = valSearch(vals,order,val*(1+tol),false);
    List x;
    x["a"]=min;
    x["b"]=max;
    //return std::pair<int,int>(min,max);
    return(x);
}


// [[Rcpp::export]]
std::set<int> searchVals(const NumericVector& vals
        ,const NumericVector& order
        ,const double val, const double tol,int maxValues) {
    int min = valSearch(vals,order,val*(1-tol),true);
    int max = valSearch(vals,order,val*(1+tol),false);

    int count=max-min+1;
    if(count > maxValues) {
        int extra = (count-maxValues)/2;
        min=min+extra;
        max=max-extra;
    }
    
    const NumericVector::const_iterator it1 = order.begin() + (min-1);
    const NumericVector::const_iterator it2 = order.begin() + (max-1);
    
    return std::set<int>(it1,it2);
}



/*
  input a,b
*/

// [[Rcpp::export]]
void searchMe(const DataFrame& a,const DataFrame& b,List tolerances,List namemapping) {
  std::set<int> matchedPos;
  std::pair<int,int> minmax;
  
  NumericVector&& vals = a["a1"];
  NumericVector&& order = a["a1.order"];


}


