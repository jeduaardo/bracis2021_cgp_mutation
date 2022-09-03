#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include "cgp v2.h"
#include <string>
#include <map>
#include<cstdlib>
#include <sstream> 




using namespace std;


void gera_rede_saida(int ni, int nTests, vector<vector<int>> OTIMIZADOS_LOCAL){

	//vector<vector<int>> OTIMIZADOS_LOCAL = {{1,1,1},{1,1,1},{1,1,1}};

	ofstream rankedEdges;
	string filename = "rankedEdges.csv";
	rankedEdges.open(filename);
	map<int, string> dicionario;
  //INICIO VSC:
  //dicionario[0] = "Dbx1";
  //dicionario[1] = "Dbx2";
  //dicionario[2] = "Irx3";
  //dicionario[3] = "Nkx22";
  //dicionario[4] = "Nkx61";
  //dicionario[5] = "Nkx62";
  //dicionario[6] = "Olig2";
  //dicionario[7] = "Pax6";
  //dicionario[8] = "Dbx1";
  //dicionario[9] = "Dbx2";
  //dicionario[10] = "Irx3";
  //dicionario[11] = "Nkx22";
  //dicionario[12] = "Nkx61";
  //dicionario[13] = "Nkx62";
  //dicionario[14] = "Olig2";
  //dicionario[15] = "Pax6"; 
  //FIM VSC
  //INICIO HSC:
  //dicionario[0] = "Cebpa";
  //dicionario[1] = "EgrNab";
  //dicionario[2] = "Eklf";
  //dicionario[3] = "Fli1";
  //dicionario[4] = "Fog1";
  //dicionario[5] = "Gata1";
  //dicionario[6] = "Gata2";
  //dicionario[7] = "Gfi1";
  //dicionario[8] = "Pu1";
  //dicionario[9] = "Scl";
  //dicionario[10] = "cJun"; 
  //dicionario[11] = "Cebpa";
  //dicionario[12] = "EgrNab";
  //dicionario[13] = "Eklf";
  //dicionario[14] = "Fli1";
  //dicionario[15] = "Fog1";
  //dicionario[16] = "Gata1";
  //dicionario[17] = "Gata2";
  //dicionario[18] = "Gfi1";
  //dicionario[19] = "Pu1";
  //dicionario[20] = "Scl";
  //dicionario[21] = "cJun"; 
  //FIM HSC  
  //INICIO mCAD:
  dicionario[0] = "Coup";
  dicionario[1] = "Emx2";
  dicionario[2] = "Fgf8";
  dicionario[3] = "Pax6";
  dicionario[4] = "Sp8";
  dicionario[5] = "Coup";
  dicionario[6] = "Emx2";
  dicionario[7] = "Fgf8";
  dicionario[8] = "Pax6";
  dicionario[9] = "Sp8";  
  //FIM mCAD
  //dicionario[7] = "FOXL2";
  //dicionario[8] = "GATA4";
  //dicionario[9] = "NR0B1";
  //dicionario[10] = "NR5A1";
  //dicionario[11] = "PGD2";
  //dicionario[12] = "RSPO1";
  //dicionario[13] = "SOX9";
  //dicionario[14] = "SRY";
  //dicionario[15] = "UGR";
  //dicionario[16] = "WNT4";
  //dicionario[17] = "WT1mKTS";
  //dicionario[18] = "WT1pKTS";
  //dicionario[19] = "AMH";
  //dicionario[20] = "CBX2";
  //dicionario[21] = "CTNNB1";
  //dicionario[22] = "DHH";
  //dicionario[23] = "DKK1";
  //dicionario[24] = "DMRT1";
  //dicionario[25] = "FGF9";
  //dicionario[26] = "FOXL2";
  //dicionario[27] = "GATA4";
  //dicionario[28] = "NR0B1";
  //dicionario[29] = "NR5A1";
  //dicionario[30] = "PGD2";
  //dicionario[31] = "RSPO1";
  //dicionario[32] = "SOX9";
  //dicionario[33] = "SRY";
  //dicionario[34] = "UGR";
  //dicionario[35] = "WNT4";
  //dicionario[36] = "WT1mKTS";
  //dicionario[37] = "WT1pKTS";





	int metade = ni/2;



  for(int i = 0; i < OTIMIZADOS_LOCAL.size(); i++){
    vector<int> vetor_local = {};
    for(int j = 0; j < ni; j++){
      int mycount = count(OTIMIZADOS_LOCAL[i].begin(), OTIMIZADOS_LOCAL[i].end(), j);
      //cout << "ESTOU NO J: " << j << endl;
      //cout << mycount << endl;
      vetor_local.push_back(mycount);
    }
    for(int k = 0; k < vetor_local.size(); k++){
      if(vetor_local[k] != 0){
        //cout << "VALOR EH " << vetor_local[k] << endl;
        rankedEdges << dicionario[k] << "\t" << dicionario[i] << "\t";
        float conta = (float)vetor_local[k] / (float)nTests;
        if(k >= metade){
          rankedEdges << "-" << conta;
        }
        else{
          rankedEdges << conta;
        }
        rankedEdges << "\n";
      }
    }
  }

}



void printFirstSolution(Individual * p, string Letra, string test){

	ofstream arquivo_factivel;
    string filename = Letra + "_" + test + "_feasible.txt";
    arquivo_factivel.open(filename);
    arquivo_factivel << "Test Number: " << test << endl;
    for(int outputs = 0; outputs < p->no; outputs++){
    	arquivo_factivel << "Output " << outputs << endl;
    	cout << "Output " << outputs << endl;
    	sort(p->phenotype[outputs].begin(), p->phenotype[outputs].end());
    	vector<int> phenotype_local = {};

    	for(int nodes = 0; nodes < p->phenotype[outputs].size(); nodes++){

			auto search = find(phenotype_local.begin(), phenotype_local.end(), p->phenotype[outputs][nodes]);

      

			if(search == phenotype_local.end()){
				phenotype_local.push_back(p->phenotype[outputs][nodes]);
			}	


    	}





    	for(int actives = 0; actives < phenotype_local.size(); actives++){
        	int currentActive = phenotype_local[actives];
        	vector<int> gene = p->genotype[currentActive];
        	cout << "NODE: " << currentActive << " - ";
        	arquivo_factivel << "NODE: " << currentActive << " - ";
        	for(int i = 0; i < gene.size(); i++){
          		cout << gene[i] << "  ";
          		arquivo_factivel << gene[i] << "  ";
        	}
        	cout << "\n";
        	arquivo_factivel << "\n";
    	}
    }
    arquivo_factivel.close();
}



void printFinalSolution(vector<vector<int>> genotype, string Letra, string test, int ni_c, int no_c, int nc_c, int nr_c, int lb_c){
	Individual * local = new Individual(ni_c, no_c, nc_c, nr_c, lb_c, genotype);
  	for(int j = 0; j < local->no; j++){
    	int currentOutput = local->size + local->ni + j;
      	local->phenotype[j].push_back(currentOutput);
      	local->phenotype[j].push_back(local->genotype[currentOutput][0]);
      	local->getActiveNodes(j, local->genotype[currentOutput][0]);
  	}
  	ofstream arquivo_final;
  	string filename = Letra + "_" + test + "_optimized.txt";
  	arquivo_final.open(filename);
  	for(int outputs = 0; outputs < local->no; outputs++){
    	arquivo_final << "Output " << outputs << endl;
      	cout << "Output " << outputs << endl;
      	sort(local->phenotype[outputs].begin(), local->phenotype[outputs].end());
      
    	vector<int> phenotype_local = {};

    	for(int nodes = 0; nodes < local->phenotype[outputs].size(); nodes++){

			auto search = find(phenotype_local.begin(), phenotype_local.end(), local->phenotype[outputs][nodes]);
			if(search == phenotype_local.end()){
				phenotype_local.push_back(local->phenotype[outputs][nodes]);
			}	


    	}

      	for(int actives = 0; actives < phenotype_local.size(); actives++){
        	int currentActive = phenotype_local[actives];
          	vector<int> gene = local->genotype[currentActive];
          	cout << "NODE: " << currentActive << " - ";
          	arquivo_final << "NODE: " << currentActive << " - ";
          	for(int i = 0; i < gene.size(); i++){
              	cout << gene[i] << "  ";
              	arquivo_final << gene[i] << "  ";
          	}
      		cout << "\n";
      		arquivo_final << "\n";
      	}
  	}
  	local->countLE3();
  	cout << local->LE << endl;
  	arquivo_final.close();
}



void printNonFeasibleSolution(vector<vector<int>> genotype, string Letra, string test, int ni_c, int no_c, int nc_c, int nr_c, int lb_c){
	Individual * local = new Individual(ni_c, no_c, nc_c, nr_c, lb_c, genotype);
  	for(int j = 0; j < local->no; j++){
    	int currentOutput = local->size + local->ni + j;
      	local->phenotype[j].push_back(currentOutput);
      	local->phenotype[j].push_back(local->genotype[currentOutput][0]);
      	local->getActiveNodes(j, local->genotype[currentOutput][0]);
  	}
  	ofstream arquivo_final;
  	string filename = Letra + "_" + test + "_nonFeasible.txt";
  	arquivo_final.open(filename);
  	for(int outputs = 0; outputs < local->no; outputs++){
    	arquivo_final << "Output " << outputs << endl;
      	cout << "Output " << outputs << endl;
      	sort(local->phenotype[outputs].begin(), local->phenotype[outputs].end());
      
    	vector<int> phenotype_local = {};

    	for(int nodes = 0; nodes < local->phenotype[outputs].size(); nodes++){

			auto search = find(phenotype_local.begin(), phenotype_local.end(), local->phenotype[outputs][nodes]);
			if(search == phenotype_local.end()){
				phenotype_local.push_back(local->phenotype[outputs][nodes]);
			}	


    	}

      	for(int actives = 0; actives < phenotype_local.size(); actives++){
        	int currentActive = phenotype_local[actives];
          	vector<int> gene = local->genotype[currentActive];
          	cout << "NODE: " << currentActive << " - ";
          	arquivo_final << "NODE: " << currentActive << " - ";
          	for(int i = 0; i < gene.size(); i++){
              	cout << gene[i] << "  ";
              	arquivo_final << gene[i] << "  ";
          	}
      		cout << "\n";
      		arquivo_final << "\n";
      	}
  	}
  	arquivo_final.close();
}


int main()
{ 

   int MELHOR_APTIDAO;
   vector<vector<int>> dAllOutputs = {};
   string myText;
   ifstream MyReadFile("saida2.txt");
   int linha = 0;
   while (getline (MyReadFile, myText)) {
  // Output the text from the file
      dAllOutputs.push_back({});
      for(int i = 0; i < myText.size(); i++){
         int valor_atual = myText[i];
         int ivalor_atual = valor_atual - '0';
         dAllOutputs[linha].push_back(ivalor_atual);
      }

      cout << myText;
      linha += 1;
   }
   MyReadFile.close();
  

   cout << dAllOutputs[0].size() << endl;
   map<string, int> intparam;
   map<string, string> strparam;
   map<int, string> alfabeto;
   intparam["nTests"] = 5;
   intparam["nEvaluations"] = 50000;
   intparam["initialSeed"] = 16;
   intparam["mu"] = 1;
   intparam["lambda"] = 1;
   intparam["ni"] = 10;
   intparam["no"] = 1;
   intparam["nc"] = 100;
   intparam["nr"] = 1;
   intparam["lb"] = 100;
   alfabeto[0] = "A"; 
   alfabeto[1] = "B";
   alfabeto[2] = "C";
   alfabeto[3] = "D";
   alfabeto[4] = "E";
   alfabeto[5] = "F";
   alfabeto[6] = "G";
   alfabeto[7] = "H";
   alfabeto[8] = "I";
   alfabeto[9] = "J";
   alfabeto[10] = "K";
   alfabeto[11] = "L";
   alfabeto[12] = "M";
   alfabeto[13] = "N";
   alfabeto[14] = "O";
   alfabeto[15] = "P";
   alfabeto[16] = "Q";
   alfabeto[17] = "R";
   alfabeto[18] = "S";
   alfabeto[19] = "T";
   alfabeto[20] = "U";
   alfabeto[21] = "V";
   alfabeto[22] = "W";
   alfabeto[23] = "X";
   alfabeto[24] = "Y";
   alfabeto[25] = "Z";                        

   //gera_rede_saida(6, 3);
   vector<vector<int>> OTIMIZADOS = {};

   for(int saida = 0; saida < dAllOutputs.size(); saida++){
   	OTIMIZADOS.push_back({});
   		vector<vector<int>> dOutput = {dAllOutputs[saida]};
   		for(int test = 0; test < intparam["nTests"]; test++){
   			srand(intparam["initialSeed"]+test);
   			cout << "Initializing Test Number " << test << "/" << intparam["nTests"]-1 << " for variable " << alfabeto[saida] <<endl;
   			
   			Population * k = new Population(intparam["mu"],intparam["lambda"], dOutput); 
   			k->clearPopulation();

   			for (int i=0; i<intparam["mu"]+intparam["lambda"]; i++){
      			k->Pop.push_back(new Individual(intparam["ni"], intparam["no"], intparam["nc"], intparam["nr"], intparam["lb"], {}));
      			k->Pop[i]->code_genotype2();
      			for(int j = 0; j < k->Pop[i]->no; j++){
         			int currentOutput = k->Pop[i]->size + k->Pop[i]->ni + j;
    	 			k->Pop[i]->phenotype[j].push_back(currentOutput);
    	 			k->Pop[i]->phenotype[j].push_back(k->Pop[i]->genotype[currentOutput][0]);
    	 			k->Pop[i]->getActiveNodes(j, k->Pop[i]->genotype[currentOutput][0]);
      			}
	   
	  			k->Pop[i]->evalIndividual(k->desiredOutputs);
		    }


    		vector<int> all_fitness;
 
    		for(int i =0; i<intparam["mu"]+intparam["lambda"];i++){
      			all_fitness.push_back(k->Pop[i]->fitness);
      			if(k->Pop[i]->fitness == (pow(2, intparam["ni"]/2)) * k->Pop[i]->no){
        			cout << "Feasible Solution Found on Initial Population" << endl;
        			string nome2;
        			if (test == 0){
          				nome2 = "0";
        			}
        			if (test == 1){
          				nome2 = "1";
        			}
        			if (test == 2){
          				nome2 = "2";
        			}
        			if (test == 3){
          				nome2 = "3";
        			}
        			if (test == 4){
          				nome2 = "4";
        			}                                
        			printFirstSolution(k->Pop[i], alfabeto[saida], nome2);
        			k->parentUpdateOptimize1(k->Pop[i]->genotype, k->Pop[i]->fitness, k->Pop[i]->LE);
        			k->feasible = 1;        
      			}
    		}

    		k->parentUpdateIndividual(k->Pop[max_element( all_fitness.begin(), all_fitness.end()) - all_fitness.begin()]->genotype, k->Pop[max_element( all_fitness.begin(), all_fitness.end()) - all_fitness.begin()]->fitness, intparam["ni"], intparam["no"], intparam["nc"], intparam["nr"], intparam["lb"]); // ATUALIZA CORRETAMENTE O BEST

    		int evaluations = 0;
    		while(evaluations < intparam["nEvaluations"]){
          //if(k->feasible == 1){
          //  break;
          //}
    			k->clearPopulation();

   				for (int i=0; i<intparam["lambda"]; i++){
        			k->Pop.push_back(new Individual(intparam["ni"], intparam["no"], intparam["nc"], intparam["nr"], intparam["lb"], k->best));
        
        			for(int j = 0; j < k->Pop[i]->no; j++){
            			int currentOutput = k->Pop[i]->size + k->Pop[i]->ni + j;
            			k->Pop[i]->phenotype[j].push_back(currentOutput);
            			k->Pop[i]->phenotype[j].push_back(k->Pop[i]->genotype[currentOutput][0]);
            			k->Pop[i]->getActiveNodes(j, k->Pop[i]->genotype[currentOutput][0]);
         			}
              if(k->feasible == 0){
                //k->Pop[i]->mutateSemanticSAM(k->desiredOutputs);    
                //k->Pop[i]->mutateSemanticSAMandInactive(k->desiredOutputs);
                //k->Pop[i]->mutateSemanticSAMOnly(k->desiredOutputs);
                //k->Pop[i]->mutateSAM();
                k->Pop[i]->mutateSemanticSAMOnlyPF50(k->desiredOutputs);


              }
              else{
                k->Pop[i]->mutateSAM();
                //k->Pop[i]->mutateSemanticSAMOnly(k->desiredOutputs);
              }
              

        			
         			for(int j = 0; j < k->Pop[i]->no; j++){
            			int currentOutput = k->Pop[i]->size + k->Pop[i]->ni + j;
            			k->Pop[i]->phenotype[j].push_back(currentOutput);
            			k->Pop[i]->phenotype[j].push_back(k->Pop[i]->genotype[currentOutput][0]);
            			k->Pop[i]->getActiveNodes(j, k->Pop[i]->genotype[currentOutput][0]);
         			}       
      
        			k->Pop[i]->evalIndividual(k->desiredOutputs);
        			evaluations += 1;
        			if(k->feasible == 1){
          				k->Pop[i]->countLE();
        			}
    			}


    			all_fitness.clear();
    			int max_fitness = pow(2, intparam["ni"]/2) * k->Pop[0]->no;


    			for(int i =0; i<intparam["lambda"];i++){
      				all_fitness.push_back(k->Pop[i]->fitness);
      
      
      				if(k->Pop[i]->fitness == max_fitness && k->feasible == 0){
        				cout << "Feasible Solution Found with " << evaluations << " evaluations." << endl;
        				string nome;
        				if (test == 0){
          					nome = "0";
        				}
        				if (test == 1){
          					nome = "1";
        				}
        				if (test == 2){
          					nome = "2";
        				}
        				if (test == 3){
          					nome = "3";
        				}
        				if (test == 4){
          					nome = "4";
        				}    
                //cout << "CHEGOU AQUI " << endl;   
                //cout << k->Pop[i]->phenotype.size() << endl;                         
        				printFirstSolution(k->Pop[i], alfabeto[saida], nome);
        				k->parentUpdateOptimize1(k->Pop[i]->genotype, k->Pop[i]->fitness, k->Pop[i]->LE);
        				k->feasible = 1;
        				break;
      				}

    			}
          
    			int greaterFitness = k->Pop[max_element( all_fitness.begin(), all_fitness.end()) - all_fitness.begin()]->fitness;

    			if(k->feasible == 0){
      				if(greaterFitness >= k->currentFitness){
        				k->parentUpdateIndividual(k->Pop[max_element( all_fitness.begin(), all_fitness.end()) - all_fitness.begin()]->genotype, k->Pop[max_element( all_fitness.begin(), all_fitness.end()) - all_fitness.begin()]->fitness, intparam["ni"], intparam["no"], intparam["nc"], intparam["nr"], intparam["lb"]); // ATUALIZA CORRETAMENTE O BEST
      				}

			    }
    			else{

      				k->parentUpdateOptimize();

    			}    

    			if(evaluations % 1000 == 0){
      				cout << "Evaluations: " << evaluations << " Fitness: " << k->currentFitness << endl;
      				cout << "Logic Elements " << k->currentLE << endl;

              /*
              if(k->feasible == 0){
                k->clearPopulation();

                for (int i=0; i<intparam["mu"]+intparam["lambda"]; i++){
                  k->Pop.push_back(new Individual(intparam["ni"], intparam["no"], intparam["nc"], intparam["nr"], intparam["lb"], {}));
                  k->Pop[i]->code_genotype2();
                    for(int j = 0; j < k->Pop[i]->no; j++){
                        int currentOutput = k->Pop[i]->size + k->Pop[i]->ni + j;
                        k->Pop[i]->phenotype[j].push_back(currentOutput);
                        k->Pop[i]->phenotype[j].push_back(k->Pop[i]->genotype[currentOutput][0]);
                        k->Pop[i]->getActiveNodes(j, k->Pop[i]->genotype[currentOutput][0]);
                  }
                
                k->Pop[i]->evalIndividual(k->desiredOutputs);
              }


              vector<int> all_fitness;


              for(int i =0; i<intparam["mu"]+intparam["lambda"];i++){
                  all_fitness.push_back(k->Pop[i]->fitness);
                  if(k->Pop[i]->fitness == (pow(2, intparam["ni"]/2)) * k->Pop[i]->no){
                    cout << "Feasible Solution Found on Initial Population" << endl;
                    string nome2;
                    if (test == 0){
                        nome2 = "0";
                    }
                    if (test == 1){
                        nome2 = "1";
                    }
                    if (test == 2){
                        nome2 = "2";
                    }
                    if (test == 3){
                        nome2 = "3";
                    }
                    if (test == 4){
                        nome2 = "4";
                    }                                
                    printFirstSolution(k->Pop[i], alfabeto[saida], nome2);
                    k->parentUpdateOptimize1(k->Pop[i]->genotype, k->Pop[i]->fitness, k->Pop[i]->LE);
                    k->feasible = 1;        
                  }
              }

              k->parentUpdateIndividual(k->Pop[max_element( all_fitness.begin(), all_fitness.end()) - all_fitness.begin()]->genotype, k->Pop[max_element( all_fitness.begin(), all_fitness.end()) - all_fitness.begin()]->fitness, intparam["ni"], intparam["no"], intparam["nc"], intparam["nr"], intparam["lb"]); // ATUALIZA CORRETAMENTE O BEST


            }


          */
    			}

    		} // Fim Processo Geracional WHILE
    		cout << "End of Test Number " << test << "/" << intparam["nTests"]-1 << " for variable " << alfabeto[saida] <<endl;
    		string nome2;
        	if (test == 0){
          		nome2 = "0";
        	}
        	if (test == 1){
          		nome2 = "1";
        	}
        	if (test == 2){
          		nome2 = "2";
        	}
        	if (test == 3){
          		nome2 = "3";
        	}
        	if (test == 4){
          		nome2 = "4";
        	} 
        	if(k->feasible == 1){
	    		printFinalSolution(k->best, alfabeto[saida], nome2, intparam["ni"], intparam["no"], intparam["nc"], intparam["nr"], intparam["lb"]);


				Individual * local = new Individual(intparam["ni"], intparam["no"], intparam["nc"], intparam["nr"], intparam["lb"], k->best);
  				for(int j = 0; j < local->no; j++){
    				int currentOutput = local->size + local->ni + j;
      				local->phenotype[j].push_back(currentOutput);
      				local->phenotype[j].push_back(local->genotype[currentOutput][0]);
      				local->getActiveNodes(j, local->genotype[currentOutput][0]);
  				}
  	
  
  				for(int outputs = 0; outputs < local->no; outputs++){
      				sort(local->phenotype[outputs].begin(), local->phenotype[outputs].end());
      
    				vector<int> phenotype_local = {};

    				for(int nodes = 0; nodes < local->phenotype[outputs].size(); nodes++){

						auto search = find(phenotype_local.begin(), phenotype_local.end(), local->phenotype[outputs][nodes]);
						if(search == phenotype_local.end()){
							phenotype_local.push_back(local->phenotype[outputs][nodes]);
						}	
    				}

      				for(int actives = 0; actives < phenotype_local.size(); actives++){
        				int currentActive = phenotype_local[actives];
        				if (currentActive < intparam["ni"]){
        					OTIMIZADOS[saida].push_back(currentActive);
        				}
      				}
  				}

          //for(int tg = 0; tg < OTIMIZADOS.size(); tg++){
          //  for(int tg1 = 0; tg1 < OTIMIZADOS[tg].size(); tg1++){
          //    cout << OTIMIZADOS[tg][tg1];
           // }
          //  cout << "\n\n";
          //}
    		}
    		else{
    			printNonFeasibleSolution(k->best, alfabeto[saida], nome2, intparam["ni"], intparam["no"], intparam["nc"], intparam["nr"], intparam["lb"]);
    		}
    		k->setStandard();
		} // Fim nTests
} //Fim nSaidas
//cout << "TAMANHO" << OTIMIZADOS.size() << endl;
gera_rede_saida(intparam["ni"], intparam["nTests"], OTIMIZADOS);

return 0;
} // Fim main