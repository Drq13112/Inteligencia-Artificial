%% Algoritno Genético
% Una vez que tenemos el modelo del sulfitudor obtenido mediante redes
% neuronales y el modelo del sufitudor obtenido proporcionado en la sesión
% 2. Pasamos a obtener los valores más adecuados para las Ke,Kd y Ku.
% Para ello se usará un algoritmo genético y se estudiarán los resultados
% para los dos modelos.
%
% La variable global solución es utilizada para muestrear los valores que
% van tomando las Ks despues de cada iteración. Esta idea la tomé de mi
% compañero Ángel Padilla, pues a el también le pasaba que muchas veces el
% algoritmo tardaba mucho más del tiempo limite impuesto. De esta forma si
% introducimos el comando Ctrl+C cortamos el proceso y podemos ver los
% valores que ha ido almacenando.

global SulfitadorMamdani2022;

global Solucion;
global MiNet;

Solucion=[];

Modelos=load('Modelos.mat');
MiNet=Modelos.Modelos{1,5};

SulfitadorMamdani2022=readfis("P1.fis");
NParametrosSintonizar=3;

% Defino unos margenes algo amplios para no quedarme en 'mínimos locales'

lb=[0 0 0];%low bound -> limite inferior
ub=[20 20 20];%limite superior -> limite superior  

rng default;

funOBJ=@Funcion_FitnessObjetivo;

% Indico al algoritmo el tiempo maximo y el tamaño de la poblacion, de esta
% forma puedo limitar su ejecución y obtener los resultados que ha hecho,
% de lo contrario necesitaria un computador mucho más potente y más tiempo
% para ejecutar el algoritmo.

time=3600*4;% Para las simulaciones he usado tiempos de 3 a 4h
population=20;
options=gaoptimset('TimeLimit',time,'PopulationSize',population);

%Esta linea esta comentada, pero no tendría que estarlo pues es la qeu ejecuta el algoritmo. 
%[X,EVAL,EXITFLAG,OUTPUT,POPULATION,Scores]=ga(funOBJ,NParametrosSintonizar,[],[],[],[],lb,ub,[],[],options);

%% Resultados del AG:
% El algoritmo solo ha sido capaz de generar 40 iteraciones en el tiempo
% establecido. Por lo que no se puede apreciar muy bien la evolución del
% sistema. Escojo los valores que mejor rendimiento me han dado. 
% El rendimiento es valor medio de los errores en cada instante de la
% simulación.
%
% Para la fase de determinación de las Ks mediante el algoritmo he usado un
% input de varios escalones, de esta forma trato de ajustar los parametros
% para varios puntos de trabajo y escalones de diferentes magnitudes.

load('Solucion.mat');
%% Ke:
plot(Solucion(:,1))
title('Ke')

%% Kd:
plot(Solucion(:,2))
title('Kd')

%% Kd:
plot(Solucion(:,3))
title('Ku')

% Siendo el resultado final: Ke=8.4352; Kd=0.6889; Ku=11.7054 

% Para el modelo de la red neuronal obtuve los siguientes resultados:
load('Solucionnn.mat');
% De este podemos observar como los valores van convergiendo hacia el punto
% optimo.

%% Ke:
plot(Solucion(:,1))
title('Ke')

%% Kd:
plot(Solucion(:,2))
title('Kd')

%% Kd:
plot(Solucion(:,3))
title('Ku')

% Siendo el resultado final: Ke=8.4587; Kd=1.7984; Ku=2.3936 