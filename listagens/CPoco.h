#ifndef CPOCO_H
#define CPOCO_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

/// Classe CPoco, que armazena as propriedades do poco, como profundidades, diametros e capacidades das fases do poco
/// Tambem calcula o numero de tubos necessarias e os volumes de fluido de perfuracao e de cimento
class CPoco
{
	// Atributos
	private:
		
		/// vetor que armazena as profundidades das fases do poco
		vector< double > profundidade;
		
		/// vetor que armazena o numero de tubos utilizados em cada fase	
		vector< double > numeroJuntas;
		
		/// vetor que armazena volume de fluido de perfuracao utilizado em cada fase
		vector< double > volumeFluido;
	
		/// vetor que armazena o volume de cimento utilizado em cada fase
		vector< double > volumeCimento;
	
		/// vetor que armazena o diametro da broca utilizada em cada fase
		vector< double > diametroBroca;
	
		/// vetor que armazena o diametro dos revestimentos utilizados em cada fase
		vector< double > diametroRevestimento;
		
		/// vetor que armazena as capacidades das brocas	
		vector< double > capacidadeBroca;
		
		/// vetor que armazena as capacidades dos revestimentos	
		vector< double > capacidadeRevestimento;
		
		/// variavel que armazena o diametro do drill pipe	
		double diametroDP;
	
		/// variavel que armazena a capacidade do drill pipe
		double capacidadeDP;
	
	// Metodos	  
	public:

		/// Construtor, define valores para os atributos e chama o metodo AtualizarPropriedades
		CPoco (vector< double > profundidade_) : profundidade(profundidade_)       
		{			
			diametroBroca = vector< double >(6);			
			diametroBroca[0] = 0;
			diametroBroca[1] = 36;
			diametroBroca[2] = 26;
			diametroBroca[3] = 17.5;
			diametroBroca[4] = 12.25;
			diametroBroca[5] = 8.5;
			
			diametroRevestimento = vector< double >(6);			
			diametroRevestimento[0] = 19;
			diametroRevestimento[1] = 30;
			diametroRevestimento[2] = 20;
			diametroRevestimento[3] = 13.375;
			diametroRevestimento[4] = 9.625;
			diametroRevestimento[5] = 7;
			
			capacidadeBroca = vector< double >(6);
			for (int i=0 ; i<6 ; i++)
			{
				capacidadeBroca[i] = 0.0031871*diametroBroca[i]*diametroBroca[i];
			}
			
			capacidadeRevestimento = vector< double >(6);
			for (int i=0 ; i<6 ; i++)
			{
				capacidadeRevestimento[i] = 0.0031871*diametroRevestimento[i]*diametroRevestimento[i];
			}
			
			diametroDP = 4.275;
	
			capacidadeDP = 0.0031871*diametroDP*diametroDP;
    
			AtualizarPropriedades();
    	}
		
		/// Metodo para atribuir valores a profundidade
		void SetProfundidade (vector< double > profundidade_)
		{			
			/// Salva a profundidade    
			profundidade = profundidade_;
    			
			/// Atualiza as outras propriedades do poco
			AtualizarPropriedades();    
		}
	
		/// Metodo que atualiza as propriedades do poco dependentes da profundidade de cada fase
		void AtualizarPropriedades()
		{			
			/// Atualiza o número de juntas
    		NumeroJuntas ();
    		
			/// Atualiza o volume de fluido
    		VolumeFluido ();
    		
			/// Atualiza o volume de cimento
			VolumeCimento ();    
		}
		
		/// Metodo para retornar a profundidade
		vector< double > GetProfundidade ()
		{			
			return profundidade;			
		}
		
		/// Metodo para retornar o numero de tubos
		vector< double > GetNumeroJuntas ()
		{			
			return numeroJuntas;			
		}
		
		/// Metodo para retornar o volume de cimento
		vector< double > GetVolumeCimento ()
		{			
			return volumeCimento;			
		}
		
		/// Metodo para retornar o volume de fluido de perfuracao
		vector< double > GetVolumeFluido ()
		{			
			return volumeFluido;			
		}
		
		/// Metodo para retornar a capacidade da broca
		vector< double > GetCapacidadeBroca ()
		{			
			return capacidadeBroca;			
		}
		
		/// Metodo para retornar a capacidade do revestimento
		vector< double > GetCapacidadeRevestimento ()
		{			
			return capacidadeRevestimento;			
		}
		
		/// Metodo para retornar a capacidade do drill pipe
		double GetCapacidadeDP ()
		{			
			return capacidadeDP;			
		}
		
		/// Metodo que calcula o numero de tubos utilizados em cada fase
		vector< double > NumeroJuntas ()
		{			
			numeroJuntas = vector< double >(6);
			numeroJuntas[0] = profundidade[0] / 15.0;
			
			for (int i = 1 ; i < 5 ; i++)
			{
				numeroJuntas[i] = (profundidade[i] - profundidade[0]) / 12.0;
			}
			
			numeroJuntas[5] = (profundidade[5] - profundidade[4] + 100.0) / 12.0;
			
			return numeroJuntas;			
		}
		
		/// Metodo que calcula o volume de fluido de perfuracao utilizado em cada fase; as fases 1 e 2 utilizam agua do mar e por isso nao sao calculadas
		vector< double > VolumeFluido ()
		{            
			volumeFluido = vector< double >(6, 0);
			
			for (int i = 3 ; i < 6 ; i++)
            {
				volumeFluido[i] = 1.1*((profundidade[i] - profundidade[i-1] + 10)*capacidadeBroca[i] + (profundidade[i-1] - profundidade[0])*capacidadeRevestimento[i-1] + profundidade[0]*capacidadeRevestimento[0]);
			}
    		
			return volumeFluido;		
		}
		
		/// Metodo que calcula os volumes de cimento utilizados nas fases
		vector< double > VolumeCimento ()
		{			
			volumeCimento = vector< double >(6);
			
			for (int i = 1 ; i < 3 ; i++)
			{
				volumeCimento[i] = 2.0*((profundidade[i]-profundidade[0])*(capacidadeBroca[i]-capacidadeRevestimento[i]));
			}
			
			for (int i = 3 ; i < 5 ; i++)
			{
				volumeCimento[i] = (profundidade[i]-profundidade[i-1]-100.0)*(capacidadeBroca[i]-capacidadeRevestimento[i]);
			}
			
			volumeCimento[5] = (profundidade[5]-profundidade[4])*(capacidadeBroca[5]-capacidadeRevestimento[5])+100.0*(capacidadeRevestimento[4]-capacidadeRevestimento[5])+60.0*capacidadeRevestimento[4];
			
			return volumeCimento;			
		}
	
};

#endif
