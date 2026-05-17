#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"

// FUNCIÓN para limpiar el buffer después de usar scanf y evitar que el siguiente fgets se salte
void LimpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { } // Limpia el buffer hasta encontrar un salto de línea o el fin de archivo
}

// FUNCIÓN para validar que el texto ingresado no contenga caracteres no permitidos (solo letras, números y espacios)
int TextoValido(char texto[]) {
    for(int i = 0; texto[i] != '\0'; i++) { // BUCLE para verificar cada caracter del texto y validar que solo contenga letras, números y espacios
        if(!isalpha(texto[i]) && !isdigit(texto[i]) && !isspace(texto[i])) { // Si se encuentra un caracter que no es letra ni número ni espacio, se considera inválido
            return 0; // Si el texto es inválido, se devuelve 0
        }
    }
    return 1; // Si el texto es válido, se devuelve 1
}

// FUNCIÓN para validar textos y evitar que estén vacíos o contengan caracteres no permitidos
void ValidarTexto(char texto[], int tamaño) {
    do {
        fgets(texto, tamaño, stdin);
        texto[strcspn(texto, "\n")] = 0; // Elimina el salto de línea al final del texto ingresado
        if(strlen(texto) == 0) { // Si el texto está vacío, se muestra un mensaje de error y se solicita ingresar nuevamente
            printf("La entrada no puede estar vacia. Ingrese nuevamente: ");
        } else if(!TextoValido(texto)) {
            printf("Solo se permiten letras, numeros y espacios. Ingrese nuevamente: ");
        }
    } while(strlen(texto) == 0 || !TextoValido(texto)); // BUCLE para validar que el texto no esté vacío y que no contenga caracteres no permitidos
}

// FUNCIÓN para validar que los valores ingresados sean números enteros y positivos
void ValidarCantidad(int *numero) {
    while(scanf("%d", numero) != 1 || *numero < 0) { // BUCLE para validar que la entrada sea un número entero y positivo
        printf("Valor invalido. Ingrese un numero positivo: ");
        LimpiarBuffer(); // Llamada a la función para limpiar el buffer después de una entrada inválida
    }
    LimpiarBuffer(); // Llamada a la función para limpiar el buffer después de una entrada válida
}

// FUNCIÓN para validar que los valores ingresados sean números flotantes y positivos
void ValidarFloat(float *numero) {
    while(scanf("%f", numero) != 1 || *numero < 0) { // BUCLE para validar que la entrada sea un número flotante y positivo
        printf("Valor invalido. Ingrese un numero positivo: ");
        LimpiarBuffer(); // Llamada a la función para limpiar el buffer después de una entrada inválida
    }
    LimpiarBuffer(); // Llamada a la función para limpiar el buffer después de una entrada válida
}

// FUNCIÓN para registrar productos
void registrarProductos(char nombres[][MAX_NOMBRE], int cantidades[], float tiempos[], int recursos[], int *total) {
    if(*total >= MAX_PRODUCTOS) { // Verifica si se ha alcanzado la capacidad máxima de productos antes de intentar registrar un nuevo producto
        printf("Capacidad maxima alcanzada.\n");
        return;
    }
    printf("Ingrese el nombre del producto: ");
    ValidarTexto(nombres[*total], MAX_NOMBRE); // Llamada a la función para validar que el texto ingresado sea correcto
    printf("Ingrese la cantidad demandada: ");
    ValidarCantidad(&cantidades[*total]); // Llamada a la función para validar que la cantidad ingresada sea un número entero positivo
    printf("Ingrese el tiempo de fabricacion por unidad (en horas): ");
    ValidarFloat(&tiempos[*total]); // Llamada a la función para validar que el tiempo ingresado sea un número flotante positivo
    printf("Ingrese los recursos necesarios por unidad: ");
    ValidarCantidad(&recursos[*total]); // Llamada a la función para validar que los recursos ingresados sean un número entero positivo
    LimpiarBuffer(); // Llamada a la función para limpiar el buffer después de registrar un nuevo producto
    (*total)++; // Incrementa el contador de productos después de registrar un nuevo producto
    printf("Producto registrado correctamente.\n");
}

// FUNCIÓN para mostrar productos registrados
void mostrarProductos(char nombres[][MAX_NOMBRE], int cantidades[], float tiempos[], int recursos[], int total) {
    if(total == 0) { // Verifica si no hay productos registrados antes de intentar mostrarlos
        printf("No existen productos registrados.\n");
        return;
    }
    for(int i = 0; i < total; i++) { // BUCLE para mostrar todos los productos registrados
        printf("\nPRODUCTO %d: \n Nombre: %s\n Cantidad demandada: %d\n Tiempo de fabricacion: %.2f horas\n Recursos necesarios: %d\n", i + 1, nombres[i], cantidades[i], tiempos[i], recursos[i]);
    }

}

// FUNCIÓN para buscar productos
int buscarProducto(char nombres[][MAX_NOMBRE], int total, char buscado[]) {
    if(total == 0) { // Verifica si no hay productos registrados antes de intentar buscar
        printf("No existen productos registrados.\n");
        return -1;
    }
    for(int i = 0; i < total; i++) { // BUCLE para comparar nombres de productos registrados con el nombre del producto buscado y devolviendo la posición del producto encontrado o -1 si no se encuentra
        if(strcmp(nombres[i], buscado) == 0) {
            return i; // Si se encuentra el producto, se devuelve su posición en los arreglos
        }
    }
    return -1; // Si no se encuentra el producto, se devuelve -1 para indicar que no se encontró el producto buscado
}

// FUNCIÓN para editar productos
void editarProducto(char nombres[][MAX_NOMBRE], int cantidades[], float tiempos[], int recursos[], int total) {
    char buscado[MAX_NOMBRE]; // Variable para almacenar el nombre del producto a editar
    if(total == 0) { // Verifica si no hay productos registrados antes de intentar buscar y editar
        printf("No existen productos registrados.\n");
        return;
    }
    printf("Ingrese el nombre del producto a editar: ");
    ValidarTexto(buscado, MAX_NOMBRE); // Llamada a la función para validar que el texto ingresado sea correcto
    
    int posicion = buscarProducto(nombres, total, buscado); // Llamada a la función para buscar el producto

    if(posicion == -1) { // Si la función buscarProducto devuelve -1, se muestra un mensaje indicando que el producto no fue encontrado y se retorna para evitar intentar editar un producto inexistente
        printf("Producto no encontrado.\n");
        return;
    }

    printf("Nuevo nombre: ");
    ValidarTexto(nombres[posicion], MAX_NOMBRE); // Llamada a la función para validar que el nuevo nombre ingresado sea correcto para actualizar el nombre del producto en la posición encontrada
    printf("Nueva cantidad demandada: ");
    ValidarCantidad(&cantidades[posicion]); //Llamada a la función para validar que la nueva cantidad ingresada sea un número entero positivo para actualizar la cantidad del producto en la posición encontrada
    printf("Nuevo tiempo de fabricacion: ");
    ValidarFloat(&tiempos[posicion]); // Llamada a la función para validar que el nuevo tiempo ingresado sea un número flotante positivo para actualizar el tiempo de fabricación del producto en la posición encontrada
    printf("Nuevos recursos necesarios: ");
    ValidarCantidad(&recursos[posicion]); // Llamada a la función para validar que los nuevos recursos ingresados sean un número entero positivo para actualizar los recursos necesarios del producto en la posición encontrada
    printf("Producto editado correctamente.\n");
}

// FUNCIÓN para eliminar productos
void eliminarProducto(char nombres[][MAX_NOMBRE], int cantidades[], float tiempos[], int recursos[], int *total) {
    char buscado[MAX_NOMBRE]; // Variable para almacenar el nombre del producto a eliminar
    if(*total == 0) { // Verifica si no hay productos registrados antes de intentar eliminar
        printf("No existen productos registrados.\n");
        return;
    }
    printf("Ingrese el nombre del producto a eliminar: ");
    ValidarTexto(buscado, MAX_NOMBRE); // Llamada a la función para validar que el texto ingresado sea correcto
    
    int posicion = buscarProducto(nombres, *total, buscado); // Llamada a la función para buscar el producto

    if(posicion == -1) { // Si la función buscarProducto devuelve -1, se muestra un mensaje indicando que el producto no fue encontrado y se retorna para evitar intentar eliminar un producto inexistente
        printf("Producto no encontrado.\n");
        return;
    }
    for(int i = posicion; i < *total - 1; i++) { // BUCLE para mover todos los elementos una posición atrás a partir de la posición del producto a eliminar
        strcpy(nombres[i], nombres[i + 1]); // Se copia el nombre del producto siguiente al actual para eliminar el producto en la posición encontrada
        cantidades[i] = cantidades[i + 1]; // Se copia la cantidad del producto siguiente al actual para eliminar el producto en la posición encontrada
        tiempos[i] = tiempos[i + 1]; // Se copia el tiempo de fabricación del producto siguiente al actual para eliminar el producto en la posición encontrada
        recursos[i] = recursos[i + 1]; // Se copian los recursos del producto siguiente al actual para eliminar el producto en la posición encontrada
    }
    (*total)--; // Decrementa el contador de productos después de eliminar un producto
    printf("Producto eliminado correctamente.\n");
}

// FUNCIÓN para calcular el tiempo total de producción necesario para cumplir con la demanda de todos los productos registrados
float calcularTiempoTotal(int cantidades[], float tiempos[], int total) {
    float suma = 0; // Variable para acumular el tiempo total necesario para cumplir con la demanda de todos los productos registrados
    for(int i = 0; i < total; i++) { // BUCLE para calcular el tiempo total
        suma += cantidades[i] * tiempos[i]; // Se multiplica la cantidad demandada de cada producto por su tiempo de fabricación por unidad y se acumula en la variable suma para obtener el tiempo total necesario para cumplir con la demanda de todos los productos registrados
    }
    return suma;
}

// FUNCIÓN para calcular los recursos totales necesarios para cumplir con la demanda de todos los productos registrados
int calcularRecursosTotales(int cantidades[], int recursos[], int total) {
    int suma = 0; // Variable para acumular los recursos totales necesarios para cumplir con la demanda de todos los productos registrados
    for(int i = 0; i < total; i++) { // BUCLE para calcular recursos totales necesarios para cumplir con la demanda de todos los productos registrados
        suma += cantidades[i] * recursos[i]; // Se multiplica la cantidad demandada de cada producto por sus recursos necesarios por unidad y se acumula en la variable suma para obtener los recursos totales necesarios para cumplir con la demanda de todos los productos registrados
    }
    return suma;
}

// FUNCIÓN para verificar la producción viable con recursos disponibles
void verificarProduccion(int cantidades[], float tiempos[], int recursos[], int total) {
    float tiempoDisponible; // Variable para almacenar el tiempo disponible ingresado por el usuario
    int recursosDisponibles; // Variable para almacenar los recursos disponibles ingresados por el usuario
    float tiempoNecesario = calcularTiempoTotal(cantidades, tiempos, total); // Llamada a la función para calcular el tiempo total necesario para cumplir con la demanda de todos los productos registrados
    int recursosNecesarios = calcularRecursosTotales(cantidades, recursos, total); // Llamada a la función para calcular los recursos totales necesarios para cumplir con la demanda de todos los productos registrados

    printf("Ingrese el tiempo disponible: ");
    ValidarFloat(&tiempoDisponible); // Llamada a la función para validar que el tiempo disponible ingresado sea un número flotante positivo

    printf("Ingrese los recursos disponibles: ");
    ValidarCantidad(&recursosDisponibles); // Llamada a la función para validar que los recursos disponibles ingresados sean un número entero positivo

    if(tiempoNecesario <= tiempoDisponible && recursosNecesarios <= recursosDisponibles) { // Se verifica si el tiempo necesario para cumplir con la demanda de todos los productos registrados es menor o igual al tiempo disponible ingresado por el usuario, y si los recursos necesarios para cumplir con la demanda de todos los productos registrados son menores o iguales a los recursos disponibles ingresados por el usuario, lo que indica que la producción es viable con los recursos disponibles
        printf("La fabrica SI puede cumplir la produccion.\n");
    } else {
        printf("La fabrica NO puede cumplir la produccion.\n");
    }
}