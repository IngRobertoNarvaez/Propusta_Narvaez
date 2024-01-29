#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 50
#define MAX_USERS 100

struct User
{
    char nombredeusuario[MAX_LENGTH];
    char contraseña[MAX_LENGTH];
};

void agregarUsuario(const char *nombredeusuario, const char *contraseña)
{
    FILE *Archivo = fopen("usuarios.txt", "a");

    if (Archivo == NULL)
    {
        printf("Error al abrir el archivo.\n");
        return;
    }

    fprintf(Archivo, "%s %s\n", nombredeusuario, contraseña);

    fclose(Archivo);
}

int leerUsuarios(struct User *usuarios)
{
    FILE *Archivo = fopen("usuarios.txt", "r");

    if (Archivo == NULL)
    {
        printf("El archivo de usuarios no existe. Creando archivo...\n");
        fclose(fopen("usuarios.txt", "w"));
        return 0;
    }

    int num_usuarios = 0;

    while (fscanf(Archivo, "%s %s", usuarios[num_usuarios].nombredeusuario, usuarios[num_usuarios].contraseña) != EOF)
    {
        num_usuarios++;
    }

    fclose(Archivo);
    return num_usuarios;
}

int main()
{
    struct User usuarios[MAX_USERS];
    int num_usuarios = leerUsuarios(usuarios);

    int opcion;

    while (1)
    {
        printf("\nSeleccione una opcion:\n");
        printf("1. Ingresar\n");
        printf("2. Crear usuario\n");
        printf("3. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
        {
            char input_nombredeusuario[MAX_LENGTH];
            char input_contraseña[MAX_LENGTH];

            printf("\nIngrese su nombre de usuario: ");
            scanf("%s", input_nombredeusuario);
            printf("Ingrese su contrasena: ");
            scanf("%s", input_contraseña);

            int i;
            for (i = 0; i < num_usuarios; i++)
            {
                if (strcmp(input_nombredeusuario, usuarios[i].nombredeusuario) == 0 && strcmp(input_contraseña, usuarios[i].contraseña) == 0)
                {
                    printf("Inicio de sesion exitoso. Bienvenido, %s\n", input_nombredeusuario);

                    int opcion_despues_logeo;
                    while (1)
                    {
                        printf("\nSeleccione una opcion:\n");
                        printf("1. Realizar otra accion\n");
                        printf("2. Cerrar sesión\n");
                        printf("Opcion: ");
                        scanf("%d", &opcion_despues_logeo);

                        if (opcion_despues_logeo == 1)
                        {
                            printf("\nRealizando otra accion...\n");
                        }
                        else if (opcion_despues_logeo == 2)
                        {
                            printf("\nCerrando sesion...\n");
                            break;
                        }
                        else
                        {
                            printf("\nOpción no valida.\n");
                        }
                    }
                    break;
                }
            }
            if (i == num_usuarios)
            {
                printf("Nombre de usuario o contrasena incorrectos.\n");
            }
        }
        break;
        case 2:
        {
            char nuevo_nombredeusuario[MAX_LENGTH];
            char nueva_contraseña[MAX_LENGTH];

            printf("\nIngrese un nuevo nombre de usuario: ");
            scanf("%s", nuevo_nombredeusuario);
            printf("Ingrese una nueva contraseña: ");
            scanf("%s", nueva_contraseña);

            agregarUsuario(nuevo_nombredeusuario, nueva_contraseña);
            printf("Usuario creado con éxito.\n");

            num_usuarios = leerUsuarios(usuarios);
        }
        break;
        case 3:
            printf("\nSaliendo del programa...\n");
            return 0;
        default:
            printf("\nOpción no válida.\n");
            break;
        }
    }
}
