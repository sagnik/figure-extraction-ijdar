function [c,h,g]=table_gen(w,l,ii);

%to generate training data for OCR; 
%w = image set *gif (all resolved, matrix like)
%l = normalization factor (eg., 0.95)
%ii; if 1 or 2 return ascii dec code with characters


%read  data; need imread

[a b]=imread(w);

[c d]=size(a);

% convert to 2 bits, with threshold val
  % determined from colormap 

  [a]=binarize(a);

%use any to determine non-zero regions

ai=any(a');
aj=any(a);


%determine regions of intell, i, by detecting state change 0/1 & 1/0

k=1;
for i=2:length(ai)

if ((ai(i)==1)&&(ai(i-1)==0))||((ai(i-1)==1)&&(ai(i)==0))

f(k)=i;
k++;
end

end



%determine regions of intell, j

k=1;
for i=2:length(aj)

if ((aj(i)==1)&&(aj(i-1)==0))||((aj(i-1)==1)&&(aj(i)==0))

ff(k)=i;
k++;

end

end

%keyboard;

f=reshape(f,2,length(f)/2)';
ff=reshape(ff,2,length(ff)/2)';

%generate training table using eig, trace

tic
for i=1:length(f);
for j=1:length(ff);

dd=a(f(i,1):f(i,2),ff(j,1):ff(j,2));


tt=flipud(eig(dd'*dd)/(trace(dd'*dd)^l));

hh((i-1)*3*length(ff)+(j-1)*3+1:(i-1)*3*length(ff)+3*j)=tt(1:3);

end
end
toc


c=reshape(hh,3,length(hh)/3)';


%relate to ascii caps if ii==1
%formatted to train FANN

if ii==1

for i=1:26
for j=1:6

h((i-1)*6+j,:)=[c((i-1)*6+j,:)];
g((i-1)*6+j,:)    =dec_to_bin(64+i);
end
end

end

%relate to ascii lowercase if ii==2

if ii==2

for i=1:26
for j=1:6

h((i-1)*6+j,:)=[c((i-1)*6+j,:)];
g((i-1)*6+j,:)=dec_to_bin(95+i);

end
end

end

%write input/output pairs

fid=fopen('train.txt','w');
fdisp(fid,[length(h) 3 8]);

for i=1:length(h)
fdisp(fid,h(i,:));
fdisp(fid,g(i,:));
end

fclose(fid);


