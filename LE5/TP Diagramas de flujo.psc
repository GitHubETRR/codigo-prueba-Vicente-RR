Algoritmo TP_Diagramas_de_flujo
	// Saluda al usuario y le pregunta c�mo expresa los �ngulos
	tipo_de_angulo <- bienvenida()
	Repetir
		// Pregunta qu� operaci�n quiere realizar, cada una siendo su punto respectivo del TP
		operacion <- consultar_operacion()
		// Act�a en funci�n de la operaci�n indicada
		Segun operacion  Hacer
			1:
				binomica_a_polar(tipo_de_angulo)
			2:
				polar_a_binomica(tipo_de_angulo)
			3:
				sumar_complejos(tipo_de_angulo)
			4:
				impedancia_a_componentes()
			5:
				voltaje_intensidad_a_componentes(tipo_de_angulo)
			De Otro Modo:
				// Es imposible
		FinSegun
		Escribir 'Si deseas hacer otro pasaje u operaci�n, envi� 1'
		// Repite el algoritmo en caso de ser deseado
		Leer repite
	Mientras Que repite==1
FinAlgoritmo

Funcion tipo_de_angulo = bienvenida()
	Repetir
		Escribir 'Bienvenido a la calculadora de n�meros complejos. �Us�s radianes (1) o grados (2)?'
		Leer tipo_de_angulo
	Mientras Que tipo_de_angulo<>1 Y tipo_de_angulo<>2
FinFuncion

Funcion operacion = consultar_operacion()
	Repetir
		Escribir '�Quer�s pasar de bin�mica a polar (1), de polar a bin�mica (2), sumar complejos (3), calcular los componentes que forman una impedancia (4) o calcular los componentes seg�n el voltaje y la intensidad (5)?'
		Leer operacion
	Mientras Que operacion<>1 Y operacion<>2 Y operacion<>3 Y operacion<>4 Y operacion<>5
FinFuncion

Funcion binomica_a_polar(tipo_de_angulo)
	// Pregunta al usuario las componentes de su n�mero complejo en forma cartesiana
	a <- consultar_a()
	b <- consultar_b()
	// Calcula las componentes del complejo en forma polar
	modulo <- binomica_modulo(a,b)
	angulo <- binomica_angulo(a,b,tipo_de_angulo)
	// Escribe el resultado
	escribir_polar(modulo,angulo,tipo_de_angulo)
FinFuncion

Funcion polar_a_binomica(tipo_de_angulo)
	// Pregunta el m�dulo y �ngulo del n�mero complejo
	modulo <- consultar_modulo()
	angulo <- consultar_angulo()
	// Calcula las componentes cartesianas
	a <- polar_a(modulo,angulo,tipo_de_angulo)
	b <- polar_b(modulo,angulo,tipo_de_angulo)
	// Escribe el resultado
	escribir_binomica(a,b)
FinFuncion

Funcion sumar_complejos(tipo_de_angulo)
	// Pregunta la cantidad de n�meros complejos a sumar
	cantidad_suma <- consultar_suma()
	// Establece las componentes cartesianas del resultado en 0, para luego empezar a sumarles
	a_suma <- 0
	b_suma <- 0
	// Repite el proceso de suma todas las veces que haya sido indicado
	Para contador<-1 Hasta cantidad_suma Hacer
		// Pregunta si el complejo que se va a introducir est� en forma bin�mica o polar
		forma_complejo <- consultar_forma_complejo(contador)
		Si forma_complejo==1 Entonces
			// En caso de que est� en forma bin�mica, �nicamente consulta sus componentes
			a <- consultar_a()
			b <- consultar_b()
		SiNo
			// Si est� en forma polar, consulta su m�dulo y �ngulo
			modulo <- consultar_modulo()
			angulo <- consultar_angulo()
			// Y los pasa a forma bin�mica
			a <- polar_a(modulo,angulo,tipo_de_angulo)
			b <- polar_b(modulo,angulo,tipo_de_angulo)
		FinSi
		// Agrega las componentes cartesianas al resultado de la suma
		a_suma <- a+a_suma
		b_suma <- b+b_suma
	FinPara
	// Escribe el resultado
	resultado_suma(a_suma,b_suma,tipo_de_angulo)
FinFuncion

Funcion impedancia_a_componentes()
	// Pregunta la parte real (resistencia) y la parte imaginaria (reactancia) de la impedancia
	R <- consultar_R()
	X <- consultar_X()
	w <- consultar_w()
	// Le da valores de 0 a la capacitancia y la inductancia para evitar un error en el programa por enviar un dato vac�o
	C <- 0
	L <- 0
	Si X>0 Entonces
		// Si la reactancia es positiva, se trata de un inductor, por lo que calcula la inductancia
		L <- inductancia(X,w)
	SiNo
		Si X<0 Entonces
			// Si la reactancia es negativa, se trata de un capacitor, por lo que calcula la capacitancia
			C <- capacitancia(X,w)
		SiNo
			// En este caso, la reactancia es 0, por lo que no hay inductor ni capacitor
		FinSi
	FinSi
	// Escribe los componentes que hay en el circuito
	lista_componentes(R,L,C)
FinFuncion

Funcion voltaje_intensidad_a_componentes(tipo_de_angulo)
	// Pregunta todos los datos iniciales necesarios (m�dulo y �ngulo de los fasores de tensi�n y corriente y la velocidad angular/frecuencia)
	modulo_V <- consultar_modulo_V()
	angulo_V <- consultar_angulo_V()
	modulo_I <- consultar_modulo_I()
	angulo_I <- consultar_angulo_I()
	w <- consultar_w()
	// Verifica si hay voltaje o corriente 0 antes de calcular los valores de los componentes, porque en esos casos el circuito est� abierto o es un corto
	Si modulo_V==0 O modulo_I==0 Entonces
		circuito_sin_componentes(modulo_V,modulo_I)
	SiNo
		// Calcula el m�dulo y el �ngulo de la impedancia como la raz�n entre el voltaje y la corriente
		modulo_Z <- modulo_V/modulo_I
		angulo_Z <- angulo_V-angulo_I
		// Calcula la parte real (resistencia) y la imaginaria (reactancia) de la impedancia pas�ndola a forma bin�mica
		R <- polar_a(modulo_Z,angulo_Z,tipo_de_angulo)
		X <- polar_b(modulo_Z,angulo_Z,tipo_de_angulo)
		// Le da valores de 0 a la capacitancia y la inductancia para evitar un error en el programa por enviar un dato vac�o
		C <- 0
		L <- 0
		Si X>0 Entonces
			// Si la reactancia es positiva, se trata de un inductor, por lo que calcula la inductancia
			L <- inductancia(X,w)
		SiNo
			Si X<0 Entonces
				// Si la reactancia es negativa, se trata de un capacitor, por lo que calcula la capacitancia
				C <- capacitancia(X,w)
			SiNo
				// En este caso, la reactancia es 0, por lo que no hay inductor ni capacitor
			FinSi
		FinSi
		// Escribe el resultado de la impedancia en forma cartesiana
		escribir_impedancia(R,X)
		// Escribe los componentes que hay en el circuito
		lista_componentes(R,L,C)
	FinSi
FinFuncion

Funcion a = consultar_a()
	// Pregunta la parte real
	Escribir 'Siendo tu n�mero complejo a + b*j'
	Escribir '�Cu�nto vale a?'
	Leer a
FinFuncion

Funcion b = consultar_b()
	// Pregunta la parte imaginaria
	Escribir '�Cu�nto vale b?'
	Leer b
FinFuncion

Funcion modulo = binomica_modulo(a,b)
	// Calcula el m�dulo por el teorema de pit�goras
	modulo <- Raiz(a^2+b^2)
FinFuncion

Funcion angulo = binomica_angulo (a,b,tipo_de_angulo)
	// Calcula el �ngulo a partir seg�n las componentes cartesianas
	angulo <- atan(b/a)
	// En caso de tener la parte real o imaginaria negativa, suma el �ngulo necesario para que el resultado est� en formato de 0�-360�  O  0R - 2piR
	Si a<0 Entonces
		angulo <- angulo+pi
	SiNo
		Si b<0 Entonces
			angulo <- angulo+2*pi
		FinSi
	FinSi
	// Si el usuario usa grados, pasa el �ngulo de radianes a grados
	Si tipo_de_angulo==2 Entonces
		angulo <- angulo*180/pi
	FinSi
FinFuncion

Funcion escribir_polar(modulo,angulo,tipo_de_angulo)
	// Escribe el m�dulo del n�mero complejo
	Escribir 'M�dulo: ',modulo
	// Escribe el �ngulo con la unidad preferida del usuario
	Si tipo_de_angulo==1 Entonces
		Escribir '�ngulo: ',angulo,'R'
		Escribir 'Tu n�mero complejo en forma polar es: ',modulo,' * e^(',angulo,'R * j)'
	SiNo
		Escribir '�ngulo: ',angulo,'�'
		Escribir 'Tu n�mero complejo en forma polar es: ',modulo,' * e^(',angulo,'� * j)'
	FinSi
FinFuncion

Funcion modulo = consultar_modulo()
	Escribir '�Cu�l es el m�dulo de tu n�mero complejo?'
	Leer modulo
FinFuncion

Funcion angulo = consultar_angulo()
	Escribir '�Cu�l es el �ngulo de tu n�mero complejo?'
	Leer angulo
FinFuncion

Funcion a = polar_a(modulo,angulo,tipo_de_angulo)
	// Calcula la parte real, pasando el �ngulo a radianes antes en caso de que est� en grados
	Si tipo_de_angulo==1 Entonces
		a <- modulo*cos(angulo)
	SiNo
		a <- modulo*cos(angulo/180*pi)
	FinSi
FinFuncion

Funcion b = polar_b(modulo,angulo,tipo_de_angulo)
	// Calcula la parte imaginaria, pasando el �ngulo a radianes antes en caso de que est� en grados
	Si tipo_de_angulo==1 Entonces
		b <- modulo*sen(angulo)
	SiNo
		b <- modulo*sen(angulo/180*pi)
	FinSi
FinFuncion

Funcion escribir_binomica(a,b)
	Escribir 'Parte real: ',a
	Escribir 'Parte imaginaria: ',b
	Escribir 'Tu n�mero complejo es: ',a,' + j*',b
FinFuncion

Funcion cantidad_suma = consultar_suma()
	Repetir
		Escribir '�Cu�ntos n�meros complejos vas a sumar?'
		Leer cantidad_suma
		// En caso de que se quiera sumar menos de dos n�meros, pide introducir la cantidad nuevamente
		Si cantidad_suma<2 Entonces
			Escribir 'No se puede sumar menos de dos n�meros'
		FinSi
	Mientras Que cantidad_suma<2
FinFuncion

Funcion forma_complejo = consultar_forma_complejo(contador)
	Repetir
		Escribir 'El ',contador,'� n�mero complejo:'
		Escribir '�Est� expresado en forma bin�mica (1) o polar (2)?'
		Leer forma_complejo
	Mientras Que forma_complejo<>1 Y forma_complejo<>2
FinFuncion

Funcion resultado_suma(a,b,tipo_de_angulo)
	// Pregunta al usuario de qu� forma quiere ver el resultado
	Repetir
		Escribir '�Deseas expresar el resultado en forma bin�mica (1) o polar (2)?'
		Leer forma_complejo
	Mientras Que forma_complejo<>1 Y forma_complejo<>2
	Si forma_complejo==1 Entonces
		// En caso de que quiera verlo en forma bin�mica, escribe el resultado directamente
		escribir_binomica(a,b)
	SiNo
		// En caso de que quiera verlo en forma polar, calcula el m�dulo y �ngulo
		modulo <- binomica_modulo(a,b)
		angulo <- binomica_angulo(a,b,tipo_de_angulo)
		// Escribe el resultado en forma polar
		escribir_polar(modulo,angulo,tipo_de_angulo)
	FinSi
FinFuncion

Funcion R = consultar_R()
	Escribir 'Siendo tu impedancia R + J*X'
	Escribir '�Cu�nto vale R (resistencia)?'
	Leer R
FinFuncion

Funcion X = consultar_X()
	Escribir '�Cu�nto vale X (reactancia)?'
	Leer X
FinFuncion

Funcion w = consultar_w()
	// Pregunta al en qu� unidad expresa la frecuencia
	Repetir
		Escribir '�La frecuencia del circuito est� expresada en hertz (1) o en radianes/segundos (2)?'
		Leer unidad
	Mientras Que unidad<>1 Y unidad<>2
	// Pregunta el valor de la frecuencia
	Escribir '�Cu�l es la frecuencia?'
	Leer w
	// En caso de estar en hertz, pasa la frecuencia a radianes/segundos
	Si unidad=1 Entonces
		w <- w*2*pi
	FinSi
FinFuncion

Funcion L = inductancia(X,w)
	L <- X/w
FinFuncion

Funcion C = capacitancia(X,w)
	C <- -1/w/X
FinFuncion

Funcion lista_componentes(R,L,C)
	Escribir 'Tu circuito'
	// Escribe el valor de la resistencia, o que no hay en caso de que sea 0
	Si R<>0 Entonces
		Escribir 'Tiene una resistencia de ',R,' ohms'
	SiNo
		Escribir 'No tiene resistencia'
	FinSi
	Si L<>0 Entonces
		// Escribe el valor del inductor, en caso de que haya
		Escribir 'Tiene un inductor de ',L,'H'
	SiNo
		Si C<>0 Entonces
			// Escribe el valor del capacitor, en caso de que haya
			Escribir 'Tiene un capacitor de ',C,'F'
		SiNo
			Escribir 'No tiene inductor ni capacitor'
		FinSi
	FinSi
FinFuncion

Funcion modulo_V = consultar_modulo_V()
	Escribir '�Cu�l es el m�dulo del fasor de tensi�n (valor eficaz en volts)?'
	Leer modulo_V
FinFuncion

Funcion angulo_V = consultar_angulo_V()
	Escribir '�Cu�l es el �ngulo del fasor de tensi�n?'
	Leer angulo_V
FinFuncion

Funcion modulo_I = consultar_modulo_I()
	Escribir '�Cu�l es el m�dulo del fasor de corriente (valor eficaz en amperes)?'
	Leer modulo_I
FinFuncion

Funcion angulo_I = consultar_angulo_I()
	Escribir '�Cu�l es el �ngulo del fasor de corriente?'
	Leer angulo_I
FinFuncion

Funcion circuito_sin_componentes(modulo_V,modulo_I)
	Si modulo_V == 0 Entonces
		Si modulo_I == 0 Entonces
			Escribir 'No hay circuito.'
		SiNo
			// Si la tensi�n es 0 y hay corriente, 0/I = 0 = Z; hay un corto
			Escribir 'La impedancia es 0. Hay un corto-circuito.'
		FinSi
	SiNo
		// Si hay tensi�n sin corriente, hay un circuito abierto
		Escribir 'La impedancia es infinita. Hay un circuito abierto.'
	FinSi
FinFuncion

Funcion escribir_impedancia(R,X)
	Escribir 'Parte real: ',R
	Escribir 'Parte imaginaria: ',X
	Escribir 'Tu circuito tiene una impedancia de ',R,' + J*',X
FinFuncion
