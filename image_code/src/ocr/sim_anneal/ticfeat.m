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

