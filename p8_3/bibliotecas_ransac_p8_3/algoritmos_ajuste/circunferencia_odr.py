"""Módulo con funciones de estimación ODR para circunferencias."""
import numpy as np
from scipy import odr

# -----------------------------------------------------------------------------------------------
# ODR CIRCUNFERENCIA FORMULACIÓN DISTANCIA GEOMÉTRICA


def distancia_punto_circunferencia(param, x):
    """Distancia de un punto a una circunferencia."""
    return np.sqrt((x[0]-param[0])**2 + (x[1]-param[1])**2) - param[2]


def jac_param_distancia(param, x):
    """Jacobianos de los parámetros de la función de error a minimizar distancia."""
    df_p = np.empty((param.size, x.shape[1]))
    factor = ((x[0]-param[0])**2 + (x[1]-param[1])**2)**0.5
    df_p[0] = -(x[0]-param[0])/factor
    df_p[1] = -(x[1]-param[1])/factor
    df_p[2] = -1.

    return df_p


def jac_var_distancia(param, x):
    """Jacobianos de las variables de la función de error a minimizar distancia."""
    df_x = np.empty_like(x)
    factor = ((x[0]-param[0])**2 + (x[1]-param[1])**2)**0.5
    df_x[0] = (x[0]-param[0])/factor
    df_x[1] = (x[1]-param[1])/factor

    return df_x


def circunferencia_odr_geometrica(puntos, param):
    """Se trata de minimizar el sumatorio de las distancias al cuadrado de los puntos (x,y) a la
    circunferencia de centro (xc,yc) y radio R: distancia(p,circ) = sqrt((x-xc)^2 + (y-yc)^2) - R"""
    num_puntos = puntos.shape[0]

    if num_puntos < 4:
        raise ValueError('Deben proporcionarse al menos cuatro puntos.')

    datos = odr.Data(puntos.T, y=1)  # y=1 -> implicita
    modelo = odr.Model(distancia_punto_circunferencia, implicit=True,
                       fjacd=jac_var_distancia, fjacb=jac_param_distancia)
    circ_odr = odr.ODR(datos, modelo, param)
    circ_odr.set_job(fit_type=1, deriv=3)  # Se usan los jacobianos del usuario sin comprobar

    return circ_odr.run().beta

# -----------------------------------------------------------------------------------------------

# -----------------------------------------------------------------------------------------------
# ODR CIRCUNFERENCIA FORMULACIÓN DISTANCIA ALGEBRAICA


def circunferencia_implicita(param, x):
    """Función de error para la circunferencia implícita."""
    return (x[0]-param[0])**2 + (x[1]-param[1])**2 - param[2]**2


def jac_param_implicita(param, x):
    """Jacobianos de los parámetros de la formulación implícita."""
    df_p = np.empty((param.size, x.shape[1]))
    df_p[0] = 2*(param[0]-x[0])
    df_p[1] = 2*(param[1]-x[1])
    df_p[2] = -2*param[2]

    return df_p


def jac_var_implicita(param, x):
    """Jacobianos de las variables de la formulación implícita."""
    df_x = np.empty_like(x)
    df_x[0] = 2*(x[0]-param[0])
    df_x[1] = 2*(x[1]-param[1])

    return df_x


def circunferencia_odr_algebraica(puntos, param):
    """Se trata de minimizar el sumatorio de los errores algebraicos al cuadrado de los puntos (x,y)
    a la circunferencia de centro (xc,yc) y radio R: error(p, circ) = (x-xc)^2 + (y-yc)^2 - R^2)"""
    num_puntos = puntos.shape[0]

    if num_puntos < 4:
        raise ValueError('Deben proporcionarse al menos cuatro puntos.')

    datos = odr.Data(puntos.T, y=1)  # y=1 -> implicita
    modelo = odr.Model(circunferencia_implicita, implicit=True,
                       fjacd=jac_var_implicita, fjacb=jac_param_implicita)
    circ_odr = odr.ODR(datos, modelo, param)
    circ_odr.set_job(fit_type=1, deriv=3)  # Se usan los jacobianos del usuario sin comprobar

    return circ_odr.run().beta

# -----------------------------------------------------------------------------------------------


if __name__ == '__main__':
    import modelo_geometrico as mod_geom
    import modelo_circunferencia2d as mod_circ
    import figuras_aleatorias as fig_aleat

    circunferencia_rand = fig_aleat.circunferencia2d_en_rectangulo_rand([-100, -100, 100, 100],
                                                                        200, 1., 50.)
    puntos = circunferencia_rand['puntos']

    cx = circunferencia_rand['centro'][0]
    cy = circunferencia_rand['centro'][1]
    print('({:.3f}, {:.3f}), {:.3f}'.format(cx, cy, circunferencia_rand['radio']))

    circ_1_odr = mod_circ.ModeloCircunferencia2d()
    circ_1_odr.ajusta(circunferencia_odr_algebraica, puntos, [0., 0., 50.])
    sum_errores = sum(mod_geom.errores_cuadrado(circ_1_odr, puntos))
    print(circ_1_odr.parametros)
    print('errores odr algebraico:', sum_errores)

    circ_2_odr = mod_circ.ModeloCircunferencia2d()
    circ_2_odr.ajusta(circunferencia_odr_geometrica, puntos, [0., 0., 50.])
    sum_errores = sum(mod_geom.errores_cuadrado(circ_2_odr, puntos))
    print(circ_2_odr.parametros)
    print('errores odr geométrico:', sum_errores)
