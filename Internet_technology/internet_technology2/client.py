import requests
def getAllPosts(): 

    r = requests.get('https://jsonplaceholder.typicode.com/posts')
    
    if r.status_code == 200:
        json = r.json()
        for i in json:
            print(i['id'], ".", i['title'])
    else:
        print("GET запрос не успешен. Ошибка:", r.status_code)

        

def getPost(id):

    base = 'https://jsonplaceholder.typicode.com/posts/'
    r = requests.get(base + str(id))
    
    if r.status_code == 200:
        json = r.json()
        print("userId:", json['userId'])  
        print("id:", json['id'])
        print("title:", json['title'])
        print("body:", json['body'])
    else:
        print("GET запрос не успешен. Ошибка:", r.status_code)


def postMethod(userId, id, title, body):
    data = {'userId': str(userId), 'id' : str(id), 'title' : str(title), 'body' : str(body)}
    headers = {'Content-Type': 'application/json'}
    r = requests.post('https://jsonplaceholder.typicode.com/posts/', data, headers)
    if r.status_code == 201:
        print("POST запрос успешен")
    else:
        print("POST запрос не успешен. Ошибка:", r.status_code)



print("--------------GET запрос все посты---------------\n")   
getAllPosts()
print("--------------GET запрос пост №1---------------\n")   
getPost(1)
print("-----------------POST запрос------------------\n")   
postMethod("user",1,323,"hello")


