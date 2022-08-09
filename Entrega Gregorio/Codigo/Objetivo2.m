%% Objetivo 2: Usando redes neuronales

%% Introducción
%
% Durante este apartado voy a diseñar y entrenar varias redes neuronales
% con la finalidad de obtener un modelo lo más parecido posible al real.
% Una vez selecionada la red, obtendré los parametros más optimos para el
% modelos mediante un algoritmo genético.

%% Metodología empleada para entrenar las redes
% Voy a crear 18 modelos distintos, 9 cascadeforward y otros 9 RBF.
% Dispongo de 9 paquetes de datos, formados cada uno por 2 ficheros. Uno de
% los ficheros contiene las entradas del sistema y el otro las salidas del 
% sistema para dichas entradas.
% 
% El método consiste en usar 8 de los 9 paquetes unicamente para entrenar,
% mientras que el paquete restante servirá para la validación del modelo
% entrenado.
%
% Rotando el paquete se evaluación obtenemos los 9 modelos comentados al
% principio, cada uno evaluado con un set distino y entrenados con los
% restantes.

%% Criterio de elección del modelo
%
% De entre los 2 grupos eligiré aquel cuyo error medio sea menor.
% Una vez selecccionado el grupo, eligiré
% aquel modelo cuyo error sea más próximo al error medio del grupo.
% Eligo este criterío para que el modelo final no sea aquel que tenga ni el
% peor ni el mejor rendimiento. Pues lo que más me interesa es que el
% modelo tenga un rendimiento similar al obtenido durante su entrenamiento
% y evaluación.
%
% *Si eligio el modelo con el *peor rendimiento* me aseguraría de que
% el rendimiento de la red en el peor de los casos sería parecido al
% despesempeñado durante el test, pero perdería la oportunidad de usar
% otras redes que funcionan mejor.
%
% *Por el contrario, si eligo la red cuyo desempeño ha sido el más alto
% durante su entrenamiento y su test de validación, me estoy arriesgando a
% que dicha red en realidad no sea tan buena como aparenta. Pues existe la
% posibilidad de que el test de validación era muy parecido a los de
% entrenamiento y por eso ha obtenido muy buen rendimiento. Por lo que existe 
% un posibilidad bastante alta de que si sometemos la red a otras situaciones 
% su rendimiento empeore muchisimo. Lo cual haría su ejecución muy
% impredecible al igual que el caso anterior.
%
% También puede suceder que debido a la estrutura de entrenamiento y testeo
% que estoy aplicando, el test de dicha red ha sido más 'sencillo' que el
% del resto de redes. Lo cual provocaría que la elección del modelo
% estuviera sesgada.
%
% Es por estas razones por las que considero que la mejor opción es elegir
% aquel modelo cuyo rendimiento está en la media del grupo. De esta forma
% reducimos la posibilidad de que el modelo funcione peor de lo esperado, 
% pero también la posibilidad de que funcione mejor.


%% Creo los arreglos donde almcenaré los modelos
%
% Creo los arrays donde voy a almacenar los 18 modelos 

% Modelos=cell(1,9);
% Modelos_RBF=cell(1,9);

%% Creación de los sets de entreno y evaluación 
% Organizo los datos de la forma comentada:
% 2 matrices para el entreno de tamaño 8000x9, una de entrada y la otra de
% salida
%
% Las columnas tienen el siguiente orden:
%
% SetEntrada:
% Entrada2, Entrada3, Entrada4, Entrada5, Entrada1, Entrada3, Entrada4,...
%
% SetSalida:
% Salida2, Salida3, Salida4, Salida5, Salida1, Salida3, Salida4,...
%
% Mientras que las matrices de validacion siguen este orden:
%
% Entrada1, Entrada2, Entrada3,...
% Salida1, Salida2, Salida3,...
%
% De esta forma entreno con 8 de los 9 ficheros y testeo con el restante

% SetEntrada=[];
% SetSalida=[];
% ValidacionEntrada=[];
% ValidacionSalida=[];
% Errores_test=zeros(1,9);
% Errores_Entrenamiento=zeros(1,9);
% Errores_RBF=zeros(1,9);
% Performance_Entrenamiento=zeros(1,9);
% Performance_Test=zeros(1,9);

% % El iterador i lo uso para especificar el set de validacion y el resto de
% % sets serán los de entrenamiento
% % Ejemplo:
% %
% % i=4->SetValidacion=4;SetEntreno=1,2,3,5,6,7,8,9

% for i=1:9
%     i;
%     
%     %Cargo los datos de valizacion en una matriz
%     miniSetEntrada=[];
%     miniSetSalida=[];
%     [ValidacionEntrada,ValidacionSalida]=ActualizaDatos(ValidacionEntrada,ValidacionSalida,i,1);
%     switch i
%         case 1
%             for j=2:9
%                 j;
%                 [miniSetEntrada,miniSetSalida]=ActualizaDatos(miniSetEntrada, miniSetSalida,j,0);
%             end
%         otherwise
%             for j=1:i-1
%                 j;
%                 [miniSetEntrada,miniSetSalida]=ActualizaDatos(miniSetEntrada, miniSetSalida,j,0);
%             end
%             for j=i+1:9
%                 j;
%                 [miniSetEntrada,miniSetSalida]=ActualizaDatos(miniSetEntrada, miniSetSalida,j,0);
%             
%             end    
%     end
%     SetSalida=[SetSalida,miniSetSalida];
%     SetEntrada=[SetEntrada,miniSetEntrada];
%     
% end
% SetEntrada;
% SetSalida;
% ValidacionSalida;
% ValidacionEntrada;


%% ANN: red neuronal cascadeforward, perceptrón multicapa

%% Configuracion:

% A base de ir probando e ir modificando parametros he llegado a esta
% configuración. 

% NeuronasPorCapa=[20,50,20];
% for i=1:9
%     
%     MiNet=cascadeforwardnet(NeuronasPorCapa);
%     MiNet.divideParam.trainRatio=1;
%     MiNet.divideFcn = 'dividerand';
%     MiNet.trainParam.max_fail=20;
%     MiNet.trainParam.epochs=100;
%     MiNet.performFcn='mse';                     %MSE->Mean square error
%     MiNet.trainParam.goal=1e-5;                 %Objetivo performance
%     MiNet.trainParam.showWindow=false;

%% Funciones de activacion de cada capa

%     MiNet.layers{1}.transferFcn='tansig';
%     MiNet.layers{2}.transferFcn='tansig';
%     MiNet.layers{3}.transferFcn='tansig';

%% Entreno de los 9 modelos cascadeforward  

%     % Saco los datos de entrenamiento ordenados anteriormente
%     DatosEntrada=SetEntrada(:,i);
%     DatosSalida=SetSalida(:,i);
%     % Entrenamiento
%     [MiNet,InfoEntreno,SalidaEstimada,Error]=train(MiNet,DatosEntrada',DatosSalida');
%     
%     % Tenemos dos formar de medir el desempeño durante el entrenamiento:
%     
%     % *Con la función performance que nos da el error cuadrático medio entre
%     % la salida estimada y la real
%     
%     % *Con el parametro error que devuelve el entrenamiento
%     
%     Errores_Entrenamiento(:,i)=mean(Error');
%     % Error caudrático medio
%     Perform_Entreno=perform(MiNet,DatosSalida',SalidaEstimada');
%     Performance_Entrenamiento(:,i)=Perform_Entreno;
%     Modelos{i}=MiNet;
% end
% Performance_Entrenamiento
% Errores_Entrenamiento

%% Test de los 9 modelos cascadeforward

% for i=1:9
%     
%     MiNet=Modelos{i};
%     DatosEntrada=ValidacionEntrada(:,i);
%     DatosSalida=ValidacionSalida(:,i);
%     SalidaEstimada=MiNet(DatosEntrada');
%     
%     % Calculo el error de de la salida estimada respecto a la salida de
%     % validacion
%     
%     Errores_test(:,i)=mean(abs(SalidaEstimada'-DatosSalida));
%     Perform_test=perform (MiNet,DatosSalida',SalidaEstimada');%Error cuadratico medio
%     Performance_Test(:,i)=Perform_test;
%     
%     sgtitle('Test de todos los modelos CascadeForward') 
%     subplot(3,3,i),plot([1:1000],DatosEntrada,[1:1000],SalidaEstimada,[1:1000],DatosSalida)
%     title(['Evaluacion',int2str(i)],['Performance: ',num2str(Perform_test)])
%     legend({'DatosEntrada','SalidaEstimada','DatosSalida'},'Location','southwest')
%     
% end
% 
% Performance_Test


%% Calculo el error medio de cada modelo:

% Errores_test

%% Red RBF: Radia Basis Funtion Network
%
% Una vez creados los 9 modelos cascadeforward, creo los 9 modelos restantes
% usando una red tipo RBF(Radio Funtion network).
%
% La función newbr irá aumentado la cantidad de neuronas en las capas
% ocultas hasta alacanzar el error establecido como meta. El problema que
% me ha surgido con este modelo reside en que la red por muchas neuronas
% que meta, el error no baja de 6.01, por lo que pondré como meta un error
% cuadrático medio de 6.015. Dicho rendimiento es alcanzado entre las 50 Y 0
% neuronas en la capa oculta.

%% Configuración

% ObjetivoError=6.015;
% SpreadCte=1;

%% Creo las 9 redes RBF

% for i=1:9
%     DatosEntrada=SetEntrada(:,i);
%     DatosSalida=SetSalida(:,i);
%     MiNetRBF=newrb(DatosEntrada',DatosSalida',ObjetivoError,SpreadCte);
%     Modelos_RBF{i}=MiNetRBF;
% end

%% Testeo de las 9 redes

% for i=1:9
%     MiNetRBF=Modelos_RBF{i};
%     DatosEntrada=ValidacionEntrada(:,i);
%     DatosSalida=ValidacionSalida(:,i);
%     SalidaEstimadaRBF=MiNetRBF(DatosEntrada');
%     Errores_RBF(:,i)=mean(abs(SalidaEstimadaRBF'-DatosSalida));
%     sgtitle('Test de todos los modelos Radia Basis'); 
%     subplot(3,3,i),plot([1:1000],DatosEntrada,[1:1000],SalidaEstimadaRBF,[1:1000],DatosSalida)
%     title(['Evaluacion',int2str(i)],['Performance: ',num2str(Errores_RBF(:,i))])
%     legend({'DatosEntrada','SalidaEstimada','DatosSalida'},'Location','southwest')
% end
% Errores_RBF
% media_errores_RBF=mean(Errores_RBF')


%% Conclusiones del entrenamiento de los modelos neuronales
%
% Como se puede ver, el resultado de las redes RBF es significativamente
% mejor que el de las redes en cascasda, por lo que selecionaré una de estas
% como modelo del sulfitador.
% Siguiendo con la metodología explicada al principio del informe, eligiré
% el modelo cuyo desempeño está más cercano a la media la cual vemos que
% es: 2.19 aprox
%
% Por lo que el modelo que más se ajusta es el modelo 8. Esto lo podemos
% ver en la figura que contiene el resultado de test de cada uno de los
% modelos.
%
% Sin embargo, el error medio en todos los modelos es bastante grande y
% podemos decir que el comporamiento de estos en general es muy malo.
% Sospecho que se debe a la falta de datos de entrenamiento, de modo que si
% este fuera el problema y no se pudiera disponer de más sets, se podrían
% obtener más mezclando sets.
%
% Aún así, he probado a entrenar las redes variando muchos parametos y el
% desempeño apenas mejoraba. Incluyendo la posibilidad de que entrenar una
% red con un único set durante 500 epocas y haciendo la validación con ese 
% mismo set de entrenamiento. 
%
% Sin embargo el modelo no mejoraba apenas, lo cual me daba a enteder que
% el problema puede radicar en que este tipo de red no es adecuada para
% simular este tipo de comportamientos. No obstante, creo que este no es 
% el problema, sino  que radica en la manera en la que introduzco los valores de los
% sets durante los entrenamientos, haciendo así incapaz a la red
% de mejorar.
%
% Yo introduzco los datos de entrada y salida como columnas de 8000x1, la
% concantenzación de los sets. Sin embargo, al introducir los valores de esta forma
% la red solo es capaz de asociar el valor instantaneo de la entrada con el
% valor instantaneo de la salida. De modo que no es capaz de seguir la
% dinámica oscilatoria de muchos sets. Para que pudiera seguirla deberiamos
% introducir todos los valores a la vez. De esta forma la red podría
% conocer los valores anteriores y siguientes de cada instante e identificar
% las diferentes dinámicas.
%
% A pesar de que esa fuera la solución, desconozco la forma de implementar
% en simulink una red con 1000 entradas en el sistema dado en clase.

%% Algoritmo Genético
%
% Una vez que tenemos el modelo del sulfitudor obtenido mediante redes
% neuronales. Pasamos a obtener los valores más adecuados para las Ke,Kd y Ku.
% Para ello se usará un algoritmo genético y se estudiarán los resultados
% para los dos modelos.
%
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

%% Funciones Fitness
%
% Como ya he comentado antes, es la misma función que la usada en el
% Objetivo 1. Quiero usar la misma para que la optimización sea la misma
% entre los dos objetivos y que la comparación de resultados no este
% sesgada.

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
% Final=1000;
% t=(1:Final);
% U(t)=[ones(1,Final/4)*7,ones(1,Final/4)*5,ones(1,Final/4)*9,ones(1,Final/4)*6];
% Input=[t',U'];
% [t,x,y]=sim('sulfitadornn.slx',t,opt,Input);
% 
% % Evaluacion; Para ver la evolucion de las Ks a lo largo de la optimización
% Error=abs(mean(U'-y));
% Solucion(end+1,1)=Ke;
% Solucion(end,2)=Kd;
% Solucion(end,3)=Ku;
% Solucion(end,4)=Error;
% end

%% Resultados del AG:

% Para el modelo de la red neuronal obtuve los siguientes resultados:
% Ke=8.4587; Kd=1.7984; Ku=2.3936 
% En las fotos del directorio 'Imagenes_Objetivo2' podemos observar como el 
% algortimo va convergiendo hacia los valores
% optimos.Las imagenes de los resultados los puedes encontrar con los
% nombres AG_Ke, AG_Ku y AG_Kd.

% Ke:
% plot(Solucion(:,1))
% title('Ke')
% Kd:
% plot(Solucion(:,2))
% title('Kd')
% Ku:
% plot(Solucion(:,3))
% title('Ku')

%% Prueba con el modelo neuronal
%
% Al igual que para el otro objetivo, probamos varias entradas sobre el modelo neuronal y vemos su 
% resultado con las Ks obtenidas por el AG.
% 
% Para poder simular la red neuronal en simulink hay que romper el lazo
% algebriaco que se produce por la realimentación del lazo. La solución que
% he encontrado ha sido añadir el bloque Unit Delay. A groso modo lo que
% hace es implementar un retardo usando un tiempo de muestreo discreto
% especificado por el usuario.
% Ke=8.4587;
% Kd=1.7984;
% Ku=2.3936;

% Ke=X(1)
% Kd=X(2)
% Ku=X(3)
%% Entrada Escalón simple

% Simula(2,1,t,Final);

%% Secuencia de entradas escalón

% Simula(2,2,t,Final);

%% Entrada oscilatoria

% Simula(2,3,t,Final);
%% Conclusiones 
%
% Mientras que el resultado del objetivo 1 es muy bueno,
% el comportamiento de la red se comporta extremadamente mal. No es capaz
% de seguir el SetPoint en ninguno de los 3 casos.
%
% Era predecible su horrible comportamiento, pues el entrenamiento de la red ha sido
% muy malo.
%
% Si se hubiera logrado hacer que la red aprendiera de forma correcta,
% habría sido una opción más interesante que la de crear un modelo en
% simulink del sulfitador, pues para crear el modelo de la red solo hace
% falta tener datos de entrada y salida con los que entrenar el modelo.
%
% Mientras que para crear el gemelo digitial del sulfitador tendríamos que
% profundizar en su funcionamiento y las ecuaciones que lo rigen.
%
% Luego, lo mejor siempre será tener un modelo digital de la planta, pero
% en caso de tener que construirlo, la mejor opción será crear un modelo
% basado en redes neuronales.

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
% end

%% Funcion usada para preparar los sets

% function [SetEntrada,SetSalida]=ActualizaDatos(SetEntrada, SetSalida,j,tipo)
% 
%     filenameInPut=sprintf('Ph%d_input2022.mat',j);
%     filenameOutPut=sprintf('Ph%d_OutPut2022.mat',j);
%     DatosLeidosInput=load(filenameInPut);
%     DatosEntrada=[DatosLeidosInput.Dt.Data];
%     
%     %Creamos el set de entrada
%     if tipo==0
%         SetEntrada=[SetEntrada;DatosEntrada];
%     else
%         SetEntrada=[SetEntrada,DatosEntrada];
%     end
%     
%     DatosLeidosOutput=load(filenameOutPut);
%     DatosSalida=[DatosLeidosOutput.ans.Data];
%     %trunco la matriz a 1000
%     DatosSalida=DatosSalida(1:1000,1);
%     
%     %Creamos el set de salida
%     if tipo==0
%         SetSalida= [SetSalida;DatosSalida];
%     else
%         SetSalida= [SetSalida,DatosSalida];
%     end
%     
% end
















