#ifndef CGRAFICO_H
#define CGRAFICO_H

#include "CPoco.h"
#include "CPerfuracao.h"
#include "CRevestimento.h"
#include "COperacao.h"
#include "CGnuplot.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

/// Classe CGrafico, que ira solicitar os resultados das classe COperacao, e calcular os pares ordenados do grafico a ser gerado
class CGrafico
{
    // Atributos
	private:

		/// Vetor que armazena os valores de profundidade para gerar o grafico
		vector< double > profundidadeGrafico;
		
		/// Vetor que armazena os valores de profundidade para gerar o grafico
		vector< double > tempoGrafico;
		
		/// Vetor que armazena os valores de profundidade para gerar o grafico
		vector< double > tempoDescidaDP;
		
		/// Vetor que armazena os valores de profundidade para gerar o grafico
		vector< double > tempoTaxaPerfuracao;
		
		/// Vetor que armazena os valores de profundidade para gerar o grafico
		vector< double > tempoPatamar;
		
	// Metodos
	public:
		
		/// Criando objeto do tipo COperacao com o nome operacao
		COperacao operacao;
		
		/// Criando objeto do tipo CPoco com o nome poco
		CPoco poco;
		
		/// Criando objeto do tipo CPerfuracao com o nome perfuracao
		CPerfuracao perfuracao;
		
		/// Construtor, define valores para os atributos e chama o metodo AtualizarTempoBOP da classe COperacao
		CGrafico (COperacao operacao_, CPoco poco_, CPerfuracao perfuracao_) : operacao(operacao_), poco(poco_), perfuracao(perfuracao_)
		{
			/// Cria um vetor profundidade para receber os valores do vetor de profundidades da classe CPoco
			vector< double > profundidade = poco.GetProfundidade ();
			
			/// Carrega o vetor profundidadeGrafico com os seus valores de profundidade respectivos
			profundidadeGrafico = vector< double >(18);
			profundidadeGrafico[0] = 0.0;
			profundidadeGrafico[1] = profundidade[0];
			profundidadeGrafico[2] = profundidade[1];
			profundidadeGrafico[3] = profundidade[1];
			profundidadeGrafico[4] = profundidade[1];
			profundidadeGrafico[5] = profundidade[2];
			profundidadeGrafico[6] = profundidade[2];
			profundidadeGrafico[7] = profundidade[2];
			profundidadeGrafico[8] = profundidade[2];
			profundidadeGrafico[9] = profundidade[3];
			profundidadeGrafico[10] = profundidade[3];
			profundidadeGrafico[11] = profundidade[3];
			profundidadeGrafico[12] = profundidade[4];
			profundidadeGrafico[13] = profundidade[4];
			profundidadeGrafico[14] = profundidade[4];
			profundidadeGrafico[15] = profundidade[5];
			profundidadeGrafico[16] = profundidade[5];
			profundidadeGrafico[17] = profundidade[5];
			
			/// Variavel que representa o tempo gasto para montar e desmontar o BHA
			double montarBHA = 8.0;
			
			/// Variavel que representa a velocidade de descida e subida do BHA
			double descerBHA = 1.0/0.006;
			
			/// Vetor que armazena os tempos de descida dos DP de cada uma das fases
			tempoDescidaDP = vector< double >(6);
			
			for (int i=1 ; i<6 ; i++)
			{
				tempoDescidaDP[i] = montarBHA + profundidade[i-1]/descerBHA;
			}
			
			/// Vetor que armazena as taxas de perfuracao de cada uma das fases
			vector< double > perfurar = perfuracao.GetPerfurar ();
			
			/// Vetor que armazena os tempos de perfuracao de cada uma das fases
			tempoTaxaPerfuracao = vector< double >(6);
			
			for (int i=1 ; i<6 ; i++)
			{
				tempoTaxaPerfuracao[i] = (profundidade[i]-profundidade[i-1])/perfurar[i];
			}
			
			/// Vetor que armazena os tempos calculados pela classe COperacao
			vector< double > TempoFase = operacao.TempoFase ();
				
			///Vetor que armazena os tempos de subida de DP, revestir e cimentar cada uma das fases
			tempoPatamar = vector< double >(6);
			
			for (int i=1 ; i<6 ; i++)
			{
				tempoPatamar[i] = TempoFase[i]-tempoDescidaDP[i]-tempoTaxaPerfuracao[i];
			}
			
			/// Vetor que armazena os tempos de descida e subida do BOP, calculados pela classe COperacao
			vector< double > TempoBOP = operacao.GetTempoBOP ();
			
			/// Vetor que armazena os tempos para plotar o grafico
			tempoGrafico = vector< double >(18);
			tempoGrafico[0] = 0.0;
			tempoGrafico[1] = tempoDescidaDP[1] + tempoGrafico[0];
			tempoGrafico[2] = tempoTaxaPerfuracao[1] + tempoGrafico[1];
			tempoGrafico[3] = tempoPatamar[1] + tempoGrafico[2];
			tempoGrafico[4] = tempoDescidaDP[2] + tempoGrafico[3];
			tempoGrafico[5] = tempoTaxaPerfuracao[2] + tempoGrafico[4];
			tempoGrafico[6] = tempoPatamar[2] + tempoGrafico[5];
			tempoGrafico[7] = TempoBOP[0] + tempoGrafico[6];
			tempoGrafico[8] = tempoDescidaDP[3] + tempoGrafico[7];
			tempoGrafico[9] = tempoTaxaPerfuracao[3] + tempoGrafico[8];
			tempoGrafico[10] = tempoPatamar[3] + tempoGrafico[9];
			tempoGrafico[11] = tempoDescidaDP[4] + tempoGrafico[10];
			tempoGrafico[12] = tempoTaxaPerfuracao[4] + tempoGrafico[11];
			tempoGrafico[13] = tempoPatamar[4] + tempoGrafico[12];
			tempoGrafico[14] = tempoDescidaDP[5] + tempoGrafico[13];
			tempoGrafico[15] = tempoTaxaPerfuracao[5] + tempoGrafico[14];
			tempoGrafico[16] = tempoPatamar[5] + tempoGrafico[15];
			tempoGrafico[17] = TempoBOP[1] + tempoGrafico[16];
		}
		
		/// Metodo que gera o grafico
		void PlotarGrafico ()
		{
			CGnuplot gplot("lines"); 
			gplot.set_xlabel("Tempo");
            gplot.set_ylabel("Profundidade");
            gplot << "set yrange [*:*] reverse";
            gplot.plot_xy(tempoGrafico, profundidadeGrafico);
            gplot << "set terminal png size 1200,900";
            gplot << "set output 'Grafico.png'";
            gplot.plot_xy(tempoGrafico, profundidadeGrafico);
			cout << "Pressione <enter> para continuar" << endl;
            cin.get();
		}
    
};

#endif
