
import pandas as pd
import os
import numpy as np
from skimage.io import imsave
# source is the current directory
# Open dataset file




def read_process_save(dataset,folder_path,max = None):

	MAIN_LIST = ["Angry","Disgust","Fear","Happy","Sad","Surprise","Neutral"]

	img_labels = list(dataset['emotion'].values)

	
	folders_to_be_created = np.unique(img_labels)

	for newpath in folders_to_be_created:
	    if not os.path.exists(folder_path+"/"+str(MAIN_LIST[newpath])):
	        os.makedirs(folder_path+"/"+str(MAIN_LIST[newpath]))

	all_images = dataset['pixels'].values
	all_labels = dataset['emotion'].values


	total = 0

	for label,image in zip(all_labels,all_images):
		image = np.array([int(x) for x in image.split(" ")])
		image = image.reshape(48,48)
		imsave(str(folder_path)+"/"+str(MAIN_LIST[label])+"/"+str(MAIN_LIST[int(label)])+str(total)+".png",image)
		#print(str(folder_path)+"/"+str(label)+"/"+str(MAIN_LIST[int(label)]+str(total)+".jpg"))
		print(total)
		total+=1
		if(max is not None):
			if(total>=max):
				break


def main():

	dataset = pd.read_csv('fer2013.csv')


	print(dataset.columns)


	TrainingSet = dataset[dataset.Usage=='Training']

	ValidationSet = dataset[dataset.Usage=='PublicTest']

	TestSet = dataset[dataset.Usage=='PrivateTest']


	read_process_save(TestSet,"PrivateTest1",200)

	read_process_save(TrainingSet,"Training1",200)

	read_process_save(ValidationSet,"PublicTest1",20)


if __name__ == '__main__':
	main()


# file_names = list(dataset['Usage'].values)
# img_labels = list(dataset['emotion'].values)


# folders_to_be_created = np.unique(list(dataset['emotion']))

# main_folders_to_be_created = np.unique(file_names)

# print(folders_to_be_created)


# print(dataset.head())


# source = os.getcwd()




# for newpath in main_folders_to_be_created:
#     if not os.path.exists(str(newpath)):
#         os.makedirs(str(newpath))

# # ## Be Sure that there is nothing else in your directory except the data, csv and the code file, IT's Better to only have your data in that directory and reference the CSV file from a different Directory...

# folders = folders_to_be_created.copy()


# i = 0

# for f in range(len(file_names)):

#   current_img = file_names[f]
#   current_label = img_labels[f]

#    ##**Check this Line Accordingly** 

#   shutil.move("path/to/current/file i.e ..//..//data//current_img", "path//to//new//destination//folder//current_label//")
