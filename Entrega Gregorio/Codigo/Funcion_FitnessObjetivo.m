function Error = Funcion_FitnessObjetivo(K)

global SulfitadorMamdani2022;
global Solucion;
global MiNet;

opt=simset('SrcWorkspace','Current');
warning off

%Simulacion del sistema
Ke=K(1);
Kd=K(2);
Ku=K(3);

%SetPoint=5;
%step=1;
Final=1000;
t=(1:Final);
%U(t)=ones(1,Final)*SetPoint;
U(t)=[ones(1,Final/4)*7,ones(1,Final/4)*5,ones(1,Final/4)*9,ones(1,Final/4)*6];
Input=[t',U'];
%[t,x,y]=sim('sulfitador.slx',t,opt,Input);
[t,x,y]=sim('sulfitador.slx',t,opt,Input);

% Evaluacion; Para ver la evolucion de las Ks a lo largo de la optimización
Error=abs(mean(U'-y));
Solucion(end+1,1)=Ke;
Solucion(end,2)=Kd;
Solucion(end,3)=Ku;
Solucion(end,4)=Error;
end