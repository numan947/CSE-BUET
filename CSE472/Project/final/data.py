
import pandas as pd
import os
import numpy as np
from skimage.io import imsave
import sys
import zipfile
# source is the current directory
# Open dataset file




def read_process_save(dataset,folder_path,max = None):

	MAIN_LIST = ["Angry","Disgust","Fear","Happy","Sad","Surprise","Neutral"]

	img_labels = list(dataset['emotion'].values)

	
	folders_to_be_created = np.unique(img_labels)

	for newpath in folders_to_be_created:
	    if not os.path.exists(os.path.join(folder_path,str(MAIN_LIST[newpath]))):
	        os.makedirs(os.path.join(folder_path,str(MAIN_LIST[newpath])))

	if(max is not None):
		if(max>7):
			max = (max/7)+1

		for em in MAIN_LIST:
			total=0
			tmp_data = dataset[dataset.emotion==MAIN_LIST.index(em)]
			all_images = tmp_data['pixels'].values
			all_labels = tmp_data['emotion'].values
			print(em)
			for label,image in zip(all_labels,all_images):
				image = np.array([int(x) for x in image.split(" ")])
				image = image.reshape(48,48)
				imsave(os.path.join(str(folder_path),str(MAIN_LIST[label]),str(MAIN_LIST[int(label)])+str(total)+".png"),image)
				#print(str(folder_path)+"/"+str(label)+"/"+str(MAIN_LIST[int(label)]+str(total)+".jpg"))
				#print(total)
				total+=1
				if(total>=max):
					break


	else:
		all_images = dataset['pixels'].values
		all_labels = dataset['emotion'].values
		total=0
		for label,image in zip(all_labels,all_images):
			image = np.array([int(x) for x in image.split(" ")])
			image = image.reshape(48,48)
			imsave(os.path.join(str(folder_path),str(MAIN_LIST[label]),str(MAIN_LIST[int(label)])+str(total)+".png"),image)
			#print(str(folder_path)+"/"+str(label)+"/"+str(MAIN_LIST[int(label)]+str(total)+".jpg"))
			print(total)
			total+=1



def make_dirs(path):
	if not os.path.exists(path):
		os.makedirs(path)

def zipdir(path):
	print("zipping.........",path)
	cd = os.getcwd()
	os.chdir(path)
	print(os.getcwd())
	zipf = zipfile.ZipFile(os.path.join('data.zip'),'w',zipfile.ZIP_DEFLATED)
	for root,dirs,files in os.walk(os.getcwd()):
		for file in files:
			if 'data' not in file:
				zipf.write(os.path.join(os.path.basename(root),file))
	zipf.close()
	os.chdir(cd)
	print("zipping........Done!")


def main(path_to_csv):

	dataset = pd.read_csv(path_to_csv)


	path_test = os.path.join('Data','Test','Test_10_percent')
	make_dirs(path_test)
	path_train_best_hyp = os.path.join('Data','Train','Best_hyperparameter_80_percent')
	make_dirs(path_train_best_hyp)
	path_to_train_under_10 = os.path.join('Data','Train','Under_10_min_training')
	make_dirs(path_to_train_under_10)
	path_to_train_under_90 = os.path.join('Data','Train','Under_90_min_tuning')
	make_dirs(path_to_train_under_90)
	path_to_validation_3_samp = os.path.join('Data','Validation','3_samples')
	make_dirs(path_to_validation_3_samp)
	path_to_validation_10 = os.path.join('Data','Validation','Validation_10_percent')
	make_dirs(path_to_validation_10)


	print(dataset.columns)


	TrainingSet = dataset[dataset.Usage=='Training']

	ValidationSet = dataset[dataset.Usage=='PublicTest']

	TestSet = dataset[dataset.Usage=='PrivateTest']


	#make full datas
	read_process_save(TestSet,path_test)
	zipdir(path_test)
	read_process_save(TrainingSet,path_train_best_hyp)
	zipdir(path_train_best_hyp)
	read_process_save(ValidationSet,path_to_validation_10)
	zipdir(path_to_validation_10)

	#make others

	read_process_save(TrainingSet,path_to_train_under_10,490)
	zipdir(path_to_train_under_10)
	read_process_save(TrainingSet,path_to_train_under_90,3500)
	zipdir(path_to_train_under_90)
	read_process_save(ValidationSet,path_to_validation_3_samp,3)
	zipdir(path_to_validation_3_samp)


if __name__ == '__main__':
	zip_ref = zipfile.ZipFile(sys.argv[1],'r')
	zip_ref.extractall(os.path.join('Data'))
	zip_ref.close()
	path_to_csv = os.path.join('Data','fer2013.csv')
	print(sys.argv[1])
	main(path_to_csv)



