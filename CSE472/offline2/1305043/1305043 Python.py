
# coding: utf-8

# In[1550]:


import numpy as np
import pandas as pd
import random
import matplotlib.pyplot as plt
from scipy.stats import norm
from sklearn.datasets import make_spd_matrix
import sys
import operator
from scipy.stats import multivariate_normal


# In[1551]:


np.random.seed(43)


# In[1552]:


def generate_data(n_feat,n_clust,mu_list,cov_list,n_sample_per_clust):
    
    features=[]
    for x in range(n_feat):
        features.append([])
        
    for mu, cov in zip(mu_list,cov_list):
        TT=np.random.multivariate_normal(mu,cov,n_sample_per_clust).T
        for i in range(n_feat):
            features[i].append(TT[i])
    for i in range(len(features)):
        features[i]=np.concatenate(features[i])   
    labels=[]
    for i in range(1,n_clust+1):
        labels+=[i]*n_sample_per_clust
    
    data = {'label':labels}
    
    for i in range(len(features)):
        data['feat_'+str(i)]=features[i]
    
    df=pd.DataFrame(data=data)
    return df


# In[1553]:


def plot_data_scatter(feat1,feat2,sz,label,data):
    plt.scatter(x=data[feat1],y=data[feat2],s=sz,c=data[label])


# In[1554]:


class Cluster:
    def __init__(self,mu,cov):
        assert(len(mu)*len(mu)==len(cov)*len(cov[0]))
        self.mu=mu
        self.cov=cov


# In[1026]:


def likelihood(x,mu,cov):
    mm=np.asmatrix(cov)
    nn=np.asmatrix(mu)
    xx=np.asmatrix(x)
    
    
    
    
    e_param=-0.5*(x-nn)*np.linalg.pinv(mm)*(x-nn).T
    
    #print("e_params ",e_param)
    #print("cov-det * 2pi ",2*np.pi*np.linalg.det(cov))
    
    #print("sqrt",np.sqrt(np.abs(2*np.pi*np.linalg.det(cov))))
    print("e_params ",e_param," exp ",np.exp(e_param))
    
    if(np.exp(e_param)==np.inf):
        print(mm)
        print(nn)
        print(xx)
        
    
    lob=np.exp(e_param)
    hor=np.sqrt(((2*np.pi)**len(x))*np.abs(np.linalg.det(cov)))
    return np.linalg.det(lob/hor)


# In[1555]:


def calculate_prob(x,mu,cov,w):
    prob=w
    prob*=multivariate_normal.pdf(x=x,cov=cov,mean=mu)
    return prob


# In[1556]:


def normalize(probs):
    #print("sum ",sum(probs))
    return [p/sum(probs) for p in probs]


# In[1571]:


def getMatrix(size):
    from scipy import random
    A= random.rand(size,size)
    B=np.dot(A,A.transpose())
    return B


# In[1572]:


def initparams(n_clust,n_feat):
    params={}
    for i in range(n_clust):
        params['mu'+str(i+1)]=list(np.random.uniform(size=n_feat,low=0.001,high=1.0))
        params['cov'+str(i+1)]=list(getMatrix(n_feat))
    
    ws=[]
    for i in range(n_clust):
        ws.append(1/n_clust)
    params['weights']=ws
    return params


# In[1573]:


#todo incorporate overall loglikelihood here
def calculate_change(old,new):
    mus=[t for t in list(old.columns) if "mu" in t]
    covs=[t for t in list(old.columns) if "cov" in t]
    
    d=0.0
    
    for mu in mus:
        for i in range(len(old)):
            d+=(old[mu][i]- new[mu][i])**2
    
    return d**0.5


# In[1614]:


def expectation(df,params,n_clust):
    print("EXPECTATION")
    cur=0
    for row in df.itertuples(index=False, name='Pandas'):
        x=list(np.asarray(row))
        
        for i in range(n_clust+1):
            del x[-1]
        
        clust_probs=[]
        for i in range(n_clust):
            pp=calculate_prob(x,list(params["mu"+str(i+1)]),list(params["cov"+str(i+1)]),params['weights'][i])
            df["w"+str(i+1)][cur]=pp
            clust_probs.append(pp)
        clust_probs=normalize(clust_probs)
        index, value = max(enumerate(clust_probs), key=operator.itemgetter(1))
        df['label'][cur]=index+1
        cur+=1
    
    return df


# In[1618]:


def maximize(df,params,n_clust):
    total=len(df)
    
    
    
    
    for i in range(n_clust):
        assigned_i = df[df.label==(i+1)]
        percent_i=len(assigned_i)/float(total)
        params['weights'][i]=percent_i
        #print(list(assigned_i.mean()))
        
        update_mu=list(assigned_i.mean())
        del update_mu[-1]
        
        px=0
        ps=0
        for j in range(df.shape[0]):
#             px+=df['w'+str(i)][j] *x 
#             ps+=df['w'+str(i)][j]
            pass
        
        
        
        
        params['mu'+str(i+1)]=update_mu
        
        
        
        
        
        break
        
        
        
        #params["mu"+str(i+1)]=
    


# In[1616]:


def EM(df,n_clust,n_feat):
    params=initparams(n_clust,n_feat)
    #print(params)
    params=pd.DataFrame(params)
    
    print(params)
    
    
    df_=df.copy(deep=True)
    
    #random labeling
    df_['label']=np.random.randint(1, n_clust+1, df.shape[0])
    
    for  i in range(1,n_clust+1):
        df_['w'+str(i)]=(1/n_clust)
    
    #print(df_)
    
    dist=sys.maxsize
    eps=0.01
    n_iter=0
    #print(calculate_change(params,params))
    
    while( dist > eps):
        n_iter+=1
        
        new_lab=expectation(df_.copy(deep=True),params,n_clust)
        
        
        print(new_lab)
        
        new_params=maximize(new_lab,params.copy(deep=True),n_clust)
        
        break
    
    


# In[1613]:


EM(df,2,2)


# In[ ]:


guess = { 'mu1': [1,1],
          'sig1': [ [1, 0], [0, 1] ],
          'mu2': [4,4],
          'sig2': [ [1, 0], [0, 1] ],
          'lambda': [0.4, 0.6]
        }
guess=pd.DataFrame(guess)


# In[1480]:


guess


# In[1481]:


mu1 = [0, 5]
sig1 = [ [2, 0], [0, 3] ]

mu2 = [5, 0]
sig2 = [ [4, 0], [0, 1] ]


df=generate_data(2,2,[mu1,mu2],[sig1,sig2],30)
df.head()

df_t=df.drop(columns=["label"])
plot_data_scatter("feat_0","feat_1",20,"label",df)
plt.show()



c1=Cluster(mu=mu1,cov=sig1)
c2=Cluster(mu=mu2,cov=sig2)


# In[1482]:


for row in df_t.itertuples(index=False, name='Pandas'):
    x=np.asarray(row)
    break


# In[490]:


x

