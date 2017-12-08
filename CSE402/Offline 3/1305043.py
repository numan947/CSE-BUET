import bisect
import copy
import logging
import math
import random
import re

from prettytable import PrettyTable

# def printBoard():
# 	p = PrettyTable()

# 	for i in range(8):
# 		x = []
# 		for j in range(8):
# 			x.append(i*j)
# 		p.add_row(x)

# 	print(p.get_string(header=False,border=False))




class ReversiDisk():
	"""docstring for ClassName"""
	def __init__(self):
		self.currentSide = None #0->white, 1->black
		self.currentPosition = None #a tuple for (r,c) positioning system

	def setCurrentPosition(self,position):
		self.currentPosition = position

	def getCurrentPosition(self):
		return self.currentPosition

	def setCurrentSide(self,side):
		self.currentSide = side

	def getCurrentSide(self):
		return self.currentSide
	
	def __str__(self):
		st = ""
		st+=str(self.currentPosition)+"->"
		if self.currentSide==0 :
			st+="White"
		elif self.currentSide==1:
			st+="Black"
		return st




class ReversiBoard():
	"""docstring for ReversiBoard"""
	def __init__(self,heuristic):
		self.grid_heuristic = heuristic
		self.grid = []
		for i in range(8):
			tmp = []
			for j in range(8):
				tmp.append(-1)
			self.grid.append(tmp)

		self.black_list = []
		self.white_list = []

		self.total_disks = 0




	def _print_board(self):

		p=PrettyTable()
		for i in range(8):
			p.add_row(self.grid[i])

		print(p.get_string(header=False,border=False))





def main():

	dd = ReversiBoard([])

	dd._print_board()



if __name__ == "__main__":
	main()