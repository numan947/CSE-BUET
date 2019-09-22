function w = my_perceptron(w,learn_rate,train)
  
  train_size=size(train);
  
  count_error=[];
  time=[];
  count=0;
  
  
  for k=1:500
    time=[time k];
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    update=zeros(1,3)
    for i=1:train_size(1)
    %insert your code within this for loop and record the number of
    %missclassified examples on count variable
      tmp=train(i,1:2)
      tmp=[tmp,1]
      x=w'*tmp'
      
      cls=0
      if(x>0)
        cls=2
      else 
        cls=1
      endif
      
      if(cls!=train(i,3))
        count=count+1
        w=w-learn_rate.*tmp
      else
        w=w+learn_rate.*tmp
      endif
      
      
    end
    
    
    
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%    
  
   
    count_error=[count_error count];
    if count==0
      break;
    end
    count=0; 
  end
  
  plot(time,count_error)
   
end