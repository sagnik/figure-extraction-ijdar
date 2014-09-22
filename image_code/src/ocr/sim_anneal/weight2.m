function [w,wt]=weight2(q,m,n,qq);


%to update indices q, in matrix r
%diffuse all pieces simultaneously

%also turn pieces off (weight  0 -> 1)
%where similar shapes virtually overlap;
%in this manner the number of underlying 
%subimages is determined

%qq=weights
%q=offsets/positions/index

%wjb 06/07



%initial case only, all weights ==1
if nargin<4

qq=ones(1,length(q));
end



mm=m;

nn=n;

[m n]=size(q);

rn=round(2*rand(1,2*m)-1);

 dq=[rn(1:m); rn(m+1:2*m)]';

%updated positions

w=(q+dq);



%check that images are within bounds
%bool logic

ww= [(mm*ones(m,1)<w(:,1))'; (nn*ones(m,1)<w(:,2))']';


w=!ww.*w+[ww(:,1)*mm, ww(:,2)*nn];

ww=[(ones(m,1)>w(:,1))'; (ones(m,1)>w(:,2))']';

w=!ww.*w+[ww(:,1), ww(:,2)];


%determine whether two images of same type overlap (ie., one is irrelevant 
%and should be removed)

%(fudge factor of e pixels)
e=4;

wt(1)= (!(abs(w(1,1)-w(2,1))<e && abs(w(1,2)-w(2,2))<e) || !(abs(w(1,1)-w(3,1))<e && abs(w(1,2)-w(3,2))<e)) && qq(1);
wt(2)= (!(abs(w(1,1)-w(2,1))<e && abs(w(1,2)-w(2,2))<e) || !(abs(w(2,1)-w(3,1))<e && abs(w(2,2)-w(3,2))<e)) && qq(2);
wt(3)= (!(abs(w(1,1)-w(3,1))<e || abs(w(1,2)-w(3,2))<e) || !(abs(w(3,1)-w(2,1))<e || abs(w(3,2)-w(2,2))<e)) && qq(3);

wt(4)= (!(abs(w(4,1)-w(5,1))<e && abs(w(4,2)-w(5,2))<e) || !(abs(w(4,1)-w(6,1))<e && abs(w(4,2)-w(6,2))<e)) && qq(4);
wt(5)= (!(abs(w(5,1)-w(4,1))<e && abs(w(5,2)-w(4,2))<e) || !(abs(w(5,1)-w(6,1))<e && abs(w(5,2)-w(6,2))<e)) && qq(5);
wt(6)= (!(abs(w(6,1)-w(4,1))<e || abs(w(6,2)-w(4,2))<e) || !(abs(w(6,1)-w(5,1))<e || abs(w(6,2)-w(5,2))<e)) && qq(6);








