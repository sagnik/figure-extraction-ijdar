function [] = labelImage(w);

%do pattern recog on 2d plot WJB 05/06, 06/06, 07/06, 12/06
   
%read  data

[a b]=imread(w);
[c d]=size(a);

% convert to 2 bits, with threshold val
% determined from colormap  

  [a]=binarize(a);

label=zeros(c,d);

x=1;
y=1;

%locate axes/tics; 

sa=sum(a);%row matrix for binarized image (Sum along the coloums for X axis )
%disp(sa);
%find the maximum value of the first half of row vector 
%obtained from adding all the row vectors
[ii si]=max(sa(1:floor(d/2)));
%disp(d);
%disp(si);
%disp(ii);
[ii sj]=max(sa(floor(d/2)+1:d));
%disp(sj);
%disp(ii);

%For along the Y axis.

sb=sum(a');
%disp(sb);
[ii ti]=max(sb(1:floor(c/2)));
[ii tj]=max(sb(floor(c/2)+1:c));

% find the top left area of plot containing the curve
ax=[tj+floor(c/2), si; ti,si; tj+floor(c/2), sj+floor(d/2); ti, sj+floor(d/2)];
%disp(ax);
%disp(ax(2,1));
da=a(ax(2,1):ax(3,1),ax(2,2):ax(3,2));

%get tic frequency; y axis
ii=1;
sx(ii)=0;

for i=ti:tj+floor(c/2)% MOve along Y axis from start of axis line to end
for j=si-5:si+5

sx(ii)=sx(ii)+a(i,j);

end
%disp(sx);
sx=[sx, 1];
%disp(sx);
ii++;
end

sx=fliplr(sx);

sx=sx(1:round(0.8*length(sx)));

sx=sx-sum(sx)./length(sx);

sxf=abs(fft(sx,round(8*length(sx))));

[ii jj]=max(sxf(1:round(length(sxf/2))));

fsx=round((length(sxf)-1)/(jj-1))+2;


%get tic frequency; x axis

ii=1;
sy(ii)=0;
for j=si:sj+floor(d/2)
for i=(tj+floor(c/2)-5):(tj+floor(c/2)+5)


sy(ii)=sy(ii)+a(i,j);

end
sy=[sy, 1];
ii++;
end

sy=sy(1:round(0.8*length(sy)));
keyboard;
sy=sy-sum(sy)./length(sy);

syf=abs(fft(sy,round(8*length(sy))));

[ii jj]=max(syf(1:round(length(syf/2))));

fsy=round((length(syf)-1)/(jj-1))+2;
keyboard;
%examine x text area

bx=a(tj+floor(c/2):c,si:sj+floor(d/2));


%use 'any' to determine non-zero regions

ai=any(bx');
aj=any(bx);

%determine regions of intell, i, by detecting state change 0/1 & 1/0

k=1;
for i=2:length(ai)

if ((ai(i)==1)&&(ai(i-1)==0))||((ai(i-1)==1)&&(ai(i)==0))

f(k)=i;
k++;
end

end

%determine regions of intell, j

%k=1;
%for i=2:length(aj)

%if ((aj(i)==1)&&(aj(i-1)==0))||((aj(i-1)==1)&&(aj(i)==0))

%ff(k)=i;
%k++;
%end

%end

f=[1 f];

f=reshape(f,2,length(f)/2)';
 
%ff=reshape(ff,2,length(ff)/2)';


%pull out data points

for i=1:length(f);

aa((1:length(f(i,1):f(i,2))),:)=bx(f(i,1):f(i,2),:);

k++;
end
end
dda=da;
dda2=da;

[M N]=size(da);

%filter lines from field; size/shape of pixel region should be tuned
%automatically, this is canned as of 12/06
%this is w/o relaxing around tick regions

%fudge factor
			    ff=1;

for i=1:M
for j=1:N


if ((i>ff)&(i<M-ff)&(j>ff)&(j<N-ff))

  if ((da(i,j)==1)&((da(i-ff,j)==0)||(da(i+ff,j)==0))||((da(i,j-ff)==0)||(da(i,j+ff)==0)))
    dda(i,j)=0;
end
end
end
end

%this is with relaxed filtering around tick regions

%line fudge factor
			    ff=1;
%tick fudge factor
fg=5;

for i=1:M
for j=1:N
 
  if ((i>ff)&(i<M-ff)&(j>ff)&(j<N-ff)&(!((mod(j,fsy)<fg)||(mod(j,fsy)>(fsy-fg)))))

  if ((da(i,j)==1)&((da(i-ff,j)==0)||(da(i+ff,j)==0))||((da(i,j-ff)==0)||(da(i,j+ff)==0)))
    dda2(i,j)=0;
end
end
end
end




%these are CCL steps; use in conjunction with sim anneal/supervised net to get x,y 

lab=1;
freq=1;
% main loop(s)

for i=2:c
  for j=2:d

  if !((label(i,j)>0) || (a(i,j)==0))

  [x,y]=push_s(i,x,j,y);


label(i,j)=lab;

while (!(x==0) && !(y==0))

  [i,x,j,y]=pop_s(x,y);



 if (a(i-1,j-1)==1 && label(i-1,j-1)==0)

    [x,y]=push_s(i-1,x,j-1,y);
  label(i-1,j-1)=lab;
freq(lab)++;
end


 if (a(i-1,j)==1) && (label(i-1,j)==0)

   [x,y]=push_s(i-1,x,j,y);
  label(i-1,j)=lab;
freq(lab)++;
end  

if (a(i-1,j+1)==1) && (label(i-1,j+1)==0)

    [x,y]=push_s(i-1,x,j+1,y);
  label(i-1,j+1)=lab;
freq(lab)++;
end

  if (a(i,j-1)==1) && (label(i,j-1)==0)

    [x,y]=push_s(i,x,j-1,y);
  label(i,j-1)=lab;
freq(lab)++;
end

  if (a(i,j+1)==1) && (label(i,j+1)==0)

    [x,y]=push_s(i,x,j+1,y);
  label(i,j+1)=lab;
freq(lab)++;
end

  if (a(i+1,j-1)==1) && (label(i+1,j-1)==0)

    [x,y]=push_s(i+1,x,j-1,y);
  label(i+1,j-1)=lab;
freq(lab)++;
end

  if (a(i+1,j)==1) && (label(i+1,j)==0)

    [x,y]=push_s(i+1,x,j,y);
  label(i+1,j)=lab;
freq(lab)++;
end

  if (a(i+1,j+1)==1) && (label(i+1,j+1)==0)

    [x,y]=push_s(i+1,x,j+1,y);
  label(i+1,j+1)=lab;
freq(lab)++;
end 

end %endwhile

lab++; 
freq=[freq, 1];

end %endif


end
end


% this part for segregating points; higher freq. from CCL == points
% of interest


[h g]=sort(freq);

x=1:length(freq);

for i=1:length(freq);

hh(i)=x(g(i));

end

hh=fliplr(hh);
h=fliplr(h);
i1=1;
i2=1;
i3=1;
i4=1;
i5=1;


for i=1:c
  for j=1:d

  if round(label(i,j))==round(hh(1))

    l1(i1,:)=[i,j];
i1++;
  elseif round(label(i,j))==round(hh(2))

    l2(i2,:)=[i,j];
i2++;
 elseif round(label(i,j))==round(hh(3))

    l3(i3,:)=[i,j];
i3++;
 elseif round(label(i,j))==round(hh(4))

    l4(i4,:)=[i,j];
i4++;
 elseif round(label(i,j))==round(hh(5))

    l5(i5,:)=[i,j];
i5++;
end
end
end


 %keyboard;
