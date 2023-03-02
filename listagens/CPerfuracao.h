#ifndef CPERFURACAO_H
#define CPERFURACAO_H

#include "CPoco.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

/// Classe CPerfuracao, responsavel pelos calculos da etapa de perfuracao de um poco
class CPerfuracao
{
	// Atributos
	private:
		
		/// Vetor para armazenar o tempo gasto na perfuracao, para cada fase do poco
		vector< double > tempoPerfuracao;
		
		/// Variavel que representa o tempo gasto para montar e desmontar o BHA, eh um valor fixo
		double montarBHA;
		
		/// Variavel que representa a velocidade de descida e subida do BHA
		double descerBHA;
	
		/// Vetor que representa a taxa de penetracao para cada fase do poco
		vector< double > perfurar;
		
		/// Variavel que representa o tempo de duracao da circulacao do fluido dentro do poco
		double circular;
	
	// Metodos
	public:
		
		/// Criando objeto do tipo CPoco com o nome poco
		CPoco poco;
		
		/// Construtor, define valores para os atributos e chama o metodo CalcularPerfuracao
		CPerfuracao (CPoco poco_) : poco(poco_)
		{			
			montarBHA = 8.0;
	
			descerBHA = 1.0/0.006;
		    
            perfurar = vector< double >(6);
			perfurar[0] = 0.0;
			perfurar[1] = 10.0;
			perfurar[2] = 10.0;
			perfurar[3] = 5.0;
			perfurar[4] = 5.0;
			perfurar[5] = 3.0;
		
			circular = 3.0;
			
			CalcularPerfuracao ();			
		}
		
		/// Metodo para retornar os valores de taxa de perfuracao
		vector< double > GetPerfurar ()
		{			
			return perfurar;			
		}

		/// Metodo que calcula o tempo gasto em toda a etapa de perfuracao
		vector< double > CalcularPerfuracao ()
		{    		
			tempoPerfuracao = vector< double >(6);
    		
			/// Cria um vetor profundidade para receber os valores do vetor de profundidades da classe CPoco	
			vector< double > profundidade = poco.GetProfundidade ();
    		
    		/// Um "for" para realizar a conta para cada fase e preencher o vetor com os tempos gastos em cada fase
			for ( int i = 1 ; i < 6 ; i++ )
            {				
				tempoPerfuracao[i] = 2.0*montarBHA + profundidade[i-1]/descerBHA + (profundidade[i]-profundidade[i-1])/perfurar[i] + profundidade[i]/descerBHA + circular;				
            }
    
			return tempoPerfuracao;			
		}
		
		/// Metodo para retornar o vetor com os tempos gastos na perfuracao
		vector< double > GetTempoPerfuracao ()
		{			
			return tempoPerfuracao;			
		}

};

#endif
