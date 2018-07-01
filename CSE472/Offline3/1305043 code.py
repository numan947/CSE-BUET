import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from numpy.linalg import solve
from sklearn.metrics import mean_squared_error
import matplotlib.pyplot as plt
from collections import defaultdict
import gzip


RATE_LOW = 0
RATE_HIGH = 5


def readGz(f):
  for l in gzip.open(f):
    yield eval(l)

def read_GZIP():
	cnt=0
	allRatings = []
	userRatings = defaultdict(list)
	for l in readGz("assignment2/train.json.gz"):
		user,item = l['reviewerID'],l['itemID']
		allRatings.append(l['rating'])
		userRatings[user].append(l['rating'])
		cnt+=1
		print(user,item)
		if(cnt>=100):
			break
	print(userRatings)





def make_dummy():
	print("\nREADING DATA.................................\n")
	MAXITEM = 5
	MAXUSER = 5

	ratings = np.random.uniform(low=RATE_LOW,high=RATE_HIGH,size=(MAXUSER, MAXITEM))
	print(ratings)
	wRat = make_weight_matrix(ratings)
	sparsity = 100.0*float(np.count_nonzero(wRat)/(wRat.shape[0]*wRat.shape[1]))

	#print(ratings.shape,wRat.shape)

	print("sparsity:",sparsity)
	print("\nDATA READING COMPLETED.......................\n")
	return ratings,sparsity


def read_data(col_names):
	return make_dummy()

def train_validation_test_split(ratings):
	train,test = train_test_split(ratings,test_size=0.4,random_state=94743)
	validation,test = train_test_split(test,test_size=0.5,random_state=94743)
	print(len(train))
	print(len(validation))
	print(len(test))


	#	return np.array([[5,0,5,0,0],[5,3,5,0,0],[1,2,3,4,5]]),validation,test
	return train,validation,test

def calculate_rmse(pred,actual):
	pred=pred[actual.nonzero()].flatten()
	actual=actual[actual.nonzero()].flatten()
	return np.sqrt(mean_squared_error(pred,actual))

def make_weight_matrix(ratingMatrix):
	tmp = ratingMatrix>=(RATE_LOW+1)
	#print(tmp*1)
	return tmp*1



class Matrix_Factorization():

	def __init__(self,ratingMatrix,latentFactors=5,lambdaU=0,lambdaV=0,printIntermediate=False):
		self.u_len,self.v_len = ratingMatrix.shape
		self.ratingMatrix = ratingMatrix
		self.latentFactors = latentFactors
		self.lambdaU = lambdaU
		self.lambdaV = lambdaV
		self.pr = printIntermediate
		self.W = make_weight_matrix(ratingMatrix)



	def ALSU(self,U,V,X,lam):
		#print(self.W)
		lamI = np.eye(self.latentFactors)*lam

		#print(X[0,:].shape)

		#print(V.shape)

		for p in range(U.shape[0]):
			Wu = np.diag(self.W[p,:])

			#print("Wu ",Wu.shape)
			#print(Wu)
			
			VTV = Wu.dot(V)
			#print("VTV1 shape ",VTV.shape)
			VTV = V.T.dot(VTV)
		#	print("VTV2 shape ",VTV.shape)

			#print(X[p,:].shape)

			U[p,:] = solve((VTV+lamI), (X[p,:].T.dot(Wu)).dot(V))

		return U

	def ALSV(self,U,V,X,lam):
		
		lamI = np.eye(self.latentFactors)*lam
		for p in range(V.shape[0]):
			Wi = np.diag(self.W[:,p])

			UTU = Wi.dot(U)
			UTU = U.T.dot(UTU)
		
			V[p,:] = solve(UTU+lamI,(X[:,p].T.dot(Wi)).dot(U))
		return V


	def calculate_loss(self):
		UTV = self.U.dot(self.V.T)
		XNM = np.multiply(self.ratingMatrix,self.W) - UTV
		#print(self.W)
		#print(XNM)

		total1 = np.sum(np.square(XNM))

		total2 = self.lambdaU * np.sum(np.square(self.U))
		total3 = self.lambdaV * np.sum(np.square(self.V))

		return np.sqrt(total1+total2+total3)


	def Train(self,iter = 33,converge=False):

		self.U = 5*np.random.random((self.u_len,self.latentFactors))
		self.V = 5*np.random.random((self.v_len,self.latentFactors))


		cur = 0

		while(cur<iter):
			#if self.pr==True and cur%5==4:
			#ss	print("------------->Iteration Number....",cur+1)
			
			self.U = self.ALSU(self.U, self.V, self.ratingMatrix, self.lambdaU)
			self.V = self.ALSV(self.U, self.V, self.ratingMatrix, self.lambdaV)

			
			loss = self.calculate_loss()
			print("Iteration ",cur,"-->",loss)

			cur+=1

		#print(self.U)
		#print(self.V)

	def Predict_one(self,u,v):
		return self.U[u,:].dot(self.V[v,:].T)

	def Predict(self):
		predictions = np.zeros((self.u_len,self.v_len))
		for u in range(self.u_len):
			for v in range(self.v_len):
				predictions[u,v] = self.Predict_one(u,v)
		return predictions























def main():
	np.random.seed(94743)


	col_names = ['UID','IID','RTN','TMS']
	ratings,sparsity = read_data(col_names)

	train,validation,test = train_validation_test_split(ratings)


	
	MF = Matrix_Factorization(train,latentFactors=50,printIntermediate=True,lambdaV=1,lambdaU=1)

	MF.Train()
	
	print(train)
	
	print(MF.Predict())



	print(calculate_rmse(MF.Predict(),train))




if __name__=="__main__":
	main()
