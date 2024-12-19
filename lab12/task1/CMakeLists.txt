# Задание: задать имя проекта и версию cmake, добавить subdirectory для background и pipes, в которых 
# тоже есть свои CMakeLists.txt (внутри них тоже нужно добавить одну-две строки для сборки, задание описано в них же)
# Решить проблему с заголовочными файлами, включив директории в корневом CMakeLists.txt (include_directories)
# Слинковать исполняемый файл из src/main.c с библиотекой background
# Все это дело собрать, используя cmake и make
# Для установки cmake нужно установить его: sudo apt install build-essential cmake -y


cmake_minimum_required(VERSION 3.10) 	# Проверка версии CMake.
										# Если версия установленой программы
										# старее указаной, произойдёт аварийный выход.

project(task1)					# Название проекта

set(SOURCE_EXE main.c)					# Установка переменной со списком исходников

include_directories("./background" "./pipes")			# Расположение заголовочных файлов

add_executable(main src/main.c )		# Создает исполняемый файл с именем main

add_subdirectory("./background")			# Добавление подпроекта, указывается имя дирректории

add_subdirectory("./pipes")


target_link_libraries(main PIPES BACK)		#Линковка программы с библиотекой 