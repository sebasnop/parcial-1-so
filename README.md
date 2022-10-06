# Primera evaluación parcial - Sistemas Operativos

## Hecho por

- Alejandra Uribe Sierra
- Sebastián Valencia Zapata

## Enunciado

Escriba un programa en lenguaje C que use mecanismos de IPC para habilitar la comunicación entre un proceso padre y un proceso hijo. El proceso padre debe quedar en un ciclo leyendo una cadena de texto desde la entrada estándar (el teclado). La cadena de texto debe enviarse al proceso hijo a través del mecanismo de IPC. El proceso hijo convierte la cadena de texto a mayúsculas y la envía de regreso al proceso padre usando el mecanismo de IPC elegido. El padre lee lo entregado por el hijo y lo muestra en la salida estándar (la pantalla) antes de volver a iterar para la próxima lectura.
