function [v,u,y,x]=pop_s(u,x);

%pop element v,y off stacks u,x

  i=length(u);
j=length(x);

if (i==1)||(j==1)

  v=u;
u=0;
y=x;
x=0;

elseif

v=u(1);
u=u(2:i);


y=x(1);
x=x(2:j);

end
