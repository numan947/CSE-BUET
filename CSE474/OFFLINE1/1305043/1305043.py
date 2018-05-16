
# coding: utf-8

# In[13]:


import pandas as pd
import numpy as np


# In[14]:


def vectorize_target(target):
    t_v = np.zeros((len(target),len(np.unique(target)))) #labels are 0,1,2.......
    #print(t_v.shape)
    for i in range(len(target)):
        #print(i,target[i])
        t_v[i,target[i]]=1
    return t_v


# In[15]:


def sigmoid(z):
    return 1/(1+np.exp(-z))


# In[16]:


def sigmoid_deriv(z):
    return sigmoid(z)*(1-sigmoid(z))


# In[17]:


def initialize_weights(nn_config): #number of features, hidden layers, output nodes
    weights={}
    bias={}
    for layer in range(1,len(nn_config)):
        weights[layer]=np.random.random((nn_config[layer],nn_config[layer-1]))
        bias[layer]=np.random.random((nn_config[layer],))
    
    return weights,bias


# In[18]:


def initialize_diffs(nn_config):
    dweights={}
    dbias={}
    for layer in range(1,len(nn_config)):
        dweights[layer]=np.zeros((nn_config[layer],nn_config[layer-1]))
        dbias[layer]=np.zeros((nn_config[layer],))
    return dweights,dbias


# In[19]:


def forward_pass(x,W,b):
    h={1:x} #setting up layer 1
    z={}
    for layer in range(1,len(W)+1):
        if(layer==1):
            inputs=x
        else:
            inputs=h[layer]
        z[layer+1]=W[layer].dot(inputs) + b[layer]
        h[layer+1]=sigmoid(z[layer+1])
    return h,z


# In[20]:


def outputlayer_error(y_actual,h_out,z_out):
    #y_actual=y_actual.reshape(len(y_actual),1)
    tmp=-(y_actual-h_out)*sigmoid_deriv(z_out)
   # print(tmp.shape)
    return tmp


# In[21]:


def hiddenlayer_error(next_layer_error,weights,z):
    tmp=np.dot(np.transpose(weights),next_layer_error) * sigmoid_deriv(z)
   # print(tmp.shape)
    return tmp


# In[22]:


def train_neural_net(nn_config,X,y,iters=1000,alpha=0.15):
    
    W,b=initialize_weights(nn_config)
    
    total_train=len(y)
    
    print('TOTAL ITERATIONS-->',iters)
    
    cur_iter=0
    
    while cur_iter<iters:
        if(cur_iter%50==0):
            print("ITERATION NUMBER ",cur_iter," IS RUNNING")
        
        dW,db=initialize_diffs(nn_config)
        
        for i in range(total_train):
            diffs={}
            
            h,z = forward_pass(X[i,:],W,b)
            
            for l in range(len(nn_config),0,-1):
                
                if(l==len(nn_config)):
                    diffs[l]=outputlayer_error(y[i,:],h[l],z[l])
                else:
                    if(l>1):
                        diffs[l]=hiddenlayer_error(diffs[l+1],W[l],z[l])
                    
                   #print(dW[l].shape)
                    #print(diffs[l+1].shape)
                   # print(h[l].shape)
                    
                    dW[l]+=np.dot(diffs[l+1][:,np.newaxis],np.transpose(h[l][:,np.newaxis]))
                    db[l]+=diffs[l+1]
                
            
            for l in range(len(nn_config)-1,0,-1):
                W[l]+= -alpha*(1.0/total_train * dW[l])
                b[l]+=-alpha*(1.0/total_train *db[l])
        cur_iter+=1
    return W,b


# In[23]:


def predict_neural_net(W,b,X,n_layers):
    m=X.shape[0] #number of predictions to make
    y=np.zeros((m))
    
    for i in range(m):
        h,z = forward_pass(X[i,:],W,b)
        y[i]=np.argmax(h[n_layers])
    return y


# In[24]:


from sklearn.preprocessing import StandardScaler
X_scale = StandardScaler()


# In[25]:


train_data=pd.read_csv('train.txt',delim_whitespace=True,header=None)


# In[26]:


train_data.head()


# In[70]:


X_train=train_data.as_matrix(columns=[0,1])
X_train=X_scale.fit_transform(X_train)


# In[71]:


y_train=train_data.as_matrix(columns=[2])


# In[72]:


for i in range(len(y_train)):
    y_train[i]-=1


# In[73]:


y_v_train=vectorize_target(y_train)


# In[74]:


y_v_train=vectorize_target(target=y_train)


# In[78]:


W,b = train_neural_net([X_train.shape[1],40,y_v_train.shape[1]],X_train,y_v_train,iters=200)


# In[79]:


y_pred=predict_neural_net(W=W,b=b,X=X_train,n_layers=3)


# In[80]:


from sklearn.metrics import accuracy_score
acc=accuracy_score(y_pred=y_pred,y_true=y_train)
print(acc)

print()
print(train_data.head())
