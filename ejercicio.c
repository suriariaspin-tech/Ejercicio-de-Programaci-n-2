/*
Nombres: Nicolas Menendez, Joel Cruz y Suri Arias
Fecha: 05/05/2026
Descripcion: Este programa permite gestionar la producción de una fábrica a través de un sistema de registro, edición, eliminación y visualización de productos, así como el cálculo del tiempo total requerido y los recursos necesarios para cumplir con la demanda, y la verificación de si la producción es viable con los recursos disponibles. 
El programa utiliza funciones para validar entradas, manejar el buffer de entrada y realizar las operaciones necesarias para gestionar los productos y calcular los tiempos y recursos requeridos.
*/

#include <stdio.h>
#include "funciones.h"

int main() {
    char nombres[MAX_PRODUCTOS][MAX_NOMBRE]; //Matriz para almacenar los nombres de los productos
    int cantidades[MAX_PRODUCTOS]; //Arreglo para almacenar las cantidades demandadas
    float tiempos[MAX_PRODUCTOS]; //Arreglo para almacenar los tiempos de fabricacion por unidad
    int recursos[MAX_PRODUCTOS]; //Arreglo para almacenar los recursos necesarios por unidad
    int totalProductos = 0; //Variable para llevar el conteo de productos registrados
    int opcion; //Variable para el menu

    do {
        printf("\n===== SISTEMA GCP =====\n 1. Registrar producto\n 2. Mostrar productos\n 3. Buscar producto\n 4. Editar producto\n 5. Eliminar producto\n 6. Calcular tiempo total\n 7. Calcular recursos totales\n 8. Verificar produccion\n 9. Salir\n Seleccione una opcion: ");
        ValidarCantidad(&opcion); // Llamada a la función para validar que la opción ingresada sea un número entero positivo
        while(opcion < 1 || opcion > 9) { // BUCLE para validar que la opción ingresada esté dentro del rango permitido
            printf("Opcion invalida. Seleccione una opcion del 1 al 9: ");
            ValidarCantidad(&opcion); // Llamada a la función para validar que la opción ingresada sea un número entero positivo
        }

        switch(opcion) {

            case 1:
                registrarProductos(nombres, cantidades, tiempos, recursos, &totalProductos); // Llamada a la función para registrar un nuevo producto
                break;

            case 2:
                mostrarProductos(nombres, cantidades, tiempos, recursos, totalProductos); // Llamada a la función para mostrar los productos registrados
                break;

            case 3: 
            {
                char buscado[MAX_NOMBRE]; // Variable para almacenar el nombre del producto a buscar
                printf("Ingrese el nombre del producto: ");
                ValidarTexto(buscado, MAX_NOMBRE); // Llamada a la función para validar que el texto ingresado sea correcto

                int posicion = buscarProducto(nombres, totalProductos, buscado); // Llamada a la función para buscar el producto

                if(posicion != -1) { // Si la función devuelve una posición válida, se muestra la información del producto encontrado
                    printf("\nProducto encontrado:\n");
                    printf("Nombre: %s\n", nombres[posicion]);
                    printf("Cantidad: %d\n", cantidades[posicion]);
                    printf("Tiempo: %.2f\n", tiempos[posicion]);
                    printf("Recursos: %d\n", recursos[posicion]);
                } else {
                    printf("Producto no encontrado.\n"); // Si la función devuelve -1, se muestra un mensaje indicando que el producto no fue encontrado
                }
                break;
            }

            case 4:
                editarProducto(nombres, cantidades, tiempos, recursos, totalProductos); // Llamada a la función para editar un producto existente
                break;

            case 5:
                eliminarProducto(nombres, cantidades, tiempos, recursos, &totalProductos); // Llamada a la función para eliminar un producto
                break;

            case 6: 
            {
                float totalTiempo = calcularTiempoTotal(cantidades, tiempos, totalProductos); // Llamada a la función para calcular el tiempo total de producción
                printf("Tiempo total requerido: %.2f horas\n", totalTiempo);
                break;
            }

            case 7: 
            {
                int totalRecursos = calcularRecursosTotales(cantidades, recursos, totalProductos); // Llamada a la función para calcular los recursos totales necesarios
                printf("Recursos totales necesarios: %d\n", totalRecursos);
                break;
            }

            case 8:
                verificarProduccion(cantidades, tiempos, recursos, totalProductos); // Llamada a la función para verificar si la producción es viable con los recursos disponibles
                break;

            case 9:
                printf("Saliendo del sistema...\n"); // Mensaje de despedida al salir del programa
                break;

            default:
                printf("Opcion invalida.\n");

        }

    } while(opcion != 9);

    return 0;

}