import bisect
import copy
import logging
import math
import random
import re
import sys


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
	def __init__(self,currentSide = None,currentPosition = None):
		self.currentSide = currentSide #0->white, 1->black
		self.currentPosition = currentPosition #a tuple for (r,c) positioning system

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

	def __eq__(self,other):
		return self.currentPosition == other.getCurrentPosition()

	

def outofbound(x,y):
	return not(x>=0 and x<8 and y>=0 and y<8)




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

		self.row_mv = [ -1, 0, 1, -1, 1, -1, 0, 1 ]
		self.col_mv = [ -1, -1, -1, 0, 0, 1, 1, 1 ]


	def initialize_board(self):
		self.grid[3][3] = 0
		self.grid[4][4] = 0
		self.grid[3][4] = 1
		self.grid[4][3] = 1


		##test
		# self.grid[3][5]=1
		# self.grid[4][5]=0

		# w35 = ReversiDisk(currentSide=1,currentPosition=(3,5))
		# w45 = ReversiDisk(currentSide=0,currentPosition=(3,4))
		# self.white_list.append(w45)
		# self.black_list.append(w35)


		w33 = ReversiDisk(currentSide = 0,currentPosition = (3,3))
		w34 = ReversiDisk(currentSide = 0,currentPosition = (4,4))

		b43 = ReversiDisk(currentSide = 1,currentPosition = (3,4))
		b44 = ReversiDisk(currentSide = 1,currentPosition = (4,3))

		
		self.white_list.append(w33)
		self.white_list.append(w34)

		self.black_list.append(b43)
		self.black_list.append(b44)

		self.total_disks = 4


	def find_moves(self,side):

		def getMoves(moves,pos):
			posr,posc = pos
			print("Parent is: ",posr,posc)
			for idx in range(8):
				flag = False
				dirr = self.row_mv[idx]
				dirc = self.col_mv[idx]
				
				curr = posr+dirr
				curc = posc+dirc


				while(True):
					if(outofbound(curr,curc)):
						flag=False
						break
					if self.grid[curr][curc]==-1: #Found Empty
						break
					elif self.grid[curr][curc]==(1-side): #Found opposite color
						print("Making True for: ",curr,curc)
						flag=True
					else: #Found same color
						flag=False
						break
					curr = curr+dirr
					curc = curc+dirc

					

				if(flag):
					print(curr,curc)
					moves.append((curr,curc))


		moves = []

		if(side==0): #white
			for e in self.white_list:
				#start 8 directional search here
				getMoves(moves = moves, pos = e.getCurrentPosition())


		else: #black
			for e in self.black_list:
				getMoves(moves = moves, pos = e.getCurrentPosition())
		moves.sort()
		return moves



	def select_move(self,pos,side):
		rd = ReversiDisk(currentPosition = pos,currentSide = side)
		r,c = pos
		self.grid[r][c] = side

		if side==0: #white	
			self.white_list.append(rd)
		else: #black
			self.black_list.append(rd)

		self.total_disks+=1




	def apply_move(self,pos):
		
		r,c = pos
		side = self.grid[r][c]
		

		def applyMoves(pos):
			posr,posc = pos
			
			for idx in range(8):
				flag = False
				dirr = self.row_mv[idx]
				dirc = self.col_mv[idx]

				curr = posr+dirr
				curc = posc+dirc

				tr = None
				tc = None

				to_change = []

				while(True):
					if outofbound(curr,curc):
						break

					curside = self.grid[curr][curc]

					if(curside==-1): #we get -1 after a lot of blacks, so not replacable
						del to_change[:]
						break

					elif (curside==side): #we get a stopping point, we need to change all the lsts
						break
					else:
						to_change.append((curr,curc)) #append the tuple to the list
					
					curr+=dirr
					curc+=dirc

				if(len(to_change)>0):
					for (r,c) in to_change:
						self.grid[r][c] = side #make change in main grid

					if(side==0):# side is white, so remove from black,add in white list
						indx_lst = []
						for i in range(len(self.black_list)):
							if(to_change.count(self.black_list[i].getCurrentPosition())==1): #actually 1
								indx_lst.append(i)
							elif(to_change.count(self.black_list[i].getCurrentPosition())>1):
								raise ValueError(f"This shouldn't be printed")

						for i in range(len(indx_lst)):
							tmp = self.black_list.pop(indx_lst[i])
							tmp.setCurrentSide(side)
							self.white_list.append(tmp)

					else:# side is black, so remove from white,add in black list
						indx_lst = []
						for i in range(len(self.white_list)):
							if(to_change.count(self.white_list[i].getCurrentPosition())==1): #actually 1
								indx_lst.append(i)
							elif(to_change.count(self.white_list[i].getCurrentPosition())>1):
								raise ValueError(f"This shouldn't be printed")

						for i in range(len(indx_lst)):
							tmp = self.white_list.pop(indx_lst[i])
							tmp.setCurrentSide(side)
							self.black_list.append(tmp)
		applyMoves(pos)



	def get_total_disks(self):
		return self.total_disks


	def get_total_white(self):
		return len(self.white_list)

	def get_total_black(self):
		return len(self.black_list)

	def _print_board(self):
		print("\nWhite-->0,Black-->1")
		
		p=PrettyTable()
		p.add_row(['',0,1,2,3,4,5,6,7])
		for i in range(8):
			xx = []
			xx.append(i)
			for j in range(8):
				if self.grid[i][j]==1: #black
					xx.append('B')
				elif self.grid[i][j]==0: #white
					xx.append('W')
				else: #empty
					xx.append('e')
			p.add_row(xx)

		print(p.get_string(header=False,border=False))
		print("\n")







def PlayGame():
	h1 = []

	for i in range(8):
		tmp = []
		for j in range(8):
			tmp.append(0)
		h1.append(tmp)


	rv = ReversiBoard(h1)


	rv.initialize_board()
	rv._print_board()

	# print("Black Moves:")
	# print(rv.find_moves(side=1))
	
	# pos = tuple(int(x.strip()) for x in input().split(','))

	# rv.select_move(pos, side = 1)

	# rv.apply_move(pos)

	rv._print_board()

	turn = 1
	
	moves = rv.find_moves(turn)

	while(rv.get_total_disks()<64):
		if turn==0:
			print("White's Turn!")
		else:
			print("Black's Turn!")

		print("Input a comma seperated tuple: "+str(moves))
		pos = tuple(int(x.strip()) for x in input().split(','))
		rv.select_move(pos, turn)
		rv.apply_move(pos)

		print("White Score: "+str(rv.get_total_white()))
		print("Black Score: "+str(rv.get_total_black()))
		
		rv._print_board()
		
		moves = rv.find_moves(1-turn)
		if len(moves)>0: #moves available for opponent
			turn = 1-turn
		else:
			print("No Move for Opponent!!")
			moves = rv.find_moves(turn)



	if rv.get_total_black()>rv.get_total_white():
		print("Black Wins")
	elif rv.get_total_black()<rv.get_total_white():
		print("White Wins")
	else:
		print("Draw!!")

	print("Score: Black=",rv.get_total_black(),",White=",rv.get_total_white())





def main():
	PlayGame()



if __name__ == "__main__":
	main()