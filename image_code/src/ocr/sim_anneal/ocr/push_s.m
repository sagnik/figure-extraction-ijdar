function [u,x]=push_s(v,u,y,x);

% push an element v,y onto  stacks u,x
  


i=length(u);

j=length(x);

if (i==1)||(j==1)

  u=v;
x=y;

elseif

uu(1)=v;
uu(2:i+1)=u;

u=uu;

xx(1)=y;
xx(2:j+1)=x;

x=xx;

end
