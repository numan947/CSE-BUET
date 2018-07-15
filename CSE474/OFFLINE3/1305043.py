import numpy as np





EPS = 0.000000025






def eta(sigma_sq):
	return np.random.normal(scale = np.sqrt(sigma_sq))

def calculate_xk(Is,Ws,sigma_sq):
	Is = list(Is)
	Is = [int(x) for x in Is]
	Is = np.array(Is)

	return np.sum(np.multiply(Is,Ws)) + eta(sigma_sq)



def build_priors(trainBits,n,w,sigma_sq):

	priors = np.zeros(2**n)
	states = []
	xks = [[] for x in range(2**n)]
	#print(xks)
	for i in range(len(trainBits)-n+1):
		state = int(trainBits[i:i+n],2)
		xk = calculate_xk(trainBits[i:i+n], w, sigma_sq)
		xks[state].append(xk)
		priors[state]+=1
		states.append(state)
	
	# for x in range(2**n):
	# 	print(xks[x])
	
	priors/=np.sum(priors)

	priors+=EPS

	means = [np.mean(xks[p]) for p in range(len(xks))]
	
	#print(means)

	return priors,states,means


def build_transitions(stateSeq,n):
	transitions = np.zeros((2**n,2**n))

	for i in range(len(stateSeq)-1):
		transitions[stateSeq[i],stateSeq[i+1]]+=1

	#print(transitions)

	#print(np.sum(transitions,axis=1)) 
	transitions /= np.sum(transitions,axis=1).reshape((2**n,1))

	transitions+=EPS

	#print(transitions)

	return transitions


def findXks():
	pass




def main():
	np.random.seed(947)
	
	config = open("config.txt").read().splitlines()
	
	tmp = config[0].split(' ')

	n = int(tmp[0])
	l = int(tmp[1])

	tmp = config[1].split(' ')
	tmp = [np.float(x) for x in tmp]
	
	w = np.array(tmp)
	w = w[::-1]

	tmp = np.float(config[2])

	sigma_sq = tmp


	train = open("train.txt").read().splitlines()[0]
	#zero padding
	for i in range(n-1):
		train = '0'+train

	#train = list(train)
	#train = [int(x) for x in train]
	#train = np.array(train)

	test = open("test.txt").read().splitlines()[0]

	for i in range(n-1):
		test = '0'+test



	priors,stateSeq,means = build_priors(train,n,w,sigma_sq)

	print(stateSeq)
	print(means)

	transitions = build_transitions(stateSeq,n)
	print(priors)

	# print(xk(train[0:n],w,sigma_sq))





	#print(eta(sigma_sq))



if __name__ == '__main__':
	main()
