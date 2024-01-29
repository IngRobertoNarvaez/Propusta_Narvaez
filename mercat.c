#include <stdio.h>
/*Se define el maximo de productos que puede ingresar*/
#define MAX_PRODUCTOS 100

// Definición de la estructura del producto
struct Producto
{
    char codigo[20]; // Nuevo miembro para el código del producto
    char nombre[50];
    float precioCompra;
    int cantidad;
};

// Función para calcular la utilidad por producto
float calcularUtilidad(struct Producto producto)
{
    // Supongamos que la utilidad es el 10% del precio de compra
    float utilidad = 0.1 * producto.precioCompra;
    return utilidad;
}

// Función para guardar el inventario en un archivo
void guardarInventario(struct Producto inventario[], int numProductos)
{
    FILE *archivost;
    archivost = fopen("inventario.txt", "w");
    if (archivost == NULL)
    {
        printf("Error al abrir el archivo.");
        return;
    }

    for (int i = 0; i < numProductos; i++)
    {
        fprintf(archivost, "%s %s %.2f %d\n", inventario[i].codigo, inventario[i].nombre, inventario[i].precioCompra, inventario[i].cantidad);
    }

    fclose(archivost);
}

// Función para cargar el inventario desde un archivo
int cargarInventario(struct Producto inventario[])
{
    FILE *archivost;
    archivost = fopen("inventario.txt", "r");
    if (archivost == NULL)
    {
        printf("Error al abrir el archivo.");
        return 0;
    }

    int numProductos = 0;
    while (fscanf(archivost, "%s %s %f %d", inventario[numProductos].codigo, inventario[numProductos].nombre, &inventario[numProductos].precioCompra, &inventario[numProductos].cantidad) == 4)
    {
        numProductos++;
    }

    fclose(archivost);
    return numProductos;
}

// Función para ingresar un nuevo producto
int ingresarProducto(struct Producto inventario[], int numProductos)
{
    printf("\nIngrese los datos para el nuevo producto:\n");
    printf("Codigo: ");
    scanf("%s", inventario[numProductos].codigo);
    printf("Nombre: ");
    scanf("%s", inventario[numProductos].nombre);
    printf("Precio de compra: ");
    scanf("%f", &inventario[numProductos].precioCompra);
    printf("Cantidad: ");
    scanf("%d", &inventario[numProductos].cantidad);

    // Guardar el inventario después de ingresar un nuevo producto
    guardarInventario(inventario, numProductos + 1);

    return numProductos + 1;
}

// Función para buscar un producto por su código
void buscarProducto(struct Producto inventario[], int numProductos)
{
    char codigoBuscado[20];
    printf("\nIngrese el codigo del producto a buscar: ");
    scanf("%s", codigoBuscado);

    for (int i = 0; i < numProductos; i++)
    {
        if (strcmp(inventario[i].codigo, codigoBuscado) == 0)
        {
            printf("Nombre: %s\n", inventario[i].nombre);
            printf("Codigo: %s\n", inventario[i].codigo);
            printf("Cantidad: %d\n", inventario[i].cantidad);
            printf("Precio de compra: %.2f\n", inventario[i].precioCompra);
            printf("Utilidad: %.2f\n", calcularUtilidad(inventario[i]));
            return;
        }
    }

    printf("Producto no encontrado.\n");
}

// Función para mostrar los nombres y códigos de los productos
void mostrarProductos(struct Producto inventario[], int numProductos)
{
    printf("\nLista de productos disponibles:\n");
    for (int i = 0; i < numProductos; i++)
    {
        printf("%d. Nombre: %s, Codigo: %s\n", i + 1, inventario[i].nombre, inventario[i].codigo);
    }
}

int main()
{
    struct Producto inventario[MAX_PRODUCTOS];
    int numProductos = 0;

    // Cargar el inventario desde el archivo
    numProductos = cargarInventario(inventario);

    int opcion;
    do
    {
        printf("\nMenu:\n");
        printf("1. Ingresar nuevo producto\n");
        printf("2. Buscar producto por codigo\n");
        printf("3. Mostrar nombres y codigos de productos disponibles\n");
        printf("0. Salir\n");
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            if (numProductos < MAX_PRODUCTOS)
            {
                numProductos = ingresarProducto(inventario, numProductos);
            }
            else
            {
                printf("No se pueden agregar mas productos. Limite alcanzado.\n");
            }
            break;
        case 2:
            buscarProducto(inventario, numProductos);
            break;
        case 3:
            mostrarProductos(inventario, numProductos);
            break;
        case 0:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opcion no valida. Intente de nuevo.\n");
            break;
        }
    } while (opcion != 0);

    return 0;
}
