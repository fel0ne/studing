# Задание: Создать библиотеку из background.c и слинковать ее с библиотекой pipes


set(SOURCE_LIB background.c)

add_library(BACK STATIC ${SOURCE_LIB})

target_link_libraries( BACK PIPES)		#Линковка программы с библиотекой 