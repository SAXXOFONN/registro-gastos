#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Estructura para representar un gasto
struct Gasto {
    string usuario;
    string descripcion;
    double monto;
    string fecha;
};

// Estructura para representar un usuario
struct Usuario {
    string nombre;
    string contrasena;
};

// Base de datos en memoria para almacenar los usuarios y los gastos
vector<Usuario> usuarios;
vector<Gasto> gastos;

// Función para cargar usuarios desde un archivo
void cargarUsuarios() {
    ifstream archivo("usuarios.txt");
    if (archivo.is_open()) {
        Usuario usuario;
        while (archivo >> usuario.nombre >> usuario.contrasena) {
            usuarios.push_back(usuario);
        }
        archivo.close();
    }
}

// Función para guardar usuarios en un archivo
void guardarUsuarios() {
    ofstream archivo("usuarios.txt");
    if (archivo.is_open()) {
        for (const Usuario& usuario : usuarios) {
            archivo << usuario.nombre << " " << usuario.contrasena << endl;
        }
        archivo.close();
    }
}

// Función para cargar gastos desde un archivo
void cargarGastos() {
    ifstream archivo("gastos.txt");
    if (archivo.is_open()) {
        Gasto gasto;
        while (archivo >> gasto.usuario >> gasto.descripcion >> gasto.monto >> gasto.fecha) {
            gastos.push_back(gasto);
        }
        archivo.close();
    }
}

// Función para guardar gastos en un archivo
void guardarGastos() {
    ofstream archivo("gastos.txt");
    if (archivo.is_open()) {
        for (const Gasto& gasto : gastos) {
            archivo << gasto.usuario << " " << gasto.descripcion << " " << gasto.monto << " " << gasto.fecha << endl;
        }
        archivo.close();
    }
}

// Función para registrar un usuario
void registrarUsuario(const string& nombre, const string& contrasena) {
    Usuario usuario = { nombre, contrasena };
    usuarios.push_back(usuario);
    cout << "Usuario registrado con éxito." << endl;
    guardarUsuarios();  // Guardar usuarios después de cada registro
}

// Función para registrar un gasto
void registrarGasto(const string& usuario, const string& descripcion, double monto, const string& fecha) {
    Gasto gasto = { usuario, descripcion, monto, fecha };
    gastos.push_back(gasto);
    cout << "Gasto registrado con éxito." << endl;
    guardarGastos();  // Guardar gastos después de cada registro
}

// Función para ver gastos
void verGastos(const string& usuario) {
    cout << "Gastos de " << usuario << ":" << endl;
    for (const Gasto& gasto : gastos) {
        if (gasto.usuario == usuario) {
            cout << "Descripción: " << gasto.descripcion << ", Monto: " << gasto.monto << ", Fecha: " << gasto.fecha << endl;
        }
    }
}

// Función para calcular el promedio de los gastos de un usuario
void calcularPromedio(const string& usuario) {
    double total = 0.0;
    int cantidadGastos = 0;

    for (const Gasto& gasto : gastos) {
        if (gasto.usuario == usuario) {
            total += gasto.monto;
            cantidadGastos++;
        }
    }

    if (cantidadGastos > 0) {
        double promedio = total / cantidadGastos;
        cout << "El promedio de gastos de " << usuario << " es: $" << fixed << setprecision(2) << promedio << "\n";
    }
    else {
        cout << "No hay gastos registrados para " << usuario << "\n";
    }
}

// Función para generar una factura y guardarla en un archivo
void generarFactura(const string& usuario) {
    double total = 0.0;
    string nombreArchivo = "factura_" + usuario + ".txt";

    ofstream facturaArchivo(nombreArchivo);

    facturaArchivo << "\n=============================\n";
    facturaArchivo << "=         Factura           =\n";
    facturaArchivo << "=============================\n";
    facturaArchivo << "Usuario: " << usuario << "\n";
    facturaArchivo << "=============================\n";

    for (const Gasto& gasto : gastos) {
        if (gasto.usuario == usuario) {
            facturaArchivo << "Descripción: " << setw(20) << left << gasto.descripcion;
            facturaArchivo << "Monto: $" << setw(10) << right << fixed << setprecision(2) << gasto.monto << "\n";
            total += gasto.monto;
        }
    }

    facturaArchivo << "=============================\n";
    facturaArchivo << "Total: $" << setw(10) << right << fixed << setprecision(2) << total << "\n\n";

    facturaArchivo.close();

    cout << "Factura generada con éxito. Se ha guardado en el archivo: " << nombreArchivo << "\n";
}

// Función para mostrar la interfaz principal
void mostrarInterfaz(const string& usuario) {
    cout << "\n=============================\n";
    cout << "=          Inició           =\n";
    cout << "=============================\n";

    cout << "\nBienvenido, " << usuario << "!\n";

    cout << "=============================\n";
    cout << "=          Opciones         =\n";
    cout << "=============================\n";
    cout << "1. Registrar Gasto\n";
    cout << "2. Ver Gastos\n";
    cout << "3. Generar Factura\n";
    cout << "4. Calcular Promedio de Gastos\n";
    cout << "5. Salir\n";
}

// Función para el menú principal
void menuPrincipal(const string& usuario) {
    while (true) {
        mostrarInterfaz(usuario);

        int opcion;
        cout << "Ingrese el número de la opción deseada: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            string descripcion;
            double monto;
            string fecha;

            cout << "Ingrese la descripción del gasto: ";
            cin.ignore();
            getline(cin, descripcion);

            cout << "Ingrese el monto del gasto: ";
            cin >> monto;

            cout << "Ingrese la fecha del gasto (YYYY-MM-DD): ";
            cin >> fecha;

            registrarGasto(usuario, descripcion, monto, fecha);
            break;
        }
        case 2:
            verGastos(usuario);
            break;
        case 3:
            generarFactura(usuario);
            break;
        case 4:
            calcularPromedio(usuario);
            break;
        case 5:
            cout << "Saliendo...\n";
            guardarUsuarios();
            guardarGastos();
            exit(0);
        default:
            cout << "Opción no válida. Por favor, ingrese un número válido.\n";
        }
    }
}

// Función para el menú de registro
void menuRegistro() {
    string nombre, contrasena;
    cout << "Ingrese un nombre de usuario: ";
    cin >> nombre;

    // Verificar si el nombre de usuario ya existe
    for (const Usuario& usuario : usuarios) {
        if (usuario.nombre == nombre) {
            cout << "El nombre de usuario ya existe. Por favor, elija otro.\n";
            return;
        }
    }

    cout << "Ingrese una contraseña: ";
    cin >> contrasena;

    registrarUsuario(nombre, contrasena);
}

// Función para iniciar sesión
string iniciarSesion() {
    while (true) {
        cout << "\n1. Iniciar Sesión\n";
        cout << "2. Registrarse\n";
        cout << "3. Salir\n";

        int opcion;
        cout << "Ingrese el número de la opción deseada: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            string nombre, contrasena;
            cout << "Ingrese su nombre de usuario: ";
            cin >> nombre;

            cout << "Ingrese su contraseña: ";
            cin >> contrasena;

            // Verificar credenciales
            for (const Usuario& usuario : usuarios) {
                if (usuario.nombre == nombre && usuario.contrasena == contrasena) {
                    cout << "Bienvenido, " << nombre << "!\n";
                    return nombre;
                }
            }
            cout << "Nombre de usuario o contraseña incorrectos. Inténtelo nuevamente.\n";
            break;
        }
        case 2:
            menuRegistro();
            break;
        case 3:
            cout << "Saliendo...\n";
            guardarUsuarios();
            guardarGastos();
            exit(0);
        default:
            cout << "Opción no válida. Por favor, ingrese un número válido.\n";
        }
    }
}

// Bucle principal
int main() {
    cargarUsuarios();
    cargarGastos();

    while (true) {
        string usuarioActual = iniciarSesion();
        menuPrincipal(usuarioActual);
    }

    return 0;
}