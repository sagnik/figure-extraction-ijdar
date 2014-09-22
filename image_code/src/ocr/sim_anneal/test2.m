function [cost]=test2(f,w,v);

%generate cost function for simulated anneal
%wjb 06/06-06/07

ef=zeros(size(f));

[m n]=size(w);



a=binarize(imread('a.gif'));

b=binarize(imread('b.gif'));

[g,h]=size(a);
[s,t]=size(b);

for i=1:m/2

k=w(2*i-1,1);
l=w(2*i-1,2);

kk=w(2*i,1);
ll=w(2*i,2);


ef(k:k+g-1,l:l+h-1)=ef(k:k+g-1,l:l+h-1)|(a*v(i));
ef(kk:kk+s-1,ll:ll+t-1)=ef(kk:kk+s-1,ll:ll+t-1)|(b*v(i));

end

cost=sum(sum((f-ef).^2));



