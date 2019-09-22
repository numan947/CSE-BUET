import keras
from keras.applications import vgg16

from keras.preprocessing.image import ImageDataGenerator

from keras.models import Sequential
from keras.callbacks import CSVLogger, ModelCheckpoint, EarlyStopping
from keras.callbacks import ReduceLROnPlateau
from keras import layers
from keras import optimizers

import numpy as np

vgg_conv = vgg16.VGG16(weights = 'imagenet',include_top = False, input_shape=(224,224,3))

train_dir = './fer2013/Training'
validation_dir = './fer2013/PublicTest'

nTrain = 28709
nValid = 3589

datagen = ImageDataGenerator(rescale = 1.0/255)
batch_size = 32
patience = 50
nEpoch = 100


train_features = np.zeros(shape=(nTrain,7,7,512))
train_labels = np.zeros(shape=(nTrain,7))

train_generator = datagen.flow_from_directory(train_dir, target_size=(224,224),batch_size=batch_size,class_mode = 'categorical',shuffle=False)


i = 0

for inputs_batch, labels_batch in train_generator:
	features_batch = vgg_conv.predict(inputs_batch,verbose=1)
	train_features[i*batch_size:(i+1)*batch_size] = features_batch
	train_labels[i*batch_size:(i+1)*batch_size] = labels_batch
	i+=1
	if i*batch_size >=nTrain:
		break

train_features = np.reshape(train_features,(nTrain,7*7*512))



validation_features = np.zeros(shape=(nValid,7,7,512))
validation_labels = np.zeros(shape=(nValid,7))

validation_generator = datagen.flow_from_directory(validation_dir, target_size=(224,224),batch_size=batch_size,class_mode = 'categorical',shuffle=False)


i = 0

for inputs_batch, labels_batch in validation_generator:
	features_batch = vgg_conv.predict(inputs_batch,verbose=1)
	validation_features[i*batch_size:(i+1)*batch_size] = features_batch
	validation_labels[i*batch_size:(i+1)*batch_size] = labels_batch
	i+=1
	if i*batch_size >=nValid:
		break

validation_features = np.reshape(validation_features,(nValid,7*7*512))




model = Sequential()

model.add(layers.Dense(512,activation='relu',input_dim = 7*7*512))
model.add(layers.Dropout(0.5))
model.add(layers.Dense(256,activation='relu',input_dim = 7*7*512))
model.add(layers.Dropout(0.5))
model.add(layers.Dense(256,activation='relu',input_dim = 7*7*512))
model.add(layers.Dropout(0.25))
model.add(layers.Dense(7,activation='softmax'))



# callbacks
tensor_board = keras.callbacks.TensorBoard(log_dir='./logs', histogram_freq=0, write_graph=True, write_images=True)
log_file_path = './logs/training.log'
csv_logger = CSVLogger(log_file_path, append=False)
early_stop = EarlyStopping('val_acc', patience=patience)
reduce_lr = ReduceLROnPlateau('val_acc', factor=0.1, patience=int(patience / 4), verbose=1)
trained_models_path = 'models/model'
model_names = trained_models_path + '.{epoch:02d}-{val_acc:.2f}.hdf5'
model_checkpoint = ModelCheckpoint(model_names, monitor='val_acc', verbose=1, save_best_only=True)
callbacks = [tensor_board, model_checkpoint, csv_logger, early_stop, reduce_lr]




model.compile(optimizer = optimizers.RMSprop(lr=2e-4),loss = 'categorical_crossentropy',metrics=['acc'])

history = model.fit(train_features,train_labels,epochs=nEpoch,batch_size=batch_size,validation_data=(validation_features,validation_labels),verbose=1,callbacks=callbacks)

fnames = validation_generator.filenames

ground_truth = validation_generator.classes

label2index = validation_generator.class_indices

idx2label = dict((v,k) for k,v in label2index.items())

predictions = model.predict_classes(validation_features)

prob = model.predict(validation_features)

errors = np.where(predictions!=ground_truth)[0]

print("No of errors = {}/{}".format(len(errors),nValid))

