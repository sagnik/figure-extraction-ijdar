function [a]=binarize(b);

%make predominant number white (0), remainder black (1)

  [m n]=size(b);

%256 possible color in map

bb=1:256;

for i=1:m

  [c(i,:) d]=hist(b(i,:),bb);

end


  c=sum(c);

[i j]=max(c);

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



