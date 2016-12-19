
require(data.table)
require(Rcpp)
set.seed(0)



a1=runif(1000)*100
a2=rnorm(1000)*100
a3=rnorm(1000)*100
a4=rnorm(1000)*100

#Make sure same number of colums


b1=runif(1000)*100
b2=rnorm(1000)*100
b3=rnorm(1000)*100
b4=rnorm(1000)*100

a=data.table(a1,a2,a3,a4)
b=data.table(b1,b2,b3,b4)

columns_to_be_ordered = colnames(a)

for(cname in columns_to_be_ordered){
    newcname = paste0(cname,'.order');
    a[[newcname]] = order(a[[cname]])
}



#list the tolerance for each column
tolerances = list()
#mapping for reference table cname and input table cname
namemapping = list()

for(cname in columns_to_be_ordered){
    tolerances[[cname]]=0.5
}

namemapping$a1="b1"
namemapping$a2="b2"
namemapping$a3="b3"
namemapping$a4="b4"

sourceCpp('functions.cpp')
