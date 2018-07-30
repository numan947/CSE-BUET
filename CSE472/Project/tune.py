import numpy as np
import train
from keras.preprocessing.image import ImageDataGenerator
from keras.models import model_from_json


optimizers = ['SGD', 'RMSprop', 'Adam']
learn_rate = [0.001, 0.01, 0.1]
activation_function = ['softmax', 'softplus', 'softsign']
dropout_rate = [0.25,0.50,0.75]
train_conv_layer = [5,10,15]
denselayer_size = [512,1024,2048]




log_file_path = './logs'
valid_data = 'fer2013/PublicTest1'
best_models_path = 'models/best_models'
img_width, img_height = 224, 224
num_channels = 3
num_classes = 7
batch_size = 32
patience = 50



def saveModel(model,path,config):
    # serialize model to JSON
    model_json = model.to_json()
    with open(path+"/"+config+"_"+"best_model.json", "w") as json_file:
        json_file.write(model_json)
    # serialize weights to HDF5
    model.save_weights(path+"best_model.h5")
    print(config,file = open(log_file_path+"/Tune.log","a"))
    print("Saved model to disk-->",path+"best_model.h5")





def train_and_tune():
    
	valid_data_gen = ImageDataGenerator(rescale=1.0/255)
	valid_generator = valid_data_gen.flow_from_directory(valid_data, (img_width, img_height), batch_size=batch_size,class_mode='categorical')
	fnames = valid_generator.filenames
	ground_truth = valid_generator.classes
	label2index = valid_generator.class_indices
	idx2label = dict((v,k) for k,v in label2index.items())

	cur_best = None
	cur_error = np.inf

	for lr in learn_rate:
		for dr in dropout_rate:
			for conv in train_conv_layer:
					print("Training Model With Hyper Paramters: ",file = open(log_file_path+"/Tune.log","a"))
					model = train.TrainModel(learning_rate=lr,dropout_rate=dr,train_conv_layer=conv,resnetModel = "resnet152")
					
					predictions = loaded_model.predict_generator(test_generator, steps=test_generator.samples/test_generator.batch_size,verbose=1)
					predicted_classes = np.argmax(predictions,axis=1)

					errors = np.where(predicted_classes != ground_truth)[0]
					print("No of errors = {}/{}".format(len(errors),test_generator.samples),file = open(log_file_path+"/Tune.log","a"))

					if(erros<cur_error):
						cur_best = model
						cur_error = errors
						saveModel(model,best_models_path,trained_models_path,str(lr)+'_'+str(dr)+'_'+str(conv))



if __name__ == '__main__':
	train_and_tune()