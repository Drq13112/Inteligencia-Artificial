clear all
close all

Paso=0.1;
Final=1000;
t=[1:Final];
U(t)=ones(1,Final)*5;
Input=[t',U'];

SulfitadorMandani2022=readfis("P1_Bisector.fis");

%open('sulfitador.slx');

[t,x,y]=sim('sulfitador',t,[],Input);

hold on
plot(x)
plot(y)
