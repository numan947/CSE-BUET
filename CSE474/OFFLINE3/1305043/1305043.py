import numpy as np
import scipy.stats
import operator



EPS = 0.000000025






def eta(sigma_sq):
	return np.random.normal(scale = np.sqrt(sigma_sq))

def calculate_xk(Is,Ws,sigma_sq):
	Is = list(Is)
	Is = [int(x) for x in Is]
	Is = np.array(Is)

	return np.sum(np.multiply(Is,Ws)) + eta(sigma_sq)

def getPdf(mean,variance,xk):
	return scipy.stats.norm(mean,np.sqrt(variance)).pdf(xk)


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

	#print(priors)

	priors+=EPS

	priors/=np.sum(priors)

	#print(priors)

	means = [np.mean(xks[p]) for p in range(len(xks))]
	
	#print(means)

	return np.array(priors),states,means


def build_transitions(stateSeq,n):
	transitions = np.zeros((2**n,2**n))

	for i in range(len(stateSeq)-1):
		transitions[stateSeq[i],stateSeq[i+1]]+=1

	#print(transitions)

	#print(np.sum(transitions,axis=1)) 
	transitions /= np.sum(transitions,axis=1).reshape((2**n,1))

	transitions+=EPS

	transitions /= np.sum(transitions,axis=1).reshape((2**n,1))
	#print(transitions)

	return np.array(transitions)


def build_observation_probabilities(testBits,means,sigma_sq,n,w):

	obs = []
	obs_states=[]
	for i in range(len(testBits)-n+1):
		tmp = []
		xk = calculate_xk(testBits[i:i+n], w, sigma_sq)

		obs_states.append(int(testBits[i:i+n],2))

		for mean in means:
			tmp.append(getPdf(mean, sigma_sq, xk))

		obs.append(tmp)

	return np.array(obs),obs_states



def viterbi(transition_probs,prior_probs,emission_probs):
	#print(emission_probs[0])
	#print(emission_probs.shape)
	prob_table = np.zeros((emission_probs.shape))
	max_paths = np.zeros((emission_probs.shape))



	prob_table[0,:] = prior_probs * emission_probs[0,:]
	prob_table[0,:] = prob_table[0,:]/np.sum(prob_table[0,:])


	


	for samp in range(1,emission_probs.shape[0]):
		for state in range(emission_probs.shape[1]):
			trans_prob = prob_table[samp-1,:]*transition_probs[state,:]

			max_idx,max_val = trans_prob.argmax(),max(trans_prob)

			max_paths[samp,state] = max_idx
			prob_table[samp,state] = max_val*emission_probs[samp,state]

		prob_table[samp,:] = prob_table[samp,:]/np.sum(prob_table[samp,:])

	#print(prob_table[emission_probs.shape[0]-1,:].argmax())

	#print(max_paths)

	best_path = np.zeros(emission_probs.shape[0])

	best_path[emission_probs.shape[0]-1] = prob_table[emission_probs.shape[0]-1,:].argmax()

	for samp in range(emission_probs.shape[0]-1,0,-1):
		best_path[samp-1] = max_paths[int(samp),int(best_path[samp])]

	return best_path



def calculate_accuracy(actual,estimation):
	#print(len(actual),len(estimation))

	er = 0
	ok = 0

	print("Actual String       : ",actual)
	print("Estimated String    : ",estimation)
	for i in range(len(actual)):
		if(actual[i]==estimation[i]):
			ok+=1
		else:
			er+=1

	ok*=100.0
	ok/=len(actual)

	er*=100.0
	er/=len(actual)

	return ok,er



def go(seed):
	np.random.seed(seed)
	
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


	print("Prior Probabilities:\n")
	print(priors)
	print("\n\n")

	

	#print(stateSeq)
	#print(means)

	transitions = build_transitions(stateSeq,n)
	print("Transition Probabilities:\n")
	print(transitions)
	print("\n\n")

	print("Observation Means:\n")
	print(means)
	print("\n\n")
	#print(priors)
	#print(transitions)

	obs_probs,obs_states = build_observation_probabilities(test,means,sigma_sq,n,w)

	# print("HELLO")
	# for obs in obs_probs:
	# 	print(obs)
	#print(obs_states)


	best_path = viterbi(transitions, priors, obs_probs)


	best_estimation=""

	for p in best_path:
		temp = "{0:b}".format(int(p))
		#print(temp,n-1)
		best_estimation+=temp[len(temp)-1]

	#print(best_estimation)

	print("Metrics:\n")

	accuracy,error=calculate_accuracy(test[n-1:],best_estimation)


	print("Accuray: ",accuracy)

	



def main():
	# print(xk(train[0:n],w,sigma_sq))

	go(502)


	#print(eta(sigma_sq))



if __name__ == '__main__':
	main()
