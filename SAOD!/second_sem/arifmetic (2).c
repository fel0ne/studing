#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <stdint.h>
#include <float.h>

#define MAX_UNIQUE_CHARS 4096

typedef struct {
    uint32_t code_point;
    long long count;
    long double probability;
    long double lower_bound;
    long double upper_bound;
    char utf8_str[8];
} CharacterInfo;

static int get_utf8_char(const unsigned char *data, size_t data_len, uint32_t *result, size_t *bytes_read) {
    if (data_len == 0) return 0;
    unsigned char first_byte = data[0];
    
    if (first_byte < 0x80) {
        *result = first_byte;
        *bytes_read = 1;
        return 1;
    }
    
    if ((first_byte & 0xE0) == 0xC0) {
        if (data_len < 2) return 0;
        uint32_t cp = ((first_byte & 0x1F) << 6) | (data[1] & 0x3F);
        if (cp < 0x80) return 0;
        *result = cp;
        *bytes_read = 2;
        return 1;
    }
    
    if ((first_byte & 0xF0) == 0xE0) {
        if (data_len < 3) return 0;
        uint32_t cp = ((first_byte & 0x0F) << 12) | ((data[1] & 0x3F) << 6) | (data[2] & 0x3F);
        if (cp < 0x800) return 0;
        *result = cp;
        *bytes_read = 3;
        return 1;
    }
    
    if ((first_byte & 0xF8) == 0xF0) {
        if (data_len < 4) return 0;
        uint32_t cp = ((first_byte & 0x07) << 18) | ((data[1] & 0x3F) << 12) | 
                     ((data[2] & 0x3F) << 6) | (data[3] & 0x3F);
        if (cp < 0x10000 || cp > 0x10FFFF) return 0;
        *result = cp;
        *bytes_read = 4;
        return 1;
    }
    
    return 0;
}

static int convert_to_utf8(uint32_t cp, char output[5]) {
    if (cp < 0x80) {
        output[0] = (char)cp;
        output[1] = 0;
        return 1;
    }
    
    if (cp < 0x800) {
        output[0] = (char)(0xC0 | (cp >> 6));
        output[1] = (char)(0x80 | (cp & 0x3F));
        output[2] = 0;
        return 2;
    }
    
    if (cp < 0x10000) {
        output[0] = (char)(0xE0 | (cp >> 12));
        output[1] = (char)(0x80 | ((cp >> 6) & 0x3F));
        output[2] = (char)(0x80 | (cp & 0x3F));
        output[3] = 0;
        return 3;
    }
    
    if (cp <= 0x10FFFF) {
        output[0] = (char)(0xF0 | (cp >> 18));
        output[1] = (char)(0x80 | ((cp >> 12) & 0x3F));
        output[2] = (char)(0x80 | ((cp >> 6) & 0x3F));
        output[3] = (char)(0x80 | (cp & 0x3F));
        output[4] = 0;
        return 4;
    }
    
    return 0;
}

static int locate_char_index(CharacterInfo *array, int size, uint32_t cp) {
    for (int i = 0; i < size; ++i) {
        if (array[i].code_point == cp) return i;
    }
    return -1;
}

static int compare_chars(const void *a, const void *b) {
    const CharacterInfo *char_a = (const CharacterInfo*)a;
    const CharacterInfo *char_b = (const CharacterInfo*)b;
    if (char_a->code_point < char_b->code_point) return -1;
    if (char_a->code_point > char_b->code_point) return 1;
    return 0;
}

void show_binary_representation(long double value, int bit_count) {
    printf("0.");
    for (int i = 0; i < bit_count; i++) {
        value *= 2.0L;
        if (value >= 1.0L) {
            printf("1");
            value -= 1.0L;
        } else {
            printf("0");
        }
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Формат: %s <файл_для_обработки>\n", argv[0]);
        return 1;
    }

    const char *input_filename = argv[1];
    FILE *input_file = fopen(input_filename, "rb");
    if (!input_file) {
        fprintf(stderr, "Ошибка открытия '%s': %s\n", input_filename, strerror(errno));
        return 1;
    }

    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    unsigned char *file_buffer = (unsigned char*)malloc(file_size + 1);
    if (!file_buffer) {
        fclose(input_file);
        return 1;
    }
    
    fread(file_buffer, 1, file_size, input_file);
    file_buffer[file_size] = 0;
    fclose(input_file);

    printf("Обработан файл размером: %ld байт\n", file_size);

    CharacterInfo char_data[MAX_UNIQUE_CHARS];
    int char_count = 0;
    long long total_characters = 0;
    size_t position = 0;

    // Сначала посчитаем символы
    while (position < file_size) {
        uint32_t current_char;
        size_t bytes_consumed;
        
        if (!get_utf8_char(file_buffer + position, file_size - position, 
                          &current_char, &bytes_consumed)) {
            current_char = file_buffer[position];
            bytes_consumed = 1;
        }
        
        int char_index = locate_char_index(char_data, char_count, current_char);
        
        if (char_index == -1) {
            char_data[char_count].code_point = current_char;
            char_data[char_count].count = 1;
            convert_to_utf8(current_char, char_data[char_count].utf8_str);
            char_count++;
        } else {
            char_data[char_index].count++;
        }
        
        position += bytes_consumed;
        total_characters++;
    }

    // Отладочная информация
    printf("Всего символов: %lld\n", total_characters);
    printf("Уникальных символов: %d\n", char_count);

    qsort(char_data, char_count, sizeof(CharacterInfo), compare_chars);

    // Вычисляем вероятности с большей точностью
    long double cumulative_prob = 0.0L;
    printf("\nСтатистика символов (Алфавит)\n");
    printf("------------------------------------------------------------\n");
    printf("| Символ | Частота | Вероятность | Интервал [Min, Max) |\n");
    printf("------------------------------------------------------------\n");
    
    for (int i = 0; i < char_count; i++) {
        char_data[i].probability = (long double)char_data[i].count / (long double)total_characters;
        char_data[i].lower_bound = cumulative_prob;
        char_data[i].upper_bound = cumulative_prob + char_data[i].probability;
        cumulative_prob = char_data[i].upper_bound;

        // Используем экспоненциальную форму для очень маленьких вероятностей
        if (char_data[i].probability < 1e-10) {
            printf("| %-6s | %7lld | %11.3Le | [%.8Lf, %.8Lf) |\n", 
                char_data[i].utf8_str, char_data[i].count, 
                char_data[i].probability, char_data[i].lower_bound, char_data[i].upper_bound);
        } else {
            printf("| %-6s | %7lld | %11.9Lf | [%.8Lf, %.8Lf) |\n", 
                char_data[i].utf8_str, char_data[i].count, 
                char_data[i].probability, char_data[i].lower_bound, char_data[i].upper_bound);
        }
    }
    printf("------------------------------------------------------------\n");

    int block_size;
    printf("\nВведите размер блока для кодирования (символов): ");
    if (scanf("%d", &block_size) != 1 || block_size <= 0) block_size = 3;

    printf("\nПроцесс кодирования (Первый блок)\n");
    
    position = 0;
    long long encoded_bits_total = 0;
    int blocks_encoded = 0;
    int precision_issue = 0;

    uint32_t *reconstructed_data = (uint32_t*)malloc(total_characters * sizeof(uint32_t));
    int recon_position = 0;
    
    typedef struct {
        long double encoded_value;
        int required_bits;
        int block_length;
    } EncodedBlockData;
    
    EncodedBlockData *encoding_results = (EncodedBlockData*)malloc(sizeof(EncodedBlockData) *
                                               (total_characters / block_size + 1));
    int result_count = 0;

    // Сбрасываем позицию для обработки файла заново
    position = 0;
    
    while (position < file_size) {
        long double interval_low = 0.0L;
        long double interval_high = 1.0L;
        
        uint32_t block_chars[1024];
        int chars_in_block = 0;

        size_t temp_pos = position;
        size_t block_bytes = 0;
        
        while (chars_in_block < block_size && temp_pos < file_size) {
            uint32_t cp;
            size_t bytes_used;
            
            if (!get_utf8_char(file_buffer + temp_pos, file_size - temp_pos, 
                              &cp, &bytes_used)) {
                cp = file_buffer[temp_pos];
                bytes_used = 1;
            }
            
            block_chars[chars_in_block++] = cp;
            temp_pos += bytes_used;
            block_bytes += bytes_used;
        }

        if (blocks_encoded == 0 && chars_in_block > 0) {
            printf("БЛОК №%d (%d символов):\n", blocks_encoded+1, chars_in_block);
            printf("| Символ | Пред. Min | Пред. Диап. | Нов. Min | Нов. Max | Нов. Диап. |\n");
            printf("-----------------------------------------------------------------------\n");
            printf("| НАЧАЛО | 0.00000000 | 1.00000000 | 0.00000000 | 1.00000000 | 1.00000000 |\n");
        }

        for (int i = 0; i < chars_in_block; i++) {
            int idx = locate_char_index(char_data, char_count, block_chars[i]);
            if (idx == -1) {
                // Это не должно происходить, но на всякий случай
                continue;
            }
            
            long double current_range = interval_high - interval_low;
            
            if (current_range < 1e-100L) {  // Более разумный порог
                if (!precision_issue) {
                    printf("Потеря точности в блоке %d, символ %d. Диапазон: %.2Le\n", 
                           blocks_encoded+1, i+1, current_range);
                    precision_issue = 1;
                }
                break;
            }
            
            long double previous_low = interval_low;
            long double new_low = interval_low + current_range * char_data[idx].lower_bound;
            long double new_high = interval_low + current_range * char_data[idx].upper_bound;
            
            interval_low = new_low;
            interval_high = new_high;
            current_range = interval_high - interval_low;

            if (blocks_encoded == 0 && chars_in_block > 0 && i < 5) {  // Показываем только первые 5 символов
                printf("| %-6s | %.8Lf | %.8Lf | %.8Lf | %.8Lf | %.8Lf |\n", 
                       char_data[idx].utf8_str, previous_low, 
                       current_range, interval_low, interval_high, current_range);
            }
        }
        
        long double final_value;
        if (interval_low == interval_high) {
            final_value = interval_low;
        } else {
            final_value = (interval_low + interval_high) / 2.0L;
        }
        
        long double final_interval = interval_high - interval_low;
        
        int bits_required;
        if (final_interval > 0) {
            bits_required = (int)ceil(-log2l(final_interval)) + 1;
        } else {
            bits_required = 1;
        }
        
        if (bits_required <= 0) bits_required = 1;

        encoded_bits_total += bits_required;

        encoding_results[result_count].encoded_value = final_value;
        encoding_results[result_count].required_bits = bits_required;
        encoding_results[result_count].block_length = chars_in_block;
        result_count++;

        if (blocks_encoded == 0 && chars_in_block > 0) {
            printf("-----------------------------------------------------------------------\n");
            printf("\nРезультат кодирования Блока 1 (%d символов):\n", chars_in_block);
            printf("Интервал кода: [%.18Lf, %.18Lf)\n", interval_low, interval_high);
            printf("Код (десятичный): %.18Lf\n", final_value);
            printf("Код (двоичный, %d бит): ", bits_required);
            show_binary_representation(final_value, bits_required);
            printf("\nТребуемые биты: %d\n", bits_required);
        }

        position += block_bytes;
        blocks_encoded++;
        
        // Для тестирования покажем только первый блок
        if (blocks_encoded == 1) {
            // Можем прервать после первого блока для демонстрации
            // break;
        }
    }

    printf("\nПроцесс декодирования\n");
    printf("Декодируется %d блоков...\n", result_count);

    for (int b = 0; b < result_count; b++) {
        long double decode_low = 0.0L;
        long double decode_high = 1.0L;
        long double decode_value = encoding_results[b].encoded_value;
        int block_len = encoding_results[b].block_length;

        for (int k = 0; k < block_len; k++) {
            long double decode_range = decode_high - decode_low;
            if (decode_range <= 0) break;
            
            long double normalized_val = (decode_value - decode_low) / decode_range;

            int found_idx = -1;
            for (int s = 0; s < char_count; s++) {
                if (normalized_val >= char_data[s].lower_bound && 
                    normalized_val < char_data[s].upper_bound) {
                    found_idx = s;
                    break;
                }
            }
            
            if (found_idx == -1 && normalized_val >= char_data[char_count-1].lower_bound) {
                found_idx = char_count-1;
            }

            if (found_idx != -1) {
                long double char_low = char_data[found_idx].lower_bound;
                long double char_high = char_data[found_idx].upper_bound;
                
                decode_high = decode_low + decode_range * char_high;
                decode_low = decode_low + decode_range * char_low;

                reconstructed_data[recon_position++] = char_data[found_idx].code_point;
            } else {
                break;
            }
        }
    }

    long long original_bits = file_size * 8;
    double compression_percent = (double)encoded_bits_total / (double)original_bits * 100.0;
    
    long double information_entropy = 0.0L;
    for (int i = 0; i < char_count; i++) {
        if (char_data[i].probability > 0.0L) {
            information_entropy += -char_data[i].probability * log2l(char_data[i].probability);
        }
    }

    printf("\nИтоговые метрики сжатия\n");
    printf("----------------------------------------------------\n");
    printf("|         Параметр          |       Значение      |\n");
    printf("----------------------------------------------------\n");
    printf("| Исходный размер (байт) | %ld |\n", file_size);
    printf("| Исходный размер (бит)  | %lld |\n", original_bits);
    printf("| Энтропия (бит/символ)  | %.4Lf |\n", information_entropy);
    printf("| Всего символов         | %lld |\n", total_characters);
    printf("| Уникальных символов    | %d |\n", char_count);
    printf("| Закодировано (бит)     | %lld |\n", encoded_bits_total);
    printf("| Коэффициент сжатия     | %.2f%% |\n", compression_percent);
    printf("----------------------------------------------------\n");
    printf("Коэффициент сжатия = (Закодированный размер / Исходный размер) * 100%%\n");
    
    if (precision_issue) {
        printf("\nПри N=%d обнаружены ограничения точности типа long double.\n", block_size);
        printf("Рекомендуемый максимальный размер блока: 5-8 символов.\n");
    }

    printf("\nПроверка восстановления данных\n");
    int decoding_errors = 0;
    position = 0;
    int recon_idx = 0;
    
    while (position < file_size && recon_idx < recon_position) {
        uint32_t original_char;
        size_t bytes_read;
        
        if (!get_utf8_char(file_buffer + position, file_size - position, 
                          &original_char, &bytes_read)) {
            original_char = file_buffer[position];
            bytes_read = 1;
        }
        
        if (original_char != reconstructed_data[recon_idx]) {
            decoding_errors++;
        }
        
        position += bytes_read;
        recon_idx++;
    }

    if (decoding_errors == 0 && recon_idx == total_characters) {
        printf("Результат: данные восстановлены без ошибок.\n");
    } else {
        printf("Результат: найдено ошибок: %d из %lld символов\n", decoding_errors, total_characters);
        if (recon_idx != total_characters) {
            printf("Обработано символов: %d из %lld\n", recon_idx, total_characters);
        }
    }

    free(encoding_results);
    free(reconstructed_data);
    free(file_buffer);
    return 0;
}