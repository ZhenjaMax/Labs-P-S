import wikipedia

pages_list = str(input())
pages_list = pages_list.split(', ')

if pages_list[-1] in wikipedia.languages().keys:
    wikipedia.set_lang(pages_list[-1])
    del pages_list[-1]
else:
    print('no results')
    exit

max_words, page_number_max = 0, 0

for i in range(len(pages_list)):
    text = wikipedia.summary(pages_list[i])
    words = text.count(' ') + 1
    if words >= max_words:
        max_words = words
        page_number_max = i
print(wikipedia.page(pages_list[page_number_max]).title, max_words)

chain = []

for i in pages_list:
    links = wikipedia.page(i).links
    pages_list.remove(i)
    for j in links:
        if j in pages_list:
            chain_add = [i, j]
            chain.append(chain_add)
        else:
            sublinks = wikipedia.page(j).links
            for k in sublinks:
                if k in pages_list:
                    chaid_add = [i, j, k]
                    chain.append(chain_add)
print(chain)
chain.append(pages_list[0])
for i in range(len(pages_list)-1):
    chain.append(pages_list[i])
    if not pages_list[i+1] in wikipedia.page(pages_list[i]).links:
        sublinks=wikipedia.page(pages_list[i]).links
        for j in sublinks:
            if j in pages_list:
                chain.append(j)
                chain.append(pages_list[i+1])
    else:
        chain.append(pages_list[i+1])
