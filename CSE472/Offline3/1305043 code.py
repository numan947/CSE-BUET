import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from numpy.linalg import solve
from sklearn.metrics import mean_squared_error
import matplotlib.pyplot as plt
from collections import defaultdict
import gzip


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
	MAXITEM = 10
	MAXUSER = 10
	RATE_LOW = 0
	RATE_HIGH = 5

	ratings = np.random.randint(RATE_LOW,RATE_HIGH,(MAXUSER, MAXITEM))
	print(ratings)
	sparsity = 100.0*float(np.count_nonzero(ratings)/(ratings.shape[0]*ratings.shape[1]))



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
	return train,validation,test

def calculate_rmse(pred,actual):
	pred=pred[actual.nonzero()].flatten()
	actual=actual[actual.nonzero()].flatten()
	return np.sqrt(mean_squared_error(pred,actual))



class Matrix_Factorization():

	def __init__(self,ratingMatrix,latentFactors=5,lambdaU=0,lambdaV=0,printIntermediate=False):
		self.u_len,self.v_len = ratingMatrix.shape
		self.ratingMatrix = ratingMatrix
		self.latentFactors = latentFactors
		self.lambdaU = lambdaU
		self.lambdaV = lambdaV
		self.pr = printIntermediate


	def ALSU(self,U,V,X,lam):
		VTV = V.T.dot(V)
		lamI = np.eye(VTV.shape[0])*lam

		#print(X[0,:].shape)

		#print(V.shape)

		for p in range(U.shape[0]):
			pass
			U[p,:] = solve((VTV+lamI), X[p,:].T.dot(V))
		return U

	def ALSV(self,U,V,X,lam):
		UTU = U.T.dot(U)
		lamI = np.eye(UTU.shape[0])*lam
		for p in range(V.shape[0]):
			V[p,:] = solve(UTU+lamI, X[:,p].T.dot(U))
		return V

	def Train(self,iter = 20):

		self.U = np.random.random((self.u_len,self.latentFactors))
		self.V = np.random.random((self.v_len,self.latentFactors))


		cur = 0

		while(cur<iter):
			if self.pr==True and cur%5==4:
				print("------------->Iteration Number....",cur+1)
			
			self.U = self.ALSU(self.U, self.V, self.ratingMatrix, self.lambdaU)
			self.V = self.ALSV(self.U, self.V, self.ratingMatrix, self.lambdaV)

			cur+=1


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


	print(train)

	MF = Matrix_Factorization(train,latentFactors=7,printIntermediate=True)

	MF.Train()

	print(MF.Predict())


	print(calculate_rmse(MF.Predict(),train))




if __name__=="__main__":
	main()
