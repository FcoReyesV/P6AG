#include <iostream>
#include <stdio.h>     
#include <stdlib.h>    
#include <time.h>   
#include <math.h>

class Cruza{
private:
    int poblacion;
    int alelos;
    int *individuosE;
    int **individuosB;
    int **individuosBC; //Binario cruza
public:
    Cruza(int, int);
    void CreaIndividuos();
    void ConvBinario(int,int);
    void CruzaUnPunto(int);
    void CruzaDosPuntos(int,int);
    void CruzaUniforme();
    void CruzaAcentuada();
    bool CheckRep(int, int*,int*);
    bool CheckRepCA(int,int*,int*,int,int);
    void ImprimirRes(int **,int**);
    void LiberarMemoria();
};
using namespace std;

Cruza::Cruza(int ipoblacion,int ialelos){
    poblacion = ipoblacion;
    alelos = ialelos;
    individuosE = new int[poblacion]; // se debe liber la memoria dinamica delete [] cadena_dinamica;  cadena_dinamica = NULL;
    individuosB = new int*[poblacion];
    individuosBC = new int*[poblacion];

    for(int i=0;i<poblacion;i++){
        individuosB[i] = new int[alelos];
        individuosBC[i] = new int[alelos];
    }

   

}

void Cruza::CreaIndividuos(){
    int limite=0,random;
    int individuos[16];
    for(int i=0;i<alelos;i++){
        limite += pow(2,i);
    }
    for(int i=0;i<poblacion;i++){
        random =  rand() % limite + 1;//numero para el individuo
        individuosE[i]= random;
        //cout<<"Individuo: "<<individuosE[i]<<endl;
        ConvBinario(random,i);
    }
    
   
}

void Cruza::ConvBinario(int numero,int valori){
    int dividendo, resto, divisor = 2,cont = 1,j=alelos-1;
    for(int i=0;i<alelos;i++){
        individuosB[valori][i] = 0;
    }
    dividendo = numero;
    while(dividendo >= divisor){
    resto = dividendo % 2;
    if(resto == 1)
        individuosB[valori][j] = 1;
    else
       individuosB[valori][j] = 0;
       dividendo = dividendo/divisor;
       cont++;
       j--;
    }
    if(dividendo == 1)
       individuosB[valori][j] = 1;
    else
       individuosB[valori][j] = 0;
    

}

void Cruza::CruzaUnPunto(int pcruza){
    for(int i=0;i<poblacion-1;i++){
        for(int j=0;j<pcruza;j++){
            individuosBC[i][j] = individuosB[i][j];
            individuosBC[i+1][j] = individuosB[i+1][j];
        }
        for(int k=pcruza;k<alelos;k++){
            individuosBC[i][k] = individuosB[i+1][k];
            individuosBC[i+1][k] = individuosB[i][k];
        }
        i++;
    }
    cout<<"No. |   Individuos   |   Cruza "<<endl;
    cout<<"____________________________________________"<<endl;
    ImprimirRes(individuosB,individuosBC);

}

void Cruza::CruzaDosPuntos(int pcruza1,int pcruza2){
    for(int i=0;i<poblacion-1;i++){
        for(int j=0;j<pcruza1;j++){
            individuosBC[i][j] = individuosB[i][j];
            individuosBC[i+1][j] = individuosB[i+1][j];
        }
        for(int k=pcruza1;k<pcruza2;k++){
            individuosBC[i][k] = individuosB[i+1][k];
            individuosBC[i+1][k] = individuosB[i][k];
        }
        for(int l=pcruza2;l<alelos;l++){
            individuosBC[i][l] = individuosB[i][l];
            individuosBC[i+1][l] = individuosB[i+1][l];
        }
        i++;
    }
    cout<<"No. |   Individuos   |   Cruza "<<endl;
    cout<<"____________________________________________"<<endl;
    ImprimirRes(individuosB,individuosBC);

}

void Cruza::CruzaUniforme(){
    //Necesitamos primero generar las posiciones aleatorias de donde se van a copiar los cromosomas. 
    int indice=alelos/2;
    int random, aux1[indice],aux2[indice];
    //numero para el individuo
    for(int i=0;i<indice;i++){
        do
            random =  rand() % alelos;
        while(CheckRep(random, aux1, aux2));
        aux1[i]=random; //Contiene la posición que será seleccionada de los padres

        do
            random =  rand() % alelos;
        while(CheckRep(random, aux1, aux2));
        aux2[i]=random;
        cout<<"Posiciones 1: "<<aux1[i]<<" Posiciones 2: "<<aux2[i]<<endl;
    }
    //Tenemos que recorrer los dos arreglos auxiliares, el primero toma los indices del primer padre en la primera parte
    for(int i=0;i<poblacion-1;i++){

        for(int j=0;j<alelos;j++){
            
            for(int k=0;k<indice;k++){
                if(j == aux1[k]){
                    individuosBC[i][aux1[k]] = individuosB[i][aux1[k]]; 

                    individuosBC[i+1][aux1[k]] = individuosB[i+1][aux1[k]]; 
                }
                if(j == aux2[k]){
                     individuosBC[i][aux2[k]] = individuosB[i+1][aux2[k]];

                     individuosBC[i+1][aux2[k]] = individuosB[i][aux2[k]];
                }
            }
        }

        i++;
    }
    cout<<endl<<"No. |   Individuos   |   Cruza "<<endl;
    cout<<"____________________________________________"<<endl;
    ImprimirRes(individuosB,individuosBC);

}

void Cruza::CruzaAcentuada(){
    int indice1 = rand() % 2 + 1; 
    int indice2 = rand() % 3 + 1;
    int random, signos1[indice1],signos2[indice2];
    bool h1=true,h2=false,posicion=true,posicion2=false;
    cout<<"Posicion de signo(s) ! del primer padre: "<<endl;  
    for(int i=0;i<indice1;i++){
        do
            random =  rand() % (alelos-2) + 1;
        while(CheckRepCA(random,signos1,signos2,indice1,indice2));
        signos1[i]=random; //Contiene la posición que será seleccionada de los padres
        cout<<signos1[i]<<endl;
    }
    cout<<"Posicion de signo(s) ! del segundo padre: "<<endl;  
    for(int i=0;i<indice2;i++){
        do
            random =  rand() % (alelos-2) + 1;
        while(CheckRepCA(random,signos1,signos2,indice1,indice2));
        signos2[i]=random; //Contiene la posición que será seleccionada de los padres
        cout<<signos2[i]<<endl;
    }
    

    for(int i=0;i<poblacion-1;i++){
        for(int j=0;j<alelos;j++){
            for(int k=0;k<indice1;k++) //Aqui buscamos si hace match el indice del alelo con el signo
                if(j == signos1[k]){
                    h1=true;
                    h2=false;
                    posicion=!posicion;
                    posicion2=!posicion2;
                }
            for(int l=0;l<indice2;l++)
                if(j == signos2[l]){
                    h1=false;
                    h2=true;
                    posicion=!posicion;
                    posicion2=!posicion2;
                }


            if(h1){ //Copiamos del primer padre
                if(posicion) //Nos aseguramos de que se copie intercaladamente
                    individuosBC[i][j] = individuosB[i][j];
                else
                    individuosBC[i][j] = individuosB[i+1][j];
               
            }
            else{ //Copiamos del segundo padre
                if(posicion)
                    individuosBC[i][j] = individuosB[i][j];
                else
                    individuosBC[i][j] = individuosB[i+1][j];
               
            }

            if(!h2){ //Copiamos del segundo padre
                if(!posicion2)
                    individuosBC[i+1][j] = individuosB[i+1][j];
                else
                    individuosBC[i+1][j] = individuosB[i][j]; 
                
            }
            else{ //Copiamos del primer padrfe 
                if(!posicion2)
                    individuosBC[i+1][j] = individuosB[i+1][j];
                else
                    individuosBC[i+1][j] = individuosB[i][j]; 
                
            }


            
        }
    }
    cout<<endl<<"No. |   Individuos   |   Cruza "<<endl;
    cout<<"____________________________________________"<<endl;
    ImprimirRes(individuosB,individuosBC);
}

void Cruza::ImprimirRes(int **arr, int **arr2){
    for(int i=0;i<poblacion;i++){
        cout<<i+1<<"   |   ";
        for(int j=0;j<alelos;j++)
            cout<<arr[i][j];
        cout<<"   |   ";
        for(int j=0;j<alelos;j++)
            cout<<arr2[i][j];
        cout<<endl;
    }
}

void Cruza::LiberarMemoria(){
    for(int i=0;i<poblacion;i++){
        delete []individuosB[i];
        delete []individuosBC[i];
    }
    
    delete []individuosE;
    delete []individuosB;
    delete []individuosBC;
}

bool Cruza::CheckRep(int n, int num[], int num2[])
{
    for(int i=0; i<alelos/2; i++)
        if(n == num[i] || n == num2[i])
            return true;
    return false;
}

bool Cruza::CheckRepCA(int n, int num1[], int num2[],int indice1,int indice2){
    bool aux=false;
    for(int i=0; i<indice1; i++)
        if(n == num1[i])
            aux=true;
    for(int i=0; i<indice2; i++)
        if(n == num2[i])
            aux=true;
    return aux;
}

int main(int argc, char const *argv[])
{
    char opc;
    
	int indiv, alel,opc1;
    srand(time(NULL));
	do{
	
	    cout<<"Metodos de cruza 1"<<endl;
	    cout<<"1.- Cruza de un punto"<<endl<<"2.- Cruza de dos puntos"<<endl<<"3.- Cruza uniforme"<<endl<<"4.- Cruza acentuada"<<endl<<"5.- Salir"<<endl;
	    
	    cout<<"Escribe el numero de individuos: ";
	    cin>>indiv;
	    cout<<endl<<"Escribe el numero de alelos: ";
	    cin>>alel;
	    
	    Cruza c(indiv, alel);
	    c.CreaIndividuos();
	    cout<<endl<<"Escribe una opcion de cruza: ";
	    cin>>opc1;
	    switch(opc1){
	        case 1:
	            system("cls");
	            int ptocruza;
	            cout<<"Cruza de un punto"<<endl;
	            cout<<"Escribe el punto de cruza: ";
	            cin>>ptocruza;
	            cout<<endl;
	            c.CruzaUnPunto(ptocruza);
	            break;
	        case 2:
	            system("cls");
	            int ptocruza1,ptocruza2;
	            cout<<"Cruza de dos puntos"<<endl;
	            cout<<"Escribe el punto de cruza 1: ";
	            cin>>ptocruza1;
	            cout<<endl;
	            cout<<"Escribe el punto de cruza 2: ";
	            cin>>ptocruza2;
	            cout<<endl;
	            c.CruzaDosPuntos(ptocruza1,ptocruza2);
	            
	            break;
	        case 3:
	            system("cls");
	            cout<<"Cruza uniforme"<<endl;
	            c.CruzaUniforme();
	            break;
	        case 4:
	            system("cls");
	            cout<<"Cruza acentuada"<<endl;
	            c.CruzaAcentuada();
	            break;
	        case 5:
	            exit(0);
	            break;
	    }
	    c.LiberarMemoria();
        cout<<endl<<"Deseas volver al menu?(s/n): "<<endl;
        cin>>opc;
        
        system("cls");
	}while(opc=='s');	
    cout<<endl;
   

    
    return 0;
}



