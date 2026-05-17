#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_PRODUCTOS 5
#define MAX_NOMBRE 50

void LimpiarBuffer(); // Función para limpiar el buffer después de usar scanf y evitar que el siguiente fgets se salte
int TextoValido(char texto[]); // Función para validar que el texto ingresado no contenga caracteres no permitidos (solo letras, números y espacios)
void ValidarTexto(char texto[], int tamaño); // Función para validar textos
void ValidarCantidad(int *numero); // Función para validar que los valores ingresados sean números enteros y positivos
void ValidarFloat(float *numero); // Función para validar que los valores ingresados sean números flotantes y positivos
void registrarProductos(char nombres[][MAX_NOMBRE], int cantidades[], float tiempos[], int recursos[], int *total); // Función para registrar productos en el sistema
int buscarProducto(char nombres[][MAX_NOMBRE], int total, char buscado[]); // Función para buscar un producto por su nombre
void mostrarProductos(char nombres[][MAX_NOMBRE], int cantidades[], float tiempos[], int recursos[], int total); // Función para mostrar los productos registrados
void editarProducto(char nombres[][MAX_NOMBRE], int cantidades[], float tiempos[], int recursos[], int total); // Función para editar un producto existente
void eliminarProducto(char nombres[][MAX_NOMBRE], int cantidades[], float tiempos[], int recursos[], int *total); // Función para eliminar un producto
float calcularTiempoTotal(int cantidades[], float tiempos[], int total); // Función para calcular el tiempo total de producción
int calcularRecursosTotales(int cantidades[], int recursos[], int total); // Función para calcular los recursos totales necesarios
void verificarProduccion(int cantidades[], float tiempos[], int recursos[], int total); // Función para verificar si la producción es viable con los recursos disponibles

#endif