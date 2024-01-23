# Structure

!= Mirar build-ins

1. Inicializar estructura --> msh

2. Bucle inf de comandos hasta 'exit'
	- Leer los comandos y guardarlos en la estructura
		- Mirar que las comillas esten bien puestas (" && ')

		- Expandir las variable --> $HOME = /Users/...

		- Guardar el comando
		- Guardar las flags
		- Guardar los infiles
		- Guardar los outfiles

	- Paso intermedio
		- Abrir los infiles useless
		- Abrir los outfiles useless

	- Ejecutor
		- Mirar si es built-in
			- Si sí que es, ejecutarlo
			- Sino, pipex

	- Liberar memoria
		- Liberar toda la reserva de memoria

3. Liberar toda la memoria

# TAREAS
- [] Parseo<br>
	- [] Mirar que esten bien las comillas
	- [] Expandir las variables del input
		- tener en cuenta las comillas si esta dentro de comillas simples no expande
		- 
- [] Built-ins



No hay nada abierto ->			     Se interpreta ->     /Users…
Hay comillas dobles abiertas->    Se interpreta ->      /Users/…
Hay comillas simples abiertas -> No se interpreta -> $PATH