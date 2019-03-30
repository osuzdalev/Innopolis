class unique_element:
	def __init__(self,value,occurrences):
		self.value = value
		self.occurrences = occurrences

def perm_unique(elements):
	eset=set(elements)
	listunique = [unique_element(i,elements.count(i)) for i in eset]
	u=len(elements)
	return perm_unique_helper(listunique,[0]*u,u-1)

def perm_unique_helper(listunique,result_list,d):
	if d < 0:
		yield tuple(result_list)
	else:
		for i in listunique:
			if i.occurrences > 0:
				result_list[d]=i.value
				i.occurrences-=1
				for g in  perm_unique_helper(listunique,result_list,d-1):
					yield g
				i.occurrences+=1

def lst_filter(lst):
	lst_2 = []
	for i in lst:
		count = 0
		if i[len(i) - 1] == 'A':
			lst_2.append(i)
	return lst_2
		
		


a = list(perm_unique(['A','A','X','X','X','X']))
b = lst_filter(a)
print(a)
print(len(a))