function [out,out2,tt,ef,cff]=sim_anneal(input,e,it);

% master function for image analysis/sim anneal
% inputs
% e=anneal fraction
% it=iterations
%
% outputs
% out=energy; if all is well should decrease :)
% out2=random walks around configuration (i,j) space, where
% i,j are matrix indicies/offsets of sub image within full image
% tt=temperature schedule
% ef=output image
% cff=energy difference; if all is well should be normal/gaussian dist

% WJB 09/06, 05/07

%get sizes of components

[k l]=size(imread('a.gif'));
[m n]=size(imread('b.gif'));

sz=[k l; m n];

%and thus range of values for x-y

 sz=(size(input) - max(sz));
m=sz(1);
n=sz(2);

 
%initial parameters
%index offset (postion of sub image; these are randomly walked

w0=[round(rand(1,6)*(m-1)+1); round(rand(1,6)*(n-1)+1)]';

%weights (1 or 0)

%w1=round(rand(1,6));
w1=ones(1,6);

%temperature

t=test2(input,w0,w1);



%master loop

j=1;
k=1;
p=1;
out(j)=0;


%test2 generates cost; bp is best value, stored for occasional lattice
%resets

bp=test2(input,w0,w1);

for i=1:it

%weight2 random walks sub images 
 
  [wn,wt]=weight2(w0,m,n,w1);

%but don't start pruning until temp is low

if t>20
wt=ones(size(wt));
end


bb=test2(input,w0,w1);
cc=test2(input,wn,wt);

cf=cc-bb;
cff(i)=cf;

%out2 tracks the random walks around configuration (i,j) space
%Euclidean distance -> 0 when weight is 0 (image dropped)

out2(1,k)=(w0(1,1).^2+w0(1,2).^2)*w1(1);
out2(2,k)=(w0(2,1).^2+w0(2,2).^2)*w1(2);
out2(3,k)=(w0(3,1).^2+w0(3,2).^2)*w1(3);
out2(4,k)=(w0(4,1).^2+w0(4,2).^2)*w1(4);
out2(5,k)=(w0(5,1).^2+w0(5,2).^2)*w1(5);
out2(6,k)=(w0(6,1).^2+w0(6,2).^2)*w1(6);

k++;

if cf<0

w0=wn;
w1=wt;
out(j)=cc;
j++;

%MC step

elseif ((rand<exp(-cf/t))&(cf>0))

w0=wn;
w1=wt;
out(j)=cc;
j++;

end

%update best value for occasional lattice reset

if (cc<bp)
  wp=w0;
wpp=w1;
bp=cc; 



end



%reset lattice

if (mod(p,8)==0)&(cc>bp)
  w0=wp;
w1=wpp;
end


%anneal schedule

if (mod(i,16)==0)

t=(1-e)*t;



end
tt(i)=t;
end

% create final image

ef=zeros(size(input));


a=binarize(imread('a.gif'));

b=binarize(imread('b.gif'));

[g,h]=size(a);
[s,t]=size(b);
w=w0;

[m n]=size(w);

for i=1:m/2

k=w(2*i-1,1);
l=w(2*i-1,2);

kk=w(2*i,1);
ll=w(2*i,2);


ef(k:k+g-1,l:l+h-1)=ef(k:k+g-1,l:l+h-1)|(a*w1(i));
ef(kk:kk+s-1,ll:ll+t-1)=ef(kk:kk+s-1,ll:ll+t-1)|(b*w1(i));

end

%done
