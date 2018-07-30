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

def module_from_file(module_name, file_path):
    spec = importlib.util.spec_from_file_location(module_name, file_path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module

def TrainModel(activation_function,learning_rate,optimizer,dropout_rate,denselayer_size,resnetModel='resnet50',train_conv_layer=10):


    img_width, img_height = 224, 224
    num_channels = 3
    num_classes = 7
    train_data = 'fer2013/Training1'

    num_train_samples =200 #28709
    verbose = 1
    batch_size = 32
    num_epochs =1 #10000
    patience = 50
    log_file_path = './logs/training.log'
    trained_models_path = 'models/model'



    if(resnetModel=='resnet50'):
        resnet_conv = resnet50.ResNet50(weights='imagenet', include_top=False, input_shape=(img_height,img_width, num_channels))

    else:
        resnet152 = module_from_file("resnet152_keras","resnet152_keras.py")
        resnet_conv = resnet152.ResNet152(include_top=False, weights='imagenet',input_shape=(img_height,img_width, num_channels))

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


    # callbacks
    tensor_board = keras.callbacks.TensorBoard(log_dir='./logs', histogram_freq=0, write_graph=True, write_images=True)
    
    csv_logger = CSVLogger(log_file_path, append=False)
    early_stop = EarlyStopping('val_acc', patience=patience)
    reduce_lr = ReduceLROnPlateau('val_acc', factor=0.1, patience=int(patience / 4), verbose=1)
    
    model_names = str(trained_models_path) +'_'+str(activation_function)+'_'+str(learning_rate)+'_'+str(optimizer)+'_'+str(dropout_rate)+'_'+str(denselayer_size)+'_'+str(resnetModel)+'_'+str(train_conv_layer)+'.{epoch:02d}-{val_acc:.2f}.hdf5'
    model_checkpoint = ModelCheckpoint(model_names, monitor='val_acc', verbose=1, save_best_only=True)
    callbacks = [tensor_board, model_checkpoint, csv_logger, early_stop, reduce_lr]

    # generators
    train_generator = train_data_gen.flow_from_directory(train_data, (img_width, img_height), batch_size=batch_size,
                                                         class_mode='categorical')


    print("Starting Tuning the Model")

    #fine tune the model
    model.fit_generator(train_generator,steps_per_epoch=num_train_samples / batch_size,validation_split=0.2, epochs=num_epochs,callbacks=callbacks,verbose=1)

    return model
