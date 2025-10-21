from fastapi import FastAPI,Response
from pydantic import BaseModel

class Book(BaseModel):
    id : int 
    title : str
    author : str 
    publication_year : int 

main = FastAPI()
books = [Book(id = 1, title = "master and margaret", author = "Bulgakov", publication_year = 1898),
         Book(id = 2, title = "white bim black ear", author = "Troepolski", publication_year = 1971)]

last_id = 0
for book in books:
    last_id += 1

@main.get("/books", response_model =list[Book])
def get_books():
    return(books)

@main.get("/books/{book_id}", response_model=Book)
def get_book(book_id: int):
    for book in books:
        if book.id == book_id:
            return book
    return Response(content = "Book not found", status_code = 404)
    
    


@main.post("/books")
def post_book(book_data: Book):
    global last_id 

    new_book = Book(
        id=last_id,
        title=book_data.title,
        author=book_data.author,
        publication_year=book_data.publication_year
    )
    
    books.append(new_book)
    last_id += 1
    return Response(content = "succes append", status_code = 200)



