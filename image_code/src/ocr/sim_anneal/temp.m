function [x] = temp(w)


%do pattern recog on 2d plot WJB 05/06, 06/06, 07/06, 12/06

%read  data

[a b]=imread(w);

[c d]=size(a);

% convert to 2 bits, with threshold val
% determined from colormap

  [a]=binarize(a);
%imwrite('binarized.gif',a);
label=zeros(c,d);
x=1;
y=1;


%locate axes/tics;

sa=sum(a);
%disp('sa:');
%disp(sa);
imwrite('sa.gif', sa);
[ii si]=max(sa(1:floor(d/2)));
[ii sj]=min(sa(floor(d/2)+1:d));

sb=sum(a');
%imwrite('sb.gif',sb);
[ii ti]=min(sb(1:floor(c/2)));
[ii tj]=max(sb(floor(c/2)+1:c));

ax=[tj+floor(c/2), si; ti,si; tj+floor(c/2), sj+floor(d/2); ti, sj+floor(d/2)];
%disp('ax:');
%disp(ax);

da=a(ax(2,1):ax(3,1),ax(2,2):ax(3,2));
imwrite('da.gif',da);
%disp('da:');
%disp(da);
%get legend region
region_legend=a(1:tj+floor(c/2)-5,si+5:d);
imwrite('region1.gif',region_legend);
intensity_distribution_alongx=sum(region_legend);
intensity_distribution_alongy=sum(region_legend');
[ii max_x]=max(intensity_distribution_alongx);
[ii max_y]=max(intensity_distribution_alongy);
region_legend1=a(max_y:tj+floor(c/2)-5,max_x+5:d);
imwrite('region2.gif',region_legend1);
intensity_distribution_alongx=sum(region_legend);
intensity_distribution_alongy=sum(region_legend');
[ii max_xx]=max(intensity_distribution_alongx);
[ii max_yy]=max(intensity_distribution_alongy);
region_legend=a(max_y:max_yy,max_x:max_xx);
imwrite('region.gif',region_legend);

