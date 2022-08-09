%% Obtención de un modelo mediante redes neuronales

%% Introducción
% Durante este apartado voy a diseñar y entrenar varias redes neuronales
% con la finalidad de obeter un modelo lo más parecido posible al real.

%% Metodología empleada
% Voy a crear 18 modelos distintos, 9 cascadefroward y otros 9 RBF.
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
% su rendimiento empeore muchisimo. Lo cual haría su rendimiento muy
% impredecible al igual que el caso anterior.
%
% También puede suceder que debido a la estrutura de entrenamiento y testeo
% que estoy aplicando, el test de dicha red ha sido más 'sencillo' que el
% del resto de redes.
%
% Es por estas razones por las que considero que la mejor opción es elegir
% aquel modelo cuyo rendimiento está en la media del grupo. De esta forma
% reducimos la posibilidad de que el modelo funcione peor de lo esperado, 
% pero también la posibilidad de que funcione mejor.


%% Creación de los sets de entreno y evaluación
% Creo los arrays donde voy a almacenar los 18 modelos 
Modelos=cell(1,9);
Modelos_RBF=cell(1,9);

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

%De esta forma entreno con 8 de los 9 ficheros y testeo con el restante

SetEntrada=[];
SetSalida=[];
ValidacionEntrada=[];
ValidacionSalida=[];
Errores_test=zeros(1,9);
Errores_Entrenamiento=zeros(1,9);
Errores_RBF=zeros(1,9);
Performance_Entrenamiento=zeros(1,9);
Performance_Test=zeros(1,9);

%El iterador i lo uso para especificar el set de validacion y el resto de
%sets serán los de entrenamiento
%Ejemplo:
%
%i=4->SetValidacion=4;SetEntreno=1,2,3,5,6,7,8,9

for i=1:9
    i;
    
    %Cargo los datos de valizacion en una matriz
    miniSetEntrada=[];
    miniSetSalida=[];
    [ValidacionEntrada,ValidacionSalida]=ActualizaDatos(ValidacionEntrada,ValidacionSalida,i,1);
    switch i
        case 1
            for j=2:9
                j;
                [miniSetEntrada,miniSetSalida]=ActualizaDatos(miniSetEntrada, miniSetSalida,j,0);
            end
        otherwise
            for j=1:i-1
                j;
                [miniSetEntrada,miniSetSalida]=ActualizaDatos(miniSetEntrada, miniSetSalida,j,0);
            end
            for j=i+1:9
                j;
                [miniSetEntrada,miniSetSalida]=ActualizaDatos(miniSetEntrada, miniSetSalida,j,0);
            
            end    
    end
    SetSalida=[SetSalida,miniSetSalida];
    SetEntrada=[SetEntrada,miniSetEntrada];
    
end
SetEntrada;
SetSalida;
ValidacionSalida;
ValidacionEntrada;


%% ANN: red neuronal cascadeforward, perceptrón multicapa

%% Configuracion:
% A base de ir probando e ir modificando parametros he llegado a esta
% configuración. 

% MiNet.divideParam.trainRatio=1;
MiNet.trainParam.epochs=1000;
MiNet.performFcn='mse';               %MSE->Mean square error
%MiNet.trainParam.time=10000;
MiNet.trainParam.goal=0.0001;          %Objetivo performance
MiNet.trainParam.showWindow=false;

NeuronasPorCapa=[20,50,20];%20 50 20
for i=1:9
    MiNet=cascadeforwardnet(NeuronasPorCapa);
    MiNet.divideParam.trainRatio=1;
    MiNet.divideFcn = 'dividerand';
    MiNet.trainParam.max_fail=20;
    MiNet.trainParam.epochs=100;
    MiNet.performFcn='mse';                     %MSE->Mean square error
    MiNet.trainParam.goal=1e-5;                 %Objetivo performance
    MiNet.trainParam.showWindow=false;

%% Funciones de activacion de cada capa
    MiNet.layers{1}.transferFcn='tansig';
    MiNet.layers{2}.transferFcn='tansig';
    MiNet.layers{3}.transferFcn='tansig';

%% Entreno de los 9 modelos cascadeforward  
    % Sacamos los datos de entrenamiento ordenados anteriormente
    DatosEntrada=SetEntrada(:,i);
    DatosSalida=SetSalida(:,i);
    % Entrenamos
    [MiNet,InfoEntreno,SalidaEstimada,Error]=train(MiNet,DatosEntrada',DatosSalida');
    
    % Tenemos dos formar de medir el desempeño durante el entrenamiento:
    
    % *Con la función performance que nos da el error cuadrático medio entre
    % la salida estimada y la real
    
    % *Con el parametro error que devuelve el entrenamiento
    
    Errores_Entrenamiento(:,i)=mean(Error');
    % Error caudrático medio
    Perform_Entreno=perform(MiNet,DatosSalida',SalidaEstimada');
    Performance_Entrenamiento(:,i)=Perform_Entreno;
    Modelos{i}=MiNet;
end
Performance_Entrenamiento;
Errores_Entrenamiento;

%% Test de los 9 modelos cascadeforward

for i=1:9
    
    MiNet=Modelos{i};
    DatosEntrada=ValidacionEntrada(:,i);
    DatosSalida=ValidacionSalida(:,i);
    SalidaEstimada=MiNet(DatosEntrada');
    
    %Calculo el error de de la salida estimada respecto a la salida de
    %validacion
    
    Errores_test(:,i)=mean(abs(SalidaEstimada'-DatosSalida));
    Perform_test=perform (MiNet,DatosSalida',SalidaEstimada');%Error cuadratico medio
    Performance_Test(:,i)=Perform_test;
    
    sgtitle('Test de todos los modelos CascadeForward') 
    subplot(3,3,i),plot([1:1000],DatosEntrada,[1:1000],SalidaEstimada,[1:1000],DatosSalida);
    title(['Evaluacion',int2str(i)],['Performance: ',num2str(Perform_test)]);
    legend({'DatosEntrada','SalidaEstimada','DatosSalida'},'Location','southwest');
    
end

Performance_Test;


% Calculo el error medio de cada modelo:
Errores_test;


%% Red RBF: Radia Basis Funtion Network
%Una vez creados los 9 modelos cascadeforward, creo los 9 modelos restantes
%usando una red tipo RBF(Radio Funtion network).

% La función newbr irá aumentado la cantidad de neuronas en las capas
% ocultas hasta alacanzar el error establecido como meta. El problema que
% me ha surgido con este modelo reside en que la red por muchas neuronas
% que meta, el error no baja de 6.01, por lo que pondré como meta un error
% cuadrático medio de 6.015. Dicho rendimiento es alcanzado entre las 50 Y 0
% neuronas en la capa oculta.

%Configuración
ObjetivoError=6.015;
SpreadCte=1;

%Creamos las 9 redes RBF
for i=1:9
    DatosEntrada=SetEntrada(:,i);
    DatosSalida=SetSalida(:,i);
    MiNetRBF=newrb(DatosEntrada',DatosSalida',ObjetivoError,SpreadCte);
    Modelos_RBF{i}=MiNetRBF;
end

%Testeo de las 9 redes
for i=1:9
    MiNetRBF=Modelos_RBF{i};
    DatosEntrada=ValidacionEntrada(:,i);
    DatosSalida=ValidacionSalida(:,i);
    SalidaEstimadaRBF=MiNetRBF(DatosEntrada');
    Errores_RBF(:,i)=mean(abs(SalidaEstimadaRBF'-DatosSalida));
    sgtitle('Test de todos los modelos Radia Basis'); 
    subplot(3,3,i),plot([1:1000],DatosEntrada,[1:1000],SalidaEstimadaRBF,[1:1000],DatosSalida);
    title(['Evaluacion',int2str(i)],['Performance: ',num2str(Errores_RBF(:,i))]);
    legend({'DatosEntrada','SalidaEstimada','DatosSalida'},'Location','southwest');
end
Errores_RBF;
media_errores_RBF=mean(Errores_RBF');


%% Conclusiones
% Como se puede ver, el resultado de las redes RBF es significativamente
% mejor que el de las redes en cascasda, por lo que selecionaré una de estas
% como modelo del sulfitador.
% Siguiendo con la metodología explicada al principio del informe, eligiré
% el modelo cuyo desempeño está más cercano a la media la cual vemos que
% es: 2.199
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
% el problema, sino  que readica en la manera en la que introduzco los valores de los
% sets durante los entrenamientos, haciendo de esta manera incapaz a la red
% de mejorar.
%
% Yo introduzco los datos de entrada y salida como columnas de 8000x1, la
% concantenzación de los sets. Sin embargo, al introducir los valores de esta forma
% la red solo es capaz de asociar el valor instantaneo de la entrada con el
% valor instantaneo de la entrada. De modo que no es capaz de seguir la
% dinámica oscilatoria de muchos sets. Para que pudiera seguirla deberiamos
% introducir todos los valores a la vez. De esta forma la red podría
% conocer los valores anteriores y siguientes de cada instante e identificar
% las diferentes dinámicas.
%
% A pesar de que esa fuera la solución, desconzco la forma de implementar
% en simulink una red con 1000 entradas en el sistema dado en clase.

function [SetEntrada,SetSalida]=ActualizaDatos(SetEntrada, SetSalida,j,tipo)

    filenameInPut=sprintf('Ph%d_input2022.mat',j);
    filenameOutPut=sprintf('Ph%d_OutPut2022.mat',j);
    DatosLeidosInput=load(filenameInPut);
    DatosEntrada=[DatosLeidosInput.Dt.Data];
    
    %Creamos el set de entrada
    if tipo==0
        SetEntrada=[SetEntrada;DatosEntrada];
    else
        SetEntrada=[SetEntrada,DatosEntrada];
    end
    
    DatosLeidosOutput=load(filenameOutPut);
    DatosSalida=[DatosLeidosOutput.ans.Data];
    %trunco la matriz a 1000
    DatosSalida=DatosSalida(1:1000,1);
    
    %Creamos el set de salida
    if tipo==0
        SetSalida= [SetSalida;DatosSalida];
    else
        SetSalida= [SetSalida,DatosSalida];
    end
    
end