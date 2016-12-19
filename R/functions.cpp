#include <Rcpp.h> 
using namespace Rcpp;




// [[Rcpp::export]]
int valSearch(const NumericVector& vals, const IntegerVector& order,int val,bool low) {
    int start=0;
    int end=order.size()-1;
    int out;

    while(true) {
       // std::cout << start << "<---------->" << end << std::endl;
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
        ,const IntegerVector& order
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
        ,const IntegerVector& order
        ,const double val, const double tol,int maxValues) {
    int sign=1;
    if(val<0)
        sign=-1;
    int min = valSearch(vals,order,sign*val*(1-tol),true);
    int max = valSearch(vals,order,sign*val*(1+tol),false);
    

    int count=max-min+1;
    if(count > maxValues) {
        int extra = (count-maxValues)/2;
        min=min+extra;
        max=max-extra;
    }
    
    const IntegerVector::const_iterator it1 = order.begin() + (min-1);
    const IntegerVector::const_iterator it2 = order.begin() + (max-1);
    
    return std::set<int>(it1,it2);
}



/*
  input a,b
*/

// [[Rcpp::export]]
void searchMe(const DataFrame& a,const DataFrame& b,List tolerances,List namemapping) {
  std::set<int> matchedPos;
  std::pair<int,int> minmax;
  
  std::vector<std::vector<int>> out2;

  StringVector n1 = namemapping.names();
  int inrows=b.nrows();
  for(int rowid=0; rowid<inrows; rowid++) {
      std::cout << "Id : " << rowid << std::endl;
      std::set<int> allmatches;

      bool isfirstcheck=true;
       
      for(String x:n1) {
          //std::cout << "col : " << std::string(x) << std::endl;
          std::string y=x;
          NumericVector&& vals = a[y];
          IntegerVector&& order = a[y+".order"];
          String inname = namemapping[x];
          NumericVector&& valsin = b[inname];
          double searchVal= valsin[rowid];
          double tol = tolerances[x];
          //std::cout << "searchval" << searchVal << std::endl;
          std::set<int> out = searchVals(vals,order,searchVal,tol,500);
          if(isfirstcheck) {
              allmatches=out;
          }
          else {
              std::vector<int> zz;
              std::set_intersection (allmatches.begin(),allmatches.end()
                      , out.begin(), out.end(), std::back_inserter(zz));
              allmatches.clear();
              for(int x:zz) {
                  allmatches.insert(x);
              }
          }
          std::cout << "Size out is " << allmatches.size() << std::endl;
          //std::cout << "done row " << rowid << " for "  << std::string(x) << std::endl;
          isfirstcheck=false;
      }
  }
   

}

//searchMe(a,b,tolerances,namemapping)


