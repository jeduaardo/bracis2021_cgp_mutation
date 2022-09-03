#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <cmath>
#include<numeric>
using namespace std;





class Individual{
	public:
		int ni, no, nc, nr, lb, arity, size, fitness, LE;	
		vector<int> outputFitness;
		vector<vector<int>> genotype;
		vector<vector<int>> phenotype;
		vector<int> functionTable = {1,2,8,4,5,6,7};


		Individual(int ni_c, int no_c, int nc_c, int nr_c, int lb_c, vector<vector<int>> genotype_c){
			ni = ni_c;
			no = no_c;
			nc = nc_c;
			nr = nr_c;
			lb = lb_c;
			size = nc * nr;
			arity = 2;
			fitness = 0;
			LE = 1500;
			if(genotype_c.size() != 0){
				for(int i = 0; i < genotype_c.size(); i++){
					vector<int> vlocal = {};
					for(int j = 0; j < genotype_c[i].size(); j++){
						vlocal.push_back(genotype_c[i][j]);
					}
					genotype.push_back(vlocal);
				}

			}
			else{
				genotype = {};
			}
			for(int i = 0; i < no; i++){
				phenotype.push_back({});
				
			}
		};


		

	void code_genotype(){
		for (int i=0; i<ni; i++){
			genotype.push_back({i});
		}
		for (int i=0; i<size; i++)
		{
			int current_pos = ni + i;
			int current_col = (current_pos - ni + nr)/nr;

			int firstPossibleValue = 0;

			if (current_col - lb > 0) {
				firstPossibleValue = ni + ((current_col - lb - 1) * nr);
			}

			int lastPossibleValue = ((current_col - 1) * nr) - 1 + ni;


			vector<int> currentGene = {};

			int inputA = rand()%(lastPossibleValue-firstPossibleValue + 1) + firstPossibleValue;
			int inputB = rand()%(lastPossibleValue-firstPossibleValue + 1) + firstPossibleValue;

			int functionIndex = rand() % functionTable.size();

			int function = functionTable[functionIndex];

			currentGene.push_back(inputA);
			currentGene.push_back(inputB);
			currentGene.push_back(function);
			genotype.push_back(currentGene);
		}
		int maxOutput = ni + (nc * nr) - 1;

		for (int i = 0; i < no; i++){
			vector<int> currentOutput = {};
			currentOutput.push_back(rand()%(maxOutput-0 + 1) + 0);
			genotype.push_back(currentOutput);
		}

		
		
		
	};


	void code_genotype2(){
		for (int i=0; i<ni; i++){
			genotype.push_back({i});
		}
		for (int i=0; i<size; i++)
		{
			int current_pos = ni + i;
			int current_col = (current_pos - ni + nr)/nr;

			int firstPossibleValue = 0;

			if (current_col - lb > 0) {
				firstPossibleValue = ni + ((current_col - lb - 1) * nr);
			}

			int lastPossibleValue = ((current_col - 1) * nr) - 1 + ni;


			vector<int> currentGene = {};

			int inputA = rand()%(lastPossibleValue-firstPossibleValue + 1) + firstPossibleValue;
			int inputB = rand()%(lastPossibleValue-firstPossibleValue + 1) + firstPossibleValue;

			int functionIndex = rand() % functionTable.size();

			int function = functionTable[functionIndex];

			currentGene.push_back(inputA);
			currentGene.push_back(inputB);
			currentGene.push_back(function);
			genotype.push_back(currentGene);
		}
		int maxOutput = ni + (nc * nr) - 1;

		for (int i = 0; i < no; i++){
			vector<int> currentOutput = {};
			currentOutput.push_back(rand() % ni);         // value in the range 0 to ni
			//currentOutput.push_back(rand()%(maxOutput-0 + 1) + 0);
			genotype.push_back(currentOutput);
		}

		
		
		
	};	


	void countLE(){
		vector<int> local_LE = {0};
		vector<int> evaluatedNodes = {};
		for(int outputs = 0; outputs < no; outputs++){
			vector<int> local_phenotype = {};
			for(int nodesL=0; nodesL<phenotype[outputs].size(); nodesL++){
				int actual_node = phenotype[outputs][nodesL];
				auto search2 = find(local_phenotype.begin(), local_phenotype.end(), actual_node);
				if(search2 == local_phenotype.end()){
					local_phenotype.push_back(actual_node);
				}
			}
			//for(int i =0; i < local_phenotype.size(); i++){
			//	cout << local_phenotype[i] << endl;
			//}
			//sort(phenotype[outputs].begin(), phenotype[outputs].end());
			sort(local_phenotype.begin(), local_phenotype.end());
			for(int nodes_index = 0; nodes_index < local_phenotype.size(); nodes_index++){
				int nodes = local_phenotype[nodes_index];
				if(nodes >= ni && nodes < (nc*nr + ni)){
					int nodeFunction = genotype[nodes][2];
					auto search = find(evaluatedNodes.begin(), evaluatedNodes.end(), nodes);
					if(search == evaluatedNodes.end()){
						local_LE[0] += 1;
						evaluatedNodes.push_back(nodes);
					}					
				}
			}
		}

		LE = local_LE[0];
	}


	void countLE3(){
		vector<int> local_LE = {0};
		vector<int> evaluatedNodes = {};
		for(int outputs = 0; outputs < no; outputs++){
			vector<int> local_phenotype = {};
			for(int nodesL=0; nodesL<phenotype[outputs].size(); nodesL++){
				int actual_node = phenotype[outputs][nodesL];
				auto search2 = find(local_phenotype.begin(), local_phenotype.end(), actual_node);
				if(search2 == local_phenotype.end()){
					local_phenotype.push_back(actual_node);
				}
			}
			//for(int i =0; i < local_phenotype.size(); i++){
			//	cout << local_phenotype[i] << endl;
			//}
			//sort(phenotype[outputs].begin(), phenotype[outputs].end());
			sort(local_phenotype.begin(), local_phenotype.end());
			for(int nodes_index = 0; nodes_index < local_phenotype.size(); nodes_index++){
				int nodes = local_phenotype[nodes_index];
				if(nodes >= ni && nodes < (nc*nr + ni)){
					int nodeFunction = genotype[nodes][2];
					auto search = find(evaluatedNodes.begin(), evaluatedNodes.end(), nodes);
					if(search == evaluatedNodes.end()){
						local_LE[0] += 1;
						evaluatedNodes.push_back(nodes);
					}					
				}
			}
			for(int i = 0; i < evaluatedNodes.size(); i++){
				cout << evaluatedNodes[i] << endl;
			}
		}

		LE = local_LE[0];
	}






	void mutateSAM(){

		vector<int> all_actives = {};
		for(int outputs = 0; outputs < no; outputs++){
			for(int actives_index = 0; actives_index < phenotype[outputs].size(); actives_index++){
				int actives = phenotype[outputs][actives_index];
				auto search = find(all_actives.begin(), all_actives.end(), actives);
				if (search == all_actives.end()){
					all_actives.push_back(actives);
				}
			}
		}
		
		bool selectedActive = 0;
		int v_local = 0;


		while(selectedActive == 0){
			int firstPossibleValue = ni;
			int lastPossibleValue = nc*nr + ni + no - 1;
			int chosen = rand()%(lastPossibleValue-firstPossibleValue + 1) + firstPossibleValue;
			v_local += 1;
			auto search2 = find(all_actives.begin(), all_actives.end(), chosen);
			if(search2 != all_actives.end()){
				selectedActive = 1;

			}
			vector<int> chosen_node = genotype[chosen];


			if(chosen_node.size() == 1){
				int firstPossibleValueOutput = 0;
				int lastPossibleValueOutput = nc*nr + ni - 1;
				int chosenOutput = rand()%(lastPossibleValueOutput-firstPossibleValueOutput + 1) + firstPossibleValueOutput;
				genotype[chosen][0] = chosenOutput;

			}
			else{
				int firstPossibleValueGeneIndex = 0;
				int lastPossibleValueGeneIndex = arity;
				int chosen_geneIndex = rand()%(lastPossibleValueGeneIndex-firstPossibleValueGeneIndex + 1) + firstPossibleValueGeneIndex;
				if(chosen_geneIndex == arity){
					int functionIndex = rand() % functionTable.size();

					genotype[chosen][chosen_geneIndex] = functionTable[functionIndex];
				}
				else{
					int firstPossibleValueInput;
					int lastPossibleValueInput;
					int current_col = (chosen - ni + nr) / nr;
					if(current_col - lb > 0){
						firstPossibleValueInput = ni + ((current_col - lb - 1) * nr);
					}
					else{
						firstPossibleValueInput = 0;
					}
					lastPossibleValueInput = ((current_col - 1) * nr) - 1 + ni;

					int new_value = rand()%(lastPossibleValueInput-firstPossibleValueInput + 1) + firstPossibleValueInput;
					while(new_value == chosen_node[chosen_geneIndex]){
						new_value = rand()%(lastPossibleValueInput-firstPossibleValueInput + 1) + firstPossibleValueInput;
					}
					genotype[chosen][chosen_geneIndex] = new_value;

				}

			}

		}

	}





	void mutateSemanticSAM(vector<vector<int>> &dOutput){


		vector<int> all_actives = {};
		for(int outputs = 0; outputs < no; outputs++){
			for(int actives_index = 0; actives_index < phenotype[outputs].size(); actives_index++){
				int actives = phenotype[outputs][actives_index];
				auto search = find(all_actives.begin(), all_actives.end(), actives);
				if (search == all_actives.end()){
					all_actives.push_back(actives);
				}
			}
		}
		
		bool selectedActive = 0;
		int v_local = 0;


		while(selectedActive == 0){
			int firstPossibleValue = ni;
			int lastPossibleValue = nc*nr + ni + no - 1;
			int chosen = rand()%(lastPossibleValue-firstPossibleValue + 1) + firstPossibleValue;
			v_local += 1;
			auto search2 = find(all_actives.begin(), all_actives.end(), chosen);
			if(search2 != all_actives.end()){
				selectedActive = 1;

			}

			if(selectedActive == 0){



					vector<int> chosen_node = genotype[chosen];


					if(chosen_node.size() == 1){
						int firstPossibleValueOutput = 0;
						int lastPossibleValueOutput = nc*nr + ni - 1;
						int chosenOutput = rand()%(lastPossibleValueOutput-firstPossibleValueOutput + 1) + firstPossibleValueOutput;
						genotype[chosen][0] = chosenOutput;

					}
					else{
						int firstPossibleValueGeneIndex = 0;
						int lastPossibleValueGeneIndex = arity;
						int chosen_geneIndex = rand()%(lastPossibleValueGeneIndex-firstPossibleValueGeneIndex + 1) + firstPossibleValueGeneIndex;
						if(chosen_geneIndex == arity){
							int functionIndex = rand() % functionTable.size();

							genotype[chosen][chosen_geneIndex] = functionTable[functionIndex];
						}
						else{
							int firstPossibleValueInput;
							int lastPossibleValueInput;
							int current_col = (chosen - ni + nr) / nr;
							if(current_col - lb > 0){
								firstPossibleValueInput = ni + ((current_col - lb - 1) * nr);
							}
							else{
								firstPossibleValueInput = 0;
							}
							lastPossibleValueInput = ((current_col - 1) * nr) - 1 + ni;

							int new_value = rand()%(lastPossibleValueInput-firstPossibleValueInput + 1) + firstPossibleValueInput;
							while(new_value == chosen_node[chosen_geneIndex]){
								new_value = rand()%(lastPossibleValueInput-firstPossibleValueInput + 1) + firstPossibleValueInput;
							}
							genotype[chosen][chosen_geneIndex] = new_value;

						}

					}



			}
			else{

				//chosen node é o chosen

					vector<int> chosen_node = genotype[chosen];

					//Muta Output
					if(chosen_node.size() == 1){
						int firstPossibleValueOutput = 0;
						int lastPossibleValueOutput = nc*nr + ni - 1;
						int chosenOutput = rand()%(lastPossibleValueOutput-firstPossibleValueOutput + 1) + firstPossibleValueOutput;
						genotype[chosen][0] = chosenOutput;

					}
					else{
						//Muta Porta
						int firstPossibleValueGeneIndex = 0;
						int lastPossibleValueGeneIndex = arity;
						int chosen_geneIndex = rand()%(lastPossibleValueGeneIndex-firstPossibleValueGeneIndex + 1) + firstPossibleValueGeneIndex;
						if(chosen_geneIndex == arity){
							int functionIndex = rand() % functionTable.size();

							genotype[chosen][chosen_geneIndex] = functionTable[functionIndex];
						}
						else{
							//Muta Entrada
							int originalInput = genotype[chosen][chosen_geneIndex];
							vector<int> previousNodes;
							for(int i=0; i<chosen; i++){
								if(i >= ni){
									previousNodes.push_back(i);
								}
							}
							//cout << "Chosen Node: " << chosen << endl;

							vector<int> all_fitness_nodes;

							for(int i=0; i<previousNodes.size(); i++){
								//cout << previousNodes[i] << endl;


							genotype[chosen][chosen_geneIndex] = previousNodes[i];


							//Descobrir nós ativos

		        			for(int j = 0; j < no; j++){
		        				phenotype[j].clear();
		            			int currentOutput = size + ni + j;
		            			phenotype[j].push_back(currentOutput);
		            			phenotype[j].push_back(genotype[currentOutput][0]);
		            			getActiveNodes(j, genotype[currentOutput][0]);
		         			}


							//Montagem da Tabela Verdade
								vector<vector<int>> local_tt;
								int half = ni/2;
								for(int i = 0; i < half; i++){
									local_tt.push_back({});
									int proportion = pow(2, half) / pow(2, i + 1);
									for(int divisions = 0; divisions < pow(2, i + 1); divisions++){
										for(int bits = 0; bits < proportion; bits++){
											if(divisions % 2 == 0){
												local_tt[i].push_back(0);
											}
											else{
												local_tt[i].push_back(1);
											}
										}
									}
								}
								for(int i = 0; i < half; i++){
									local_tt.push_back({});
									int proportion = pow(2, half) / pow(2, i + 1);
									for(int divisions = 0; divisions < pow(2, i + 1); divisions++){
										for(int bits = 0; bits < proportion; bits++){
											if(divisions % 2 == 0){
												local_tt[i + half].push_back(1);
											}
											else{
												local_tt[i + half].push_back(0);
											}
										}
									}
								}		



								for(int i = 0; i<size; i++){
									local_tt.push_back({});
								}							



								vector<int> all_actives = {};
								for(int i = 0; i < no; i++){
									for(int j = 0; j < phenotype[i].size(); j++){
										auto search_active = find(all_actives.begin(), all_actives.end(), phenotype[i][j]);
										if (search_active == all_actives.end()){
											all_actives.push_back(phenotype[i][j]);
										}
									}
								}
								sort(all_actives.begin(), all_actives.end());


								for(int i = 0; i < all_actives.size(); i++){
									int actives = all_actives[i];
									if(actives >= ni && actives < size + ni){
										vector<int> node = genotype[actives];
										int inputA = node[0];
										int inputB = node[1];
										int function = node[2];

										for(int bits = 0; bits < pow(2, half); bits ++){
											int v1 = local_tt[inputA][bits];
											int v2 = local_tt[inputB][bits];
											int v3;
											if(function == 1){
												v3 = v1 && v2;
												local_tt[actives].push_back(v3);

											}
											else{
												if(function == 2){
													v3 = v1 || v2;
													local_tt[actives].push_back(v3);
												}
												else{
													if(function == 3){
														v3 = (!v1);
														local_tt[actives].push_back(!v1);
													}
													else{
														if(function == 4){
															v3 = ((!v1) && (v2)) || ((v1) && (!v2));
															local_tt[actives].push_back(v3);
														}
													}
												}
											}


											if(function == 5){
												v3 = !(v1 && v2);
												local_tt[actives].push_back(v3);
												//cout << "EH NAND" << endl;
											}
											if(function == 6){
												v3 = !(v1 || v2);
												local_tt[actives].push_back(v3);
												//cout << "EH NOR" << endl;
											}
											if(function == 7){
												v3 = !(((!v1) && (v2)) || ((v1) && (!v2)));
												local_tt[actives].push_back(v3);
												//cout << "EH XNOR" << endl;
											}
											if(function == 8){
												//EH NOT
												if(local_tt[inputA][bits] == 0){
													local_tt[actives].push_back(1);	
												}
												else{
													local_tt[actives].push_back(0);
												}
												
											}
										}
									}
								}



							//adiciona aptidao no vetor de aptidoes para cada nó

							//int current_fitness = 0;
							//int current_output = size + ni;				
							//vector<int> tt_currentOutput = local_tt[genotype[current_output][0]];

							//for(int bits = 0; bits < tt_currentOutput.size(); bits++){
							//	if(tt_currentOutput[bits] == dOutput[0][bits] || dOutput[0][bits] == 9){
							//		
							//		current_fitness += 1;
							//	}
							//}
							//all_fitness_nodes.push_back(current_fitness);

							//vector<int> local_fitness = {};
							for(int outputs = 0; outputs < no; outputs++){
								int current_fitness = 0;
								int current_output = size + ni + outputs;

								vector<int> tt_currentOutput = local_tt[genotype[current_output][0]];

								for(int bits = 0; bits < tt_currentOutput.size(); bits++){
									if(tt_currentOutput[bits] == dOutput[outputs][bits] || dOutput[outputs][bits] == 9){
										
										current_fitness += 1;
									}
								}
								all_fitness_nodes.push_back(current_fitness);
								
							}							



							} //for dos nós

							//cout << "AQUI" << endl;
							//for(int i=0; i<all_fitness_nodes.size(); i++){
							//	cout << all_fitness_nodes[i] << endl;
							//}

							int argMax = distance(all_fitness_nodes.begin(), max_element(all_fitness_nodes.begin(), all_fitness_nodes.end()));
							//cout << "ARGMAX " << argMax << endl;
							int newInput;
							if(all_fitness_nodes.size() == 0){
								newInput = originalInput;
							}
							else{
								newInput = previousNodes[argMax];
							}
							genotype[chosen][chosen_geneIndex] = newInput;
							// atribui o melhor valor de entrada agora


						} //fecha o else do muta Entrada

					} // fecha else				

			} // fecha else





		} //fecha while

	} //fecha procedimento





	void mutateSemanticSAMandInactive(vector<vector<int>> &dOutput){


		vector<int> all_actives = {};
		for(int outputs = 0; outputs < no; outputs++){
			for(int actives_index = 0; actives_index < phenotype[outputs].size(); actives_index++){
				int actives = phenotype[outputs][actives_index];
				auto search = find(all_actives.begin(), all_actives.end(), actives);
				if (search == all_actives.end()){
					all_actives.push_back(actives);
				}
			}
		}
		

		bool selectedActive = 0;
		int v_local = 0;





		vector<int> all_inactives = {};

		for(int i = ni; i < (nc*nr + ni + no - 1); i++){
			auto searchActive = find(all_actives.begin(), all_actives.end(), i);
			if(searchActive == all_actives.end()){
				all_inactives.push_back(i);

					for(int j = 0; j <= arity; j++){
						if(j < arity){
							//cout << "muta input " << j << endl;

							int firstPossibleValueInputLocal;
							int lastPossibleValueInputLocal;
							int current_col = (i - ni + nr) / nr;
							if(current_col - lb > 0){
								firstPossibleValueInputLocal = ni + ((current_col - lb - 1) * nr);
							}
							else{
								firstPossibleValueInputLocal = 0;
							}
							lastPossibleValueInputLocal = ((current_col - 1) * nr) - 1 + ni;

							int new_valueLocal = rand()%(lastPossibleValueInputLocal-firstPossibleValueInputLocal + 1) + firstPossibleValueInputLocal;
							while(new_valueLocal == genotype[i][j]){
								new_valueLocal = rand()%(lastPossibleValueInputLocal-firstPossibleValueInputLocal + 1) + firstPossibleValueInputLocal;
							}
							genotype[i][j] = new_valueLocal;


						} //fecha if mutação input
						else{
							//cout << "Muta output" << j << endl;
							int functionIndexLocal = rand() % functionTable.size();
							genotype[i][j] = functionTable[functionIndexLocal];
						} //fecha else para mutação porta
					} // fecha arity



			} // fecha if do search active
			
		} // fecha for de todos os nós para encontrar os inativos





		while(selectedActive == 0){
			int firstPossibleValue = ni;
			int lastPossibleValue = nc*nr + ni + no - 1;
			//int chosen = rand()%(lastPossibleValue-firstPossibleValue + 1) + firstPossibleValue;
			int chosenIndex = rand() % all_actives.size();
			int chosen = all_actives[chosenIndex];
			v_local += 1;
			auto search2 = find(all_actives.begin(), all_actives.end(), chosen);
			if(search2 != all_actives.end()){
				selectedActive = 1;

			}


			if(selectedActive == 0){



					vector<int> chosen_node = genotype[chosen];


					if(chosen_node.size() == 1){
						int firstPossibleValueOutput = 0;
						int lastPossibleValueOutput = nc*nr + ni - 1;
						int chosenOutput = rand()%(lastPossibleValueOutput-firstPossibleValueOutput + 1) + firstPossibleValueOutput;
						genotype[chosen][0] = chosenOutput;

					}
					else{
						int firstPossibleValueGeneIndex = 0;
						int lastPossibleValueGeneIndex = arity;
						int chosen_geneIndex = rand()%(lastPossibleValueGeneIndex-firstPossibleValueGeneIndex + 1) + firstPossibleValueGeneIndex;
						if(chosen_geneIndex == arity){
							int functionIndex = rand() % functionTable.size();

							genotype[chosen][chosen_geneIndex] = functionTable[functionIndex];
						}
						else{
							int firstPossibleValueInput;
							int lastPossibleValueInput;
							int current_col = (chosen - ni + nr) / nr;
							if(current_col - lb > 0){
								firstPossibleValueInput = ni + ((current_col - lb - 1) * nr);
							}
							else{
								firstPossibleValueInput = 0;
							}
							lastPossibleValueInput = ((current_col - 1) * nr) - 1 + ni;

							int new_value = rand()%(lastPossibleValueInput-firstPossibleValueInput + 1) + firstPossibleValueInput;
							while(new_value == chosen_node[chosen_geneIndex]){
								new_value = rand()%(lastPossibleValueInput-firstPossibleValueInput + 1) + firstPossibleValueInput;
							}
							genotype[chosen][chosen_geneIndex] = new_value;

						}

					}



			}
			else{

				//chosen node é o chosen

					vector<int> chosen_node = genotype[chosen];

					//Muta Output
					if(chosen_node.size() == 1){
						int firstPossibleValueOutput = 0;
						int lastPossibleValueOutput = nc*nr + ni - 1;
						int chosenOutput = rand()%(lastPossibleValueOutput-firstPossibleValueOutput + 1) + firstPossibleValueOutput;
						genotype[chosen][0] = chosenOutput;

					}
					else{
						//Muta Porta
						int firstPossibleValueGeneIndex = 0;
						int lastPossibleValueGeneIndex = arity;
						int chosen_geneIndex = rand()%(lastPossibleValueGeneIndex-firstPossibleValueGeneIndex + 1) + firstPossibleValueGeneIndex;
						if(chosen_geneIndex == arity){
							int functionIndex = rand() % functionTable.size();

							genotype[chosen][chosen_geneIndex] = functionTable[functionIndex];
						}
						else{
							//Muta Entrada
							int originalInput = genotype[chosen][chosen_geneIndex];
							vector<int> previousNodes;
							for(int i=0; i<chosen; i++){
								if(i >= ni){
									previousNodes.push_back(i);
								}
							}
							//cout << "Chosen Node: " << chosen << endl;

							vector<int> all_fitness_nodes;

							for(int i=0; i<previousNodes.size(); i++){
								//cout << previousNodes[i] << endl;


							genotype[chosen][chosen_geneIndex] = previousNodes[i];


							//Descobrir nós ativos

		        			for(int j = 0; j < no; j++){
		        				phenotype[j].clear();
		            			int currentOutput = size + ni + j;
		            			phenotype[j].push_back(currentOutput);
		            			phenotype[j].push_back(genotype[currentOutput][0]);
		            			getActiveNodes(j, genotype[currentOutput][0]);
		         			}


							//Montagem da Tabela Verdade
								vector<vector<int>> local_tt;
								int half = ni/2;
								for(int i = 0; i < half; i++){
									local_tt.push_back({});
									int proportion = pow(2, half) / pow(2, i + 1);
									for(int divisions = 0; divisions < pow(2, i + 1); divisions++){
										for(int bits = 0; bits < proportion; bits++){
											if(divisions % 2 == 0){
												local_tt[i].push_back(0);
											}
											else{
												local_tt[i].push_back(1);
											}
										}
									}
								}
								for(int i = 0; i < half; i++){
									local_tt.push_back({});
									int proportion = pow(2, half) / pow(2, i + 1);
									for(int divisions = 0; divisions < pow(2, i + 1); divisions++){
										for(int bits = 0; bits < proportion; bits++){
											if(divisions % 2 == 0){
												local_tt[i + half].push_back(1);
											}
											else{
												local_tt[i + half].push_back(0);
											}
										}
									}
								}		



								for(int i = 0; i<size; i++){
									local_tt.push_back({});
								}							



								vector<int> all_actives = {};
								for(int i = 0; i < no; i++){
									for(int j = 0; j < phenotype[i].size(); j++){
										auto search_active = find(all_actives.begin(), all_actives.end(), phenotype[i][j]);
										if (search_active == all_actives.end()){
											all_actives.push_back(phenotype[i][j]);
										}
									}
								}
								sort(all_actives.begin(), all_actives.end());


								for(int i = 0; i < all_actives.size(); i++){
									int actives = all_actives[i];
									if(actives >= ni && actives < size + ni){
										vector<int> node = genotype[actives];
										int inputA = node[0];
										int inputB = node[1];
										int function = node[2];

										for(int bits = 0; bits < pow(2, half); bits ++){
											int v1 = local_tt[inputA][bits];
											int v2 = local_tt[inputB][bits];
											int v3;
											if(function == 1){
												v3 = v1 && v2;
												local_tt[actives].push_back(v3);

											}
											else{
												if(function == 2){
													v3 = v1 || v2;
													local_tt[actives].push_back(v3);
												}
												else{
													if(function == 3){
														v3 = (!v1);
														local_tt[actives].push_back(!v1);
													}
													else{
														if(function == 4){
															v3 = ((!v1) && (v2)) || ((v1) && (!v2));
															local_tt[actives].push_back(v3);
														}
													}
												}
											}


											if(function == 5){
												v3 = !(v1 && v2);
												local_tt[actives].push_back(v3);
												//cout << "EH NAND" << endl;
											}
											if(function == 6){
												v3 = !(v1 || v2);
												local_tt[actives].push_back(v3);
												//cout << "EH NOR" << endl;
											}
											if(function == 7){
												v3 = !(((!v1) && (v2)) || ((v1) && (!v2)));
												local_tt[actives].push_back(v3);
												//cout << "EH XNOR" << endl;
											}
											if(function == 8){
												//EH NOT
												if(local_tt[inputA][bits] == 0){
													local_tt[actives].push_back(1);	
												}
												else{
													local_tt[actives].push_back(0);
												}
												
											}
										}
									}
								}



							//adiciona aptidao no vetor de aptidoes para cada nó

							//int current_fitness = 0;
							//int current_output = size + ni;				
							//vector<int> tt_currentOutput = local_tt[genotype[current_output][0]];

							//for(int bits = 0; bits < tt_currentOutput.size(); bits++){
							//	if(tt_currentOutput[bits] == dOutput[0][bits] || dOutput[0][bits] == 9){
							//		
							//		current_fitness += 1;
							//	}
							//}
							//all_fitness_nodes.push_back(current_fitness);

							//vector<int> local_fitness = {};
							for(int outputs = 0; outputs < no; outputs++){
								int current_fitness = 0;
								int current_output = size + ni + outputs;

								vector<int> tt_currentOutput = local_tt[genotype[current_output][0]];

								for(int bits = 0; bits < tt_currentOutput.size(); bits++){
									if(tt_currentOutput[bits] == dOutput[outputs][bits] || dOutput[outputs][bits] == 9){
										
										current_fitness += 1;
									}
								}
								//cout << current_fitness << endl;
								all_fitness_nodes.push_back(current_fitness);
								
							}							



							} //for dos nós

							//cout << "AQUI" << endl;
							//for(int i=0; i<all_fitness_nodes.size(); i++){
							//	cout << all_fitness_nodes[i] << endl;
							//}

							int argMax = distance(all_fitness_nodes.begin(), max_element(all_fitness_nodes.begin(), all_fitness_nodes.end()));
							//cout << "ARGMAX " << argMax << endl;
							int newInput;
							if(all_fitness_nodes.size() == 0){
								newInput = originalInput;
							}
							else{
								newInput = previousNodes[argMax];
							}
							genotype[chosen][chosen_geneIndex] = newInput;
							// atribui o melhor valor de entrada agora


						} //fecha o else do muta Entrada

					} // fecha else				

			} // fecha else





		} //fecha while

	} //fecha procedimento







	void mutateSemanticSAMOnly(vector<vector<int>> &dOutput){


		vector<int> all_actives = {};
		for(int outputs = 0; outputs < no; outputs++){
			for(int actives_index = 0; actives_index < phenotype[outputs].size(); actives_index++){
				int actives = phenotype[outputs][actives_index];
				auto search = find(all_actives.begin(), all_actives.end(), actives);
				if (search == all_actives.end()){
					all_actives.push_back(actives);
				}
			}
		}
		

		bool selectedActive = 0;
		int v_local = 0;





		vector<int> all_inactives = {};

		for(int i = ni; i < (nc*nr + ni + no - 1); i++){
			auto searchActive = find(all_actives.begin(), all_actives.end(), i);
			if(searchActive == all_actives.end()){
				all_inactives.push_back(i);

					for(int j = 0; j <= arity; j++){
						if(j < arity){
							//cout << "muta input " << j << endl;

							int firstPossibleValueInputLocal;
							int lastPossibleValueInputLocal;
							int current_col = (i - ni + nr) / nr;
							if(current_col - lb > 0){
								firstPossibleValueInputLocal = ni + ((current_col - lb - 1) * nr);
							}
							else{
								firstPossibleValueInputLocal = 0;
							}
							lastPossibleValueInputLocal = ((current_col - 1) * nr) - 1 + ni;

							int new_valueLocal = rand()%(lastPossibleValueInputLocal-firstPossibleValueInputLocal + 1) + firstPossibleValueInputLocal;
							while(new_valueLocal == genotype[i][j]){
								new_valueLocal = rand()%(lastPossibleValueInputLocal-firstPossibleValueInputLocal + 1) + firstPossibleValueInputLocal;
							}
							genotype[i][j] = new_valueLocal;


						} //fecha if mutação input
						else{
							//cout << "Muta output" << j << endl;
							int functionIndexLocal = rand() % functionTable.size();
							genotype[i][j] = functionTable[functionIndexLocal];
						} //fecha else para mutação porta
					} // fecha arity



			} // fecha if do search active
			
		} // fecha for de todos os nós para encontrar os inativos





		while(selectedActive == 0){
			int firstPossibleValue = ni;
			//int lastPossibleValue = nc*nr + ni + no - 1;
			int lastPossibleValue = nc*nr + ni - 1;
			//cout << "INICIO" << endl;
			//for(int i = 0; i < all_actives.size(); i++){
			//	cout << all_actives[i] << endl;
			//}
			//cout << "FIM" << endl;
			//int chosen = rand()%(lastPossibleValue-firstPossibleValue + 1) + firstPossibleValue;
			int chosenIndex = rand() % all_actives.size();
			int chosen = all_actives[chosenIndex];

			v_local += 1;
			auto search2 = find(all_actives.begin(), all_actives.end(), chosen);
			if(search2 != all_actives.end()){
				selectedActive = 1;

			}


			if(selectedActive == 0){


					cout << "entrou aqui?" << endl;
					




			}
			else{

				//chosen node é o chosen

					vector<int> chosen_node = genotype[chosen];
					//cout << "CHOSEN: " << chosen << endl;
					//cout << "TAMANHO: " << genotype[chosen].size() << endl;
					//cout << chosen_node[0] << endl;
					//cout << chosen_node[1] << endl;
					//cout << chosen_node[2] << endl;
					//Muta Output
					if(chosen_node.size() == 1){
						//cout << "entrou e não pode entrar" << endl;
						int firstPossibleValueOutput = 0;
						int lastPossibleValueOutput = nc*nr + ni - 1;
						int chosenOutput = rand()%(lastPossibleValueOutput-firstPossibleValueOutput + 1) + firstPossibleValueOutput;
						//genotype[chosen][0] = chosenOutput;

						int chosen_geneIndex = 0;
						int originalInput = genotype[chosen][chosen_geneIndex];


							vector<int> previousNodes;
							for(int i=0; i<chosen; i++){
								if(i >= ni){
									previousNodes.push_back(i);
								}
							}
							//cout << "Chosen Node: " << chosen << endl;

							vector<int> all_fitness_nodes;

							for(int i=0; i<previousNodes.size(); i++){
								//cout << previousNodes[i] << endl;


							genotype[chosen][chosen_geneIndex] = previousNodes[i];


							//Descobrir nós ativos

		        			for(int j = 0; j < no; j++){
		        				phenotype[j].clear();
		            			int currentOutput = size + ni + j;
		            			phenotype[j].push_back(currentOutput);
		            			phenotype[j].push_back(genotype[currentOutput][0]);
		            			getActiveNodes(j, genotype[currentOutput][0]);
		         			}


							//Montagem da Tabela Verdade
								vector<vector<int>> local_tt;
								int half = ni/2;
								for(int i = 0; i < half; i++){
									local_tt.push_back({});
									int proportion = pow(2, half) / pow(2, i + 1);
									for(int divisions = 0; divisions < pow(2, i + 1); divisions++){
										for(int bits = 0; bits < proportion; bits++){
											if(divisions % 2 == 0){
												local_tt[i].push_back(0);
											}
											else{
												local_tt[i].push_back(1);
											}
										}
									}
								}
								for(int i = 0; i < half; i++){
									local_tt.push_back({});
									int proportion = pow(2, half) / pow(2, i + 1);
									for(int divisions = 0; divisions < pow(2, i + 1); divisions++){
										for(int bits = 0; bits < proportion; bits++){
											if(divisions % 2 == 0){
												local_tt[i + half].push_back(1);
											}
											else{
												local_tt[i + half].push_back(0);
											}
										}
									}
								}		



								for(int i = 0; i<size; i++){
									local_tt.push_back({});
								}							



								vector<int> all_actives = {};
								for(int i = 0; i < no; i++){
									for(int j = 0; j < phenotype[i].size(); j++){
										auto search_active = find(all_actives.begin(), all_actives.end(), phenotype[i][j]);
										if (search_active == all_actives.end()){
											all_actives.push_back(phenotype[i][j]);
										}
									}
								}
								sort(all_actives.begin(), all_actives.end());


								for(int i = 0; i < all_actives.size(); i++){
									int actives = all_actives[i];
									if(actives >= ni && actives < size + ni){
										vector<int> node = genotype[actives];
										int inputA = node[0];
										int inputB = node[1];
										int function = node[2];

										for(int bits = 0; bits < pow(2, half); bits ++){
											int v1 = local_tt[inputA][bits];
											int v2 = local_tt[inputB][bits];
											int v3;
											if(function == 1){
												v3 = v1 && v2;
												local_tt[actives].push_back(v3);

											}
											else{
												if(function == 2){
													v3 = v1 || v2;
													local_tt[actives].push_back(v3);
												}
												else{
													if(function == 3){
														v3 = (!v1);
														local_tt[actives].push_back(!v1);
													}
													else{
														if(function == 4){
															v3 = ((!v1) && (v2)) || ((v1) && (!v2));
															local_tt[actives].push_back(v3);
														}
													}
												}
											}


											if(function == 5){
												v3 = !(v1 && v2);
												local_tt[actives].push_back(v3);
												//cout << "EH NAND" << endl;
											}
											if(function == 6){
												v3 = !(v1 || v2);
												local_tt[actives].push_back(v3);
												//cout << "EH NOR" << endl;
											}
											if(function == 7){
												v3 = !(((!v1) && (v2)) || ((v1) && (!v2)));
												local_tt[actives].push_back(v3);
												//cout << "EH XNOR" << endl;
											}
											if(function == 8){
												//EH NOT
												if(local_tt[inputA][bits] == 0){
													local_tt[actives].push_back(1);	
												}
												else{
													local_tt[actives].push_back(0);
												}
												
											}
										}
									}
								}



							//adiciona aptidao no vetor de aptidoes para cada nó

							//int current_fitness = 0;
							//int current_output = size + ni;				
							//vector<int> tt_currentOutput = local_tt[genotype[current_output][0]];

							//for(int bits = 0; bits < tt_currentOutput.size(); bits++){
							//	if(tt_currentOutput[bits] == dOutput[0][bits] || dOutput[0][bits] == 9){
							//		
							//		current_fitness += 1;
							//	}
							//}
							//all_fitness_nodes.push_back(current_fitness);

							//vector<int> local_fitness = {};
							for(int outputs = 0; outputs < no; outputs++){
								int current_fitness = 0;
								int current_output = size + ni + outputs;

								vector<int> tt_currentOutput = local_tt[genotype[current_output][0]];

								for(int bits = 0; bits < tt_currentOutput.size(); bits++){
									if(tt_currentOutput[bits] == dOutput[outputs][bits] || dOutput[outputs][bits] == 9){
										
										current_fitness += 1;
									}
								}
								//cout << current_fitness << endl;
								all_fitness_nodes.push_back(current_fitness);
								
							}							



							} //for dos nós

							//cout << "AQUI" << endl;
							//for(int i=0; i<all_fitness_nodes.size(); i++){
							//	cout << all_fitness_nodes[i] << endl;
							//}

							int argMax = distance(all_fitness_nodes.begin(), max_element(all_fitness_nodes.begin(), all_fitness_nodes.end()));
							//cout << "ARGMAX " << argMax << endl;
							int newInput;
							if(all_fitness_nodes.size() == 0){
								newInput = originalInput;
							}
							else{
								newInput = previousNodes[argMax];
							}
							genotype[chosen][chosen_geneIndex] = newInput;
							// atribui o melhor valor de entrada agora





					}
					else{
						//Muta Porta
						int firstPossibleValueGeneIndex = 0;
						int lastPossibleValueGeneIndex = arity-1;
						int chosen_geneIndex = rand()%(lastPossibleValueGeneIndex-firstPossibleValueGeneIndex + 1) + firstPossibleValueGeneIndex;
						if(chosen_geneIndex == arity){
							int functionIndex = rand() % functionTable.size();

							genotype[chosen][chosen_geneIndex] = functionTable[functionIndex];
						}
						else{
							//Muta Entrada
							int originalInput = genotype[chosen][chosen_geneIndex];
							vector<int> previousNodes;
							for(int i=0; i<chosen; i++){
								if(i >= ni){
									previousNodes.push_back(i);
								}
							}
							//cout << "Chosen Node: " << chosen << endl;

							vector<int> all_fitness_nodes;

							for(int i=0; i<previousNodes.size(); i++){
								//cout << previousNodes[i] << endl;


							genotype[chosen][chosen_geneIndex] = previousNodes[i];


							//Descobrir nós ativos

		        			for(int j = 0; j < no; j++){
		        				phenotype[j].clear();
		            			int currentOutput = size + ni + j;
		            			phenotype[j].push_back(currentOutput);
		            			phenotype[j].push_back(genotype[currentOutput][0]);
		            			getActiveNodes(j, genotype[currentOutput][0]);
		         			}


							//Montagem da Tabela Verdade
								vector<vector<int>> local_tt;
								int half = ni/2;
								for(int i = 0; i < half; i++){
									local_tt.push_back({});
									int proportion = pow(2, half) / pow(2, i + 1);
									for(int divisions = 0; divisions < pow(2, i + 1); divisions++){
										for(int bits = 0; bits < proportion; bits++){
											if(divisions % 2 == 0){
												local_tt[i].push_back(0);
											}
											else{
												local_tt[i].push_back(1);
											}
										}
									}
								}
								for(int i = 0; i < half; i++){
									local_tt.push_back({});
									int proportion = pow(2, half) / pow(2, i + 1);
									for(int divisions = 0; divisions < pow(2, i + 1); divisions++){
										for(int bits = 0; bits < proportion; bits++){
											if(divisions % 2 == 0){
												local_tt[i + half].push_back(1);
											}
											else{
												local_tt[i + half].push_back(0);
											}
										}
									}
								}		



								for(int i = 0; i<size; i++){
									local_tt.push_back({});
								}							



								vector<int> all_actives = {};
								for(int i = 0; i < no; i++){
									for(int j = 0; j < phenotype[i].size(); j++){
										auto search_active = find(all_actives.begin(), all_actives.end(), phenotype[i][j]);
										if (search_active == all_actives.end()){
											all_actives.push_back(phenotype[i][j]);
										}
									}
								}
								sort(all_actives.begin(), all_actives.end());


								for(int i = 0; i < all_actives.size(); i++){
									int actives = all_actives[i];
									if(actives >= ni && actives < size + ni){
										vector<int> node = genotype[actives];
										int inputA = node[0];
										int inputB = node[1];
										int function = node[2];

										for(int bits = 0; bits < pow(2, half); bits ++){
											int v1 = local_tt[inputA][bits];
											int v2 = local_tt[inputB][bits];
											int v3;
											if(function == 1){
												v3 = v1 && v2;
												local_tt[actives].push_back(v3);

											}
											else{
												if(function == 2){
													v3 = v1 || v2;
													local_tt[actives].push_back(v3);
												}
												else{
													if(function == 3){
														v3 = (!v1);
														local_tt[actives].push_back(!v1);
													}
													else{
														if(function == 4){
															v3 = ((!v1) && (v2)) || ((v1) && (!v2));
															local_tt[actives].push_back(v3);
														}
													}
												}
											}


											if(function == 5){
												v3 = !(v1 && v2);
												local_tt[actives].push_back(v3);
												//cout << "EH NAND" << endl;
											}
											if(function == 6){
												v3 = !(v1 || v2);
												local_tt[actives].push_back(v3);
												//cout << "EH NOR" << endl;
											}
											if(function == 7){
												v3 = !(((!v1) && (v2)) || ((v1) && (!v2)));
												local_tt[actives].push_back(v3);
												//cout << "EH XNOR" << endl;
											}
											if(function == 8){
												//EH NOT
												if(local_tt[inputA][bits] == 0){
													local_tt[actives].push_back(1);	
												}
												else{
													local_tt[actives].push_back(0);
												}
												
											}
										}
									}
								}



							//adiciona aptidao no vetor de aptidoes para cada nó

							//int current_fitness = 0;
							//int current_output = size + ni;				
							//vector<int> tt_currentOutput = local_tt[genotype[current_output][0]];

							//for(int bits = 0; bits < tt_currentOutput.size(); bits++){
							//	if(tt_currentOutput[bits] == dOutput[0][bits] || dOutput[0][bits] == 9){
							//		
							//		current_fitness += 1;
							//	}
							//}
							//all_fitness_nodes.push_back(current_fitness);

							//vector<int> local_fitness = {};
							for(int outputs = 0; outputs < no; outputs++){
								int current_fitness = 0;
								int current_output = size + ni + outputs;

								vector<int> tt_currentOutput = local_tt[genotype[current_output][0]];

								for(int bits = 0; bits < tt_currentOutput.size(); bits++){
									if(tt_currentOutput[bits] == dOutput[outputs][bits] || dOutput[outputs][bits] == 9){
										
										current_fitness += 1;
									}
								}
								//cout << current_fitness << endl;
								all_fitness_nodes.push_back(current_fitness);
								
							}							



							} //for dos nós

							//cout << "AQUI" << endl;
							//for(int i=0; i<all_fitness_nodes.size(); i++){
							//	cout << all_fitness_nodes[i] << endl;
							//}

							int argMax = distance(all_fitness_nodes.begin(), max_element(all_fitness_nodes.begin(), all_fitness_nodes.end()));
							//cout << "ARGMAX " << argMax << endl;
							int newInput;
							if(all_fitness_nodes.size() == 0){
								newInput = originalInput;
							}
							else{
								newInput = previousNodes[argMax];
							}
							genotype[chosen][chosen_geneIndex] = newInput;
							// atribui o melhor valor de entrada agora


						} //fecha o else do muta Entrada

					} // fecha else				

			} // fecha else





		} //fecha while

	} //fecha procedimento




	void mutateSemanticSAMOnlyPF50(vector<vector<int>> &dOutput){


		vector<int> all_actives = {};
		for(int outputs = 0; outputs < no; outputs++){
			for(int actives_index = 0; actives_index < phenotype[outputs].size(); actives_index++){
				int actives = phenotype[outputs][actives_index];
				auto search = find(all_actives.begin(), all_actives.end(), actives);
				if (search == all_actives.end()){
					all_actives.push_back(actives);
				}
			}
		}
		

		bool selectedActive = 0;
		int v_local = 0;





		vector<int> all_inactives = {};

		for(int i = ni; i < (nc*nr + ni + no - 1); i++){
			auto searchActive = find(all_actives.begin(), all_actives.end(), i);
			if(searchActive == all_actives.end()){
				all_inactives.push_back(i);

			} // fecha if do search active
			
		} // fecha for de todos os nós para encontrar os inativos

		
		vector<int> all_inactives_mutate = {};

		//cout << all_inactives.size()/2 << endl;

		for(int i = 0; i < all_inactives.size()/2; i++){
			int random = rand() % all_inactives.size();
			int sel_elem = all_inactives[random];
			//auto searchInactive = find(all_inactives_mutate.begin(), all_inactives_mutate.end(), sel_elem);
			
			if(find(all_inactives_mutate.begin(), all_inactives_mutate.end(), sel_elem) == all_inactives_mutate.end()){
				//cout << "Não está" << endl;
				all_inactives_mutate.push_back(sel_elem);
			}
			else{
				while(find(all_inactives_mutate.begin(), all_inactives_mutate.end(), sel_elem) != all_inactives_mutate.end()){
					random = rand() % all_inactives.size();
					sel_elem = all_inactives[random];
					//cout << sel_elem << endl;
				}
				all_inactives_mutate.push_back(sel_elem);
			}
		}


		/*
		cout << all_inactives.size() << endl;
		while(all_inactives_mutate.size() < all_inactives.size()/2){
			cout << all_inactives_mutate.size() << endl;
			int random = rand() % all_inactives.size();
			int sel_elem = all_inactives[random];
			auto searchInactive = find(all_inactives_mutate.begin(), all_inactives_mutate.end(), sel_elem);
			while(searchInactive != all_inactives_mutate.end()){
				random = rand() % all_inactives.size();
				sel_elem = all_inactives[random];
				auto searchInactive = find(all_inactives_mutate.begin(), all_inactives_mutate.end(), sel_elem);
				cout << "estou aqui" << endl;
			}
			cout << "saiu" << endl;

			all_inactives_mutate.push_back(sel_elem);	
		}

		cout << "chegou aqui" << endl;
		//cout << all_inactives_mutate.size() << endl;
		*/



//COMEÇA AQUI

		for(int k = 0; k < all_actives.size(); k++){
			int i = all_inactives_mutate[k];

		


					for(int j = 0; j <= arity; j++){
						if(j < arity){
							//cout << "muta input " << j << endl;

							int firstPossibleValueInputLocal;
							int lastPossibleValueInputLocal;
							int current_col = (i - ni + nr) / nr;
							if(current_col - lb > 0){
								firstPossibleValueInputLocal = ni + ((current_col - lb - 1) * nr);
							}
							else{
								firstPossibleValueInputLocal = 0;
							}
							lastPossibleValueInputLocal = ((current_col - 1) * nr) - 1 + ni;

							int new_valueLocal = rand()%(lastPossibleValueInputLocal-firstPossibleValueInputLocal + 1) + firstPossibleValueInputLocal;
							while(new_valueLocal == genotype[i][j]){
								new_valueLocal = rand()%(lastPossibleValueInputLocal-firstPossibleValueInputLocal + 1) + firstPossibleValueInputLocal;
							}
							genotype[i][j] = new_valueLocal;


						} //fecha if mutação input
						else{
							//cout << "Muta output" << j << endl;
							int functionIndexLocal = rand() % functionTable.size();
							genotype[i][j] = functionTable[functionIndexLocal];
						} //fecha else para mutação porta
					} // fecha arity for


		} // fecha for k





		while(selectedActive == 0){
			int firstPossibleValue = ni;
			//int lastPossibleValue = nc*nr + ni + no - 1;
			int lastPossibleValue = nc*nr + ni - 1;
			//cout << "INICIO" << endl;
			//for(int i = 0; i < all_actives.size(); i++){
			//	cout << all_actives[i] << endl;
			//}
			//cout << "FIM" << endl;
			//int chosen = rand()%(lastPossibleValue-firstPossibleValue + 1) + firstPossibleValue;
			int chosenIndex = rand() % all_actives.size();
			int chosen = all_actives[chosenIndex];

			v_local += 1;
			auto search2 = find(all_actives.begin(), all_actives.end(), chosen);
			if(search2 != all_actives.end()){
				selectedActive = 1;

			}


			if(selectedActive == 0){


					cout << "entrou aqui?" << endl;
					




			}
			else{

				//chosen node é o chosen

					vector<int> chosen_node = genotype[chosen];
					//cout << "CHOSEN: " << chosen << endl;
					//cout << "TAMANHO: " << genotype[chosen].size() << endl;
					//cout << chosen_node[0] << endl;
					//cout << chosen_node[1] << endl;
					//cout << chosen_node[2] << endl;
					//Muta Output
					if(chosen_node.size() == 1){
						//cout << "entrou e não pode entrar" << endl;
						int firstPossibleValueOutput = 0;
						int lastPossibleValueOutput = nc*nr + ni - 1;
						int chosenOutput = rand()%(lastPossibleValueOutput-firstPossibleValueOutput + 1) + firstPossibleValueOutput;
						//genotype[chosen][0] = chosenOutput;

						int chosen_geneIndex = 0;
						int originalInput = genotype[chosen][chosen_geneIndex];


							vector<int> previousNodes;
							for(int i=0; i<chosen; i++){
								if(i >= ni){
									previousNodes.push_back(i);
								}
							}
							//cout << "Chosen Node: " << chosen << endl;

							vector<int> all_fitness_nodes;

							for(int i=0; i<previousNodes.size(); i++){
								//cout << previousNodes[i] << endl;


							genotype[chosen][chosen_geneIndex] = previousNodes[i];


							//Descobrir nós ativos

		        			for(int j = 0; j < no; j++){
		        				phenotype[j].clear();
		            			int currentOutput = size + ni + j;
		            			phenotype[j].push_back(currentOutput);
		            			phenotype[j].push_back(genotype[currentOutput][0]);
		            			getActiveNodes(j, genotype[currentOutput][0]);
		         			}


							//Montagem da Tabela Verdade
								vector<vector<int>> local_tt;
								int half = ni/2;
								for(int i = 0; i < half; i++){
									local_tt.push_back({});
									int proportion = pow(2, half) / pow(2, i + 1);
									for(int divisions = 0; divisions < pow(2, i + 1); divisions++){
										for(int bits = 0; bits < proportion; bits++){
											if(divisions % 2 == 0){
												local_tt[i].push_back(0);
											}
											else{
												local_tt[i].push_back(1);
											}
										}
									}
								}
								for(int i = 0; i < half; i++){
									local_tt.push_back({});
									int proportion = pow(2, half) / pow(2, i + 1);
									for(int divisions = 0; divisions < pow(2, i + 1); divisions++){
										for(int bits = 0; bits < proportion; bits++){
											if(divisions % 2 == 0){
												local_tt[i + half].push_back(1);
											}
											else{
												local_tt[i + half].push_back(0);
											}
										}
									}
								}		



								for(int i = 0; i<size; i++){
									local_tt.push_back({});
								}							



								vector<int> all_actives = {};
								for(int i = 0; i < no; i++){
									for(int j = 0; j < phenotype[i].size(); j++){
										auto search_active = find(all_actives.begin(), all_actives.end(), phenotype[i][j]);
										if (search_active == all_actives.end()){
											all_actives.push_back(phenotype[i][j]);
										}
									}
								}
								sort(all_actives.begin(), all_actives.end());


								for(int i = 0; i < all_actives.size(); i++){
									int actives = all_actives[i];
									if(actives >= ni && actives < size + ni){
										vector<int> node = genotype[actives];
										int inputA = node[0];
										int inputB = node[1];
										int function = node[2];

										for(int bits = 0; bits < pow(2, half); bits ++){
											int v1 = local_tt[inputA][bits];
											int v2 = local_tt[inputB][bits];
											int v3;
											if(function == 1){
												v3 = v1 && v2;
												local_tt[actives].push_back(v3);

											}
											else{
												if(function == 2){
													v3 = v1 || v2;
													local_tt[actives].push_back(v3);
												}
												else{
													if(function == 3){
														v3 = (!v1);
														local_tt[actives].push_back(!v1);
													}
													else{
														if(function == 4){
															v3 = ((!v1) && (v2)) || ((v1) && (!v2));
															local_tt[actives].push_back(v3);
														}
													}
												}
											}


											if(function == 5){
												v3 = !(v1 && v2);
												local_tt[actives].push_back(v3);
												//cout << "EH NAND" << endl;
											}
											if(function == 6){
												v3 = !(v1 || v2);
												local_tt[actives].push_back(v3);
												//cout << "EH NOR" << endl;
											}
											if(function == 7){
												v3 = !(((!v1) && (v2)) || ((v1) && (!v2)));
												local_tt[actives].push_back(v3);
												//cout << "EH XNOR" << endl;
											}
											if(function == 8){
												//EH NOT
												if(local_tt[inputA][bits] == 0){
													local_tt[actives].push_back(1);	
												}
												else{
													local_tt[actives].push_back(0);
												}
												
											}
										}
									}
								}



							//adiciona aptidao no vetor de aptidoes para cada nó

							//int current_fitness = 0;
							//int current_output = size + ni;				
							//vector<int> tt_currentOutput = local_tt[genotype[current_output][0]];

							//for(int bits = 0; bits < tt_currentOutput.size(); bits++){
							//	if(tt_currentOutput[bits] == dOutput[0][bits] || dOutput[0][bits] == 9){
							//		
							//		current_fitness += 1;
							//	}
							//}
							//all_fitness_nodes.push_back(current_fitness);

							//vector<int> local_fitness = {};
							for(int outputs = 0; outputs < no; outputs++){
								int current_fitness = 0;
								int current_output = size + ni + outputs;

								vector<int> tt_currentOutput = local_tt[genotype[current_output][0]];

								for(int bits = 0; bits < tt_currentOutput.size(); bits++){
									if(tt_currentOutput[bits] == dOutput[outputs][bits] || dOutput[outputs][bits] == 9){
										
										current_fitness += 1;
									}
								}
								//cout << current_fitness << endl;
								all_fitness_nodes.push_back(current_fitness);
								
							}							



							} //for dos nós

							//cout << "AQUI" << endl;
							//for(int i=0; i<all_fitness_nodes.size(); i++){
							//	cout << all_fitness_nodes[i] << endl;
							//}

							int argMax = distance(all_fitness_nodes.begin(), max_element(all_fitness_nodes.begin(), all_fitness_nodes.end()));
							//cout << "ARGMAX " << argMax << endl;
							int newInput;
							if(all_fitness_nodes.size() == 0){
								newInput = originalInput;
							}
							else{
								newInput = previousNodes[argMax];
							}
							genotype[chosen][chosen_geneIndex] = newInput;
							// atribui o melhor valor de entrada agora





					}
					else{
						//Muta Porta
						int firstPossibleValueGeneIndex = 0;
						int lastPossibleValueGeneIndex = arity-1;
						int chosen_geneIndex = rand()%(lastPossibleValueGeneIndex-firstPossibleValueGeneIndex + 1) + firstPossibleValueGeneIndex;
						if(chosen_geneIndex == arity){
							int functionIndex = rand() % functionTable.size();

							genotype[chosen][chosen_geneIndex] = functionTable[functionIndex];
						}
						else{
							//Muta Entrada
							int originalInput = genotype[chosen][chosen_geneIndex];
							vector<int> previousNodes;
							for(int i=0; i<chosen; i++){
								if(i >= ni){
									previousNodes.push_back(i);
								}
							}
							//cout << "Chosen Node: " << chosen << endl;

							vector<int> all_fitness_nodes;

							for(int i=0; i<previousNodes.size(); i++){
								//cout << previousNodes[i] << endl;


							genotype[chosen][chosen_geneIndex] = previousNodes[i];


							//Descobrir nós ativos

		        			for(int j = 0; j < no; j++){
		        				phenotype[j].clear();
		            			int currentOutput = size + ni + j;
		            			phenotype[j].push_back(currentOutput);
		            			phenotype[j].push_back(genotype[currentOutput][0]);
		            			getActiveNodes(j, genotype[currentOutput][0]);
		         			}


							//Montagem da Tabela Verdade
								vector<vector<int>> local_tt;
								int half = ni/2;
								for(int i = 0; i < half; i++){
									local_tt.push_back({});
									int proportion = pow(2, half) / pow(2, i + 1);
									for(int divisions = 0; divisions < pow(2, i + 1); divisions++){
										for(int bits = 0; bits < proportion; bits++){
											if(divisions % 2 == 0){
												local_tt[i].push_back(0);
											}
											else{
												local_tt[i].push_back(1);
											}
										}
									}
								}
								for(int i = 0; i < half; i++){
									local_tt.push_back({});
									int proportion = pow(2, half) / pow(2, i + 1);
									for(int divisions = 0; divisions < pow(2, i + 1); divisions++){
										for(int bits = 0; bits < proportion; bits++){
											if(divisions % 2 == 0){
												local_tt[i + half].push_back(1);
											}
											else{
												local_tt[i + half].push_back(0);
											}
										}
									}
								}		



								for(int i = 0; i<size; i++){
									local_tt.push_back({});
								}							



								vector<int> all_actives = {};
								for(int i = 0; i < no; i++){
									for(int j = 0; j < phenotype[i].size(); j++){
										auto search_active = find(all_actives.begin(), all_actives.end(), phenotype[i][j]);
										if (search_active == all_actives.end()){
											all_actives.push_back(phenotype[i][j]);
										}
									}
								}
								sort(all_actives.begin(), all_actives.end());


								for(int i = 0; i < all_actives.size(); i++){
									int actives = all_actives[i];
									if(actives >= ni && actives < size + ni){
										vector<int> node = genotype[actives];
										int inputA = node[0];
										int inputB = node[1];
										int function = node[2];

										for(int bits = 0; bits < pow(2, half); bits ++){
											int v1 = local_tt[inputA][bits];
											int v2 = local_tt[inputB][bits];
											int v3;
											if(function == 1){
												v3 = v1 && v2;
												local_tt[actives].push_back(v3);

											}
											else{
												if(function == 2){
													v3 = v1 || v2;
													local_tt[actives].push_back(v3);
												}
												else{
													if(function == 3){
														v3 = (!v1);
														local_tt[actives].push_back(!v1);
													}
													else{
														if(function == 4){
															v3 = ((!v1) && (v2)) || ((v1) && (!v2));
															local_tt[actives].push_back(v3);
														}
													}
												}
											}


											if(function == 5){
												v3 = !(v1 && v2);
												local_tt[actives].push_back(v3);
												//cout << "EH NAND" << endl;
											}
											if(function == 6){
												v3 = !(v1 || v2);
												local_tt[actives].push_back(v3);
												//cout << "EH NOR" << endl;
											}
											if(function == 7){
												v3 = !(((!v1) && (v2)) || ((v1) && (!v2)));
												local_tt[actives].push_back(v3);
												//cout << "EH XNOR" << endl;
											}
											if(function == 8){
												//EH NOT
												if(local_tt[inputA][bits] == 0){
													local_tt[actives].push_back(1);	
												}
												else{
													local_tt[actives].push_back(0);
												}
												
											}
										}
									}
								}



							//adiciona aptidao no vetor de aptidoes para cada nó

							//int current_fitness = 0;
							//int current_output = size + ni;				
							//vector<int> tt_currentOutput = local_tt[genotype[current_output][0]];

							//for(int bits = 0; bits < tt_currentOutput.size(); bits++){
							//	if(tt_currentOutput[bits] == dOutput[0][bits] || dOutput[0][bits] == 9){
							//		
							//		current_fitness += 1;
							//	}
							//}
							//all_fitness_nodes.push_back(current_fitness);

							//vector<int> local_fitness = {};
							for(int outputs = 0; outputs < no; outputs++){
								int current_fitness = 0;
								int current_output = size + ni + outputs;

								vector<int> tt_currentOutput = local_tt[genotype[current_output][0]];

								for(int bits = 0; bits < tt_currentOutput.size(); bits++){
									if(tt_currentOutput[bits] == dOutput[outputs][bits] || dOutput[outputs][bits] == 9){
										
										current_fitness += 1;
									}
								}
								//cout << current_fitness << endl;
								all_fitness_nodes.push_back(current_fitness);
								
							}							



							} //for dos nós

							//cout << "AQUI" << endl;
							//for(int i=0; i<all_fitness_nodes.size(); i++){
							//	cout << all_fitness_nodes[i] << endl;
							//}

							int argMax = distance(all_fitness_nodes.begin(), max_element(all_fitness_nodes.begin(), all_fitness_nodes.end()));
							//cout << "ARGMAX " << argMax << endl;
							int newInput;
							if(all_fitness_nodes.size() == 0){
								newInput = originalInput;
							}
							else{
								newInput = previousNodes[argMax];
							}
							genotype[chosen][chosen_geneIndex] = newInput;
							// atribui o melhor valor de entrada agora


						} //fecha o else do muta Entrada

					} // fecha else				

			} // fecha else





		} //fecha while



//TERMINA AQUI*/

	} //fecha procedimento





	void getActiveNodes(int output, int node){
		if(genotype[node].size() <= 1){

			auto search = find(phenotype[output].begin(), phenotype[output].end(), node);
			if (search != phenotype[output].end()){
				phenotype[output].push_back(node);		
			}
			
			
			}
			
		
		else{
			int inputA = genotype[node][0];
			int inputB = genotype[node][1];
			int function = genotype[node][2];

			if(function != 3){
				auto search1 = find(phenotype[output].begin(), phenotype[output].end(), inputA);
				if (search1 == phenotype[output].end()){
					phenotype[output].push_back(inputA);
				}
				auto search2 = find(phenotype[output].begin(), phenotype[output].end(), inputB);
				if (search2 == phenotype[output].end()){
					phenotype[output].push_back(inputB);
				}
				if (inputA >= ni){
					getActiveNodes(output, inputA);
				}
				if (inputB >= ni){
					getActiveNodes(output, inputB);
				}
			}
			else{
				auto search3 = find(phenotype[output].begin(), phenotype[output].end(), inputA);
				if (search3 == phenotype[output].end()){
					phenotype[output].push_back(inputA);
				}
				if(inputA >= ni){
					getActiveNodes(output, inputA);
				}
			}

			}

		}


	void evalIndividual(vector<vector<int>> &dOutput){

		vector<vector<int>> local_tt;
		int half = ni/2;
		for(int i = 0; i < half; i++){
			local_tt.push_back({});
			int proportion = pow(2, half) / pow(2, i + 1);
			for(int divisions = 0; divisions < pow(2, i + 1); divisions++){
				for(int bits = 0; bits < proportion; bits++){
					if(divisions % 2 == 0){
						local_tt[i].push_back(0);
					}
					else{
						local_tt[i].push_back(1);
					}
				}
			}
		}
		for(int i = 0; i < half; i++){
			local_tt.push_back({});
			int proportion = pow(2, half) / pow(2, i + 1);
			for(int divisions = 0; divisions < pow(2, i + 1); divisions++){
				for(int bits = 0; bits < proportion; bits++){
					if(divisions % 2 == 0){
						local_tt[i + half].push_back(1);
					}
					else{
						local_tt[i + half].push_back(0);
					}
				}
			}
		}		



		for(int i = 0; i<size; i++){
			local_tt.push_back({});
		}

		vector<int> all_actives = {};
		for(int i = 0; i < no; i++){
			for(int j = 0; j < phenotype[i].size(); j++){
				auto search_active = find(all_actives.begin(), all_actives.end(), phenotype[i][j]);
				if (search_active == all_actives.end()){
					all_actives.push_back(phenotype[i][j]);
				}
			}
		}
		sort(all_actives.begin(), all_actives.end());


		for(int i = 0; i < all_actives.size(); i++){
			int actives = all_actives[i];
			if(actives >= ni && actives < size + ni){
				vector<int> node = genotype[actives];
				int inputA = node[0];
				int inputB = node[1];
				int function = node[2];

				for(int bits = 0; bits < pow(2, half); bits ++){
					int v1 = local_tt[inputA][bits];
					int v2 = local_tt[inputB][bits];
					int v3;
					if(function == 1){
						v3 = v1 && v2;
						local_tt[actives].push_back(v3);

					}
					else{
						if(function == 2){
							v3 = v1 || v2;
							local_tt[actives].push_back(v3);
						}
						else{
							if(function == 3){
								v3 = (!v1);
								local_tt[actives].push_back(!v1);
							}
							else{
								if(function == 4){
									v3 = ((!v1) && (v2)) || ((v1) && (!v2));
									local_tt[actives].push_back(v3);
								}
							}
						}
					}


					if(function == 5){
						v3 = !(v1 && v2);
						local_tt[actives].push_back(v3);
						//cout << "EH NAND" << endl;
					}
					if(function == 6){
						v3 = !(v1 || v2);
						local_tt[actives].push_back(v3);
						//cout << "EH NOR" << endl;
					}
					if(function == 7){
						v3 = !(((!v1) && (v2)) || ((v1) && (!v2)));
						local_tt[actives].push_back(v3);
						//cout << "EH XNOR" << endl;
					}
					if(function == 8){
						//EH NOT
						if(local_tt[inputA][bits] == 0){
							local_tt[actives].push_back(1);	
						}
						else{
							local_tt[actives].push_back(0);
						}
						
					}
				}
			}
		}

		vector<int> local_fitness = {};
		for(int outputs = 0; outputs < no; outputs++){
			int current_fitness = 0;
			int current_output = size + ni + outputs;

			vector<int> tt_currentOutput = local_tt[genotype[current_output][0]];

			for(int bits = 0; bits < tt_currentOutput.size(); bits++){
				if(tt_currentOutput[bits] == dOutput[outputs][bits] || dOutput[outputs][bits] == 9){
					
					current_fitness += 1;
				}
			}
			local_fitness.push_back(current_fitness);
			
		}
		
		for(int i = 0; i < local_fitness.size(); i++){
			outputFitness.push_back(local_fitness[i]);
		}

		fitness = accumulate(local_fitness.begin(),local_fitness.end(),0);

	}

};


class Population{
	public:
		int nParents, nOffspring, feasibleEvaluations, currentFitness, feasible, currentLE;
		vector<vector<int>> best; //best individual's genotype (from all entire population)
		vector<vector<int>> desiredOutputs;
		Individual* bestIndividual;
		vector<Individual*> Pop;
		

		Population(int nParents_c, int nOffspring_c, vector<vector<int>> desiredOutputs_c){
			nParents = nParents_c;
			nOffspring = nOffspring_c;
			desiredOutputs = {};
			for(int i=0; i<desiredOutputs_c.size(); i++){
				vector<int> v_local = {};
				for(int j = 0; j < desiredOutputs_c[i].size(); j++){
					v_local.push_back(desiredOutputs_c[i][j]);
				}
				desiredOutputs.push_back(v_local);
			}
			best = {};
			currentFitness = 0;
			currentLE = 1000;
			feasible = 0;
		}



		void clearPopulation(){
			for(int i=0; i < Pop.size(); i++){
				delete Pop[i];
			}
			Pop.clear();
		}

		void setStandard(){
			best = {};
			delete bestIndividual;
			clearPopulation();
			currentFitness = 0;
			currentLE = 1000;
			feasible = 0;
		}


		void parentUpdateIndividual(vector<vector<int>> &genotype, int fitness, int ni_c, int no_c, int nc_c, int nr_c, int lb_c){
			vector<vector<int>> best_l = {};
			best = {};
			for(int i =0; i < genotype.size(); i++){
				vector<int> v_local = {};
				for(int j = 0; j < genotype[i].size(); j++){
					v_local.push_back(genotype[i][j]);
				}
				best_l.push_back(v_local);
				best.push_back(v_local);
			}
			bestIndividual = new Individual(ni_c, no_c, nc_c, nr_c, lb_c, best_l);
			currentFitness = fitness;
		}


		void parentUpdate(vector<vector<int>> &genotype, int fitness){
			best = {};
			for(int i = 0; i < genotype.size(); i++){
				vector<int> v_local = {};
				for(int j = 0; j < genotype[i].size(); j++){
					v_local.push_back(genotype[i][j]);

				}
				best.push_back(v_local);
			}
			currentFitness = fitness;
		}

		void parentUpdateOptimize1(vector<vector<int>> &genotype, int fitness, int LE){
			best = {};
			for(int i = 0; i < genotype.size(); i++){
				vector<int> v_local = {};
				for(int j = 0; j < genotype[i].size(); j++){
					v_local.push_back(genotype[i][j]);

				}
				best.push_back(v_local);
			}
			currentFitness = fitness;
			currentLE = LE;
		}




		void parentUpdateOptimize(){
			vector<int> localLE;
			for(int individuals = 0; individuals < Pop.size(); individuals ++){

				if(Pop[individuals]->fitness == currentFitness){
					if(Pop[individuals]->LE <= currentLE){
						localLE.push_back(individuals);
					}
				}
				
			}
			if(localLE.size() != 0){
				int firstPossibleValueParent = 0;
				int lastPossibleValueParent = localLE.size() - 1;
				int newParentIndex = rand()%(lastPossibleValueParent-firstPossibleValueParent + 1) + firstPossibleValueParent;
				int newParent = localLE[newParentIndex];
				best = {};
				for(int i = 0; i < Pop[newParent]->genotype.size(); i++){
					vector<int> v_local = {};
					for(int j = 0; j < Pop[newParent]->genotype[i].size(); j++){
						v_local.push_back(Pop[newParent]->genotype[i][j]);
					}
					best.push_back(v_local);
				}
				currentFitness = Pop[newParent]->fitness;
				currentLE = Pop[newParent]->LE;

			}


		}




};