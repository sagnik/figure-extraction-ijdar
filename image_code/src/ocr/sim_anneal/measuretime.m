function [] =  measuretime();
t=cputime;
labelImage('new.gif');
e=cputime-t;
disp(e);
