#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h> // Para islower, isupper, isdigit

// --- Configuración ---
#define LONGITUD 20         // Longitud de la contraseña
#define MAX_INTENTOS 0      // 0 = infinito. Cambia a un número para limitar la generación.
// #define GUARDAR_INTENTOS 1  // ELIMINADO o establecido a 0, ya que la salida se envía directamente

// Función para generar una contraseña aleatoria
char *generar_contrasena(int longitud) {
    char *caracteres = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int num_caracteres = strlen(caracteres);
    char *contrasena = (char *)malloc(sizeof(char) * (longitud + 1)); // +1 para el terminador nulo

    if (contrasena == NULL) {
        perror("Error al asignar memoria para la contraseña");
        exit(EXIT_FAILURE);
    }

    // El primer carácter se elige aleatoriamente
    contrasena[0] = caracteres[rand() % num_caracteres];

    for (int i = 1; i < longitud; i++) {
        char siguiente_caracter;
        do {
            siguiente_caracter = caracteres[rand() % num_caracteres];
            // Evitar caracteres consecutivos del mismo tipo
        } while ((islower(siguiente_caracter) && islower(contrasena[i-1])) ||
                 (isupper(siguiente_caracter) && isupper(contrasena[i-1])) ||
                 (isdigit(siguiente_caracter) && isdigit(contrasena[i-1])));
        contrasena[i] = siguiente_caracter;
    }
    contrasena[longitud] = '\0'; // Asegura que la cadena esté terminada en nulo

    return contrasena;
}

int main() {
    // Inicializa el generador de números aleatorios con la hora actual
    srand((unsigned int)time(NULL));

    // No necesitamos un archivo cuando la salida va a stdout y luego a una tubería
    // FILE *archivo = NULL;
    // if (GUARDAR_INTENTOS) { ... }

    long long contador = 0; // Usamos long long para un contador más grande
    while (MAX_INTENTOS == 0 || contador < MAX_INTENTOS) {
        char *contrasena = generar_contrasena(LONGITUD);

        // Imprime la contraseña en la consola (stdout), que será capturada por la tubería
        printf("%s\n", contrasena);
        fflush(stdout); // Asegura que la salida se imprima inmediatamente

        // Ya no necesitamos guardar en un archivo aquí
        // if (GUARDAR_INTENTOS) { ... }

        free(contrasena); // Libera la memoria asignada para la contraseña
        contador++;
    }

    // No necesitamos cerrar un archivo
    // if (GUARDAR_INTENTOS && archivo != NULL) { ... }

    return EXIT_SUCCESS;
}