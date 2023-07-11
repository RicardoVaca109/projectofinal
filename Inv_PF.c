#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
int abrirArchivo(const char *nombreArchivo);
int crearArchivo();
void LeerDocumento();
void inicializarVariables();
void guardarnom();
void sobreescribirArchivo();
void imprimirProductos();
void leerProducto();
void modificarProducto();
void eliminarProducto();
void siguiente();
int imprimirMenu();
int totalProductos;
int identificacion[10];
char nombre[10][10];
char descripcion[10][15];
float cantidad[10];
char unidades[10][10];
float precio[10];
float preciot[10];
char nom[] = "Nombres";
int main()
{
    int ops, flag = 1;
    do
    {
        if (abrirArchivo(nom))
        {
            LeerDocumento();
            while (flag)
            {
                system("cls");
                ops = imprimirMenu();
                switch (ops)
                {
                case 1:
                    system("cls");
                    imprimirProductos();
                    break;
                case 2:
                    system("cls");
                    leerProducto();
                    break;
                case 3:
                    modificarProducto();
                    break;
                case 4:
                    eliminarProducto();
                    break;
                case 5:
                    flag = 0;
                    break;
                default:
                    system("cls");
                    printf("Digite una opcion valida\n");
                    siguiente();
                    break;
                }
            }
            printf("Gracias por utilizar el sistema de inventarios\n");
            siguiente();
        }
        else
        {
            totalProductos = 5;
            inicializarVariables();
            guardarnom();
        }
    } while (flag);
    return 0;
}
void inicializarVariables()
{
    int identificacion1[10] = {1101, 2702, 4003, 5234, 5212};
    char nombre1[10][10] = {{"Leche"}, {"Cafe"}, {"Cacao"}, {"Azucar"}, {"Azucar"}};
    char descripcion1[10][15] = {{"Lacteo"}, {"Polvo"}, {"Polvo"}, {"Blanca"}, {"Morena"}};
    float cantidad1[10] = {10, 15, 12, 10, 5};
    char unidades1[10][10] = {{"Litros"}, {"Bolsa"}, {"Bolsa"}, {"Kilos"}, {"Kilos"}};
    float precio1[10] = {2.5, 5, 4.5, 1.5, 2};
    for (int i = 0; i < totalProductos; i++)
    {
        identificacion[i] = identificacion1[i];
        strcpy(nombre[i], nombre1[i]);
        strcpy(descripcion[i], descripcion1[i]);
        cantidad[i] = cantidad1[i];
        strcpy(unidades[i], unidades1[i]);
        precio[i] = precio1[i];
        preciot[i] = cantidad1[i] * precio1[i];
    }
    crearArchivo();
}
int abrirArchivo(const char *nombreArchivo)
{
    FILE *archivo;
    archivo = fopen(nombreArchivo, "r+");
    if (archivo == NULL)
    {
        printf("No se puede abrir el archivo");
        return 0;
    }
    fclose(archivo);
    return 1;
}
int crearArchivo()
{
    FILE *archivo;
    archivo = fopen(nom, "w+");
    if (archivo == NULL)
    {
        printf("No se puede crear el archivo");
        return 0;
    }
    fclose(archivo);
    return 1;
}
void sobreescribirArchivo()
{
    FILE *archivo;
    archivo = fopen(nom, "w+");
    if (archivo == NULL)
    {
        printf("No se puede crear el archivo");
    }
    else
    {
        fprintf(archivo, "%d\n", totalProductos);
        for (int i = 0; i < totalProductos; i++)
        {
            preciot[i] = cantidad[i] * precio[i];
            fprintf(archivo, "%i %s %s %f %s %.2f %.2f\n", identificacion[i], nombre[i], descripcion[i],
                    cantidad[i], unidades[i], precio[i], preciot[i]);
        }
        fclose(archivo);
    }
}
void guardarnom()
{
    FILE *archivo;
    archivo = fopen(nom, "r+");
    if (archivo == NULL)
    {
        printf("No se puede abrir el archivo");
    }
    else
    {
        fprintf(archivo, "%d\n", totalProductos);
        for (int i = 0; i < totalProductos; i++)
        {
            preciot[i] = cantidad[i] * precio[i];
            fprintf(archivo, "%i %s %s %f %s %.2f %.2f\n", identificacion[i], nombre[i], descripcion[i],
                    cantidad[i], unidades[i], precio[i], preciot[i]);
        }
        fclose(archivo);
    }
}
int imprimirMenu()
{
    int ops;
    printf("---------------Bienvenido---------------\n");
    printf("Men%c de la herramienta de inventario\n", 163);
    printf("Seleccione una opci%cn: \n", 162);
    printf("\t1) Ver productos\n");
    printf("\t2) Ingreso de producto\n");
    printf("\t3) Modificar productos\n");
    printf("\t4) Eliminar producto\n");
    printf("\t5) Salir\n");
    printf("Selecione una opcion: ");
    scanf("%d", &ops);
    return ops;
}
void modificarProducto()
{
    int id;
    printf("---- Modificar Producto ----\n");
    printf("Ingrese el ID del producto a modificar: ");
    scanf("%i", &id);

    int encontrado = 0;
    for (int i = 0; i < totalProductos; i++)
    {
        if (identificacion[i] == id)
        {
            encontrado = 1;

            printf("Nuevo nombre: ");
            scanf(" %s", nombre[i]);
            printf("Nueva Descripcion: ");
            scanf(" %s", descripcion[i]);
            printf("Nueva Cantidad: ");
            scanf("%f", &cantidad[i]);
            printf("Nuevas Unidades:");
            scanf(" %s", unidades[i]);
            printf("Nuevo Precio: ");
            scanf("%f", &precio[i]);

            preciot[i] = cantidad[i] * precio[i];
            printf("Producto modificado correctamente.\n");
            sobreescribirArchivo();
            break;
        }
    }
    if (!encontrado)
    {
        printf("No se encontró ningún producto con el ID especificado.\n");
    }
    guardarnom();
    siguiente();
}
void eliminarProducto()
{
    int id;
    printf("---- Eliminar Producto ----\n");
    printf("Ingrese el ID del producto a eliminar: ");
    scanf("%d", &id);

    int encontrado = 0;

    for (int i = 0; i < totalProductos; i++)
    {
        if (identificacion[i] == id)
        {
            encontrado = 1;

            for (int j = i; j < totalProductos - 1; j++)
            {
                identificacion[j] = identificacion[j + 1];
                strcpy(nombre[j], nombre[j + 1]);
                strcpy(descripcion[j], descripcion[j + 1]);
                cantidad[j] = cantidad[j + 1];
                strcpy(unidades[j], unidades[j + 1]);
                precio[j] = precio[j + 1];
                preciot[j] = preciot[j + 1];
            }

            totalProductos--;
            break;
        }
    }

    if (encontrado)
    {
        printf("Producto eliminado correctamente.\n");
        sobreescribirArchivo();
    }
    else
    {
        printf("No se encontró ningún producto con el ID especificado.\n");
    }
    sobreescribirArchivo();
    siguiente();
}
void siguiente()
{
    printf("Presione una tecla para continuar:");
    getch();
}
void leerProducto()
{
    printf("---- Ingresar Producto ----\n");
    printf("Ingrese el ID del producto: ");
    int id;
    scanf("%d", &id);
    for (int i = 0; i < totalProductos; i++)
    {
        if (identificacion[i] == id)
        {
            printf("El ID del producto ya existe. No se puede agregar.\n");
            siguiente();
            return;
        }
    }
    identificacion[totalProductos] = id;
    printf("Nombre: ");
    scanf(" %s", nombre[totalProductos]);
    printf("Descripcion: ");
    scanf(" %s", descripcion[totalProductos]);
    printf("Cantidad: ");
    scanf("%f", &cantidad[totalProductos]);
    printf("Unidades: ");
    scanf(" %s", unidades[totalProductos]);
    printf("Precio: ");
    scanf("%f", &precio[totalProductos]);
    preciot[totalProductos] = cantidad[totalProductos] * precio[totalProductos];
    totalProductos++;
    guardarnom();
    printf("Producto ingresado correctamente.\n");
    siguiente();
}
void LeerDocumento()
{
    FILE *archivo;
    archivo = fopen(nom, "r+");
    fscanf(archivo, "%d", &totalProductos);
    printf("Elementos en sistema : %d\n", totalProductos);
    for (int i = 0; i < totalProductos; i++)
    {
        fscanf(archivo, "%i %s %s %f %s %f %f", &identificacion[i], nombre[i], descripcion[i],
               &cantidad[i], unidades[i], &precio[i], &preciot[i]);
    }
    fclose(archivo);
}
void imprimirProductos()
{
    LeerDocumento();
    printf("ID\t Nombre\t Descripcion\t Cantidad\t Unidades\t Precio\t $Total\n");
    for (int j = 0; j < totalProductos; j++)
    {
        printf("%i\t %s\t %s\t\t %.2f\t\t %s\t\t %.2f$\t %.2f$\n", identificacion[j], nombre[j], descripcion[j],
               cantidad[j], unidades[j], precio[j], preciot[j]);
    }
    siguiente();
}