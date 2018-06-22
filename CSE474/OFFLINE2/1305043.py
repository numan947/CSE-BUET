import numpy as np
import cv2
import matplotlib.pyplot as plt
import sys
from numpy import unravel_index
import time







def Test(imgTemplate,imgMain):

	template = cv2.imread(imgTemplate)
	mainImage = cv2.imread(imgMain)

	img2 = mainImage.copy()

	tt,w,h = template.shape[::-1]
	

	res = cv2.matchTemplate(img2,template,cv2.TM_CCOEFF)

	min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(res)

	top_left = max_loc
	bottom_right= (top_left[0]+w,top_left[1]+h)
	
	print(min_val,max_val,min_loc,max_loc)
	

	cv2.rectangle(img2,top_left,bottom_right,(255,255,255),2,)


	cv2.imshow('image',img2)
	cv2.waitKey(0) & 0xFF

	cv2.destroyAllWindows()




def show_image(image,title):
	cv2.imshow(title,image)
	cv2.waitKey(0) & 0xFF
	cv2.destroyAllWindows()
	cv2.imwrite(str(title)+'.png',image)



def getValue(tmp,template):
	dTmp = template - tmp
	return np.sum(dTmp**2)


def ExhaustiveSearch(template,main):
	
	print("Temlate Size-->",end="")	
	print(template.shape)
	print("Main Image Size-->",end="")	
	print(main.shape)

	startTime = time.time()
	print("Start Time: ",startTime)

	t_h,t_w,t_d = template.shape
	m_h,m_w,m_d = main.shape
	#show_image(main,'chunked')

	D = np.ones((m_h,m_w))
	D*=np.inf

	#print(D.shape==main.shape)

	for i in range(m_h-t_h):
		for j in range(m_w-t_w):
			#print(main[i:i+t_h,j:j+t_w,:].shape,template.shape)
			tmp = main[i:i+t_h,j:j+t_w,:]
			D[i][j] = getValue(tmp, template)

	print("MAX MATCHED IMAGE-->",end="")	
	print(unravel_index(D.argmin(),D.shape))

	r,c = unravel_index(D.argmin(),D.shape)

	cv2.rectangle(main,(c,r), (c+t_w,r+t_h),(0,0,0),2)

	endTime = time.time()
	print("End Time: ",endTime)

	print("Total Time Taken: ",endTime-startTime," second(s)")
	#cv2.rectangle(main,(0,0),(50,50),(250,250,250),cv2.FILLED)

	#cv2.arrowedLine(main,())


	show_image(main, 'ExhaustiveSearch')




def TDLSearch(template,main):
	print("Temlate Size-->",end="")	
	print(template.shape)
	print("Main Image Size-->",end="")	
	print(main.shape)

	t_h,t_w,t_d = template.shape
	m_h,m_w,m_d = main.shape


	print(np.ceil(np.log2(m_h)))
	print(np.ceil(np.log2(m_w)))
	
	k_h = np.ceil(np.log2(m_h))
	k_w = np.ceil(np.log2(m_h))
	
	d1 = 2**(k_h-1)
	d2 = 2**(k_w-1)

	# centerR,centerC = np.ceil(m_h/2.0),np.ceil(m_w/2.0)

	# print(centerR,centerC)
	# print(d1,d2)
	print("AT MOST",m_h/d1,m_w/d2)
	

	pts = []
	# dx = [1,1,1,0,0,0,-1,-1,-1]
	# dy = [0,1,-1,0,1,-1,0,1,-1]



	# pts.append((centerR,centerC))

	# scl=1

	# while(True):
	# 	tmp = []
	# 	for i in range(9):
	# 		curR = centerR + dx[i]*scl*d1
	# 		curC = centerC + dy[i]*scl*d2
	# 		print(curR,curC)
	# 		print(dx[i],dy[i])
	# 		if(curR>=0 and curR<=m_h and curC>=0 and curC<=m_w):
	# 			tmp.append((curR,curC))
	# 	pts.extend(tmp)
	# 	break
	# 	scl+=1

	# print(len(pts))
	# print(pts)


	for i in range(0,int(m_h/d1)):
		for j in range(0,int(m_w/d2)):
			pts.append((np.float(i)*d1,np.float(j)*d2))

	print(pts)

	for pt in pts:
		 cv2.circle(main,(int(pt[0]),int(pt[1])), 5, (0,0,255), -1)


	show_image(main, "asdf")












def main():


	if(len(sys.argv)!=3):
		print("Usage: python 1305043.py <MainImage> <TemplateImage>")
		exit(1)

	#Read File Names
	imgMain = sys.argv[1]
	imgTemplate = sys.argv[2]


	#Read Images
	template = cv2.imread(imgTemplate)
	mainImage = cv2.imread(imgMain)


	print(imgMain)
	print(imgTemplate)

	#ExhaustiveSearch(template,mainImage)
	TDLSearch(template, mainImage)


	#Test(imgTemplate, imgMain)








if __name__ == "__main__":
	main()