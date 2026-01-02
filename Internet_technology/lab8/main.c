#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>


#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Константы для настройки сервера
#define DEFAULT_PORT 8080      // Порт по умолчанию
#define BUFFER_SIZE 1024       // Размер буфера для приема данных
#define MAX_CLIENTS 10         // Максимальное количество ожидающих соединений
#define ECHO_PREFIX "[ECHO]: " // Префикс для эхо-ответов

// Функция для вывода ошибок с описанием
void print_error(const char *message) {
    fprintf(stderr, "ОШИБКА: %s (errno: %d - %s)\n", 
            message, errno, strerror(errno));
}

// Функция для инициализации и запуска сервера
int start_server(int port) {
    int server_fd;                    // Дескриптор сокета сервера
    int client_fd;                    // Дескриптор сокета клиента
    struct sockaddr_in server_addr;   // Адресная структура сервера
    struct sockaddr_in client_addr;   // Адресная структура клиента
    socklen_t client_addr_len;        // Длина адресной структуры клиента
    char buffer[BUFFER_SIZE];         // Буфер для приема/отправки данных
    int bytes_received;               // Количество полученных байт
    char client_ip[INET_ADDRSTRLEN];  // Строковое представление IP клиента
    
    /*
     * Шаг 1: Создание сокета
     * AF_INET - семейство адресов IPv4
     * SOCK_STREAM - тип сокета для TCP
     * 0 - протокол по умолчанию (TCP для SOCK_STREAM)
     */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        print_error("Не удалось создать сокет");
        return -1;
    }
    printf("[INFO] Сокет успешно создан (fd: %d)\n", server_fd);
    
    /*
     * Шаг 2: Настройка опции SO_REUSEADDR
     * Позволяет повторно использовать адрес после перезапуска сервера
     */
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        print_error("Не удалось установить SO_REUSEADDR");
        close(server_fd);
        return -1;
    }
    
    /*
     * Шаг 3: Заполнение структуры адреса сервера
     * sin_family - семейство адресов (IPv4)
     * sin_port - порт в сетевом порядке байт
     * sin_addr.s_addr - адрес (INADDR_ANY означает "все интерфейсы")
     */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);  // Преобразование порта в сетевой порядок
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Принимаем соединения с любого интерфейса
    
    /*
     * Шаг 4: Привязка сокета к адресу и порту
     */
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        print_error("Не удалось привязать сокет к адресу");
        close(server_fd);
        return -1;
    }
    printf("[INFO] Сокет привязан к порту %d\n", port);
    
    /*
     * Шаг 5: Перевод сокета в режим прослушивания
     * MAX_CLIENTS - максимальная длина очереди ожидающих соединений
     */
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        print_error("Ошибка перевода сокета в режим прослушивания");
        close(server_fd);
        return -1;
    }
    printf("[INFO] Сервер запущен и слушает порт %d\n", port);
    printf("[INFO] Ожидание подключений...\n");
    printf("========================================\n");
    
    /*
     * Шаг 6: Основной цикл обработки клиентов
     * Сервер работает бесконечно, принимая новых клиентов
     */
    while (1) {
        // Сброс длины адресной структуры клиента
        client_addr_len = sizeof(client_addr);
        
        /*
         * Шаг 6.1: Принятие входящего соединения
         * accept() блокирует выполнение до появления нового соединения
         */
        client_fd = accept(server_fd, 
                          (struct sockaddr*)&client_addr, 
                          &client_addr_len);
        
        if (client_fd < 0) {
            print_error("Ошибка при принятии соединения");
            continue;  // Продолжаем ожидание следующих клиентов
        }
        
        /*
         * Шаг 6.2: Преобразование IP-адреса клиента в строковый формат
         */
        inet_ntop(AF_INET, &(client_addr.sin_addr), 
                 client_ip, INET_ADDRSTRLEN);
        printf("[INFO] Новое подключение от %s:%d\n", 
               client_ip, ntohs(client_addr.sin_port));
        
        /*
         * Шаг 6.3: Цикл обработки сообщений от конкретного клиента
         */
        while (1) {
            // Очистка буфера перед приемом данных
            memset(buffer, 0, BUFFER_SIZE);
            
            /*
             * Шаг 6.3.1: Прием данных от клиента
             * recv() блокируется до получения данных
             */
            bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
            
            // Проверка результата приема данных
            if (bytes_received < 0) {
                print_error("Ошибка при приеме данных");
                break;
            } else if (bytes_received == 0) {
                // Клиент корректно закрыл соединение
                printf("[INFO] Клиент %s:%d отключился\n", 
                       client_ip, ntohs(client_addr.sin_port));
                break;
            }
            
            // Удаляем символ новой строки, если он есть
            buffer[strcspn(buffer, "\n")] = 0;
            buffer[strcspn(buffer, "\r")] = 0;
            
            // Вывод полученного сообщения
            printf("[RECV] От %s: \"%s\"\n", client_ip, buffer);
            
            /*
             * Шаг 6.3.2: Проверка команды exit
             * Если клиент отправил "exit", завершаем соединение
             */
            if (strcasecmp(buffer, "exit") == 0) {
                printf("[INFO] Клиент %s запросил отключение\n", client_ip);
                break;
            }
            
            /*
             * Шаг 6.3.3: Подготовка эхо-ответа
             * Формируем строку с префиксом [ECHO]:
             */
            char response[BUFFER_SIZE];
            snprintf(response, sizeof(response), "%s%s\n", ECHO_PREFIX, buffer);
            
            /*
             * Шаг 6.3.4: Отправка ответа клиенту
             */
            int bytes_sent = send(client_fd, response, strlen(response), 0);
            if (bytes_sent < 0) {
                print_error("Ошибка при отправке данных");
                break;
            }
            printf("[SENT] Клиенту %s: \"%s\"", client_ip, response);
        }
        
        /*
         * Шаг 6.4: Закрытие соединения с клиентом
         */
        printf("[INFO] Закрытие соединения с клиентом %s\n", client_ip);
        printf("========================================\n");
        close(client_fd);
    }
    
    /*
     * Шаг 7: Закрытие сокета сервера
     * (на практике этот код никогда не выполнится из-за бесконечного цикла)
     */
    close(server_fd);
    return 0;
}

int main(int argc, char *argv[]) {
    int port = DEFAULT_PORT;
    
    /*
     * Обработка аргументов командной строки
     * Позволяет указать порт при запуске: ./server <port>
     */
    if (argc == 2) {
        port = atoi(argv[1]);
        if (port <= 0 || port > 65535) {
            fprintf(stderr, "ОШИБКА: Некорректный номер порта. Использую порт по умолчанию %d\n", 
                    DEFAULT_PORT);
            port = DEFAULT_PORT;
        }
    } else if (argc > 2) {
        fprintf(stderr, "Использование: %s [port]\n", argv[0]);
        fprintf(stderr, "Пример: %s 8080\n", argv[0]);
        return 1;
    }
    
    printf("========================================\n");
    printf("TCP Echo Server v1.0\n");
    printf("Автор: Системное программирование Linux\n");
    printf("========================================\n");
    printf("Порт: %d\n", port);
    printf("Префикс эхо: %s\n", ECHO_PREFIX);
    printf("Для выхода клиента используйте команду: exit\n");
    printf("========================================\n");
    
    // Запуск сервера
    return start_server(port);
}


