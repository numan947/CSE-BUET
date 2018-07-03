import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from numpy.linalg import solve
from sklearn.metrics import mean_squared_error
import matplotlib.pyplot as plt
from collections import defaultdict
import gzip
from collections import Counter

RATE_LOW = 0
RATE_HIGH = 5

MAXITEM = 10
MAXUSER = 1000



TOTAL_INPUT = 500
ITER_DEFAULT = 20
np.set_printoptions(threshold=np.nan)


def readGz(f):
  for l in gzip.open(f):
    yield eval(l)

def read_GZIP(MXRATINGS):
	cnt=0
	
	allRatings = []
	all_users = []
	all_items = []


	userRatings = defaultdict(list)
	for l in readGz("assignment2/train.json.gz"):
		
		user,item = l['reviewerID'],l['itemID']
		
		
		allRatings.append(l['rating'])
		all_items.append(item)
		all_users.append(user)

		userRatings[user].append(l['rating'])
		
		cnt+=1
		
		#print(user,item)
		
		if(cnt>=MXRATINGS):
			break


	mat = np.zeros((len(Counter(all_users).keys()),len(Counter(all_items).keys())))

	d_u = dict([(y,x) for x,y in enumerate(sorted(set(all_users)))])
	d_i = dict([(y,x) for x,y in enumerate(sorted(set(all_items)))])

	for x,y,r in zip(all_users, all_items, allRatings):
		mat[d_u[x],d_i[y]] = r


	#print(mat)

	return mat






def make_dummy():
	print("\nREADING DATA.................................\n")
	
	ratings = np.random.uniform(low=RATE_LOW,high=RATE_HIGH,size=(MAXUSER, MAXITEM))
	#print(ratings)
	wRat = make_weight_matrix(ratings)
	sparsity = 100.0*float(np.count_nonzero(wRat)/(wRat.shape[0]*wRat.shape[1]))

	#print(ratings.shape,wRat.shape)

	print("sparsity:",sparsity)
	print("\nDATA READING COMPLETED.......................\n")
	return ratings,sparsity


def read_data(dummy=False):
	
	if(dummy):
		return make_dummy()

	print("\nREADING DATA.................................\n")
	ratings = read_GZIP(TOTAL_INPUT)

	print(ratings.shape)
	
	wRat = make_weight_matrix(ratings)
	
	sparsity = 100.0*float(np.count_nonzero(wRat)/(wRat.shape[0]*wRat.shape[1]))


	print("sparsity:",sparsity)
	print("\nDATA READING COMPLETED.......................\n")
	return ratings,sparsity



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

	def __init__(self,ratingMatrix,latentFactors=5,lambdaU=0,lambdaV=0,scl=5,debug=False):
		self.u_len,self.v_len = ratingMatrix.shape
		self.ratingMatrix = ratingMatrix
		self.latentFactors = latentFactors
		self.lambdaU = lambdaU
		self.lambdaV = lambdaV
		self.debug = debug
		self.W = make_weight_matrix(ratingMatrix)
		self.scl = 5


	def ALSU(self,U,V,X,lam):
		if(self.debug):
			print(self.W)
		

		lamI = np.eye(self.latentFactors)*lam

		if(self.debug):
			print(X[0,:].shape)
			print(V.shape)

		for p in range(U.shape[0]):
			Wu = np.diag(self.W[p,:])

			if(self.debug):
				print("Wu ",Wu.shape)
				print(Wu)
			
			VTV = Wu.dot(V)
			

			if(self.debug):
				print("VTV1 shape ",VTV.shape)
			



			VTV = V.T.dot(VTV)
			

			if(self.debug):
				print("VTV2 shape ",VTV.shape)
				print(X[p,:].shape)


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
		
		if(self.debug):
			print(self.W)
			print(XNM)

		total1 = np.sum(np.square(XNM))

		total2 = self.lambdaU * np.sum(np.square(self.U))
		total3 = self.lambdaV * np.sum(np.square(self.V))

		return np.sqrt(total1+total2+total3)


	def Train(self,iter = ITER_DEFAULT,converge=False):

		self.U = self.scl*np.random.random((self.u_len,self.latentFactors))
		self.V = self.scl*np.random.random((self.v_len,self.latentFactors))


		cur = 0

		while(cur<iter):

			self.U = self.ALSU(self.U, self.V, self.ratingMatrix, self.lambdaU)
			self.V = self.ALSV(self.U, self.V, self.ratingMatrix, self.lambdaV)

			
			
			
			if(self.debug==True):
				loss = self.calculate_loss()
				print("Iteration ",cur,"-->",loss)
		

			cur+=1

		if(self.debug):
			print(self.U)
			print(self.V)


	def Train_Predict(self):
		predictions = np.zeros((self.u_len,self.v_len))
		for u in range(self.u_len):
			for v in range(self.v_len):
				predictions[u,v] = self.U[u,:].dot(self.V[v,:].T)
		return predictions


	def Test_Predict(self,testSet,iter=ITER_DEFAULT):
		n_u,n_i = testSet.shape
		UU = self.scl*np.random.random((n_u,self.latentFactors))

		cur = 0

		UU = self.ALSU(UU, self.V, testSet, self.lambdaU)
		if(self.debug):
			print(UU)

		predictions = np.zeros((n_u,n_i))

		for u in range(n_u):
			for v in range(n_i):
				predictions[u,v] = UU[u,:].dot(self.V[v,:].T)

		return predictions
















def regularized_hyperparameter_search(trainSet,validationSet,regularizationList=None,latentFactorList=None,iter_array=None,debug=False):
	
	lf = [5,10,15,20,25,30,35,40,45,50]
	
	rg = [ 0.01, 0.1, 1.0,10.0]
	
	#it = [10,20,30,40,50]


	if(regularizationList is not None):
		rg = regularizationList
	if(latentFactorList is not None):
		lf = latentFactorList
	if(iter_array is not None):
		it = iter_array

	rg.sort()


	best_params = {}
	best_params['latentFactors'] = lf[0]
	best_params['lambdaU'] = rg[0]
	best_params['lambdaV'] = rg[0]

	best_params['train_rmse']=np.inf
	
	best_params['valid_rmse']=np.inf
	
	best_params['model']=None



	for f in lf:
		
		
		
		for ru in rg:
			for ri in rg:

				print("Latent Factor: {}".format(f))
				print("Regularization Parameter: lambdaU->{} lambdaV->{}".format(ru,ri))

				model = Matrix_Factorization(trainSet,latentFactors = f,lambdaU = ru, lambdaV = ri,debug=debug)
				model.Train()

				valid_rmse = calculate_rmse(model.Test_Predict(validationSet),validationSet)
				train_rmse = calculate_rmse(model.Train_Predict(), trainSet)

				print("validationSet RMSE--> ",valid_rmse)
				print("trainSet RMSE--> ",train_rmse)

				if(valid_rmse<best_params['valid_rmse']):
					best_params['latentFactors'] = f
					best_params['lambdaU'] = ru
					best_params['lambdaV'] = ri
					best_params['train_rmse'] = train_rmse
					best_params['valid_rmse'] = valid_rmse
					best_params['model'] = model

					print("FOUND NEW HYPER PARAMS")
					with pd.option_context('display.max_rows', None, 'display.max_columns', 5):
						print(pd.Series(best_params))
				elif (valid_rmse == best_params['valid_rmse'] and train_rmse<best_params["train_rmse"]):
					best_params['latentFactors'] = f
					best_params['lambdaU'] = ru
					best_params['lambdaV'] = ri
					best_params['train_rmse'] = train_rmse
					best_params['valid_rmse'] = valid_rmse
					best_params['model'] = model

					print("FOUND NEW HYPER PARAMS")
					with pd.option_context('display.max_rows', None, 'display.max_columns', 5):
						print(pd.Series(best_params))


	return best_params,best_params['model']









def main():
	
	np.random.seed(947)



	ratings,sparsity = read_data(dummy=True)

	train,validation,test = train_validation_test_split(ratings)

	config,model = regularized_hyperparameter_search(train, validation,debug=False)



	print("\n\n\n")
	print("TEST RMSE")
	print(calculate_rmse(model.Test_Predict(test),test))
	print("\n\n\n")
	print("BEST MODEL")
	print(pd.Series(config))




if __name__=="__main__":
	main()
