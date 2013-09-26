GeneticAlgorithm1
=================

(Very) Basic genetic algorithm
by Dark Savant and Korn101

*apologies in advance for spelling errors*

Background:

	Genetic Algorithms (or evolutionary algorithms) are a way of finding solutions to problems that cannot neccessarily be solved by regular mathematical modelling techniques. 
	These types of algorithms get their name because of how they attempt to 'model' the environment 
	or nature. 
	They use a simulated version of Darwinian evolution to evolve the best possible solution to a problem.
	
Information:

	These classes have been written in a way that makes them completely dynamic and easy to manipulate.
	Features include:	-Variable chromosome length
										-Variable gene bitlength
										-Dynamic memory allocation that allows things like chromosome length to be altered at Run-time.
	
Notes:

	Although chromosome length can be determined (and changed) at runtime, there are still some restrictions:
		-binaryNumber bit length (the gene code) is fixed at compile time, but can be changed.)
		-static mutation rate (organisms share the same mutation rate but can be changed in the code)
		-although the code runs fast, it is not optomized for speed and may suffer in high use situations.
	
Program Structure:

-> binaryNumber class:
			
			-The binaryNumber object is an object which represents a binary number of variable number of bits. 
			-It is an effective way of representing genes.
			-It is easy to work with in terms of genetic operators like gene 'crossover'
			-Has overloaded operators such as = to perform deep copy, and [] (subscript) to directly alter individual bits.
	
-> Organism class:

			-This class represents an Organism, an organism has traits which are represented by Genes (binaryNumber's)
			-Genes are placed together in a set order within - what we call - a CHROMOSOME.
			-The chromosome is an array of binaryNumber genes.
			-Organism class contains the genetic operators such as:
							-genetic 'crossover' (crossover)
							-organism 'mating' (mate)
							-organism 'reproduction' (reproduce)
							-genetic 'mutation' (mutate)
			-Also has overloaded operators similar to binaryNumber class.

-> Controller class:

			-This is the class that serves as the frontend to the Genetic Algorithm.
			-Also known as the Evolutionary control.
			-Holds the current population or Organisms.
			-Handles the organism evolution over generations.
			-Evaluates fitness of individual organisms.
			-Extra features include:
					-graphing function (graphs max fitness per generation)
					-exception handling (extremely basic - for now atleast)
					
