# Cómo Usar el Generador de Contraseñas en C con Aircrack-ng

Este `README.md` te guiará sobre cómo ejecutar tu programa generador de contraseñas en C y utilizar su salida directamente con la herramienta `aircrack-ng` para auditorías de seguridad Wi-Fi. Este método es eficiente porque evita la necesidad de guardar las contraseñas generadas en un archivo intermedio.

---

## ⚠️ Aviso Importante

**Realiza estas acciones solo en redes de tu propiedad o para las cuales tengas permiso explícito.** El acceso no autorizado a sistemas informáticos es ilegal y puede tener graves consecuencias legales.

---

## 🚀 Requisitos Previos

Antes de empezar, asegúrate de tener lo siguiente:

1.  **El programa generador de contraseñas compilado:** Debes tener el archivo ejecutable de tu código C (`generador_contrasenas`). Si aún no lo tienes, compílalo:
    ```bash
    gcc generador_contrasenas.c -o generador_contrasenas
    ```
2.  **Aircrack-ng instalado:** Asegúrate de tener la suite Aircrack-ng instalada en tu sistema.
3.  **Un archivo de captura con un handshake WPA/WPA2:** Necesitarás un archivo `.cap` que contenga el handshake de la red Wi-Fi que deseas auditar. Este archivo se obtiene generalmente con herramientas como `airodump-ng`.

---

## ⚡️ El Concepto: "Tuberías" (Pipes)

Vamos a usar una característica de la línea de comandos llamada **"tubería" o "pipe" (`|`)**. Una tubería toma la salida estándar (`stdout`) de un programa y la envía como entrada estándar (`stdin`) a otro programa.

En este caso:

* Tu programa `./generador_contrasenas` generará contraseñas y las imprimirá en `stdout`.
* La tubería `|` tomará esas contraseñas.
* `aircrack-ng` las recibirá como su entrada (`stdin`) para utilizarlas como lista de palabras.

---

## ⚙️ Adaptación del Código C (Recomendado)

Para un uso óptimo con tuberías, es aconsejable **desactivar la función de guardar las contraseñas en un archivo** dentro de tu código C, ya que la salida irá directamente a `aircrack-ng`.

Abre tu archivo `generador_contrasenas.c` y asegúrate de que la línea `GUARDAR_INTENTOS` esté configurada o eliminada para que no escriba en un archivo:

```c
#define LONGITUD 20         // Longitud de la contraseña
#define MAX_INTENTOS 0      // 0 = infinito (ideal para pipes). Cambia a un número para limitar.
// #define GUARDAR_INTENTOS 1  // Esta línea debe estar comentada o eliminada si existía.
                            // Si la tienes, cámbiala a: #define GUARDAR_INTENTOS 0