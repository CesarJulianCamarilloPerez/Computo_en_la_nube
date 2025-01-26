#include "pch.h"
#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000
#define chunk 100
#define mostrar 10
using namespace std;

void imprimeArreglo(float* d);

int main()
{
	std::cout << "Sumando Arreglos en Paralelo! \n";
	float a[N], b[N], c[N];
	int i;

	int respuesta;
	/*Solicitamos al usuario si desea llenar manualmente o aleatoriamente los arreglos*/
	std::cout << "Escriba 1 si desea escribir los valores de los arreglos, 0 si desea asignacion aleatoria\n";
	/*Guardamos su respuesta en una variable*/
	cin >> respuesta;
	std::cout << "\n";

	if (respuesta == 1)
	{
		std::cout << "Se inicia llenado manual de arreglos A y B \n";
	}
	else
	{
		std::cout << "Se inicia llenado aleatorios de arreglos A y B \n";
	}

	std::cout << "\n";
	/*Para poder generar numeros aleatorios que no se repitan en diferentes ejecuciones, por lo que usamos como base el tiempo, el cual siempre cambia entre ejecuciones*/
	srand(time(NULL));
	for (i = 0;i < N;i++)
	{
		int num_a;
		int num_b;
		/*Segun la respuesta que dio el usuario generamos el llenado */
		/*Este llenado es de manera manual*/
		if (respuesta == 1)
		{
			std::cout << "Elemento " << i+1 << " de arreglo A"<< std::endl;
			cin >> num_a;
			std::cout << "Elemento " << i+1 << " de arreglo B" << std::endl;
			cin >> num_b;
			a[i] = num_a;
			b[i] = num_b;
		}
		else
			/*Este llenado es de manera aleatoria*/
		{
			
			a[i] = rand();
			b[i] = rand();
		}
	}
	int pedazos = chunk;
	
	std::cout << "Se visualiza la accion de los hilos en la suma paralela \n";
	std::cout << "\n";
#pragma omp parallel for \
	shared(a,b,c,pedazos) private(i) \
	schedule(static,pedazos)

	for (i = 0; i < N; i++) {
		/*Ponemos una sentencia para ver la accion de los hilos*/
		/*Con la siguiente condicion vemos si es el comienzo de un nuevo pedazo*/
			if (i % pedazos == 0) 
			{
				int thread_id = omp_get_thread_num();
				std::cout << "Hilo: " << thread_id  <<std::endl;
				
			}
			c[i] = a[i] + b[i];
		
	}
	std::cout << "\n";
	std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
	imprimeArreglo(a);
	std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
	imprimeArreglo(b);
	std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
	imprimeArreglo(c);
}

void imprimeArreglo(float* d)
{
	for (int x = 0; x < mostrar;x++)
		std::cout << d[x] << "-";
	std::cout << std::endl;
}