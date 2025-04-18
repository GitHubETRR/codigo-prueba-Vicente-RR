Algoritmo TP_Diagramas_de_flujo
	// Saluda al usuario y le pregunta cómo expresa los ángulos
	tipo_de_angulo <- bienvenida()
	Repetir
		// Pregunta qué operación quiere realizar, cada una siendo su punto respectivo del TP
		operacion <- consultar_operacion()
		// Actúa en función de la operación indicada
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
		Escribir 'Si deseas hacer otro pasaje u operación, enviá 1'
		// Repite el algoritmo en caso de ser deseado
		Leer repite
	Mientras Que repite==1
FinAlgoritmo

Funcion tipo_de_angulo = bienvenida()
	Repetir
		Escribir 'Bienvenido a la calculadora de números complejos. ¿Usás radianes (1) o grados (2)?'
		Leer tipo_de_angulo
	Mientras Que tipo_de_angulo<>1 Y tipo_de_angulo<>2
FinFuncion

Funcion operacion = consultar_operacion()
	Repetir
		Escribir '¿Querés pasar de binómica a polar (1), de polar a binómica (2), sumar complejos (3), calcular los componentes que forman una impedancia (4) o calcular los componentes según el voltaje y la intensidad (5)?'
		Leer operacion
	Mientras Que operacion<>1 Y operacion<>2 Y operacion<>3 Y operacion<>4 Y operacion<>5
FinFuncion

Funcion binomica_a_polar(tipo_de_angulo)
	// Pregunta al usuario las componentes de su número complejo en forma cartesiana
	a <- consultar_a()
	b <- consultar_b()
	// Calcula las componentes del complejo en forma polar
	modulo <- binomica_modulo(a,b)
	angulo <- binomica_angulo(a,b,tipo_de_angulo)
	// Escribe el resultado
	escribir_polar(modulo,angulo,tipo_de_angulo)
FinFuncion

Funcion polar_a_binomica(tipo_de_angulo)
	// Pregunta el módulo y ángulo del número complejo
	modulo <- consultar_modulo()
	angulo <- consultar_angulo()
	// Calcula las componentes cartesianas
	a <- polar_a(modulo,angulo,tipo_de_angulo)
	b <- polar_b(modulo,angulo,tipo_de_angulo)
	// Escribe el resultado
	escribir_binomica(a,b)
FinFuncion

Funcion sumar_complejos(tipo_de_angulo)
	// Pregunta la cantidad de números complejos a sumar
	cantidad_suma <- consultar_suma()
	// Establece las componentes cartesianas del resultado en 0, para luego empezar a sumarles
	a_suma <- 0
	b_suma <- 0
	// Repite el proceso de suma todas las veces que haya sido indicado
	Para contador<-1 Hasta cantidad_suma Hacer
		// Pregunta si el complejo que se va a introducir está en forma binómica o polar
		forma_complejo <- consultar_forma_complejo(contador)
		Si forma_complejo==1 Entonces
			// En caso de que esté en forma binómica, únicamente consulta sus componentes
			a <- consultar_a()
			b <- consultar_b()
		SiNo
			// Si está en forma polar, consulta su módulo y ángulo
			modulo <- consultar_modulo()
			angulo <- consultar_angulo()
			// Y los pasa a forma binómica
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
	// Le da valores de 0 a la capacitancia y la inductancia para evitar un error en el programa por enviar un dato vacío
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
	// Pregunta todos los datos iniciales necesarios (módulo y ángulo de los fasores de tensión y corriente y la velocidad angular/frecuencia)
	modulo_V <- consultar_modulo_V()
	angulo_V <- consultar_angulo_V()
	modulo_I <- consultar_modulo_I()
	angulo_I <- consultar_angulo_I()
	w <- consultar_w()
	// Verifica si hay voltaje o corriente 0 antes de calcular los valores de los componentes, porque en esos casos el circuito está abierto o es un corto
	Si modulo_V==0 O modulo_I==0 Entonces
		circuito_sin_componentes(modulo_V,modulo_I)
	SiNo
		// Calcula el módulo y el ángulo de la impedancia como la razón entre el voltaje y la corriente
		modulo_Z <- modulo_V/modulo_I
		angulo_Z <- angulo_V-angulo_I
		// Calcula la parte real (resistencia) y la imaginaria (reactancia) de la impedancia pasándola a forma binómica
		R <- polar_a(modulo_Z,angulo_Z,tipo_de_angulo)
		X <- polar_b(modulo_Z,angulo_Z,tipo_de_angulo)
		// Le da valores de 0 a la capacitancia y la inductancia para evitar un error en el programa por enviar un dato vacío
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
	Escribir 'Siendo tu número complejo a + b*j'
	Escribir '¿Cuánto vale a?'
	Leer a
FinFuncion

Funcion b = consultar_b()
	// Pregunta la parte imaginaria
	Escribir '¿Cuánto vale b?'
	Leer b
FinFuncion

Funcion modulo = binomica_modulo(a,b)
	// Calcula el módulo por el teorema de pitágoras
	modulo <- Raiz(a^2+b^2)
FinFuncion

Funcion angulo = binomica_angulo (a,b,tipo_de_angulo)
	// Calcula el ángulo a partir según las componentes cartesianas
	angulo <- atan(b/a)
	// En caso de tener la parte real o imaginaria negativa, suma el ángulo necesario para que el resultado esté en formato de 0°-360°  O  0R - 2piR
	Si a<0 Entonces
		angulo <- angulo+pi
	SiNo
		Si b<0 Entonces
			angulo <- angulo+2*pi
		FinSi
	FinSi
	// Si el usuario usa grados, pasa el ángulo de radianes a grados
	Si tipo_de_angulo==2 Entonces
		angulo <- angulo*180/pi
	FinSi
FinFuncion

Funcion escribir_polar(modulo,angulo,tipo_de_angulo)
	// Escribe el módulo del número complejo
	Escribir 'Módulo: ',modulo
	// Escribe el ángulo con la unidad preferida del usuario
	Si tipo_de_angulo==1 Entonces
		Escribir 'Ángulo: ',angulo,'R'
		Escribir 'Tu número complejo en forma polar es: ',modulo,' * e^(',angulo,'R * j)'
	SiNo
		Escribir 'Ángulo: ',angulo,'°'
		Escribir 'Tu número complejo en forma polar es: ',modulo,' * e^(',angulo,'° * j)'
	FinSi
FinFuncion

Funcion modulo = consultar_modulo()
	Escribir '¿Cuál es el módulo de tu número complejo?'
	Leer modulo
FinFuncion

Funcion angulo = consultar_angulo()
	Escribir '¿Cuál es el ángulo de tu número complejo?'
	Leer angulo
FinFuncion

Funcion a = polar_a(modulo,angulo,tipo_de_angulo)
	// Calcula la parte real, pasando el ángulo a radianes antes en caso de que esté en grados
	Si tipo_de_angulo==1 Entonces
		a <- modulo*cos(angulo)
	SiNo
		a <- modulo*cos(angulo/180*pi)
	FinSi
FinFuncion

Funcion b = polar_b(modulo,angulo,tipo_de_angulo)
	// Calcula la parte imaginaria, pasando el ángulo a radianes antes en caso de que esté en grados
	Si tipo_de_angulo==1 Entonces
		b <- modulo*sen(angulo)
	SiNo
		b <- modulo*sen(angulo/180*pi)
	FinSi
FinFuncion

Funcion escribir_binomica(a,b)
	Escribir 'Parte real: ',a
	Escribir 'Parte imaginaria: ',b
	Escribir 'Tu número complejo es: ',a,' + j*',b
FinFuncion

Funcion cantidad_suma = consultar_suma()
	Repetir
		Escribir '¿Cuántos números complejos vas a sumar?'
		Leer cantidad_suma
		// En caso de que se quiera sumar menos de dos números, pide introducir la cantidad nuevamente
		Si cantidad_suma<2 Entonces
			Escribir 'No se puede sumar menos de dos números'
		FinSi
	Mientras Que cantidad_suma<2
FinFuncion

Funcion forma_complejo = consultar_forma_complejo(contador)
	Repetir
		Escribir 'El ',contador,'° número complejo:'
		Escribir '¿Está expresado en forma binómica (1) o polar (2)?'
		Leer forma_complejo
	Mientras Que forma_complejo<>1 Y forma_complejo<>2
FinFuncion

Funcion resultado_suma(a,b,tipo_de_angulo)
	// Pregunta al usuario de qué forma quiere ver el resultado
	Repetir
		Escribir '¿Deseas expresar el resultado en forma binómica (1) o polar (2)?'
		Leer forma_complejo
	Mientras Que forma_complejo<>1 Y forma_complejo<>2
	Si forma_complejo==1 Entonces
		// En caso de que quiera verlo en forma binómica, escribe el resultado directamente
		escribir_binomica(a,b)
	SiNo
		// En caso de que quiera verlo en forma polar, calcula el módulo y ángulo
		modulo <- binomica_modulo(a,b)
		angulo <- binomica_angulo(a,b,tipo_de_angulo)
		// Escribe el resultado en forma polar
		escribir_polar(modulo,angulo,tipo_de_angulo)
	FinSi
FinFuncion

Funcion R = consultar_R()
	Escribir 'Siendo tu impedancia R + J*X'
	Escribir '¿Cuánto vale R (resistencia)?'
	Leer R
FinFuncion

Funcion X = consultar_X()
	Escribir '¿Cuánto vale X (reactancia)?'
	Leer X
FinFuncion

Funcion w = consultar_w()
	// Pregunta al en qué unidad expresa la frecuencia
	Repetir
		Escribir '¿La frecuencia del circuito está expresada en hertz (1) o en radianes/segundos (2)?'
		Leer unidad
	Mientras Que unidad<>1 Y unidad<>2
	// Pregunta el valor de la frecuencia
	Escribir '¿Cuál es la frecuencia?'
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
	Escribir '¿Cuál es el módulo del fasor de tensión (valor eficaz en volts)?'
	Leer modulo_V
FinFuncion

Funcion angulo_V = consultar_angulo_V()
	Escribir '¿Cuál es el ángulo del fasor de tensión?'
	Leer angulo_V
FinFuncion

Funcion modulo_I = consultar_modulo_I()
	Escribir '¿Cuál es el módulo del fasor de corriente (valor eficaz en amperes)?'
	Leer modulo_I
FinFuncion

Funcion angulo_I = consultar_angulo_I()
	Escribir '¿Cuál es el ángulo del fasor de corriente?'
	Leer angulo_I
FinFuncion

Funcion circuito_sin_componentes(modulo_V,modulo_I)
	Si modulo_V == 0 Entonces
		Si modulo_I == 0 Entonces
			Escribir 'No hay circuito.'
		SiNo
			// Si la tensión es 0 y hay corriente, 0/I = 0 = Z; hay un corto
			Escribir 'La impedancia es 0. Hay un corto-circuito.'
		FinSi
	SiNo
		// Si hay tensión sin corriente, hay un circuito abierto
		Escribir 'La impedancia es infinita. Hay un circuito abierto.'
	FinSi
FinFuncion

Funcion escribir_impedancia(R,X)
	Escribir 'Parte real: ',R
	Escribir 'Parte imaginaria: ',X
	Escribir 'Tu circuito tiene una impedancia de ',R,' + J*',X
FinFuncion
