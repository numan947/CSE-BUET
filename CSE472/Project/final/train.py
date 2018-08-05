import keras

from keras.applications import resnet50
from keras.preprocessing.image import ImageDataGenerator
from keras.callbacks import CSVLogger, ModelCheckpoint, EarlyStopping
from keras.callbacks import ReduceLROnPlateau
from keras import backend as K
from keras.layers import Flatten,Dense,Dropout
from keras.models import Sequential
from keras import optimizers
from keras.models import model_from_json
import numpy as np
import os
import importlib, importlib.util, os.path
import zipfile
import sys

def make_dirs(path):
    if not os.path.exists(path):
        os.makedirs(path)


def TrainModel(train_data,resnet_conv,learning_rate,valid_data=None,dropout_rate=0.5,activation_function='softmax',optimizer='Adam',denselayer_size=1024,train_conv_layer=10,num_epochs=10):


    img_width, img_height = 224, 224
    num_channels = 3
    num_classes = 7
    # train_data = 'fer2013/Training1'
    # valid_data = 'fer2013/PublicTest1'
    # train_data ='drive/COLAB_NOTEBOOKS/sample/Training1'
    # valid_data = 'drive/COLAB_NOTEBOOKS/sample/PublicTest1'

    verbose = 1
    batch_size = 32
    #num_epochs =1 #10000
    patience = 3
    log_file_path = os.path.join(os.getcwd(),'logs','training.log')
    trained_models_path = os.path.join(os.getcwd(),'models','model')

    make_dirs(log_file_path)
    make_dirs(trained_models_path)

    for layer in resnet_conv.layers[:-train_conv_layer]:
        layer.trainable = False



    model = Sequential()
    model.add(resnet_conv)

    model.add(Flatten())


    model.add(Dense(denselayer_size, activation='relu'))
    model.add(Dropout(dropout_rate))
    model.add(Dense(denselayer_size, activation='relu'))
    model.add(Dropout(dropout_rate))

    model.add(Dense(int(denselayer_size/2), activation='relu'))
    model.add(Dropout(dropout_rate/2.0))
    model.add(Dense(int(denselayer_size/2), activation='relu'))
    model.add(Dropout(dropout_rate/4.0))
    
    model.add(Dense(7, activation=activation_function))


    opt = None
    if(optimizer=="Adam"):
        opt = optimizers.Adam(lr = learning_rate)
    elif(optimizer=="SGD"):
        opt = optimizers.SGD(lr = learning_rate)
    elif(optimizer == "RMSprop"):
        opt = optimizers.RMSprop(lr = learning_rate)




    model.compile(optimizer=opt, loss='categorical_crossentropy', metrics=['accuracy'])


    print(model.summary())



    print("Resnet Model Weights loaded")

    # prepare data augmentation configuration
    train_data_gen = ImageDataGenerator(rescale=1.0/255,
                                        featurewise_center=False,
                                        featurewise_std_normalization=False,
                                        rotation_range=10,
                                        width_shift_range=0.1,
                                        height_shift_range=0.1,
                                        zoom_range=0.1,
                                        horizontal_flip=True)
    
    if(valid_data is not None):
        valid_data_gen = ImageDataGenerator(rescale=1.0/255)
        valid_generator = valid_data_gen.flow_from_directory(valid_data, (img_width, img_height), batch_size=batch_size,class_mode='categorical')


    # callbacks
    tensor_board = keras.callbacks.TensorBoard(log_dir=os.path.join("logs"), histogram_freq=0, write_graph=True, write_images=True)
    
    csv_logger = CSVLogger(log_file_path, append=False)
    early_stop = EarlyStopping( patience=patience)
    reduce_lr = ReduceLROnPlateau( factor=0.1, patience=int(patience / 4), verbose=1)
    
    # model_names = str(trained_models_path) +'_'+str(activation_function)+'_'+str(learning_rate)+'_'+str(optimizer)+'_'+str(dropout_rate)+'_'+str(denselayer_size)+'_'+str(train_conv_layer)+'.{epoch:02d}-{val_acc:.2f}.hdf5'
    # model_checkpoint = ModelCheckpoint(model_names, monitor='val_acc', verbose=1, save_best_only=True)
    
    callbacks = [tensor_board ,csv_logger, early_stop, reduce_lr]
    #callbacks.append(model_checkpoint)
    
    # generators
    train_generator = train_data_gen.flow_from_directory(train_data, (img_width, img_height), batch_size=batch_size,
                                                         class_mode='categorical')


    print("Starting Fine Tuning the Model")

    #fine tune the model
    if(valid_data is not None):
        model.fit_generator(
          train_generator,
          steps_per_epoch=train_generator.samples/train_generator.batch_size ,
          epochs=num_epochs,
          validation_data=valid_generator,
          validation_steps=valid_generator.samples/valid_generator.batch_size,
          verbose=1,
          callbacks=callbacks)
    else:
        model.fit_generator(
          train_generator,
          steps_per_epoch=train_generator.samples/train_generator.batch_size ,
          epochs=num_epochs,
          verbose=1,
          callbacks=callbacks)

    return model


if __name__ == '__main__':
    
    img_width, img_height = 224, 224
    num_channels = 3
    num_classes = 7

    train_data = sys.argv[1]
    hyper_params = sys.argv[2]
    
    learning_rate = -1
    train_conv = -1

    with open(hyper_params) as f:
        hyp = f.readline()
        hh = hyp.split(" ")
        learning_rate = np.float(hh[0])
        train_conv = np.int(hh[1])

    print(train_conv,learning_rate)

    print(os.path.dirname(train_data))

    zip_ref = zipfile.ZipFile(train_data,'r')
    zip_ref.extractall(os.path.join(os.path.dirname(train_data),"MAIN_DATA"))
    zip_ref.close()
    train_data = os.path.join(os.path.dirname(train_data),"MAIN_DATA")

    epoch=3
    if 'Under_90' in train_data:
        epoch = 10
    if 'Under_10' in train_data:
        epoch = 5
    


    resnet_conv = resnet50.ResNet50(include_top=False, weights='imagenet',input_shape=(img_height,img_width, num_channels))

    model = TrainModel(train_data=train_data, resnet_conv=resnet_conv, learning_rate=learning_rate, valid_data=None, train_conv_layer=train_conv, num_epochs=epoch)

    print("Training........Done!")
    model_json = model.to_json()
    with open(os.path.join("model.json"), "w") as json_file:
        json_file.write(model_json)
    # serialize weights to HDF5
    model.save_weights(os.path.join("model.h5"))
    print("Model saved.")