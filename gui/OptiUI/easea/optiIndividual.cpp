

#include <fstream>
#include <time.h>
#include <cstring>
#include <sstream>
#include "CRandomGenerator.h"
#include "CPopulation.h"
#include "COptionParser.h"
#include "CStoppingCriterion.h"
#include "CEvolutionaryAlgorithm.h"
#include "global.h"
#include "CIndividual.h"

using namespace std;

#include "optiIndividual.hpp"
bool INSTEAD_EVAL_STEP = false;

CRandomGenerator* globalRandomGenerator;
extern CEvolutionaryAlgorithm* EA;
#define STD_TPL

// User declarations

  /*
  Equipes :
0  : Toulouse
1  : Cergy
2  : Meudon
3  : Amneville
4  : Francais_Volants
5  : Asnieres
6  : Valence
7  : Avignon
8  : Marseille
9  : Chambery
10 : Annecy
11 : Limoges
12 : Clermont
13 : Villard
14 : Roanne
15 : Evry
16 : Strasbourg
17 : Wasquehal
*/
//  #define NB_EQUIPE 18
//  int coeff = 0;
//  int classement[NB_EQUIPE] = {1, 3, 4, 7, 8, 11, 12, 16, 18, 2, 5, 6, 9, 10, 13, 14, 15, 17};
//  double distances[NB_EQUIPE][NB_EQUIPE] = {
//  {0.0   , 717.0, 667.0, 1015.0, 673.0, 686.0, 449.0, 344.0, 417.0 , 604.0, 665.0, 291.0, 408.0, 517.0, 504.0, 668.0, 973.0, 901.0},
//  {717.0 , 0.0  , 52.0 , 364.0 , 42.0 , 22.0 , 599.0, 727.0, 813.0 , 610.0, 597.0, 426.0, 458.0, 634.0, 435.0, 70.0 , 526.0, 236.0},
//  {667.0 , 52.0 , 0.0  , 340.0 , 7.0  , 20.0 , 558.0, 686.0, 772.0 , 569.0, 556.0, 376.0, 409.0, 593.0, 394.0, 29.0 , 502.0, 239.0},
//  {1015.0, 364.0, 340.0, 0.0   , 332.0, 336.0, 572.0, 700.0, 787.0 , 583.0, 555.0, 725.0, 615.0, 607.0, 487.0, 340.0, 176.0, 391.0},
//  {673.0 , 42.0 , 7.0  , 332.0 , 0.0  , 14.0 , 563.0, 691.0, 777.0 , 574.0, 561.0, 385.0, 417.0, 598.0, 399.0, 35.0 , 494.0, 232.0},
//  {686.0 , 22.0 , 20.0 , 336.0 , 14.0 , 0.0  , 574.0, 702.0, 788.0 , 585.0, 572.0, 396.0, 428.0, 609.0, 410.0, 46.0 , 507.0, 224.0},
//  {449.0 , 599.0, 558.0, 572.0 , 563.0, 574.0, 0.0  , 130.0, 217.0 , 154.0, 216.0, 506.0, 264.0, 68.0 , 205.0, 531.0, 592.0, 793.0},
//  {344.0 , 727.0, 686.0, 700.0 , 691.0, 702.0, 130.0, 0.0  , 95.0  , 286.0, 347.0, 634.0, 392.0, 199.0, 333.0, 659.0, 720.0, 921.0},
//  {417.0 , 813.0, 772.0, 787.0 , 777.0, 788.0, 217.0, 95.0 , 0.0   , 372.0, 434.0, 692.0, 479.0, 286.0, 419.0, 746.0, 807.0, 1007.0},
//  {604.0 , 610.0, 569.0, 583.0 , 574.0, 585.0, 154.0, 286.0, 372.0 , 0.0  , 62.0 , 516.0, 273.0, 102.0, 197.0, 542.0, 479.0, 804.0},
//  {665.0 , 597.0, 556.0, 555.0 , 561.0, 572.0, 216.0, 347.0, 434.0 , 62.0 , 0.0  , 558.0, 316.0, 161.0, 240.0, 530.0, 432.0, 775.0},
//  {291.0 , 426.0, 376.0, 725.0 , 385.0, 396.0, 506.0, 634.0, 692.0 , 516.0, 558.0, 0.0  , 259.0, 540.0, 289.0, 381.0, 731.0, 613.0},
//  {408.0 , 458.0, 409.0, 615.0 , 417.0, 428.0, 264.0, 392.0, 479.0 , 273.0, 316.0, 259.0, 0.0  , 296.0, 111.0, 410.0, 635.0, 642.0},
//  {517.0 , 634.0, 593.0, 607.0 , 598.0, 609.0, 68.0 , 199.0, 286.0 , 102.0, 161.0, 540.0, 296.0, 0.0  , 219.0, 564.0, 597.0, 826.0},
//  {504.0 , 435.0, 394.0, 487.0 , 399.0, 410.0, 205.0, 333.0, 419.0 , 197.0, 240.0, 289.0, 111.0, 219.0, 0.0  , 370.0, 505.0, 622.0},
//  {668.0 , 70.0 , 29.0 , 340.0 , 35.0 , 46.0 , 531.0, 659.0, 746.0 , 542.0, 530.0, 381.0, 410.0, 564.0, 370.0, 0.0  , 503.0, 255.0},
//  {973.0 , 526.0, 502.0, 176.0 , 494.0, 507.0, 592.0, 720.0, 807.0 , 479.0, 432.0, 731.0, 635.0, 597.0, 505.0, 503.0, 0.0  , 553.0},
//  {901.0 , 236.0, 239.0, 391.0 , 232.0, 224.0, 793.0, 921.0, 1007.0, 804.0, 775.0, 613.0, 642.0, 826.0, 622.0, 255.0, 553.0, 0.0},
//};
//  const char *noms[NB_EQUIPE] = {
//    "Toulouse",
//    "Cergy",
//    "Meudon",
//    "Amneville",
//    "Francais_Volants",
//    "Asnieres",
//    "Valence",
//    "Avignon",
//    "Marseille",
//    "Chambery",
//    "Annecy",
//    "Limoges",
//    "Clermont",
//    "Villard",
//    "Roanne",
//    "Evry",
//    "Strasbourg",
//    "Wasquehal"
//  };
  float pMutPerGene = 0.001;




// User functions


bool isInPool(int n, int *pool, int size){
  for(int i = 0; i < size ; i ++){
    if(pool[i] == n){
      return true;
    }
  }
  return false;
}

int firstPossibleFromPool(int *source, int *dest, int dest_size){
  for(int i = 0; i < NB_EQUIPE / 2 ; i++){
    if(! isInPool(source[i], dest, dest_size)){
      return source[i];
    }
  }

  return -1;
}

int firstPossible(int *dest, int dest_size){
  for(int i = 0; i < NB_EQUIPE; i++){
    if(! isInPool(i, dest, dest_size)){
      return i;
    }
  }
  return -1;
}


int compareClassement( const void* a, const void* b)
{
  int p1 = *(int*)a;
  int p2 = *(int*)b;

  return classement[p1] - classement[p2];
}




// No before everything else function.


// No after eveything else function.



void evale_pop_chunk(CIndividual** population, int popSize){
  
// No Instead evaluation step function.

}

void optiInit(int argc, char** argv){
	
}

void optiFinal(CPopulation* pop){
	;
}

void EASEABeginningGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm){

// No at beginning of generation function.

}

void EASEAEndGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	
// No at end of generation function.

}

void EASEAGenerationFunctionBeforeReplacement(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	
// No generation function.

}


IndividualImpl::IndividualImpl() : CIndividual() {
   
  // Genome Initialiser
 // "initializer" is also accepted
  //coeff = setVariable("u3", 110);

  int size_a = 0;
  int size_b = 0;
  for(int i = 0; i < NB_EQUIPE; i++){
    if( globalRandomGenerator->tossCoin() && size_a < NB_EQUIPE / 2) {
      // On a tiré A et il y a de la place dans A
      (*this).poolA[size_a] = i;
      size_a ++;
    } else if( size_b < NB_EQUIPE / 2){
      // On a tiré B et il y a de la place dans B
      // Ou A est plein
      (*this).poolB[size_b] = i;
      size_b ++;
    } else {
      // On a tiré B mais B est plein
      (*this).poolA[size_a] = i;
      size_a ++;
    }
  }

  valid = false;
  isImmigrant = false;
}

CIndividual* IndividualImpl::clone(){
	return new IndividualImpl(*this);
}

IndividualImpl::~IndividualImpl(){
  // Destructing pointers

}


float IndividualImpl::evaluate(){
  if(valid)
    return fitness;
  else{
    valid = true;
 // Returns the score
{
  double score_dist  = 0.0;
  double score_class = 0.0;


  // Ajout des distances
  for(int i = 0; i < NB_EQUIPE / 2 ; i++){
    for(int j = 0; j < NB_EQUIPE / 2 ; j++){
      score_dist += distances[(*this).poolA[i]][(*this).poolA[j]];
      score_dist += distances[(*this).poolB[i]][(*this).poolB[j]];
    }
  }

  // Ajout des différences de points

  qsort((*this).poolA, NB_EQUIPE / 2, sizeof(int), compareClassement);
  qsort((*this).poolB, NB_EQUIPE / 2, sizeof(int), compareClassement);

  for(int i = 0; i < NB_EQUIPE / 2; i++){
    int diff = classement[(*this).poolA[i]] - classement[(*this).poolB[i]];
    if(diff < 0){
      score_class -= diff;
    } else {
      score_class += diff;
    }
  }

  double distance = (coeff*score_class + score_dist) / sqrt(pow(coeff,2.0) + 1);
  if(distance < 0){
    distance = -1*distance;
  }

  // Point (x: dist, y: class)
  return fitness =  distance;
}

  }
}

void IndividualImpl::boundChecking(){
	
// No Bound checking function.

}

string IndividualImpl::serialize(){
    ostringstream EASEA_Line(ios_base::app);
    // Memberwise serialization
	for(int EASEA_Ndx=0; EASEA_Ndx<9; EASEA_Ndx++)
		EASEA_Line << this->poolB[EASEA_Ndx] <<" ";
	for(int EASEA_Ndx=0; EASEA_Ndx<9; EASEA_Ndx++)
		EASEA_Line << this->poolA[EASEA_Ndx] <<" ";

    EASEA_Line << this->fitness;
    return EASEA_Line.str();
}

void IndividualImpl::deserialize(string Line){
    istringstream EASEA_Line(Line);
    string line;
    // Memberwise deserialization
	for(int EASEA_Ndx=0; EASEA_Ndx<9; EASEA_Ndx++)
		EASEA_Line >> this->poolB[EASEA_Ndx];
	for(int EASEA_Ndx=0; EASEA_Ndx<9; EASEA_Ndx++)
		EASEA_Line >> this->poolA[EASEA_Ndx];

    EASEA_Line >> this->fitness;
    this->valid=true;
    this->isImmigrant = false;
}

IndividualImpl::IndividualImpl(const IndividualImpl& genome){

  // ********************
  // Problem specific part
  // Memberwise copy
    {for(int EASEA_Ndx=0; EASEA_Ndx<9; EASEA_Ndx++)
       poolB[EASEA_Ndx]=genome.poolB[EASEA_Ndx];}
    {for(int EASEA_Ndx=0; EASEA_Ndx<9; EASEA_Ndx++)
       poolA[EASEA_Ndx]=genome.poolA[EASEA_Ndx];}



  // ********************
  // Generic part
  this->valid = genome.valid;
  this->fitness = genome.fitness;
  this->isImmigrant = false;
}


CIndividual* IndividualImpl::crossover(CIndividual** ps){
	// ********************
	// Generic part
	IndividualImpl** tmp = (IndividualImpl**)ps;
	IndividualImpl parent1(*this);
	IndividualImpl parent2(*tmp[0]);
	IndividualImpl child(*this);

	//DEBUG_PRT("Xover");
	/*   cout << "p1 : " << parent1 << endl; */
	/*   cout << "p2 : " << parent2 << endl; */

	// ********************
	// Problem specific part

  for(int i = 0; i < NB_EQUIPE/2; i++){
    int team = -1;
    if(globalRandomGenerator->tossCoin()){
      // On essaie de prendre du parent 1.
      team = firstPossibleFromPool(parent1.poolA, child.poolA, i);
    }
    if(team == -1){
      // Si on a pas pris du parent 1 ou si ca a échoué.
      team = firstPossibleFromPool(parent2.poolA, child.poolA, i);
    }

    if(team == -1){
      // Si aucun des parents ne fonctionne
      team = firstPossible(child.poolA, i);
    }
  }

  int size_b = 0;

  for(int i = 0; size_b < NB_EQUIPE / 2; i++){
    // On complete avec les données manquantes.
    if(! isInPool(i, child.poolA, NB_EQUIPE / 2)){
      child.poolB[size_b] = i;
      size_b ++;
    }
  }



	child.valid = false;
	/*   cout << "child : " << child << endl; */
	return new IndividualImpl(child);
}


void IndividualImpl::printOn(std::ostream& os) const{
	

//  printf("Pool A :\n");
//  for(int i = 0; i < NB_EQUIPE/2; i++){
//    printf("%s (%d)\n", noms[(*this).poolA[i]], classement[(*this).poolA[i]]);
//  }

//  printf("Pool B :\n");
//  for(int i = 0; i < NB_EQUIPE/2; i++){
//    printf("%s (%d)\n", noms[(*this).poolB[i]], classement[(*this).poolB[i]]);
//  }

//  float score2 = 0.0;
//  for(int i = 0; i < NB_EQUIPE / 2 ; i++){
//    for(int j = 0; j < NB_EQUIPE / 2 ; j++){
//      score2 += distances[(*this).poolA[i]][(*this).poolA[j]];
//      score2 += distances[(*this).poolB[i]][(*this).poolB[j]];
//    }
//  }

//  printf("Dist : %lf\n", score2);

}

std::ostream& operator << (std::ostream& O, const IndividualImpl& B)
{
  // ********************
  // Problem specific part
  O << "\nIndividualImpl : "<< std::endl;
  O << "\t\t\t";
  B.printOn(O);

  if( B.valid ) O << "\t\t\tfitness : " << B.fitness;
  else O << "fitness is not yet computed" << std::endl;
  return O;
}


unsigned IndividualImpl::mutate( float pMutationPerGene ){
  this->valid=false;


  // ********************
  // Problem specific part
 // Must return the number of mutations
  int nb_mut = 0;
  for(int i = 0; i < NB_EQUIPE / 2; i++){
    if( globalRandomGenerator->tossCoin(pMutPerGene) ){
      int pos_a = globalRandomGenerator->random(0, NB_EQUIPE / 2);
      int pos_b = globalRandomGenerator->random(0, NB_EQUIPE / 2);

      int temp = (*this).poolA[pos_a];
      (*this).poolA[pos_a] = (*this).poolB[pos_b];
      (*this).poolB[pos_b] = temp;
      nb_mut ++;
    }
  }
  return  nb_mut>0?true:false;

}

void ParametersImpl::setDefaultParameters(int argc, char** argv){

	this->minimizing = true;
	this->nbGen = setVariable("nbGen",(int)200);

	seed = setVariable("seed",(int)time(0));
	globalRandomGenerator = new CRandomGenerator(seed);
	this->randomGenerator = globalRandomGenerator;


	selectionOperator = getSelectionOperator(setVariable("selectionOperator","Tournament"), this->minimizing, globalRandomGenerator);
	replacementOperator = getSelectionOperator(setVariable("reduceFinalOperator","Tournament"),this->minimizing, globalRandomGenerator);
	parentReductionOperator = getSelectionOperator(setVariable("reduceParentsOperator","Tournament"),this->minimizing, globalRandomGenerator);
	offspringReductionOperator = getSelectionOperator(setVariable("reduceOffspringOperator","Tournament"),this->minimizing, globalRandomGenerator);
	selectionPressure = setVariable("selectionPressure",(float)2.000000);
	replacementPressure = setVariable("reduceFinalPressure",(float)2.000000);
	parentReductionPressure = setVariable("reduceParentsPressure",(float)2.000000);
	offspringReductionPressure = setVariable("reduceOffspringPressure",(float)2.000000);
	pCrossover = 1.000000;
	pMutation = 1.000000;
	pMutationPerGene = 0.05;

	parentPopulationSize = setVariable("popSize",(int)1024);
	offspringPopulationSize = setVariable("nbOffspring",(int)1024);


	parentReductionSize = setReductionSizes(parentPopulationSize, setVariable("survivingParents",(float)1.000000));
	offspringReductionSize = setReductionSizes(offspringPopulationSize, setVariable("survivingOffspring",(float)1.000000));

	this->elitSize = setVariable("elite",(int)1);
	this->strongElitism = setVariable("eliteType",(int)1);

	if((this->parentReductionSize + this->offspringReductionSize) < this->parentPopulationSize){
		printf("*WARNING* parentReductionSize + offspringReductionSize < parentPopulationSize\n");
		printf("*WARNING* change Sizes in .prm or .ez\n");
		printf("EXITING\n");
		exit(1);	
	} 
	if((this->parentPopulationSize-this->parentReductionSize)>this->parentPopulationSize-this->elitSize){
		printf("*WARNING* parentPopulationSize - parentReductionSize > parentPopulationSize - elitSize\n");
		printf("*WARNING* change Sizes in .prm or .ez\n");
		printf("EXITING\n");
		exit(1);	
	} 
	if(!this->strongElitism && ((this->offspringPopulationSize - this->offspringReductionSize)>this->offspringPopulationSize-this->elitSize)){
		printf("*WARNING* offspringPopulationSize - offspringReductionSize > offspringPopulationSize - elitSize\n");
		printf("*WARNING* change Sizes in .prm or .ez\n");
		printf("EXITING\n");
		exit(1);	
	} 
	

	/*
	 * The reduction is set to true if reductionSize (parent or offspring) is set to a size less than the
	 * populationSize. The reduction size is set to populationSize by default
	 */
	if(offspringReductionSize<offspringPopulationSize) offspringReduction = true;
	else offspringReduction = false;

	if(parentReductionSize<parentPopulationSize) parentReduction = true;
	else parentReduction = false;

	generationalCriterion = new CGenerationalCriterion(setVariable("nbGen",(int)200));
	controlCStopingCriterion = new CControlCStopingCriterion();
	timeCriterion = new CTimeCriterion(setVariable("timeLimit",0));

	this->optimise = 0;

	this->printStats = setVariable("printStats",1);
	this->generateCSVFile = setVariable("generateCSVFile",0);
	this->generatePlotScript = setVariable("generatePlotScript",0);
	this->generateRScript = setVariable("generateRScript",0);
	this->plotStats = setVariable("plotStats",0);
	this->printInitialPopulation = setVariable("printInitialPopulation",0);
	this->printFinalPopulation = setVariable("printFinalPopulation",0);
	this->savePopulation = setVariable("savePopulation",0);
	this->startFromFile = setVariable("startFromFile",0);

	this->outputFilename = (char*)"opti";
	this->plotOutputFilename = (char*)"opti.png";

	this->remoteIslandModel = setVariable("remoteIslandModel",0);
	std::string* ipFilename=new std::string();
	*ipFilename=setVariable("ipFile","ip.txt");

	this->ipFile =(char*)ipFilename->c_str();
	this->migrationProbability = setVariable("migrationProbability",(float)0.330000);
    this->serverPort = setVariable("serverPort",2929);
}

CEvolutionaryAlgorithm* ParametersImpl::newEvolutionaryAlgorithm(){

	pEZ_MUT_PROB = &pMutationPerGene;
	pEZ_XOVER_PROB = &pCrossover;
	//EZ_NB_GEN = (unsigned*)setVariable("nbGen",200);
	EZ_current_generation=0;
    EZ_POP_SIZE = parentPopulationSize;
    OFFSPRING_SIZE = offspringPopulationSize;

	CEvolutionaryAlgorithm* ea = new EvolutionaryAlgorithmImpl(this);
	generationalCriterion->setCounterEa(ea->getCurrentGenerationPtr());
	ea->addStoppingCriterion(generationalCriterion);
	ea->addStoppingCriterion(controlCStopingCriterion);
	ea->addStoppingCriterion(timeCriterion);	

	EZ_NB_GEN=((CGenerationalCriterion*)ea->stoppingCriteria[0])->getGenerationalLimit();
	EZ_current_generation=&(ea->currentGeneration);

	 return ea;
}

void EvolutionaryAlgorithmImpl::initializeParentPopulation(){
	if(this->params->startFromFile){
	  ifstream EASEA_File("opti.pop");
	  string EASEA_Line;
  	  for( unsigned int i=0 ; i< this->params->parentPopulationSize ; i++){
	  	  getline(EASEA_File, EASEA_Line);
		  this->population->addIndividualParentPopulation(new IndividualImpl(),i);
		  ((IndividualImpl*)this->population->parents[i])->deserialize(EASEA_Line);
	  }
	  
	}
	else{
  	  for( unsigned int i=0 ; i< this->params->parentPopulationSize ; i++){
		  this->population->addIndividualParentPopulation(new IndividualImpl(),i);
	  }
	}
        this->population->actualParentPopulationSize = this->params->parentPopulationSize;
}


EvolutionaryAlgorithmImpl::EvolutionaryAlgorithmImpl(Parameters* params) : CEvolutionaryAlgorithm(params){
	;
}

EvolutionaryAlgorithmImpl::~EvolutionaryAlgorithmImpl(){

}

