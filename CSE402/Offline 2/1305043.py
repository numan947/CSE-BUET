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
from queue import PriorityQueue


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
		self.__pq = PriorityQueue()



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
		
		#initialize the pq for the first time
		self._fix_pq()




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
		return self.__cost_function(
			self._get_conflict_count(t),
			self._get_conflict_count(r),
			self._get_conflict_count(c)
			)



	def _calculate_cost(self,time_table):
		
		cost = 0
		
		for r in range(5):
			for c in range(self.__num_perod):
				cost+=self._calculate_cell_cost(time_table[r][c])

		# print(cost)
		return cost


	def _fix_pq(self):
		
		def clear(pq):
			while not pq.empty():
				try:
					pq.get(False)
				except Empty:
					continue
				pq.task_done()

		
		clear(self.__pq)

		cost = 0
		for r in range(5):
			for c in range(self.__num_perod):
				tmp=self._calculate_cell_cost(self.__tt_grid[r][c])
				self.__pq.put((-1*tmp,(r,c))) #THE MESSY -1 multiplication hack -_-
				cost+=tmp					# why do I even have to put up with this shit?! -_- 

		self._set_cost(cost) #setting table cost





	#for getting the next element
	def _get_next_cell(self):
		if(self.__pq.empty()):
			return None
		return self.__pq.get()



	#just for printing purpose
	def _print_pq(self):
		while(not self.__pq.empty()):
			print(self.__pq.get())
		self._fix_pq()


	def _set_cost(self,cost):
		self.__table_cost = cost

	def _get_cost(self):
		return self.__table_cost

	def _get_elements(self):
		return self.__elements

	def _get_table(self):
		return self.__tt_grid

	def _set_table(self,grid):
		self.__tt_grid = grid

	def _print_table(self,table):

		for r in range(5):
			for c in range(self.__num_perod):
				print("Pos: ",r,c,"elements:",len(table[r][c]))
				for e in table[r][c]:
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





def ClimbTheDamnHill(timetable,num_perod):
	def get_coord(e):
		return e[1][0],e[1][1]




	timetable._random_init_table() #evaluating start state
	#timetable._check_count()
	#timetable._print_pq()

	if(timetable._get_cost()==0):
		return

	

	while(True):

		e = timetable._get_next_cell()
		if(e==None):
			print("RETURNING BECAUSE OF NONE")
			return
		r,c = get_coord(e)

		cur_grid = deepcopy(timetable._get_table())

		cur_lst = cur_grid[r][c]


		flg = False

		for i in range(len(cur_lst)):
			new_cell_state = [cur_lst[x] for x in range(len(cur_lst)) if x!=i]
			if(timetable._calculate_cell_cost(cur_lst)>timetable._calculate_cell_cost(new_cell_state)):
				#cost lessens if this item is not in the cell,so try to find a better place for this
				item = cur_grid[r][c].pop(i)
				for rr in range(5):
					for cc in range(num_perod):
						if(r!=rr and c!=cc):
							#put the item in the cell
							cur_grid[rr][cc].append(item)
							new_cost = timetable._calculate_cost(cur_grid)

							if(new_cost<timetable._get_cost()):
								timetable._set_cost(new_cost)
								timetable._set_table(cur_grid)
								flg = True

							else:
								cur_grid[rr][cc].pop(len(cur_grid[rr][cc])-1)

						if(flg):
							break
					if(flg):
						break
				if(not flg):
					cur_grid[r][c].insert(i,item)
			if(flg):
				break
		timetable._fix_pq()
		print(timetable._get_cost())
		timetable._check_count()












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


	#print("Number of days: ",5," Number of periods each day: ",num_perod," Total periods: ",5*num_perod)
	ClimbTheDamnHill(tt,num_perod)

	# print(tt._get_cost())

	# tt._print_table()



	# tt._random_init_table() #randomly initialize the table

	
	# # tt._print_table()

	# # tt._check_count()


	# tt._calculate_cell_cost(tt._get_table()[0][0])

	# tt._calculate_cost(tt._get_table())

	# tt._fix_pq()

	# print(tt._get_next_cell())












if __name__ == "__main__":
	main()