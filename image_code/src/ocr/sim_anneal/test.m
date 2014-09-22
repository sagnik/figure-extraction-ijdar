function [d]=test(p,nn);

%to generate test cases for simulated anneal on 
%overlapping images
%
%nn=dimension, > 70 (sub images are ~50x50)
%p=noise percentage
%WJB 06/06-06/07


a=binarize(imread('a.gif'));

b=binarize(imread('b.gif'));

		      d=zeros(nn,nn);

disp(a);

% no. of  sub-images

an=floor(rand*3)

bn=floor(rand*3)

[m n]=size(a);
[k l]=size(b);

for i=1:an


    an_i=floor(rand*(nn-50))+1;
an_j=floor(rand*(nn-50))+1;



d(an_i:an_i+m-1,an_j:an_j+n-1)=(d(an_i:an_i+m-1,an_j:an_j+n-1) | a);

end

for i=1:bn

    bn_i=floor(rand*(nn-50))+1;
bn_j=floor(rand*(nn-50))+1;


d(bn_i:bn_i+k-1,bn_j:bn_j+l-1)=(d(bn_i:bn_i+k-1,bn_j:bn_j+l-1) | b);


end

% noise; p percent chance of bit flip

for i=1:nn
	   for j=1:nn

    if rand < p

	   d(i,j)=!d(i,j);

end

end
end
