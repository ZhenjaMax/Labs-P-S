import wikipedia
from help_wiki_function import is_page_valid
pages = input().split(', ')

if pages[-1] in wikipedia.languages():
    wikipedia.set_lang(pages[-1])
    del pages[-1]
else:
    print('no results')
    exit()

i = 0
while i < len(pages):
    if is_page_valid(i):
        i += 1
    else:
        del pages[i]

max_words, max_number = 0, 0
for i in range(len(pages)):
    words = len(wikipedia.summary(pages[i]).split())
    if words >= max_words:
        max_words = words
        max_number = i
print(max_words, wikipedia.page(pages[max_number]).title)

chain = [pages[0]]
for i in range(len(pages) - 1):
    links = wikipedia.page(pages[i]).links
    if pages[i + 1] in links:
        chain.append(pages[i + 1])
        continue
    else:
        for j in range(len(links)):
            sublinks = wikipedia.page(links[j]).links
            if pages[i + 1] in sublinks:
                chain.append(links[j])
                chain.append(pages[i + 1])
                break
print(chain)
