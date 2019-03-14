import random
import heapq

GENESEED = ['R', 'L', 'U', 'D']
ROWS = 3
COLS = 3
MOVES = 8
POPULATION = 10
ITERATIONS = 100

class Walks:
	def __init__(self, geneseed):
		self.chromo = [random.choice(GENESEED) for i in range(MOVES)]
		self.grid = [[False for i in range(COLS)] for j in range(ROWS)]
		self.count = 0
	
	def print_grid(self):
		print(self.grid)
		
	def print_chromo(self):
		print(self.chromo)
			
	def move(self, step):
		return {
			'R': (1, 0),
			'L': (-1, 0),
			'U': (0, -1),
			'D': (0, 1)
		}.get(step)
	
	def inbound(self, x, y):
		return (x >= 0) and (x < ROWS) and (y >= 0) and (y < COLS)

	def go(self):
		x = y = 0
		self.grid[x][y] = True
		
		for i in range(MOVES):
			#creates new coordinate based on move
			step = self.move(self.chromo[i])
			x += step[0]
			y += step[1]
			
			#checks if cell is in bound or has already been visited
			if not self.inbound(x, y) or self.grid[x][y]:
				return self.count
				break

			else:
				self.grid[x][y] = True
				self.count += 1
	
	def mutation(self):
		i = random.randint(0, MOVES-1)
		move = random.choice(GENESEED)
		self.chromo[i] = move

class Gene_Algo:
	def __init__(self):
		self.population = [Walks(GENESEED) for i in range(POPULATION)]
		self.best = []
		self.stop = False
	
	def print_population(self):
		for i in self.population:
			i.print_chromo()
			i.print_grid()
			print(i.count)

	def run_walks(self):
		for i in self.population:
			i.go()
			if i.count == 8:
				self.best = i.chromo
				self.stop = True
				break

	def top2(self):
		tops = []
		a = [i.count for i in self.population]
		for i in range(2):
			indx = a.index(max(a))
			tops.append(self.population[indx])
			del a[indx]
			del self.population[indx]
		return tops

	def swap(self, walks):
		chromo = []
		for i in range(MOVES//2):
			chromo.append(walks[0].chromo[i])
		for i in range(MOVES//2, MOVES):
			chromo.append(walks[1].chromo[i])
		return chromo

	def breed(self):
		new_gene = []
		parents = self.top2()
		for i in range(POPULATION):
			child = Walks(GENESEED)
			child.chromo = self.swap(parents)
			child.mutation()
			new_gene.append(	child)
		self.population = new_gene

	def solve(self):
		for i in range(ITERATIONS):
			self.run_walks()
			if self.stop:
				print(self.best)
				break
			else:
				self.breed()

if __name__=="__main__":
	b = Gene_Algo()
	b.solve()