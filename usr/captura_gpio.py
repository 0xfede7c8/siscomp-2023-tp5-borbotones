import RPi.GPIO as GPIO
import matplotlib.pyplot as plt
import time

# Configuración de pines GPIO
pin = 17  # Pin GPIO que se utilizará
GPIO.setmode(GPIO.BCM)
GPIO.setup(pin, GPIO.IN)

# Variables para almacenar los datos de la señal
tiempo = []
valores = []

# Tiempo de muestreo (en segundos) y duración de la captura
tiempo_muestreo = 0.1
duracion_captura = 10

# Captura de datos
inicio_tiempo = time.time()
while (time.time() - inicio_tiempo) < duracion_captura:
    tiempo.append(time.time() - inicio_tiempo)
    valores.append(GPIO.input(pin))
    time.sleep(tiempo_muestreo)

# Graficar los datos capturados
plt.plot(tiempo, valores)
plt.xlabel('Tiempo (s)')
plt.ylabel('Valor')
plt.title('Grafica de la señal GPIO')
plt.show()

# Limpieza de los pines GPIO
GPIO.cleanup()

