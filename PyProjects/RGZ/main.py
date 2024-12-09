from random import randint

import PySimpleGUI as sg
from random import randint
sg.theme('DarkTeal')

layout = [ [sg.Text("Счет:"),sg.InputText(size = (30,0),k = "out_schet")],
           [sg.Image("—Pngtree—rock paper scissors playing rope_5656222 (2).png")],
           [ sg.Text("Бот: "), sg.InputText(size = (30,0), k = "out_bot"),sg.Text("Вы: "), sg.InputText(size = (30,0), k = "out_people")],
           [ sg.Text("Результат:"), sg.InputText(size = (25,0),k = "out")],
           [sg.Button("Камень", size = (20,10)),sg.Button("Ножницы", size = (20,10)),sg.Button("Бумага", size = (20,10))]
         ]

window = sg.Window('KMN', layout)

counter_bot = 0
counter_people = 0
while True:
    event, values = window.read()
    if event == sg.WIN_CLOSED :
        break

    bot = randint(0, 2)
    bot_out = ""


    if bot == 0:
        bot = 'k'
        bot_out = "Камень"
    elif bot == 1:
        bot = 'b'
        bot_out = "Бумага"
    elif bot == 2:
        bot = 'n'
        bot_out = "Ножницы"

    if event == 'Камень':
        people = 'k'
        window['out_people'].update("Камень")
    elif event == 'Ножницы':
        people = 'n'
        window['out_people'].update("Ножницы")
    elif event == 'Бумага':
        people = 'b'
        window['out_people'].update("Бумага")


    if people == bot:
        window['out'].update("Ничья")
    elif people == "k" and bot == "n":
        window['out'].update("Ты выйграл")
        counter_people += 1
    elif people == "b" and bot == "k":
        window['out'].update("Ты выйграл")
        counter_people += 1
    elif people == "n" and bot == "b":
        window['out'].update("Ты выйграл")
        counter_people += 1
    else:
        window['out'].update("Ты проиграл")
        counter_bot += 1

    window['out_bot'].update(bot_out)
    window['out_schet'].update(str(counter_people) + " : " + str(counter_bot))

window.close()





