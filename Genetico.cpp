#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <bits/stdc++.h>
#include <string>

using namespace std;

vector<int> vecindario;   //vecindario de numeros obtenidos
vector<string> vecindario_bin; //vecindario de numeros en binario
vector<string> vecindario_hijos;  //vecindario de numeros mezclados
int fin=1;    //para terminar el programa

string binario(int n)
{
    string r;
    while (n != 0){
        r += ( n % 2 == 0 ? "0" : "1" );
        n /= 2;
    }
    return r;
}

void transformavecindad(void) //solo transforma a binario los numeros originales
{
  int aux=0;
  for(int i=0; i < vecindario.size();i++)
  {
    vecindario_bin.push_back(binario(vecindario[i]));
  }
  for(int i=0; i < vecindario_bin.size();i++)
  {
    if (aux<vecindario_bin[i].size())
    {
      aux=vecindario_bin[i].size();
    }
  } //saca la extension maxima de un binario (para dar un formato)
  if (aux%2!=0)
  { //si el numero no es par, se hace par a la fuerza
    aux++;
  }
  for (int j=0; j < vecindario_bin.size(); j++)
  {
    for (int k=vecindario_bin[j].size(); k < aux; k++)
    { //se agregan 0's al inicio para que todos los numeros sean del mismo tamaño o extension
      vecindario_bin[j].append("0");
    }
    reverse(vecindario_bin[j].begin(), vecindario_bin[j].end());
  } //en un principio se guarda el binario al reves, por lo cual es necesario voltearlo para que sea correcto
  cout << "\n";
}

int bin2dec(string sbin)
{
    int j=0,sum=0,tmp;
    int len = sbin.size();
 
    for(j=0;j<len;j++)
    {
        if(sbin[j]!='1' && sbin[j]!='0')
        {
            printf("Este no es un numero en formato binario.");
            return -1;
        }
    }
 
    tmp = len-1;
    for(j=0; j<len; j++)
    {
        sum=sum+((sbin[j]-'0')*(tmp?(2<<tmp-1):1));
        tmp--;
    }
 
    return sum;
}

void imprimevecindad(void)
{
  cout << "\nResultados de evaluacion:" << endl;
  for(int i=0; i < vecindario.size();i++)
  {
    cout << vecindario[i] << "\n";
  }
}

void imprimevecindadb(void) //este e imprimevecindadr es la misma pero con diferente etiqueta, por que se llaman en diferentes momentos
{
  cout << "\nPadres:" << endl;
  for(int i=0; i < vecindario_bin.size();i++)
  {
    cout << vecindario_bin[i] << "\t";
    int nuevo;
    nuevo = bin2dec (vecindario_bin[i]);
    cout << nuevo << endl;
  }
}

void imprimevecindadr(void)
{
  cout << "\nResultado:" << endl;
  vecindario.clear();
  for(int i=0; i < vecindario_bin.size();i++)
  {
    cout << vecindario_bin[i] << "\t";
    int nuevo;
    nuevo = bin2dec (vecindario_bin[i]);
    cout << nuevo << endl;
    vecindario.push_back(nuevo);
  }
}

void imprimevecindadh(void)
{
  cout << "\nHijos:" << endl;
  for(int i=0; i < vecindario_hijos.size();i++)
  {
    cout << vecindario_hijos[i] << "\t";
    int nuevo;
    nuevo = bin2dec (vecindario_bin[i]);
    cout << nuevo << endl;
  }
}

int repeticion(int x, int y) //evitar repeticiones
{
  int c;
  if (x==y)
  {
    c=1;
  }
  else 
  {
    c=0;
  }
  return c;
}

int repetirhijo(int x) //evitar repetir padres a la sig generacion
{
  int c;
  for (int i=0;i<vecindario_bin.size();i++)
  {
    if (vecindario_bin[i]==vecindario_hijos[x])
    {
      c=1;
      return c;
    }
    else
    {
      c=0;
    }
  }
  return c;
}

void maximohijos(void) //tomar los hijos mas grandes
{    
  //vecindario ordenado de mayor a menor
  int c1,c2,auxi;
  for(c1=0;c1<vecindario.size();c1++)
  {
    for(c2=0;c2<vecindario.size();c2++)
    {
      if(vecindario[c2]<vecindario[c2+1])
      {
        auxi=vecindario[c2];
        vecindario[c2]=vecindario[c2+1];
        vecindario[c2+1]=auxi;
      }
    }
  }
  imprimevecindad();
}

void minimohijos(void) //tomar los hijos menos grandes
{    
  //vecindario ordenado de menor a mayor
  int c1,c2,auxi;
  for(c1=0;c1<vecindario.size();c1++)
  {
    for(c2=0;c2<vecindario.size();c2++)
    {
      if(vecindario[c2]>vecindario[c2+1])
      {
        auxi=vecindario[c2];
        vecindario[c2]=vecindario[c2+1];
        vecindario[c2+1]=auxi;
      } 
    }
  }
  imprimevecindad();
}

void mezcla (int cromosoma,int eleccion)
{
  int tam=vecindario_bin[0].size(); //tomar el tamano de la cadena
  string aux; //saca un caracter
  int ayuda;   //aux de comprobacion para repeticion
  srand(time(NULL));
  tam=tam/2;   //marcar la mitad de la cadena
  int largo=cromosoma;  //tamaño total de binarios=cromosomas
  int i;   //saca un aleatorio
  if (eleccion==1)
  {
    maximohijos();
  }
  else
  {
    minimohijos();
  }
  transformavecindad();
  for(int k=0;k<largo;k++)  //tomar un numero de padres = cromosomas y genera 2 hijos por padre
  {
    int validar=1;  //se ocupa al final para las repeticiones
    for (int j=0;j<tam;j++)
    {
      if (j==0)
      {
        aux=vecindario_bin[i][j];
        vecindario_hijos.push_back(aux);
      }
      else
      {
        aux=vecindario_bin[i][j];
        vecindario_hijos.back().append(aux);
      }
    }
    for (int j=0;j<tam;j++)
    {
      aux=vecindario_bin[i+1][j+tam];
      vecindario_hijos.back().append(aux);
    }
    //toma las mitades al reves
    for (int j=0;j<tam;j++)
    {
      if (j==0)
      {
        aux=vecindario_bin[i][j+tam];
        vecindario_hijos.push_back(aux);
      }
      else
      {
        aux=vecindario_bin[i][j+tam];
        vecindario_hijos.back().append(aux);
      }
    }
    for (int j=0;j<tam;j++)
    {
      aux=vecindario_bin[i+1][j];
      vecindario_hijos.back().append(aux);
    }
    
    ayuda=i;      //las repet se excluyen
    while (validar)
    {
      i = rand()%largo;
      validar=repeticion(ayuda,i); //las mezclas generadas no podran ser iguales
    }
  }
  imprimevecindadb();
  cout << "\n";
  imprimevecindadh();
  cout << "\n";
  vecindario_bin.clear();
  //tamhijos es la muestra de todos los hijos 
  int tamhijos=vecindario_hijos.size();
  int f = rand()%tamhijos;
  //cout << f << endl;
  vecindario_bin.push_back(vecindario_hijos[f]);
  for (int j=0;j<cromosoma-1;j++)  //se sacan n hijos donde n es cromosomas -1 porque se guardo uno al inicio
  {
    int validar=1; //para no repetir hijos a la siguiente generacion (evita padres iguales)
    int indicador=1; //para sacar un numero que cumpla la eleccion
    while (validar)
    {
        f = rand()%tamhijos;
        //cout << f << endl; 
        //despues de esta linea entraria en accion lo de eleccion que se pidio antes, aun no esta hecho
       /*while (indicador)
        {
          if (eleccion==1)
          {
            indicador=maximohijos(f);
          }
          else
          {
            indicador=minimohijos(f);
          }
        }*/
        validar=repetirhijo(f);
    }
    vecindario_bin.push_back(vecindario_hijos[f]);
  }
  imprimevecindadr();
  vecindario_hijos.clear();
  vecindario_bin.clear();
}

int menu(int op)
{
  cout << "\n\n\tFunciones\n1)X^2\n2)sin(x)*40\n3)cos(x)+x\n4)(1000/abs(50-x))+x\n5)(1000/abs(30-x)) + (1000/abs(50-x)) + (1000/abs(80-x))+x\n6)Salir\n\n Elige una opcion:";
  cin >> op;
  return op;
}

int menue(int op)
{
  cout << "\n\n\tOpciones\n1)maximo\n2)minimo\n\n Elige una opcion:";
  cin >> op;
  return op;
}

int uno (int x)
{
  int res;
  res=pow(x,2);
  return res;
}

int dos (int x)
{
  int res;
  res=sin(x)*40;
  return res;
}

int tres (int x)
{
  int res;
  res=cos(x)+x;
  return res;
}

int cuatro (int x)
{
  int res;
  if (x==50)
  {
    x++;
  }
  res=(1000/abs(50-x))+x;
  return res;
}

int cinco (int x)
{
  int res;
  if (x==30 || x==50 || x==80)
  {
    x++;
  }
  res=((1000/abs(30-x))+(1000/abs(50-x))+(1000/abs(80-x)))+x;
  return res;
}

void familia(int inicio, int fina, int cromosoma, int op)
{
  int valor=0;
  int iteracion=0;  //genera el numero de datos necesarios para cumplir el requisito de cromosomas
  srand(time(NULL));
  if (op==6)
  {
      fin=0;
      cout<<"\nadios\n";      
  }
  else
  {
    while (iteracion<cromosoma)
    {
      for (int i=inicio;i<fina;i++)
      {
        if (rand()%2==0)
        {
          switch (op)
          {
            case 1:
              valor=uno(i);
              break;
            case 2:
              valor=dos(i);
              break;
            case 3:
              valor=tres(i);
              break;
            case 4:
              valor=cuatro(i);
              break;
            case 5:
              valor=cinco(i);
              break;
            default:
              cout<<"Error";
              break;
          }
          vecindario.push_back(valor);
          iteracion++;
          if (iteracion>=cromosoma)
          {
            break;
          }
        }
      }
    }
  }
}

void evaluar(int op,int cromosoma, int generaciones, int inicio, int fina,int eleccion)
{
  int res;
  familia(inicio,fina,cromosoma,op);
  if (op<6)
  {
    cout << "\n";
    imprimevecindad();
    cout << "\n";
    transformavecindad();
    cout << "\n";
    for (int i=0; i<generaciones;i++)
    {
      cout << "\nGeneracion: " << i+1 << endl;
      mezcla(cromosoma,eleccion);
      cout << "\n";
    }
  }
}

int main(void)
{
  int op;
  int cromosoma;
  int generaciones;
  int inicio,fina;
  int eleccion;
  cout<<"Numero de cromosomas:";
  cin>>cromosoma;
  while (fin!=0)
  {
    op=menu(op);
    if (op<6)
    {
      cout<<"Numero de generaciones:";
  	  cin>>generaciones;
      cout << "Valor de inicio de intervalo:"; //cambia despues a valores de entrada
      cin >> inicio; //se puede hacer funcion
      cout << "Valor de final de intervalo:"; //cambia despues a valores de entrada
      cin >> fina; //se puede hacer funcion
      eleccion=menue(eleccion);
    }
    evaluar(op,cromosoma,generaciones,inicio,fina,eleccion);
    vecindario.clear();
    vecindario_bin.clear();
    vecindario_hijos.clear();
  }
  return 0;
}
