import keras

from keras.applications import resnet50
from keras.preprocessing.image import ImageDataGenerator
from keras.callbacks import CSVLogger, ModelCheckpoint, EarlyStopping
from keras.callbacks import ReduceLROnPlateau
from keras import backend as K
from keras.layers import Flatten,Dense,Dropout
from keras.models import Sequential
from keras.optimizers import SGD
from keras.models import model_from_json
import numpy as np
import os

def loadModel(path):
	# load json and create model
	json_file = open(path+'model.json', 'r')
	loaded_model_json = json_file.read()
	json_file.close()
	loaded_model = model_from_json(loaded_model_json)
	# load weights into new model
	loaded_model.load_weights(path+"model.h5")
	print("Loaded model from disk")
	 
	# evaluate loaded model on test data
	loaded_model.compile(loss='binary_crossentropy', optimizer='rmsprop', metrics=['accuracy'])

	return loaded_model

image_size = 224
batch_size=32
trained_models_path = 'models/model'
test_dir = './fer2013/PrivateTest2'


loaded_model = loadModel(trained_models_path)

test_datagen = ImageDataGenerator(rescale=1./255)

# Create a generator for prediction
test_generator = test_datagen.flow_from_directory(
        test_dir,
        target_size=(image_size, image_size),
        batch_size=batch_size,
        class_mode='categorical',
        shuffle=False)
 
fnames = test_generator.filenames
ground_truth = test_generator.classes

label2index = test_generator.class_indices
 
idx2label = dict((v,k) for k,v in label2index.items())

predictions = loaded_model.predict_generator(test_generator, steps=test_generator.samples/test_generator.batch_size,verbose=1)
predicted_classes = np.argmax(predictions,axis=1)
 
errors = np.where(predicted_classes != ground_truth)[0]
print("No of errors = {}/{}".format(len(errors),test_generator.samples))
