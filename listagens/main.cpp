#include "CPoco.h"
#include "CPerfuracao.h"
#include "CRevestimento.h"
#include "COperacao.h"
#include "CGrafico.h"
#include "CGnuplot.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

int main ()
{
	cout << "\n-------------------------   Projeto de Poco   -------------------------" ;
	cout << "\n\nAutores: Fillipe Rodrigues Sias\n\t Lucas Armando de Carvalho" << endl;
	cout << "\nProf. Andre Duarte Bueno" << endl;
	cout << "\nLicenca GPL 2.0" << endl;
	cout << "\n-----------------------------------------------------------------------\n\n" << endl;
	
	/// Vetor que armazena as profundidades das fases, para posteriormente passar para o objeto poco
	vector< double > profundidade (6);
	

	cout << "\n Entre com o valor da Lamina de Agua (metros):\t\t\t";
	cin >> profundidade [0]; 
	cin.get();
	
	for (int i=1; i<6 ; i++)
	{
		cout << "\n Entre com o valor da Profundidade da Fase "<< i <<" (metros):\t\t";
		cin >> profundidade [i]; 
		cin.get();
	}

    /// Cria objeto poco do tipo CPoco e utiliza o construtor da classe para passar os valores de profundidade inseridos pelo usuario
	CPoco poco = CPoco (profundidade);
    
	/// Passa os dados do objeto poco para o objeto perfuracao, do tipo CPerfuracao
	CPerfuracao perfuracao = CPerfuracao (poco);
	
	/// Passa os dados do poco para o objeto revestimento, do tipo CRevestimento
	CRevestimento revestimento = CRevestimento (poco);
	
	/// Passa os dados do poco, perfuracao e revestimento para o objeto operacao, do tipo COperacao
	COperacao operacao = COperacao (poco, perfuracao, revestimento);
	
	/// Vetor que armazena o numero de tubos de riser e revestimento por fase, este vetor é de numeros inteiros por se tratar de uma contagem de pecas, sendo que suas fracoes sao descartadas
	vector< double > numeroJuntas = poco.GetNumeroJuntas ();
	
	/// Vetor que armazena os tempos calculados pela classe COperacao
	vector< double > TempoFase = operacao.TempoFase ();
	
	/// Vetor que armazena os tempos de descida e subida do BOP, calculados pela classe COperacao    
	vector< double > TempoBOP = operacao.GetTempoBOP ();
    
    /// Retorna vetor com volume de fluido de perfuracao calculado na Classe CPoco
    vector< double > volumeFluido = poco.GetVolumeFluido();
    
    /// Varialvel para calcular volume total de fluido de perfuracao utilizado
    double fluidoTotal = 0;
    
    for (int i = 3 ; i < 6 ; i++)
    {
    	fluidoTotal = fluidoTotal + volumeFluido[i];
    }

	/// Retorna vetor com volume de cimento calculado na Classe CPoco
    vector< double > volumeCimento = poco.GetVolumeCimento();
    
    /// Varialvel para calcular volume total de cimento utilizado
    double cimentoTotal = 0;
    
    for (int i = 1 ; i < 6 ; i++)
    {
    	cimentoTotal = cimentoTotal + volumeCimento[i];
    }
    
	/// Saida dos resultados na tela
	
	cout << "\n\n\n-------------------------  Tubos Necessarios  -------------------------"	<< endl;
	
	cout << "\n\nTubos de Riser na Lamina de Agua: \t\t\t" << numeroJuntas [0] << " tubos" << endl;
	cout << "\nTubos de Revestimento de 30 polegadas na Fase 1: \t" << numeroJuntas [1] << " tubos" << endl;
	cout << "\nTubos de Revestimento de 20 polegadas na Fase 2: \t" << numeroJuntas [2] << " tubos" << endl;
	cout << "\nTubos de Revestimento de 13 3/8 polegadas na Fase 3: \t" << numeroJuntas [3] << " tubos" << endl;
	cout << "\nTubos de Revestimento de 9 5/8 polegadas na Fase 4: \t" << numeroJuntas [4] << " tubos" << endl;
	cout << "\nTubos de Liner de 7 polegadas na Fase 5: \t\t" << numeroJuntas [5] << " tubos" << endl;
		
	cout << "\n\n\n------------------------- Duracao da Operacao -------------------------"	<< endl;
	
	cout << "\n\nDuracao da Fase 1: \t" << TempoFase [1] << " horas" << endl;
	cout << "\nDuracao da Fase 2: \t" << TempoFase [2] << " horas" << endl;
	cout << "\nDescida do BOP: \t" << TempoBOP[0] << " horas" << endl;
	cout << "\nDuracao da Fase 3: \t" << TempoFase [3] << " horas" << endl;
	cout << "\nDuracao da Fase 4: \t" << TempoFase [4] << " horas" << endl;
	cout << "\nDuracao da Fase 5: \t" << TempoFase [5] << " horas" << endl;
	cout << "\nSubida do BOP: \t\t" << TempoBOP[1] << " horas" << endl;
    cout << "\nTempo total: \t\t" << TempoFase [1] + TempoFase [2] + TempoFase [3] + TempoFase [4] + TempoFase [5] + TempoBOP[0] + TempoBOP[1] << " horas" << endl;
	cout << "\nTempo total: \t\t" << (TempoFase [1] + TempoFase [2] + TempoFase [3] + TempoFase [4] + TempoFase [5] + TempoBOP[0] + TempoBOP[1]) / 24.0 << " dias" << endl;
	
    cout << "\n\n\n-------------------------       Volumes       -------------------------" << endl;
	
	cout << "\n\nFase 1 e 2 utilizam agua do mar como fluido de perfuracao" << endl;
	cout << "\nVolume de fluido de perfuracao usado na Fase 3: \t" << volumeFluido[3] << " barris" << endl;
    cout << "\nVolume de fluido de perfuracao usado na Fase 4: \t" << volumeFluido[4] << " barris" << endl;
    cout << "\nVolume de fluido de perfuracao usado na Fase 5: \t" << volumeFluido[5] << " barris" << endl;
    cout << "\nVolume Total de fluido de perfuracao usado: \t\t" << fluidoTotal << " barris" << endl;
	
    cout << "\n\nVolume de cimento usado na Fase 1: \t\t\t" << volumeCimento[1] << " barris" << endl;
    cout << "\nVolume de cimento usado na Fase 2: \t\t\t" << volumeCimento[2] << " barris" << endl;
    cout << "\nVolume de cimento usado na Fase 3: \t\t\t" << volumeCimento[3] << " barris" << endl;
    cout << "\nVolume de cimento usado na Fase 4: \t\t\t" << volumeCimento[4] << " barris" << endl;
    cout << "\nVolume de cimento usado na Fase 5: \t\t\t" << volumeCimento[5] << " barris" << endl;
	cout << "\nVolume Total de cimento usado: \t\t\t\t" << cimentoTotal << " barris" << endl;
    
    /// Variavel para receber a resposta do usuario quanto a salvar em disco
	string resposta;
	
	cout << "\n\nDeseja salvar os resultados em disco? (s/n): ";
	
	cin >> resposta;
	cin.get();
	
	if ( resposta == "s")
	{
	    /// Saida dos resultados em disco
		string nomeArquivo;
		
		cout << "\n\nEntre com o nome do arquivo em que os resultados serao salvos: " << endl;
		
		cin >> nomeArquivo;
		cin.get();
		
		nomeArquivo = nomeArquivo + ".txt";
		
		ofstream fout (nomeArquivo.c_str());
		
		fout << "\n-------------------------     Resultados     -------------------------"	<< endl;
		
		fout << "\n\nLamina de Agua: \t";
		fout << profundidade[0] << " metros" << endl;
		
		for(int i = 1 ; i < 6 ; i++)
		{
			fout << "\nProfundida da Fase "<< i <<": \t";
			fout << profundidade[i] << " metros" << endl;
		}
		
		fout << "\n\n\n-------------------------  Tubos Necessarios  -------------------------"	<< endl;
		
		fout << "\n\nTubos de Riser na Lamina de Agua: \t\t\t" << numeroJuntas [0] << " tubos" << endl;
		fout << "\nTubos de Revestimento de 30 polegadas na Fase 1: \t" << numeroJuntas [1] << " tubos" << endl;
		fout << "\nTubos de Revestimento de 20 polegadas na Fase 2: \t" << numeroJuntas [2] << " tubos" << endl;
		fout << "\nTubos de Revestimento de 13 3/8 polegadas na Fase 3: \t" << numeroJuntas [3] << " tubos" << endl;
		fout << "\nTubos de Revestimento de 9 5/8 polegadas na Fase 4: \t" << numeroJuntas [4] << " tubos" << endl;
		fout << "\nTubos de Liner de 7 polegadas na Fase 5: \t\t" << numeroJuntas [5] << " tubos" << endl;
		
		fout << "\n\n\n------------------------- Duracao da Operacao -------------------------"	<< endl;
		
		fout << "\n\nDuracao da Fase 1: \t" << TempoFase [1] << " horas" << endl;
		fout << "\nDuracao da Fase 2: \t" << TempoFase [2] << " horas" << endl;
		fout << "\nDescida do BOP: \t" << TempoBOP[0] << " horas" << endl;
		fout << "\nDuracao da Fase 3: \t" << TempoFase [3] << " horas" << endl;
		fout << "\nDuracao da Fase 4: \t" << TempoFase [4] << " horas" << endl;
		fout << "\nDuracao da Fase 5: \t" << TempoFase [5] << " horas" << endl;
		fout << "\nSubida do BOP: \t\t" << TempoBOP[1] << " horas" << endl;
	    fout << "\nTempo total: \t\t" << TempoFase [1] + TempoFase [2] + TempoFase [3] + TempoFase [4] + TempoFase [5] + TempoBOP[0] + TempoBOP[1] << " horas" << endl;
		fout << "\nTempo total: \t\t" << (TempoFase [1] + TempoFase [2] + TempoFase [3] + TempoFase [4] + TempoFase [5] + TempoBOP[0] + TempoBOP[1]) / 24 << " dias" << endl;
	    
	    fout << "\n\n\n-------------------------       Volumes       -------------------------" << endl;
	    
		fout << "\n\nFase 1 e 2 utilizam agua do mar como fluido de perfuracao" << endl;
		fout << "\nVolume de fluido de perfuracao usado na Fase 3: \t" << volumeFluido[3] << " barris" << endl;
	    fout << "\nVolume de fluido de perfuracao usado na Fase 4: \t" << volumeFluido[4] << " barris" << endl;
	    fout << "\nVolume de fluido de perfuracao usado na Fase 5: \t" << volumeFluido[5] << " barris" << endl;
	    fout << "\nVolume Total de fluido de perfuracao usado: \t\t" << fluidoTotal << " barris" << endl;
	    
	    fout << "\n\nVolume de cimento usado na Fase 1: \t\t\t" << volumeCimento[1] << " barris" << endl;
	    fout << "\nVolume de cimento usado na Fase 2: \t\t\t" << volumeCimento[2] << " barris" << endl;
	    fout << "\nVolume de cimento usado na Fase 3: \t\t\t" << volumeCimento[3] << " barris" << endl;
	    fout << "\nVolume de cimento usado na Fase 4: \t\t\t" << volumeCimento[4] << " barris" << endl;
	    fout << "\nVolume de cimento usado na Fase 5: \t\t\t" << volumeCimento[5] << " barris" << endl;
		fout << "\nVolume Total de cimento usado: \t\t\t\t" << cimentoTotal << " barris" << endl;
		
		fout.close ();
		
	
	}
	
	else
	{
		cout << "\n";
	}
	
		
	/// Cria objeto do tipo CGrafico
	CGrafico grafico(operacao, poco, perfuracao);
		
	string resposta_grafico;
		
	cout << "\n\nDeseja gerar grafico? (s/n): ";
	cin >> resposta_grafico;
	cin.get();
		
	if (resposta_grafico == "s")
	{
		grafico.PlotarGrafico();
		cout << "\n\n-------------------------  FIM DO PROGRAMA  -------------------------";
	}
	else
	{
		cout << "\n\n-------------------------  FIM DO PROGRAMA  -------------------------";
	}	

	
	cin.get();
    
	return 0;
	
}
