20170629
========

```
	project.init ();
```

Vamos a perder un poco de tiempo, pero estableciendo las bases necesarias para que pueda volver al Spectrum. No tocarlo en 2 años pasa factura, porque ahora todo lo que tengo, motores y herramientas, se me antojan obsoletos. Me gustaría aplicar todo lo que he aprendido programando al NES para volver al Spectrum. Como le prometí al de Monument un Ninjajar exclusivo con outtakes, me voy a dedicar a ello.

Para empezar necesito conversores nuevos. Paso de la mierda de formato de tileset de siempre, voy a usar el neuvo. No sé si adaptar mkts o hacer un mkts-sp desde cero (cortapegando, claro). Creo que mejor lo segundo.

Veamos, lo suyo sería que todo generase binarios para poder comprimirlos, pensando siempre en el modus operandi de mi trabajo en Spectrum 128K.

- **Metatilesets**: Para Z80 es mejor intercalar los tiles de cada metatiles, por lo que los metatilesets serán una ristra de atributos y números de tile. Como se imprimirán con sp_PrintAtInv, y los parámetros son (x, y, attr, chr), el formato intercalará, en este orden, atributos y tiles, de izquierda a derecha y de arriba a abajo.

- **Spritesets**: Se debe generar un binario que pueda descomprimir e interpretar directamente. Debe empezar con 7 ceros. La dirección del primer sprite debe ser 7 más la dirección de carga. Cada sprite ocupa 3 columnas de 24 filas de 16 bits, 3*24*2 = 144 bytes, por lo que cada sprite S estará en dir+7+144*S, y cada columna de ese sprite será un offset de 48 bytes sobre la anterior. Por ahora no lo meteré, pero en un futuro debería poder intercalar sprites sin máscaras.

- **Charsets**: El modo chars es directo, sin problemas.

Debo empezar escribiendo la rutina básica de interpretar un 8x8 y a partir de ahí construir todo lo demás. Voy a empezar de cero, copiapegando, y al final portaré el intérprete de los scripts.

~~

Cool! mkts_sp está bastante limpio y exporta charsets, metatilesets y spritesets por separado. Por ahora voy a pasar de integrar el scripting porque tengo ganas de seguir adelante con el resto del framework.

Veamos: mapas. Usaré RLE 5.3 con decoraciones, deberían salir pocas decoraciones en un juego como Ninjajar. Para el RLE deberá haber un array de offsets, ya que lo que generaré será un binario que pueda comprimir con aplib. 

El conversor reservará por tanto `2*MAP_W*MAP_H` bytes al principio del binario e irá comprimiendo las pantallas y añadiéndolas al mismo, escribiendo en el índice el offset actual antes de empezar.

Son las 21:42, a ver si lo puedo hacer en 18 minutos #-)

20170630
========

Por lo general, yo soy más de ir haciendo según voy necesitando, pero por alguna razón quiero tener antes de empezar a programar nada el conversor de enemigos. Esto puede cambiar. Pero en los próximos 10-15 minutos voy a convertir eneexp3c para que genere binarios para MK3 de Spectrum.

Necesitamos mejores nombres para los motores.

~~

Buenobuenobueno, ya tengo los conversores convirtiendo, y un buildbins funcionando que convierte todo y comprime todas las cosas comprimiscibles.

Ahora es cuando empiezo con el esqueleto del proyecto. Hay que empezar con un system donde defina todo y ponga todas las cosas en su sitio. Luego empezaré a montar un level_manager. Cuando el esqueleto esté listo lo primero siempre es mostrar el mapa en pantalla.

20170705
========

He refinado las utilidades y he hecho el level setup, parece que lo pone todo en su sitio. Voy a imprimir cosas, los patrones por ejemplo.

~~

Y el map renderer también está bien. Ahora he empezado a importar cosas. He metido definitions.h y he logrado compilar con player.h (pero obviamente no hay nada que ejecutar todavía). Estoy haciendo modificaciones pensando siempre en poder portar a otros ordenadores de mierda, además del Spectrum.

Lo siguiente es crear las estructuras de los sprites (y hacerlo de una forma más genérica y mejor que la original), sacar sprites en pantalla, y luego empezar a montar un game_loop básico para intentar hacer funcionar player.h.

~~

Ya he metido un montón de castaña y tentetieso, he hecho un inicializador de sprites menos apestoso, todos los sprites irán en el mismo choco para actualizarlos de una plumez, y tal y cual.

Echo de menos más permisividad para definir constantes y tal, pero bueno. Se puede beberciar.

Ya he pintado un sprite en pantalla. Y se mueve, y no se corrompe, y tal y cual y pascual.

Ahora lo que viene es montar el bucle principal. Pero voy a descansar.

20170707
========

Todo iba bien y chuli metiendo los bloques destructibles del escenario (ayer hice el puñito) hasta que me ha dado por pensar que a ver cómo coño modifico el mapa de forma persistente si está almacenado en RLE.

Epic fail, manolito.

Tendré que cambiar el mapa a packed.

