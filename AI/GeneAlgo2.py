import random
import copy

RANGE_BOT = 60
RANGE_UP = 90
TONICS = [0 + 12 * i for i in range(6)]
CHORD_SIZE = 3
SEQUENCE_SIZE = 3
POPULATION = 100
ITERATIONS = 1000

def checkSubdominant(sequence):
	return sequence[1][0] == sequence[0][0] + 5

def checkDominant(sequence):
	return sequence[2][0] == sequence[0][0] + 7

def checkChords(chord):
	return (chord[1] - chord[0] == 4) and (chord[2] - chord[0] == 7)

def checkIdenChords(sequence):
	return ((sequence[0] == sequence[1]) or (sequence[0] == sequence[2]) or (sequence[1] == sequence[2]))

def fitFunc(sequence):
	#Max fitness == 11
	fitness = 0
	#Tonic not C
	if sequence[0][0] not in TONICS:
		return fitness
	else:
		fitness += 4
	#checks if chords are identical
	if checkIdenChords(sequence):
		fitness -= 4
	#correct subDominant
	if checkSubdominant(sequence):
		fitness += 2
	#correct Dominant
	if checkDominant(sequence):
		fitness += 2
	#check each chords
	for i in range(SEQUENCE_SIZE):
		if checkChords(sequence[i]):
			fitness += 1
	return fitness

class Sequence:
	def __init__(self):
		self.chromo = [[random.randint(RANGE_BOT, RANGE_UP) for i in range(CHORD_SIZE)] for j in range(SEQUENCE_SIZE)]
		self.fitness = 0
	
	def printSequence(self):
		print(self.chromo)
	
	def mutation(self):
		self.chromo[random.randrange(0, SEQUENCE_SIZE)][random.randrange(0, CHORD_SIZE)] = random.randint(RANGE_BOT, RANGE_UP)
		#boosting chord fitness
		for i in range(SEQUENCE_SIZE):
			#Boosting Major 3rd
			if self.chromo[i][1] - self.chromo[i][0] < 4:
				self.chromo[i][1] += 1
			elif self.chromo[i][1] - self.chromo[i][0] > 4:
				self.chromo[i][1] -= 1
			#Boosting Perfect 5th
			if self.chromo[i][2] - self.chromo[i][0] < 7:
				self.chromo[i][2] += 1
			elif self.chromo[i][2] - self.chromo[i][0] > 7:
				self.chromo[i][2] -= 1

class Gene_Algo:
	def __init__(self):
		self.population = [Sequence() for i in range(POPULATION)]
		self.maxfitness = 11
		self.best = []
		self.stop = False
		
	def printPopulation(self):
		print("POPULATION")
		for i in self.population:
			print(i.chromo)
		print()
	
	def checkSequence(self):
		for i in self.population:
			i.fitness = fitFunc(i.chromo)
			if i.fitness == self.maxfitness:
				self.best = i.chromo
				self.stop = True
				break
	
	def getBest(self):
		a = [i.fitness for i in self.population]
		indx = a.index(max(a))
		self.best = self.population[indx].chromo
	
	def top2(self):
		#return array of Object "Sequences"
		#tops need to be in same octave
		tops = []
		a = [i.fitness for i in self.population]
		for i in range(2):
			indx = a.index(max(a))
			tops.append(copy.deepcopy(self.population[indx]))
			del a[indx]
			del self.population[indx]
		return tops
	
	def swap(self, tops):
		#return array of 2 new chromos
		indx = random.randrange(0, SEQUENCE_SIZE)
		temp = tops[0].chromo[indx]
		tops[0].chromo[indx] = tops[1].chromo[indx]
		tops[1].chromo[indx] = temp
		return tops
	
	def breed(self):
		new_gene = []
		parents = self.top2()
		for i in range(POPULATION//2):
			#Parents produce 2 offsprings with 50/50 switch
			#producing 2 offsprings
			offsprings = [Sequence(), Sequence()]
			#producing their chronos from parents
			new_chromos = self.swap(parents)
			#assigning chronos to offsprings
			offsprings[0].chromo = new_chromos[0].chromo
			offsprings[1].chromo = new_chromos[1].chromo
			#mutations
			offsprings[0].mutation()
			offsprings[1].mutation()

			new_gene.append(copy.deepcopy(offsprings[0]))
			new_gene.append(copy.deepcopy(offsprings[1]))
		self.population = new_gene
	
	def solve(self):
		for i in range(ITERATIONS):
			self.checkSequence()
			self.getBest()
			print("BEST")
			print(self.best, "\n")
			if self.stop:
				print("\t\tSOLUTION")
				print(self.best)
				break
			else:
				self.breed()
		print("Last Iteration")

if __name__=="__main__":
	b = Gene_Algo()
	b.solve()