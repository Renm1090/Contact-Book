#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Estructura para almacenar la informacion de un contacto
struct contactos {
    char nombre[50];
    char telefono[10]; // 10 digitos para el telefono
    char correo[50];
};

typedef struct contactos Contacto; //Definimos un alias para la estructura

//Funcion para convertir una cadena a minusculas
void convertirAMinusculas(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);//convierte cada caracter a minuscula
    }
}

//Funcion para escanear el nombre del contacto
void escanearNombre(char *nombre) {
    char c;
    int i = 0;
    //Lee los caracteres hasta que el usuario precione enter
    while ((c = getchar()) != '\n') {
        nombre[i++] = c;//Almacena los carateres en el arreglo
    }
    nombre[i] = '\0';//Termina la cadena con un carater nulo
}

//Funcion para verificar si un contacto ya existe en el archivo
int verificarInexistenciaEnArchivo(char *str) {
    FILE *archivo = fopen("contactos.txt", "r");//Se abre el archivo en modo lectura
    if (archivo == NULL) {
        return 2; // Error al abrir el archivo
    }
    char linea[50];
    int encontrado = 0;

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        linea[strcspn(linea, "\n")] = 0; // Eliminar salto de línea
        if (strcmp(linea, str) == 0) { // Comparación exacta
            encontrado = 1;
            break;
        }
        fgets(linea, sizeof(linea), archivo); // Omitir teléfono
        fgets(linea, sizeof(linea), archivo); // Omitir correo
    }
    fclose(archivo);

    if (encontrado) {
        printf("Un contacto con este elemento ya existe. Ingrese 0 para intentarlo de nuevo o 1 para salir.\n");
        char opcion[10];
        scanf("%s", opcion);
        if (strcmp(opcion, "1") == 0) {
            return 0; // Salir
        }
        return 1; // Intentar de nuevo
    }

    return 2; // No encontrado
}

//funcion para validar el numero de telefono
int esTelefonoValido(char *telefono) {
    // Verifica que tenga exactamente 10 caracteres
    if (strlen(telefono) != 10) {
        return 0; // No válido
    }
    // Verifica que todos los caracteres sean dígitos
    for (int i = 0; i < 10; i++) {
        if (!isdigit(telefono[i])) {
            return 0; // No válido
        }
    }
    return 1; // Válido
}

//funcion para agregar un nuevo contacto
void agregarContacto() {
    system("cls");//se limpia la pantalla
    Contacto nuevo;//se crea una nueva variable de tipo contacto
    printf("\n\t--- AGREGAR CONTACTO ---\n");
    printf("Introduce los datos del contacto:\n");

    //bucle para ingresar el nombre
    while (1) {
        printf("Nombre: ");
        getchar(); //limpiar el buffer
        escanearNombre(nuevo.nombre);//se escanea el nombre
        convertirAMinusculas(nuevo.nombre);//se convierte a minusculas
        if (strlen(nuevo.nombre) == 0) {
            printf("El nombre no puede estar vacío. Inténtalo de nuevo.\n");
            continue;//volver a pedir el nombre
        }
        int resultado = verificarInexistenciaEnArchivo(nuevo.nombre);//verificar la existencia
        if (resultado == 0) {
            return; //salir
        } else if (resultado == 2) {
            break; //continuar
        }
    }

    //bucle para ingresar el telefono
    while (1) {
        printf("Telefono: ");
        scanf("%s", nuevo.telefono);//se escanea el telefono
        if (!esTelefonoValido(nuevo.telefono)) {
            printf("El teléfono debe tener 10 dígitos. Inténtalo de nuevo.\n");
            continue;//volver a pedir el telefono si no es valido
        }
        int resultado = verificarInexistenciaEnArchivo(nuevo.telefono);//verificaion de la exixtencia
        if (resultado == 0) {
            return; //salir
        } else if (resultado == 2) {
            break; //continuar si no se encontro
        }
    }

    //bucle para ingresar el correo
    while (1) {
        printf("Correo: ");
        scanf("%s", nuevo.correo);//se escanea el correo
        if (strstr(nuevo.correo, "@") == NULL) {
            printf("El correo debe contener un '@'. Inténtalo de nuevo.\n");
            continue;//volver a pedir el correo si no es valido
        }
        int resultado = verificarInexistenciaEnArchivo(nuevo.correo);// verificar la existencia
        if (resultado == 0) {
            return; //salir
        } else if (resultado == 2) {
            break; //continuar sib no se encontro
        }
    }

    // se abre el archivo en modo append para agragar el nuevo contacto
    FILE *archivo2 = fopen("contactos.txt", "a");
    if (archivo2 == NULL) {
        printf("Error al abrir el archivo.\n");
        return;//salir si hay un error al abrir el archivo
    }

    //se escribe los datos del nuevo contacto en el archivo
    fprintf(archivo2, "%s\n%s\n%s\n", nuevo.nombre, nuevo.telefono, nuevo.correo);
    fclose(archivo2);//se cierra el archivo
    printf("Contacto agregado exitosamente.\n");
}

//funcion para leer y mostrar todos los contactos
void leerContactos() {
    system("cls");//limpiar la pantalla
    FILE *archivo = fopen("contactos.txt", "r");//se abre el archivo en modo lectura
    if (archivo == NULL) {
        printf("No hay contactos guardados.\n");
        return;//salir si no hay contactos
    }

    printf("\n\t--- LISTA DE CONTACTOS ---\n");
    char linea[50];
    //se lee el archivo linea por linea
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        printf("Nombre: %s", linea);//se muestra el nombre
        fgets(linea, sizeof(linea), archivo);
        printf("Telefono: %s", linea);//se muestra el telefono
        fgets(linea, sizeof(linea), archivo);
        printf("Correo: %s", linea);//se muestra el correo
        printf("\n");
    }
    fclose(archivo);//se cierra el archivo :)
    getchar();// espera entrada del usuario
    getchar();// se espera otra entrada para continuar :p
}

//funcion para borrar un contacto
void borrarContacto() {
    system("cls");// se limpia la pantalla
    leerContactos();// se muetran los contactos para que el usuario pueda buscar el contacto a borrar
    printf("\nIntroduce el nombre del contacto a eliminar: ");
    char nombre[20];
    getchar();//se limpia el buffer
    escanearNombre(nombre);// se escanea el nombre del contacto a borrar
    convertirAMinusculas(nombre);//se convierte a minusculas

    FILE *archivo = fopen("contactos.txt", "r");//se abre el archivo en modo lectura :)
    FILE *temp = fopen("temp.txt", "w");// se crea un archivo temporal para guardar los contactos que no se van a borrar
    if (archivo == NULL || temp == NULL) {
        printf("Error al manejar los archivos.\n");
        return;//salir si hay un error al abrir el archivo
    }

    char linea[50];
    int encontrado = 0;//bandera para indicar que si se encontro el contacto :p

    //se lee el archivo y se copea el archivo original a el archivo temporal, omitiendo al que se desea borrar
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        if (strstr(linea, nombre) != NULL) {
            encontrado = 1;//se encontro el contacto a borrar
            fgets(linea, sizeof(linea), archivo);//omitir telefono
            fgets(linea, sizeof(linea), archivo);//omitir correo
        } else {// si no se encontro el contacto escribirlo en el archivo temporal
            fprintf(temp, "%s", linea);//escribe el nombre
            if (fgets(linea, sizeof(linea), archivo) != NULL) {
                fprintf(temp, "%s", linea);//escribe el telefono
            }
            if (fgets(linea, sizeof(linea), archivo) != NULL) {
                fprintf(temp, "%s", linea);//escribe el correo
            }
        }
    }

    fclose(archivo);//se cierra el archivo original :)
    fclose(temp);//se cierra el archivo temporal :p

    //se remplaza el archivo original con el archivo temporal
    remove("contactos.txt");//elemina el archivo original
    rename("temp.txt", "contactos.txt");//se renombra el archivo temporal

    //se le informa al usuario que el contacto fue encontrado y eleminado
    if (encontrado) {
        printf("Contacto eliminado exitosamente.\n");
    } else {
        printf("Contacto no encontrado.\n");
    }
}

//funcion para buscar un contacto
//funcion para buscar un contacto
void buscarContacto() {
    system("cls");
    printf("\n\t--- BUSCAR CONTACTO ---\n");
    printf("Introduce el nombre del contacto a buscar:\n");
    char nombre[50];
    getchar(); // Limpiar el buffer
    escanearNombre(nombre); // Usar la función escanearNombre para permitir espacios
    convertirAMinusculas(nombre); // Convertir el nombre buscado a minúsculas

    FILE *archivo = fopen("contactos.txt", "r");
    if (archivo == NULL) {
        printf("No hay contactos guardados.\n");
        return;
    }

    char linea[50];
    int encontrado = 0;
    system("cls");
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        char nombreContacto[50];
        strcpy(nombreContacto, linea); // Copiar el nombre del contacto
        convertirAMinusculas(nombreContacto); // Convertir el nombre del contacto a minúsculas

        if (strstr(nombreContacto, nombre) != NULL) { // Comparar sin importar mayúsculas/minúsculas
            printf("Contacto encontrado:\n");
            printf("Nombre: %s", linea);
            fgets(linea, sizeof(linea), archivo);
            printf("Telefono: %s", linea);
            fgets(linea, sizeof(linea), archivo);
            printf("Correo: %s", linea);
            encontrado = 1;
            break;
        }
    }

    fclose(archivo);

    if (!encontrado) {
        printf("Contacto no encontrado.\n");
    }

    getchar(); // Esperar entrada del usuario
}

int main() {
    int opcion;//variable para almacenar la opcion del usuario

    //menu de la agenda de contactos
    do {
        system("cls");//se limpia la pantalla
        printf("\n\t--- AGENDA DE CONTACTOS ---\n");
        printf("1. Agregar contacto\n");
        printf("2. Ver contactos\n");
        printf("3. Eliminar contacto\n");
        printf("4. Buscar contacto\n");
        printf("5. Salir\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);//leer la opcion del usuario

        switch (opcion) {
            case 1:
                agregarContacto();//agregar un contacto nuevo
                break;
            case 2:
                leerContactos();//leer y mostrar todos los contactos
                break;
            case 3:
                borrarContacto();//eleminar un contacto
                break;
            case 4:
                buscarContacto();// buscar un contacto
                break;
            case 5:
                system("cls");//se limpia la pantalla
                printf("Saliendo de la agenda.\n");//un mensaje de salida
                break;
            default:
                printf("Opcion no valida. Intenta de nuevo.\n");//mensaje de error por si la opcion no es valida
        }
    } while (opcion != 5);//repetir hasta que el usuario elija salir

    return 0;//finalizar el programa
}