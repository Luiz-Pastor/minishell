# Structure

!= Mirar build-ins

1. Inicializar estructura --> msh

2. Bucle inf de comandos hasta 'exit'
	- Leer los comandos y guardarlos en la estructura
		- Mirar que las comillas esten bien puestas (" && ')

		- Guardar el comando
		- Guardar las flags
		- Guardar los infiles
		- Guardar los outfiles

	- Paso intermedio
		- Abrir los infiles useless
		- Abrir los outfiles useless

	- Ejecutor
		- Mirar si es build-in
			- Si sí que es, ejecutarlo
			- Sino, pipex

	- Liberar memoria
		- Liberar toda la reserva de memoria

3. Liberar toda la memoria
