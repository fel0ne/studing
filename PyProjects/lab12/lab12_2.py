def check_dialog(message):
    questions_count = 0

    for sym in message:
        if sym == 'Q':
            questions_count += 1
        elif sym == 'A':
            questions_count -= 1
    if questions_count == 0:
        return('+')
    else:
        return('-')

message = input()
result = check_dialog(message)
print(result)
