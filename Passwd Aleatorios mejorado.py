import random
import string
import sys
import time

# Configuración
LONGITUD = 20  # Longitud de la contraseña
MAX_INTENTOS = 100000  # Cambia este valor para limitar intentos (0 = infinito)
GUARDAR_INTENTOS = True  # Cambia a False si no quieres guardar intentos

def generar_contraseña(longitud=LONGITUD):
    """Genera una contraseña aleatoria sin repetir caracteres consecutivos del mismo tipo."""
    caracteres = string.ascii_lowercase + string.ascii_uppercase + string.digits
    contraseña = [random.choice(caracteres)]

    while len(contraseña) < longitud:
        siguiente = random.choice(caracteres)
        if (siguiente.islower() and contraseña[-1].islower()) or \
           (siguiente.isupper() and contraseña[-1].isupper()) or \
           (siguiente.isdigit() and contraseña[-1].isdigit()):
            continue
        contraseña.append(siguiente)

    return ''.join(contraseña)

# Abre el archivo para guardar intentos (si está activado)
if GUARDAR_INTENTOS:
    archivo = open("intentos.txt", "a")

contador = 0
while MAX_INTENTOS == 0 or contador < MAX_INTENTOS:
    contraseña = generar_contraseña()
    sys.stdout.write(contraseña + "\n")
    sys.stdout.flush()

    if GUARDAR_INTENTOS:
        archivo.write(contraseña + "\n")
        archivo.flush()

    contador += 1

# Cierra el archivo si está activado
if GUARDAR_INTENTOS:
    archivo.close()



##python3 generador.py | aircrack-ng -b <BSSID> -w - captura.cap