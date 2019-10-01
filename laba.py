import wikipedia                                                                
                                                                                
pages_list = str(input())                                                       
pages_list = pages_list.split(', ')                                             
                                                                                
if pages_list[-1] in wikipedia.languages():                                     
    wikipedia.set_lang(pages_list[-1])                                          
    del pages_list[-1]                                                          
else:                                                                           
    print('no results')                                                         
    exit()                                                                      
                                                                                
from help_wiki_function import is_page_valid                                    
for i in pages_list:                                                            
    if not is_page_valid(i):                                                    
        pages_list.remove(i)                                                    
                                                                                
max_words, page_number_max = 0, 0                                               
for i in range(len(pages_list)):                                                
    text = wikipedia.summary(pages_list[i])                                     
    words = text.count(' ') + 1                                                 
    if words >= max_words:                                                      
        max_words = words                                                       
        page_number_max = i                                                     
print(max_words, wikipedia.page(pages_list[page_number_max]).title)          
                                                                                
chain=[]                                                                        
chain.append(pages_list[0])                                                     
for i in range(len(pages_list)-1):                                              
    if pages_list[i+1] in wikipedia.page(pages_list[i]).links:                  
        chain.append(pages_list[i+1])                                           
    else:                                                                       
        sublinks=wikipedia.page(pages_list[i]).links                            
        for j in sublinks:                                                      
            if pages_list[i+1] in wikipedia.page(j).links:                      
                chain.append(j)                                                 
                chain.append(pages_list[i+1])                                   
print(chain)
