/* 
Hilda Beltrán y Silvana Ruiz
A01251916 y A01252346
TC1033 Pensamiento Computacional Orientado a Objetos
03/Dic/2020
*/

#include <iostream> 
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>

using namespace std;

int precioFinal = 0;

class Factura{
    private:
        string fecha;
        string claveF;
        string vendedor;
        string cliente;
        string articulos;
        string total;
    public:
        string get_Fecha(){
            return fecha;
        }
        string get_ClaveF(){
            return claveF;
        }
        string get_Vendedor(){
            return vendedor;
        }
        string get_Cliente(){
            return cliente;
        }
        string get_Articulos(){
            return articulos;
        }
        string get_Total(){
            return total;
        }
        void get_Datos(string f, string c, string v, string cl, string a, string t){
            fecha = f;
            claveF = c;
            vendedor = v;
            cliente = cl;
            articulos = a;
            total = t;
        }
};
class Inventario{
    private:
        string claveI;
        string descripcion;
        string precio;
        string tipo;
        string existencia;
        string vendido;
    public:
        string get_ClaveI(){
            return claveI;
        }
        string get_Descripcion(){
            return descripcion;
        }
        string get_Precio(){
            return precio;
        }
        string get_Tipo(){
            return tipo;
        }
        string get_Existencia(){
            return existencia;
        }
        string get_Vendido(){
            return vendido;
        }
        void get_Datos(string c, string d, string p, string t, string e, string v){
            claveI = c;
            descripcion = d;
            precio = p;
            tipo = t;
            existencia = e;
            vendido = v;
        }
};
class Cliente{
    private:
        string claveC;
        string nombre;
        string direccion;
        string telefono;
        string compras;
    public:
        string get_ClaveC(){
            return claveC;
        }
        string get_Nombre(){
            return nombre;
        }
        string get_Direccion(){
            return direccion;
        }
        string get_Telefono(){
            return telefono;
        }
        string get_Compras(){
            return compras;
        }
        void get_Datos(string c, string n, string d, string t, string co){
            claveC = c;
            nombre = n;
            direccion = d;
            telefono = t;
            compras = co;
        }
};
class Vendedor{
    private:
        string claveV;
        string nombre;
        string comision;
        string ventas;
    public:
        string get_ClaveV(){
            return claveV;
        }
        string get_Nombre(){
            return nombre;
        }
        string get_Comision(){
            return comision;
        }
        string get_Ventas(){
            return ventas;
        }
        void get_Datos(string c, string n, string co, string v){
            claveV = c;
            nombre = n;
            comision = co;
            ventas = v;
        }
};

//Leer archivos inventario, clientes, vendedores
void leeArchivos(vector <Inventario> &producto, vector <Cliente> &cliente, vector <Vendedor> &vendedor){
    //Abrir y guardar datos archivo inventario
    string strInventario;
    stringstream ss;
    string claveI;
    string descripcion;
    string precio;
    string tipo;
    string existencia;
    string vendido;

    ifstream fileinventario("inventario");
    if(!fileinventario){
        cerr << "No se encontró el archivo inventario.csv" << endl;
        exit(1);
    }
    Inventario datosInv;
    getline(fileinventario, strInventario);
    while(getline(fileinventario, strInventario)){
        ss.clear();
        ss << strInventario;
        getline(ss, claveI, ',');
        getline(ss, descripcion, ',');
        getline(ss, precio, ',');
        getline(ss, tipo, ',');
        getline(ss, existencia,  ',');
        getline(ss, vendido, ',');
        datosInv.get_Datos(claveI, descripcion, precio, tipo, existencia, vendido);
        producto.push_back(datosInv);
    }
    fileinventario.close();

    // Abrir y guardar datos archivo vendedores
    string strVendedor;
    string claveV;
    string nombreV;
    string comision;
    string ventas;
    ifstream filevendedores("vendedores");
    if(!filevendedores){
        cerr << "No se encontró el archivo vendedores.csv" << endl;
        exit(1);
    }
    Vendedor datosVend;
    getline(filevendedores, strVendedor);
    while(getline(filevendedores, strVendedor)){
        ss.clear();
        ss << strVendedor;
        getline(ss, claveV, ',');
        getline(ss, nombreV, ',');
        getline(ss, comision, ',');
        getline(ss, ventas, ',');
        datosVend.get_Datos(claveV, nombreV, comision, ventas);
        vendedor.push_back(datosVend);
    }
    filevendedores.close();

    // Abrir y guardar datos archivo clientes
    string strCliente;
    string claveC;
    string nombreC;
    string direccion;
    string telefono;
    string compras;

    ifstream fileclientes("clientes");
    if(!fileclientes){
        cerr << "No se encontró el archivo clientes.csv" << endl;
        exit(1);
    }

    Cliente datosCli;
    getline(fileclientes, strCliente);
    while(getline(fileclientes, strCliente)){
        ss.clear();
        ss << strCliente;
        getline(ss, claveC, ',');
        getline(ss, nombreC, ',');
        getline(ss, direccion, ',');
        getline(ss, telefono, ',');
        getline(ss, compras, ',');
        datosCli.get_Datos(claveC, nombreC, direccion, telefono, compras);
        cliente.push_back(datosCli);
    }
    fileclientes.close();
}

//Escribir datos en el archivo facturas, con método append
void escribir_Factura(vector <Inventario> &producto, vector <Cliente> &cliente, vector <Vendedor> &vendedor, string claveF, string fecha, int contCli, int contVend, int j, int Articulos[]){
    ofstream fileescfacturas("facturas", ios::app);
    fileescfacturas << endl << fecha << ',' << claveF << ',' << vendedor[contVend].get_ClaveV() << 
    ',' << cliente[contCli].get_ClaveC() << ',';
    for (int i = 0; i < j; i++){
        int x = Articulos[i];
        fileescfacturas << producto[x].get_ClaveI() << ',';
    }
    fileescfacturas << precioFinal;
    fileescfacturas.close();

    ofstream filevendnuevo("vendedores", ios::trunc);
    filevendnuevo << "Clave,nombre,comision,ventas" << endl;

    for (int i = 0; i < vendedor.size(); i++){
        if(vendedor[contVend].get_ClaveV() == vendedor[i].get_ClaveV()){
            filevendnuevo << vendedor[i].get_ClaveV() << ',' << vendedor[i].get_Nombre() <<
            ',' << vendedor[i].get_Comision() << ',' << (stoi(vendedor[i].get_Ventas()) + j) << endl;
        }
        else{
            filevendnuevo << vendedor[i].get_ClaveV() << ',' << vendedor[i].get_Nombre() <<
            ',' << vendedor[i].get_Comision() << ',' << vendedor[i].get_Ventas() << endl;
        }
    }
    filevendnuevo.close();

    ofstream fileclinuevo("clientes", ios::trunc);
    fileclinuevo << "Clave,nombre,direccion,telefono,compras" << endl;

    for (int i = 0; i < cliente.size(); i++){
        if(cliente[contCli].get_ClaveC() == cliente[i].get_ClaveC()){
            fileclinuevo << cliente[i].get_ClaveC() << ',' << cliente[i].get_Nombre() << ',' <<
            cliente[i].get_Direccion() << ',' << cliente[i].get_Telefono() << ',' <<
            (stoi(cliente[i].get_Compras()) + j) << endl;
        }
        else{
            fileclinuevo << cliente[i].get_ClaveC() << ',' << cliente[i].get_Nombre() << ',' <<
            cliente[i].get_Direccion() << ',' << cliente[i].get_Telefono() << ',' <<
            cliente[i].get_Compras() << endl;
        }
    }
    fileclinuevo.close();
}

//Obtener clave de vendedor, cliente, y articulos
void venderArticulos(vector <Inventario> &producto, vector <Cliente> &cliente, vector <Vendedor> &vendedor){
    cout << endl << "Clave del vendedor: ";
    string claveV;
    cin >> claveV;
    cout << endl << "Clave del cliente: ";
    string claveC;
    cin >> claveC;
    cout << endl << "Clave de factura: ";
    string claveF;
    cin >> claveF;
    cout << endl << "Fecha (mmddyy): ";
    string fecha;
    cin >> fecha;

    cout << endl;

    int Articulos[100];
    int j = 0;
    while(true){
        cout << "Clave de artículo: ";
        string claveI;
        cin >> claveI;
        for (int i = 0; i < producto.size(); i++){
            if (producto[i].get_ClaveI() == claveI){
                Articulos[j] = i;
                j++;
            }
            else{continue;}
        }
        if (claveI == "n"){cout << endl; break;}
    }

    cout << "Fecha: " << fecha << endl << "Clave factura: " << claveF << endl;
    int contVend;
    for(int i = 0; i < vendedor.size(); i++){
        if (vendedor[i].get_ClaveV() == claveV){
            cout << "Vendedor: " << vendedor[i].get_ClaveV() << ", " << vendedor[i].get_Nombre() << endl;
            contVend = i;
        }
        else{continue;}
    }
    int contCli;
    for(int i = 0; i < cliente.size(); i++){
        if (cliente[i].get_ClaveC() == claveC){
            cout << "Cliente: " << cliente[i].get_ClaveC() << ", " << cliente[i].get_Nombre() << endl;
            contCli = i;
        }
        else{continue;}
    }
    cout << endl << "Productos" << endl;
    for (int i = 0; i < j; i++){
        int x = Articulos[i];
        cout << producto[x].get_ClaveI() << ", " << producto[x].get_Descripcion() <<
        ", " << producto[x].get_Precio() << endl;
        precioFinal = precioFinal + stoi(producto[x].get_Precio());
    }
    cout << endl << "Precio Total: " << precioFinal << endl;
    escribir_Factura(producto, cliente, vendedor, claveF, fecha, contCli, contVend, j, Articulos);
}

//Leer archivo de facturas y desplegar la factura solicitada
void buscaFactura(vector <Factura> &factura, vector <Inventario> &producto, vector <Cliente> &cliente, vector <Vendedor> &vendedor, string clave){
    stringstream ss;
    string fecha;
    string claveF;
    string vendedorFact;
    string clienteFact;
    string articulos;
    string total;
    string strFact;

    ifstream filebusca("facturas");
    if(!filebusca){
        cerr << "No se encontró el archivo facturas" << endl;
        exit(1);
    }

    Factura datosFact;
    getline(filebusca, strFact);
    while(getline(filebusca, strFact)){
        if(strFact.find(clave) != string::npos){
            ss.clear();
            ss << strFact;
            getline(ss, fecha, ',');
            getline(ss, claveF, ',');
            getline(ss, vendedorFact, ',');
            getline(ss, clienteFact, ',');
            getline(ss, articulos, ',');
            getline(ss, total, ',');
            datosFact.get_Datos(fecha, claveF, vendedorFact, clienteFact, articulos, total);
            factura.push_back(datosFact);
        }
    }
    filebusca.close();


    for(int i = 0; i < 1; i++){
        cout << endl << clave << endl << "Fecha: " << factura[i].get_Fecha() << endl;
        for(int j = 0; j < vendedor.size(); j++){
            if(factura[0].get_Vendedor() == vendedor[j].get_ClaveV()){
                cout << "Vendedor: " << vendedor[j].get_ClaveV() << ", " <<
                vendedor[j].get_Nombre() << endl;
            }
        }
        for(int j = 0; j < cliente.size(); j++){
            if(factura[0].get_Cliente() == cliente[j].get_ClaveC()){
                cout << "Cliente: " << cliente[j].get_ClaveC() << ", " <<
                cliente[j].get_Nombre() << endl; 
            }
        }
        for(int j = 0; j < producto.size(); j++){
            if(factura[0].get_Articulos() == producto[j].get_ClaveI()){
                cout << "Producto: " << producto[j].get_ClaveI() << ", " <<
                producto[j].get_Descripcion() << ", " << producto[j].get_Precio() << endl;
            }
        }
        cout << "Total: " << factura[i].get_Total() << endl;
    }

}

//Leer el atributo ventas del vector vendedor, compararlos y decidir cuál es el mayor y cuál el menor
void mejorPeorVendedor(vector <Vendedor> &vendedor){
    int num = 0;
    int x = 0;
    for(int i = 0; i < vendedor.size(); i++){
        int num2 = stoi(vendedor[i].get_Ventas());
        if(num2 > num){
            num = num2;
            x = i;
        }
    }
    cout << "El mejor vendedor es: " << vendedor[x].get_ClaveV() << ", " << vendedor[x].get_Nombre() <<
    ", " << vendedor[x].get_Comision() << ", con " << vendedor[x].get_Ventas() << " ventas" << endl << endl;

    int num1 = 100000;
    int y = 0;
    for(int i = 0; i < vendedor.size(); i++){
        int num3 = stoi(vendedor[i].get_Ventas());
        if(num3 < num1){
            num1 = num3;
            y = i;
        }
    }
    cout << "El peor vendedor es: " << vendedor[y].get_ClaveV() << ", " << vendedor[y].get_Nombre() <<
    ", " << vendedor[y].get_Comision() << ", con " << vendedor[y].get_Ventas() << " ventas" << endl;
}

//Leer el atributo compras del vector cliente, compararlos y decidir cuál es el mayor y cuál el menor
void mejorPeorCliente(vector <Cliente> &cliente){
    int num = 0;

    int x = 0;
    for(int i = 0; i < cliente.size(); i++){
        int num2 = stoi(cliente[i].get_Compras());
        if(num2 > num){
            num = num2;
            x = i;
        }
    }
    cout << "El mejor cliente es: " << cliente[x].get_ClaveC() << ", " << cliente[x].get_Nombre() <<
    ", " << cliente[x].get_Direccion() << ", con " << cliente[x].get_Compras() << " compras" << endl << endl;

    int num1 = 100000;
    int y = 0;
    for(int i = 0; i < cliente.size(); i++){
        int num3 = stoi(cliente[i].get_Compras());
        if(num3 < num1){
            num1 = num3;
            y = i;
        }
    }
    cout << "El peor cliente es: " << cliente[y].get_ClaveC() << ", " << cliente[y].get_Nombre() <<
    ", " << cliente[y].get_Direccion() << ", con " << cliente[y].get_Compras() << " compras" << endl;
}

//Leer el atributo vendido del vector producto, compararlos y decidir cuál es el mayor y cuál es el menor
void mejorPeorArticulo(vector <Inventario> &producto){
    int num = 0;

    int x = 0;
    for(int i = 0; i < producto.size(); i++){
        int num2 = stoi(producto[i].get_Vendido());
        if(num2 > num){
            num = num2;
            x = i;
        }
    }
    cout << "El artículo más vendido es: " << producto[x].get_ClaveI() << ", " << producto[x].get_Descripcion() <<
    ", " << producto[x].get_Precio() << ", " << producto[x].get_Tipo() << ", vendido " << producto[x].get_Vendido() <<
    " veces" << endl;

    int num1 = 100000;
    int y = 0;
    for(int i = 0; i < producto.size(); i++){
        int num3 = stoi(producto[i].get_Vendido());
        if(num3 < num1){
            num1 = num3;
            y = i;
        }
    }
    cout << "El artículo menos vendido es: " << producto[y].get_ClaveI() << ", " << producto[y].get_Descripcion() <<
    ", " << producto[y].get_Precio() << ", " << producto[y].get_Tipo() << ", vendido " << producto[y].get_Vendido() <<
    " veces" << endl;
}

//Leer el archivo de facturas y desplegar las facturas de la fecha solicitada
void buscaFacturaFecha(string fechaind, vector <Factura> &factura, vector <Inventario> &producto, vector <Vendedor> &vendedor, vector <Cliente> &cliente){
    stringstream ss;
    string fecha;
    string claveF;
    string vendedorFact;
    string clienteFact;
    string articulos;
    string total;
    string strFact;

    ifstream filebusca("facturas");
    if(!filebusca){
        cerr << "No se encontró el archivo facturas" << endl;
        exit(1);
    }

    Factura datosFact;
    getline(filebusca, strFact);
    while(getline(filebusca, strFact)){
        if(strFact.find(fechaind) != string::npos){
            ss.clear();
            ss << strFact;
            getline(ss, fecha, ',');
            getline(ss, claveF, ',');
            getline(ss, vendedorFact, ',');
            getline(ss, clienteFact, ',');
            getline(ss, articulos, ',');
            getline(ss, total, ',');
            datosFact.get_Datos(fecha, claveF, vendedorFact, clienteFact, articulos, total);
            factura.push_back(datosFact);
        }
    }
    filebusca.close();


    for(int i = 0; i < factura.size(); i++){
        cout << endl << fechaind << endl << "Clave Factura: " << factura[i].get_ClaveF() << endl;
        for(int j = 0; j < vendedor.size(); j++){
            if(factura[0].get_Vendedor() == vendedor[j].get_ClaveV()){
                cout << "Vendedor: " << vendedor[j].get_ClaveV() << ", " <<
                vendedor[j].get_Nombre() << endl;
            }
        }
        for(int j = 0; j < cliente.size(); j++){
            if(factura[0].get_Cliente() == cliente[j].get_ClaveC()){
                cout << "Cliente: " << cliente[j].get_ClaveC() << ", " <<
                cliente[j].get_Nombre() << endl; 
            }
        }
        for(int j = 0; j < producto.size(); j++){
            if(factura[0].get_Articulos() == producto[j].get_ClaveI()){
                cout << "Producto: " << producto[j].get_ClaveI() << ", " <<
                producto[j].get_Descripcion() << ", " << producto[j].get_Precio() << endl;
            }
        }
        cout << "Total: " << factura[i].get_Total() << endl;
    }
}

int main(){
    vector <Factura> factura;
    vector <Inventario> producto;
    vector <Cliente> cliente;
    vector <Vendedor> vendedor;

    while(true){
        precioFinal = 0;
        factura.clear();
        producto.clear();
        cliente.clear();
        vendedor.clear();
        cout << "------------------------------------------" << endl << "Bienvenido a Refaccionaria On The Go" << endl << endl;
        cout << endl << "Seleccione la opción de la operación que desea llevar a cabo" <<
        endl << endl << "\t 1: Vender artículo" << endl << "\t 2: Desplegar archivo de facturas" << endl <<
        "\t 3: Conocer al vendedor con más ventas y con menos ventas" << endl <<
        "\t 4: Conocer al cliente con más compras y con menos compras" << endl <<
        "\t 5: Conocer el artículo más vendido y el menos vendido" << endl <<
        "\t 6: Ver facturas por fecha" << endl << "\t 7: Exit" << endl;
        int opc;
        cin >> opc;
        cout << endl;

        leeArchivos(producto, cliente, vendedor);

        if(opc == 1){
            cout << "Vender artículos" << endl << "--------------------------" << endl;
            venderArticulos(producto, cliente, vendedor);
        }
        else if(opc == 2){
            cout << "Buscar factura por clave" << endl << "---------------------------" << endl;
            cout << "Clave de Factura: ";
            string clave;
            cin >> clave;
            buscaFactura(factura, producto, cliente, vendedor, clave);
        }
        else if(opc == 3){
            cout << "Mejor y Peor vendedor" << endl << "--------------------------" << endl;
            mejorPeorVendedor(vendedor);
        }
        else if(opc == 4){
            cout << "Mejor y Peor cliente" << endl << "--------------------------" << endl;
            mejorPeorCliente(cliente);
        }
        else if(opc == 5){
            cout << "Mejor y Peor artículo" << endl << "--------------------------" << endl;
            mejorPeorArticulo(producto);
        }
        else if(opc == 6){
            cout << "Buscar Factura por fechas" << endl << "--------------------------------" << endl;
            cout << "Ingrese la fecha (mmddyy): ";
            string fecha;
            cin >> fecha;
            buscaFacturaFecha(fecha,factura, producto, vendedor, cliente);
        }
        else if(opc == 7){
            cout << "Gracias por visitar Refaccionaria On The Go" << endl;
            cout << "-------------------------------------------" << endl;
            exit(1);
        }
    }

    return 0;
}