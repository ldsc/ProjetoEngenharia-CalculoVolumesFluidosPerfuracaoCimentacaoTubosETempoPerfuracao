#ifndef COPERACAO_H
#define COPERACAO_H

#include "CPoco.h"
#include "CPerfuracao.h"
#include "CRevestimento.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

/// Classe COperacao, que ira solicitar os resultados das classes CPerfuracao e CRevestimento, e calcular o tempo total gasto em toda a operacao para cada fase
class COperacao
{
	// Atributos
	private:
		
		/// Variavel que representa a velocidade de descida do BOP
		double descidaBOP;
		
		/// Variavel que representa a velocidade de subida do BOP
		double subidaBOP;
		
		/// Vetor que armazena o tempo gasto com subida e descida do BOP
		vector < double > tempoBOP;
		
		/// Vetor que armazena o tempo total gasto em toda operacao para cada fase
		vector < double > tempoTotal;
	
	
	// Metodos
	public:
		
		/// Criando objeto do tipo CPoco com o nome poco
		CPoco poco;
		
		/// Criando objeto do tipo CPerfuracao com o nome perfuracao
		CPerfuracao perfuracao;
		
		/// Criando objeto do tipo CRevestimento com o nome revestimento
		CRevestimento revestimento;
		
		/// Construtor, define valores para os atributos e chama o metodo AtualizarTempoBOP
		COperacao (CPoco poco_, CPerfuracao perfuracao_, CRevestimento revestimento_) : poco(poco_), perfuracao(perfuracao_), revestimento(revestimento_)       
		{
			descidaBOP = 500.0/24.0;
	
			subidaBOP = 750.0/24.0;
			
			AtualizarTempoBOP ();
		}
		
		/// Metodo AtualizarTempoBOP, que calcula o tempo gasto com a descida e subida do BOP e armazena no vetor tempoBOP
		void AtualizarTempoBOP ()
		{
			tempoBOP = vector< double >(2);
			
			vector< double > profundidade = poco.GetProfundidade ();
			
			tempoBOP[0] = profundidade[0]/descidaBOP;
			tempoBOP[1] = profundidade[0]/subidaBOP;
		}
		
		/// Metodo TempoFase, que calcula o tempo gasto em toda a operacao para cada fase e armazena no vetor tempoTotal
		/// O tempo total e a soma do tempo gasto na perfuracao, revestimento e cimentacao por fase
		vector < double > TempoFase ()
		{
			tempoTotal = vector< double >(6);
			
			vector< double > tempoPerfuracao = perfuracao.GetTempoPerfuracao ();
			vector< double > tempoRevestimento = revestimento.GetTempoRevestimento ();
			
			for ( int i = 1 ; i < 6 ; i++ )
			{
				tempoTotal[i] = tempoPerfuracao[i] + tempoRevestimento[i];
			}				
			
			return tempoTotal;
		}
		
		/// Metodo que retorna o vetor tempoTotal
		vector< double > GetTempoFase ()
		{
			return tempoTotal;
		}
		
		/// Metodo que retorna o vetor tempoBOP
		vector< double > GetTempoBOP ()
		{
			return tempoBOP;
		}

};

#endif
