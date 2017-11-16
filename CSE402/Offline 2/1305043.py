import bisect
import timeit
from copy import copy, deepcopy
import logging
import math
import random
import re
import argparse
import itertools
from collections import Counter

def print_total_periods(tt_grid):
	print(len(list(itertools.chain.from_iterable(tt_grid))))




def read_input(rooms,classes,teachers,file):

	fin = open(file,"r")
#	lin_read = rooms*classes

	elems = []
	
	for r in range(rooms):
		for c in range(classes):
			ff = fin.readline() #read line

			tt = re.split(pattern=" |\n", string=ff) #split
			tt = [x for x in tt if x] #filter out empty string

			for t in range(teachers):

				t_rep = int(tt[t])
				for _ in range(t_rep):
					elems.append(Element(t,c,r))


			#print(tt)

			#print("room no: "+str(r),"class no: "+str(c),ff)

	# print("Total elements: "+str(len(elems)))
	# for x in elems:
	# 	print(x)

	return elems



def test(pos,num_perod):
	x = math.ceil(pos/num_perod)
	y = pos%num_perod 

	print(x,y)


class Element(object):
	"""docstring for Element"""
	def __init__(self, t,c,r):
		self.__tch = t
		self.__cls = c
		self.__rom = r

	def get_tch(self):
		return self.__tch
	
	def get_cls(self):
		return self.__cls
	
	def get_rom(self):
		return self.__rom


	#position in timetable grid
	def _setposition(self,x,y):
		self.__position = (x,y)	

	#position in timetable grid
	def _getposition(self):
		return self.__position
	
	def __describe__(self):
		return "Room: "+str(self.__rom)+" Class: "+str(self.__cls)+" Teacher: "+str(self.__tch)

	def __unicode_describe__(self):
		return u"Room: "+str(self.__rom)+" Class: "+str(self.__cls)+" Teacher: "+str(self.__tch)

	def __str__(self):
		return "<"+" R:"+str(self.__rom)+", C:"+str(self.__cls)+", T:"+str(self.__tch)+" >"





class TimeTable(object):
	"""docstring for TimeTable"""
	def __init__(self,elements,num_perod,cost_function):
		self.__elements = elements
		self.__num_perod = num_perod
		self.__cost_function = cost_function

	def _random_init_table(self):
		
		tot_pos = 5*self.__num_perod

		tt_grid = []

		for i in range(5): #adding weekly days
			tt_grid.append([])
			for k in range(self.__num_perod): #adding day's periods
				tt_grid[i].append([])

		# print(len(self.__elements))

		i=0

		for e in self.__elements:
			pos = random.randint(1, tot_pos)
			xx = (math.ceil(pos/self.__num_perod))-1
			yy = (pos%self.__num_perod)-1

			tt_grid[xx][yy].append(e)
			e._setposition(xx,yy)
			i+=1
			#print("Printing x,y position: ",x,y) 

		self.__tt_grid = tt_grid

		# i = 0
		# for r in range(5):
		# 	for c in range(self.__num_perod):
		# 		i+=len(self.__tt_grid[r][c])

		# print("len ",i)

	def _get_conflict_count(self,lst):
		c = Counter(lst)
		conf = 0

		for x,y in c.items():
			conf+=max(0, y-1)

		return conf


	def _calculate_cell_cost(self,lst):
		t = []
		r = []
		c = []

		for x in lst:
			t.append(x.get_tch())
			r.append(x.get_rom())
			c.append(x.get_cls())
		# print(t)
		# print(r)
		# print(c)
		self._get_conflict_count(t),self._get_conflict_count(r),self._get_conflict_count(c))



	def _calculate_cost(self):
		pass


	def _calculate_another_cost(self):
		pass




	def _get_elements(self):
		return self.__elements

	def _get_table(self):
		return self.__tt_grid

	def _print_table(self):

		for r in range(5):
			for c in range(self.__num_perod):
				print("Pos: ",r,c,"elements:",len(self.__tt_grid[r][c]))
				for e in self.__tt_grid[r][c]:
					print(e)


	def _check_count(self):
		cnt = 0
		
		for r in range(5):
			for c in range(self.__num_perod):
				cnt += len(self.__tt_grid[r][c])

		print("Checked: ",cnt)		



def cost1_1_1(tc,rc,cc):
	return tc+rc+cc


def cost10_1_1(tc,rc,cc):
	return (10*tc)+rc+cc


def cost1_10_1(tc,rc,cc):
	return (tc)+(10*rc)+cc


def cost1_1_10(tc,rc,cc):
	return (tc)+(rc)+(10*cc)



def main():
	parser = argparse.ArgumentParser()
	parser.add_argument("--file","-f",type=str,required = True)
	parser.add_argument("--rooms","-r",type=int,required=True)
	parser.add_argument("--teachers","-t",type=int,required=True)
	parser.add_argument("--classes","-c",type=int,required=True)
	parser.add_argument("--periods","-p",type=int,required=True)
	args = parser.parse_args()

	num_teach = args.teachers
	num_rooms = args.rooms
	num_class = args.classes
	file_read = args.file
	num_perod = args.periods

	elems = read_input(num_rooms,num_class,num_teach,file_read) #generate elements

	tt = TimeTable(elements=elems, num_perod=num_perod,cost_function=cost1_1_1) #create table from the elements

	tt._random_init_table() #randomly initialize the table

	
	tt._print_table()

	# tt._check_count()


	tt._calculate_cell_cost(tt._get_table()[0][0])










if __name__ == "__main__":
	main()