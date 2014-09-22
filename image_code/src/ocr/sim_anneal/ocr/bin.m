function [a]=bin(im);

%make predominant number white (0), remainder black (1) i.e. mark any feature with black and else (background) white.
b=imread(im);

  [m n]=size(b);

%256 possible color in map

bb=1:256;
%disp(m);
%disp(n);
%disp(b);
for i=1:m

  [c(i,:) d]=hist(b(i,:),bb);%c is a (m, 256) matrix with each row of the b mappes to 256 values of c
  %if(i==2) disp(c(i,:));disp(d);end
end
%disp(c);
%disp(d);
%[inde1 inde2]=size(c);
%disp(inde1);
%disp(inde2);
  c=sum(c);

[i j]=max(c);
disp(i);disp(j);
%make highest frequency number white (0) else black (1)

for k=1:m
  for l=1:n

  if(b(k,l)==j)

    a(k,l)=0;

  else

    a(k,l)=1;

end
end
end
%keyboard;
imwrite(a,'sample.pgm');



