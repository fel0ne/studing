import requests
def getAllPosts(): 

    r = requests.get('http://localhost:8000/books/')
    
    if r.status_code == 200:
        json = r.json()
        for i in json:
            print(i['id'], ".", i['title'])
    else:
        print("GET запрос не успешен. Ошибка:", r.status_code)

        

def getPost(id):

    base = 'http://localhost:8000/books/'
    r = requests.get(base + str(id))
    
    if r.status_code == 200:
        json = r.json()
        print(json)  
    
    else:
        print("GET запрос не успешен. Ошибка:", r.status_code)


def postMethod(id, title, author, publication_year):
    data = {'id': id, 'title' : title, 'author' : author, 'publication_year' : publication_year}
    #data = {id,title, author, publication_year}
    headers = {'Content-Type': 'application/json'}
    r = requests.post('http://localhost:8000/books/', json=data, headers=headers)
    if r.status_code == 201:
        print("POST запрос успешен")
    else:
        print("POST запрос не успешен. Ошибка:", r.status_code)




print("--------------GET запрос все посты---------------\n")   
getAllPosts()
print("--------------GET запрос пост №1---------------\n")   
getPost(1)
print("-----------------POST запрос------------------\n")   
postMethod(1,"qwer","qwr",1928)


