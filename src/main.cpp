#include <Arduino.h>

// Prototipo de la función que ejecutará la tarea secundaria
void anotherTask(void * parameter);

void setup() {
  // Inicializamos el puerto serie a 115200 bps
  Serial.begin(115200); 

  /* Creamos una nueva tarea en FreeRTOS */
  xTaskCreate(
    anotherTask,      /* Función que implementa la tarea [cite: 168] */
    "another Task",   /* Nombre de la tarea para depuración [cite: 168] */
    10000,            /* Tamaño de la pila (en bytes) [cite: 168] */
    NULL,             /* Parámetro de entrada para la tarea [cite: 169] */
    1,                /* Prioridad de la tarea (1 es baja) [cite: 170] */
    NULL              /* Identificador (handle) opcional [cite: 171] */
  );
}

/* La función loop() es invocada por la tarea loopTask de ESP32 [cite: 173] */
void loop() {
  Serial.println("this is ESP32 Task");
  delay(1000); // Pausa de 1 segundo [cite: 177]
}

/* Función de la tarea secundaria */
void anotherTask(void * parameter) {
  /* Bucle infinito obligatorio para tareas que no terminan [cite: 182] */
  for(;;) {
    Serial.println("this is another Task");
    delay(1000); // Pausa de 1 segundo dentro de la tarea [cite: 185]
  }
  
  /* vTaskDelete(NULL) se llamaría si la tarea terminara, 
     pero aquí no sucede por el bucle for(;;) [cite: 190] */
  vTaskDelete(NULL); 
}