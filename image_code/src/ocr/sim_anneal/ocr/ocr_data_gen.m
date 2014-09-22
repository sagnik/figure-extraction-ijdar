function [c]=ocr_data_gen(w,l,ll);

%to generate data for OCR; 
%w = image *gif or binarized data(all resolved, matrix like)
%l = normalization factor (eg., 0.95)
%ll = anything; ifdef w is binarized, not gif input

if nargin < 3

%read  data; need imread

[a b]=imread(w);

[c d]=size(a);

% convert to 2 bits, with threshold val
  % determined from colormap 

  [a]=binarize(a);
else
a=w;

end


%use any to determine non-zero regions

ai=any(a');
aj=any(a);

%keyboard;

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

[fn fm]=size(f);
[ffn ffm]=size(ff);
%keyboard;

%generate data using eig, trace

tic
for i=1:fn;
for j=1:ffn;

dd=a(f(i,1):f(i,2),ff(j,1):ff(j,2));


tt=flipud(eig(dd'*dd)/(trace(dd'*dd)^l));

hh((i-1)*3*length(ff)+(j-1)*3+1:(i-1)*3*length(ff)+3*j)=tt(1:3);

end
end
toc


c=reshape(hh,3,length(hh)/3)';



%write data to file

fid=fopen('ocr_data.bin','w');

fwrite(fid,c','double');

fclose(fid);


