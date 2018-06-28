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

	ratings = np.zeros((MAXUSER, MAXITEM))

	for i in range(MAXUSER):
		for j in range(MAXITEM):
			ratings[i][j] = np.random.randint(RATE_LOW, RATE_HIGH)

	sparsity = 100.0*float(np.count_nonzero(ratings)/(ratings.shape[0]*ratings.shape[1]))

	print("sparsity:",sparsity)
	print(ratings)
	print("\nDATA READING COMPLETED.......................\n")
	return ratings,sparsity





def read_data(col_names):
	
	



	
	
	return make_dummy()






























def main():
	np.random.seed(94743)


	col_names = ['UID','IID','RTN','TMS']
	ratings,sparsity = read_data(col_names)



if __name__=="__main__":
	main()
