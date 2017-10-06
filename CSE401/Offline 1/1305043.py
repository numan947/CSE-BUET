import random
import math
from copy import copy, deepcopy
from queue import PriorityQueue




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

		self.__move = None


	def __eq__(self,other): #Utility function for equality check
		if(self.__class__ != other.__class__):
			return False
		return (self.__current_state ==other.__current_state) and (self.__goal_state == other.__goal_state)

	def __str__(self): #Utility function for printing a RubiksCube Object
		
		ret = "Current_State:\r\n"

		for row in range(self.__dimension):
			ret+=" ".join(map(str,self.__current_state[row]))
			ret+="\r\n"
		ret+="Goals:\r\n"
		ret+=str(self.__goal_map)
		ret+="\r\nMove Parent: "
		if(self.__move == None):
			ret+="No more move"+"\r\n"
		else:
			ret+=self.__move+"\r\n"

		ret+="Parent State:\r\n"
		if(self.__parent != None):
			for row in range(self.__dimension):
				ret+=" ".join(map(str,self.__parent.__current_state[row]))
				ret+="\r\n"
		else:
			ret+="No Parent State\r\n"
		
		return ret



	def get_parent_state(self):
		ret = ""
		for row in range(self.__dimension):
			ret+=" ".join(map(str,self.__parent.__current_state[row]))
			ret+="\r\n"

		return ret

	def get_move_on_parent(self):
		return self.__move;

	def get_current_state(self):
		ret = ""

		for row in range(self.__dimension):
			ret+=" ".join(map(str,self.__current_state[row]))
			ret+="\r\n"
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
			p.__move = "L"+str(i)
			p.__distance = self.__distance+1
			p.__parent = self
			tmp.append(p)
			
			p = self._clone()
			p._move_right(i)
			p.__move = "R"+str(i)
			p.__distance = self.__distance+1
			p.__parent = self
			tmp.append(p)
			
			p = self._clone()
			p._move_up(i)
			p.__move = "U"+str(i)
			p.__distance = self.__distance+1
			p.__parent = self
			tmp.append(p)
			
			p = self._clone()
			p._move_down(i)
			p.__move = "D"+str(i)
			p.__distance = self.__distance+1
			p.__parent = self
			tmp.append(p)
			
			return tmp

		ret = []

		for rc in range(self.__dimension):
			ret+=_clone_and_rotate(rc)
		return ret



	def _calcH(self): #calculates Heuristic for the cube
		total = 0

		#print(self.__dimension)
		for i in range(self.__dimension):
			for j in range(self.__dimension):

				cur = self.__current_state[i][j]
				target = self.__goal_map[cur]

				# print(cur)
				# print(target)

				dst = 0
				if(target[0]=='C'):
					dst = min((abs(int(target[1]) - j)),abs(self.__dimension - abs(int(target[1])-j)))
					# print(str(i)+" "+str(j)+" "+str(dst))
				
				elif(target[0]=='R'):
					dst = min((abs(int(target[1]) - i)),abs(self.__dimension - abs(int(target[1])-i)))
				total+=dst

		return total

	def _generate_solution(self,path): #Recursively constructs the solution
		if(self.__parent is None):
			return path
		else:
			path.append(self)
			return self.__parent._generate_solution(path)



	def solve_cube(self): #Main solver for the cube

		def done(cube):
			return cube.__current_state == cube.__goal_state


		def findIndex(item,iters):
			if(item in iters):
				return iters.index(item)
			return -1

		to_visit = [self] #The states to explore, basically the PQ
		visited = [] #Already explored states

		state_cnt = 0


		while(len(to_visit)>0):

			new_state = to_visit.pop(0)

			state_cnt+=1
			print(new_state.get_current_state())

			print(state_cnt)
			

			if(done(new_state)):
				if(len(visited)>0):
					return new_state._generate_solution([]),state_cnt
				else:
					return [new_state],state_cnt


			successors = new_state._generate_moves()

			idx_to_visit = idx_visited = -1


			for move in successors:
				idx_to_visit = findIndex(move,to_visit)
				idx_visited = findIndex(move, visited)

				# minimize {f(n) = g(n) + h(n)}
				hval = move._calcH()
				fval = hval + move.__distance


				if(idx_visited == -1 and idx_to_visit == -1): #Forward edge
					move.__heuristic = hval
					to_visit.append(move)

				elif(idx_to_visit > -1):
					tmp = to_visit[idx_to_visit]

					if (fval < tmp.__heuristic + tmp.__distance):
						tmp.__heuristic = hval
						tmp.__move = move.__move
						tmp.__distance = move.__distance
						tmp.__parent = move.__parent
				elif(idx_visited > -1):
					tmp = visited[idx_visited]

					if (fval < tmp.__heuristic + tmp.__distance):
						tmp.__heuristic = hval
						tmp.__move = move.__move
						tmp.__distance = move.__distance
						tmp.__parent = move.__parent

						visited.remove(tmp) # We need to re-explore the state, as better can be found
						to_visit.append(tmp)

			visited.append(new_state)

			to_visit = sorted(to_visit, key = lambda p : p.__heuristic + p.__distance)

		return [],0















def main():
	goal_state = [
			 [1,1,1,1],
			 [2,2,2,2],
			 [3,3,3,3],
			 [4,4,4,4]
			 ]

	start_state = [
			 [2,1,1,4],
			 [4,2,1,4],
			 [4,1,2,3],
			 [3,3,3,2]
			 ]

	dif = [
			 [1,2,3,4],
			 [1,2,3,4],
			 [1,2,3,4],
			 [1,2,3,4]
			 ]
	nn=[
			 [1,2,3,4],
			 [1,2,3,4],
			 [1,2,3,4],
			 [1,2,3,4]
			 ]


	gola = [
			[1,1,1],
			[2,2,2],
			[3,3,3]
		   ]
	
	st = [
    [1,2,3],
    [1,2,3],
    [1,2,3]
    ]
	cube = RubiksCube(gola,st)
	print("Original:\r\n")
	
	print(cube)
	solution,explored_states = cube.solve_cube()
	print("total explored states: "+str(explored_states)+"\r\n")

	solution.reverse()


	#print(cube.get_current_state())

	print("Total steps needed: "+str(len(solution))+"\r\n")

	if(len(solution)>0):
		for i in range(0,len(solution)):
			cur = solution[i]
			
			if(cur.get_parent_state()==None):
				print("WTF")

			print(cur.get_parent_state())
			print("move: "+cur.get_move_on_parent()+"\r\n")
			#print(cur.get_current_state())

		print(solution[len(solution)-1].get_current_state())


if __name__ == "__main__":
	main()