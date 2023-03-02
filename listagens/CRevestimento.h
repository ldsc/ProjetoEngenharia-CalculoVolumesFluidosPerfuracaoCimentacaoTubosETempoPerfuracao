#ifndef CREVESTIMENTO_H
#define CREVESTIMENTO_H

#include "CPoco.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

/// Classe CRevestimento, responsavel pelos calculos da etapa de revestimento e cimentacao
class CRevestimento
{	
	// Atributos	
	private:
		
		/// Vetor para armazenar o tempo gasto nesta etapa, para cada fase
		vector< double > tempoRevestimento;
		
		/// Vetor com os valores que representam a taxa de montagem do revestimento em cada fase (cada fase possui uma taxa diferente)
		vector< double > montarRevestimento;
		
		/// Variavel que representa a velocidade de descida do revestimento a poco aberto
		double descerAberto;
		
		/// Variavel que representa a velocidade de descida do revestimento a poco revestido
		double descerRevestido;
		
		/// Variavel que representa a velocidade de descida do revestimento por dentro do riser
		double descerRiser;
		
		/// Variavel que representa a vazao de bobeio de cimento
		double bombearCimento;
		
		/// Variavel que representa o tempo necessario para que o cimento de pega
		double esperarCimentoSecar;
		
		/// Variavel que representa a taxa de subida do drill pipe
		double subirDP;

	// Metodos
	public:
		
		/// Criando objeto do tipo CPoco com o nome poco
		CPoco poco;

		/// Construtor, define valores para os atributos e chama o metodo CalcularRevestimento
		CRevestimento (CPoco poco_) : poco(poco_)        
		{			
			montarRevestimento = vector< double >(6);
			montarRevestimento[0] = 0.0;
			montarRevestimento[1] = 2.0;
			montarRevestimento[2] = 6.0;
			montarRevestimento[3] = 8.0;
			montarRevestimento[4] = 11.0;
			montarRevestimento[5] = 13.0;
		
			descerAberto = 240.0;
		
			descerRevestido = 360.0;
		
			descerRiser = 720.0;
		
			bombearCimento = 600.0;
		
			esperarCimentoSecar = 12.0;
		
			subirDP = 1.0/0.006;
			
			CalcularRevestimento ();				
		}
		
		/// Metodo CalcularRevestimento, que calcula o tempo gasto para a etapa de instalacao do revestimento e cimentacao do poco	
		vector< double > CalcularRevestimento ()
		{			
			tempoRevestimento = vector< double >(6);
			
			/// Recebe da classe CPoco os valores de profundidade, numero de tubos, volumes de cimento e capacidades das brocas, dos revestimentos e do drill pipe
			vector< double > profundidade = poco.GetProfundidade ();			
			vector< double > numeroJuntas = poco.GetNumeroJuntas ();			
			vector< double > volumeCimento = poco.GetVolumeCimento ();
			vector< double > capacidadeBroca = poco.GetCapacidadeBroca ();
			vector< double > capacidadeRevestimento = poco.GetCapacidadeRevestimento ();
			double capacidadeDP = poco.GetCapacidadeDP ();
			
			/// Primeiro "for" para calcular o tempo para as duas primeiras fases
			for ( int i = 1 ; i < 3 ; i++ )
			{					
				tempoRevestimento[i] = numeroJuntas[i]/montarRevestimento[i] + (profundidade[0]-(profundidade[i]-profundidade[0]))/descerAberto + ((profundidade[i]-50.0)*capacidadeDP+50.0*capacidadeRevestimento[i]+volumeCimento[i])/bombearCimento + esperarCimentoSecar + (profundidade[i]-50.0)/subirDP;					
			}
			
			/// Segundo "for" para calcular o tempo para a terceira e quarta fases
			for ( int i = 3 ; i < 5 ; i++ )
			{
				tempoRevestimento[i] = numeroJuntas[i]/montarRevestimento[i] + (profundidade[i-1]-(profundidade[i]-profundidade[0]))/descerRevestido + (profundidade[i]-profundidade[i-1])/descerAberto + (profundidade[0]*capacidadeRevestimento[0]+(profundidade[i]-profundidade[0])*capacidadeRevestimento[i]+volumeCimento[i])/bombearCimento + esperarCimentoSecar + (profundidade[0])/subirDP;
			}
			
			/// Calculo do tempo para a quinta fase
			tempoRevestimento[5] = numeroJuntas[5]/montarRevestimento[5] + (profundidade[0]-(profundidade[5]-profundidade[4]+100.0))/descerRiser + (profundidade[4]-(profundidade[5]-profundidade[4]-100.0)-profundidade[0])/descerRevestido + (profundidade[5]-profundidade[4]-100.0)/descerAberto + ((profundidade[4]-100.0)*capacidadeDP+(profundidade[5]-profundidade[4]+100.0)*capacidadeRevestimento[4]+volumeCimento[5])/bombearCimento + esperarCimentoSecar + (profundidade[4]-100.0)/subirDP;
			
			return tempoRevestimento;
		}

		/// Metodo para retornar o tempo gasto na operacao, em cada fase
		vector< double > GetTempoRevestimento ()
		{
			return tempoRevestimento;
		}
		
};

#endif
