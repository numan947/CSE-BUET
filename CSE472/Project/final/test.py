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
import sys
import zipfile

def make_dirs(path):
	if not os.path.exists(path):
		os.makedirs(path)

def loadModel(mode_json,model_wgts):
	# load json and create model
	json_file = open(model_json)
	loaded_model_json = json_file.read()
	json_file.close()
	loaded_model = model_from_json(loaded_model_json)
	# load weights into new model
	loaded_model.load_weights(model_wgts)
	print("Loaded model from disk")
	 
	# evaluate loaded model on test data
	loaded_model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])

	return loaded_model

def test(test_data,model):
	image_size = 224
	batch_size=32

	test_datagen = ImageDataGenerator(rescale=1./255)

	# Create a generator for prediction
	test_generator = test_datagen.flow_from_directory(
	        test_data,
	        target_size=(image_size, image_size),
	        batch_size=batch_size,
	        class_mode='categorical',
	        shuffle=False)


	print("Generating Predictions.............")
	fnames = test_generator.filenames
	ground_truth = test_generator.classes

	predictions = model.predict_generator(test_generator, steps=test_generator.samples/test_generator.batch_size,verbose=1)
	predicted_classes = np.argmax(predictions,axis=1)
	 
	errors = np.where(predicted_classes != ground_truth)[0]
	print("No of errors = {}/{}".format(len(errors),test_generator.samples))






if __name__ == '__main__':
	test_data = sys.argv[1]
	model_data = sys.argv[2]

	zip_ref = zipfile.ZipFile(test_data,'r')
	zip_ref.extractall(os.path.join(os.path.dirname(test_data),"MAIN_DATA"))
	zip_ref.close()
	test_data = os.path.join(os.path.dirname(test_data),"MAIN_DATA")

	tmp = os.path.basename(model_data).split(".")

	model_json = tmp[0]+".json"
	model_wgts = tmp[0]+".h5"
	print(model_json)
	print(model_wgts)

	model = loadModel(model_json,model_wgts)

	#print(model.summary())

	test(test_data,model)