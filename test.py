import numpy as np
import os
import time
from vgg16 import VGG16
from keras.preprocessing import image
from keras.applications.imagenet_utils import preprocess_input
from imagenet_utils import decode_predictions
from keras.layers import Dense, Activation, Flatten
from keras.layers import merge, Input
from keras.models import Model
from keras.utils import np_utils
from sklearn.utils import shuffle
from sklearn.model_selection import train_test_split

#### PREDICTION TEST #####
##########################
##########################

model = VGG16(include_top=True, weights='imagenet')     ### import VGG16 model with all the weights and layers (include_top means including also last fully-connected classifaying layers)
img_path = 'elephant.jpg'   ### path to an image to be classified
img = image.load_img(img_path, target_size=(224, 224))  ### target img size for VGG16
x = image.img_to_array(img)                             ### img into array
x = np.expand_dims(x, axis=0)                           ### expand in order to have (nr. of images , pixelsX, pixelsY, channels(RGB))
x = preprocess_input(x)                                 ### pre-processing (mean extraction etc.)
print('Input image shape:', x.shape)

preds = model.predict(x)                                ### class prediction
print('Predicted:', decode_predictions(preds))          ### decoding

model.summary()                                        ### model summary
model.layers[-1].get_config()

##########################################################################


### LOAD CUSTOM DATA ###
########################
########################

PATH = os.getcwd() ### path to my GoogleDrive repoh
data_path = PATH + '/data'
data_dir_list = os.listdir(data_path)
print(data_dir_list)

img_data_list=[]

### LOADS IMAGES FROM ALL DIRECTORIES PRESENT IN /data
for dataset in data_dir_list:  ### loop over dir's
	img_list=os.listdir(data_path+'/'+ dataset)
	print ('Loaded the images of dataset-'+'{}\n'.format(dataset))
	for img in img_list:        ### loop over images inside dir
		img_path = data_path + '/'+ dataset + '/'+ img
		img = image.load_img(img_path, target_size=(224, 224))  ### target size for image
		x = image.img_to_array(img)
		x = np.expand_dims(x, axis=0)
		x = preprocess_input(x)
#		x = x/255
		print('Input image shape:', x.shape)
		img_data_list.append(x) ### append image to list



###########################################################################







### PUTTING DATA INTO RIGHT FORMAT ###
### (nr. of images, pixelsX, pixelsY, channels(RGB))
####################################################

img_data = np.array(img_data_list)
#img_data = img_data.astype('float32')
#print (img_data.shape)
img_data=np.rollaxis(img_data,1,0) ### switch axis 0 and 1 for desired vector form
#print (img_data.shape)
img_data=img_data[0] ### get rid of '1' for desired vector form
print (img_data.shape)


###########################################################################








### DEFINING NUMBER OF CLASS
### SPLITING CLASSES
### SPLITING TRAINING AND TESTING DATASET

num_classes = 4
num_of_samples = img_data.shape[0]
labels = np.ones((num_of_samples,),dtype='int64')

### ASSIGNING LABELS BASED ON IMG INDEX
labels[0:202]=0
labels[202:404]=1
labels[404:606]=2
labels[606:]=3

### DEFINING LABELS NAMES
names = ['cats','dogs','horses','humans']


Y = np_utils.to_categorical(labels, num_classes) ### convert class labels to on-hot encoding
                                                 ### -> (1,0,0,0) for class 1
                                                 ### -> (0,1,0,0) for class 2
                                                 ### -> (0,0,1,0) for class 3
                                                 ### -> (0,0,0,1) for class 4


x,y = shuffle(img_data,Y, random_state=2) ### shuffle the dataset

X_train, X_test, y_train, y_test = train_test_split(x, y, test_size=0.2, random_state=2) ### split the dataset

#############################################################################################################




### LOADING A MODEL AND MAKE IT COMPATIBLE WITH OUR DATASET
############################################################

image_input = Input(shape=(224, 224, 3)) ### pre-define image imput dimension

model = VGG16(input_tensor=image_input, include_top=True,weights='imagenet') ### import VGG16 model
model.summary()
last_layer = model.get_layer('fc2').output ### get the last layer (last before prediction layer)
#x= Flatten(name='flatten')(last_layer)
out = Dense(num_classes, activation='softmax', name='output')(last_layer) ### definition of the last prediction layer and setting it after 'fc2'
custom_vgg_model = Model(image_input, out) ### creating a model based on input and layers definiton
custom_vgg_model.summary()

########################################################################################################################

##########################################
### COMPILING AND TRAINING CUSTOM MODEL ###
##########################################

custom_vgg_model.compile(loss='categorical_crossentropy', optimizer='rmsprop',
						 metrics=['accuracy'])  ### compile custom model

for layer in custom_vgg_model.layers[:-1]:  ### set all layers except last one to untrainable
	layer.trainable = False

t = time.time()
#	t = now()
hist = custom_vgg_model.fit(X_train, y_train, batch_size=32, epochs=6, verbose=1,
							validation_data=(X_test, y_test))  ### train
print('Training time: %s' % (t - time.time()))

(loss, accuracy) = custom_vgg_model.evaluate(X_test, y_test, batch_size=10, verbose=1)

print("[INFO] loss={:.4f}, accuracy: {:.4f}%".format(loss, accuracy * 100))




