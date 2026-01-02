import requests
AUTH_TOKEN = None
BASE_URL = 'http://127.0.0.1:8000'

def register_user():
    username = input("Enter username: ")
    password = input("Enter password: ")
    response = requests.post(f"{BASE_URL}/auth/register", json={"username": username, "password": password})
    if response.status_code == 200:
        print("Registration successful!")
        print(response.json())
    else:
        print(f"Error: {response.status_code} - {response.text}")


def login_user():

    global AUTH_TOKEN
    username = input("Enter username: ")
    password = input("Enter password: ")
    response = requests.post(f"{BASE_URL}/auth/token", data={"username": username, "password": password})
    if response.status_code == 200:
        AUTH_TOKEN = response.json().get("access_token")
        print("Login successful. Token stored.")
        print(f"Token: {AUTH_TOKEN}")
    else:
        print(f"Error: {response.status_code} - {response.text}")

def getAllBooks(author=None):
    url = f"{BASE_URL}/books"
    params = {}
    if author:
        params['author'] = author
    
    r = requests.get(url, params=params)
    
    if r.status_code == 200:
        json = r.json()
        for i in json:
            print(i['id'], ".", i['title'], "by", i['author'])
    else:
        print("GET запрос не успешен. Ошибка:", r.status_code)

def getBook(id):
    
    r = requests.get(f"{BASE_URL}/books" + str(id))
    
    if r.status_code == 200:
        json = r.json()
        print("ID:", json['id'])
        print("Title:", json['title'])
        print("Author:", json['author'])
        print("Year:", json['publication_year'])
    else:
        print("GET запрос не успешен. Ошибка:", r.status_code)

def createBook(id, title, author, publication_year):
    if not AUTH_TOKEN:
        print("Зарегестрируйтесь или войдите, чтобы добавлять книги.")
        return
    
    

    data = {'id': id, 'title' : title, 'author' : author, 'publication_year' : publication_year}
    headers = {"Authorization": f"Bearer {AUTH_TOKEN}"}
    r = requests.post(f"{BASE_URL}/books/", json=data, headers=headers)
    if r.status_code == 200:
        print("Book added successfully:")
        print(r.json())
    elif r.status_code == 401:
        print("Authentication error. Your session may have expired. Please log in again.")
    else:
        print(f"Error: {r.status_code} - {r.text}")

def updateBook(id, title, author, publication_year):

    if not AUTH_TOKEN:
        print("Зарегестрируйтесь или войдите, чтобы изменять книги.")
        return
    

    data = {'id': id, 'title' : title, 'author' : author, 'publication_year' : publication_year}

    headers = {"Authorization": f"Bearer {AUTH_TOKEN}"}
    r = requests.put(f"{BASE_URL}/books/" + str(id), json=data, headers=headers)
    
    if r.status_code == 200:
        print("Book puted successfully:")
        print(r.json())
    elif r.status_code == 401:
        print("Authentication error. Your session may have expired. Please log in again.")
    else:
        print(f"Error: {r.status_code} - {r.text}")

def deleteBook(id):
    if not AUTH_TOKEN:
        print("Зарегестрируйтесь или войдите, чтобы удалять книги.")
        return

    headers = {"Authorization": f"Bearer {AUTH_TOKEN}"}
    r = requests.delete(f"{BASE_URL}/books/" + str(id), headers=headers)
    
    if r.status_code == 200:
        print("Book deleted successfully:")
        print(r.json())
    elif r.status_code == 401:
        print("Authentication error. Your session may have expired. Please log in again.")
    else:
        print(f"Error: {r.status_code} - {r.text}")






while True:
    print("\n-------------- МЕНЮ --------------")
    print("1. Показать все книги")
    print("2. Показать книги автора")
    print("3. Найти книгу по ID") 
    print("4. Добавить книгу")
    print("5. Обновить книгу")
    print("6. Удалить книгу")
    print("7. register")
    print("8. login")
    print("9. Выход")
    
    choice = input("Выберите действие: ")
    
    if choice == "1":
        print("-------------- Все книги --------------")
        getAllBooks()
            
    elif choice == "2":
        author = input("Введите имя автора: ")
        print(f"-------------- Книги автора {author} --------------")
        getAllBooks(author)
            
    elif choice == "3":
        try:
            id = int(input("Введите ID книги: "))
            print(f"-------------- Книга №{id} --------------")
            getBook(id)
        except:
            print("Ошибка: ID должен быть числом")
                
    elif choice == "4":
        try:
            id = int(input("Введите ID: "))
            title = input("Введите название: ")
            author = input("Введите автора: ")
            year = int(input("Введите год: "))
            print("-------------- Добавление книги --------------")
            createBook(id, title, author, year)
        except:
            print("Ошибка: ID и год должны быть числами")
                
    elif choice == "5":
        try:
            id = int(input("Введите ID книги для обновления: "))
            title = input("Введите новое название: ")
            author = input("Введите нового автора: ")
            year = int(input("Введите новый год: "))
            print("-------------- Обновление книги --------------")
            updateBook(id, title, author, year)
        except:
            print("Ошибка: ID и год должны быть числами")
                
    elif choice == "6":
        try:
            id = int(input("Введите ID книги для удаления: "))
            print("-------------- Удаление книги --------------")
            deleteBook(id)
        except:
            print("Ошибка: ID должен быть числом")

    elif choice == "7":
        try:
            register_user()
        except:
            print("Ошибка регистрации")


    elif choice == "8":
        try:
            login_user()
        except:
            print("Ошибка входа")
                
    elif choice == "9":
        print("Выход...")
        break
            
    else:
        print("Неверный выбор, попробуйте снова")

