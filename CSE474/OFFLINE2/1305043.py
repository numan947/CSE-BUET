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




def show_image(image,title,w=False):
	cv2.imshow(title,image)
	cv2.waitKey(0) & 0xFF
	cv2.destroyAllWindows()
	if(w==True):
		cv2.imwrite(str(title)+'.png',image)



def getValue(tmp,template):
	dTmp = template - tmp
	return np.sum(dTmp**2)


def ExhaustiveSearch(template,main):
	print("Running: ExhaustiveSearch")
	
	# print("Temlate Size-->",end="")	
	# print(template.shape)
	# print("Main Image Size-->",end="")	
	# print(main.shape)

	startTime = time.time()
	print("Start Time: ",startTime)

	t_h,t_w,t_d = template.shape
	m_h,m_w,m_d = main.shape
	#show_image(main,'chunked')

	D = np.ones((m_h-t_h,m_w-t_w))
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
	

	endTime = time.time()
	print("End Time: ",endTime)
	print("Total Time Taken: ",endTime-startTime," second(s)")

	
	cv2.rectangle(main,(c,r), (c+t_w,r+t_h),(0,0,0),2)
	show_image(main, 'ExhaustiveSearch',True)

	return ((r,c),endTime-startTime)





def TDLSearch(template,main,p):
	print("Running: 2DLogarithmicSearch")
	# print("Temlate Size-->",end="")	
	# print(template.shape)
	# print("Main Image Size-->",end="")	
	# print(main.shape)

	startTime = time.time()
	print("Start Time: ",startTime)


	t_h,t_w,t_d = template.shape
	m_h,m_w,m_d = main.shape


	k=np.ceil(np.log2(p))
	d = 2**(k-1)

	centerR,centerC = np.ceil(m_h/2.0),np.ceil(m_w/2.0)
	centerPoint = (int(centerR),int(centerC))	

	# 8 direction
	dx = [1,1,1,0,0,-1,-1,-1]
	dy = [0,1,-1,1,-1,0,1,-1]

	def getPoints(center,d):
		pts=[]
		for i in range(8):
			pts.append((int(center[0]+dy[i]*d),int(center[1]+dx[i]*d)))
		return pts

	def showPts(pts):
		for pt in pts:
			cv2.circle(main,(int(pt[0]),int(pt[1])), 1, (0,0,255), -1)

	while(p>=1):
		k=np.ceil(np.log2(p))
		d = 2**(k-1)
		print(d,k)
		pts = getPoints(centerPoint,d)
		
		pts.append(centerPoint)
		mn = np.inf
		mnPt = (np.inf,np.inf)
		
		for pt in pts:
			if(pt[0]+t_h<m_h and pt[1]+t_w<m_w):
				tmp = main[pt[0]:pt[0]+t_h,pt[1]:pt[1]+t_w,:]
				cur = getValue(tmp, template)
				if(cur<=mn):
					mn = cur
					mnPt = pt

		if(mnPt==centerPoint):
			p/=2
		else:
			centerPoint=mnPt
			#p/=2


	c = centerPoint[1]
	r = centerPoint[0]
	
	print("MAX MATCHED IMAGE-->",end="")
	print(r,c)


	
	endTime = time.time()
	print("End Time: ",endTime)
	print("Total Time Taken: ",endTime-startTime," second(s)")


	cv2.rectangle(main,(c,r), (c+t_w,r+t_h),(0,0,0),2)
	show_image(main, '2DLogarithmicSearch',True)


	return ((r,c),endTime-startTime)





def HeirarchicalSearch(template,main,level):

	for i in range(level):
		blur_main = cv2.GaussianBlur(main,(9,9),0)  #blur
		blur_main = blur_main[1::2,1::2] #downsample

		blur_temp = cv2.GaussianBlur(template,(9,9),0)
		blur_temp = blur_temp[1::2,1::2]

		




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

	#t_es = (ExhaustiveSearch(template,mainImage))[1]
	#t_tdls= (TDLSearch(template, mainImage,20))[1]
	HeirarchicalSearch(template, mainImage, 2)

	#print(t_es,t_tdls)



	#Test(imgTemplate, imgMain)








if __name__ == "__main__":
	main()