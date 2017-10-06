import random
import math
from copy import copy, deepcopy




class RubiksCube:

	def __init__(self,target_state,input_state):  #Constructor
		self.__heuristic = 0 #heuristic value for current state
		self.__distance = 0 #distance for current state
		self.__parent = None #parent of current state
		self.__current_state = input_state #input state
		self.__goal_state = target_state #solution state

		assert (len(self.__current_state) == len(self.__goal_state)) #just making sure everything is in order
		self.__dimension = len(self.__current_state) #saving the dimension of the matrix
		self.__goal_map = self._generate_goal_map(self.__goal_state)


	def __eq__(self,other): #Utility function for equality check
		return (self.__current_state ==other.__current_state) and (self.__goal_state == other.__goal_state)

	def __str__(self): #Utility function for printing a RubiksCube Object
		ret = "Current_State:\r\n"

		for row in range(self.__dimension):
			ret+=" ".join(map(str,self.__current_state[row]))
			ret+="\r\n"
		ret+="Goals:\r\n"
		ret+=str(self.__goal_map)
		return ret

	



	def _clone(self): #Utility function for generating Rubik's cube clone

		return RubiksCube(deepcopy(self.__goal_state),deepcopy(self.__current_state))

	def _transpose(self): #Utility function for transposing the Rubik's cube
		self.__current_state = list(map(list,zip(*self.__current_state)))

	def _generate_goal_map(self,goal_state): #Genrates goal map for different colors, e.g. (Color,goal) (int,String)

		goal_map = {}

		def all_same(items):
			return all(x == items[0] for x in items)

		if(all_same(goal_state[0])): # True == row wise target color
			for x in range(self.__dimension):
				goal_map[goal_state[x][x]] = "R"+str(x)
		else: # False == column wise target color
			for x in range(self.__dimension):
				goal_map[goal_state[x][x]] = "C"+str(x)
		
		return goal_map

	

	def _move_right(self,row_num): #move the row right 
		assert(row_num>=0 and row_num<self.__dimension)
		self.__current_state[row_num] = self.__current_state[row_num][2:]+self.__current_state[row_num][0:2]


	def _move_left(self,row_num): #move the row left
		assert(row_num>=0 and row_num<self.__dimension)
		l = len(self.__current_state[row_num])
		self.__current_state[row_num] = self.__current_state[row_num][l-2:]+self.__current_state[row_num][0:l-2]

	def _move_up(self,col_num):
		assert(col_num>=0 and col_num<self.__dimension)
		self._transpose()
		self._move_left(col_num)
		self._transpose()

	def _move_down(self,col_num):
		assert(col_num>=0 and col_num<self.__dimension)
		self._transpose()
		self._move_right(col_num)
		self._transpose()

	def _generate_moves(self): #Returns all the moves --> 4*dimension in total
		def _clone_and_rotate(i):
			tmp = []
			p = self._clone()
			p._move_left(i)
			tmp.append(p)
			p = self._clone()
			p._move_right(i)
			tmp.append(p)
			p = self._clone()
			p._move_up(i)
			tmp.append(p)
			p = self._clone()
			p._move_down(i)
			tmp.append(p)
			return tmp

		ret = []

		for rc in range(self.__dimension):
			ret+=_clone_and_rotate(rc)
		return ret



	

	def _generate_solution(self,path): #Recursively constructs the solution
		if(self.__parent == None):
			return path
		else:
			path.append(self)
			return self._generate_solution(path)

	def _calcH(self): #calculates Heuristic for the cube
		total = 0

		for i in range(self.__dimension):
			for j in range(self.__dimension):

				cur = self.__current_state[i][j]
				target = self.__goal_map[cur]

				dst = 0
				if(target[0]=='C'):
					dst = min(abs(int(target[1] - j)),abs(self.__dimension - (int(target[1])-j)))
				
				elif(target[0]=='R'):
					dst = min(abs(int(target[1] - i)),abs(self.__dimension - (int(target[1])-i)))
				total+=dst

		return total


		#TODO

	def solve_cube(self): #Main solver for the cube

		def done(cube):
			return cube.__current_state == cube.__goal_state
		#TODO















def main():
	goal_state = [
			 [1,2,3],
			 [1,2,3],
			 [1,2,3]
			 ]

	start_state = [
			 [2,1,3],
			 [2,3,1],
			 [3,1,2]
			 ]
	cube = RubiksCube(goal_state, start_state)
	print("Original:\r\n")
	print(cube)
	
if __name__ == "__main__":
	main()