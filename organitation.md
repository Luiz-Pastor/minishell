## **Organizacion del proyecto**
El proyecto se puede dividir esencialmente en dos partes: parseador y ejecutor, a parte de las señales. Antes de ello, sería importante comprobar, por un lado, que el input esté vació; si es este caso, nos podemos omitir el parseo. También es interesante comprobar que las comillas este bien puestas (`cat "archivo`), ya que si falta alguna pdría dar problemas posteriormente. Ante esta situación, hay dos posibilidades:
1. Tratarlo como error y volver a pedir un comando.
2. Pedir al usuario que introduzca más parte del comando, hasta que las comillas estén correctamente.

### **Parseador**
Se encargar de, a través del input del usuario, guardar la información de forma estructurada para ser fácilmente manipulada. Hay que tener en cuenta la posibilidad de que haya varios comandos comunicados por pipes, varios infiles, varios outfiles...

**IMPORTANTE**: aunque se puedan hacer optimizaciones de cara al ejecutor, el parseador solo se debería de encargar de guardar los datos, no debería de mirar si el comando o los archivos existen o se pueden ejecutar, por ejemplo.

Pasos que seguimos:
1. Ya con el input correcto (comillas bien puestas y todo bien localizado), expandimos las variables. Esto es sustituir una cadena de caracteres que se vinculan a una variable del entorno con su valor. Ejemplos:
	- Al hacer `echo $USER`, el valor de `$USER` se sustituye por su valor. Por lo que en realidad `echo $USER` y `echo nombre_usuario` son lo mismo.
	- Al hacer `echo $NOEXISTO`, al no existir en el env se sustituye por un espacio, `echo_`, donde la `_` sería un espacio.
2. Dividir los comandos que se van a ejecutar. Esto es separar los diferentes comando que se comunican mediantes pipes. Ejemplo: si se ejecuta la linea `ls | cat`, se guardaran de forma separada el `ls` y el `cat`.
3. Para cada comando, hay que revisar todos los campos que puede poseer. Estos son:
	- **Comando principal**: es el comando que se va a ejecutar. Es el primer argumento de la linea introducida que no sea ni infile ni outfile. Pueden ser ejecutados con o sin comillas. Ejemplo:
		- ~ `ls` --> Ejecuta el comando ls
		- ~ `"ls"` --> Ejecuta el comando ls
		- ~ `"ls "` --> Ejecuta el comando "ls " (sin comillas), que no existe
	- **Argumentos**: son los argumentos/flags con los que va a ser ejecutado el comando. Un argumento es todo aquello que no sea ni infile ni outfile ni el comando en sí. Ejemplos:
		- ~ ls -al`
		- ~ ls `-a -l`
		- ...
	- **Infile**: archivo con la información con la que va a ser ejecutada el comando (el comando la toma como entrada de datos). Puede estar en cualquier lugar del comando. Puede ser de dos tipos (en todos los ejemplos el infile es `infile`):
		- **Infile normal**: el comando lee la información de un archivo existente. Ejemplos:
			- ~ `< infile cat` |--| ~ `cat < infile`
			- ~ `<infile cat` |--| ~ `cat <infile`
			- ~ `<"infile" cat` |--| ~ `cat <"infile"`
			- ~ `< "infile" cat` |--| ~ `cat < "infile"`
		- **Here doc**: el comando leerá los datos introducidos por el usuario en tiempo de ejecución. Una vez ejecutada la linea, el proceso se quedará suspendido hasta que el usuario introduzca datos, hasta escribir el delimitador `del`. Ejemplos:
			- ~ `<< del cat` |--| ~ `<< del cat`
			- ~ `<< "del" cat` |--| ~ `cat << "del"`
			- ~ `<<del cat` |--| ~ `cat <<del`
			- ~ `<<"del" cat` |--| ~ `cat <<"del"`
	- **Outfile**: archivo donde se va a guardar el resultado de el/los comando/s. Puede estar en cualquier parte del comando. Puede ser de dos tipos (en todos los ejemplo el outfile es `outfile`):
		- **Modo TRUC**: la información del comando se guardará en el archivo, sobrescribiendo lo que hubiera antes. Ejemplos:
			- ~ cat `> outfile` |--| ~ cat `> outfile`
			- ~ cat `>outfile`
			- ~ cat `> "outfile"`
			- ~ cat `>"outfile"` |--| ~ `>"outfile"` cat
		- **Modo APPEND**: la información se añadirá al final del archivo. Ejemplos:
			- ~ cat `>> outfile` |--| ~ cat `>> outfile`
			- ~ cat `>>outfile`
			- ~ cat `>> "outfile"`
			- ~ cat `>>"outfile"` |--| ~ `>>"outfile"` cat

Por ejemplo, para el comando `<<del < . ls >"1" -a >2 -l >>3`, se ejecutará el comando `ls`, con argumentos `-a -l`, con infiles, uno de here_doc con delimitador `del`, y otro de archivo normal `.`, y outfiles, dos de sobreescritura, `1` y `2`, y uno de adición, `3`.

Para guardar todo, usamos arrays en vez de listas enlazadas, por o que siempre hemos de llevar la cuenta del tamaño de la array para evitar seg faults.

Una vez terminado la parte del parseo, la información debería de estar completamente guardada y estructurada.

### **Ejecutor**
Es el encargado de ejecutar todos los comandos proporcionador por el usuario.

Antes de entrar en las divisiones, hay que tener en cuenta unas cuantas cosas:
- Solo se lee la información de un infile
- Solo se escribe la información en un outfile
- Si el comando recibe varios infiles, solo se leera la información del ultimo de ellos; no obstante, el resto han de ser abierto, ya que si alguno de ellos no existe el comando no se llegará a ejecutar.
- Al igual que el anterior punto, si existieran varios outfiles para el mismo comando, solo se escribiría el resultado en el último, aunque el resto de ellos serían abierto (y probablemento creados)
- Existe un orden de prioridad entre pipes y infiles/outfiles. Por ejemplo, el la linea `ls > out1 | cat`, el `ls` posee un outfile, que es `out1`; no obstante, también tiene la redirección del pipe. En estos casos, bash da prioridad al archivo. Siguiendo el ejemplo de antes, el `ls` escribirá el resultado de su comando en el archivo `out1`, dejando vacío el pipe, por lo que el comando `cat` no imprimirá nada
- Al igual que lo anteriormente mencionado, bash de prioridad a los infiles antes que a los pipes; por ello, en la linea `ls | < inf cat`, el `ls` escribirá su resultado en el pipe, pero el `cat` leerá la información del infile `inf`

Dependiendo del número de comandos que haya, podemos dividirlo en dos categorías:
- **Un solo comando**: escribirá del último infile que posea y escribirá en el último outfile que posea. En caso de no haber infile, leera de la entrada estandar (`STDIN_FILENO`), mientras que si no tiene salida escribirá en la salida estandar (`STDOUT_FILENO`).
	- En el caso en el que el comando no sea un built-in, este será ejecutado en un proceso hijo, fruto de la llamada al sistema `fork`.
	- Si fuera un built-in, deberá ser ejecutado en el padre, ya que comandos como exit o unset han de modificar las variables principales del programa. Es importante recalcar la importancia de mantener en algún lugar las referencias a `STDIN_FILENO` y `STDOUT_FILENO`, ya que al ejecuatar un `dup2` sustituyendo alguna de estas la perderemos.
- **Varios comandos**: dependiendo de la posición del comando:
	- Leerá de un archivo y escribirá en un pipe (primer comando)
	- Leerá de un pipe y escribirá en un pipe (comandos intermedios)
	- Leerá de un pipe ye escribirá en un archivo (último comando)

	Aún siendo un built-in, en este caso será ejecutado en un proceso hijo.

Para ejecutar un comando no built-in, se pueden seguir los siguientes pasos:
1. Abrimos el archivo de entrada de datos (infile, pipe o STDIN_FILENO, en ese orden).
2. Abrimos el archivo de salida (outfile, pipe o STDOUT_FILENO, en ese orden).
3. Buscamos el path del comando a ejecutar. Hay que diferenciar si el comando nos lo han pasado como ruta relativa o absoluta, o si está en alguna carpeta del PATH:
	- Si el comando poseía una '/', el comando es relativo o absoluto, por lo que no hace falta buscar nada
	- Si no posee este carácter, es necesario buscar en que carpeta disponible de la variable `PATH`está (si es que está)
4. Tambien han de ser guardados juntos el comando junto con sus argumentos. Este paso puede ser ahorrado en el parseo, juntando todo a final.

**NOTA**: es importante cerrar todos los archivos, y sobre todos los pipes. En el caso en el que haya una entrada de pipe abierto, se podría producir un bloqueo en algún comando, lo que haría que nunca se terminaran los procesos.

Después de haber ejecutado todos los comandos, ha de ser guardado el retorno del último de ellos, ya sea built-in o un comando normal. Este valor puede ser mostrado por terminal con el comando `echo $?`