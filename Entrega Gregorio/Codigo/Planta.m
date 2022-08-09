%% Modelo Sulfitador 
% Realizo la prueba para el primer caso, con el modelo aportado en clase
% del sulfitador. Se insertan los valores optimos hayados por el algoritmo
% genético y simulo para varias entradas.

Ke=8.4352; 
Kd=0.6889; 
Ku=11.7054;

SulfitadorMamdani2022=readfis("P1.fis");
Final=1000;
t=(1:Final);

%% Entrada Escalón simple

Simula(1,1,t,Final);
%% Secuencia de entradas escalón

Simula(1,2,t,Final);

%% Entrada oscilatoria

Simula(1,3,t,Final);

%% Prueba con el modelo neuronal

% Al igual que antes, probamos varias entradas sobre el modelo neuronal y vemos su 
% resultado con las Ks obtenidas por el AG.
% 
% Para poder simular la red neuronal en simulink hay que romper el lazo
% algebriaco que se produce por la realimentación del lazo. La solución que
% he encontrado ha sido añadir el bloque Unit Delay. A groso modo lo que
% hace es implementar un retardo usando un tiempo de muestreo discreto
% especificado por el usuario.

Ke=8.4587;
Kd=1.7984;
Ku=2.3936;

%% Entrada Escalón simple
Simula(2,1,t,Final);

%% Secuencia de entradas escalón
Simula(2,2,t,Final);

%% Entrada oscilatoria
Simula(2,3,t,Final);

%% Conclusiones de los resultados 
% Como se puede ver, el control final en el sistema con el modelo del
% sulfitador es bastante rápida. Sin embargo genera un esfuerzo de control
% demasiado fuerte en mi opinion. Teniendo en algunas ocasiones un
% sobrepico excesivo. Lo cual es lógico de acuerdo a la función fitness definida,
% pues busca el error medio más pequeño a lo largo de la simulación.
%
% Si queremos reducir ese sobre pico habría que reducir el valor de Ku pues
% está actuando como ganancia del regulador. También se podría aumentar el
% los Kd y Ke los cuales amortiguarian la respuesta. Probando algunas
% combinaciones de Ks llegue a esta: Ke=18.2675; Kd=16.8926; Ku=8.63912
%%

Ke=18.2675;
Kd=16.9826;
Ku=8.63912;

%% Entrada Escalón simple

Simula(1,1,t,Final);

%% Secuencia de entradas escalón

Simula(1,2,t,Final);

%% Entrada oscilatoria

Simula(1,3,t,Final);

%%
% Sin embargo no podemos decir lo mismo del control con el modelo con 
% redes neuronales. Mientras que el comportamiento del modelo del
% sulfitador, la red se comporta extremadamente mal
%
% Era predecible su comportamiento, pues el entrenamiento de la red ha sido
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

%% funcion

function Simula(tipo_red,entrada,t,Final)
switch entrada
    case 1
        U(t)=ones(1,Final)*6;
    case 2
        U(t)=[ones(1,Final/4)*6,ones(1,Final/4)*8.25,ones(1,Final/4)*5.5,ones(1,Final/4)*6.3];
    case 3
        U(t)=sin(t*0.01)+6;
end
Input=[t',U'];
switch tipo_red
    case 1
        [a,b,y]=sim('sulfitador.slx',t,[],Input);
        error_medio=abs(mean(U'-y))
        figure('Name','Evaluacion modelo simulink');
        plot(t,U,'-',t,y,'--');
    case 2
        
        [a,b,y]=sim('sulfitadornn.slx',t,[],Input);
        error_medio=abs(mean(U'-y))
        figure('Name','Evaluacion modelo simulink');
        plot(t,U,'-',t,y,'--');
end

end

