%% Objetivo 1
%% Introducción
% Utilizando el modelo del sulfitador aportado por el profesor, optimizar la estructura de control
% medainte los parametros Ke,Kd,Ku. Para ello se usará un algoritmo
% genético acompañado de la función objetivofitness. Una vez optimizados
% los parametros Ks, se ejecutarán 3 pruebas con las que eveluaré el
% funcionamiento de la estructura optimizada.

%% Algoritmo genético
% La variable global solución es utilizada para muestrear los valores que
% van tomando las Ks despues de cada iteración. Esta idea la tomé de mi
% compañero Ángel Padilla, pues a el también le pasaba que muchas veces el
% algoritmo tardaba mucho más del tiempo limite impuesto. De esta forma si
% introducimos el comando Ctrl+C cortamos el proceso y podemos ver los
% valores que ha ido almacenando.

% global SulfitadorMamdani2022;
% 
% global Solucion;
% global MiNet;
% 
% Solucion=[];
% 
% Modelos=load('Modelos.mat');
% MiNet=Modelos.Modelos{1,5};
% 
% SulfitadorMamdani2022=readfis("P1.fis");
% NParametrosSintonizar=3;
% 
% % Defino unos margenes algo amplios para no quedarme en 'mínimos locales'
% 
% lb=[0 0 0];%low bound -> limite inferior
% ub=[20 20 20];%limite superior -> limite superior  
% 
% rng default;
% 
% funOBJ=@Funcion_FitnessObjetivo;
% 
% % Indico al algoritmo el tiempo maximo y el tamaño de la poblacion, de esta
% % forma puedo limitar su ejecución y obtener los resultados que ha hecho,
% % de lo contrario necesitaria un computador mucho más potente y más tiempo
% % para ejecutar el algoritmo.
% 
% time=3600*4;% Para las simulaciones he usado tiempos de 3 a 4h
% population=20;
% options=gaoptimset('TimeLimit',time,'PopulationSize',population);
% 
% %Esta linea esta comentada, pero no tendría que estarlo pues es la qeu ejecuta el algoritmo. 
% [X,EVAL,EXITFLAG,OUTPUT,POPULATION,Scores]=ga(funOBJ,NParametrosSintonizar,[],[],[],[],lb,ub,[],[],options);

%% Funcion Fitness Objetivo
% Como se puede ver esta función genera como error el
% valor medio de los errores a lo largo de toda la iteración.
% Para la simulación decidí usar un input de varios escalones seguidos para que el
% algortimo ajustara mejor los parametros K y no se quedera siempre en el
% mismo punto de trabajo.

% function Error = Funcion_FitnessObjetivo(K)
% 
% global SulfitadorMamdani2022;
% global Solucion;
% global MiNet;
% 
% opt=simset('SrcWorkspace','Current');
% warning off
% 
% %Simulacion del sistema
% Ke=K(1);
% Kd=K(2);
% Ku=K(3);
% 
% 
% Final=1000;
% t=(1:Final);
% U(t)=[ones(1,Final/4)*7,ones(1,Final/4)*5,ones(1,Final/4)*9,ones(1,Final/4)*6];
% Input=[t',U'];
% [t,x,y]=sim('sulfitador.slx',t,opt,Input);
% 
% % Evaluacion; Para ver la evolucion de las Ks a lo largo de la optimización
% Error=abs(mean(U'-y));
% Solucion(end+1,1)=Ke;
% Solucion(end,2)=Kd;
% Solucion(end,3)=Ku;
% Solucion(end,4)=Error;
% end

%% Resultados del AG
% El algoritmo solo ha sido capaz de generar 40 iteraciones en el tiempo
% establecido. Por lo que no se puede apreciar muy bien la evolución del
% sistema. Escojo los valores que mejor rendimiento me han dado. 
% El rendimiento es valor medio de los errores en cada instante de la
% simulación.
%
% Para la fase de determinación de las Ks mediante el algoritmo he usado un
% input de varios escalones, de esta forma trato de ajustar los parametros
% para varios puntos de trabajo y escalones de diferentes magnitudes.
% % Siendo el resultado final: Ke=8.4352; Kd=0.6889; Ku=11.7054 
% Las imagenes de los resultados los puedes encontrar en el directorio
% imaagnes 'Imagenes_Objetivo1' con los nombres AG_Ke,AG_Ku y AG_Kd

% Ke:
% plot(Solucion(:,1))
% title('Ke')

% Kd:
% plot(Solucion(:,2))
% title('Kd')

% Kd:
% plot(Solucion(:,3))
% title('Ku')


%% Prueba de la optimizacion
% Realizo la prueba para el primer caso, con el modelo aportado en clase
% del sulfitador. Se insertan los valores optimos hayados por el algoritmo
% genético y simulo para varias entradas.
%
% Ke=8.4352; 
% Kd=0.6889; 
% Ku=11.7054;

% Ke=X(1);
% Kd=X(2);
% Ku=X(3);
% 
% SulfitadorMamdani2022=readfis("P1.fis");
% Final=1000;
% t=(1:Final);

% Entrada Escalón simple

% Simula(1,1,t,Final);

% Secuencia de entradas escalón

% Simula(1,2,t,Final);

% Entrada oscilatoria

% Simula(1,3,t,Final);


%% Conclusiones
% Como se puede ver, el control final en el sistema con el modelo del
% sulfitador es bastante rápido. Sin embargo genera un esfuerzo de control
% demasiado fuerte en mi opinion. Teniendo en algunas ocasiones un
% sobrepico excesivo. Lo cual es lógico de acuerdo a la función fitness definida,
% pues busca el error medio más pequeño a lo largo de la simulación.
%
% Si queremos reducir ese sobre pico habría que reducir el valor de Ku pues
% está actuando como ganancia del regulador. También se podría aumentar el
% los Kd y Ke los cuales amortiguarian la respuesta. Probando algunas
% combinaciones de Ks llegue a esta: Ke=18.2675; Kd=16.8926; Ku=8.63912

% Ke=18.2675;
% Kd=16.9826;
% Ku=8.63912;

% Entrada Escalón simple

% Simula(1,1,t,Final);

% Secuencia de entradas escalón

% Simula(1,2,t,Final);

% Entrada oscilatoria

% Simula(1,3,t,Final);

% Se puede observar su resultado en las imagenes del directorio
% 'imagenes_objetivo2' bajo los nombres onda_modelo2, escalon_modelo2 y
% escalones_modelo2.


%% Funcion usada para probar el modelo

% function Simula(tipo_red,entrada,t,Final)
% switch entrada
%     case 1
%         U(t)=ones(1,Final)*6;
%     case 2
%         U(t)=[ones(1,Final/4)*6,ones(1,Final/4)*8.25,ones(1,Final/4)*5.5,ones(1,Final/4)*6.3];
%     case 3
%         U(t)=sin(t*0.01)+6;
% end
% Input=[t',U'];
% switch tipo_red
%     case 1
%         [a,b,y]=sim('sulfitador.slx',t,[],Input);
%         error_medio=abs(mean(U'-y))
%         figure('Name','Evaluacion modelo simulink');
%         plot(t,U,'-',t,y,'--');
%     case 2
%         
%         [a,b,y]=sim('sulfitadornn.slx',t,[],Input);
%         error_medio=abs(mean(U'-y))
%         figure('Name','Evaluacion modelo simulink');
%         plot(t,U,'-',t,y,'--');
% end
% 
