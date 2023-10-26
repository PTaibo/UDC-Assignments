Commando help de close le falta un parentesis

	Closes a specified file
	Usage: cloase [fd] //aqui es close 
	Options:
		fd: file descriptor of the opened file
	Related commands: listopen (gives you the list of opened
			  files with their file descriptors //aqui te falta cerrar el parentesis

creé un directorio y lo intenté abrir con el commando open 
me deja abrirlo solo en los casos en dode uso open directorio ro y el ap 
entonces lo añade a la lista de listopen dos veces

> listopen
   FD  MODE  FILE
    0   rw   stdin
    1   rw   stdout
    2   rw   stderr
    3   ro   hola.txt
    4   ro   hola.txt


> stat -long -acc hola.txg
    last access     links  inode     own     grp      mode         size  name
Couldn't get file stats for hola.txg: No such file or directory

no se si hiciste aposta esto de poner el titulo igualmente

el help de delete:DELETE:
	Deltes files and/or emtpy directories //esto es deletes
	Usage: delete [NAMES]

> 





